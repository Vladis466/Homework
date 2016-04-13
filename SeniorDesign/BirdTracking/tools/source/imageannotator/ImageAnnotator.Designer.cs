namespace SampleCropor
{
    partial class ImageAnnotator
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ImageAnnotator));
            this.toolStripContainer = new System.Windows.Forms.ToolStripContainer();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.readyStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.frameRatioStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.threadModelStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.CaptureModeStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.viewScaleDropDownButton = new System.Windows.Forms.ToolStripDropDownButton();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.mainToolStrip = new System.Windows.Forms.ToolStrip();
            this.captureStripButton = new System.Windows.Forms.ToolStripButton();
            this.stopCaptureButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.locationTextBox = new System.Windows.Forms.ToolStripTextBox();
            this.openButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel2 = new System.Windows.Forms.ToolStripLabel();
            this.ratioWidthTextBox = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripLabel3 = new System.Windows.Forms.ToolStripLabel();
            this.ratioHeightTextBox = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripLabel4 = new System.Windows.Forms.ToolStripLabel();
            this.minScaleTextBox = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.negativeSampleButton = new System.Windows.Forms.ToolStripSplitButton();
            this.rOIToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.clearRoiToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.清除内容ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripContainer.BottomToolStripPanel.SuspendLayout();
            this.toolStripContainer.ContentPanel.SuspendLayout();
            this.toolStripContainer.TopToolStripPanel.SuspendLayout();
            this.toolStripContainer.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.mainToolStrip.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStripContainer
            // 
            // 
            // toolStripContainer.BottomToolStripPanel
            // 
            this.toolStripContainer.BottomToolStripPanel.Controls.Add(this.statusStrip);
            // 
            // toolStripContainer.ContentPanel
            // 
            resources.ApplyResources(this.toolStripContainer.ContentPanel, "toolStripContainer.ContentPanel");
            this.toolStripContainer.ContentPanel.Controls.Add(this.tabControl1);
            resources.ApplyResources(this.toolStripContainer, "toolStripContainer");
            this.toolStripContainer.Name = "toolStripContainer";
            // 
            // toolStripContainer.TopToolStripPanel
            // 
            this.toolStripContainer.TopToolStripPanel.Controls.Add(this.mainToolStrip);
            // 
            // statusStrip
            // 
            resources.ApplyResources(this.statusStrip, "statusStrip");
            this.statusStrip.GripMargin = new System.Windows.Forms.Padding(0);
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.readyStatusLabel,
            this.frameRatioStatusLabel,
            this.threadModelStatusLabel,
            this.CaptureModeStripStatusLabel,
            this.viewScaleDropDownButton});
            this.statusStrip.Name = "statusStrip";
            // 
            // readyStatusLabel
            // 
            resources.ApplyResources(this.readyStatusLabel, "readyStatusLabel");
            this.readyStatusLabel.Name = "readyStatusLabel";
            // 
            // frameRatioStatusLabel
            // 
            resources.ApplyResources(this.frameRatioStatusLabel, "frameRatioStatusLabel");
            this.frameRatioStatusLabel.Name = "frameRatioStatusLabel";
            // 
            // threadModelStatusLabel
            // 
            resources.ApplyResources(this.threadModelStatusLabel, "threadModelStatusLabel");
            this.threadModelStatusLabel.ForeColor = System.Drawing.Color.Black;
            this.threadModelStatusLabel.Name = "threadModelStatusLabel";
            // 
            // CaptureModeStripStatusLabel
            // 
            resources.ApplyResources(this.CaptureModeStripStatusLabel, "CaptureModeStripStatusLabel");
            this.CaptureModeStripStatusLabel.Image = global::SampleCropor.Properties.Resources.Capture;
            this.CaptureModeStripStatusLabel.IsLink = true;
            this.CaptureModeStripStatusLabel.Name = "CaptureModeStripStatusLabel";
            this.CaptureModeStripStatusLabel.Click += new System.EventHandler(this.CaptureModeStripStatusLabel_Click);
            // 
            // viewScaleDropDownButton
            // 
            this.viewScaleDropDownButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.viewScaleDropDownButton.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem4,
            this.toolStripMenuItem3,
            this.toolStripMenuItem2});
            resources.ApplyResources(this.viewScaleDropDownButton, "viewScaleDropDownButton");
            this.viewScaleDropDownButton.Name = "viewScaleDropDownButton";
            this.viewScaleDropDownButton.DropDownItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.viewScaleDropDownButton_DropDownItemClicked);
            this.viewScaleDropDownButton.Click += new System.EventHandler(this.viewScaleDropDownButton_Click);
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            resources.ApplyResources(this.toolStripMenuItem4, "toolStripMenuItem4");
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            resources.ApplyResources(this.toolStripMenuItem3, "toolStripMenuItem3");
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            resources.ApplyResources(this.toolStripMenuItem2, "toolStripMenuItem2");
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            resources.ApplyResources(this.tabControl1, "tabControl1");
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.splitContainer1);
            resources.ApplyResources(this.tabPage1, "tabPage1");
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // splitContainer1
            // 
            resources.ApplyResources(this.splitContainer1, "splitContainer1");
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.splitContainer1.Panel1.Controls.Add(this.pictureBox1);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.pictureBox1.Cursor = System.Windows.Forms.Cursors.SizeAll;
            resources.ApplyResources(this.pictureBox1, "pictureBox1");
            this.pictureBox1.ErrorImage = global::SampleCropor.Properties.Resources.stop;
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseDown);
            this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseMove);
            this.pictureBox1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseUp);
            // 
            // mainToolStrip
            // 
            resources.ApplyResources(this.mainToolStrip, "mainToolStrip");
            this.mainToolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.captureStripButton,
            this.stopCaptureButton,
            this.toolStripSeparator2,
            this.toolStripLabel1,
            this.locationTextBox,
            this.openButton,
            this.toolStripSeparator1,
            this.toolStripLabel2,
            this.ratioWidthTextBox,
            this.toolStripLabel3,
            this.ratioHeightTextBox,
            this.toolStripLabel4,
            this.minScaleTextBox,
            this.toolStripSeparator4,
            this.negativeSampleButton,
            this.helpToolStripButton});
            this.mainToolStrip.Name = "mainToolStrip";
            // 
            // captureStripButton
            // 
            this.captureStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.captureStripButton.Image = global::SampleCropor.Properties.Resources.Capture;
            resources.ApplyResources(this.captureStripButton, "captureStripButton");
            this.captureStripButton.Name = "captureStripButton";
            this.captureStripButton.Click += new System.EventHandler(this.captureStripButton_Click);
            // 
            // stopCaptureButton
            // 
            this.stopCaptureButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.stopCaptureButton.Image = global::SampleCropor.Properties.Resources.stop;
            resources.ApplyResources(this.stopCaptureButton, "stopCaptureButton");
            this.stopCaptureButton.Name = "stopCaptureButton";
            this.stopCaptureButton.Click += new System.EventHandler(this.stopCaptureButton_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            resources.ApplyResources(this.toolStripSeparator2, "toolStripSeparator2");
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            resources.ApplyResources(this.toolStripLabel1, "toolStripLabel1");
            // 
            // locationTextBox
            // 
            this.locationTextBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.locationTextBox.Name = "locationTextBox";
            this.locationTextBox.ReadOnly = true;
            resources.ApplyResources(this.locationTextBox, "locationTextBox");
            // 
            // openButton
            // 
            this.openButton.Image = global::SampleCropor.Properties.Resources.Update;
            resources.ApplyResources(this.openButton, "openButton");
            this.openButton.Name = "openButton";
            this.openButton.Click += new System.EventHandler(this.openButton_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            resources.ApplyResources(this.toolStripSeparator1, "toolStripSeparator1");
            // 
            // toolStripLabel2
            // 
            this.toolStripLabel2.Name = "toolStripLabel2";
            resources.ApplyResources(this.toolStripLabel2, "toolStripLabel2");
            // 
            // ratioWidthTextBox
            // 
            this.ratioWidthTextBox.Name = "ratioWidthTextBox";
            resources.ApplyResources(this.ratioWidthTextBox, "ratioWidthTextBox");
            this.ratioWidthTextBox.Click += new System.EventHandler(this.ratioWidthTextBox_Click);
            this.ratioWidthTextBox.TextChanged += new System.EventHandler(this.ratioWidthTextBox_TextChanged);
            // 
            // toolStripLabel3
            // 
            this.toolStripLabel3.Name = "toolStripLabel3";
            resources.ApplyResources(this.toolStripLabel3, "toolStripLabel3");
            // 
            // ratioHeightTextBox
            // 
            this.ratioHeightTextBox.Name = "ratioHeightTextBox";
            resources.ApplyResources(this.ratioHeightTextBox, "ratioHeightTextBox");
            this.ratioHeightTextBox.Click += new System.EventHandler(this.ratioHeightTextBox_Click);
            this.ratioHeightTextBox.TextChanged += new System.EventHandler(this.ratioHeightTextBox_TextChanged);
            // 
            // toolStripLabel4
            // 
            this.toolStripLabel4.Name = "toolStripLabel4";
            resources.ApplyResources(this.toolStripLabel4, "toolStripLabel4");
            // 
            // minScaleTextBox
            // 
            this.minScaleTextBox.Name = "minScaleTextBox";
            resources.ApplyResources(this.minScaleTextBox, "minScaleTextBox");
            this.minScaleTextBox.Click += new System.EventHandler(this.minScaleTextBox_Click);
            this.minScaleTextBox.TextChanged += new System.EventHandler(this.minScaleTextBox_TextChanged);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            resources.ApplyResources(this.toolStripSeparator4, "toolStripSeparator4");
            // 
            // negativeSampleButton
            // 
            this.negativeSampleButton.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.rOIToolStripMenuItem,
            this.clearRoiToolStripMenuItem});
            this.negativeSampleButton.Image = global::SampleCropor.Properties.Resources.ark2;
            resources.ApplyResources(this.negativeSampleButton, "negativeSampleButton");
            this.negativeSampleButton.Name = "negativeSampleButton";
            this.negativeSampleButton.ButtonClick += new System.EventHandler(this.negativeSampleButton_ButtonClick);
            this.negativeSampleButton.DropDownOpening += new System.EventHandler(this.negativeSampleButton_DropDownOpening);
            // 
            // rOIToolStripMenuItem
            // 
            this.rOIToolStripMenuItem.Name = "rOIToolStripMenuItem";
            resources.ApplyResources(this.rOIToolStripMenuItem, "rOIToolStripMenuItem");
            this.rOIToolStripMenuItem.Click += new System.EventHandler(this.rOIToolStripMenuItem_Click);
            // 
            // clearRoiToolStripMenuItem
            // 
            this.clearRoiToolStripMenuItem.Name = "clearRoiToolStripMenuItem";
            resources.ApplyResources(this.clearRoiToolStripMenuItem, "clearRoiToolStripMenuItem");
            this.clearRoiToolStripMenuItem.Click += new System.EventHandler(this.clearRoiToolStripMenuItem_Click);
            // 
            // helpToolStripButton
            // 
            this.helpToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.helpToolStripButton.Image = global::SampleCropor.Properties.Resources.Alienware;
            resources.ApplyResources(this.helpToolStripButton, "helpToolStripButton");
            this.helpToolStripButton.Name = "helpToolStripButton";
            this.helpToolStripButton.Click += new System.EventHandler(this.helpToolStripButton_Click);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.清除内容ToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            resources.ApplyResources(this.contextMenuStrip1, "contextMenuStrip1");
            // 
            // 清除内容ToolStripMenuItem
            // 
            this.清除内容ToolStripMenuItem.Name = "清除内容ToolStripMenuItem";
            resources.ApplyResources(this.清除内容ToolStripMenuItem, "清除内容ToolStripMenuItem");
            // 
            // ImageAnnotator
            // 
            this.AllowDrop = true;
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.toolStripContainer);
            this.Name = "ImageAnnotator";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ExpressionDetector_FormClosing);
            this.DragDrop += new System.Windows.Forms.DragEventHandler(this.SampleCropor_DragDrop);
            this.DragEnter += new System.Windows.Forms.DragEventHandler(this.SampleCropor_DragEnter);
            this.toolStripContainer.BottomToolStripPanel.ResumeLayout(false);
            this.toolStripContainer.BottomToolStripPanel.PerformLayout();
            this.toolStripContainer.ContentPanel.ResumeLayout(false);
            this.toolStripContainer.TopToolStripPanel.ResumeLayout(false);
            this.toolStripContainer.TopToolStripPanel.PerformLayout();
            this.toolStripContainer.ResumeLayout(false);
            this.toolStripContainer.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.mainToolStrip.ResumeLayout(false);
            this.mainToolStrip.PerformLayout();
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ToolStripContainer toolStripContainer;
        private System.Windows.Forms.ToolStrip mainToolStrip;
        private System.Windows.Forms.ToolStripButton captureStripButton;
        private System.Windows.Forms.ToolStripButton stopCaptureButton;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel readyStatusLabel;
        private System.Windows.Forms.ToolStripStatusLabel frameRatioStatusLabel;
        private System.Windows.Forms.ToolStripStatusLabel threadModelStatusLabel;
        private System.Windows.Forms.ToolStripStatusLabel CaptureModeStripStatusLabel;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripTextBox locationTextBox;
        private System.Windows.Forms.ToolStripButton openButton;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripLabel toolStripLabel2;
        private System.Windows.Forms.ToolStripTextBox ratioWidthTextBox;
        private System.Windows.Forms.ToolStripLabel toolStripLabel3;
        private System.Windows.Forms.ToolStripTextBox ratioHeightTextBox;
        private System.Windows.Forms.ToolStripLabel toolStripLabel4;
        private System.Windows.Forms.ToolStripTextBox minScaleTextBox;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 清除内容ToolStripMenuItem;
        private System.Windows.Forms.ToolStripDropDownButton viewScaleDropDownButton;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem4;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripSplitButton negativeSampleButton;
        private System.Windows.Forms.ToolStripMenuItem rOIToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem clearRoiToolStripMenuItem;
        private System.Windows.Forms.ToolStripButton helpToolStripButton;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;

    }
}

