#include "Fase.h"
using namespace fases;


Fase::Fase(Jogador* j1, Jogador* j2, GerenciadorGrafico* gf) : Ente(), gerenciadorGrafico(gf), qtdJogadores(1)
{
    id = 5;

    inicializarJogador(j1, j2);
    janela = gerenciadorGrafico->getJanela();
}

Fase::~Fase()
{

}


void Fase::inicializarFundoTela(const char* caminho) {
    if(!fundoTelaTex.loadFromFile(caminho))
        cout << "Erro: nao foi possivel carregar o background" << endl;
    fundoTela.setTexture(fundoTelaTex);
}

void Fase::renderFundoTela() {
    janela->draw(fundoTela);
}

Texture Fase::getFundoTela() {
    return fundoTelaTex;
}

void Fase::salvarJogada() {
    ofstream arq("jogada.txt", fstream::app);
    arq << jogador1->getPosition().x << "\n" << jogador1->getPosition().y << "\n";
    arq.close();
}

void Fase::pausarJogada() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
        salvarJogada();
        janela->close();
    }
}

void Fase::verPontos() {
    if(qtdJogadores == 1) {
        if(jogador1->getPontos() <= 0) {
            janela->close();
        }
    }
    else {
        if(jogador1->getPontos() <= 0 && jogador2->getPontos() > 0) {
            jogador1->desenhavel.move(0.0f, 500.f);
        }
        else if (jogador1->getPontos() > 0 && jogador2->getPontos() <= 0)
            jogador2->desenhavel.move(0.0f, 500.f);
        else if(jogador1->getPontos() <= 0 && jogador2->getPontos() <= 0) {
            janela->close();
        }
    }
}

void Fase::inicializarJogador(Jogador* j1, Jogador* j2)
{
    jogador1 = new Jogador();
    jogador2 = new Jogador();
    jogador1 = j1;
    jogador2 = j2;
}

void Fase::atualizarJogador1()
{
    jogador1->atualizar1();
}

void Fase::atualizarJogador2() {
    jogador2->atualizar2();
}

void Fase::atualizar1()
{
    cout << "oi12" << endl;
    while (janela->pollEvent(event1))
    {
        if (event1.type == Event::Closed)
            janela->close();
        else if (event1.type == Event::KeyPressed && event1.key.code == Keyboard::Escape)
            janela->close();

        if(event1.type ==  Event::KeyReleased &&
            (event1.key.code == Keyboard::Escape || event1.key.code == Keyboard::Up ||
                 event1.key.code == Keyboard::Down || event1.key.code == Keyboard::Left
                    || event1.key.code == Keyboard::Right))
        {
            jogador1->resetTimerAnimacao();
        }
    }
    cout << "oi13" << endl;
    atualizarJogador1();
    cout << "oi14" << endl;
    atualizarColisao();
    cout << "oi15" << endl;
}

void Fase::atualizar2()
{
    while (janela->pollEvent(event2))
    {

        if (event2.type == Event::Closed)
            janela->close();
        else if (event2.type == Event::KeyPressed && event2.key.code == Keyboard::Escape)
            janela->close();

        if(event2.type ==  Event::KeyReleased &&
            (event2.key.code == Keyboard::Escape || event2.key.code == Keyboard::E ||
                 event2.key.code == Keyboard::D || event2.key.code == Keyboard::S
                    || event2.key.code == Keyboard::F))
        {
            jogador2->resetTimerAnimacao();
        }
    }
    atualizarJogador2();
    atualizarColisao();
}

void Fase::atualizarRenderJogador() {
    if(qtdJogadores == 1) {
        jogador1->render(*janela);
    }
    else {
        jogador1->render(*janela);
        jogador2->render(*janela);
    }
}

void Fase::atualizarColisao() {
    if(qtdJogadores == 1) {
        cout << "oi16" << endl;
        gerenciadorColisao.verificarColisoes(*janela, jogador1);
    }
    else {
        cout << "oi15" << endl;
        gerenciadorColisao.verificarColisoes(*janela, jogador1);
        cout << "oi17" << endl;
        gerenciadorColisao.verificarColisoes(*janela, jogador2);
        cout << "oi18" << endl;
    }
}

void Fase::render()
{
    renderFundoTela();
    atualizarRenderJogador();
    atualizarRenderObstaculos();
    atualizarRenderInimigos();

    janela->display();
}

int Fase::gerarAleatoriamente(int maior, int menor) {
    srand(time(NULL));
    int aleatorio = rand()%(maior-menor)+1 + menor;

    return aleatorio;
}

void Fase::setQtdJogadores(int qtd) {
    qtdJogadores = qtd;
}

int Fase::getQtdJogadores() {
    return qtdJogadores;
}

void Fase::executar() {
    janela->clear();
    cout << "oi3" << endl;
    gerenciadorGrafico->centralizar(jogador1->getPosition());
    cout << "oi4" << endl;
    pausarJogada();
    cout << "oi5" << endl;
    // verPontos();
    cout << "oi6" << endl;
    if(qtdJogadores == 1) {
        atualizar1();
        cout << "oi7" << endl;
    }
    else {
        cout << "oi8" << endl;
        atualizar1();
        cout << "oi12" << endl;
        atualizar2();
        cout << "oi9" << endl;
    }
    cout << "oi10" << endl;
    render();
    cout << "oi11" << endl;
}
