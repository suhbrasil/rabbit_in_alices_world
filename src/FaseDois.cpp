#include "FaseDois.h"
using namespace fases;


FaseDois::FaseDois(Jogador* j, GerenciadorGrafico* gf) : Fase(j, gf)
{
    id = 6;

    inicializarFundoTela();
    inicializarJogador(j);
    qtdeGalhos = 0;
    qtdeCogumelos = 1;
    qtdeRainhas = 1;
    qtdeGatos = 0;
    gerarObstaculos();
    gerarInimigos();
}

FaseDois::~FaseDois()
{
}

void FaseDois::gerarGatos(){
   for (int i = 0 ; i < qtdeGatos; i++) {
        Gato* temp = new Gato();
        gatos.lista.inserir(dynamic_cast<Entidade*> (temp));
        temp->setPosicao(i);
        gerenciadorColisao.adicionarInimigo(temp);
    }
}

void FaseDois::gerarRainhas(){
   for (int i = 0 ; i < qtdeRainhas; i++) {
        Rainha* temp = new Rainha();
        rainhas.lista.inserir(dynamic_cast<Entidade*> (temp));
        temp->setPosicao(i);
        gerenciadorColisao.adicionarInimigo(temp);
    }
}

void FaseDois::gerarInimigos() {
    gerarRainhas();
    gerarGatos();
}


void FaseDois::gerarCogumelos(){
   for (int i = 0 ; i < qtdeCogumelos; i++) {
        Cogumelo* temp = new Cogumelo();
        cogumelos.lista.inserir(dynamic_cast<Entidade*> (temp));
        temp->setPosicao(i);
        gerenciadorColisao.adicionarObstaculo(temp);
    }
}

void FaseDois::gerarGalhos(){
   for (int i = 0 ; i < qtdeGalhos; i++) {
        Galho* temp = new Galho();
        galhos.lista.inserir(dynamic_cast<Entidade*> (temp));
        temp->setPosicao(i);
        gerenciadorColisao.adicionarObstaculo(temp);
    }
}

void FaseDois::gerarObstaculos() {
    gerarGalhos();
    gerarCogumelos();
}

void FaseDois::atualizarRenderGatos(int i) {
    Gato* gato = dynamic_cast <Gato*>(gatos.lista.getItem(i)->getInfo());
    gato->render(*janela);

}

void FaseDois::atualizarRenderRainhas(int j) {
    Rainha* rainha = dynamic_cast <Rainha*>(rainhas.lista.getItem(j)->getInfo());
    rainha->render(*janela);
}

void FaseDois::atualizarRenderGalhos(int i) {
    Galho* galho = dynamic_cast <Galho*>(galhos.lista.getItem(i)->getInfo());
    galho->render(*janela);

}

void FaseDois::atualizarRenderCogumelos(int j) {
    Cogumelo* cogumelo = dynamic_cast <Cogumelo*>(cogumelos.lista.getItem(j)->getInfo());
    cogumelo->render(*janela);
}

void FaseDois::atualizarRenderInimigos() {
    for (int i = 0 ; i < qtdeGatos; i++){
       atualizarRenderGatos(i);
    }

    for (int j = 0 ; j < qtdeRainhas; j++){
       atualizarRenderRainhas(j);
    }
}

void FaseDois::atualizarRenderObstaculos() {
    for (int i = 0 ; i < qtdeGalhos; i++){
       atualizarRenderGalhos(i);
    }

    for (int j = 0 ; j < qtdeCogumelos; j++){
       atualizarRenderCogumelos(j);
    }
}
