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
	//un método para obtener cada sprite en la clase Guego
	Sprite* getSpriteArriba() { return enemSpriteArriba; }
	Sprite* getSpriteAbajo() { return enemSpriteAbajo; }
	Sprite* getSpritePuerta() { return enemSpritePuerta; }

	//un booleano para verificar la colisión
	bool Colision(float x, float y);

	//metodo para que no arrastre la posición (0,0) al iniciarlas en el constructor Juego
	void setPositions(float x, float y);
};
