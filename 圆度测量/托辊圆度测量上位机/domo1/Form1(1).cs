using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.Threading;
using System.Xml;
using System.IO;
using System.Runtime.InteropServices;

namespace domo1
{
    public partial class Form1 : Form
    {
        private int num = 100;
        private byte[] receive = new byte[21];
        private LinkedList<double> dataList1 = new LinkedList<double>();//利用链表类（容器类）创造一个可以装double的容器
        //private LinkedList<double> dataList2 = new LinkedList<double>();
        //private LinkedList<double> dataList3 = new LinkedList<double>();

        private string fileName = "app.xml";

        public Form1()
        {
            InitializeComponent();
            button2.Text = "采集";
            for (int i = 1; i < 17; i++)
            {
                comboBox1.Items.Add("COM" + i);
            }
            for (int i = 0; i < 17; i++)
            {
                try
                {
                    serialPort1.PortName = "COM" + i;
                    serialPort1.Open();
                    serialPort1.Close();
                }
                catch
                {
                }
            }

            //【1】加载配置文件，获得属性（读xml）
            XmlDocument xmlDoc = new XmlDocument();

            //下面用来处理文件不存在的情况
            if (!File.Exists(fileName))
            {
                FileStream fs = File.Create(fileName);
                fs.Close();

                XmlDeclaration xmlDec = xmlDoc.CreateXmlDeclaration("1.0", "UTF-8", null);
                xmlDoc.AppendChild(xmlDec);

                XmlElement root = xmlDoc.CreateElement("root");
                xmlDoc.AppendChild(root);

                xmlDoc.Save(fileName);
            }

            //【2】
            xmlDoc.Load("app.xml");

            //【3】
            XmlNode portNode = xmlDoc.SelectSingleNode("/root/port");
            if (portNode != null)
            {
                //加载到了配置信息
                comboBox1.Text = portNode.InnerText;
            }
            else
            {
                //没有配置信息，给一默认值
                comboBox1.SelectedIndex = 0;
            }


        }

        [DllImport("winmm.dll")]
        public static extern bool PlaySound(String Filename, int Mod, int Flags); 
        private void Form1_Load(object sender, EventArgs e)
        {
            button1.BackColor = Color.FromArgb(0, 255, 0);
            button3.BackColor = Color.FromArgb(0, 255, 0);
            button4.BackColor = Color.FromArgb(0, 255, 0);

            Form1_SizeChanged(null, null);//窗体上的控件自适应
        }



        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            //#region 绘制试点1图线及数据处理
            //byte[] y1 = new byte[2];
            //dataList.AddLast(receive[6]);
            //dataList.AddLast(receive[7]);
            //y1 = dataList.ToArray();
            ////y1 = (Convert.ToDouble(y1))/1000;
            //y1 = Math.Round(y1, 3);

            //dataList.AddLast(y1);
            //if (dataList.Count > num)
            //{
            //    dataList.RemoveFirst();
            //}

            //chart1.Series["Series1"].Points.DataBindY(dataList);
            //double max1 = dataList.First();
            //double min1 = dataList.First();
            //foreach (double i in dataList)
            //{
            //    max1 = max1 > i ? max1 : i;
            //    min1 = min1 < i ? min1 : i;
            //}
            //textBox1.Text = Convert.ToString(max1);
            //textBox2.Text = Convert.ToString(min1);
            //textBox3.Text = Convert.ToString(max1 - min1);
            //# endregion

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (button2.Text.Equals("采集"))
            {
                serialPort1.PortName = comboBox1.Text;
                serialPort1.Open();
                timer2.Enabled = true;
                button2.Text = "暂停";

                XmlDocument doc = new XmlDocument();
                doc.Load(fileName);

                XmlNode node = doc.SelectSingleNode("/root/port");
                if (node == null)
                {
                    //创建
                    XmlElement element = doc.CreateElement("port");
                    element.InnerText = comboBox1.Text;
                    doc.DocumentElement.AppendChild(element);
                }
                else
                {
                    //更新
                    node.InnerText = comboBox1.Text;
                }
                doc.Save(fileName);
            }
            else
            {
                button2.Text = "采集";
                serialPort1.Close();
                timer2.Enabled = false;
                textBox3.Text = "0";
                button1.BackColor = Color.FromArgb(0, 255, 0);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            #region 试点1警示颜色处理

            if (Double.Parse(textBox3.Text) > 3)
            {
                if (button1.BackColor.Equals(Color.Red))
                {
                    button1.BackColor = Color.FromArgb(255, 255, 210);
                }
                else
                {
                    button1.BackColor = Color.Red;
                }
                PlaySound("D:/KuGou/music.mp3", 0, 1);
            }
            #endregion
            #region 试点2警示颜色处理
            if (Double.Parse(textBox6.Text) > 6)
            {
                if (button3.BackColor.Equals(Color.Red))
                {
                    button3.BackColor = Color.FromArgb(255, 255, 210);
                }
                else
                {
                    button3.BackColor = Color.Red;
                }
            }
            #endregion
            #region 试点3警示颜色处理
            if (Double.Parse(textBox9.Text) > 6)
            {
                if (button4.BackColor.Equals(Color.Red))
                {
                    button4.BackColor = Color.FromArgb(255, 255, 210);
                }
                else
                {
                    button4.BackColor = Color.Red;
                }
            }
            #endregion
        }


        private void Form1_SizeChanged(object sender, EventArgs e)
        {
            int gap = 5;
            int perY = (this.Height - 80) / 3;

            groupBox1.Location = new Point(gap, gap);
            groupBox1.Size = new Size(this.Width - 20, perY - 2 * gap);

            groupBox2.Location = new Point(gap, gap + perY);
            groupBox2.Size = new Size(this.Width - 20, perY - 2 * gap);

            groupBox3.Location = new Point(gap, gap + 2 * perY);
            groupBox3.Size = new Size(this.Width - 20, perY - 2 * gap);
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            byte[] buffer = { 0x80, 0x03, 0x00, 0x00, 0x00, 0x08, 0x5A, 0x1D };
            serialPort1.Write(buffer, 0, buffer.Length);

            int count = serialPort1.Read(receive, 0, 21);
            for (int i = 0; i < 21; i++)
            {
                Console.Write(receive[i] + " ");
            }
            int data1 = 0;
            //int data2 = 0;
            //int data3 = 0;
            double y1 = 0;
            //double y2 = 0;
            //double y3 = 0;
            #region 试点1数据接收及处理
            if (count != 21)
            {

            }
            else
            {
                data1 = receive[5] * 16 * 16 + receive[6];
                y1 = (Convert.ToDouble(data1) / 1000);
                y1 = Math.Round(y1, 3);
                Console.WriteLine(y1);
                dataList1.AddLast(y1);
                if (dataList1.Count > num)
                {
                    dataList1.RemoveFirst();
                }

                #region 试点1图像处理
                chart1.Series["Series1"].Points.DataBindY(dataList1);
                double max1 = 0;
                double min1 = 0;
                foreach (double i in dataList1)
                {
                    max1 = max1 > i ? max1 : i;
                    min1 = min1 < i ? min1 : i;
                }
                textBox1.Text = Convert.ToString(max1);
                textBox2.Text = Convert.ToString(min1);
                textBox3.Text = Convert.ToString(max1 - min1);
                #endregion
            }
            #endregion
            #region 试点2数据接收及处理
            //if (count != 21)
            //{

            //}
            //else
            //{
            //    data2 = Int32.Parse(receive[9] + "" + receive[10], System.Globalization.NumberStyles.HexNumber);
            //    y2 = Convert.ToDouble(data2) / 1000;
            //    y2 = Math.Round(y2, 3);
            //    dataList2.AddLast(y2);
            //    if (dataList2.Count > num)
            //    {
            //        dataList2.RemoveFirst();
            //    }
            #region 试点2图像处理
            //chart2.Series["Series1"].Points.DataBindY(dataList2);
            //double max2 = dataList2.First();

            //double min2 = dataList2.First();
            //foreach (double i in dataList2)
            //{
            //    max2 = max2 > i ? max2 : i;
            //    min2 = min2 < i ? min2 : i;
            //}
            //textBox4.Text = Convert.ToString(max2);
            //textBox5.Text = Convert.ToString(min2);
            //textBox6.Text = Convert.ToString(max2 - min2);
            #endregion
            //}
            #endregion
            #region 试点3数据接收及处理
            //if (count != 21)
            //{

            //}
            //else
            //{
            //    data3 = Int32.Parse(receive[13] + "" + receive[14], System.Globalization.NumberStyles.HexNumber);
            //    y3 = Convert.ToDouble(data3) / 1000;
            //    y3 = Math.Round(y3, 3);
            //    dataList2.AddLast(y3);
            //    if (dataList3.Count > num)
            //    {
            //        dataList3.RemoveFirst();
            //    }
            #region 试点3图像处理
            //chart3.Series["Series1"].Points.DataBindY(dataList3);
            //double max3 = dataList3.First();
            //double min3 = dataList3.First();
            //foreach (double i in dataList3)
            //{
            //    max3 = max3 > i ? max3 : i;
            //    min3 = min3 < i ? min3 : i;
            //}
            //textBox7.Text = Convert.ToString(max3);
            //textBox8.Text = Convert.ToString(min3);
            //textBox9.Text = Convert.ToString(max2 - min3);
            #endregion
            //}
            #endregion
            #region 与系统当前时间同步
            // t = System.DateTime.Now.ToString("hh:mm:ss\nyyyy-MM-dd");
            // Console.WriteLine(t);
            //timer.AddLast(t);
            //if (timer.Count > num)
            //{
            //    timer.RemoveFirst();
            //}
            #endregion
        }
    }
}
