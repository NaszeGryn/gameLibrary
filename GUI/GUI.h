#pragma once
#include <SFML/Graphics.hpp>
#include "UI.h"

#define defaultGuiColor sf::Color(40, 40, 40, 180)

namespace GUI {
	// gui elements events
	enum class Event {
		None = 0,
		// button event
		Clicked = 1

		// other
	};

	// element types
	enum class ElementType {
		Button = 0,
		TextBox = 1
	};

	// virtual class for GUI elements
	class GUIElement {
	public:
		virtual void Draw(sf::RenderTarget* window) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void EventUpdate(sf::Event event) = 0;
		virtual Event getEvent() = 0;
		virtual ElementType getType() = 0;
	};

	// button class
	class Button : public GUIElement {
	public:
		Button(
			sf::Vector2f pos, sf::Vector2f size,
			sf::Text* text, sf::Color color);
		~Button();

		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime);
		void EventUpdate(sf::Event event);
		Event getEvent();
		ElementType getType();

	private:
		sf::RectangleShape* shape;
		sf::Text* text;
		sf::Color color;

	private:
		Event event;
		float alpha;
	};


}