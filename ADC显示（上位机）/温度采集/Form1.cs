using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Xml;
using System.IO;
using System.Runtime.InteropServices;

namespace 温度采集
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;

            for (int i = 0; i < 10; i++)
            {
                comboBox2.Items.Add("COM" + i);
            }
            for (int i = 0; i < 10; i++)
            {
                comboBox1.Items.Add("COM" + i);
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            /* if (button1.Text == "打开串口")
             {
                 try
                 {
                     serialPort1.PortName = comboBox2.Text;
                     serialPort1.Open();
                     timer1.Enabled = true;
                     button1.Text = "关闭串口";
                     button1.BackColor = Color.FromArgb(0, 255, 0);

                 }
                 catch (Exception e1)
                 {
                     MessageBox.Show(e1.Message);
                 }
             }
             else
             {
                 serialPort1.Close();
                 timer1.Enabled = false;
                 button1.Text = "打开串口";
                 button1.BackColor = Color.FromArgb(3, 108, 3);
             }*/
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
           /* int data = serialPort1.ReadByte();
            double V = Math.Round(Convert.ToDouble(data) / 51, 3);
            double Rt = Math.Round(20 * V / (5 - V), 3);
            //double T = (Math.Log(Rt / 10)) / 3950 + 1 / 298.15;
            textBox1.Text = V + "V";
            textBox2.Text = Rt + "Ω";
            */
            string str = serialPort2.ReadLine();
            textBox3.Text = str;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort2.WriteLine(textBox4.Text);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            serialPort2.WriteLine(textBox5.Text);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            serialPort2.WriteLine(textBox6.Text);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            serialPort2.WriteLine(textBox9.Text);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            serialPort2.WriteLine(textBox8.Text);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            serialPort2.WriteLine(textBox7.Text);
        }

        private void button10_Click(object sender, EventArgs e)
        {
            serialPort2.WriteLine(textBox12.Text);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            serialPort2.WriteLine(textBox11.Text);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            textBox10.Text = textBox2.Text;
            serialPort2.WriteLine(textBox10.Text);
        }

        private void button11_Click(object sender, EventArgs e)
        {
            string jishu = Convert.ToString(0x1A);
            serialPort2.WriteLine(jishu);
        }

        private void button12_Click(object sender, EventArgs e)
        {
            if (button12.Text == "打开串口")
            {
                try
                {
                    serialPort2.PortName = comboBox1.Text;
                    serialPort2.BaudRate = Convert.ToInt32(comboBox3.Text);
                    serialPort2.Open();
                    button12.Text = "关闭串口";
                    button12.BackColor = Color.FromArgb(0,255,0);
                    

                }
                catch (Exception e1)
                {
                    MessageBox.Show(e1.Message);
                }
            }
            else
            {
                serialPort2.Close();
                button12.Text = "打开串口";
                button12.BackColor = Color.FromArgb(3,108,3);
            }
        }
    }
}
