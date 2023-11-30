#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Jugador.h"

using namespace sf;

class Juego {

private:

	//variables ventana
	RenderWindow* ventana1;

	//variables para el fondo
	Texture* textura1;
	Sprite* fondo;

	//variables para el menu de inicio
	Font* font;
	Text* menu;

	//un booleano para determinar cu�ndo se est� jugando y cu�ndo est� en el menu
	bool start;

	//variable jugador
	Jugador* jugador;

	

public:
	//constructor de juego
	Juego(int ancho, int alto, std::string titulo);

	//m�todo para iniciar el juego desde un men�
	void ejecutar();
	//m�todos de bucle, dibujo, actualizar y procesar eventos
	void gameLoop();
	void dibujar();
	void actualizar();
	void procesar_eventos();
	// m�todo para gestionar el disparo del mouse
	void disparar();
	//m�todo de gameover para cuando se acaben las vidas
	void gameOver();


	//destructor de juego
	~Juego();

};
