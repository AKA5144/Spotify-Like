#pragma once

#include <al.h>
#include <alc.h>
#include <iostream>

namespace OpenALTools {

    public ref class AudioPlayer {
    private:
        ALuint source;  // Variable pour la source
        ALuint buffer;  // Variable pour le tampon
        bool isPlaying;

    public:
        AudioPlayer() : source(0), buffer(0), isPlaying(false) {
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
            std::cout << "Ressources audio libérées." << std::endl;
        }

        void LoadAudio(const std::string& filePath) {
            // Exemple de code pour charger des données audio
            // Utilisez une bibliothèque tierce pour lire le fichier audio et charger les données dans le tampon
            pin_ptr<ALuint> pSource = &source;
            pin_ptr<ALuint> pBuffer = &buffer;
            alSourcei(*pSource, AL_BUFFER, *pBuffer);
        }

        void Play() {
            if (!isPlaying) {
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
