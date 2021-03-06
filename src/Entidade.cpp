#include "Entidade.h"
using namespace entidades;

Entidade::Entidade() : Ente() {
    id = 3;
}

Entidade::~Entidade() {

}

void Entidade::inicializarTextura(const char* caminho)
{
    if (!textura.loadFromFile(caminho))
    {
        printf("imagem não encontrada");
    }
}

void Entidade::inicializarDesenhavel() {}

void Entidade::inicializarAnimacao()
{
    timerAnimacao.restart();
}

void Entidade::resetTimerAnimacao() {

    timerAnimacao.restart();
}

const FloatRect Entidade::getGlobalBounds() const {
    return desenhavel.getGlobalBounds();
}

const Vector2f Entidade::getPosition() const {
    return desenhavel.getPosition();
}

void Entidade::setPosition(const float x, const float y) {
    desenhavel.setPosition(x,y);
}

const Vector2f Entidade::getDimensoesMetade() const {
    return dimensoes/2.0f;
}

void Entidade::render(RenderTarget &target)
{
    target.draw(desenhavel);
}
