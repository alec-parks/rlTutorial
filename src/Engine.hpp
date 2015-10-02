#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine {
public:
  enum GameStatus {
    STARTUP,
    IDLE,
    NEW_TURN,
    VICTORY,
    DEFEAT
  } gameStatus;
  int fovRadius;
  Actor *player;
  Map *map;

  int screenWidth;
  int screenHeight;
  Gui *gui;
  TCOD_key_t lastKey;
  TCOD_mouse_t mouse;
  TCODList<Actor *> actors;

  Engine(int screenWidth, int screenHeight);
  ~Engine();
  void update();
  void render();
  void sendToBack(Actor *actor);
private:
  bool computeFov;
};

extern Engine engine;
#endif
