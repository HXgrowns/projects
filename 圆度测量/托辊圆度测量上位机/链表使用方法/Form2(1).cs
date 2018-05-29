using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 链表使用方法
{
    public partial class Form2 : Form
    {
        LinkedList<int>datalist = new LinkedList<int>();//创建链表容器

        string[] a = {"1","2","3"};
        public Form2()
        {
            InitializeComponent();

            for (int i = 0; i < a.Length; i++)
            {
                datalist.AddLast(Convert.ToInt32(a[i]));//添加数据
                Console.WriteLine("添加数据到链表");
                
            }
            chart1.Series["Series1"].Points.DataBindY(datalist);
            foreach (int item in datalist)//遍历链表
            {
                
            }

        }

    }
}
