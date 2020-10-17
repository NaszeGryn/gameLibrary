#include "GUI.h"

namespace GUI {
	BSBox::BSBox(sf::Vector2f pos, float size, sf::Color color, sf::Color TextColor,
		std::vector<std::string>& strings, sf::Font* font, int charsize, int def_Val, const std::string& ID) {

		this->strings = strings;
		this->font = font;

		this->value = def_Val;
		this->checkVal();


		this->hover = 0;

		this->minRDv = pos;
		this->maxRDv = pos + sf::Vector2f(size, size/4.f);

		{
			// arrow width = 1/10 size
			// height = 1/4 size
			middleText.setCharacterSize(charsize);
			middleText.setFillColor(TextColor);
			middleText.setPosition(pos + sf::Vector2f(size/10.f + 2.f, 0.f));
			middleText.setFont(*this->font);
			middleText.setString(strings[def_Val]);
		}
		{
			pointers.push_back(sf::VertexArray(sf::PrimitiveType::TriangleStrip));

			//triangle 1
			tr1.push_back(pos + sf::Vector2f(size / 10.f, 0.f));
			tr1.push_back(pos + sf::Vector2f(size / 10.f, size / 4.f));
			tr1.push_back(pos + sf::Vector2f(0.f, size / 8.f));

			for (int i = 0; i < tr1.size(); i++) {
				pointers[0].append(sf::Vertex(tr1[i], color));
			}

			pointers.push_back(sf::VertexArray(sf::PrimitiveType::TriangleStrip));

			// triangle 2
			tr2.push_back(pos + sf::Vector2f(size - size / 10.f, 0.f));
			tr2.push_back(pos + sf::Vector2f(size - size / 10.f, size / 4.f));
			tr2.push_back(pos + sf::Vector2f(size, size / 8.f));

			for (int i = 0; i < tr2.size(); i++) {
				pointers[1].append(sf::Vertex(tr2[i], color));
			}
		}
	}


	void BSBox::Draw(sf::RenderTarget* window) {
		if (value != 0)
			window->draw(pointers[0]);
			
		if (value < strings.size() - 1)
			window->draw(pointers[1]);

		window->draw(middleText);
	}

	void BSBox::Update(float deltaTime, sf::RenderWindow* window) {
		if (hoverTriangle1(sf::Vector2f(sf::Mouse::getPosition(*window)) ))
			hover = 1;
		else if (hoverTriangle2(sf::Vector2f(sf::Mouse::getPosition(*window)) ))
			hover = 2;
		else
			hover = 0;
	}

	void BSBox::EventUpdate(sf::Event event) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Button::Left) {
				if (hover == 1) {
					value--;
				}
				else if (hover == 2) {
					value++;
				}

				checkVal();

				this->middleText.setString(strings[value]);
			}
		}
	}

	bool BSBox::hoverTriangle1(sf::Vector2f mouse) {
		float trS = (tr1[0].x * (tr1[1].y - tr1[2].y) + tr1[1].x * (tr1[2].y - tr1[0].y)
			+ tr1[2].x * (tr1[0].y - tr1[1].y)) / 2.f;

		// A B mouse
		float tr1s = abs(tr1[0].x * (tr1[1].y - mouse.y) + tr1[1].x * (mouse.y - tr1[0].y)
			+ mouse.x * (tr1[0].y - tr1[1].y)) / 2.f;

		// B C mouse
		float tr2s = abs(mouse.x * (tr1[1].y - tr1[2].y) + tr1[1].x * (tr1[2].y - mouse.y)
			+ tr1[2].x * (mouse.y - tr1[1].y)) / 2.f;

		// A C mouse
		float tr3s = abs(tr1[0].x * (mouse.y - tr1[2].y) + mouse.x * (tr1[2].y - tr1[0].y)
			+ tr1[2].x * (tr1[0].y - mouse.y)) / 2.f;


		return trS == (tr1s + tr2s + tr3s);
	}

	bool BSBox::hoverTriangle2(sf::Vector2f mouse) {
		float trS = (tr2[0].x * (tr2[1].y - tr2[2].y) + tr2[1].x * (tr2[2].y - tr2[0].y)
			+ tr2[2].x * (tr2[0].y - tr2[1].y)) / 2.f;



		// A B mouse
		float tr1s = (tr2[0].x * (tr2[1].y - mouse.y) + tr2[1].x * (mouse.y - tr2[0].y)
			+ mouse.x * (tr2[0].y - tr2[1].y)) / 2.f;

		// B C mouse
		float tr2s = (mouse.x * (tr2[1].y - tr2[2].y) + tr2[1].x * (tr2[2].y - mouse.y)
			+ tr2[2].x * (mouse.y - tr2[1].y)) / 2.f;

		// A C mouse
		float tr3s = (tr2[0].x * (mouse.y - tr2[2].y) + mouse.x * (tr2[2].y - tr2[0].y)
			+ tr2[2].x * (tr2[0].y - mouse.y)) / 2.f;


		return trS == (tr1s + tr2s + tr3s);
	}
}