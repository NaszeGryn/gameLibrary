#pragma once
#include <SFML/Audio.hpp>

namespace Audio {
	
	class Sound {
	public:
		Sound(std::string filename, float volume, bool loop) {
			this->buffer = new sf::SoundBuffer();
			this->buffer->loadFromFile(filename);
			this->sound = new sf::Sound(*this->buffer);
			this->sound->setVolume(volume);
			this->sound->setLoop(loop);
		}
		~Sound() {
			delete this->sound;
			delete this->buffer;
			this->buffer = NULL;
			this->sound = NULL;
		}

		void setVolume(float volume) { this->sound->setVolume(volume); }

		void play() { this->sound->play(); }
		void stop() { this->sound->stop(); }

		sf::Sound* getSound() { return this->sound; }
		sf::SoundBuffer* getBuffer() { return this->buffer; }
	private:
		sf::Sound* sound;
		sf::SoundBuffer* buffer;
	};
}