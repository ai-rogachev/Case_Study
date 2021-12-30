
using System.Collections;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

class InteropTool
{
   IToolClient m_client;

   public InteropTool(IToolClient client)
   {
      m_client = client;
   }

   public void RegisterAssembly(
      string assemblyFilename, 
      string tlbFilename, 
      string libraryName)
   {
      // Create TLB file
      Hashtable loadedTypeLibs = new Hashtable();
      Exporter export = new Exporter(m_client, loadedTypeLibs);

      ITypeLib typeLib = export.Export(assemblyFilename, tlbFilename, libraryName, null);

      // Register assembly
      Hashtable loadedAssemblies = new Hashtable();
      Registrar registrar = new Registrar(m_client, loadedAssemblies);

      RegisterOptions option;
      option.Flags = AssemblyRegistrationFlags.SetCodeBase;

      registrar.Options = option;
      var res = registrar.Register(assemblyFilename);
      m_client.SendMessage(MessageTypes.Notification, res, null);
      
      // Register TLB
      res = registrar.RegisterTlb(typeLib, tlbFilename);
      m_client.SendMessage(MessageTypes.Notification, res, null);
   }

   public void UnregisterAssembly(string assemblyFilename)
   {
      Hashtable loadedAssemblies = new Hashtable();
      Registrar registrar = new Registrar(m_client, loadedAssemblies);
      
      // Unregister assembly
      var res = registrar.Unregister(assemblyFilename);
      m_client.SendMessage(MessageTypes.Notification, res, null);

      // Unregister TLB
      res = registrar.UnregisterTlb(assemblyFilename);
      m_client.SendMessage(MessageTypes.Notification, res, null);
   }
}