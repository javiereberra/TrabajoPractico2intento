#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Enemigo.h"

using namespace sf;
using namespace std;

Enemigos::Enemigos() {

	//establecer texturas y sprites
	enemVentanaArriba = new Texture;
	enemVentanaArriba->loadFromFile("assets/ventana_arriba_enemigo.png");

	enemVentanaAbajo = new Texture;
	enemVentanaAbajo->loadFromFile("assets/ventana_abajo_enemigo.png");

	enemPuerta = new Texture;
	enemPuerta->loadFromFile("assets/puerta_enemigo.png");


	enemSpriteArriba = new Sprite(*enemVentanaArriba);
	enemSpriteAbajo = new Sprite(*enemVentanaAbajo);
	enemSpritePuerta = new Sprite(*enemPuerta);

	

	
}
//para obtener los bounds de cada sprite en la clase Juego
bool Enemigos::Colision(float x, float y) {

	
		FloatRect bounds1 = enemSpriteArriba->getGlobalBounds();
		FloatRect bounds2 = enemSpriteAbajo->getGlobalBounds();
		FloatRect bounds3 = enemSpritePuerta->getGlobalBounds();


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
	