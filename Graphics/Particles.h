#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

namespace Particles {
	// Particle type
	enum class Type {
		Line = 0,
		Out = 1
	};

	// Particle class
	class Particle {
	public:
		Particle(float size, sf::Vector2f move, sf::Vector2f pos, float alpha_change, sf::Color color) {
			this->shape = new sf::CircleShape(size);
			this->move = move;
			this->alpha_change = alpha_change;

			this->shape->setOrigin(sf::Vector2f(size, size));
			this->shape->setPosition(pos);
			this->shape->setFillColor(color);

			this->alpha = 255;
			this->color = color;
		}
		~Particle() {
			delete this->shape;
			this->shape = NULL;
		}

		void update(float dtime) {
			if (alpha > 0) {
				this->shape->move(this->move * dtime);
				this->alpha -= this->alpha_change * dtime;

				this->color.a = (uint8_t) this->alpha;
				this->shape->setFillColor(color);
			}

		}

		void draw(sf::RenderTarget* target) {
			if (this->alpha > 0) {
				target->draw(*shape);
			}
		}

		bool finished() {
			return this->alpha <= 0;
		}

	private:
		sf::CircleShape* shape;

	private:
		sf::Vector2f move;
		sf::Color color;
		float alpha_change;
		float alpha;
	};

	
	// Particle handler
	class ParticleHandler {
	public:
		ParticleHandler(float size, float rot, sf::Vector2f pos, float alpha_change,
				sf::Color color, Type type, int span, float speed, int particle_amount) {

			this->size = size;
			this->color = color;
			this->type = type;

			rot *= 3.14159 / 180.f;
			
			this->move = sf::Vector2f(0.f, speed);
			this->move = sf::Vector2f(-speed * sin(rot), speed * cos(rot));

			this->span = span;
			this->alpha_change = alpha_change;

			this->particles.resize(particle_amount);
			this->pos = pos;

			for (size_t i = 0; i < particles.size(); i++) {
				this->particles[i] = NULL;
			}

			this->adding = true;
		}
		~ParticleHandler() {
			this->particles.clear();
		}

		void Draw(sf::RenderTarget* target) {
			for (size_t i = 0; i < particles.size(); i++) {
				if (this->particles[i] != NULL)
					this->particles[i]->draw(target);
			}
		}

		void Update(float dtime) {
			int maxu = 0;
			for (size_t i = 0; i < particles.size(); i++) {
				if (this->particles[i] != NULL) {
					this->particles[i]->update(dtime);

					if (this->particles[i]->finished()) {
						delete this->particles[i];
						this->particles[i] = NULL;
					}
				}
				else {
					if (maxu < 10 && adding) {
						float angle = 0.f;
						if (this->type == Type::Line) {
							if (span != 0)
								angle = float((rand() % span * 2) - span) + (float)rand() / (float)RAND_MAX;
						}
						else {
							angle = rand() % 360 + (float)rand() / (float)RAND_MAX;
						}

						angle *= 3.14159 / 180.f;
						sf::Vector2f a(move.x * cos(angle) - move.y * sin(angle),
							move.x * sin(angle) + move.y * cos(angle));
						this->particles[i] = new Particle(size, a, pos, alpha_change, color);

						maxu++;
					}
				}
			}
		}

		void setAdding(bool adding) {
			this->adding = adding;
		}

		bool getAdding() {
			return this->adding;
		}

	private:
		std::vector<Particle*> particles;

	private:
		sf::Vector2f move;
		sf::Vector2f pos;
		sf::Color color;
		float alpha_change;
		float size;
		int span;
		Type type;

	private:
		bool adding;
	};
}