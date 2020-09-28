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
		// constructor Particle(float size, sf::Vector2f move, sf::Vector2f pos, float alpha_change, sf::Color color)
		Particle(float size, sf::Vector2f& move, sf::Vector2f& pos, float alpha_change, sf::Color& color) {
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

		void set(sf::Vector2f& move, sf::Vector2f& pos) {
			this->move = move;

			this->shape->setPosition(pos);

			this->alpha = 255;
			this->color = color;
		}

		void update(float dtime) {
			if (alpha > 10) {
				this->shape->move(this->move * dtime);
				this->alpha -= this->alpha_change * dtime;

				this->color.a = (uint8_t) this->alpha;
				this->shape->setFillColor(color);
			}
		}

		void draw(sf::RenderTarget* target) {
			target->draw(*shape);
		}

		bool finished() {
			return this->alpha <= 10.f;
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
		// constructor (float size, float rot, sf::Vector2f pos, float alpha_change,
		//sf::Color color, Type type, int span, float speed, int particle_amount)
		ParticleHandler(float size, float rot, sf::Vector2f pos, float alpha_change,
				sf::Color color, Type type, int span, float speed, int particle_amount) {

			this->size = size;
			this->color = color;
			this->type = type;

			rot *= 3.14159f / 180.f;
			
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

		void Add_Particle(int index) {
			float angle = 0.f;
			if (this->type == Type::Line) {
				if (span != 0)
					angle = float((rand() % span * 2) - span) + (float)rand() / (float)RAND_MAX;
			}
			else {
				angle = rand() % 360 + (float)rand() / (float)RAND_MAX;
			}

			angle *= 3.14159f / 180.f;
			sf::Vector2f a(move.x * cos(angle) - move.y * sin(angle),
				move.x * sin(angle) + move.y * cos(angle));
			this->particles[index] = new Particle(size, a, pos, alpha_change, color);
		}

		void Reset_Particle(int index) {
			float angle = 0.f;
			if (this->type == Type::Line) {
				if (span != 0)
					angle = float((rand() % span * 2) - span) + (float)rand() / (float)RAND_MAX;
			}
			else {
				angle = rand() % 360 + (float)rand() / (float)RAND_MAX;
			}

			angle *= 3.14159f / 180.f;
			sf::Vector2f a(move.x * cos(angle) - move.y * sin(angle),
				move.x * sin(angle) + move.y * cos(angle));
			(*this->particles[index]).set(a, pos);
		}

		void Draw(sf::RenderTarget* target) {
			if (adding) {
				for (size_t i = 0; i < particles.size(); i++) {
					if (this->particles[i] != NULL) {
						if (!this->particles[i]->finished()) {
							this->particles[i]->draw(target);
						}
					}
				}
			}
		}

		void Update(float dtime) {
			if (adding) {
				int maxu = 0;
				for (size_t i = 0; i < particles.size(); i++) {
					if (this->particles[i] != NULL) {
						if (this->particles[i]->finished() && maxu < 2 && adding) {
							this->Reset_Particle(i);
							maxu++;
						}
						
						this->particles[i]->update(dtime);
					}
					else {
						if (maxu < 1 && adding) {
							this->Add_Particle(i);
							maxu++;
						}
					}
				}
			}
		}

		void setAdding(bool add) {
			if (add && !this->adding) {
				for (int i = 0; i < particles.size() / 2.f; i++) {
					if (particles[i] != NULL) {
						delete particles[i];
						particles[i] = NULL;
					}
					Add_Particle(i);
				}
			}
			this->adding = add;
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