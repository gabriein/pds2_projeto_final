#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "constants.h"
#include "fundo.hpp"
#include "tubo.hpp"
#include "jogador.hpp"

int main() {
    srand(time(0)); // gera numeros aleatorios pras alturas dos tubos
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY* tela = al_create_display(LARGURA_TELA, ALTURA_TELA); // cria a janela
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue(); // teclado e timer (eventos)
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    ALLEGRO_FONT* fonte = al_load_ttf_font("font.ttf", 32, 0);

    Fundo fundo;
    carregar_imagens_tubo();
    Jogador jogador;

    const int NUM_TUBOS = 3;
    Tubo tubos[NUM_TUBOS] = { Tubo(400), Tubo(700), Tubo(1000) }; // cria os tubos espaçados pra aparecer varios simultaneos (3)

    al_register_event_source(fila_eventos, al_get_display_event_source(tela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    bool sair = false;
    bool tecla_espaco = false;

    al_start_timer(timer);

    while (!sair) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            sair = true; // sai do loop quando fecha a janela
        } else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evento.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                tecla_espaco = true;
            }
        } else if (evento.type == ALLEGRO_EVENT_TIMER) {
            if (tecla_espaco) {
                jogador.pular();
                tecla_espaco = false; // o passaro pula e atualiza o status d tecla
            }

            fundo.atualizar();
            jogador.atualizar();

            for (int i = 0; i < NUM_TUBOS; ++i) {
                tubos[i].atualizar(); // move os tubos

                if (tubos[i].colide(jogador.x, jogador.y, 51, 38)) {
                    sair = true; // verifica colisão
                }
            }

            if (jogador.y > ALTURA_TELA || jogador.y < 0) {
                sair = true; // verifica se saiu da tela
            }

            al_clear_to_color(al_map_rgb(0, 0, 0));
            fundo.desenhar();

            for (int i = 0; i < NUM_TUBOS; ++i) {
                tubos[i].desenhar();
            }

            jogador.desenhar();

            al_flip_display();
        }
    }

    destruir_imagens_tubo();
    al_destroy_font(fonte);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(tela);

    return 0;
}
