#pragma once

#include <SFML/Graphics.hpp>
#include "Obstaculo.h"

using namespace sf;

namespace obstaculos
{
    class Galho : public Obstaculo
    {
    private:
    public:
        Galho();
        ~Galho();
        void inicializarTextura();
        void inicializarDesenhavel();
        void inicializarVariaveis();
        void setPosicao(int i);
        float operator+(float i);
        float operator-(float i);
    };
}
