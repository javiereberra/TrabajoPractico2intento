#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Juego.h"
#include <iostream> 
#include "Enemigo.h"
#include "Inocente.h"


using namespace sf;
using namespace std;

Juego::Juego(int ancho, int alto, std::string titulo) {
	
	//Ventana
	ventana1 = new RenderWindow(VideoMode(ancho, alto), titulo);
	
	//inicializar variables vida y puntaje
	vidas = 3;
	ptos = 0;

	//fuente y texto para el menu
	font = new Font;
	menu = new Text;
	font->loadFromFile("assets/nintendo-nes-font.ttf");
	menu->setFont(*font);
	menu->setString("PRESIONA 'S' PARA COMENZAR");
	menu->setCharacterSize(20);
	menu->setPosition(115, 400);
		
	//textos puntaje, vidas, Game Over y Puntaje Final
	puntajeText = new Text;
	puntajeText->setFont(*font);
	puntajeText->setCharacterSize(20);
	puntajeText->setString("PUNTAJE: " + to_string(ptos));
	puntajeText->setPosition(500, 10);

	vidasText = new Text;
	vidasText->setFont(*font);
	vidasText->setCharacterSize(20);
	vidasText->setString("VIDAS: " + to_string(vidas));
	vidasText->setPosition(10, 10);

	textGameOver = new Text;
	textGameOver->setFont(*font);
	textGameOver->setCharacterSize(36);
	textGameOver->setString("GAME OVER");
	textGameOver->setPosition(220, 150);

	volverMenu = new Text;
	volverMenu->setFont(*font);
	volverMenu->setCharacterSize(20);
	volverMenu->setString("PRESIONA 'I' PARA VOLVER AL INICIO");
	volverMenu->setPosition(50, 300);

	puntajeGameOver = new Text;
	puntajeGameOver->setFont(*font);
	puntajeGameOver->setCharacterSize(20);
	puntajeGameOver->setPosition(170, 400);
	
	//Textura y Sprite de fondo
	textura1 = new Texture;
	fondo = new Sprite;
	textura1->loadFromFile("assets/fondo_base_cerrado.jpg");
	fondo->setTexture(*textura1);

	//Textura y Sprite de perder una vida
	textura3 = new Texture;
	fondo_danio = new Sprite;
	textura3->loadFromFile("assets/fondo_danio_cerrado.jpg");
	fondo_danio->setTexture(*textura3);

	//Textura de Menu Wild Gunman
	textura2 = new Texture;
	menuFondo = new Sprite;
	textura2->loadFromFile("assets/menu.png");
	menuFondo->setTexture(*textura2);
	menuFondo->setScale(0.5f, 0.5f);
	menuFondo->setPosition(75, 0);

	//Inicializar el jugador
	jugador = new Jugador();

	//Inicializar arreglos para Enemigos e Inocentes
	enemigos[0] = new Enemigos();
	enemigos[1] = new Enemigos();
	enemigos[2] = new Enemigos();
	enemigos[3] = new Enemigos();
	enemigos[4] = new Enemigos();

	inocentes[0] = new Inocente();
	inocentes[1] = new Inocente();
	inocentes[2] = new Inocente();
	inocentes[3] = new Inocente();
	inocentes[4] = new Inocente();

	//para que siempre inicie el menú
	start = false;

	//establecer las posiciones de los sprites para que coincidan con el fondo
	enemigos[0]->setPositions(75.f, 84.f);
	enemigos[1]->setPositions(525.f, 84.f);
	enemigos[2]->setPositions(50.f, 334.f);
	enemigos[3]->setPositions(337.f, 328.f);
	enemigos[4]->setPositions(550.f, 334.f);
		
	inocentes[0]->setPositions(75.f, 84.f);
	inocentes[1]->setPositions(525.f, 84.f);
	inocentes[2]->setPositions(50.f, 334.f);
	inocentes[3]->setPositions(337.f, 328.f);
	inocentes[4]->setPositions(550.f, 334.f);

	//tiempos para gestionar las apariciones de enemigos e inocentes en pantalla
	tiempoApagado = 2.0f;
	tiempoVisible = 1.5f;

	//establecer que comience el juego sin enemigos
	_EnemVisibles = false;
	_InocVisibles = false;

	//se le asigna un valor en el constructor a las posiciones sólo por prolijidad
	pos1 = 0;
	pos2 = 0;
}

//Método que gestiona si se está en el menú o jugando.
void Juego::ejecutar() {

	while (ventana1->isOpen()) {
		Event evento;
		while (ventana1->pollEvent(evento)) {
			if (evento.type == Event::Closed)
				ventana1->close();
			//Presionar "s" para iniciar el gameloop
			if (evento.type == Event::KeyPressed) {
				if (evento.key.code == Keyboard::Key::S && !start) {

					start = true;
					//los relojes se reinician para que no empiecen a correr cuando uno está en el menu
					_clock.restart();
					_clock2.restart();
				}
			}
		}

		ventana1->clear(Color::Black);

		if (start) {
			//iniciar el loop si start es true
			gameLoop();

		}
		else {
			//Menu de fondo si start es false
			ventana1->draw(*menuFondo);
			ventana1->draw(*menu);
		}

		ventana1->display();
	}
}
// loop que procesa eventos actualiza y dibuja
// acá se inicia el juego, gameOver false
void Juego::gameLoop() {

	bool gameOver = false;

	while (ventana1->isOpen() && !gameOver) {

		procesar_eventos();
		actualizar();
		dibujar();
		// si las vidas llegan a 0, gameOver true
		if (vidas <= 0) {
			gameOver = true;

		}
	}
	//Pantalla gameOver con puntuación actualizada
	while (gameOver && ventana1->isOpen()) {
		ventana1->clear();

		ventana1->draw(*textGameOver);
		ventana1->draw(*volverMenu);
		puntajeGameOver->setString("TU PUNTUACION FUE: " + to_string(ptos));
		ventana1->draw(*puntajeGameOver);

		ventana1->display();

		//procesar eventos en GameOver para volver a Inicio
		Event eventoGameOver;
		while (ventana1->pollEvent(eventoGameOver)) {
			if (eventoGameOver.type == Event::Closed) {
				ventana1->close();
			}
			if (eventoGameOver.type == Event::KeyPressed && eventoGameOver.key.code == Keyboard::Key::I) {
				// Regresar al menú principal (start = false) y reiniciar valores
				start = false;
				vidas = 3;
				ptos = 0;
				vidasText->setString("VIDAS: " + to_string(vidas));
				puntajeText->setString("PUNTAJE: " + to_string(ptos));
				gameOver = false;

			}
		}
	}
}


//Eventos para poder cerrar ventana y procesar el disparo del jugador dentro del loop
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
	if (!_EnemVisibles) {
		//si el tiempo transcurrido es mayor al tiempo apagado//
		if (_clock.getElapsedTime().asSeconds() > tiempoApagado) {
			//reiniciar reloj//
			_clock.restart();
			//establecer posicion de ENEMIGOS que no coincida con INOCENTES
			pos1 = rand() % 5;
			while (pos1 == pos2) {
				pos1 = rand() % 5;
			}
			//VISIBLES es true//
			_EnemVisibles = true;
			
		
		}
		
	}
	//si están visibles
	else {
		{
			//si el tiempo transcurrido es mayor al tiempo visible
			if (_clock.getElapsedTime().asSeconds() > tiempoVisible) {
				//dejan de estar visibles, disparan y restan una vida y se reinicia el reloj
				_EnemVisibles = false;
				vidas -= 1;
				vidasText->setString("VIDAS: " + to_string(vidas));
				//metodo de recibir daño
				recibirDanio();
				//reiniciar el reloj
				_clock.restart();
			}
		}
	}


	//cuando no hay inocentes visibles//
	if (!_InocVisibles) {
		//si el tiempo transcurrido es mayor al tiempo apagado//
		if (_clock2.getElapsedTime().asSeconds() > tiempoApagado) {
			//reiniciar reloj//
			_clock2.restart();
			//establacer posicion INOCENTES que no coincida ENEMIGOS
			pos2 = rand() % 5;
			while (pos2 == pos1) {
				pos2 = rand() % 5;
			}
			//visibles es true
			_InocVisibles = true;
			
		}

	}
	else {
		{
			//si el tiempo transcurrido es mayor al tiempo visible
			if (_clock2.getElapsedTime().asSeconds() > tiempoVisible) {
				//dejan de estar visibles, disparan y restan una vida y se reinicia el reloj
				_InocVisibles = false;
				//reinicia el reloj
				_clock2.restart();

			}
		}
	}

}

//método actualizar para gestionar la posición del cursor y el método spawn
void Juego::actualizar() {

	Vector2i mousePos = Mouse::getPosition(*ventana1);
	jugador->Movimiento(mousePos.x, mousePos.y);
	//Método para las apariciones de Enemigos e Inocente
	spawn();

	//Condición para aumentar dificultad al llegar a 15 puntos

	if (ptos >= 15) {

		tiempoApagado = 1.0f;
		tiempoVisible = 0.8f;
	}
	else {
		tiempoApagado = 2.0f;
		tiempoVisible = 1.5f;
	}
	

}
//metodo disparar comprobar la colisión y sumar puntos o restar vidas según el caso
void Juego::disparar() {

	Vector2f playerPos = jugador->ObtenerPosicion();
	//si están visibles y si el enemigo correspondiente a la posiciones coincide con las coordenadas del click del mouse
	if (_EnemVisibles) {
		if (enemigos[pos1]->Colision(playerPos.x, playerPos.y)) {
			//ELIMINADOS: dejan de estar visible y suma 1 pto
			_EnemVisibles = false;
			ptos += 1;
			//hay que actualizar el string para que se refleje en pantalla
			puntajeText->setString("PUNTAJE: " + to_string(ptos));
			
		}
}
	//mismo proceso con Inocentes
	if (_InocVisibles) {
		if (inocentes[pos2]->Colision(playerPos.x, playerPos.y)) {
			//ELIMINADOS: dejan de estar visible y suman 10 ptos
			_InocVisibles = false;
			//agregar el mismo efecto por perder una vida al matar inocente
			recibirDanio();
			vidas -= 1;
			ptos -= 10;
			vidasText->setString("VIDAS: " + to_string(vidas));
			puntajeText->setString("PUNTAJE: " + to_string(ptos));
			
		}
}

}
//método para agregarle un efecto al perder vidas (recibir daño y matar inocentes)
void Juego::recibirDanio() {
	//se dibuja un sprite de fondo 
	ventana1->draw(*fondo_danio);
	ventana1->display();

	// tiempo del fondo visble
	Clock clock;
	while (clock.getElapsedTime().asSeconds() < 0.3) {
		
	}

}


//metodo dibujar para la ventana y el enemigo
//se utiliza un switch para ver qué sprite se debe dibujar según la pos1 y si están visibles
void Juego::dibujar() {

	ventana1->clear();

	ventana1->draw(*fondo);
	ventana1->draw(*puntajeText);
	ventana1->draw(*vidasText);

	//un switch para determinar qué sprite debe dibujarse según el arreglo y las posiciones
	if (_EnemVisibles) {
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
	
	if (_InocVisibles) {
		switch (pos2) {
		case 0:
			ventana1->draw(*inocentes[0]->getSpriteArriba());
			break;
		case 1:
			ventana1->draw(*inocentes[1]->getSpriteArriba());
			break;
		case 2:
			ventana1->draw(*inocentes[2]->getSpriteAbajo());
			break;
		case 3:
			ventana1->draw(*inocentes[3]->getSpritePuerta());
			break;
		case 4:
			ventana1->draw(*inocentes[4]->getSpriteAbajo());
			break;
		default:
			break;
		}
	}
	
	

	jugador->Dibujar(ventana1);

	ventana1->display();


}

//Destructor de Juego
Juego::~Juego() {
	
	delete inocentes;
	delete enemigos;
	delete jugador;
	delete ventana1;


}