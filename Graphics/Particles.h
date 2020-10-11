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

		sf::Vector2f getPos() {
			return this->shape->getPosition();
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

			this->ReConstruct(size, rot, pos, alpha_change,
				color, type, span, speed, particle_amount);

			for (size_t i = 0; i < particles.size(); i++) {
				this->particles[i] = NULL;
			}
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
			sf::Vector2f a(move.x * cosf(angle) - move.y * sinf(angle),
				move.x * sinf(angle) + move.y * cosf(angle));
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
			bool atZero = false;
			if (this->drawing) {
				for (size_t i = 0; i < particles.size(); i++) {
					if (this->particles[i] != NULL) {
						if (!this->particles[i]->finished()) {

							if (this->particles[i]->getPos() == this->pos) {
								if (!atZero) {
									this->particles[i]->draw(target);
									atZero = true;
								}
							}
							else {
								this->particles[i]->draw(target);
							}
						}
					}
				}
			}
		}

		void Update(float dtime) {
			if (drawing) {
				int maxu = 0;
				for (size_t i = 0; i < particles.size(); i++) {
					if (this->particles[i] != NULL) {
						if (this->particles[i]->finished() && maxu < 1 && adding) {
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

		void clearMem();
		void creatMem();

		void ReConstruct(float size, float rot, sf::Vector2f pos, float alpha_change,
			sf::Color color, Type type, int span, float speed, int particle_amount);

		// Setting and getting
		void setDrawing(bool draw);
		bool getDrawing();

		void setAdding(bool add);

		bool getAdding();

		void changePos(sf::Vector2f newPos);
		sf::Vector2f getPos();

		void changeColor(sf::Color newColor);
		sf::Color getColor();

		void changeSpan(int newSpan);
		int getSpan();

		void changeType(Type newType);
		Type getType();

		void changeMoveVector(sf::Vector2f newMove);
		sf::Vector2f getMove();

		void changeSize(float newSize);
		float getSize();
		
		void changeAlphaChange(float newAlpha_change);
		float getAlpha_change();

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
		bool drawing;
	};
}