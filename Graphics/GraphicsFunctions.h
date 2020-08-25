#pragma once
#include <SFML/Graphics.hpp>


namespace GraphFunc {
	// Draws text on the screen
	static void DrawText(sf::Vector2f pos, std::string textf,
		sf::Font* font, unsigned int fontSize, sf::RenderWindow* window) {

		sf::Text text(textf, *font, fontSize);
		text.setPosition(pos);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(1.f);
		window->draw(text);
	}

	// Returns text
	static sf::Text getText(std::string textf, sf::Font* font,
		unsigned int fontSize, sf::Vector2f pos = sf::Vector2f(0.f, 0.f)) {

		sf::Text text(textf, *font, fontSize);
		text.setPosition(pos);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(1.f);

		return text;
	}

	// Returns Texture 
	static sf::Texture loadHQTexture(std::string location) {
		sf::Texture texture;
		texture.loadFromFile(location);
		texture.setSmooth(true);
		return texture;
	}

	// Creates and saves screenshots
	static void do_ScreenShot(sf::RenderWindow* window, std::string location) {
		std::string string = location + "screenshot_";
		sf::Texture txt;
		txt.create(window->getSize().x, window->getSize().y);
		sf::Image img;
		txt.update(*window);

		time_t t = time(NULL);

		tm time;
		localtime_s(&time, &t);

		string += std::to_string(1900 + time.tm_year) + "_" + std::to_string(time.tm_mday) + "_" +
			std::to_string(time.tm_hour) + "_" + std::to_string(time.tm_min) + "_" + std::to_string(time.tm_sec) + ".png";
	

		img = txt.copyToImage();
		img.saveToFile(string);
	}
}