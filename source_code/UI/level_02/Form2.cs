using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace level_02
{
    public partial class Form2 : Form
    {
        [DllImport("WorkDll.dll", EntryPoint = "getFeatures")]
        public static extern void getFeatures(string Path, int flag);

        [DllImport("WorkDll.dll", EntryPoint = "TrainFunction")]
        public static extern void TrainFunction(int num);

        public Form2()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form1 tmp = new Form1();
            tmp.Show();
            this.Hide();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        delegate void SetTextCallback(string text);
        private void setText(string text)
        {
            if (this.label1.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(setText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.label1.Text=text;
                this.label1.Refresh();
            }
        }
        private void CallToChild()
        {
            Thread childThred0 = new Thread(new ThreadStart(CallToChild_Child));
            childThred0.Start();
            while (childThred0.IsAlive)
            {
                Thread.Sleep(2000);
            }
            setText("训练完成！");
        }
        
        private void CallToChild_Child()
        {
            string Path = "../_t_male/";
            int tot = 0;
            DirectoryInfo TheFolder = new DirectoryInfo(Path);
            foreach (FileInfo nextFile in TheFolder.GetFiles())
            {
                string s_tmp = Path + nextFile.ToString();
                getFeatures(s_tmp, 0);
                tot++;
            }
            Path = "../_t_female/";
            TheFolder = new DirectoryInfo(Path);
            foreach (FileInfo nextFile in TheFolder.GetFiles())
            {
                string s_tmp = Path + nextFile.ToString();
                getFeatures(s_tmp, 1);
                tot++;
            }
            TrainFunction(tot);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            setText("训练中...");
            Thread childThred = new Thread(new ThreadStart(CallToChild));
            childThred.Start(); 
        }
    }
}
