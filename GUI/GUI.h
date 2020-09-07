#pragma once
#include <SFML/Graphics.hpp>
#include "UI.h"

#define gL_defaultGuiColor sf::Color(40, 40, 40, 180)

namespace GUI {
	// gui elements events
	enum class Event {
		None = 0,
		// button event
		Clicked = 1,

		// other
		NewVal = 2
	};

	// element types
	enum class ElementType {
		null = 0,
		Button = 1,
		TextureButton = 2,
		TextBox = 3,
		TextureBox = 4,
		Slider = 5
	};

	// virtual class for GUI elements
	class GUIElement {
	public:
		virtual void Draw(sf::RenderTarget* window) = 0;
		virtual void Update(float deltaTime, sf::RenderWindow* window) = 0;
		virtual void EventUpdate(sf::Event event) = 0;
		virtual Event getEvent() = 0;
		virtual ElementType getType() = 0;
		virtual int getValue() = 0;

		virtual sf::Vector2f maxRD() = 0;
		virtual sf::Vector2f minRD() = 0;  
		virtual std::string getID() = 0;
	};

	// button class
	class Button : public GUIElement {
	public:
		Button(
			sf::Vector2f pos, sf::Vector2f size,
			sf::Text* text, sf::Color color, std::string ID = "");
		~Button();

		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent();
		ElementType getType();

		int getValue() { return 0; }

		sf::Vector2f maxRD();
		sf::Vector2f minRD();

		std::string getID() { return this->ID; }

	private:
		sf::RectangleShape* shape;
		sf::Text* text;
		sf::Color color;

	private:
		Event event;
		float alpha;
		std::string ID;
	};

	// button class
	class TextureButton : public GUIElement {
	public:
		TextureButton(sf::Vector2f pos, sf::Texture& texture, std::string ID = "");
		TextureButton(sf::Vector2f pos, sf::Texture& texture, sf::IntRect rect, std::string ID = "");
		~TextureButton();
		
		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent();
		ElementType getType();

		int getValue() { return 0; }

		sf::Vector2f maxRD();
		sf::Vector2f minRD();

		std::string getID() { return this->ID; }

	private:
		sf::Sprite* sprite;
	private:
		Event event;
		std::string ID;
	};
	

	// textbox class
	class TextBox : public GUIElement {
	public:
		TextBox(
			sf::Vector2f pos, sf::Vector2f size,
			sf::Text* text, sf::Color color, std::string ID = "");
		~TextBox();

		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent();
		ElementType getType();

		int getValue() { return 0; }

		sf::Vector2f maxRD();
		sf::Vector2f minRD();

		std::string getID() { return this->ID; }

	private:
		sf::RectangleShape* shape;
		sf::Text* text;

		std::string ID;
	};

	// texturebox class
	class TextureBox : public GUIElement {
	public:
		TextureBox(
			sf::Vector2f pos,
			sf::Texture* texture, std::string ID = "");

		TextureBox(
			sf::Vector2f pos,
			sf::Texture* texture,
			sf::IntRect rect, std::string ID = "");

		~TextureBox();

		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent();
		ElementType getType();

		int getValue() { return 0; }

		sf::Vector2f maxRD();
		sf::Vector2f minRD();

		std::string getID() { return this->ID; }

	private:
		sf::Sprite* sprite;

		std::string ID;

	};

	// Slider
	class Slider : public GUIElement {
	public:
		Slider(
			sf::Vector2f pos,
			float size,
			float length,
			sf::Color color,
			int starting_Val = 50,
			std::string ID = ""
			);

		~Slider();

		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent();
		ElementType getType();

		int getValue() { return this->value; }

		sf::Vector2f maxRD();
		sf::Vector2f minRD();

		std::string getID() { return this->ID; }
	private:
		std::vector<sf::RectangleShape> list;
		sf::IntRect background;

	private:
		sf::Vector2f pos;
		float size;
		float length;
		int value;

		Event event;
		std::string ID;
	};


	// GUI handler
	class GUIHandler {
	public:
		GUIHandler(sf::Vector2f pos, int margin, sf::Color color);
		~GUIHandler();

		void add_GUI_ELEMENT(GUIElement* element);
		std::vector<GUIElement*>* getArray();

		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);

		size_t getArraySize();
		Event getEvent(int index);
		ElementType getElementType(int index);
		int getValue(int index);

		Event getEvent(std::string ID);
		ElementType getElementType(std::string ID);
		int getValue(std::string ID);

		int getIndex(std::string ID);
		std::string getID(int index);

	private:
		sf::RectangleShape shape;
		std::vector<GUIElement*> elements;

	private:
		int margin;
		sf::Vector2f mRD;
		sf::Vector2f miRD;
	};
}