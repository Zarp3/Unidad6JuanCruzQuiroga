#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow window(VideoMode(960, 540), "Wild Physics");
    window.setMouseCursorVisible(false);

    Texture texturaMira, texturaObjeto;

    if (!texturaMira.loadFromFile("MiraPrincipal.png") ||
        !texturaObjeto.loadFromFile("ObjetoCinematico.png")) {
        cerr << "Error al cargar texturas" << endl;
        return -1;
    }

    Mira mira("MiraPrincipal.png");
    HUD hud("WesternCowboy.ttf", 3, 0, 0);

    vector<ObjetoCinematico> objetos;
    Clock relojObjetos;
    Clock relojDeltaTime;

    int puntaje = 0;

    while (window.isOpen()) {
        Event evento;
        while (window.pollEvent(evento)) {
            if (evento.type == Event::Closed) {
                window.close();
            }
        }

        float deltaTime = relojDeltaTime.restart().asSeconds();

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2f posicionDisparo = window.mapPixelToCoords(Mouse::getPosition(window));
            for (auto it = objetos.begin(); it != objetos.end();) {
                if (it->fueImpactado(posicionDisparo)) {
                    puntaje++;
                    hud.actualizarPuntaje(puntaje);
                    it = objetos.erase(it);
                }
                else {
                    ++it;
                }
            }
        }

        if (relojObjetos.getElapsedTime().asSeconds() > 1.0f) {
            bool tipoMovimiento = rand() % 2;
            Vector2f posicionInicial;
            Vector2f velocidadInicial;
            Vector2f aceleracion;

            if (tipoMovimiento) {
                
                posicionInicial = Vector2f(-50, rand() % 400 + 50);
                velocidadInicial = Vector2f(200.0f, 0.0f);
                aceleracion = Vector2f(0.0f, 0.0f);
            }
            else {
                
                posicionInicial = Vector2f(rand() % 800 + 50, -50);
                velocidadInicial = Vector2f(0.0f, 0.0f);
                aceleracion = Vector2f(0.0f, 300.0f);
            }

            objetos.emplace_back(texturaObjeto, posicionInicial, velocidadInicial, aceleracion);
            relojObjetos.restart();
        }

        for (auto it = objetos.begin(); it != objetos.end();) {
            it->mover(deltaTime);
            if (it->fueraDePantalla()) {
                it = objetos.erase(it);
            }
            else {
                ++it;
            }
        }

        mira.Seguimiento(window);

        window.clear();
        for (auto& objeto : objetos) {
            objeto.draw(window);
        }
        hud.draw(window);
        mira.draw(window);
        window.display();
    }

    return 0;
}
