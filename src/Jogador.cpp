#include "Jogador.h"
#include <iostream>
using namespace personagens;
using namespace sf;

Jogador::Jogador() : Personagem()
{
    id = 11;

    inicializarVariaveis();
    inicializarDesenhavel();
    inicializarAnimacao();

    desenhavel.setPosition(posicaoInicialX,posicaoInicialY);
}

Jogador::~Jogador()
{
}

void Jogador::setTextura(const char* caminho) {
    inicializarTextura(caminho);
}

void Jogador::inicializarDesenhavel()
{
    desenhavel.setTexture(textura);

    frameAtual = IntRect(0, 0, 45, 34);
    desenhavel.setTextureRect(frameAtual);
    // para mudar o tamanho do desenho
    desenhavel.setScale(2.0f, 2.0f);
}

void Jogador::atualizar1()
{
    atualizarMovimentacaoJ1();
    atualizarAnimacao();
    atualizarFenomenosFisicos();
}

void Jogador::atualizar2()
{
    atualizarMovimentacaoJ2();
    atualizarAnimacao();
    atualizarFenomenosFisicos();
}

void Jogador::inicializarVariaveis()
{
    countFrame = 0;
    movimentando = false;
    estadoDeAnimacao = ESTADOINICIAL;
    podePular = true;
    pontos = 700;
    fstream pos ("jogada.txt");
    // colcocar a posicao inicial para a salva se estiver pausado o jogo
    if(pos.is_open()) {
        string linhaPosX;
        pos >> linhaPosX;
        posicaoInicialX = std::stof(linhaPosX);
        string linhaPosY;
        pos >> linhaPosY;
        posicaoInicialY = std::stof(linhaPosX);
        pos.close();
        remove("jogada.txt");
    }
    else {
        posicaoInicialX = 640.f;
        posicaoInicialY = 637.f;
    }
}

void Jogador::atualizarMovimentacaoJ1()
{
    movimentando = false;

    if (Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        movimentar(-0.5f, 0.f);
        movimentando = true;
    }

    else if(Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && podePular) {
        podePular = false;
        movimentar(2.f, -sqrtf(2.f * gravidade * alturaPulo));
        movimentando = true;
    }

    else if(Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && podePular) {
        podePular = false;
        movimentar(-2.0f, -sqrtf(2.f * gravidade * alturaPulo));
        movimentando = true;
    }

    else if (Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        movimentar(0.5f, 0.f);
        movimentando = true;
    }

    else if (Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && podePular)
    {
        podePular = false;
        velocidade.y = -sqrtf(2.f * gravidade * alturaPulo);
        velocidade.y *= 10.f;
        movimentando = true;

    }
    velocidade.y += gravidade * 0.8;
    countFrame++;

    if(estadoDeAnimacao == ESTADOINICIAL)
        estadoDeAnimacao = SEGUNDOESTADO;
    else
        estadoDeAnimacao = ESTADOINICIAL;
}

void Jogador::atualizarMovimentacaoJ2()
{
    movimentando = false;

    if (Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        movimentar(-0.5f, 0.f);
        movimentando = true;
    }

    else if(Keyboard::isKeyPressed(sf::Keyboard::Key::D) && Keyboard::isKeyPressed(sf::Keyboard::Key::W) && podePular) {
        podePular = false;
        movimentar(2.f, -sqrtf(2.f * gravidade * alturaPulo));
        movimentando = true;
    }

    else if(Keyboard::isKeyPressed(sf::Keyboard::Key::A) && Keyboard::isKeyPressed(sf::Keyboard::Key::W) && podePular) {
        podePular = false;
        movimentar(-2.0f, -sqrtf(2.f * gravidade * alturaPulo));
        movimentando = true;
    }

    else if (Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        movimentar(0.5f, 0.f);
        movimentando = true;
    }

    else if (Keyboard::isKeyPressed(sf::Keyboard::Key::W) && podePular)
    {
        podePular = false;
        velocidade.y = -sqrtf(2.f * gravidade * alturaPulo);
        velocidade.y *= 10.f;
        movimentando = true;

    }
    velocidade.y += gravidade * 0.8;
    countFrame++;

    if(estadoDeAnimacao == ESTADOINICIAL)
        estadoDeAnimacao = SEGUNDOESTADO;
    else
        estadoDeAnimacao = ESTADOINICIAL;
}

void Jogador::movimentar(const float direcaoX, const float direcaoY) {
    velocidade.x += direcaoX * aceleracao;
    velocidade.y += direcaoY * aceleracao;

    if(abs(velocidade.x) > velocidadeMaxima) {
        if(velocidade.x < 0)
            velocidade.x = velocidadeMaxima * -1.f;
        else if(velocidade.x > 0)
            velocidade.x  = velocidadeMaxima;
    }
}

void Jogador::resetPosicao() {
    desenhavel.setPosition(640,632);
}

void Jogador::atualizarAnimacao()
{
    if (timerAnimacao.getElapsedTime().asSeconds() >= 0.2f)
    {
        if (!movimentando)
        {
            // movimenta a textura pra esquerda
            frameAtual.left += 273.3f;
            if (frameAtual.left >= 273.f)
                frameAtual.left = 0;
        }
        else if(movimentando && countFrame > 20){
            if(estadoDeAnimacao == ESTADOINICIAL) {
                frameAtual = IntRect(0, 0, 40, 34);
            }
            else if(estadoDeAnimacao == SEGUNDOESTADO) {
                frameAtual = IntRect(46, 0, 47, 34);
            }
            else if(estadoDeAnimacao == PULO){
                frameAtual = IntRect(96,0,49,34);
            }
            countFrame = 0;
        }
    }
    desenhavel.setTextureRect(frameAtual);
}

Vector2f Jogador::getVelocidade() {
    return velocidade;
}

bool Jogador::getPodePular() {
    return podePular;
}

void Jogador::setPodePular(bool pular) {
    podePular = pular;
}

void Jogador::diminuirPontos(int ponto) {
    pontos -= ponto;
}

void Jogador::ganharPontos(int ponto) {
    pontos += ponto;
}

int Jogador::getPontos() {
    return pontos;
}
