#pragma once
#include <iostream>
#define gL_log(x) std::cout << x << std::endl

static void showV2f(sf::Vector2f a) {
	std::cout << "x: " << a.x << ", y: " << a.y << std::endl;
}

static std::string getV2fStr(sf::Vector2f a) {
	return std::string("x: " + std::to_string(a.x) + ", y: " + std::to_string(a.y));
}