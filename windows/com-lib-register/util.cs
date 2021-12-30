using System;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

// Contains common functions used by the other classes
internal class Util
{
   // Load a type library from a filename
   [DllImport("oleaut32.dll", CharSet = CharSet.Unicode, PreserveSig = false)]
   internal static extern ITypeLib LoadTypeLibEx(string szFile,
   REGKIND regkind);

   // Unregister a type library
   [DllImport("oleaut32.dll", PreserveSig = false)]
   internal static extern void UnRegisterTypeLib(ref Guid libID,
   short wVerMajor, short wVerMinor, int lcid, System.Runtime.InteropServices.ComTypes.SYSKIND syskind);

   // Return a nice-looking "display name" for the input assembly
   internal static string GetDisplayNameForAssembly(Assembly assembly)
   {
      if (assembly.GetCustomAttributes(
      typeof(AssemblyTitleAttribute), false).Length > 0)
      {
         AssemblyTitleAttribute attribute =
         (AssemblyTitleAttribute)(assembly.GetCustomAttributes(
         typeof(AssemblyTitleAttribute), false)[0]);

         return attribute.Title + " (" +assembly.FullName + ")";
      }
      else if (assembly.GetCustomAttributes(
      typeof(AssemblyDescriptionAttribute), false).Length > 0)
      {
         AssemblyDescriptionAttribute attribute =
         (AssemblyDescriptionAttribute)(assembly.GetCustomAttributes(
         typeof(AssemblyDescriptionAttribute), false)[0]);

         return attribute.Description + " (" +assembly.FullName + ")";
      }
      else
      {
         return assembly.FullName;
      }
   }

   // Return a nice-looking "display name" for the input type library
   internal static string GetDisplayNameForTypeLib(ITypeLib typeLib)
   {
      string typeLibName;
      string typeLibDocString;
      string typeLibHelpFile;
      int typeLibHelpContext;

      // Calling GetDocumentation with an index of -1 gets documentation
      // for the library itself.
      typeLib.GetDocumentation(-1, out typeLibName, out typeLibDocString,
      out typeLibHelpContext, out typeLibHelpFile);

      if (typeLibDocString != null)
         return typeLibDocString;
      else
         return typeLibName;
   }
}

// Implemented by users of the Importer, Exporter, Registrar, and/or
// ComPlusInstaller classes to receive notifications
public interface IToolClient
{
   void SendMessage(MessageTypes type, string message, object data);
   string GetAssemblyReference(string assemblyDisplayName);
   bool AskYesNoQuestion(string question, bool defaultIsYes);
   int ProgressMaximum { get; set; }
   int Progress { get; set; }
}

// Message types sent via IToolClient.SendMessage
public enum MessageTypes
{
   InvalidRef,
   Warning,
   Notification,
   BeginFile,
   EndFile
}

// REGKIND enumeration used by LoadTypeLibEx
internal enum REGKIND
{
   DEFAULT = 0,
   REGISTER = 1,
   NONE = 2
}

// An almost-complete definition of ICreateTypeLib that returns
// an IntPtr from CreateTypeInfo rather than an ICreateTypeInfo
// interface, to avoid having to define ICreateTypeInfo.
[
ComImport,
Guid("00020406-0000-0000-C000-000000000046"),
InterfaceType(ComInterfaceType.InterfaceIsIUnknown)
]
internal interface ICreateTypeLib
{
   IntPtr CreateTypeInfo(string szName, System.Runtime.InteropServices.ComTypes.TYPEKIND tkind);
   void SetName(string szName);
   void SetVersion(short wMajorVerNum, short wMinorVerNum);
   void SetGuid(ref Guid guid);
   void SetDocString(string szDoc);
   void SetHelpFileName(string szHelpFileName);
   void SetHelpContext(int dwHelpContext);
   void SetLcid(int lcid);
   void SetLibFlags(uint uLibFlags);
   void SaveAllChanges();
}