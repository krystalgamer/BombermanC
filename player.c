#include "game.h"

void TryToMovePlayer(ENTITY *player, int key, TILES map[15][13],PLAYER* pl){
      switch(key){
        case ALLEGRO_KEY_DOWN:
        case ALLEGRO_KEY_UP:
          MoveVertical(player,key==ALLEGRO_KEY_DOWN?true:false,map);
          break;
        case ALLEGRO_KEY_RIGHT:
        case ALLEGRO_KEY_LEFT:
          MoveHorizontal(player,key==ALLEGRO_KEY_RIGHT?true:false,map);
          break;
        case ALLEGRO_KEY_SPACE:
          PlaceBomb(pl, map);
          break;
      }

}
void MoveVertical(ENTITY* player,bool forward, TILES map[15][13]){
  if(forward){
    if(map[player->x][(player->y)+1] == GRASS)
      (player->y)++;
  }
  else{
    if(map[player->x][(player->y)-1] == GRASS)
      (player->y)--;
  }
}
void MoveHorizontal(ENTITY* player,bool forward, TILES map[15][13]){
  if(forward){
    if(map[(player->x)+1][player->y] == GRASS)
      (player->x)++;
  }
  else{
    if(map[(player->x)-1][player->y] == GRASS)
      (player->x)--;
  }
}

void CheckIfAlive(PLAYER* player, EXPLOSION explosion){

  if((explosion.horizontalB <= player->entity.x && explosion.horizontalF >= player->entity.x &&
    explosion.entity.y == player->entity.y))
      player->isAlive = false;

  else if((explosion.verticalB <= player->entity.y && explosion.verticalF >= player->entity.y &&
        explosion.entity.x == player->entity.x))
          player->isAlive = false;

}

void InitPlayer(PLAYER* player){

  player->entity.x = player->entity.y = 1;
  player->isAlive = true;
  player->maxBombs = MAX_BOMBS;
}
