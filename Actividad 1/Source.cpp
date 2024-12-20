#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main() {
  
    const int AnchoPantalla = 800;
    const int AltoPantalla = 600;
    const float VelocidadIncial = 100.0f;
    const float VelocidadFinal = 500.0f;   
    const float IncrementoVelocidad = 50.0f; 

    RenderWindow window(VideoMode(AnchoPantalla, AltoPantalla), "Círculo en movimiento");
    window.setFramerateLimit(60);

    CircleShape Circulo(20.0f); 
    Circulo.setFillColor(Color::Red);
    Circulo.setPosition(0.0f, AltoPantalla / 2.0f - Circulo.getRadius());

    float currentSpeed = VelocidadIncial;
    Clock reloj;

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = reloj.restart().asSeconds();

        sf::Vector2f position = Circulo.getPosition();
        position.x += currentSpeed * deltaTime;

        if (position.x > AnchoPantalla) {
            position.x = -Circulo.getRadius() * 2; 
            currentSpeed += IncrementoVelocidad;      

            if (currentSpeed >= VelocidadFinal) {
                std::cout << "Velocidad final alcanzada: " << currentSpeed << " pixeles/segundo\n";
                window.close();
            }
        }

        Circulo.setPosition(position);

        window.clear(Color::Black);
        window.draw(Circulo);
        window.display();
    }

    return 0;
}