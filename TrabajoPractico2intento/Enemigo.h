#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


using namespace sf;

class Enemigos {

private:
	//las tres texturas y sprites necesarios para las distintas posiciones
	Texture* enemVentanaArriba;
	Texture* enemVentanaAbajo;
	Texture* enemPuerta;

	Sprite* enemSpriteArriba;
	Sprite* enemSpriteAbajo;
	Sprite* enemSpritePuerta;

public:
	//constructor
	Enemigos();
	//un m�todo para obtener cada sprite en la clase Guego
	Sprite* getSpriteArriba() { return enemSpriteArriba; }
	Sprite* getSpriteAbajo() { return enemSpriteAbajo; }
	Sprite* getSpritePuerta() { return enemSpritePuerta; }

	//un booleano para verificar la colisi�n
	bool Colision(float x, float y);
};
