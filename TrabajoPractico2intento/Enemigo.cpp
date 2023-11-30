#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Enemigo.h"

using namespace sf;
using namespace std;

Enemigos::Enemigos() {


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

