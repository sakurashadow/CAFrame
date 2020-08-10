using SmartEkwing.Win32API;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Reflection;
using static SmartEkwing.Win32API.CAlib;
using System.Threading;
using System.Diagnostics;

namespace callCdll
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {

        CallbackDelegate deleRecv;
        CallbackDelegate deleSend;
        public void recvcb(int size , byte[] array)
        {
            //this.Dispatcher.Invoke(() =>
            //{
            //    string str = System.Text.Encoding.UTF8.GetString(array, 0, size);
            //    recvbox.Text += str + "\r\n";
            //});
        }
        public void sendcb(int size, byte[] array)
        {
            string str = System.Text.Encoding.UTF8.GetString(array, 0, size + 1); //BitConverter.ToString(k);
            Console.WriteLine(str);
        }
        public class set_server_client_name
        {
            public string server { get; set; }
            public string client { get; set; }
            public int callback_addr { get; set; }
        }
   
        public MainWindow()
        {
            InitializeComponent();
            deleRecv = new CallbackDelegate(recvcb);
            deleSend = new CallbackDelegate(sendcb);
            var ret0 = CAlib.init(true);
         //   var ret2 = CAlib.register_server("dll","zhugeIO", true);
            var ret = CAlib.register_server("dll","IPC", true);
        }
        //发送
        private void send_Click(object sender, RoutedEventArgs e)
        {
            Stopwatch sw = new Stopwatch();
            sw.Start();
            for (int i=0;i<10000;i++)
            {
                int a = i + i-1;

                //byte[] byteArr = System.Text.Encoding.UTF8.GetBytes(sendbox.Text);
                //int k = sizeof(byte);
                //CAlib.cmdExecAsync(deleSend, "IPC", "client_send", byteArr, byteArr.Length*k);
            }
            sw.Stop();
            Console.WriteLine("span = {0}",sw.ElapsedMilliseconds);
        }
        IntPtr testValueIntPtr1;
        //连接远程应用
        private void Button_Click(object sender, RoutedEventArgs e)
        {
                testValueIntPtr1 = Marshal.GetFunctionPointerForDelegate(deleRecv);
                Console.WriteLine(testValueIntPtr1);
                set_server_client_name param = new set_server_client_name();
                param.server = local.Text;
                param.client = remote.Text;
                param.callback_addr = (int)testValueIntPtr1;

                var str = Newtonsoft.Json.JsonConvert.SerializeObject(param);
                byte[] byteArray = System.Text.Encoding.ASCII.GetBytes(str);
                CAlib.cmdExec(null, "IPC", "client_init", byteArray);
        }
    }
}
