#pragma once
#include "ChartsRoot.h"

Chart* plex;
ChartPoint* CurrPoint;
Point* p = new Point;
Point* Tmp = new Point;
Chart* LineNew;
ChartPoint* PointsForm;

namespace Lab2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Plex
	/// </summary>
	public ref class Plex : public System::Windows::Forms::Form
	{
	public:
		Plex(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			BackColor = Color::White;
			gr = CreateGraphics();
			plex = new Chart;
			plex->SetVisible(false);
			CurrPoint = new ChartPoint;
			CurrPoint->SetX(0);
			CurrPoint->SetY(0);
		}

	public:
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button1;

	public:
		Graphics ^ gr;

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Plex()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(770, 27);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(104, 32);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Стереть";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Plex::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(770, 65);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(103, 31);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Переместить";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Plex::button3_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(770, 102);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(51, 20);
			this->textBox1->TabIndex = 3;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(827, 102);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(46, 20);
			this->textBox2->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(790, 125);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(14, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"X";
			this->label1->TextAlign = System::Drawing::ContentAlignment::BottomLeft;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(842, 125);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(14, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Y";
			this->label2->Click += gcnew System::EventHandler(this, &Plex::label2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(779, 175);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(93, 43);
			this->button1->TabIndex = 7;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Plex::button1_Click);
			// 
			// Plex
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(896, 562);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Name = L"Plex";
			this->Text = L"Plex";
			this->Load += gcnew System::EventHandler(this, &Plex::Plex_Load);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Plex::Plex_MouseClick);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Plex::Plex_MouseDown);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Plex::Plex_MouseUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Plex_Load(System::Object^  sender, System::EventArgs^  e) {
	}
			 
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	Chart* BC = new Chart;
	Chart* CA = new Chart;
	ChartPoint* B = new ChartPoint(400, 200);
	ChartPoint* C = new ChartPoint(300, 400);
	ChartPoint* A = new ChartPoint(200, 200);

	CurrPoint->SetX(-1);
	CurrPoint->SetY(-1);

	BC->SetFirst(B);
	BC->SetLast(C);
	CA->SetFirst(BC);
	CA->SetLast(A);

	plex->SetFirst(CA);
	plex->SetLast(B);
	plex->Show(gr, Pens::Black);
	plex->SetVisible(true);
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	if (plex->GetVisible())
	{
		plex->Hide(gr, Pens::White);
		plex->SetVisible(false);
	}
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	int x = Convert::ToInt32(textBox1->Text);
	int y = Convert::ToInt32(textBox2->Text);

	plex->Hide(gr, Pens::White);
	plex->MoveTo(x, y);
	plex->Show(gr, Pens::Black);
	plex->Reset();
}

private: System::Void Plex_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (plex->GetVisible())
	{
		*p = PointToClient(Control::MousePosition);
		CurrPoint = plex->SetCurrPoint(gr, Pens::Black, p->X, p->Y);
	}
	if (!plex->GetVisible()) {
		
		ChartPoint* A = new ChartPoint(e->X, e->Y);
		LineNew->SetFirst(A);
	}

	
}
private: System::Void Plex_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (plex->GetVisible() && CurrPoint->GetX() > 0 && CurrPoint->GetY() > 0 && e->X != CurrPoint->GetX() && e->Y != CurrPoint->GetY())
	{
		*Tmp = PointToClient(Control::MousePosition);

		PointsForm = new ChartPoint(Tmp->X, Tmp->Y);
		LineNew = new Chart;

		LineNew->SetFirst(PointsForm);
		LineNew->SetLast(CurrPoint);

		plex->AddLine(gr, Pens::Black, CurrPoint, LineNew);
		plex->Show(gr, Pens::Black);
	}
	if (!plex->GetVisible()){
		/*ChartPoint* B = new ChartPoint(e->X, e->Y);
		plex->SetLast(B);
		plex->Show(gr, Pens::Black);
		plex->SetVisible(true);*/
		ChartPoint* B = new ChartPoint(e->X, e->Y);
		LineNew->SetLast(B);
		plex->AddLine(gr, Pens::Black, CurrPoint, LineNew);
		plex->Show(gr, Pens::Black);
	}
}
private: System::Void Plex_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	
}
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
}

};
}
