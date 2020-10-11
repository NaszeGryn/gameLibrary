#pragma once
#include <SFML/Graphics.hpp>

namespace Collisions {
	//collisions are buggy

	struct CLine {
		sf::Vector2f a;
		sf::Vector2f b;
	};

	enum class ColliderType {
		Poly = 0,
		Circle = 1
	};

	class Collider {
	public:
		virtual std::vector<sf::Vector2f>* getPoly() = 0;
		virtual float getRadius() = 0;
		virtual ColliderType getType() = 0;
		virtual sf::Vector2f getPos() = 0;
	};

	class Poly : public Collider {
	public:
		Poly(std::vector<sf::Vector2f>& vectorList) {
			this->Update(vectorList);
		}
		Poly(sf::VertexArray& vectorList) {
			this->Update(vectorList);
		}

		Poly(sf::RectangleShape& shape) {
			this->Update(shape);
		}

		Poly() { ; }

		~Poly() {
			poly.clear();
		}

		void add(sf::Vector2f a) {
			poly.push_back(a);
		}

		void Update(sf::RectangleShape& shape) {
			poly.clear();
			poly.resize(4);
			sf::Vector2f size(shape.getGlobalBounds().width, shape.getGlobalBounds().height);
			sf::Vector2f origin = shape.getOrigin();
			poly.push_back(shape.getPosition() - origin);
			poly.push_back((shape.getPosition() - origin) + sf::Vector2f(size.x, 0.f));
			poly.push_back((shape.getPosition() - origin) + size);
			poly.push_back((shape.getPosition() - origin) + sf::Vector2f(0.f, size.y));
		}

		void Update(sf::VertexArray& vectorList) {
			poly.clear();
			for (int i = 0; i < vectorList.getVertexCount(); i++) {
				poly.push_back(vectorList[i].position);
			}
		}

		void Update(std::vector<sf::Vector2f>& vectorList) {
			poly = vectorList;
		}

		std::vector<sf::Vector2f>* getPoly() {
			return &poly;
		}

		float getRadius() {
			return 0.f;
		}
		sf::Vector2f getPos() {
			return sf::Vector2f();
		}

		ColliderType getType() {
			return ColliderType::Poly;
		}

	private:
		std::vector<sf::Vector2f> poly;
	};

	class Circle : public Collider {
	public:
		// CENTERED CIRCLE
		Circle(float radius, sf::Vector2f pos) {
			this->radius = radius;
			this->pos = pos;

			this->createPoly();
		}

		// CENTERED CIRCLE
		Circle(sf::CircleShape* shape) {
			this->Update(shape);
		}

		Circle() { this->radius = 0.f; this->pos = sf::Vector2f(0.f, 0.f);
			this->createPoly();
		}

		~Circle() {
			poly.clear();
		}

		void Update(sf::CircleShape* shape) {
			this->radius = shape->getRadius();
			this->pos = shape->getPosition();

			this->createPoly();
		}

		std::vector<sf::Vector2f>* getPoly() {
			return &poly;
		}

		float getRadius() {
			return radius;
		}
		sf::Vector2f getPos() {
			return pos;
		}

		ColliderType getType() {
			return ColliderType::Circle;
		}

	private:
		void createPoly() {
			poly.clear();
			poly.resize(4);
			poly.push_back(pos - sf::Vector2f(radius, radius));
			poly.push_back(pos - sf::Vector2f(-radius, radius));
			poly.push_back(pos - sf::Vector2f(radius, -radius));
			poly.push_back(pos - sf::Vector2f(-radius, -radius));
		}

		std::vector<sf::Vector2f> poly;

		float radius;
		sf::Vector2f pos;
	};


	bool collide(Collider* a, Collider* b) {

		if (a->getType() == ColliderType::Circle &&
			b->getType() == ColliderType::Circle) {

			return sqrt(pow((a->getPos() - b->getPos()).x, 2) + pow((a->getPos() - b->getPos()).y, 2))
				< a->getRadius() + b->getRadius();

		}

		else {
			Collider* co1 = a;
			Collider* co2 = b;

			for (int i = 0; i < 2; i++) {
				float xSum = 0.f;
				float ySum = 0.f;

				for (int x = 0; x < co1->getPoly()->size(); x++) {
					xSum += ((*co1->getPoly()).at(x).x);
					ySum += ((*co1->getPoly()).at(x).y);
				}

				sf::Vector2f center(
					xSum / (float)co1->getPoly()->size(),
					ySum / (float)co1->getPoly()->size());

				sf::Vector2f l_start = center;
				for (int i = 0; i < co1->getPoly()->size(); i++) {
					sf::Vector2f l_end = (*co1->getPoly())[i];
					//std::cout << "L1 end: x: " << l_end.x << ", y: " << l_end.y << std::endl;
					for (int j = 0; j < co2->getPoly()->size(); j++) {
						sf::Vector2f l2_start = (*co2->getPoly())[j];
						sf::Vector2f l2_end = (*co2->getPoly())[(j + 1) % (co2->getPoly()->size() - 1)];

						//std::cout << "L2 Start: x: " << l2_start.x << ", y: " << l2_start.y << std::endl;
						//std::cout << "L2 end: x: " << l2_end.x << ", y: " << l2_end.y << std::endl;

						
						// line line intersection
						float a1 = (l2_end.x - l2_start.x) * (l_start.y - l_end.y) -
							(l_start.x - l_end.x) * (l2_end.y - l2_start.y);

						if (a1 == 0.f) {
							a1 = 1;
						}

						float b1 = ((l2_start.y - l2_end.y) * (l_start.x - l2_start.x)
							+ (l2_end.x - l2_start.x) * (l_start.y - l2_start.y)) / a1;


						float c1 = ((l_start.y - l_end.y) * (l_start.x - l2_start.x)
							+ (l_end.x - l_start.x) * (l_start.y - l2_start.y)) / a1;


						//std::cout << i << " : " << j << ":: A1 " << a1 << " - B1 " << b1 << " - C1 " << c1 << std::endl;

						if (b1 >= 0.0f && b1 < 1.0f && c1 >= 0.0f && c1 < 1.0f) {
							return true;
						}

					}

				}

				co1 = b;
				co2 = a;

			}
		}
		return false;
	}
}




