#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


using namespace sf;

class Inocente {

private:
	//las tres texturas y sprites necesarios para las distintas posiciones
	Texture* inocVentArriba;
	Texture* inocVentanaAbajo;
	Texture* inocPuerta;

	Sprite* inocSpriteArriba;
	Sprite* inocSpriteAbajo;
	Sprite* inocSpritePuerta;

public:
	//constructor
	Inocente();
	//un m�todo para obtener cada sprite en la clase Juego
	Sprite* getSpriteArriba() { return inocSpriteArriba; }
	Sprite* getSpriteAbajo() { return inocSpriteAbajo; }
	Sprite* getSpritePuerta() { return inocSpritePuerta; }

	//un booleano para verificar la colisi�n
	bool Colision(float x, float y);

	//metodo para que no arrastre la posici�n (0,0) al iniciarlas en el constructor Juego
	void setPositions(float x, float y);
};
