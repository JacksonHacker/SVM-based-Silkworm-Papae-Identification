using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace level_02
{
    public partial class Form1 : Form
    {
        [DllImport("WorkDll.dll", EntryPoint = "WorkFunction")]
        public static extern int WorkFunction(string Path);
        public Form1()
        {
            InitializeComponent();
            var pos = this.PointToScreen(label1.Location);
            pos = pictureBox1.PointToClient(pos);
            label1.Parent = pictureBox1;
            label1.Location = pos;
            label1.BackColor = Color.Transparent;

            pos = this.PointToScreen(label2.Location);
            pos = pictureBox2.PointToClient(pos);
            label2.Parent = pictureBox2;
            label2.Location = pos;
            label2.BackColor = Color.Transparent;

            pos = this.PointToScreen(label3.Location);
            pos = pictureBox3.PointToClient(pos);
            label3.Parent = pictureBox3;
            label3.Location = pos;
            label3.BackColor = Color.Transparent;

            pos = this.PointToScreen(label4.Location);
            pos = pictureBox4.PointToClient(pos);
            label4.Parent = pictureBox4;
            label4.Location = pos;
            label4.BackColor = Color.Transparent;

            pos = this.PointToScreen(label5.Location);
            pos = pictureBox5.PointToClient(pos);
            label5.Parent = pictureBox5;
            label5.Location = pos;
            label5.BackColor = Color.Transparent;

            pos = this.PointToScreen(label6.Location);
            pos = pictureBox6.PointToClient(pos);
            label6.Parent = pictureBox6;
            label6.Location = pos;
            label6.BackColor = Color.Transparent;

            pos = this.PointToScreen(label7.Location);
            pos = pictureBox7.PointToClient(pos);
            label7.Parent = pictureBox7;
            label7.Location = pos;
            label7.BackColor = Color.Transparent;


            pos = this.PointToScreen(label8.Location);
            pos = pictureBox8.PointToClient(pos);
            label8.Parent = pictureBox8;
            label8.Location = pos;
            label8.BackColor = Color.Transparent;

            pos = this.PointToScreen(label9.Location);
            pos = pictureBox9.PointToClient(pos);
            label9.Parent = pictureBox9;
            label9.Location = pos;
            label9.BackColor = Color.Transparent;

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private string sexJudge(string s)
        {
            int judge = WorkFunction(s);
            string result;
            if (judge == 1)
            {
                label1.Visible = true;
                label1.ForeColor = Color.Red;
                result = "雌\n性";
            }
            else if (judge == -1)
            {
                label1.Visible = true;
                label1.ForeColor = Color.Green;
                result = "雄\n性";
            }
            else
            {
                label1.Visible = true;
                result = "WRONG";
            }
            return result;
        }

        private void show_picture_result(int index, string result, string path)
        {
            
            switch (index)
            {
                case 1:
                    pictureBox1.Image = new Bitmap(new Bitmap(path), pictureBox1.Width, pictureBox1.Height);
                    pictureBox1.Visible = true;
                    label1.Visible = true;
                   
                    label1.Text = result;
                    label1.ForeColor = Color.Green;
                    if (result == "雌\n性") label1.ForeColor = Color.Red;
                    break;
                case 2:
                    pictureBox2.Image = new Bitmap(new Bitmap(path), pictureBox2.Width, pictureBox2.Height);
                    pictureBox2.Visible = true;
                    //pictureBox2.Update();
                    label2.Visible = true;
                   
                    label2.Text = result;
                    label2.ForeColor = Color.Green;
                    if (result == "雌\n性") label2.ForeColor = Color.Red;

                    break;
                case 3:
                    pictureBox3.Image = new Bitmap(new Bitmap(path), pictureBox3.Width, pictureBox3.Height);
                    pictureBox3.Visible = true;
                    label3.Visible = true;
                    label3.Text = result;
                    label3.ForeColor = Color.Green;
                    if (result == "雌\n性") label3.ForeColor = Color.Red;

                    break;
                case 4:
                    pictureBox4.Image = new Bitmap(new Bitmap(path), pictureBox4.Width, pictureBox4.Height);
                    pictureBox4.Visible = true;
                    label4.Visible = true;
                    label4.Text = result;
                    label4.ForeColor = Color.Green;
                    if (result == "雌\n性") label4.ForeColor = Color.Red;

                    break;
                case 5:
                    pictureBox5.Image = new Bitmap(new Bitmap(path), pictureBox5.Width, pictureBox5.Height);
                    pictureBox5.Visible = true;
                    label5.Visible = true;
                    label5.Text = result;
                    label5.ForeColor = Color.Green;
                    if (result == "雌\n性") label5.ForeColor = Color.Red;

                    break;
                case 6:
                    pictureBox6.Image = new Bitmap(new Bitmap(path), pictureBox6.Width, pictureBox6.Height);
                    pictureBox6.Visible = true;
                    label6.Visible = true;
                    label6.Text = result;
                    label6.ForeColor = Color.Green;
                    if (result == "雌\n性") label6.ForeColor = Color.Red;
                    break;
                case 7:
                    pictureBox7.Image = new Bitmap(new Bitmap(path), pictureBox7.Width, pictureBox7.Height);
                    pictureBox7.Visible = true;
                    label7.Visible = true;
                    label7.Text = result;
                    label7.ForeColor = Color.Green;
                    if (result == "雌\n性") label7.ForeColor = Color.Red;

                    break;
                case 8:
                    pictureBox8.Image = new Bitmap(new Bitmap(path), pictureBox8.Width, pictureBox8.Height);
                    pictureBox8.Visible = true;
                    label8.Visible = true;
                    label8.Text = result;
                    label8.ForeColor = Color.Green;
                    if (result == "雌\n性") label8.ForeColor = Color.Red;

                    break;
                case 9:
                    pictureBox9.Image = new Bitmap(new Bitmap(path), pictureBox9.Width, pictureBox9.Height);
                    pictureBox9.Visible = true;
                    label9.Visible = true;
                    label9.Text = result;
                    label9.ForeColor = Color.Green;
                    if (result == "雌\n性") label9.ForeColor = Color.Red;

                    break;
            }
        }

        private void clearBox()
        {
            pictureBox1.Image = null;
            pictureBox2.Image = null;
            pictureBox3.Image = null;
            pictureBox4.Image = null;
            pictureBox5.Image = null;
            pictureBox6.Image = null;
            pictureBox7.Image = null;
            pictureBox8.Image = null;
            pictureBox9.Image = null;
            pictureBox1.Invalidate();
            pictureBox2.Invalidate();
            pictureBox3.Invalidate();
            pictureBox4.Invalidate();
            pictureBox5.Invalidate();
            pictureBox6.Invalidate();
            pictureBox7.Invalidate();
            pictureBox8.Invalidate();
            pictureBox9.Invalidate();
            label1.Text = null;
            label1.Invalidate();
            label2.Text = null;
            label2.Invalidate();
            label3.Text = null;
            label3.Invalidate();
            label4.Text = null;
            label4.Invalidate();
            label5.Text = null;
            label5.Invalidate();
            label6.Text = null;
            label6.Invalidate();
            label7.Text = null;
            label7.Invalidate();
            label8.Text = null;
            label8.Invalidate();
            label9.Text = null;
            label9.Invalidate();

        }

        private void button2_Click(object sender, EventArgs e)
        {
            clearBox();
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = true;
            Stream mystream;
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                if ((mystream = dialog.OpenFile()) != null)
                {
                    for(int i = 0; i < dialog.FileNames.Length && i<9; i++)
                    {
                        string path = dialog.FileNames[i].ToString();
                        string result = sexJudge(path);
                        show_picture_result(i + 1, result, path);
                    }
                }
            }
            else return;
        }

     }
}
