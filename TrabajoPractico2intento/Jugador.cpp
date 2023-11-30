#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Jugador.h"

using namespace sf;

Jugador::Jugador()
{

	jugadorText = new Texture;
	jugadorText->loadFromFile("assets/crosshair.png");
	mira = new Sprite;
	mira->setTexture(*jugadorText);

	mira->setOrigin(jugadorText->getSize().x / 2.0f, jugadorText->getSize().y / 2.0f);
	mira->setPosition(400, 300);
	mira->setScale(0.3f, 0.3f);

}

void Jugador::Dibujar(RenderWindow* ventana1) {

	ventana1->draw(*mira);

}

void Jugador::Movimiento(float x, float y) {

	mira->setPosition(x, y);


}

Vector2f Jugador::ObtenerPosicion() {

	return mira->getPosition();

}