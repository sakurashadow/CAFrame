using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SmartEkwing.Win32API
{
    class CAlib
    {
        const string str = @"dll/CAlib";
        //同步
        [DllImport(str, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static int register_server([MarshalAs(UnmanagedType.LPStr)] string bucket, [MarshalAs(UnmanagedType.LPStr)]string pServerName, bool is_print_log);
        // public extern static int register_server([MarshalAs(UnmanagedType.LPStr)] string pServerName, bool is_print_log);
        [DllImport(str, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static  int init(bool is_print_log);
        [DllImport(str, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public extern static int cmdExec(byte[] pRet, [MarshalAs(UnmanagedType.LPStr)]string pServerName, [MarshalAs(UnmanagedType.LPStr)]string pServerItemName,byte[] param);
        //异步
        [System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate void CallbackDelegate(int size, [MarshalAs(UnmanagedType.LPArray, SizeConst = 1024)]byte[] array); 

        [DllImport(str, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public extern static void cmdExecAsync(CallbackDelegate callback,
            [MarshalAs(UnmanagedType.LPStr)]string pServerName,
            [MarshalAs(UnmanagedType.LPStr)]string pServerItemName,
            byte[] param, int nLenParam);
    }
}
