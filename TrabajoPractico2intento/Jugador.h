#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Jugador {

private:

	Texture* jugadorText;
	Sprite* mira;

public:

	Jugador();

	void Dibujar(RenderWindow* ventana1);

	void Movimiento(float x, float y);

	Vector2f ObtenerPosicion();

};
