using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.OleDb;

namespace DoAccess
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OleDbConnection strConnection = new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + "data.accdb;" + "Persist Security Info=False");
            String sql = "select * from test";
            OleDbDataAdapter adapter = new OleDbDataAdapter(sql, strConnection);
            DataSet dataSet = new DataSet();
            adapter.Fill(dataSet, "");
            dataGridView1.DataSource = dataSet.Tables[""];
        }
    }
}
