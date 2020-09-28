#pragma once
#include "GraphicsClasses.h"
#include "GraphicsFunctions.h"
#include "GraphicsProcessing.h"
#include "Particles.h"

#define rgb(r, g, b) sf::Color(r, g, b)
#define rgba(r, g, b, a) sf::Color(r, g, b, a)
#define gL_fullScreen sf::VideoMode::getDesktopMode()
#define gL_fullScreenSize sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)