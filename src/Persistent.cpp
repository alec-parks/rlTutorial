#include "main.hpp"

void Engine::save() {
  if (player->destructible->isDead() ){
    TCODSystem::deleteFile("game.sav");
  }else {
    TCODZip zip;
    //save the map
    zip.putInt(map->width);
    zip.putInt(map->height);
    map->save(zip);
    //then the player
    player->save(zip);
    //All the other actors
    zip.putInt(actors.size()-1);
    for (Actor **iterator=actors.begin(); iterator!=actors.end();
           iterator++){
      if(*iterator != player){
        (*iterator)->save(zip);
      }
    }
    //Save the logs
    gui->save(zip);
    zip.saveToFile("game.sav");
  }
}

void Engine::load(){
  if ( TCODSystem::fileExists("game.sav")) {
    TCODZip zip;
    zip.loadFromFile("game.sav");
    //load map
    int width = zip.getInt();
    int height = zip.getInt();
    map = new Map(width,height);
    map->load(zip);
    //Player
    player = new Actor(0,0,0,NULL,TCODColor::white);
    player->load(zip);
    actors.push(player);
    //All other Actors
    int nbActors=zip.getInt();
    while (nbActors > 0) {
      Actor *actor = new Actor(0,0,0,NULL,TCODColor::white);
      actor->load(zip);
      actors.push(actor);
      nbActors--;
    }
    //Last - Logs
    gui->load(zip);
  } else {
    engine.init();
  }
}
