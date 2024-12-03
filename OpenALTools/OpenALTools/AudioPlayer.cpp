#pragma once

#include <al.h>
#include <alc.h>
#include "CWaves.h"  // Inclure la classe CWaves pour la gestion de fichiers audio
#include "LoadOAL.h" // Pour les fonctions de gestion OpenAL si n�cessaire
#include <iostream>
#include <vector>

namespace OpenALTools {

    public ref class AudioPlayer {
    private:
        ALuint source;  // Variable pour la source
        ALuint buffer;  // Variable pour le tampon
        bool isPlaying;
        CWaves* waveHandler; // Pointeur vers l'instance de CWaves

    public:
        AudioPlayer() : source(0), buffer(0), isPlaying(false), waveHandler(nullptr) {
            // Initialisation de OpenAL
            ALCdevice* device = alcOpenDevice(nullptr);
            if (!device) {
                std::cerr << "Erreur de connexion au p�riph�rique audio." << std::endl;
                return;
            }
            ALCcontext* context = alcCreateContext(device, nullptr);
            if (!context || !alcMakeContextCurrent(context)) {
                std::cerr << "Erreur de cr�ation du contexte audio." << std::endl;
                return;
            }
            std::cout << "OpenAL initialis� avec succ�s." << std::endl;

            // Utilisation de pin_ptr pour s'assurer que la m�moire n'est pas d�plac�e par le GC
            pin_ptr<ALuint> pSource = &source;
            pin_ptr<ALuint> pBuffer = &buffer;

            // G�n�ration de la source et du tampon
            alGenSources(1, pSource);
            if (alGetError() != AL_NO_ERROR) {
                std::cerr << "Erreur lors de la g�n�ration de la source." << std::endl;
            }

            alGenBuffers(1, pBuffer);
            if (alGetError() != AL_NO_ERROR) {
                std::cerr << "Erreur lors de la g�n�ration du tampon." << std::endl;
            }

            // Initialisation de la classe CWaves
            waveHandler = new CWaves();
        }

        ~AudioPlayer() {
            // Lib�ration des ressources audio
            if (source != 0) {
                pin_ptr<ALuint> pSource = &source;
                alDeleteSources(1, pSource);
            }
            if (buffer != 0) {
                pin_ptr<ALuint> pBuffer = &buffer;
                alDeleteBuffers(1, pBuffer);
            }
            if (waveHandler) {
                delete waveHandler;
            }
            std::cout << "Ressources audio lib�r�es." << std::endl;
        }

        void LoadAudio(const std::string& filePath) {
            // Charger le fichier audio
            WAVEID waveID;
            WAVERESULT result = waveHandler->LoadWaveFile(filePath.c_str(), &waveID);
            if (result != WR_OK) {
                std::cerr << "Erreur lors du chargement du fichier audio : " << filePath << std::endl;
                return;
            }

            // Obtenir les informations n�cessaires sur le format de l'audio
            WAVEFORMATEX waveFormat;
            result = waveHandler->GetWaveFormatExHeader(waveID, &waveFormat);
            if (result != WR_OK) {
                std::cerr << "Erreur lors de l'obtention des informations de format de l'audio." << std::endl;
                return;
            }

            // Lire la taille totale du fichier audio
            unsigned long fileSize;
            result = waveHandler->GetWaveSize(waveID, &fileSize);
            if (result != WR_OK || fileSize == 0) {
                std::cerr << "Erreur : la taille du fichier audio est nulle ou la r�cup�ration a �chou�." << std::endl;
                return;
            }

            // Lire les donn�es dans un tampon
            char* data = new char[fileSize]; // Allocation m�moire pour les donn�es
            unsigned long bytesRead;
            result = waveHandler->ReadWaveData(waveID, data, fileSize, &bytesRead);
            if (result != WR_OK || bytesRead != fileSize) {
                std::cerr << "Erreur lors de la lecture des donn�es audio." << std::endl;
                delete[] data;
                return;
            }

            // D�terminer le format pour OpenAL
            ALenum format;
            if (waveFormat.nChannels == 1) {
                format = (waveFormat.wBitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
            }
            else if (waveFormat.nChannels == 2) {
                format = (waveFormat.wBitsPerSample == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
            }
            else {
                std::cerr << "Format audio non support�." << std::endl;
                delete[] data;
                return;
            }

            // Charger les donn�es dans le tampon OpenAL
            alBufferData(buffer, format, data, bytesRead, waveFormat.nSamplesPerSec);
            if (alGetError() != AL_NO_ERROR) {
                std::cerr << "Erreur lors du chargement des donn�es audio dans le tampon." << std::endl;
                delete[] data;
                return;
            }

            // Lib�rer la m�moire apr�s le chargement
            delete[] data;

            // Attacher le tampon � la source
            alSourcei(source, AL_BUFFER, buffer);
            if (alGetError() != AL_NO_ERROR) {
                std::cerr << "Erreur lors de l'attachement du tampon � la source." << std::endl;
                return;
            }

            std::cout << "Chargement de l'audio r�ussi." << std::endl;
        }


        void Play() {
            if (!isPlaying) {
                if (buffer == 0) {
                    std::cerr << "Aucun tampon audio charg�. Veuillez charger un fichier audio d'abord." << std::endl;
                    return;
                }

                pin_ptr<ALuint> pSource = &source;
                alSourcePlay(*pSource);
                if (alGetError() != AL_NO_ERROR) {
                    std::cerr << "Erreur lors de la lecture de la source." << std::endl;
                }
                else {
                    isPlaying = true;
                    std::cout << "Lecture commenc�e." << std::endl;
                }
            }
            else {
                std::cout << "L'audio est d�j� en lecture." << std::endl;
            }
        }

        void Pause() {
            if (isPlaying) {
                pin_ptr<ALuint> pSource = &source;
                alSourcePause(*pSource);
                if (alGetError() != AL_NO_ERROR) {
                    std::cerr << "Erreur lors de la pause de la source." << std::endl;
                }
                else {
                    isPlaying = false;
                    std::cout << "Lecture en pause." << std::endl;
                }
            }
            else {
                std::cout << "L'audio n'est pas en lecture." << std::endl;
            }
        }

        void Stop() {
            if (isPlaying) {
                pin_ptr<ALuint> pSource = &source;
                alSourceStop(*pSource);
                if (alGetError() != AL_NO_ERROR) {
                    std::cerr << "Erreur lors de l'arr�t de la source." << std::endl;
                }
                else {
                    isPlaying = false;
                    std::cout << "Lecture arr�t�e." << std::endl;
                }
            }
            else {
                std::cout << "L'audio n'est pas en lecture." << std::endl;
            }
        }
    };
}
