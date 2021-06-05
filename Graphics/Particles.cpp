#include "Particles.h"

namespace Particles {
	void ParticleHandler::setAdding(bool add) {
		if (add && !this->adding) {
			for (int i = 0; i < particles.size(); i++) {
				if (particles[i] != NULL) {
					delete particles[i];
					particles[i] = NULL;
				}
				Add_Particle(i);
			}
		}
		this->adding = add;
	}

	void ParticleHandler::setDrawing(bool draw) {
		this->drawing = draw;
	}
	bool ParticleHandler::getDrawing() {
		return this->drawing;
	}


	bool ParticleHandler::getAdding() {
		return this->adding;
	}

	void ParticleHandler::changePos(sf::Vector2f newPos) {
		this->pos = newPos;
	}

	void ParticleHandler::changeColor(sf::Color newColor) {
		this->color = newColor;
	}

	void ParticleHandler::changeSpan(int newSpan) {
		this->span = newSpan;
	}

	void ParticleHandler::changeType(Type newType) {
		this->type = newType;
	}

	void ParticleHandler::changeMoveVector(sf::Vector2f newMove) {
		this->move = newMove;
	}

	void ParticleHandler::changeSize(float newSize) {
		this->size = newSize;
	}

	void ParticleHandler::changeAlphaChange(float newAlpha_change) {
		this->alpha_change = newAlpha_change;
	}

	float ParticleHandler::getAlpha_change() {
		return this->alpha_change;
	}

	sf::Vector2f ParticleHandler::getPos() {
		return this->pos;
	}

	
	sf::Color ParticleHandler::getColor() {
		return this->color;
	}


	int ParticleHandler::getSpan() {
		return this->span;
	}


	Type ParticleHandler::getType() {
		return this->type;
	}


	sf::Vector2f ParticleHandler::getMove() {
		return this->move;
	}


	float ParticleHandler::getSize() {
		return this->size;
	}


	// reconstruct

	void ParticleHandler::ReConstruct(float size, float rot, sf::Vector2f pos, float alpha_change,
		sf::Color color, Type type, int span, float speed, int particle_amount, int alpha_variety) {
		this->drawing = true;
		this->adding = true;

		this->size = size;
		this->color = color;
		this->type = type;

		rot *= 3.14159f / 180.f;

		this->move = sf::Vector2f(0.f, speed);
		this->move = sf::Vector2f(-speed * sinf(rot), speed * cosf(rot));

		this->span = span;
		this->alpha_change = alpha_change;

		this->particles.resize(particle_amount);
		this->pos = pos;
		this->alpha_variety = alpha_variety;
	}


	///--------
	
	void ParticleHandler::clearMem() {
		for (int i = 0; i < particles.size(); i++) {
			if (particles[i] != NULL) {
				delete particles[i];
				particles[i] = NULL;
			}
		}
		this->adding = false;
		this->drawing = false;
	}

	void ParticleHandler::creatMem() {
		this->adding = true;
		this->drawing = true;
	}

}