#pragma once

#include <iostream>
#include "AudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace experimental;

class SoundManager
{
public:
	SoundManager();
	int Play(string soundName, bool loop);
	void setVolume(int soundId, float value);
	void Pause(int soundId);
	void Resume(int soundId);
	void Stop(int soundId);
	~SoundManager();
};
