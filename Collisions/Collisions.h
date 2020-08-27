#pragma once
#include <SFML/Graphics.hpp>

namespace Collisions {
	enum class ColliderType {
		Box = 0,
		Circle = 1
	};

	class Collider {
	public:
		virtual ColliderType getType() = 0;
		virtual sf::IntRect getRect() = 0;
		virtual float getRadius() = 0;
		virtual sf::Vector2f getPos() = 0;
	};

	// Box collider
	class BoxCollider : public Collider {
	public:
		BoxCollider(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f origin = sf::Vector2f(0.f, 0.f)) {
			this->UpdateCollider(pos, size, origin);
		}

		BoxCollider(sf::RectangleShape shape) {
			this->UpdateCollider(shape);
		}

		void UpdateCollider(sf::RectangleShape shape) {
			rect.left = (int)shape.getPosition().x - (int)shape.getOrigin().x;
			rect.top = (int)shape.getPosition().y - (int)shape.getOrigin().y;

			rect.width = (int)shape.getSize().x;
			rect.height = (int)shape.getSize().y;
		}

		void UpdateCollider(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f origin = sf::Vector2f(0.f, 0.f)) {
			rect.left = (int)pos.x;
			rect.top = (int)pos.y;

			rect.width = (int)size.x;
			rect.height = (int)size.y;
		}

		// virtual functions

		ColliderType getType() override {
			return ColliderType::Box;
		}

		sf::IntRect getRect() override {
			return rect;
		}

		float getRadius() override {
			return 0.f;
		}

		sf::Vector2f getPos() override {
			return sf::Vector2f(rect.left, rect.top);
		}

		sf::IntRect rect;

	};

	// only works when origin is in the circle's center (centered if origin is at (rad, rad)
	class CircleCollider : public Collider {
	public:
		CircleCollider(sf::Vector2f pos, float size, bool centered) {
			this->centered = centered;
			this->UpdateCollider(pos, size);
		}

		CircleCollider(sf::CircleShape shape, bool centered) {
			this->centered = centered;
			this->UpdateCollider(shape);
		}

		void UpdateCollider(sf::Vector2f pos, float size) {
			this->pos = pos;
			if (!centered) {
				this->pos += sf::Vector2f(size, size);
			}
			this->radius = size;
		}
		void UpdateCollider(sf::CircleShape shape) {
			this->radius = shape.getRadius();
			this->pos = shape.getPosition();
			if (!centered) {
				this->pos = sf::Vector2f(this->radius, this->radius);
			}
		}

		// virtual functions

		ColliderType getType() override {
			return ColliderType::Circle;
		}
		sf::IntRect getRect() override {
			sf::IntRect rectangle(
				(int)pos.x, (int)pos.y,
				(int)radius * 2, (int)radius * 2
			);

			if (centered) {
				rectangle.left -= (int)radius;
				rectangle.top -= (int)radius;
			}

			return rectangle;
		}

		float getRadius() override {
			return radius;
		}

		sf::Vector2f getPos() override {
			return pos;
		}

		float radius;
		sf::Vector2f pos;
		bool centered;
	};

	/* collisions */

	static bool singleCollider(Collider* col1, Collider* col2) {
		if (col1->getType() == ColliderType::Box) {
			return col1->getRect().intersects(col2->getRect());
		}
		else {
			if (col2->getType() == ColliderType::Box) {
				return col1->getRect().intersects(col2->getRect());
			}
		}

		return sqrt(pow((col1->getPos() - col2->getPos()).x, 2) + pow((col1->getPos() - col2->getPos()).y, 2)) < col1->getRadius() + col2->getRadius();
	}

	static bool listCollider(Collider* col1, std::vector<Collider*>* col) {
		for (int i = 0; i < col->size(); i++) {
			if (singleCollider(col1, col->at(i))) {
				return true;
			}
		}
		return false;
	}
}




