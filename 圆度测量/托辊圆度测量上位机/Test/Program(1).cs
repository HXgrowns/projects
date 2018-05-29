using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;
using System.Runtime.InteropServices;
namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            string t = "";
            int[] a = { 8, 1, 3, 2, 6, 5, 9 };
            int max = a[0]; int min = a[0];
            for (int i = 0; i < a.Length; i++)
            {
                max = max > a[i] ? max : a[i];
                min = min < a[i] ? min : a[i];
            }
            Console.WriteLine("max =" + max + "min =" + min);
            Console.WriteLine("\n\n");
            Console.WriteLine("============LinkedList===============");

            //1.把数组a的值装入LinkedList
            LinkedList<int> list = new LinkedList<int>();
            for (int i = 0; i < a.Length; i++)
            {
                list.AddLast(a[i]);

            }

            foreach (int i in list)
            {
                max = max > i ? max : i;
            }
            // Console.WriteLine("max="+max);
            int b = Int32.Parse("1" + 2, System.Globalization.NumberStyles.HexNumber);


            ////2.LinkedList -> int[]
            //int[] b = list.ToArray();
            ////3.遍历找到最大值和最小值
            //for (int i = 0; i < b.Length; i++)
            //{
            //    max = max > b[i] ? max : b[i];
            //    min = min < b[i] ? min : b[i];
            //}
            //Console.WriteLine("max =" + max + "min =" + min);

            Console.WriteLine("\n\n============系统时间===============");
            // Console.WriteLine(b);
            t = System.DateTime.Now.ToString("mm:ss:ffff");
            Console.WriteLine(t);

            Console.WriteLine("\n\n============配置文件（xml文件）===============");
            //fun1("app1.xml");
            //fun2("app2.xml");
            //fun3("app2.xml");
            fun4("app4.xml");
        }

        /// <summary>
        /// 往xml文件里添加节点
        /// </summary>
        /// <param name="fileName">文件路径+文件名</param>
        public static void fun1(string fileName)
        {
            //create document
            XmlDocument doc = new XmlDocument();

            //【1】load file
            doc.Load(fileName);

            //【2】get root node
            XmlElement root = doc.DocumentElement;

            //【3】create new node
            //1.create son node
            XmlElement port = doc.CreateElement("port");
            //2.set son node value
            port.InnerText = "5";
            //3.add to root node
            root.AppendChild(port);

            //1.
            XmlElement buadRate = doc.CreateElement("buadrate");
            //2.
            buadRate.InnerText = "9600";
            //3.
            root.AppendChild(buadRate);

            //【4】save file
            doc.Save(fileName);
        }

        /// <summary>
        /// 往xml文件里添加或更新节点(不重复)
        /// </summary>
        /// <param name="fileName">文件路径+文件名</param>
        public static void fun2(string fileName)
        {
            //create document
            XmlDocument doc = new XmlDocument();

            //【1】load file
            doc.Load(fileName);

            //【2】get root node
            XmlElement root = doc.DocumentElement;

            //【3】find port node
            XmlNode portNode = doc.SelectSingleNode("/root/port");
            if (portNode == null)
            {
                // if not exist: create port node
                //1.
                XmlElement port = doc.CreateElement("port");
                //2.
                port.InnerText = "20";
                //3.
                root.AppendChild(port);
            }
            else
            {
                // if exist: update value
                portNode.InnerText = "20";
            }

            XmlNode buadRateNode = doc.SelectSingleNode("/root/buadrate");
            if (buadRateNode == null)
            {
                // if not exist: create port node
                //1.
                XmlElement buadRate = doc.CreateElement("buadrate");
                //2.
                buadRate.InnerText = "6666";
                //3.
                root.AppendChild(buadRate);
            }
            else
            {
                // if exist: update value
                buadRateNode.InnerText = "6666";
            }

            //【4】save file
            doc.Save(fileName);
        }

        /// <summary>
        /// 读取xml文件
        /// </summary>
        /// <param name="fileName"></param>
        public static void fun3(string fileName)
        {
            //create document
            XmlDocument doc = new XmlDocument();

            //【1】load file
            doc.Load(fileName);

            //【2】find port node
            XmlNode portNode = doc.SelectSingleNode("/root/port");

            //【3】judge find result
            if (portNode != null)
            {
                String port = portNode.InnerText;
                Console.WriteLine("端口号：" + port);
            }
            else
            {
                Console.WriteLine("未查到端口号！");
            }

            XmlNode buadRateNode = doc.SelectSingleNode("/root/buadrate");
            if (buadRateNode != null)
            {
                String buadRate = buadRateNode.InnerText;
                Console.WriteLine("波特率：" + buadRate);
            }
            else
            {
                Console.WriteLine("未查到波特率！");
            }

            //【4】save file
            doc.Save(fileName);
        }

        /// <summary>
        /// 空文件里添加节点
        /// </summary>
        /// <param name="fileName"></param>
        public static void fun4(string fileName)
        {
            XmlDocument doc = new XmlDocument();

            //判断文件是否存在，不存在则创建之
            if (!File.Exists(fileName))
            {
                //【1】创建文件（一定要关闭）
                FileStream fs = File.Create(fileName);
                fs.Close();

                //【2】创建声明
                XmlDeclaration declaration = doc.CreateXmlDeclaration("1.0", "utf-8", null);
                doc.AppendChild(declaration);

                //【3】创建根节点
                XmlElement root = doc.CreateElement("root");
                doc.AppendChild(root);

                //【4】保存文件
                doc.Save(fileName);
            }

            doc.Load(fileName);

            //进行相关操作

            doc.Save(fileName);
        }

    }
}
