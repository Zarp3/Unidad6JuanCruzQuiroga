#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class ObjetoCinematico {
private:
    Sprite sprite;
    Vector2f velocidad;
    Vector2f aceleracion;

public:
    ObjetoCinematico(Texture& textura, const Vector2f& posicionInicial, const Vector2f& velocidadInicial, const Vector2f& aceleracionInicial)
        : velocidad(velocidadInicial), aceleracion(aceleracionInicial) {
        sprite.setTexture(textura);
        sprite.setPosition(posicionInicial);
        sprite.setScale(0.2f, 0.2f);
    }

    void mover(float deltaTime) {
        velocidad += aceleracion * deltaTime;
        sprite.move(velocidad * deltaTime);
    }

    bool fueImpactado(const Vector2f& posicionDisparo) {
        return sprite.getGlobalBounds().contains(posicionDisparo);
    }

    bool fueraDePantalla() {
        FloatRect bounds = sprite.getGlobalBounds();
        return (bounds.top > 600 || bounds.left < -100 || bounds.left > 960);
    }

    void draw(RenderWindow& window) {
        window.draw(sprite);
    }
};
