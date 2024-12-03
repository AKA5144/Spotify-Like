#pragma once
#include "AudioPlayer.cpp"
#include <msclr/marshal_cppstd.h>
namespace OpenALTools {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			audioPlayer = gcnew OpenALTools::AudioPlayer();
			//TODO: ajoutez ici le code du constructeur
			//
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: OpenALTools::AudioPlayer^ audioPlayer;
	private: System::Windows::Forms::Button^ playButton;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ProgressBar^ timelineBar;
	private: System::Windows::Forms::Button^ importButton;

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ pauseButton;
	private: System::Windows::Forms::Button^ stopButton;
	private: System::Windows::Forms::ListBox^ listBox1;

	protected:

	protected:

	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timelineBar = (gcnew System::Windows::Forms::ProgressBar());
			this->importButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->pauseButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// playButton
			// 
			this->playButton->Location = System::Drawing::Point(175, 233);
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(75, 23);
			this->playButton->TabIndex = 0;
			this->playButton->Text = L"Play";
			this->playButton->UseVisualStyleBackColor = true;
			this->playButton->Click += gcnew System::EventHandler(this, &MyForm::playButtonClick);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(99, 152);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->trackBar1->Size = System::Drawing::Size(45, 104);
			this->trackBar1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(21, 152);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(48, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Volume :";
			// 
			// timelineBar
			// 
			this->timelineBar->Location = System::Drawing::Point(188, 176);
			this->timelineBar->Name = L"timelineBar";
			this->timelineBar->Size = System::Drawing::Size(184, 23);
			this->timelineBar->TabIndex = 3;
			this->timelineBar->Click += gcnew System::EventHandler(this, &MyForm::timelineBar_Click);
			// 
			// importButton
			// 
			this->importButton->Location = System::Drawing::Point(24, 13);
			this->importButton->Name = L"importButton";
			this->importButton->Size = System::Drawing::Size(120, 23);
			this->importButton->TabIndex = 4;
			this->importButton->Text = L"Import music. . .";
			this->importButton->UseVisualStyleBackColor = true;
			this->importButton->Click += gcnew System::EventHandler(this, &MyForm::import_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = "Audio Files|*.wav;*.ogg";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(150, 13);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(126, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Save Playlist";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// pauseButton
			// 
			this->pauseButton->Location = System::Drawing::Point(267, 233);
			this->pauseButton->Name = L"pauseButton";
			this->pauseButton->Size = System::Drawing::Size(75, 23);
			this->pauseButton->TabIndex = 6;
			this->pauseButton->Text = L"Pause";
			this->pauseButton->UseVisualStyleBackColor = true;
			this->pauseButton->Click += gcnew System::EventHandler(this, &MyForm::pauseButtonClick);
			// 
			// stopButton
			// 
			this->stopButton->Location = System::Drawing::Point(348, 233);
			this->stopButton->Name = L"stopButton";
			this->stopButton->Size = System::Drawing::Size(75, 23);
			this->stopButton->TabIndex = 7;
			this->stopButton->Text = L"Stop";
			this->stopButton->UseVisualStyleBackColor = true;
			this->stopButton->Click += gcnew System::EventHandler(this, &MyForm::stopButtonClick);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(450, 131);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(322, 264);
			this->listBox1->TabIndex = 8;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox1_SelectedIndexChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Gray;
			this->ClientSize = System::Drawing::Size(819, 464);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->stopButton);
			this->Controls->Add(this->pauseButton);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->importButton);
			this->Controls->Add(this->timelineBar);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->playButton);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	}

private: System::Void import_Click(System::Object^ sender, System::EventArgs^ e) {
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		// Obtenir le chemin complet du fichier sélectionné
		String^ filePath = openFileDialog1->FileName;

		// Convertir System::String^ en std::string (si nécessaire pour l'audioPlayer)
		std::string nativeFilePath = msclr::interop::marshal_as<std::string>(filePath);

		// Appeler la méthode LoadAudio de AudioPlayer
		audioPlayer->LoadAudio(nativeFilePath);
		audioPlayer->Play();

		// Extraire le nom du fichier pour l'afficher dans la ListBox
		String^ fileName = System::IO::Path::GetFileName(filePath);
		listBox1->Items->Add(fileName);
	}
}

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		saveFileDialog1->ShowDialog();

}
private: System::Void timelineBar_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void stopButtonClick(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pauseButtonClick(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void playButtonClick(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
