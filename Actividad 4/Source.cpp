#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main() {
    
    const int AnchoPantalla = 800;
    const int AltoPantalla = 600;
    const float gravedad = 500.0f;          
    const float Rebote = 0.7f;     
    const float suelo = AltoPantalla - 40.0f; 

    RenderWindow window(VideoMode(AnchoPantalla, AltoPantalla), "Rebote de Esfera");
    window.setFramerateLimit(60);

    CircleShape pelota(20.0f); 
    pelota.setFillColor(Color::Blue);
    pelota.setPosition(AltoPantalla / 2.0f, 0.0f);

    float velocidadY = 0.0f;
    Clock clock;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        velocidadY += gravedad * deltaTime;

        Vector2f posicion = pelota.getPosition();
        posicion.y += velocidadY * deltaTime;

        if (posicion.y > suelo) {
            posicion.y = suelo; 
            velocidadY = -velocidadY * Rebote; 

            if (std::abs(velocidadY) < 10.0f) {
                velocidadY = 0.0f;
            }
        }

        pelota.setPosition(posicion);

        window.clear(Color::Black);
        window.draw(pelota);
        window.display();
    }

    return 0;
}
