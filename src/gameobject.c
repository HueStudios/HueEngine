#if INTERFACE
  #include "engine.h"
  #include "gamestate.h"
  typedef struct {
    void (*on_update) (GameObject* object);
    void (*on_draw) (GameObject* object, double dt);
    bool (*on_event) (GameObject* object, ALLEGRO_EVENT event);
    int depth;
    void* data;
    Engine* engine;
    GameState* state;
  } GameObject;
#endif
