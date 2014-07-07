#include "AudioHandler.h"
#include "Logger.h"

AudioHandler::AudioHandler() :
	currentMusic(nullptr),
	currentEffects()
{

}

AudioHandler::~AudioHandler(){
	if(this->currentMusic != nullptr){
		Mix_FreeMusic(this->currentMusic);
		this->currentMusic = nullptr;
	}

	for(auto effect : this->currentEffects){
		Mix_FreeChunk(effect);
	}

	this->currentEffects.clear();
}

void AudioHandler::setCurrentMusic(const std::string& path_){
	if(this->currentMusic != nullptr){
		Mix_FreeMusic(this->currentMusic);
	}

	this->currentMusic = Mix_LoadMUS(path_.c_str());
}

void AudioHandler::playMusic(const int times_){
	if(this->currentMusic){
		Mix_PlayMusic(this->currentMusic, times_);
	}
	else{
		Log(WARN) << "There is no song loaded.";
	}
}

void AudioHandler::stopMusic(){
	Mix_HaltMusic();	
}

void AudioHandler::setMusicVolume(const unsigned int percent_){
	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_VolumeMusic(value);
}

void AudioHandler::addSoundEffect(const std::string& path_){
	Mix_Chunk* effect = Mix_LoadWAV(path_.c_str());

	if(effect == nullptr){
		Log(DEBUG) << "Loaded null chunk " << path_ << " " << Mix_GetError();
	}

	/// @todo Resource manager for audio.
	this->currentEffects.push_back(effect);

	playEffect(effect, 0);
}

void AudioHandler::playEffect(Mix_Chunk* const effect_, const int times_){
	const int playedChannel = Mix_PlayChannel(-1, effect_, times_);

	if(playedChannel == -1){
		Log(ERROR) << "Failed to play sound effect on a channel. " << Mix_GetError();
	}
}

void AudioHandler::setEffectVolume(const unsigned int percent_){
	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_Volume(1, value);
}

void AudioHandler::changeMusic(const std::string& path_){
	stopMusic();
	setCurrentMusic(path_);
	playMusic(MIX_LOOP);
}
