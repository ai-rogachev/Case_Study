using System;
using System.Collections;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

// Registration Options
public struct RegisterOptions
{
   public AssemblyRegistrationFlags Flags;
}

// Registers and unregisters assemblies for COM
public class Registrar
{
    // Windows API to register a COM type library.
    [DllImport("Oleaut32.dll", 
        CallingConvention = CallingConvention.StdCall, 
        CharSet = CharSet.Unicode)]
    public extern static UInt32 RegisterTypeLib(
        ITypeLib tlib,
        string szFullPath,
        string szHelpDir);

    [DllImport("Oleaut32.dll", 
        CallingConvention = CallingConvention.StdCall, 
        CharSet = CharSet.Unicode)]
   internal static extern UInt32 UnRegisterTypeLib(
      ref Guid libID,
      UInt16 wVerMajor,
      UInt16 wVerMinor,
      int lcid,
      System.Runtime.InteropServices.ComTypes.SYSKIND syskind);

   private RegisterOptions options;
   private RegistrationServices registration;
   private IToolClient client;
   private Hashtable loadedAssemblies;

   // Constructor
   public Registrar(IToolClient client, Hashtable loadedAssemblies)
   {
      this.client = client;
      this.loadedAssemblies = loadedAssemblies;
      this.registration = new RegistrationServices();
   }

   // Property to get/set options
   public RegisterOptions Options
   {
      get { return options; }
      set { options = value; }
   }

   // Registers the assembly given by the filename
   public string Register(string assemblyName)
   {
      return Register(LoadAndDisplayAssembly(assemblyName));
   }

   // Unregisters the assembly given by the filename
   public string Unregister(string assemblyName)
   {
      return Unregister(LoadAndDisplayAssembly(assemblyName));
   }

   public string RegisterTlb(ITypeLib typeLib, string typeLibPath)
   {
      uint res = RegisterTypeLib(typeLib, typeLibPath, null);

      if (res == 0)
         return "TLB file registered successfully.";
      else
         return "Unexpected error: 0x{0:Х}" + res;
   }

   public string UnregisterTlb(string assemblyFilePath)
   {
      try
      {
         Assembly assembly = Assembly.LoadFrom(assemblyFilePath);
         //Assembly assembly = Assembly.Load(assemblyFilePath);

         Version version = assembly.GetName().Version;
         GuidAttribute guid_attribute = (GuidAttribute)assembly.GetCustomAttributes(typeof(GuidAttribute), false)[0];
         Guid guid = new Guid(guid_attribute.Value);
         System.Runtime.InteropServices.ComTypes.SYSKIND syskind;

         if (Is32Bits())
         {
            syskind = System.Runtime.InteropServices.ComTypes.SYSKIND.SYS_WIN32;
         }
         else if (Is64Bits())
         {
            syskind = System.Runtime.InteropServices.ComTypes.SYSKIND.SYS_WIN64;
         }
         else
         {
            return string.Format("Unknown bit-ness.");
         }

         uint uiRetTemp = UnRegisterTypeLib(ref guid, 
            (UInt16)(version.Major), 
            (UInt16)(version.Minor), 
            0, 
            syskind);

         string result;
         if (uiRetTemp == 0)
         {
            result = string.Format("TypeLib File for assembly [{0:S}] unregistered.", 
               assemblyFilePath);
         }
         else
         {
            result = string.Format("Failed to unregister TypeLib File for assembly [0x{0:S}]. Error code : [{1:X}]",
                assemblyFilePath, uiRetTemp);
         }
         return result;
      }
      catch (Exception ex)
      {
         return string.Format("An exception occurred. Exception description : [{0:S}].",
            ex.Message);
      }
   }

   // Registers the loaded assembly
   public string Register(Assembly assembly)
   {
      try
      {
         // Register the assembly
         if (registration.RegisterAssembly(assembly, options.Flags))
            return "Types registered successfully.";
         else
            return "There were no types to register.";
      }
      catch (TargetInvocationException ex)
      {
         // Construct a better message for registration function error
         throw new Exception("Error from custom registration function: " +
         ex.InnerException.Message, ex.InnerException);
      }
   }

   // Unregisters the loaded assembly
   public string Unregister(Assembly assembly)
   {
      try
      {
         // Unregister the assembly
         if (registration.UnregisterAssembly(assembly))
            return "Types unregistered successfully.";
         else
            return "There were no types to unregister.";
      }
      catch (TargetInvocationException ex)
      {
         // Construct a better message for unregistration function error
         throw new Exception("Error from custom unregistration function: " +
            ex.InnerException.Message, ex.InnerException);
      }
   }

   // Loads an assembly from the input filename and notifies
   // the client so it can display it.
   private Assembly LoadAndDisplayAssembly(string assemblyName)
   {
      Assembly returnAssembly;

      try
      {
         // Load the assembly
         returnAssembly = Assembly.LoadFrom(assemblyName);
         //returnAssembly = Assembly.Load(assemblyName);
      }
      catch
      {
         throw new ApplicationException("Unable to load the assembly \"" +
            assemblyName + "\".");
      }

      // Construct a nice "display name" for the assembly
      string assemblyDisplayName = "Assembly: " +
      Util.GetDisplayNameForAssembly(returnAssembly);

      // Notify the client that the assembly has been loaded.
      // Give both beginning and ending notifications since there’s no
      // progress to report.
      client.SendMessage(MessageTypes.BeginFile, assemblyDisplayName, null);
      client.SendMessage(MessageTypes.EndFile, assemblyDisplayName, null);
      loadedAssemblies[Marshal.GetTypeLibGuidForAssembly(returnAssembly)]
      = returnAssembly;

      return returnAssembly;
   }

   public static bool Is32Bits()
   {
      if (IntPtr.Size == 4)
      {
         // 32-bit
         return true;
      }

      return false;
   }

   public static bool Is64Bits()
   {
      if (IntPtr.Size == 8)
      {
         // 64-bit
         return true;
      }

      return false;
   }
}