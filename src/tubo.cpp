#include "tubo.hpp"
#include "constants.h"
#include <allegro5/allegro_image.h>
#include <cstdlib>

ALLEGRO_BITMAP* Tubo::imagem_cima = nullptr;
ALLEGRO_BITMAP* Tubo::imagem_baixo = nullptr;

void carregar_imagens_tubo() {
    Tubo::imagem_cima = al_load_bitmap("output/cimaori.png");
    Tubo::imagem_baixo = al_load_bitmap("output/baixoori.png");
}

void destruir_imagens_tubo() {
    al_destroy_bitmap(Tubo::imagem_cima);
    al_destroy_bitmap(Tubo::imagem_baixo);
}

Tubo::Tubo(int posicao_x) {
    x = posicao_x;
    altura_abertura = rand() % (ALTURA_TELA - ESPACO_ENTRE_TUBOS - 100) + 50;
}

void Tubo::atualizar() {
    x -= VELOCIDADE_TUBO;
    if (x + LARGURA_TUBO < 0) {
        x = LARGURA_TELA;
        altura_abertura = rand() % (ALTURA_TELA - ESPACO_ENTRE_TUBOS - 100) + 50;
    }
}

void Tubo::desenhar() {
    al_draw_bitmap(imagem_cima, x, altura_abertura - ALTURA_TUBO, 0);
    al_draw_bitmap(imagem_baixo, x, altura_abertura + ESPACO_ENTRE_TUBOS, 0);
}

bool Tubo::colide(int jogador_x, int jogador_y, int jogador_largura, int jogador_altura) {
    if (jogador_x + jogador_largura > x && jogador_x < x + LARGURA_TUBO) { // lado direito está depois do tubo mas o jogador/flappy está antes
        if (jogador_y < altura_abertura || jogador_y + jogador_altura > altura_abertura + ESPACO_ENTRE_TUBOS) {
            return true;// alt abertuda = borda inferior do tubo de cima; alt abertura + espaço é a borda inferior do de baixo
        } // no caso vê se encosta ou pega no tubo inferior/superior
    } // diz respeito a toda regiao do y, por isso nao precisa se preocupar tanto com batids laterais
    return false;
}
