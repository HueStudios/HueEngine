#if INTERFACE
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>
#include "gamestate.h"

typedef struct GameState GameState;

typedef struct Engine {
  int screen_width;
  int screen_height;
  void (*pre_update)(Engine *engine, double dt);
  void (*post_update)(Engine *engine, double dt);
  void (*pre_draw)(Engine *engine);
  void (*post_draw)(Engine *engine);
  bool (*pre_event)(Engine *engine, ALLEGRO_EVENT event);
  bool (*post_event)(Engine *engine, ALLEGRO_EVENT event);
  GameState *states[32];
  unsigned char state_index;
  ALLEGRO_DISPLAY *display;
  ALLEGRO_EVENT_QUEUE *queue;
  ALLEGRO_TIMER *timer;
} Engine;
#endif

#include "engine.h"

Engine *newEngine(int screen_width, int screen_height) {
  Engine *engine = malloc(sizeof(*engine));
  engine->screen_width = screen_width;
  engine->screen_height = screen_height;
  engine->pre_update = NULL;
  engine->post_update = NULL;
  engine->pre_draw = NULL;
  engine->post_draw = NULL;
  engine->pre_event = NULL;
  engine->post_event = NULL;

  al_init();
  al_init_image_addon();
  al_init_primitives_addon();
  al_init_font_addon();
  al_init_ttf_addon();

  engine->display = al_create_display(engine->screen_width, engine->screen_height);
  engine->queue = al_create_event_queue();
  engine->timer = al_create_timer(1.0 / 60.0);

  al_install_keyboard();
  al_install_mouse();
  al_register_event_source(engine->queue, al_get_keyboard_event_source());
  al_register_event_source(engine->queue, al_get_display_event_source(engine->display));
  al_register_event_source(engine->queue, al_get_mouse_event_source());
  al_register_event_source(engine->queue, al_get_timer_event_source(engine->timer));

  al_start_timer(engine->timer);

  return engine;
}

int engine_run(Engine *engine) {
  double dt = 0;
  double old_time = al_get_time();

  ALLEGRO_EVENT event;
  bool running = true;
  while (running) {

    if (engine->state_index == 0) {
      running = false;
      break;
    }

    al_wait_for_event(engine->queue, &event);
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      running = false;
    }

    if (event.type == ALLEGRO_EVENT_TIMER) {
      if (engine->pre_update != NULL) {
        engine->pre_update(engine, dt);
      }
      gamestate_update(engine->states[engine->state_index], dt);
      if (engine->post_update != NULL) {
        engine->post_update(engine, dt);
      }

      al_clear_to_color(al_map_rgb(20, 20, 20));
      if (engine->pre_draw != NULL) {
        engine->pre_draw(engine);
      }
      gamestate_draw(engine->states[engine->state_index]);
      if (engine->post_draw != NULL) {
        engine->post_draw(engine);
      }
      al_flip_display();
      double new_time = al_get_time();
      dt = new_time - old_time;
      double fps = 1/dt;
      old_time = new_time;
      printf("%f\n", fps);
    }
    if (engine->pre_event != NULL) {
      engine->pre_event(engine, event);
    }
    gamestate_event(engine->states[engine->state_index], event);
    if (engine->post_event != NULL) {
      engine->post_event(engine, event);
    }

  }

  al_stop_timer(engine->timer);
  al_destroy_timer(engine->timer);
  al_uninstall_keyboard();
  al_destroy_event_queue(engine->queue);
  al_destroy_display(engine->display);
  al_shutdown_primitives_addon();
  al_uninstall_system();

  return 0;
}
