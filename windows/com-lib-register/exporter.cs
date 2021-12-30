using System;
using System.Collections;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

// Export Options
public struct ExportOptions
{
   public string[] Names;
   public TypeLibExporterFlags Flags;
}

// Creates a type library from an assembly
public class Exporter : ITypeLibExporterNotifySink, ITypeLibExporterNameProvider
{
   private ExportOptions options;
   private TypeLibConverter converter;
   private IToolClient client;
   private Hashtable loadedTypeLibs;
   private string outputDirectory;

   // Constructor
   public Exporter(IToolClient client, Hashtable loadedTypeLibs)
   {
      this.client = client;
      this.loadedTypeLibs = loadedTypeLibs;
      this.converter = new TypeLibConverter();
   }

   // Property to get/set options
   public ExportOptions Options
   {
      get { return options; }
      set { options = value; }
   }

   // Output directory where type libraries will be saved
   public string OutputDirectory
   {
      set { outputDirectory = value; }
   }

   // Creates a type library with the given filename, library name,
   // and help file from the assembly specified by assemblyFilename
   public ITypeLib Export(string assemblyFilename, string tlbFilename,
   string libraryName, string helpFile)
   {
      Assembly assembly;

      try
      {
         // Load the assembly
         assembly = Assembly.LoadFrom(assemblyFilename);
      }
      catch
      {
         throw new ApplicationException("Unable to load the assembly \'" +
         assemblyFilename + "\'.");
      }

      outputDirectory = Path.GetDirectoryName(assemblyFilename);
      return Export(assembly, tlbFilename, libraryName, helpFile);
   }

   // Creates a type library with the given filename, library name,
   // and help file from the loaded input assembly
   public ITypeLib Export(Assembly assembly, string tlbFilename,
   string libraryName, string helpFile)
   {
      ITypeLib returnTypeLib;
      int numTypes = 0;

      // Before beginning export, check if the assembly has a type library
      // already embedded as a resource
      foreach (FileStream file in assembly.GetFiles())
      {
         try
         {
            // Attempt to load a type library
            returnTypeLib = Util.LoadTypeLibEx(file.Name,
            REGKIND.NONE);

            // It worked!
            if (client.AskYesNoQuestion("The assembly \'" + assembly.FullName +
            " contains an embedded type library inside the file \'" +
            file.Name + "\'. Would you like to load this type library " +
            "instead of exporting a new one?", true))
            {
               client.SendMessage(MessageTypes.BeginFile,
               "Embedded Type Library in " + file.Name, null);
               client.SendMessage(MessageTypes.EndFile,
               "Embedded Type Library in " + file.Name, returnTypeLib);
               loadedTypeLibs[Marshal.GetTypeLibGuid(returnTypeLib)]
               = returnTypeLib;
               return returnTypeLib;
            }
         }
         catch
         {
            // There must not be a type library embedded in this file
         }
      }

      // At this point, either none of the assembly’s files contain a type
      // library or the user selected not to use any of them.

      string assemblyDisplayName = "Type Library for " +
      Util.GetDisplayNameForAssembly(assembly);


      if (tlbFilename == null)
         tlbFilename = assembly.GetName().Name + ".tlb";

      client.SendMessage(MessageTypes.BeginFile, assemblyDisplayName,
      outputDirectory + Path.DirectorySeparatorChar + tlbFilename);

      try
      {
         // Get the total number of types for the progress bar
         // by tallying the number of types that will be exported
         foreach (Type t in assembly.GetTypes())
         {
            if (Marshal.IsTypeVisibleFromCom(t) && !t.IsImport)
               numTypes++;
         }
      }
      catch (Exception ex)
      {
         if (ex is System.Reflection.ReflectionTypeLoadException)
         {
            var typeLoadException = ex as ReflectionTypeLoadException;
            var loaderExceptions = typeLoadException.LoaderExceptions;
            foreach (var exc in loaderExceptions)
               client.SendMessage(MessageTypes.Warning, exc.Message, null);
         }
         throw new ApplicationException(ex.Message);
      }

      client.ProgressMaximum += numTypes;

      // Create a type library from the assembly
      returnTypeLib = (ITypeLib)converter.ConvertAssemblyToTypeLib(
      assembly,
      tlbFilename,
      options.Flags,
      this);

      // Change the library name if one is given
      if (libraryName != null)
         ((ICreateTypeLib)returnTypeLib).SetName(libraryName);

      // Add a help file name if one is given
      if (helpFile != null)
         ((ICreateTypeLib)returnTypeLib).SetHelpFileName(helpFile);

      client.SendMessage(MessageTypes.EndFile, assemblyDisplayName,
      returnTypeLib);
      loadedTypeLibs[Marshal.GetTypeLibGuid(returnTypeLib)] = returnTypeLib;

      ICreateTypeLib typeLib = (ICreateTypeLib)returnTypeLib;
      typeLib.SaveAllChanges();

      return returnTypeLib;
   }

   // Implementation of ITypeLibExporterNotifySink.ReportEvent
   public void ReportEvent(ExporterEventKind eventKind, int eventCode,
   string eventMsg)
   {
      MessageTypes messageType;

      // Get the MessageType for the corresponding ExporterEventKind
      switch (eventKind)
      {
         case ExporterEventKind.ERROR_REFTOINVALIDASSEMBLY:
            messageType = MessageTypes.InvalidRef;
            break;
         case ExporterEventKind.NOTIF_CONVERTWARNING:
            messageType = MessageTypes.Warning;
            break;
         case ExporterEventKind.NOTIF_TYPECONVERTED:
            messageType = MessageTypes.Notification;
            // Update the progress for type conversions
            client.Progress++;
            break;
         default:
            throw new ApplicationException(
               "Encountered unknown ExporterEventKind value.");
      }

      client.SendMessage(messageType, "[" +
      DateTime.Now.ToString("hh: mm:ss.f") + " 0x" +
      eventCode.ToString("x") + "] " + eventMsg, null);
   }

   // Implementation of ITypeLibExporterNotifySink.ResolveRef
   public object ResolveRef(Assembly assembly)
   {
      // If we’ve already loaded the necessary type library, return it
      ITypeLib returnTypeLib = (ITypeLib)
      loadedTypeLibs[Marshal.GetTypeLibGuidForAssembly(assembly)];

      if (returnTypeLib != null)
         return returnTypeLib;

      // Ask the user for either an assembly or type library to satisfy
      // the reference
      string filename = client.GetAssemblyReference(
      Util.GetDisplayNameForAssembly(assembly));

      if (filename != null)
      {
         try
         {
            // Load the type library without registering it
            returnTypeLib =
            Util.LoadTypeLibEx(filename, REGKIND.NONE);
         }
         catch
         {
            // Since LoadTypeLibEx didn’t work, this must be an assembly.
            // Export it with its default filename, library name, and
            // help file
            returnTypeLib = Export(filename, null, null, null);
         }
      }
      else
      {
         // Export the assembly passed into ResolveRef with its
         // default filename, library name, and help file
         returnTypeLib = Export(assembly, null, null, null);
      }

      return returnTypeLib;
   }

   // Implementation of ITypeLibExporterNameProvider.GetNames
   public string[] GetNames()
   {
      if (options.Names == null)
         return new string[] { };
      else
         return options.Names;
   }
}