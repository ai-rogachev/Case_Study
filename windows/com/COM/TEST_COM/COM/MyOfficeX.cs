using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace MyOfficeX.COM
{
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    [Guid("5B44EE53-3349-4380-92E8-A4458EBBC6E2")]
    [ProgId("MyOfficeX.Application")]
    public partial class MyOfficeX : UserControl, IMyOfficeX
    {
        [DllImport("msvcr120.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int _controlfp_s(out uint _CurrentState, uint _NewValue, uint _Mask);


        public MyOfficeX()
        {
            InitializeComponent();
        }

        public void LoadRTF(string rtf)
        {
            //const uint _MCW_EM = 0x009001F; //Interrupt exception mask

            //uint currentState = 0;
            //int r = _controlfp_s(out currentState, _MCW_EM, _MCW_EM);

            myRichEditControl1.SetText(rtf);
        }
    }
}
