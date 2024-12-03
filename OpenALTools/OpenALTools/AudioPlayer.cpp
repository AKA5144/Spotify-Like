#pragma once

#include <al.h>
#include <alc.h>
#include "CWaves.h"  // Inclure la classe CWaves pour la gestion de fichiers audio
#include "LoadOAL.h" // Pour les fonctions de gestion OpenAL si nécessaire
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
                std::cerr << "Erreur de connexion au périphérique audio." << std::endl;
                return;
            }
            ALCcontext* context = alcCreateContext(device, nullptr);
            if (!context || !alcMakeContextCurrent(context)) {
                std::cerr << "Erreur de création du contexte audio." << std::endl;
                return;
            }
            std::cout << "OpenAL initialisé avec succès." << std::endl;

            // Utilisation de pin_ptr pour s'assurer que la mémoire n'est pas déplacée par le GC
            pin_ptr<ALuint> pSource = &source;
            pin_ptr<ALuint> pBuffer = &buffer;

            // Génération de la source et du tampon
            alGenSources(1, pSource);
            if (alGetError() != AL_NO_ERROR) {
                std::cerr << "Erreur lors de la génération de la source." << std::endl;
            }

            alGenBuffers(1, pBuffer);
            if (alGetError() != AL_NO_ERROR) {
                std::cerr << "Erreur lors de la génération du tampon." << std::endl;
            }

            // Initialisation de la classe CWaves
            waveHandler = new CWaves();
        }

        ~AudioPlayer() {
            // Libération des ressources audio
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
            std::cout << "Ressources audio libérées." << std::endl;
        }

        void LoadAudio(const std::string& filePath) {
            // Charger le fichier audio
            WAVEID waveID;
            WAVERESULT result = waveHandler->LoadWaveFile(filePath.c_str(), &waveID);
            if (result != WR_OK) {
                std::cerr << "Erreur lors du chargement du fichier audio : " << filePath << std::endl;
                return;
            }

            // Obtenir les informations nécessaires sur le format de l'audio
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
                std::cerr << "Erreur : la taille du fichier audio est nulle ou la récupération a échoué." << std::endl;
                return;
            }

            // Lire les données dans un tampon
            char* data = new char[fileSize]; // Allocation mémoire pour les données
            unsigned long bytesRead;
            result = waveHandler->ReadWaveData(waveID, data, fileSize, &bytesRead);
            if (result != WR_OK || bytesRead != fileSize) {
                std::cerr << "Erreur lors de la lecture des données audio." << std::endl;
                delete[] data;
                return;
            }

            // Déterminer le format pour OpenAL
            ALenum format;
            if (waveFormat.nChannels == 1) {
                format = (waveFormat.wBitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
            }
            else if (waveFormat.nChannels == 2) {
                format = (waveFormat.wBitsPerSample == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
            }
            else {
                std::cerr << "Format audio non supporté." << std::endl;
                delete[] data;
                return;
            }

            // Charger les données dans le tampon OpenAL
            alBufferData(buffer, format, data, bytesRead, waveFormat.nSamplesPerSec);
            if (alGetError() != AL_NO_ERROR) {
                std::cerr << "Erreur lors du chargement des données audio dans le tampon." << std::endl;
                delete[] data;
                return;
            }

            // Libérer la mémoire après le chargement
            delete[] data;

            // Attacher le tampon à la source
            alSourcei(source, AL_BUFFER, buffer);
            if (alGetError() != AL_NO_ERROR) {
                std::cerr << "Erreur lors de l'attachement du tampon à la source." << std::endl;
                return;
            }

            std::cout << "Chargement de l'audio réussi." << std::endl;
        }


        void Play() {
            if (!isPlaying) {
                if (buffer == 0) {
                    std::cerr << "Aucun tampon audio chargé. Veuillez charger un fichier audio d'abord." << std::endl;
                    return;
                }

                pin_ptr<ALuint> pSource = &source;
                alSourcePlay(*pSource);
                if (alGetError() != AL_NO_ERROR) {
                    std::cerr << "Erreur lors de la lecture de la source." << std::endl;
                }
                else {
                    isPlaying = true;
                    std::cout << "Lecture commencée." << std::endl;
                }
            }
            else {
                std::cout << "L'audio est déjà en lecture." << std::endl;
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
                    std::cerr << "Erreur lors de l'arrêt de la source." << std::endl;
                }
                else {
                    isPlaying = false;
                    std::cout << "Lecture arrêtée." << std::endl;
                }
            }
            else {
                std::cout << "L'audio n'est pas en lecture." << std::endl;
            }
        }
    };
}
