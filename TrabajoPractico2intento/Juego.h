#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Jugador.h"
#include "Enemigo.h"
#include "Inocente.h"

using namespace sf;

class Juego {

private:

	//variables ventana
	RenderWindow* ventana1;

	//variables para el fondo
	Texture* textura1;
	Sprite* fondo;
	
	Texture* textura2;
	Sprite* menuFondo;

	Texture* textura3;
	Sprite* fondo_danio;

	//variables para el menu e interfaz
	Font* font;
	Text* menu;
	Text* vidasText;
	Text* puntajeText;
	Text* textGameOver;
	Text* volverMenu;
	Text* puntajeGameOver;

	//un booleano para determinar cuándo se está jugando y cuándo está en el menu
	bool start;

	//el reloj para el spawn
	Clock _clock;
	Clock _clock2;
	float tiempoApagado;
	float tiempoVisible;

	//booleando para gestionar la aparicion de enemigos e inocentes
	bool _EnemVisibles;
	bool _InocVisibles;
	//atributos para las posiciones de las apariciones
	int pos1;
	int pos2;

	//jugador
	Jugador* jugador;
	//enemigo con arreglo para ajustar posiciones
	Enemigos* enemigos[5];
	//lo mismo con inocente
	Inocente* inocentes[5];

	//atributos para vidas y puntos
	int vidas;
	int ptos;


public:
	//constructor de juego
	Juego(int ancho, int alto, std::string titulo);

	//método para iniciar el juego desde un menú
	void ejecutar();
	//métodos de bucle, dibujo, actualizar y procesar eventos
	void gameLoop();
	void dibujar();
	void actualizar();
	void procesar_eventos();
	// método para gestionar el disparo del mouse
	void disparar();
	
	//metodo para la aparición de enemigos e inocente
	void spawn();
	
	//método de gameover para cuando se acaben las vidas
	void recibirDanio();


	//destructor de juego
	~Juego();

};

