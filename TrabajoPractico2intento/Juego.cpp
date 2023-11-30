#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Juego.h"
#include <iostream> 

using namespace sf;
using namespace std;

Juego::Juego(int ancho, int alto, std::string titulo) {
	
	//Ventana
	ventana1 = new RenderWindow(VideoMode(ancho, alto), titulo);
	
	//fuente y texto para el menu
	font = new Font;
	menu = new Text;
	font->loadFromFile("assets/arial.ttf");
	menu->setFont(*font);
	menu->setString("Presiona 'S' para comenzar");
	menu->setCharacterSize(24);
	menu->setPosition(250, 300);
	
	//Textura y Sprite de fondo
	textura1 = new Texture;
	fondo = new Sprite;
	textura1->loadFromFile("assets/fondo_base_cerrado.jpg");
	fondo->setTexture(*textura1);

	//Inicializar el jugador
	jugador = new Jugador();

	//para que siempre inicie el menú
	start = false;

}

//Método que gestiona si se está en el menú o jugando.
void Juego::ejecutar() {

	while (ventana1->isOpen()) {
		Event evento;
		while (ventana1->pollEvent(evento)) {
			if (evento.type == Event::Closed)
				ventana1->close();

			if (evento.type == Event::KeyPressed) {
				if (evento.key.code == Keyboard::Key::S && !start) {

					start = true;
				}
			}
		}

		ventana1->clear(Color::Black);

		if (start) {

			gameLoop();

		}
		else {


			ventana1->draw(*menu);
		}

		ventana1->display();
	}
}

void Juego::gameLoop() {

	while (ventana1->isOpen()) {

		procesar_eventos();
		actualizar();
		dibujar();


	}
}

void Juego::procesar_eventos() {
	Event evento1;
	while (ventana1->pollEvent(evento1)) {
		switch (evento1.type) {
		case Event::Closed:
			ventana1->close();
			break;
		
		}
	}
}

void Juego::actualizar() {

	Vector2i mousePos = Mouse::getPosition(*ventana1);
	jugador->Movimiento(mousePos.x, mousePos.y);

	

}

void Juego::disparar() {

	Vector2f playerPos = jugador->ObtenerPosicion();



}

void Juego::dibujar() {

	ventana1->clear();

	ventana1->draw(*fondo);
	

	jugador->Dibujar(ventana1);

	ventana1->display();


}

Juego::~Juego() {


	delete jugador;
	delete ventana1;


}