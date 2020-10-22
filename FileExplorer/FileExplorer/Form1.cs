using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FileExplorer
{
    public partial class Form1 : Form
    {


        public Form1()
        {
            InitializeComponent();

            DriveInfo[] drives = DriveInfo.GetDrives();



            LeftDrive.Items.AddRange(drives);
            RightDrive.Items.AddRange(drives);

        }

        private void Open(CheckedListBox obj, string path)
        {
            bool isFile;
            isFile = File.Exists(path);

            if (isFile)
            {
                Process.Start(path);
                return;
            }


            if (obj == LeftExplorer)
            {
                LeftPath.Items.Clear();
                LeftPath.Items.AddRange(Directory.GetDirectories(path));
                LeftPath.Text = path;
            }
            else
            {
                RightPath.Items.Clear();
                RightPath.Items.AddRange(Directory.GetDirectories(path));
                RightPath.Text = path;
            }

            obj.Items.Clear();

            string[] dirs = Directory.GetDirectories(path);
            string[] files = Directory.GetFiles(path);

            foreach (var dir in dirs)
            {
                obj.Items.Add(dir.Substring(dir.LastIndexOf('\\') + 1));
            }

            foreach (var file in files)
            {
                obj.Items.Add(file.Substring(file.LastIndexOf('\\') + 1));
            }

            if(dirs.Length > 0)
             obj.SelectedIndex = 0;
        }

        private void Exit(CheckedListBox obj)
        {
            var file = obj == LeftExplorer ? LeftPath.Text : RightPath.Text;
            if (file.Length == 0) return;
            file = file.Substring(0, file.LastIndexOf('\\'));
            if (!file.Contains('\\')) file += '\\';
            Open(obj,file);
        }
        private void DriveSelected(object sender, EventArgs e)
        {
            if (((sender as ComboBox).SelectedItem as DriveInfo).IsReady)
            {
                string file = (sender as ComboBox).SelectedItem.ToString();
                if((sender as ComboBox) == LeftDrive)
                    Open(LeftExplorer, file);
                else
                    Open(RightExplorer,file);
            }
            else
            {
                MessageBox.Show("INSERT DRIVE", "", 
                    MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
        

        private void CheckBySquare(object sender, MouseEventArgs e)
        {
            if (!(sender is CheckedListBox checkedListBox)) return;
            if (checkedListBox.Items.Count == 0 || checkedListBox.SelectedIndex == -1) return;
            if (e.X > 13)
                checkedListBox.SetItemChecked(checkedListBox.SelectedIndex, !checkedListBox.GetItemChecked(checkedListBox.SelectedIndex));
        }

        private void ExplorerButtonDown(object sender, KeyEventArgs e)
        {
            if (!(sender is CheckedListBox checkedListBox)) return;
            if (checkedListBox.Items.Count == 0 || checkedListBox.SelectedIndex == -1) return;
            if (e.KeyData == Keys.Enter) 
                if(LeftPath.Text.Length == 3)
                    Open(checkedListBox, LeftPath.Text + checkedListBox.SelectedItem.ToString());
                else
                    Open(checkedListBox, LeftPath.Text + '\\' + checkedListBox.SelectedItem.ToString());
            else if (e.KeyData == Keys.Escape)
                Exit(checkedListBox);
        }

        private static void DirectoryCopy(string sourceDirName, string destDirName, bool copySubDirs)
        {
            // Get the subdirectories for the specified directory.
            DirectoryInfo dir = new DirectoryInfo(sourceDirName);

            if (!dir.Exists)
            {
                throw new DirectoryNotFoundException(
                    "Source directory does not exist or could not be found: "
                    + sourceDirName);
            }

            DirectoryInfo[] dirs = dir.GetDirectories();

            // If the destination directory doesn't exist, create it.       
            Directory.CreateDirectory(destDirName);

            // Get the files in the directory and copy them to the new location.
            FileInfo[] files = dir.GetFiles();
            foreach (FileInfo file in files)
            {
                string tempPath = Path.Combine(destDirName, file.Name);
                file.CopyTo(tempPath, false);
            }

            // If copying subdirectories, copy them and their contents to new location.
            if (copySubDirs)
            {
                foreach (DirectoryInfo subdir in dirs)
                {
                    string tempPath = Path.Combine(destDirName, subdir.Name);
                    DirectoryCopy(subdir.FullName, tempPath, copySubDirs);
                }
            }
        }

        private void Refresh()
        {
            if(Directory.Exists(LeftPath.Text))
                Open(LeftExplorer, LeftPath.Text);
            if (Directory.Exists(RightPath.Text))
                Open(RightExplorer, RightPath.Text);
        }

        private void Action(object sender, EventArgs e)
        {
            CheckedListBox FromExplorer;
            CheckedListBox ToExplorer;
            ComboBox FromPath;
            ComboBox ToPath;
            if ((sender as Button) == button_left)
            {
                FromExplorer = RightExplorer;
                ToExplorer = LeftExplorer;
                FromPath = RightPath;
                ToPath = LeftPath;
            }
            else
            {
                FromExplorer = LeftExplorer;
                ToExplorer = RightExplorer;
                FromPath = LeftPath;
                ToPath = RightPath;
            }
            if (action.SelectedIndex != -1)
            {
                switch (action.SelectedItem)
                {
                    case "MOVE":
                        foreach (string name in FromExplorer.CheckedItems)
                        {
                            string from;
                            if (ToPath.Text.EndsWith("\\"))
                                from = FromPath.Text + name;
                            else
                                from = FromPath.Text + '\\' + name;

                            string to;
                            if (ToPath.Text.EndsWith("\\"))
                                to = ToPath.Text + name;
                            else
                                to = ToPath.Text + '\\' + name;

                            if (from == to)
                            {
                                MessageBox.Show("Source and destination is same", "Senseless operation",
                                    MessageBoxButtons.OK, MessageBoxIcon.Information);
                                return;
                            }

                            if (File.Exists(name))
                            {
                                File.Move(from, to);
                            }
                            else
                            {
                                Directory.Move(from, to);
                            }
                        }
                        Refresh();
                        break;
                    case "COPY":
                        foreach (string name in FromExplorer.CheckedItems)
                        {
                            string from;
                            if (ToPath.Text.EndsWith("\\"))
                                from = FromPath.Text + name;
                            else
                                from = FromPath.Text + '\\' + name;

                            string to;
                            if (ToPath.Text.EndsWith("\\"))
                                to = ToPath.Text + name;
                            else
                                to = ToPath.Text + '\\' + name;

                            if (from == to)
                            {
                                MessageBox.Show("Source and destination is same", "Senseless operation",
                                    MessageBoxButtons.OK, MessageBoxIcon.Information);
                                return;
                            }

                            if (File.Exists(name))
                            {
                                File.Copy(from,to);
                            }
                            else
                            {
                                DirectoryCopy(from, to, true);
                            }
                        }
                        Refresh();
                        break;
                    case "DELETE":
                        List<string> toDel = new List<string>();
                        foreach (string name in ToExplorer.CheckedItems)
                        {
                            if (ToPath.Text.EndsWith("\\"))
                                toDel.Add(ToPath.Text + name);
                            else
                                toDel.Add(ToPath.Text + '\\' + name);
                        }

                        foreach (var name in toDel)
                        {
                            if (File.Exists(name))
                            {
                                //File.Delete(toDel);
                                MessageBox.Show("File removing is disabled", "Disabled operation",
                                    MessageBoxButtons.OK, MessageBoxIcon.Information);
                            }
                            else
                            {
                                try
                                {
                                    Directory.Delete(name);
                                }
                                catch
                                {
                                    MessageBox.Show("Removing not empty directories in disabled", "Disabled operation",
                                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                                }
                            }
                        }
                        Refresh();
                        break;
                    case "CREATE":

                        string path;

                        if (ToPath.Text.EndsWith("\\"))
                            path = ToPath.Text + CreateName.Text;
                        else
                            path = ToPath.Text + '\\' + CreateName.Text;
                        if (FileOrFolder.Text == "Folder" && !Directory.Exists(path))
                        {
                            Directory.CreateDirectory(path);
                        }
                        else if (FileOrFolder.Text == "File" && !File.Exists(path))
                        {
                            var my_file = File.Create(path);
                            my_file.Close();
                        }
                        else
                        {
                            MessageBox.Show("NAME IS TAKEN", "",
                                MessageBoxButtons.OK, MessageBoxIcon.Information);
                            int i = 1;
                            string temp = CreateName.Text;
                            while (true)
                            {
                                if (FileOrFolder.Text == "Folder")
                                {
                                    CreateName.Text = temp + i;
                                }
                                else
                                {
                                    CreateName.Text = temp.Insert(temp.LastIndexOf("."), i.ToString());
                                }

                                if (ToPath.Text.EndsWith("\\")) path = ToPath.Text + CreateName.Text;
                                else path = ToPath.Text + '\\' + CreateName.Text;
                                if(FileOrFolder.Text == "Folder" && !Directory.Exists(path)) return;
                                else if (FileOrFolder.Text == "File" && !File.Exists(path)) return;
                                
                                i++;
                            }
                        }
                        Refresh();
                        ToExplorer.SetSelected(ToExplorer.FindString(CreateName.Text),true);
                        break;
                }
            }

        }

        private void Up(object sender, EventArgs e)
        {
            Exit((sender as Button) == LeftExit ? LeftExplorer : RightExplorer);
        }

        private void FilePathKeyDown(object sender, KeyEventArgs e)
        {
            Open(LeftExplorer, (sender as ComboBox).Text);
        }

        private void PathChanged(object sender, EventArgs e)
        {
            if((sender as ComboBox) == LeftPath)
                Open(LeftExplorer, (sender as ComboBox).Text);
            else
                Open(RightExplorer, (sender as ComboBox).Text);
        }

        private void ExplorerDoubleClick(object sender, MouseEventArgs e)
        {
            if (!(sender is CheckedListBox checkedListBox)) return;
            if (checkedListBox.Items.Count == 0 || checkedListBox.SelectedIndex == -1) return;
            var Path = checkedListBox == LeftExplorer ? LeftPath : RightPath;
            if (Path.Text.Length == 3)
                Open(checkedListBox, Path.Text + checkedListBox.SelectedItem.ToString());
            else
                Open(checkedListBox, Path.Text + '\\' + checkedListBox.SelectedItem.ToString());

        }

        private void action_SelectedIndexChanged(object sender, EventArgs e)
        {
            if ((sender as ComboBox).SelectedIndex == 2)
            {
                FileOrFolder.Visible = true;
                FileOrFolder.Enabled = true;
            }
            else
            {
                FileOrFolder.Visible = false;
                FileOrFolder.Enabled = false;
            }
        }

        private void FileOrFolder_SelectedIndexChanged(object sender, EventArgs e)
        {
            if ((sender as ComboBox).SelectedIndex != -1)
            {
                CreateName.Visible = true;
                CreateName.Enabled = true;
                if ((sender as ComboBox).SelectedIndex == 0) CreateName.Text = "NewFolder";
                else CreateName.Text = "NewFile.txt";
            }
            else
            {
                FileOrFolder.Visible = false;
                FileOrFolder.Enabled = false;
            }
        }
    }
}
