#pragma once
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include "cvaux.h"
#include <cstdio>
#include <math.h>




namespace mmgg {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql;
	using namespace MySql::Data::MySqlClient;
	//using namespace MySql::Data::Common;	
	//using namespace MySql::Data::Types;
	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	CvHaarClassifierCascade *cascade,*cascade_e,*cascade_nose,*cascade_mouth;
CvMemStorage *storage;
char *face_cascade="C:\\OpenCV-2.1.0\\data\\haarcascades\\haarcascade_frontalface_default.xml";
char *eye_cascade="C:\\OpenCV-2.1.0\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";
char *nose_cascade="C:\\OpenCV-2.1.0\\data\\haarcascades\\haarcascade_mcs_nose.xml";
char *mouth_cascade="C:\\OpenCV-2.1.0\\data\\haarcascades\\haarcascade_mcs_mouth.xml";
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel2;
	protected: 
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::Panel^  panel1;



	private: System::Windows::Forms::Button^  button3;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		int i,blink_count,yawn_count,last,now;
		CvCapture * capture; 
		IplImage * srcImage; 
		Graphics ^ g;
		Bitmap ^ bmp ;
		int stop;
		bool takeimg,displaymsg;
		MySqlConnection^ con;


	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Timer^  timer2;

			 Bitmap ^ bmpPicBox ;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Button^  btn_start;
	private: System::Windows::Forms::Label^  label9;

	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TextBox^  eyecount;




			 
    int       key;
	
    ;
	
   

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->btn_start = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->eyecount = (gcnew System::Windows::Forms::TextBox());
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
			this->panel1->SuspendLayout();
			this->panel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel2
			// 
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->button4);
			this->panel2->Controls->Add(this->button2);
			this->panel2->Controls->Add(this->textBox3);
			this->panel2->Controls->Add(this->textBox2);
			this->panel2->Controls->Add(this->textBox1);
			this->panel2->Controls->Add(this->label5);
			this->panel2->Controls->Add(this->label4);
			this->panel2->Controls->Add(this->label3);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Location = System::Drawing::Point(12, 183);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(350, 177);
			this->panel2->TabIndex = 15;
			this->panel2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel2_Paint);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(73, 138);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(98, 25);
			this->button4->TabIndex = 9;
			this->button4->Text = L"Submit";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(177, 138);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(98, 25);
			this->button2->TabIndex = 8;
			this->button2->Text = L"Reject";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(177, 101);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 7;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Form1::textBox3_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(177, 72);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 6;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(177, 43);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 5;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(32, 114);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(0, 13);
			this->label5->TabIndex = 4;
			this->label5->Click += gcnew System::EventHandler(this, &Form1::label5_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(59, 101);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(112, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Mouth Yawning Count";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(57, 75);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(82, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Eye Blink Count";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(59, 50);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(16, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Id";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(141, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(77, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Data Collected";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pictureBox2->Location = System::Drawing::Point(0, 0);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(111, 70);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &Form1::pictureBox2_Click);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pictureBox3->Location = System::Drawing::Point(128, 0);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(110, 70);
			this->pictureBox3->TabIndex = 5;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &Form1::pictureBox3_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pictureBox1->Location = System::Drawing::Point(376, 83);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(416, 277);
			this->pictureBox1->TabIndex = 10;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pictureBox4->Location = System::Drawing::Point(255, 0);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(161, 70);
			this->pictureBox4->TabIndex = 6;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &Form1::pictureBox4_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->pictureBox4);
			this->panel1->Controls->Add(this->pictureBox3);
			this->panel1->Controls->Add(this->pictureBox2);
			this->panel1->Location = System::Drawing::Point(376, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(416, 73);
			this->panel1->TabIndex = 14;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel1_Paint);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(178, 126);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(82, 29);
			this->button3->TabIndex = 16;
			this->button3->Text = L"Stop";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Interval = 30;
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel3->Controls->Add(this->label9);
			this->panel3->Controls->Add(this->btn_start);
			this->panel3->Controls->Add(this->label8);
			this->panel3->Controls->Add(this->comboBox1);
			this->panel3->Controls->Add(this->textBox4);
			this->panel3->Controls->Add(this->textBox5);
			this->panel3->Controls->Add(this->label6);
			this->panel3->Controls->Add(this->button3);
			this->panel3->Controls->Add(this->label7);
			this->panel3->Location = System::Drawing::Point(15, 12);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(347, 165);
			this->panel3->TabIndex = 18;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(138, 9);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(58, 13);
			this->label9->TabIndex = 10;
			this->label9->Text = L"Enter Data";
			// 
			// btn_start
			// 
			this->btn_start->AccessibleName = L"btn_start";
			this->btn_start->Location = System::Drawing::Point(82, 126);
			this->btn_start->Name = L"btn_start";
			this->btn_start->Size = System::Drawing::Size(90, 29);
			this->btn_start->TabIndex = 14;
			this->btn_start->Text = L"Start";
			this->btn_start->UseVisualStyleBackColor = true;
			this->btn_start->Click += gcnew System::EventHandler(this, &Form1::button1_Click_1);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(56, 96);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(90, 13);
			this->label8->TabIndex = 13;
			this->label8->Text = L"Observation Time";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {L"5", L"10", L"15", L"20", L"25", L"30"});
			this->comboBox1->Location = System::Drawing::Point(174, 93);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(58, 21);
			this->comboBox1->TabIndex = 12;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(174, 67);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 10;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(174, 38);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 20);
			this->textBox5->TabIndex = 9;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(54, 70);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(26, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"Age";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(56, 45);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(35, 13);
			this->label7->TabIndex = 7;
			this->label7->Text = L"Name";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(380, 375);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(106, 36);
			this->button5->TabIndex = 20;
			this->button5->Text = L"Take Image";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// eyecount
			// 
			this->eyecount->Location = System::Drawing::Point(15, 375);
			this->eyecount->Name = L"eyecount";
			this->eyecount->Size = System::Drawing::Size(100, 20);
			this->eyecount->TabIndex = 21;
			this->eyecount->Text = L"xyz";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(811, 526);
			this->Controls->Add(this->eyecount);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->panel1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void dataGridView1_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 }
private: System::Void panel2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {

			
			 String^ sql=String::Format("Insert into data"+
				 "(id,name,blink,yawn) Values"+
				 "('{0}','{1}','{2}','{3}')",textBox1->Text,textBox5->Text,textBox2->Text,textBox3->Text);
			 MySqlCommand^ cmd=gcnew MySqlCommand(sql,con);
			 cmd->ExecuteNonQuery();
			 

		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void pictureBox2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void pictureBox3_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void pictureBox4_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 }
/*private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 //srcImage = cvQueryFrame( capture );
			//captureImage(srcImage,pictureBox1);
		timer2->Enabled=true;
		timer2->Interval=30;
		timer1->Enabled=true;
		timer1->Interval=60000*int::Parse(comboBox1->Text);
		blink_count=0;
    storage = cvCreateMemStorage( 0 );
    cascade = ( CvHaarClassifierCascade* )cvLoad( face_cascade, 0, 0, 0 );
    cascade_e = ( CvHaarClassifierCascade* )cvLoad( eye_cascade, 0, 0, 0 );
    cascade_nose = ( CvHaarClassifierCascade* )cvLoad( nose_cascade, 0, 0, 0 );
    cascade_mouth = ( CvHaarClassifierCascade* )cvLoad( mouth_cascade, 0, 0, 0 );
  
	capture = cvCreateCameraCapture(0);
	takeimg=false;
			 
			 
			 }*/
		 
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

			 timer2->Enabled=false;
			timer1->Enabled=false;
			cvReleaseHaarClassifierCascade( &cascade );
    cvReleaseHaarClassifierCascade( &cascade_e );
   
    cvReleaseHaarClassifierCascade( &cascade_nose );
    cvReleaseHaarClassifierCascade( &cascade_mouth );
    cvReleaseMemStorage( &storage );
	blink_count/=2;
	textBox2->Text= Convert::ToString(blink_count);
	//this->Close();
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 
			
			 con = gcnew MySqlConnection("Data Source=localhost; Database=project; User Id=root;Password=""");
			 con->Open();
			 
			 capture = cvCreateCameraCapture(0);
			 
			 
			  }
private: System:: Void captureImage (IplImage * srcImage,PictureBox^ pictureBox1){

		 
            
			if ((pictureBox1->Image == nullptr)||(pictureBox1->Width!=srcImage->width)||(pictureBox1->Height!=srcImage->height))
			 {

			bmpPicBox = gcnew Bitmap (pictureBox1-> Width, pictureBox1-> Height);

			pictureBox1-> Image = bmpPicBox;
											}
			g = Graphics:: FromImage (pictureBox1-> Image);
			bmp = gcnew Bitmap (srcImage-> width, srcImage-> height, srcImage->widthStep,
			System:: Drawing:: Imaging:: PixelFormat:: Format24bppRgb, IntPtr (srcImage->imageData));

			g-> DrawImage (bmp, 0, 0, pictureBox1-> Width, pictureBox1-> Height);

            pictureBox1-> Refresh ();

			delete g;

		
		 }





/*Mouth detect ion*/
private: System::Void detectMouth( IplImage *img,CvRect *r)
{  static int img_no=0;
	char image[20]; 
   CvSeq *mouth;
   //mouth detecetion - set ROI
   cvSetImageROI(img,/* the source image */
                 cvRect(r->x,            /* x = start from leftmost */
                        r->y+(r->height *2/3), /* y = a few pixels from the top */
                        r->width,        /* width = same width with the face */
                        r->height/3    /* height = 1/3 of face height */
                       )
                );
   IplImage *img3 = cvCreateImage(cvGetSize(img),
                               img->depth,
                               img->nChannels);
 
/* copy subimage */
cvCopy(img, img3, NULL);
    mouth = cvHaarDetectObjects(img,/* the source image, with the estimated location defined */
                                cascade_mouth,      /* the eye classifier */
                                storage,        /* memory buffer */
                                1.15, 4, 0,     /* tune for your app */
                                cvSize(25, 15)  /* minimum detection scale */
                               );
	//cvNamedWindow( "Mouth", 1 );

        for( int i = 0; i < (mouth ? mouth->total : 0); i++ )
        {
     
          CvRect *mouth_cord = (CvRect*)cvGetSeqElem(mouth, i);

		  //if(((mouth_cord->x+mouth_cord->width/2) <= (r->x + r->width+mouth_cord->width/15))&&((mouth_cord->x+mouth_cord->width/2) <= (r->x + r->width-mouth_cord->width/10)))
		  {
		  /* draw a red rectangle */
          cvRectangle(img,
                      cvPoint(mouth_cord->x, mouth_cord->y),
                      cvPoint(mouth_cord->x + mouth_cord->width, mouth_cord->y + mouth_cord->height),
                      CV_RGB(255,255, 255),
                      1, 8, 0
                    );
		  }
		  cvSetImageROI(img3, cvRect(mouth_cord->x, mouth_cord->y, mouth_cord->width, mouth_cord->height));
		  IplImage *img2 = cvCreateImage(cvGetSize(img3),
                               img3->depth,
                               img3->nChannels);
 
/* copy subimage */
cvCopy(img3, img2, NULL);
//----------------------------

		IplImage* gray = cvCreateImage( cvGetSize(img2), IPL_DEPTH_8U, 1 );
        IplImage* canny=cvCreateImage(cvGetSize(img2),IPL_DEPTH_8U,1);
        IplImage* rgbcanny=cvCreateImage(cvGetSize(img2),IPL_DEPTH_8U,3);
        CvMemStorage* storage = cvCreateMemStorage(0);
        cvCvtColor( img3, gray, CV_BGR2GRAY );
        cvSmooth( gray, gray, CV_GAUSSIAN, 5,5  ); // smooth it, otherwise a lot of false circles may be detected
        cvCanny(gray,canny,10,100,3);

        //CvSeq* circles = cvHoughCircles( canny, storage, CV_HOUGH_GRADIENT, 2, gray->height/4, 200, 100 );
        //int j=0;
        cvCvtColor(canny,rgbcanny,CV_GRAY2BGR);
        

 
/* copy subimage */
	/*	 sprintf(image,"%d.jpg",img_no);
            cvSaveImage( image, canny );
img_no++;
*/
//----------------------------
		  //cvShowImage( "Mouth", img );
		  captureImage(img2,pictureBox4);

        }
     //end mouth detection
         
}

/*Nose detection*/
private: System::Void detectNose( IplImage *img,CvRect *r)
{
  CvSeq *nose;
 
  //nose detection- set ROI
  cvSetImageROI(img,                    /* the source image */
                cvRect(r->x,            /* x = start from leftmost */
                       r->y+(r->height *1/2) , /* y = a few pixels from the top */
                       r->width,        /* width = same width with the face */
                       r->height/2  /* height = 1/3 of face height */
                      )
               );
         

  nose = cvHaarDetectObjects(img, /* the source image, with the estimated location defined */
                             cascade_nose,      /* the eye classifier */
                             storage,        /* memory buffer */
                             1.15, 3, 0,     /* tune for your app */
                             cvSize(25, 15)  /* minimum detection scale */
                            );

  for( int i = 0; i < (nose ? nose->total : 0); i++ )
      {
          CvRect *nose_cord = (CvRect*)cvGetSeqElem(nose, i);

          /* draw a red rectangle */
          cvRectangle(img,
                      cvPoint(nose_cord->x, nose_cord->y),
                      cvPoint(nose_cord->x + nose_cord->width, nose_cord->y + nose_cord->height),
                      CV_RGB(0,255, 0),
                      1, 8, 0
                    );

      }
}

/*Eyes detection*/
private: System::Void detectEyes( IplImage *img,CvRect *r)
{	int i;
	char image[20]; 
	static int  img_no;
    char *eyecascade;
    CvSeq *eyes;
    int eye_detect=0;

	CvFont font;
	double hScale=0.5;
	double vScale=0.5;
	int    lineWidth=1;
   IplImage *img2;
   IplImage *im[2];

   displaymsg=false;
   //eye detection starts
  /* Set the Region of Interest: estimate the eyes' position */
   
    cvSetImageROI(img,                    /* the source image */
          cvRect
          (
              r->x,            /* x = start from leftmost */
              r->y + (r->height/5.5), /* y = a few pixels from the top */
              r->width,        /* width = same width with the face */
              r->height/3.0    /* height = 1/3 of face height */
          )
      );

 
      /* detect the eyes */
      eyes = cvHaarDetectObjects( img,            /* the source image, with the estimated location defined */
                                  cascade_e,      /* the eye classifier */
                                  storage,        /* memory buffer */
                                  1.15, 3, 0,     /* tune for your app */
                                  cvSize(25, 15)  /* minimum detection scale */
                                );
   
     // printf("\no of eyes detected are %d",eyes->total);
	  
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	  if(eyes->total==0)
		{
			now=0;
			displaymsg=true;
			
		}
   else
	   now=1;
   if(last!=now){
	   blink_count++;
	}
   last=now;
   eyecount->Text=Convert::ToString(blink_count);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     
        /* draw a rectangle for each detected eye */
        for(  i = 0; i < (eyes ? eyes->total : 0); i++ )
          {
              eye_detect++;
              /* get one eye */
              CvRect *eye = (CvRect*)cvGetSeqElem(eyes, i);
              /* draw a blue rectangle */
			  int x,y,width,height;
			  x=eye->x;
			  y=eye->y;
			  width=eye->width;
			  height=eye->height;

                        cvRectangle(img,
                                    cvPoint(eye->x, eye->y),
                                    cvPoint(eye->x + eye->width, eye->y + eye->height),
                                    CV_RGB(0, 0, 255),
                                    1, 8, 0
                                   );
						IplImage *img3 = cvCreateImage(cvGetSize(img),
                               img->depth,
                               img->nChannels);
						cvCopy(img, img3, NULL);

cvSetImageROI(img3, cvRect(eye->x, eye->y, eye->width, eye->height));
		  im[i] = cvCreateImage(cvGetSize(img3),
                               img3->depth,
                               img3->nChannels);

/*detect iris*/
		IplImage* gray = cvCreateImage( cvGetSize(img3), IPL_DEPTH_8U, 1 );
        IplImage* canny=cvCreateImage(cvGetSize(img3),IPL_DEPTH_8U,1);
        IplImage* rgbcanny=cvCreateImage(cvGetSize(img3),IPL_DEPTH_8U,3);
        CvMemStorage* storage = cvCreateMemStorage(0);
        cvCvtColor( img3, gray, CV_BGR2GRAY );
        cvSmooth( gray, gray, CV_GAUSSIAN, 1,1  ); // smooth it, otherwise a lot of false circles may be detected
        //cvCanny(gray,canny,10,100,3);

        CvSeq* circles = cvHoughCircles( gray, storage, CV_HOUGH_GRADIENT, 2, gray->height/4, 200, 100 );
        int j;
        cvCvtColor(canny,rgbcanny,CV_GRAY2BGR);
        for( j = 0; j < circles->total; j++ )
        {
             float* p = (float*)cvGetSeqElem( circles, j );
             cvCircle( img3, cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[3]), CV_RGB(0,255,0), 1, 8, 0 );
             cvCircle( img3, cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[2]), CV_RGB(255,0,0), 1, 8, 0 );
        
			 //sprintf(image,"%d.jpg",img_no);
            //cvSaveImage( image, img3 );
			img_no++;
		}


 /*-----------*/

/* copy subimage */

		if(takeimg)
		{
		    sprintf(image,"%d.jpg",img_no);
            cvSaveImage( image, img3 );
			img_no++;
			takeimg=false;
		}
		  cvCopy(img3, im[i], NULL);
		 if(i==0)
			 captureImage(im[0],pictureBox2);
		 if(i==1)
			 captureImage(im[1],pictureBox3);
				
           }
		
		cvResetImageROI(img);
		
		
		

           
}
private: System::Void detectFacialFeatures( IplImage *img,IplImage *temp_img,int img_no)
{
   
    char image[100],msg[100],temp_image[100];
    float m[6];
    double factor = 1;
    CvMat M = cvMat( 2, 3, CV_32F, m );
    int w = (img)->width;
   int h = (img)->height;
    CvSeq* faces;
    CvRect *r;

    m[0] = (float)(factor*cos(0.0));
   m[1] = (float)(factor*sin(0.0));
   m[2] = w*0.5f;
   m[3] = -m[1];
    m[4] = m[0];
    m[5] = h*0.5f;
   
    cvGetQuadrangleSubPix(img, temp_img, &M);
    CvMemStorage* storage=cvCreateMemStorage(0);
    cvClearMemStorage( storage );
   
    if( cascade )
        faces = cvHaarDetectObjects(img,cascade, storage, 1.2, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(20, 20));
    else
        printf("\nFrontal face cascade not loaded\n");

    printf("\n no of faces detected are %d",faces->total);
   
	if(faces->total>0)
    {
    /* for each face found, draw a red box */
    for(int i = 0 ; i < 1/*( faces ? faces->total : 0 )*/ ; i++ )
    {       
        r = ( CvRect* )cvGetSeqElem( faces, i );
        cvRectangle( img,cvPoint( r->x, r->y ),cvPoint( r->x + r->width, r->y + r->height ),
                     CV_RGB( 255, 0, 0 ), 1, 8, 0 );   
   
        printf("\n face_x=%d face_y=%d wd=%d ht=%d",r->x,r->y,r->width,r->height);
       
        detectEyes(img,r);
        /* reset region of interest */
       // cvResetImageROI(img);
        //detectNose(img,r);
        cvResetImageROI(img);
        detectMouth(img,r);
        cvResetImageROI(img);
    }
    /* reset region of interest */
      cvResetImageROI(img);
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 2, CV_AA);
	if(displaymsg){
		cvPutText(img, "Eye= Closed", cvPoint(10, 470), &font, cvScalar(0, 0, 255, 0));
	}
	else
		cvPutText(img, "Eye= Opened", cvPoint(10, 470), &font, cvScalar(0, 255, 0, 0));

      
            
			
        }
	  
}

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			timer2->Enabled=false;
			timer1->Enabled=false;
			cvReleaseHaarClassifierCascade( &cascade );
    cvReleaseHaarClassifierCascade( &cascade_e );
   
    cvReleaseHaarClassifierCascade( &cascade_nose );
    cvReleaseHaarClassifierCascade( &cascade_mouth );
    cvReleaseMemStorage( &storage );
	blink_count/=2;
	textBox2->Text=Convert::ToString(blink_count);
   
     //cvReleaseImage(&img);
     //cvReleaseImage(&temp_img);
		 }
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
			 	
	  IplImage *img,*temp_img,* t_img;
	  char image[100],temp_image[100];
   
	if( capture )
    {   int j=0;
        //for(;;)
	
        {
            srcImage = cvQueryFrame( capture );
           
			t_img=img=srcImage;
			temp_img=srcImage;
			//cvNamedWindow( "Example1", 1 );
			detectFacialFeatures(t_img,temp_img,j);
	
			//cvShowImage( "Example1", t_img );
			captureImage(t_img,pictureBox1);
			j++;		
            
        }
        //cvReleaseCapture( &capture );
    }


    
		 }
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			  //srcImage = cvQueryFrame( capture );
			//captureImage(srcImage,pictureBox1);
		timer2->Enabled=true;
		timer2->Interval=20;
		timer1->Enabled=true;
		timer1->Interval=60000*int::Parse(comboBox1->Text);
		 /* load the classifier
       note that I put the file in the same directory with
       this code */
    storage = cvCreateMemStorage( 0 );
    cascade = ( CvHaarClassifierCascade* )cvLoad( face_cascade, 0, 0, 0 );
    cascade_e = ( CvHaarClassifierCascade* )cvLoad( eye_cascade, 0, 0, 0 );
    cascade_nose = ( CvHaarClassifierCascade* )cvLoad( nose_cascade, 0, 0, 0 );
    cascade_mouth = ( CvHaarClassifierCascade* )cvLoad( mouth_cascade, 0, 0, 0 );
  
	//capture = cvCreateCameraCapture(0);
	now=0;
	last=0;
	blink_count=0;
	displaymsg=false;
			 
		 }

private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 takeimg=true;

		 }
};
}

