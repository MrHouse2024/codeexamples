#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

const char* titulo = "E";
const short ancho_pantalla = 960;
const short alto_pantalla = 540;

int main()
{
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);

    ALLEGRO_DISPLAY* pantalla = al_create_display(ancho_pantalla, alto_pantalla);
    al_set_window_position(pantalla, 540, 960); // ~medio de la pantalla
    al_set_window_title(pantalla, titulo);

    ALLEGRO_FONT* fuente = al_load_ttf_font("arial.ttf", 36, 0); // <-- tamaño 26
    al_draw_text(fuente, al_map_rgb(255, 255, 255), ancho_pantalla / 2, 10, ALLEGRO_ALIGN_CENTER, "o");

    ALLEGRO_BITMAP* img1 = al_load_bitmap(".png");
    ALLEGRO_BITMAP* img2 = al_load_bitmap(".png");

    int x_img1 = 0;
    int y_img1 = alto_pantalla - al_get_bitmap_height(img1);
    int x_img2 = 0; // poscion en x
    int y_img2 = 100; // posicion en y

    ALLEGRO_TIMER* temporizador = al_create_timer(1.0 / 60);


    ALLEGRO_EVENT_QUEUE* cola_eventos = al_create_event_queue();
    al_register_event_source(cola_eventos, al_get_keyboard_event_source());
    al_register_event_source(cola_eventos, al_get_timer_event_source(temporizador));

    // Iniciar el temporizador
    al_start_timer(temporizador);

    bool redibujar = true;

    while (true) { /
        ALLEGRO_EVENT ev;
        al_wait_for_event(cola_eventos, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            x_img2 += 5;
            if (x_img2 > ancho_pantalla) {
                x_img2 = -(al_get_bitmap_width(img2));
            }
            redibujar = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
                x_img1 += 10;
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_A) {
                x_img1 -= 10;
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_W) {
                y_img1 += 10;
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_S) {
                y_img1 -= 10;
            }
            redibujar = true;
        }

        if (redibujar) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(img1, x_img1, y_img1, 0);
            al_draw_bitmap(img2, x_img2, y_img2, 0);
            al_draw_text(fuente, al_map_rgb(255, 255, 255), ancho_pantalla / 2, 10, ALLEGRO_ALIGN_CENTER, "Práctica de Allegro");
            al_flip_display();
            redibujar = false;
        }
    }


    al_destroy_display(pantalla);
    al_destroy_bitmap(img1);
    al_destroy_bitmap(img2);
    al_destroy_timer(temporizador);
    al_destroy_event_queue(cola_eventos);
    al_destroy_font(fuente);

    return 0;
}
