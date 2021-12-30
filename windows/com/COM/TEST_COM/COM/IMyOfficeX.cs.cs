using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace MyOfficeX.COM
{
    [ComVisible(true)]
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    [Guid("45DAAF22-02CA-4850-9D30-98AF6F631BCC")]
    public interface IMyOfficeX
    {
        [DispId(0x60020001)]
        void LoadRTF(string rtf);
    }
}
