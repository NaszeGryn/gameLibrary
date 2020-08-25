#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#define MATH_NEWSEED() srand(int(time(NULL) ) )
#define MATH_PI 3.1415926535897932384626433
#define MATH_RADIAN 180/MATH_PI


#define V2FZERO sf::Vector2f(0.f, 0.f)
#define V2IZERO sf::Vector2i(0, 0)
#define V2UZERO sf::Vector2u(0U, 0U)

namespace Math {
	// Returns distance
	static float dist(sf::Vector2f a, sf::Vector2f b) {
		return sqrt( pow((a - b).x, 2) + pow((a - b).y, 2) );
	}

	// Returns normalized distance
	static sf::Vector2f normDist(sf::Vector2f a, sf::Vector2f b) {
		return (a - b) / dist(a, b);
	}

	// Returns angle
	static float getAngle(sf::Vector2f start, sf::Vector2f nxt) {
		float ab = (start - nxt).y;
		float ac = sqrt(((start - nxt).x * (start - nxt).x) + ((start - nxt).y * (start - nxt).y));

		float angle = float(asin(ab / ac) * (180 / 3.14159f)) - 90.f;

		angle = abs(angle);
		return angle;
	}

	// returns positive angle
	static float positiveAngle(float angle) {
		if (angle < 0) {
			angle = angle + 360.f;
		}
		return angle;
	}

	// returns absolute value of Vector2fs
	static sf::Vector2f v2fAbs(sf::Vector2f a) {
		return sf::Vector2f(abs(a.x), abs(a.y));
	}

	// returns random int
	static int randomI(int a, int b) {
		return (rand() % (a - b) + a);
	}

	// returns random float
	static float randomF(int a, int b) {
		return float(rand() % int(a - b)) + (float)rand() / (float)RAND_MAX;
	}

	// returns random Vector2i
	static sf::Vector2f randomVecI(int xmin, int xmax, int ymin, int ymax) {
		return sf::Vector2f(float(randomI(xmin, xmax)), float(randomI(ymin, ymax)));
	}

	// returns random Vector2f
	static sf::Vector2f randomVecF(int xmin, int xmax, int ymin, int ymax) {
		return sf::Vector2f(float(randomF(xmin, xmax)), float(randomF(ymin, ymax)));
	}

	// returns avg
	static sf::Vector2f avgV2f(sf::Vector2f first, sf::Vector2f second) {
		return sf::Vector2f((first.x + second.x) / 2.f, (first.y + second.y) / 2.f);
	}

	// returns avg
	static sf::Color avgColor(sf::Color a, sf::Color b) {
		return sf::Color((a.r + b.r) / 2, (a.g + b.g) / 2, (a.b + b.b) / 2);
	}

	// rotates point around (0,0)
	static sf::Vector2f rotateArZero(sf::Vector2f point, float angle) {
		angle *= 3.14159 / 180;
		return sf::Vector2f(point.x * cos(angle) - point.y * sin(angle),
							point.x * sin(angle) + point.y * cos(angle));
	}

	//returns avg float
	static float averageF(std::vector<float> list) {
		float sum = 0.f;
		for (unsigned i = 0; i < list.size(); i++) {
			sum += list[i];
		}
		return sum / (float)list.size();
	}

	//returns avg int
	static float averageI(std::vector<int> list) {
		int sum = 0;
		for (unsigned i = 0; i < list.size(); i++) {
			sum += list[i];
		}
		return (float)sum / (float)list.size();
	}

	//returns avg unsigned int
	static float averageU(std::vector<unsigned int> list) {
		int sum = 0;
		for (unsigned i = 0; i < list.size(); i++) {
			sum += list[i];
		}
		return (float)sum / (float)list.size();
	}

	// clock class
	class Clock {
	public:
		Clock() {
			this->clock = new sf::Clock();
			this->deltaTime = 0.f;
		}

		~Clock() {
			delete this->clock;
		}

		void Update() {
			this->deltaTime = clock->restart().asSeconds();
		}

		float deltaTime;

	private:
		sf::Clock* clock;
	};
}