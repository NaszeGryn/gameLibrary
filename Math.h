#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#define gL_MATH_NEWSEED() srand(int(time(NULL) ) )
#define gL_MATH_PI 3.1415926535897932384626433
#define gL_MATH_RADIAN 180/MATH_PI


#define gL_V2FZERO sf::Vector2f(0.f, 0.f)
#define gL_V2IZERO sf::Vector2i(0, 0)
#define gL_V2UZERO sf::Vector2u(0U, 0U)


namespace Math {
	// Returns distance
	static float dist(sf::Vector2f a, sf::Vector2f b) {
		return sqrt( pow((a - b).x, 2) + pow((a - b).y, 2) );
	}

	// Returns normalized vector
	static sf::Vector2f normVec(sf::Vector2f a, sf::Vector2f b) {
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

	static float getTriangleArea(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
		return abs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x*(a.y - b.y)) / 2.f;

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
		return float(randomI(a, b-1)) + (float)rand() / (float)RAND_MAX;
	}

	// returns random Vector2i
	static sf::Vector2f randomVecI(int xmin, int xmax, int ymin, int ymax) {
		return sf::Vector2f(float(randomI(xmin, xmax)), float(randomI(ymin, ymax)));
	}

	// returns random Vector2f
	static sf::Vector2f randomVecF(int xmin, int xmax, int ymin, int ymax) {
		return sf::Vector2f(float(randomF(xmin, xmax)), float(randomF(ymin, ymax)));
	}

	static char getRandomChar() {
		int f = randomI(0, 3);
		switch (f) {
		// numbers
		case 0:
			return randomI(0x30, 0x3A);
			break;
		//lower case
		case 1:
			return randomI(0x61, 0x7B);
			break;
		//upper case
		case 2:
			return randomI(0x41, 0x5B);
			break;
		}
		return NULL;
	}

	static std::string getRandomString(uint32_t length) {
		std::string s = "";

		for (int i = 0; i < length; i++)
			s += getRandomChar();

		return s;
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
		angle *= 3.14159f / 180.f;
		return sf::Vector2f(point.x * cos(angle) - point.y * sin(angle),
							point.x * sin(angle) + point.y * cos(angle));
	}

	//returns avg float
	static float averageF(std::vector<float>* list) {
		float sum = 0.f;
		for (unsigned i = 0; i < list->size(); i++) {
			sum += (*list)[i];
		}
		return sum / (float)list->size();
	}

	//returns avg int
	static float averageI(std::vector<int>* list) {
		int sum = 0;
		for (unsigned i = 0; i < list->size(); i++) {
			sum += (*list)[i];
		}
		return (float)sum / (float)list->size();
	}

	//returns avg unsigned int
	static float averageU(std::vector<unsigned int> list) {
		int sum = 0;
		for (unsigned i = 0; i < list.size(); i++) {
			sum += list[i];
		}
		return (float)sum / (float)list.size();
	}

	static sf::Color strHexToColor(const std::string& hexNum) {
		if (hexNum.length() == 6) {
			return sf::Color(
				(uint8_t)strtol(hexNum.substr(0, 2).c_str(), NULL, 16),
				(uint8_t)strtol(hexNum.substr(2, 2).c_str(), NULL, 16),
				(uint8_t)strtol(hexNum.substr(4, 2).c_str(), NULL, 16)
			);
		}
		return sf::Color();
	}

	static sf::Vector2f strToVec2f(const std::string& line) {
		std::string v1 = "";

		std::string v2 = "";
		if (line.length() > 0) {
			// finding '=' in line
			if (line.find(',') < line.length()) {
				int eqPos = strcspn(line.c_str(), ",");
				v1 = line.substr(0, eqPos);
				v2 = line.substr(eqPos + 1, line.size() - (eqPos + 1));
			}
			else {
				v1 = line;
			}
		}

		return sf::Vector2f(atof(v1.c_str()), atof(v2.c_str()));
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

		double deltaTime;

	private:
		sf::Clock* clock;
	};

	class ColorF {
	public:
		ColorF(float r = 0.f, float g = 0.f, float b = 0.f, float a = 255.f) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
			this->check();
		}

		ColorF(sf::Color color) {
			this->r = color.r;
			this->g = color.g;
			this->b = color.b;
			this->a = color.a;
			this->check();
		}



		void check() {
			//r
			check_One(r);
			//g
			check_One(g);
			//b
			check_One(b);
			//a
			check_One(a);
		}

		sf::Color getColor() {
			this->check();

			return sf::Color((uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a);
		}

		void add(ColorF x) {
			this->r += x.r;
			this->g += x.g;
			this->b += x.b;
			this->a += x.a;
			this->check();
		}

		void subtract(ColorF x) {
			this->r -= x.r;
			this->g -= x.g;
			this->b -= x.b;
			this->a -= x.a;
			this->check();
		}

		void multiply(float x) {
			this->r *= x;
			this->g *= x;
			this->b *= x;
			this->a *= x;
			this->check();
		}

		float r;
		float g;
		float b;
		float a;

	private:
		void check_One(float& x) {
			if (x > 255.f)
				x = 255.f;
			else if (x < 0.f)
				x = 0.f;
		}
	
	};
}

namespace Logic {
	static bool XOR(bool a, bool b) {
		return (a || b) && !(a && b);
	}
	static bool XNOR(bool a, bool b) {
		return !((a || b) && !(a && b));
	}
}