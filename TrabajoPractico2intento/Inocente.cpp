#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Inocente.h"

using namespace sf;
using namespace std;

Inocente::Inocente() {

	//establecer texturas y sprites
	inocVentArriba = new Texture;
	inocVentArriba->loadFromFile("assets/civil_arriba.png");

	inocVentanaAbajo = new Texture;
	inocVentanaAbajo->loadFromFile("assets/civil_abajo.png");

	inocPuerta = new Texture;
	inocPuerta->loadFromFile("assets/civil_fullsize.png");


	inocSpriteArriba = new Sprite(*inocVentArriba);
	inocSpriteAbajo = new Sprite(*inocVentanaAbajo);
	inocSpritePuerta = new Sprite(*inocPuerta);




}
//para obtener los bounds de cada sprite en la clase Juego
bool Inocente::Colision(float x, float y) {


	FloatRect bounds1 = inocSpriteArriba->getGlobalBounds();
	FloatRect bounds2 = inocSpriteAbajo->getGlobalBounds();
	FloatRect bounds3 = inocSpritePuerta->getGlobalBounds();


	if (bounds1.contains(x, y)) {
		return true;
	}

	if (bounds2.contains(x, y)) {
		return true;
	}

	if (bounds3.contains(x, y)) {
		return true;
	}

}
//metodo para que no arrastre la posición (0,0) al iniciarlas en el constructor Juego
void Inocente::setPositions(float x, float y) {
	inocSpriteArriba->setPosition(x, y);
	inocSpriteAbajo->setPosition(x, y);
	inocSpritePuerta->setPosition(x, y);
}