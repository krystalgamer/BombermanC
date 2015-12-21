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


/*

BOMB PART

*/
void InitBombs(BOMBS bombs[5],ALLEGRO_BITMAP* bombSprite){
  int i = 0;
  while(i<5){
    bombs[i].isLive = false;
    bombs[i].maxTime = MAX_TIME;
    bombs[i].currTime = 0;
    bombs[i].entity.sprite = bombSprite;
    i++;
  }
}

void PlaceBomb(PLAYER* player, TILES map[15][13]){
  int i = 0;
  while(i<5){
    if(!(player->bombs[i].isLive)){
    player->bombs[i].isLive = true;
    player->bombs[i].entity.x = player->entity.x;
    player->bombs[i].entity.y = player->entity.y;
    map[player->entity.x][player->entity.y] = BOMB;
    return;
    }
    i++;
  }
}

void DrawBomb(BOMBS bombs[5]){
  int i = 0;
  while(i<5){
    if((bombs[i].isLive)){
    al_draw_scaled_bitmap(bombs[i].entity.sprite, 0, 0, 16, 16, bombs[i].entity.x*32, bombs[i].entity.y*32, 32, 32, 0);
    }
    i++;
  }
}
void UpdateBomb(BOMBS bombs[5],TILES map[15][13]){
  int i = 0;
  while(i<5){
    if((bombs[i].isLive)){
    bombs[i].currTime++;
      if (bombs[i].currTime >= bombs[i].maxTime) {
        bombs[i].isLive = false;
        bombs[i].currTime = 0;
        bombs[i].radius = 2;
        map[bombs[i].entity.x][bombs[i].entity.y] = GRASS;
        ExplodeBomb(bombs[i],map);
      }
    }
    i++;
  }
}
void ExplodeBomb(BOMBS bomb,TILES map[15][13]){

    bool stopVerticalF = false, stopHorizontalF = false,
    stopVerticalB = false, stopHorizontalB = false;

    int x = 0,y = 0;

    while(x++<bomb.radius){
      if(!stopHorizontalB && !stopHorizontalF){
        if(!stopHorizontalF && (map[bomb.entity.x + x][bomb.entity.y] == BOX
        || map[bomb.entity.x + x][bomb.entity.y] == GRASS))
            map[bomb.entity.x + x][bomb.entity.y] = GRASS;
        else
          stopHorizontalF = true;

        if(!stopHorizontalB && (map[bomb.entity.x - x][bomb.entity.y] == BOX
        || map[bomb.entity.x - x][bomb.entity.y] == GRASS))
              map[bomb.entity.x - x][bomb.entity.y] = GRASS;
          else
            stopHorizontalB = true;
      }

    }
    while(y++<bomb.radius){
      if(!stopVerticalB && !stopVerticalF){
        if(!stopVerticalF && (map[bomb.entity.x][bomb.entity.y + y] == BOX
        || map[bomb.entity.x][bomb.entity.y + y] == GRASS))
            map[bomb.entity.x][bomb.entity.y + y] = GRASS;
        else
          stopVerticalF = true;

        if(!stopVerticalB && (map[bomb.entity.x][bomb.entity.y - y] == BOX
        || map[bomb.entity.x][bomb.entity.y - y] == GRASS))
              map[bomb.entity.x][bomb.entity.y - y] = GRASS;
          else
            stopVerticalB = true;
      }

    }
    /*for(int x = 1;x<=bomb.radius;x++){
      for(int y = 1;y<=bomb.radius;y++){
        map[bomb.entity.x][bomb.entity.y + y] = map[bomb.entity.x][bomb.entity.y + y]==BOX?GRASS:map[bomb.entity.x][bomb.entity.y + y];
        map[bomb.entity.x][bomb.entity.y - y] = map[bomb.entity.x][bomb.entity.y - y]==BOX?GRASS:map[bomb.entity.x][bomb.entity.y - y];

      }
      map[bomb.entity.x + x][bomb.entity.y] = map[bomb.entity.x + x][bomb.entity.y]==BOX?GRASS:map[bomb.entity.x + x][bomb.entity.y];
      map[bomb.entity.x - x][bomb.entity.y] = map[bomb.entity.x -x][bomb.entity.y]==BOX?GRASS:map[bomb.entity.x -x][bomb.entity.y];

    }*/

}
