#include "GUI.h"

#define defaultGuiColor sf::Color(40, 40, 40, 180)

namespace GUI {
	// button class
	Button::Button(
		sf::Vector2f pos, sf::Vector2f size, sf::Text* text,
		sf::Color color
	)
	{
		this->color = color;
		this->alpha = 180.f;
		// shape
		{
			this->shape = new sf::RectangleShape(size);
			this->shape->setFillColor(color);
			this->shape->setPosition(pos);
		}

		// text
		{
			this->text = new sf::Text(*text);
			float textXpos = pos.x + ( (size.x - this->text->getGlobalBounds().width) / 2.f );
			float textYpos = pos.y + ( (size.y - this->text->getGlobalBounds().height) / 2.f );

			this->text->setPosition(sf::Vector2f(textXpos, textYpos));
		}
	}

	Button::~Button() {
		delete this->shape;
		this->shape = NULL;

		delete this->text;
		this->text = NULL;
	}

	void Button::Draw(sf::RenderTarget* target) {
		target->draw(*shape);
		target->draw(*text);
	}

	void Button::Update(float deltaTime) {
		// alpha 180 - 240
		if (this->shape->getGlobalBounds().contains(
			sf::Vector2f(sf::Mouse::getPosition()))) {
			
			if (this->alpha < 240) {
				this->alpha += deltaTime * 60;
			}

		}
		else {

			if (this->alpha > 180) {
				this->alpha -= deltaTime * 60;
			}

		}

		this->color.a = (uint8_t)alpha;
		log(alpha);
		this->shape->setFillColor(color);
	}

	void Button::EventUpdate(sf::Event ev) {
		if (ev.type == sf::Event::MouseButtonPressed &&
			ev.mouseButton.button == sf::Mouse::Button::Left) {
			if (this->shape->getGlobalBounds().contains(
				sf::Vector2f(sf::Mouse::getPosition()))) {
				this->event = Event::Clicked;
			}
		}
	}

	Event Button::getEvent() {
		Event ev = this->event;
		this->event = Event::None;
		return ev;
	}

	ElementType Button::getType() {
		return ElementType::Button;
	}

}
