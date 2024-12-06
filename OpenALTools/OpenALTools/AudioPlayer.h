#pragma once

#include "Framework.h"
#include <al.h>
#include <alc.h>
#include <iostream>
#include <vector>
#include "AudioPlayer.h"
namespace OpenALTools {


	public class AudioPlayer
	{
	public:
		int playAudio(const char* audioFile);
		AudioPlayer();
		void pausePlayback();
		void resumePlayback();
		void stopPlayback();
		void cleanupResources();
		void setAudioVolume(float volumeLevel);
	};
}