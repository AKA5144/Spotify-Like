#pragma once


int playAudio(const char* audioFile);
int initialize();
void pausePlayback();
void resumePlayback();
void stopPlayback();
void cleanupResources();
void setAudioVolume(float volumeLevel);
