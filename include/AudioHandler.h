#ifndef INCLUDE_AUDIOHANDLER_H
#define INCLUDE_AUDIOHANDLER_H

#define MIX_LOOP -1

#include "SDLWrapper.h"
#include <string>

/**
* The audio handler.
* Class that handles all the audio in the game. Is a singleton, so should be called in each
* 	state.
*/
class AudioHandler {

	public:
		/**
		* The constructor.
		* Initializes attributes and calls the initializing function.
		* @see AudioHandler::initialize
		*/
		AudioHandler();

		/**
		* The destructor.
		* Deletes the AudioHandler::instance and closes SDL_Mixer.
		*/
		virtual ~AudioHandler();

		/**
		* Plays the current music.
		* @note Will warn if there is no music loaded.
		* @param times_ : Times to loop the song. MIX_LOOP (or -1) for infinite looping.
		*/
		void playMusic(const int times_);

		/**
		* Plays the current effect.
		* @note Will warn if there is no effect loaded.
		* @param times_ : Times to loop the song. MIX_LOOP (or -1) for infinite looping.
		*/
		void playEffect(const int times_);

		/**
		* Stops playing the current music.
		*/
		void stopMusic();

		/**
		* Sets the volume for the music.
		* If the percent_ is over 100, will be set to 100.
		* @param percent_ : The volume percentage (0-100).
		*/
		void setMusicVolume(const unsigned int percent_);		

		/**
		* Sets the volume for the effects.
		* If the percent_ is over 100, will be set to 100.
		* @param percent_ : The volume percentage (0-100).
		*/
		void setEffectVolume(const unsigned int percent_);

		/**
		* Changes current music.
		* Stops the music, sets it, and plays it with infinite looping.
		* @param path_ : The path to the desired music.
		*/
		void changeMusic(const std::string& path_);

		/**
		* Sets the current music.
		* If one already exists, frees it first.
		* @param path_ : The path to the desired music.
		*/
		void setCurrentMusic(const std::string& path_);

		/**
		* Sets the current effect.
		* If one already exists, frees it first.
		* @param path_ : The path to the desired effect.
		*/
		void setCurrentEffect(const std::string& path_);

	private:
		Mix_Music* currentMusic; /**< The current music that is playing. */
		Mix_Chunk* currentEffect; /**< The current effect that is playing. */

};

#endif // INCLUDE_AUDIOHANDLER_H
