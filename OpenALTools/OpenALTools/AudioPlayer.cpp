#include "../framework/Win32/Framework.h"
#include "AudioPlayer.h"
#include <msclr/marshal_cppstd.h>

namespace OpenALTools {
    // Déclaration globale de la source OpenAL
    ALuint audioSource = 0;

    AudioPlayer::AudioPlayer() {
        // Initialisation du framework
        ALFWInit();

        if (!ALFWInitOpenAL()) {
            ALFWShutdown();
            return;
        }

        return;
    }

    void AudioPlayer::stopPlayback() {
        if (audioSource) {
            alSourceStop(audioSource);
        }
    }

    int AudioPlayer::playAudio(const char* audioFile) {

        ALuint audioBuffer;
        ALint playbackState;

        AudioPlayer::stopPlayback();

        // Génération d'un buffer OpenAL
        alGenBuffers(1, &audioBuffer);

        // Chargement du fichier audio dans le buffer OpenAL
        if (!ALFWLoadWaveToBuffer((char*)audioFile, audioBuffer)) {
            ALFWprintf("Échec du chargement de %s\n", audioFile);
            return -1;
        }

        // Génération d'une source pour lire le buffer
        alGenSources(1, &audioSource);

        // Attachement du buffer à la source
        alSourcei(audioSource, AL_BUFFER, audioBuffer);
        alSourcei(audioSource, AL_LOOPING, AL_TRUE); // Lecture en boucle

        // Lecture de la source
        alSourcePlay(audioSource);

        return 0;
    }

    void AudioPlayer::pausePlayback() {
        if (audioSource) {
            alSourcePause(audioSource);
        }
    }

    void AudioPlayer::resumePlayback() {
        if (audioSource) {
            alSourcePlay(audioSource);
        }
    }

    void AudioPlayer::setAudioVolume(float volumeLevel) {
        volumeLevel /= 100.0f;
        // Limitation du volume entre 0.0f et 1.0f
        if (volumeLevel < 0.0f) volumeLevel = 0.0f;
        if (volumeLevel > 1.0f) volumeLevel = 1.0f;

        if (audioSource) {
            alSourcef(audioSource, AL_GAIN, volumeLevel);
        }
    }

    void AudioPlayer::cleanupResources() {
        if (audioSource) {
            alSourceStop(audioSource);
            alDeleteSources(1, &audioSource);
            audioSource = 0; // Réinitialisation de la source
        }

        ALFWShutdownOpenAL();
        ALFWShutdown();
    }
}