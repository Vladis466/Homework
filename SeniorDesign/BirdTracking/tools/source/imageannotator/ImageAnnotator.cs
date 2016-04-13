using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Threading;
using System.Reflection;
using VideoSource;
using Tiger.Video.VFW;
using CameraSource;
using UserComponet;

namespace SampleCropor
{
   
    public partial class ImageAnnotator : Form
    {
        UserComponet.OutputWindow outputWindow;
        public ImageAnnotator()
        {
          
            InitializeComponent();
            InitializeOutputWindows();
            InitializeOtherStaff();
        }

        private void InitializeOtherStaff()
        {
            drawFont = this.Font;

            mainToolStrip.Location = new Point(0, 0);
            newImageEvent = new ManualResetEvent(false);
            showImageEvent = new ManualResetEvent(true);
            //pictureBox1.MouseWheel += new MouseEventHandler(pictureBox1_MouseWheel);
            this.MouseWheel += new MouseEventHandler(pictureBox1_MouseWheel);
        }
        private void InitializeOutputWindows()
        {
            outputWindow = new OutputWindow();
            this.splitContainer1.Panel2.Controls.Add(outputWindow);
            outputWindow.Dock = DockStyle.Fill;
        }
       
       
        #region System Framework Members
        VideoControlForm vedioControlForm = null;
        private System.Drawing.Font drawFont = null;
        #endregion
        #region Common Members
        bool captureConsistentModeFlag = true;
        CameraSource.Camera videoSource = null;
        string targetFolder = "";
        double hotRectWidthToHeightRatio = 1.0;
        double scaleRatio = 1.05;
        int minRectSize = 32;
        int autoIndexCounter = 0;
        bool IsCaptureFlag = false;
        bool exitThreadFlag = false;
        bool mousePressed = false;
        bool lockHotRect = false;
        bool hotRectSelected = false;
        Bitmap backupImage = null;
        Rectangle hotRect = new Rectangle(0, 0, 40, 50);
        Rectangle senseRect = new Rectangle(28, 28, 4, 4);
        bool showHotRectFlag = false;
        Rectangle negativeSampleROI = new Rectangle(0,0,0,0);
        int negativeSampleAutoNameMainCounter = 0;
        int negativeSampleAutoNameSubCounter = 0;

        DateTime oldTime;//用来计算时间间隔的，测试帧率
        DateTime newTime;
        Bitmap shareBitmap = null;
        ManualResetEvent newImageEvent = null;
        ManualResetEvent showImageEvent = null;
        AutoResetEvent singleThreadExitedEvent = new AutoResetEvent(false);
        object shareImageObject = new object();//用来协调不同任务的同步对象，可能会在后期丢弃不用
        //以下两种颜色用来帮助区分按钮状态
        Color stateColor = Color.Red;
        Color controlColor = Color.Gray;
        #endregion
        public delegate void InvokeDelegate();
        public delegate void InvokeMsgDelegate(String msg);
        public delegate void InvokeObjectDelegate(object obj);
       
        #region Multi-Mode Memenber
       
        //AutoResetEvent[] autoEvent = null;//用来确定所有线程都完成后，可以用WaitAll来退出程序
        public delegate void UpdateImageInvokerDelegate(Bitmap image);
        ManualResetEvent detectManualEvent = new ManualResetEvent(false);
        public delegate void ProcessNewImage();//声明一个代表类型
        public ProcessNewImage ProcessceNewImageMothed = null;//用一个代表来表示需要调用的处理新图片的方法，同样为了灵活
        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        #endregion
        #region Multi-Mode Functions
       //------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------
        //---------------------------以下代码匀为了在多核心CPU的系统上提高效率的代码----------------
        //---------------------------为了简洁，这代码均放在同一块区域中以方便阅读-------------------
        //---------------------------代码开始编写时间：2010年1月28日，黄纯得编写--------------------
        //------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------
       
     
       

        private void ExitSingleThread()
        {
            if (!singleThreadExitedEvent.WaitOne(5000))
                throw new Exception("Unable to track single-mode work thread.");
            singleThreadExitedEvent.Reset();
        }

       
    
     
        //当有新的图片从外设返回时，可调用这方法来处理，与UpdateResutl功能相同，但在不同模式，以后需要改进
        private void NewImageAvailabe()
        {
            bool flag = false;
            try
            {
                videoSource.Lock();
                if (videoSource.LastFrame == null)
                    return;
                Bitmap bmp = (Bitmap)videoSource.LastFrame.Clone();
                videoSource.Unlock();
                flag = true;
                //imageViewer.RenderImage = videoSource.LastFrame;
                //vedioViewer.Image = videoSource.LastFrame;
                // bmp.Dispose();
               
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
            }
            finally
            {
                if (!flag)
                    videoSource.Unlock();
            }
 
        }
     
      
    
       

      
        
  
    
       
       // private void 
        //------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------
        //---------------------------以下代码匀为了在多核心CPU的系统上提高效率的代码----------------
        //---------------------------为了简洁，这代码均放在同一块区域中以方便阅读-------------------
        //---------------------------代码开始编写时间：2010年1月28日，黄纯得编写--------------------
        //------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------
       #endregion
        private void StartCapture()
        {
            this.CloseCamera();
            if (!Monitor.TryEnter(shareImageObject))
                return;
            try
            {
                CameraSource.DeviceForm form = new CameraSource.DeviceForm();
                if (form.ShowDialog() == DialogResult.OK)
                {
                    //VideoSource.CaptureDevice localSource = new VideoSource.CaptureDevice();
                    //localSource.VideoSource = form.Device;
                    //videoSource = new CameraSource.Camera(localSource);
                    videoSource = form.Camera;
                    if (videoSource == null)
                        return;
                    
                    this.Cursor = Cursors.WaitCursor;
                    videoSource.NewFrame += new EventHandler(this.New_Frame);
                     videoSource.Start();
                   ThreadPool.QueueUserWorkItem(new WaitCallback(ProcessNewImageThread));
                    IsCaptureFlag = true;
                    this.Cursor = Cursors.Default;
                    oldTime = DateTime.Now;
                    newTime = DateTime.Now;
                    //StartMultiWorkThreadMode(0);
                    if (HasInterface(videoSource.VideoSource.GetType(), typeof(IFileSource)))
                    {
                        ShowVedioControlForm((IFileSource)videoSource.VideoSource);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("StartCapture " + ex.Message.ToString());
            }
            finally
            {
                Monitor.Exit(shareImageObject);
            }
           

        }
        private void UpdateImageInvoker(Bitmap image)
        {
            if (image == null)
                return;
            if (backupImage != null)
                backupImage.Dispose();
            backupImage = (Bitmap)image.Clone();
            UpdateView();
            
          
               
        }

        private int GenerateNegativeSample(int w, int h, String mainTitle)
        {
            if (backupImage == null)
                return 0;
            if (targetFolder == null)
                return 0;
            if (targetFolder.Length == 0)
                return 0;

           

            //if (negativeSampleCounter % 10 == 0)
            {
              
                int n = 0;
                int bw = backupImage.Width;
                int bh = backupImage.Height;
                Random ran = new Random();
                Bitmap image = new Bitmap(w,h);
                Graphics g = Graphics.FromImage(image);
                Rectangle rect = new Rectangle(0, 0,w, h);
                int x0 = 0;
                int x1 = backupImage.Width;
                int y0 = 0;
                int y1 = backupImage.Height;
                if (negativeSampleROI.Width != 0)
                {
                    x1 = negativeSampleROI.Right;
                    x0 = negativeSampleROI.Left;
                    y0 = negativeSampleROI.Top;
                    y1 = negativeSampleROI.Bottom;
                }
                try
                {
                    for (int i = x0; i < x1 - w && i < bw - w; i += (w / 4 + (int)(ran.NextDouble() * w)))
                    {
                        for (int j = y0; j < y1 - h && j < bh - h; j += (h / 4 + (int)(ran.NextDouble() * h)))
                        {
                            g.DrawImage(backupImage, rect, i, j, w, h, GraphicsUnit.Pixel);
                            image.Save(GetAutoNegName(mainTitle));
                            n++;
                        }
                    }
                }
                catch (Exception ex)
                {
                    AppendMsg(ex.Message.ToString());
                }
                g.Dispose();

                AppendMsg("成功生成" + n.ToString() + "张负样本...");
                return n;
            }
            
            //negativeSampleCounter++;
           

        }

     
        private bool HasInterface(Type type, Type type_2)
        {
            return true;
        }

        private void ShowVedioControlForm(IFileSource iFileSource)
        {
            if (vedioControlForm == null)
                vedioControlForm = new VideoControlForm();
            vedioControlForm.FileSource = iFileSource;
            vedioControlForm.Icon = this.Icon;
            //  vedioControlForm.Parent = this;
            vedioControlForm.Show();
        }
        /// <summary>
        /// 关闭视频流
        /// </summary>
        private void CloseCamera()
        {

            if (videoSource != null)
            {
                if (vedioControlForm != null)
                {
                    if (vedioControlForm.SuspendFlag)
                    {
                        vedioControlForm.SuspendFlag = false;
                    }
                    vedioControlForm.Close();
                    vedioControlForm.Dispose();
                    vedioControlForm = null;
                }
                videoSource.SignalToStop();
                videoSource.WaitForStop();
                videoSource = null;
                IsCaptureFlag = false;
                exitThreadFlag = true;
               
                frameRatioStatusLabel.Text = "Frame: 0";
              
                
            }
            
        }
    
      
        //新的图片来的时候。
        private void New_Frame(object sender, EventArgs e)
        {
            //CameraEventArgs ex = (CameraEventArgs)e;
            if (captureConsistentModeFlag)
                Monitor.Enter(shareImageObject);
            else
                if (!Monitor.TryEnter(shareImageObject))
                    return;
            try
            {
                videoSource.Lock();
                if (videoSource.LastFrame == null)
                //if(e.Bitmap == null)
                //    return;
                if (shareBitmap != null)
                {
                    shareBitmap.Dispose();
                    shareBitmap = null;
                }
                shareBitmap = (Bitmap)videoSource.LastFrame.Clone();
                //shareBitmap = (Bitmap)e.Bitmap.Clone();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
            }
            finally
            {
                videoSource.Unlock();
                Monitor.Exit(shareImageObject);
                newImageEvent.Set();//通知工作线程有新的图像到来。
                //UpdateFrameRatioDelege();

            }
        }
      
       
        //用来计算每秒新图片的数目，即帧率
        private void UpdateFrameRatioDelege()
        {
            newTime = DateTime.Now;
            TimeSpan t = newTime - oldTime;
            double frames = 1000.0 / ((double)(t.Milliseconds));
            String str = frames.ToString();
            if (str.Length > 5)
                str = str.Substring(0, 5);
            frameRatioStatusLabel.Text = "Frame:" + str;
            oldTime = newTime;
          
        }
     
     
     
      
        
        private void ProcessNewImageThread(object ob)
        {
            while (true)
            {
                
                if (exitThreadFlag)
                {
                    exitThreadFlag = false;
                    break; ;
                }
                if (!newImageEvent.WaitOne(500))//不建议死等待，以方便能及时退出线程
                    continue;

                if (shareBitmap == null)
                {
                    newImageEvent.Reset();
                    continue;
                }
                
                Monitor.Enter(shareImageObject);
                try
                {
                    Graphics g = Graphics.FromImage(shareBitmap);
                   
                     g.Dispose();
                       
                    {
                        pictureBox1.BeginInvoke(new UpdateImageInvokerDelegate(UpdateImageInvoker), shareBitmap);
                        //imageViewer.RenderImage = shareBitmap;
                     
                        
                    }

                }
                catch (Exception ex)
                {
                    ShowCrossThreadsMessage(ex.Message.ToString());
                }
                finally
                {
                   newImageEvent.Reset();

                   statusStrip.BeginInvoke(new InvokeDelegate(UpdateFrameRatioDelege));
                   Monitor.Exit(shareImageObject);
                }
            }
        
            singleThreadExitedEvent.Set();
        }

        private void ShowCrossThreadsMessage(string p)
        {
           // throw new NotImplementedException();
        }

   


        private void ExpressionDetector_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (IsCaptureFlag)
            {
                if (MessageBox.Show("Are you sure to exit?", "Warming", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    CloseCamera();
                    exitThreadFlag = true;
                    return;
                }
                else
                    e.Cancel = true;
            }
            
            
        }

      
        private void captureStripButton_Click(object sender, EventArgs e)
        {
            StartCapture();
        }
      
        //用来设定捕捉视频的模式，实时或连续不丢帧模式
        private void CaptureModeStripStatusLabel_Click(object sender, EventArgs e)
        {
            captureConsistentModeFlag = !captureConsistentModeFlag;
            if (captureConsistentModeFlag)
                CaptureModeStripStatusLabel.Text = "Capture Mode: Consistent";
            else
                CaptureModeStripStatusLabel.Text = "Capture Mode: Real-Time";
        }
      
         public void CreateParentPath(string path)
         {
             string p = Path.GetDirectoryName(path);
             if (!Directory.Exists(p))
             {
                 CreateParentPath(p);
             }
             else
                 Directory.CreateDirectory(path);
         }
        /// <summary>
       
         #region System Framework Methods
         
       
        
        
     
         //用来处理进程未被处理的异常，在Application中被触发
         public static void MainUITHreadExceptionHandler(object sender, ThreadExceptionEventArgs e)
         {
             MessageBox.Show(e.Exception.Message.ToString());
         }
         protected override bool ProcessCmdKey(ref System.Windows.Forms.Message msg, System.Windows.Forms.Keys keyData)
         {

             if ((keyData & Keys.Alt) == Keys.Alt)
             {
                 if (backupImage != null)
                 {
                     GenerateSampleImageList();
                 }
             }
             else if ((keyData & Keys.Control) == Keys.Control)
             {
                 GenerateNegativeSample();
             }
             else if ((keyData) == Keys.Left)
             {
                 if (vedioControlForm != null)
                 {
                     vedioControlForm.SlowDownPlayRatio();
                 }
             }
             else if ((keyData) == Keys.Right)
             {
                 if (vedioControlForm != null)
                 {
                     vedioControlForm.SpeedUpPlayRatio();
                 }
             }
             else if((keyData == Keys.Down))
             {
                 if (vedioControlForm != null)
                 {
                     vedioControlForm.ResetPlayRatio();
                 }
             }
             else if ((keyData & Keys.Shift) == Keys.Shift)
             {
                 GenerateNegativeSample();
             }
             else if (keyData == Keys.Home)
             {
                 InputForm frm = new InputForm();
                 frm.InputTitle = "Please enter a integer.";
                 frm.InputString = negativeSampleAutoNameMainCounter.ToString();
                 if (frm.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                 {
                     try
                     {
                         negativeSampleAutoNameMainCounter = int.Parse(frm.InputString);
                     }
                     catch (Exception ex)
                     {
                         MessageBox.Show(ex.Message.ToString());
                     }
                 }
             }
             return false;
         }

         private void GenerateNegativeSample()
         {
             if (backupImage == null)
             {
                 return;
             }
             int h = Math.Min(512, backupImage.Height);
             int w = Math.Min((int)((double)h * hotRectWidthToHeightRatio), backupImage.Width);
             if (negativeSampleROI.Width != 0 && negativeSampleROI.Height != 0)
             {
                 w = Math.Min(w, negativeSampleROI.Width);
                 h = Math.Min(h, negativeSampleROI.Height);
             }
             negativeSampleAutoNameMainCounter++;
             int scale = 0;

             int total = 0;
             for (; w > 32 && h > 32; )
             {
                 scale++;
                 total += GenerateNegativeSample(w, h,"Img_" + negativeSampleAutoNameMainCounter.ToString() + "_" +scale.ToString() + "_");
                

                 w = (int)((double)w / 1.05);
                 h = (int)((double)h / 1.05);
             }
             AppendMsg(total.ToString() + "samples have been extracted...");
         }

         private void GenerateSampleImageList()
         {
             if (!showHotRectFlag)
                 return;
             if (locationTextBox.Text == null || locationTextBox.Text.Length == 0)
             {
                 MessageBox.Show("Please select a folder to save the samples");
                 return;
             }
             
             try
             {
                 Bitmap image = new Bitmap(hotRect.Width, hotRect.Height);
                 Graphics g = Graphics.FromImage(image);
                 Rectangle rect = new Rectangle(0, 0, image.Width, image.Height);
                 g.DrawImage(backupImage,rect, hotRect.X, hotRect.Y, hotRect.Width, hotRect.Height, GraphicsUnit.Pixel);
                 image.Save(GetAutoName("Sample"));
            
                 AppendText("\r\n" + DateTime.Now.ToString() + "　saved ．．．");
                 autoIndexCounter++;
                 g.Dispose();
                 image.Dispose();
             }
             catch (Exception ex)
             {
                 MessageBox.Show(ex.Message.ToString());
             }
         }

         private void AppendMsg(string p)
         {
             AppendText("\r\n" + DateTime.Now.ToString() + ": " +  p);
         }

         private void AppendText(string p)
         {
             outputWindow.AppendMsg(p);
         }

         private bool IsConfinedInImage(int x, int y, int w, int h, Bitmap image)
         {
             if (x < 0 || y < 0)
                 return false;
             if (x + w >= image.Width || y + h >= image.Height)
                 return false;
             return true;
         }

         private Point RandomOffset(Size size, double ratio)
         {
             double off = ratio - 0.5;
             int dx = (int)((double)size.Width * off);
             int dy = (int)((double)size.Height * off);
             Random ran = new Random();
             double xR = (double)size.Width *(1.0 - ratio);
             double yR = (double)size.Height * (1.0 - ratio);
             int x = (int)(ran.NextDouble() * xR);
             //x = ran.NextDouble() > 0.5 ? x : -x;
             int y = (int)(ran.NextDouble() * yR);
             //y = ran.NextDouble() > 0.5 ? y : -y;
             return new Point(x + dx, y + dy);
         }

         private Point RandomOffset(Size size)
         {
             Random ran = new Random();
             double xR = (double)size.Width / 8;
             double yR = (double)size.Height / 8;
             int x =  (int)(ran.NextDouble() * xR);
             x = ran.NextDouble() > 0.5 ? x : -x;
             int y = (int)(ran.NextDouble() * yR);
             y = ran.NextDouble() > 0.5 ? y : -y;
             return new Point(x, y);


         }

         private string GetAutoName(string p)
         {
             String name = locationTextBox.Text + "\\" + p + "\\Image_" + autoIndexCounter.ToString();
             CreateParentPath(Path.GetDirectoryName(name));
             if (File.Exists(name + ".jpg"))
             {
                 int rename = 1;
                 String temp = name + "(" + rename.ToString() + ")";
                 while (File.Exists(temp + ".jpg"))
                 {
                     temp = name + "(" + rename++.ToString() + ")";
                 }
                 return temp + ".jpg";

             }
             return name + ".jpg";
         }
         private string GetAutoNegName(string p)
         {
             String name = locationTextBox.Text + "\\NegativeSample\\" + p + negativeSampleAutoNameSubCounter.ToString();
             negativeSampleAutoNameSubCounter++;
             CreateParentPath(Path.GetDirectoryName(name));
             if (File.Exists(name + ".jpg"))
             {
                 int rename = 1;
                 String temp = name + "(" + rename.ToString() + ")";
                 while (File.Exists(temp + ".jpg"))
                 {
                     temp = name + "(" + rename++.ToString() + ")";
                 }
                 return temp + ".jpg";

             }
             return name + ".jpg";
         }
        
  
         #endregion
         #region Video Show Model
        
        
       

         private void MarkToolStripStateColor(ToolStrip toolStrip, int index)
         {
             for(int i = 0; i < toolStrip.Items.Count;i ++)
             {
                 if (i == index)
                     toolStrip.Items[i].BackColor = stateColor;
                 else
                     toolStrip.Items[i].BackColor = controlColor;
                }
            
         }

         private void EnableToolStripItems(ToolStrip toolStrip, bool p)
         {
            
            for(int i = 0; i < toolStrip.Items.Count;i ++)
            {
                toolStrip.Items[i].Enabled = p;
            }
         }
         #endregion
     
         private void stopCaptureButton_Click(object sender, EventArgs e)
         {
             CloseCamera();
         }

        

         private void UpdateRatio()
         {
             try
             {
                 int w = int.Parse(ratioWidthTextBox.Text);
                 int h = int.Parse(ratioHeightTextBox.Text);
                 if (w <= 0 || h <= 0)
                 {
                     MessageBox.Show("Invalidate Input, Please try again!");
                     return;
                 }
                 hotRectWidthToHeightRatio = (double)w / (double)h;
                 double r = ((double)hotRect.Width / (double)hotRect.Height);
                 if (r < hotRectWidthToHeightRatio)
                 {
                     hotRect.Width = (int)((double)hotRect.Height * hotRectWidthToHeightRatio);
                 }
                 else
                 {
                     hotRect.Height = (int)((double)hotRect.Width / hotRectWidthToHeightRatio);
                 }
                 UpdateView();
                
                
             }
             catch (Exception ex)
             {
                 MessageBox.Show(ex.Message.ToString());
             }
         }

         private void ratioWidthTextBox_TextChanged(object sender, EventArgs e)
         {
             UpdateRatio();
         }

         private void ratioHeightTextBox_TextChanged(object sender, EventArgs e)
         {
             UpdateRatio();
         }

         private void minScaleTextBox_TextChanged(object sender, EventArgs e)
         {
             try
             {
                 int w = int.Parse(minScaleTextBox.Text);
               
                 if (w <= 0)
                 {
                     MessageBox.Show("Invalidate Input, Please try again!");
                     return;
                 }
                 minRectSize = w;
             }
             catch (Exception ex)
             {
                 MessageBox.Show(ex.Message.ToString());
             }
         }

         private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
         {
             //if(fastGenerateModelFlag)
             //{
             //    showHotRectFlag = true;
                 
             //    if (e.Button == System.Windows.Forms.MouseButtons.Left)
             //    {
             //        showHotRect(e.Location);
             //    }
             //    else if (e.Button == System.Windows.Forms.MouseButtons.Right)
             //    {
                     
             //    }

             //    return;
             //}
             Point point = e.Location;
             point.X = (int)((double)point.X / currentViewScale);
             point.Y = (int)((double)point.Y / currentViewScale);

             if (e.Button == System.Windows.Forms.MouseButtons.Left)
             {
                 mousePressed = true;
                 if (PointInRect(point, hotRect))
                 {
                     hotRectSelected = true;
                 }
             }
             else if (e.Button == System.Windows.Forms.MouseButtons.Right)
             {
                 showHotRect(e.Location);
                 hotRectSelected = false;
             }
             else
             {
                 mousePressed = false;
                 hotRectSelected = false;
             }
             
         }

         private void showHotRect(Point point)
         {
             showHotRectFlag = !showHotRectFlag;
             //if (showHotRectFlag)
             {
                 hotRect = new Rectangle(point.X - hotRect.Width / 2, point.Y - hotRect.Height / 2, hotRect.Width, hotRect.Height);
                 UpdateView();
             }
         }

         private void UpdateView()
         {
             
             try
             {
                 if (pictureBox1.Image != null)
                     pictureBox1.Image.Dispose();
                 if (backupImage == null)
                     return;
                 Bitmap image = (Bitmap)backupImage.Clone();
                 if (showHotRectFlag)
                 {
                     Graphics g = Graphics.FromImage(image);
                     g.DrawRectangle(Pens.Red, hotRect);
                     g.Dispose();
                 }
                 if (negativeSampleROI.Width != 0 && negativeSampleROI.Height != 0)
                 {
                     Graphics g = Graphics.FromImage(image);
                     g.DrawRectangle(Pens.Yellow, negativeSampleROI);
                     g.Dispose();
                 }

                 if (viewScaleIndex == 0)
                     pictureBox1.Image = image;
                 else
                 {

                     Bitmap scaleImage = new Bitmap((int)((double)image.Width * currentViewScale), (int)((double)image.Height * currentViewScale));
                     Graphics g = Graphics.FromImage(scaleImage);
                     g.DrawImage(image, 0, 0, scaleImage.Width, scaleImage.Height);
                     g.Dispose();
                     pictureBox1.Image = scaleImage;
                     //g.Dispose();
                     image.Dispose();
                 }
             }
             catch(Exception e)
             {
                 AppendText(e.Message.ToString());
             }
         }

         private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
         {
             Point point = e.Location;
             point.X = (int)((double)point.X/ currentViewScale);
             point.Y = (int)((double)point.Y/ currentViewScale);
             if (mousePressed && showHotRectFlag)
             {
                 if(hotRectSelected)
                 {
                     
                     hotRect = new Rectangle(point.X - hotRect.Width / 2, point.Y - hotRect.Height / 2, hotRect.Width, hotRect.Height);
                     UpdateView();
                     this.Text = hotRect.ToString();
                 }
             }
         }
         private void pictureBox1_MouseWheel(object sender, MouseEventArgs e)
         {
             //this.Text = counter++.ToString();
             if (!showHotRectFlag)
                 return;
             if (lockHotRect)
                 return;
             int x = pictureBox1.Left;
             int y = pictureBox1.Top;
             int w = 1;
             int h = 1;
             Point point = e.Location;
             point.X -= 6;
             point.Y -= (mainToolStrip.Height + 24);
             point.X = (int)((double)point.X / currentViewScale);
             point.Y = (int)((double)point.Y / currentViewScale);
             Point pp = new Point(point.X, point.Y );
             if (e.Delta > 0)
             {
             
                  w =(int) ((double)hotRect.Width * scaleRatio);
                 h = (int)((double)hotRect.Height * scaleRatio);
               
                 
             }
             else
             {
                  w = (int)((double)hotRect.Width / scaleRatio);
                  h = (int)((double)hotRect.Height / scaleRatio);
                
             }
             if (w < minRectSize || h < minRectSize)
             {
                 w = Math.Max(minRectSize, w);
                 h = Math.Max(minRectSize, h);

             }
             double r = (double)w / (double)h;
             if (r > hotRectWidthToHeightRatio)
                 w = (int)((double)h * hotRectWidthToHeightRatio);
             else
                 h = (int)((double)w / hotRectWidthToHeightRatio);
            
             hotRect = new Rectangle(pp.X - w / 2, pp.Y - h / 2, w, h);
             this.Text = hotRect.ToString();
                 UpdateView();


         }
         private bool PointInRect(Point point, Rectangle hotRect)
         {
             if (point.X < hotRect.Left || point.X > hotRect.Right)
                 return false;
             if (point.Y < hotRect.Top || point.Y > hotRect.Bottom)
                 return false;
             return true;
         }

         private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
         {
             mousePressed = false;
             hotRectSelected = false;
             locationTextBox.Focus();
         }

         private void ratioWidthTextBox_Click(object sender, EventArgs e)
         {
             ratioWidthTextBox.SelectAll();
         }

         private void ratioHeightTextBox_Click(object sender, EventArgs e)
         {
             ratioHeightTextBox.SelectAll();
         }

         private void minScaleTextBox_Click(object sender, EventArgs e)
         {
             minScaleTextBox.SelectAll();
         }

       

         private void openButton_Click(object sender, EventArgs e)
         {
             SelectLocation();
             autoIndexCounter = 0;
             negativeSampleAutoNameSubCounter = 0;
             negativeSampleAutoNameMainCounter = 0;
         }

         private void SelectLocation()
         {
             FolderBrowserDialog dlg = new FolderBrowserDialog();
             if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
             {

                 locationTextBox.Text = dlg.SelectedPath;
                 targetFolder = dlg.SelectedPath;
                 if (( Directory.GetFiles(dlg.SelectedPath).Length != 0 || Directory.GetDirectories(dlg.SelectedPath).Length != 0))
                 {
                     if(MessageBox.Show("The selected folder is non-empty, a new folder is better for sample group.\n Would you wanna re-select a new target location?","Select new location",MessageBoxButtons.YesNo) == System.Windows.Forms.DialogResult.Yes)
                     {
                         SelectLocation();
                     }
                 }
             }
         }

      
      

       

         private void viewScaleDropDownButton_DropDownItemClicked(object sender, ToolStripItemClickedEventArgs e)
         {
             for (int i = 0; i < viewScaleDropDownButton.DropDownItems.Count; i++)
             {
                 if (viewScaleDropDownButton.DropDownItems[i] == e.ClickedItem)
                 {
                     changeViewScale(viewScaleDropDownButton.DropDownItems.Count - 1 - i);
                     //viewScaleDropDownButton.Text = e.ClickedItem.Text;
                     break;
                 }
             }

         }

         private void changeViewScale(int p)
         {
             currentViewScale = viewScale[p];
             viewScaleIndex = p;
             viewScaleDropDownButton.Text = viewScaleDropDownButton.DropDownItems[viewScaleDropDownButton.DropDownItems.Count - 1-p].Text;
             UpdateView();
         }

         double[] viewScale = { 1.0, 1.5, 2.0};
         double currentViewScale = 1.0;
         int viewScaleIndex = 0;

         private void viewScaleDropDownButton_Click(object sender, EventArgs e)
         {
             int p = viewScaleIndex;
             p++;
             p %= viewScaleDropDownButton.DropDownItems.Count;

             changeViewScale(p);

         }

         private void negativeSampleButton_ButtonClick(object sender, EventArgs e)
         {
             if (targetFolder == null || targetFolder.Length == 0)
                 return;
             GenerateNegativeSample();
             //autoGenerateNegativeSampleFlag = !autoGenerateNegativeSampleFlag;
             //if (autoGenerateNegativeSampleFlag)
             //{
             //    negativeSampleButton.ForeColor = Color.Red;
             //}
             //else
             //{
             //    negativeSampleButton.ForeColor = Color.Black;
             //}
         }

         private void negativeSampleButton_DropDownOpening(object sender, EventArgs e)
         {
             rOIToolStripMenuItem.Enabled = showHotRectFlag;
             clearRoiToolStripMenuItem.Enabled = (negativeSampleROI.Width != 0 && negativeSampleROI.Height != 0);
         }

         private void rOIToolStripMenuItem_Click(object sender, EventArgs e)
         {
             negativeSampleROI = hotRect;
         }

         private void SampleCropor_DragEnter(object sender, DragEventArgs e)
         {
             if (e.Data.GetDataPresent(DataFormats.Bitmap) ||
                e.Data.GetDataPresent(DataFormats.FileDrop) )
                        {
                            string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
                            String ext = Path.GetExtension(files[0]);
                            ext = ext.ToLower();
                            if (ext == ".jpg" || ext == ".bmp" || ext == ".png")
                            {

                                e.Effect = DragDropEffects.Copy;
                                return;
                            }
                
                
             }
            
             {
                 e.Effect = DragDropEffects.None;
                
             }
         }

         private void SampleCropor_DragDrop(object sender, DragEventArgs e)
         {
             if (e.Data.GetDataPresent(DataFormats.FileDrop))
             {
                 // Assign the file names to a string array, in 
                 // case the user has selected multiple files.
                 string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
                 try
                 {
                     if (files.Length > 0)
                     {
                         String ext = Path.GetExtension(files[0]);
                         ext = ext.ToLower();
                         if (ext == ".jpg" || ext == ".bmp" || ext == ".png")
                         {
                             
                             Bitmap input = (Bitmap)Bitmap.FromFile(files[0]);
                             UpdateImageInvoker(input);
                             input.Dispose();
                         }
                     }

                 }
                 catch (Exception ex)
                 {
                     MessageBox.Show(ex.Message);
                     return;
                 }
             }
         }

         private void clearRoiToolStripMenuItem_Click(object sender, EventArgs e)
         {
             negativeSampleROI = new Rectangle(0, 0, 0, 0);
         }

         private void helpToolStripButton_Click(object sender, EventArgs e)
         {
             MessageBox.Show("'Alt'--->Generate Sample\r'Ctrl'--->Generate Negative Samples");
         }

        
        
    }
}
