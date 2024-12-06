#pragma once
#include "AudioPlayer.h"
#include <vector>
#include <array>
using namespace System::IO;

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
			audioPlayer = new OpenALTools::AudioPlayer();


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
	private: OpenALTools::AudioPlayer* audioPlayer;
		   System::Collections::Generic::List<String^>^ Playlist = gcnew System::Collections::Generic::List<String^>();

	private: System::Windows::Forms::Button^ playButton;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::Label^ label1;

	private: System::Windows::Forms::Button^ importButton;

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ pauseButton;
	private: System::Windows::Forms::Button^ stopButton;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
		   int currentTrack = 0;
	private: System::Windows::Forms::Button^ button3;


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
			this->importButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->pauseButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
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
			this->trackBar1->Maximum = 100;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->trackBar1->Size = System::Drawing::Size(45, 104);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->Value = 100;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
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
			this->openFileDialog1->Filter = L"Audio Files|*.wav;*.ogg";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(150, 13);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(126, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Import Playlist";
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
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(456, 87);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(259, 281);
			this->richTextBox1->TabIndex = 9;
			this->richTextBox1->Text = L"";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(282, 13);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(112, 23);
			this->button3->TabIndex = 10;
			this->button3->Text = L"Save Playlist";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Gray;
			this->ClientSize = System::Drawing::Size(819, 464);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->stopButton);
			this->Controls->Add(this->pauseButton);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->importButton);
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
	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
	openFileDialog->Filter = "Fichiers WAV (*.wav)|*.wav|Fichiers OGG (*.ogg)|*.ogg";

	openFileDialog->ShowDialog();

	String^ filePath = openFileDialog->FileName;

	int splitSize = filePath->Split('\\')->Length;

	Playlist->Add(filePath);

	label1->Text = filePath->Split('\\')[splitSize - 1];

	richTextBox1->AppendText(label1->Text + "\n");
}

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	// Créer une instance de OpenFileDialog
	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
	openFileDialog->Filter = "Fichiers texte (*.txt)|*.txt"; // Types de fichiers pris en charge
	openFileDialog->Title = "Importer une playlist";

	// Afficher le dialogue et vérifier si l'utilisateur a sélectionné un fichier
	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		String^ filePath = openFileDialog->FileName; // Récupère le chemin complet du fichier sélectionné

		StreamReader^ reader = nullptr; // Déclare le StreamReader en dehors du try
		try {
			// Initialisation du StreamReader
			reader = gcnew StreamReader(filePath);

			// Nettoyer la playlist avant d'importer les nouvelles lignes
			Playlist->Clear();

			// Lire chaque ligne du fichier et l'ajouter à la playlist
			String^ line;
			while ((line = reader->ReadLine()) != nullptr) {
				Playlist->Add(line);
				int splitSize = line->Split('\\')->Length;
				richTextBox1->AppendText(line->Split('\\')[splitSize - 1] + "\n");
			}

			// Message de confirmation
			MessageBox::Show("succès  : " + filePath,
				"réussi", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (Exception^ ex) {
			// Gestion des erreurs
			MessageBox::Show("Erreur : " + ex->Message,
				"Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally {
			// Fermeture explicite du StreamReader
			if (reader != nullptr) {
				reader->Close();
			}
		}
	}
}

private: System::Void timelineBar_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void stopButtonClick(System::Object^ sender, System::EventArgs^ e) {
	audioPlayer->stopPlayback();

}
private: System::Void pauseButtonClick(System::Object^ sender, System::EventArgs^ e) {
	audioPlayer->pausePlayback();

}
private: System::Void playButtonClick(System::Object^ sender, System::EventArgs^ e) {
	if (Playlist->Count <= 0)
	{
		return;
	}
	String^ managedString = Playlist[currentTrack];
	std::string stdString = msclr::interop::marshal_as<std::string>(managedString);
	const char* word = stdString.c_str();

	if (managedString->Split('.')[managedString->Split('.')->Length - 1] == "wav")
	{
		audioPlayer->playAudio(word);
	}
}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
	audioPlayer->setAudioVolume(trackBar1->Value);
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	// Créer une instance de SaveFileDialog
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();

	// Configuration du SaveFileDialog
	saveFileDialog->Filter = "Fichiers texte (*.txt)|*.txt"; // Types de fichiers pris en charge
	saveFileDialog->Title = "Enregistrer la playlist";
	saveFileDialog->FileName = "playlist.txt"; // Nom de fichier par défaut

	// Afficher le dialogue et vérifier si l'utilisateur a sélectionné un fichier
	if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		String^ filePath = saveFileDialog->FileName; // Récupère le chemin choisi

		StreamWriter^ writer = nullptr; // Déclare le StreamWriter en dehors du try
		try {
			// Initialisation du StreamWriter
			writer = gcnew StreamWriter(filePath);

			// Écrit chaque ligne de la liste dans le fichier
			for each (String ^ song in Playlist) {
				writer->WriteLine(song);
			}

			// Message de confirmation
			MessageBox::Show("succès" + filePath,
				"Exportation réussie", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (Exception^ ex) {
			// Gestion des erreurs
			MessageBox::Show("Erreur" + ex->Message,
				"Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally {
			// Fermeture explicite du StreamWriter
			if (writer != nullptr) {
				writer->Close();
			}
		}
	}
}

};
}
