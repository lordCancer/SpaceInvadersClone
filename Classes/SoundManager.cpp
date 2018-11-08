#include "SoundManager.h"

SoundManager::SoundManager()
{
	AudioEngine::preload("sounds/menu.mp3");
	AudioEngine::preload("sounds/buttonsound.mp3");
	AudioEngine::preload("sounds/gameplay.mp3");
	AudioEngine::preload("sounds/shoot.mp3");
	AudioEngine::preload("sounds/explosion.mp3");
	AudioEngine::preload("sounds/enemyshoot.mp3");
	AudioEngine::preload("sounds/invaderkilled.mp3");
	AudioEngine::preload("sounds/gameover.mp3");
	AudioEngine::preload("sounds/levelclear.mp3");
}

int SoundManager::Play(string soundName, bool loop)
{
	int soundIndex = AudioEngine::play2d(soundName, loop, 1.0f);
	return soundIndex;
}

void SoundManager::setVolume(int soundId, float value)
{
	AudioEngine::setVolume(soundId, value);
}

void SoundManager::Pause(int soundId)
{
	AudioEngine::pause(soundId);
}

void SoundManager::Resume(int soundId)
{
	AudioEngine::resume(soundId);
}

void SoundManager::Stop(int soundId)
{
	AudioEngine::stop(soundId);
}

SoundManager::~SoundManager()
{

}