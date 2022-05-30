#ifndef _GERENCIADOREVENTOS_H_
#define _GERENCIADOREVENTOS_H_

#include "SFML/Graphics.hpp"

#include <map>
#include <functional>

namespace entidades {
    class GerenciadorEventos
    {
    private:
        static unsigned int proximoID;
        // ponteiro para a janela que vai ler os eventos(obstaculos nesse caso)
        sf::RenderWindow* janela;
        std::map<unsigned int, std::function<void(const sf::Event&)> > ouvintesMouse;
        std::map<unsigned int, std::function<void(const sf::Event&)> > ouvintesTeclado;
        std::map<unsigned int, std::function<void(const sf::Event&)> > ouvintesOutros;

        sf::Event evento;
    public:
        GerenciadorEventos();
        ~GerenciadorEventos();
        void tratarEventos();
        void setJanela(sf::RenderWindow* j);

        unsigned int adicionarOuvinteMouse(std::function<void(const sf::Event&)> chamada);
        void removerOuvinteMouse(int id);

        unsigned int adicionarOuvinteTeclado(std::function<void(const sf::Event&)> chamada);
        void removerOuvinteTeclado(int id);

        unsigned int adicionarOuvinteOutros(std::function<void(const sf::Event&)> chamada);
        void removerOuvinteOutros(int id);
    };
}

#endif