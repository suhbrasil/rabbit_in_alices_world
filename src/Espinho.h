#pragma once

#include <SFML/Graphics.hpp>
#include "Obstaculo.h"

using namespace sf;

namespace obstaculos {
    class Espinho : public Obstaculo {

    protected:

    public:
        Espinho();
        ~Espinho();
        void inicializarTextura();
        void inicializarVariaveis();
    };
}
