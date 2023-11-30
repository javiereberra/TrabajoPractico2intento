#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


using namespace sf;

class Enemigos {

private:

	Texture* enemVentanaArriba;
	Texture* enemVentanaAbajo;
	Texture* enemPuerta;

	Sprite* enemSpriteArriba;
	Sprite* enemSpriteAbajo;
	Sprite* enemSpritePuerta;

public:

	Enemigos();

	Sprite* getSpriteArriba() { return enemSpriteArriba; }
	Sprite* getSpriteAbajo() { return enemSpriteAbajo; }
	Sprite* getSpritePuerta() { return enemSpritePuerta; }


};
