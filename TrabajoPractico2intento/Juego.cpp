#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Juego.h"
#include <iostream> 
#include "Enemigo.h"


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
	enemigos[0] = new Enemigos();
	enemigos[1] = new Enemigos();
	enemigos[2] = new Enemigos();
	enemigos[3] = new Enemigos();
	enemigos[4] = new Enemigos();

	//para que siempre inicie el menú
	start = false;

	//establecer las posiciones de los sprites para que coincidan con el fondo
	enemigos[0]->getSpriteArriba()->setPosition(75.f, 84.f);
	enemigos[1]->getSpriteArriba()->setPosition(525.f, 84.f);
	enemigos[2]->getSpriteAbajo()->setPosition(50.f, 334.f);
	enemigos[3]->getSpritePuerta()->setPosition(337.f, 328.f);
	enemigos[4]->getSpriteAbajo()->setPosition(550.f, 334.f);

	//tiempos para gestionar las apariciones de enemigos e inocentes en pantalla
	tiempoApagado = 1.2f;
	tiempoVisible = 2.0f;

	//establecer que comience el juego sin enemigos
	_visibles = false;

	//establecer vidas y puntaje
	vidas = 20;
	ptos = 0;

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
// loop que procesa eventos actualiza y dibuja
void Juego::gameLoop() {

	while (ventana1->isOpen()) {

		procesar_eventos();
		actualizar();
		dibujar();


	}
}

//Eventos para poder cerrar ventana y procesar el disparo del jugador
void Juego::procesar_eventos() {
	Event evento1;
	while (ventana1->pollEvent(evento1)) {
		switch (evento1.type) {
		case Event::Closed:
			ventana1->close();
			break;
		case Event::MouseButtonPressed:
			if (evento1.mouseButton.button == Mouse::Button::Left)
			disparar();
			break;
		}
	}
}

//Método para gestionar las apariciones en pantalla de enemigos y civiles
void Juego::spawn() {

	//cuando no hay enemigos visibles//
	if (!_visibles) {
		//si el tiempo transcurrido es mayor al tiempo apagado//
		if (_clock.getElapsedTime().asSeconds() > tiempoApagado) {
			//reiniciar reloj//
			_clock.restart();
			//VISIBLES es true//
			_visibles = true;
			//establecer posicion de ENEMIGOS
			pos1 = rand() % 5;
		}
		//AGREGAR INOCENTE AQUI
		//posicion1 = a un rand 1 a 5, 6 o 7 para enemigo//
		//posicion2 = un rand de 1 a 5 o 6 para inocente que no sea igual al primer rand//

	}
	//si están visibles
	else {
		{
			//si el tiempo transcurrido es mayor al tiempo visible
			if (_clock.getElapsedTime().asSeconds() > tiempoVisible) {
				//dejan de estar visibles, disparan y restan una vida y se reinicia el reloj
				_visibles = false;
				vidas -= 1;
				cout << vidas;
				_clock.restart();
			}
		}



	}
}

//método actualizar para gestionar la posición del cursor y el método spawn
void Juego::actualizar() {

	Vector2i mousePos = Mouse::getPosition(*ventana1);
	jugador->Movimiento(mousePos.x, mousePos.y);
	spawn();

	

}
//metodo disparar comprobar la colisión y sumar puntos o restar vidas según el caso
void Juego::disparar() {

	Vector2f playerPos = jugador->ObtenerPosicion();
	//si están visibles y si el enemigo correspondiente a la posiciones coincide con las coordenadas del click del mouse
	if (_visibles) {
		if (enemigos[pos1]->Colision(playerPos.x, playerPos.y)) {
			cout << "hit";
			//ELIMINADOS: dejan de estar visible y suman 10 ptos
			_visibles = false;
			ptos += 10;
			cout << ptos;
		}
}
}
//metodo dibujar para la ventana y el enemigo
//se utiliza un switch para ver qué sprite se debe dibujar según la pos1 y si están visibles
void Juego::dibujar() {

	ventana1->clear();

	ventana1->draw(*fondo);

	if (_visibles) {
		switch (pos1) {
		case 0:
			ventana1->draw(*enemigos[0]->getSpriteArriba());
			break;
		case 1:
			ventana1->draw(*enemigos[1]->getSpriteArriba());
			break;
		case 2:
			ventana1->draw(*enemigos[2]->getSpriteAbajo());
			break;
		case 3:
			ventana1->draw(*enemigos[3]->getSpritePuerta());
			break;
		case 4:
			ventana1->draw(*enemigos[4]->getSpriteAbajo());
			break;
		default:
			break;
		}
	}
	
	
	

	jugador->Dibujar(ventana1);

	ventana1->display();


}

Juego::~Juego() {

	delete enemigos;
	delete jugador;
	delete ventana1;


}