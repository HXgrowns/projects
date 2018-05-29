using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

namespace Hml文件练习
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Fun1("love1.xml");
        }
        private  void Fun1(string filename)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(filename);
            XmlElement root = doc.DocumentElement;
            XmlNode port = doc.SelectSingleNode("/root/port");
           // XmlElement port = doc.CreateElement("port");
           // port.InnerText = "5";
            //root.AppendChild(port);
            port.InnerText = "21";
            doc.Save(filename);
            Console.WriteLine(port.InnerText);
        }
    }
}
