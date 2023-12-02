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
	//puntajeGameOver->setString("TU PUNTUACION FUE: " + to_string(ptos));
	puntajeGameOver->setPosition(170, 400);
	
	//Textura y Sprite de fondo
	textura1 = new Texture;
	fondo = new Sprite;
	textura1->loadFromFile("assets/fondo_base_cerrado.jpg");
	fondo->setTexture(*textura1);

	textura3 = new Texture;
	fondo_danio = new Sprite;
	textura3->loadFromFile("assets/fondo_danio_cerrado.jpg");
	fondo_danio->setTexture(*textura3);


	textura2 = new Texture;
	menuFondo = new Sprite;
	textura2->loadFromFile("assets/menu.png");
	menuFondo->setTexture(*textura2);
	menuFondo->setScale(0.5f, 0.5f);
	menuFondo->setPosition(75, 0);

	//Inicializar el jugador
	jugador = new Jugador();
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
					_clock.restart();
					_clock2.restart();
				}
			}
		}

		ventana1->clear(Color::Black);

		if (start) {

			gameLoop();

		}
		else {

			ventana1->draw(*menuFondo);
			ventana1->draw(*menu);
		}

		ventana1->display();
	}
}
// loop que procesa eventos actualiza y dibuja
void Juego::gameLoop() {

	bool gameOver = false;

	while (ventana1->isOpen() && !gameOver) {

		procesar_eventos();
		actualizar();
		dibujar();

		if (vidas <= 0) {
			gameOver = true;

		}
	}
	while (gameOver && ventana1->isOpen()) {
		ventana1->clear();

		ventana1->draw(*textGameOver);
		ventana1->draw(*volverMenu);
		puntajeGameOver->setString("TU PUNTUACION FUE: " + to_string(ptos));
		ventana1->draw(*puntajeGameOver);

		ventana1->display();

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
	if (!_EnemVisibles) {
		//si el tiempo transcurrido es mayor al tiempo apagado//
		if (_clock.getElapsedTime().asSeconds() > tiempoApagado) {
			//reiniciar reloj//
			_clock.restart();
			//establecer posicion de ENEMIGOS
			pos1 = rand() % 5;
			while (pos1 == pos2) {
				pos1 = rand() % 5;
			}
			//VISIBLES es true//
			_EnemVisibles = true;
			//chequear
			cout << pos1 << endl;

		
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
				_EnemVisibles = false;
				vidas -= 1;
				vidasText->setString("VIDAS: " + to_string(vidas));
				//recibir daño
				recibirDanio();
				//cout << vidas;
				_clock.restart();
			}
		}
	}



	if (!_InocVisibles) {
		//si el tiempo transcurrido es mayor al tiempo apagado//
		if (_clock2.getElapsedTime().asSeconds() > tiempoApagado) {
			//reiniciar reloj//
			_clock2.restart();

			pos2 = rand() % 5;
			while (pos2 == pos1) {
				pos2 = rand() % 5;
			}
			_InocVisibles = true;
			cout << pos2 << endl;
		}


	}
	else {
		{
			//si el tiempo transcurrido es mayor al tiempo visible
			if (_clock2.getElapsedTime().asSeconds() > tiempoVisible) {
				//dejan de estar visibles, disparan y restan una vida y se reinicia el reloj
				_InocVisibles = false;
				
				_clock2.restart();

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
	if (_EnemVisibles) {
		if (enemigos[pos1]->Colision(playerPos.x, playerPos.y)) {
			cout << "hit";
			//ELIMINADOS: dejan de estar visible y suman 10 ptos
			_EnemVisibles = false;
			ptos += 1;
			puntajeText->setString("PUNTAJE: " + to_string(ptos));
			cout << ptos<<endl;
		}
}

	if (_InocVisibles) {
		if (inocentes[pos2]->Colision(playerPos.x, playerPos.y)) {
			cout << "hit";
			//ELIMINADOS: dejan de estar visible y suman 10 ptos
			_InocVisibles = false;
			recibirDanio();
			vidas -= 1;
			ptos -= 10;
			vidasText->setString("VIDAS: " + to_string(vidas));
			puntajeText->setString("PUNTAJE: " + to_string(ptos));
			cout << vidas<<endl;
		}
}




}
void Juego::recibirDanio() {
	
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

Juego::~Juego() {
	
	delete inocentes;
	delete enemigos;
	delete jugador;
	delete ventana1;


}