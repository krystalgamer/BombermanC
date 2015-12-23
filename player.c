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
void InitBombs(BOMBS bombs[5],ALLEGRO_BITMAP* bombSprite,ALLEGRO_BITMAP* expSprite){
  int i = 0;
  while(i<5){
    bombs[i].isLive = bombs[i].explosion.isLive = false;
    bombs[i].maxTime = MAX_TIME;
    bombs[i].currTime = 0;
    bombs[i].radius = bombs[i].explosion.radius = 2;
    bombs[i].entity.sprite = bombSprite;
    bombs[i].explosion.frameDelay = 1;
    bombs[i].explosion.maxFrame = 6;
    bombs[i].explosion.currFrame = bombs[i].explosion.currDelay = 0;
    bombs[i].explosion.entity.sprite = expSprite;
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
        CreateExplosion(bombs[i], &bombs[i].explosion);
        ExplodeBomb(&bombs[i],map);
      }
    }
    i++;
  }
}
void ExplodeBomb(BOMBS *bomb,TILES map[15][13]){

    bool stopVerticalF = false, stopHorizontalF = false,
    stopVerticalB = false, stopHorizontalB = false;

    int x = 1,y = 1;
    bomb->explosion.horizontalF = bomb->explosion.horizontalB = bomb->entity.x;
    bomb->explosion.verticalF = bomb->explosion.verticalB = bomb->entity.y;

    while(x<=bomb->radius){
      if(!stopHorizontalB || !stopHorizontalF){

        if(!stopHorizontalF && (map[bomb->entity.x + x][bomb->entity.y] == BOX
        || map[bomb->entity.x + x][bomb->entity.y] == GRASS)){

            map[bomb->entity.x + x][bomb->entity.y] = GRASS;
            bomb->explosion.horizontalF = bomb->entity.x + x;
          }
        else
          stopHorizontalF = true;

        if(!stopHorizontalB && (map[bomb->entity.x - x][bomb->entity.y] == BOX
        || map[bomb->entity.x - x][bomb->entity.y] == GRASS)){

              map[bomb->entity.x - x][bomb->entity.y] = GRASS;
              bomb->explosion.horizontalB = bomb->entity.x - x;
            }
          else
            stopHorizontalB = true;
      }
      x++;

    }
    while(y<=bomb->radius){
      if(!stopVerticalB || !stopVerticalF){
        if(!stopVerticalF && (map[bomb->entity.x][bomb->entity.y + y] == BOX
        || map[bomb->entity.x][bomb->entity.y + y] == GRASS)){

            map[bomb->entity.x][bomb->entity.y + y] = GRASS;
            bomb->explosion.verticalF = bomb->entity.y + y;
          }
        else
          stopVerticalF = true;

        if(!stopVerticalB && (map[bomb->entity.x][bomb->entity.y - y] == BOX
        || map[bomb->entity.x][bomb->entity.y - y] == GRASS)){

              map[bomb->entity.x][bomb->entity.y - y] = GRASS;
              bomb->explosion.verticalB = bomb->entity.y - y;
            }
          else
            stopVerticalB = true;
      }
      y++;

    }

}

void CreateExplosion(BOMBS bomb, EXPLOSION* explosion){
    explosion->entity.x = bomb.entity.x;
    explosion->entity.y = bomb.entity.y;
    explosion->currFrame = 0;
    explosion->isLive = true;
}
void UpdateExplosion(BOMBS bombs[5]){

  int i = 0;
    while(i<5){
      if(bombs[i].explosion.isLive){
        if((bombs[i].explosion.currDelay)++ >= bombs[i].explosion.frameDelay){

          bombs[i].explosion.currDelay = 0;//Time to update frame

          if(++(bombs[i].explosion.currFrame) > bombs[i].explosion.maxFrame)//Updates the frame
              bombs[i].explosion.isLive = false;
          }
      }
      i++;
    }
}

void DrawExplosion(BOMBS bombs[5]){
  int i = 0;
  int drawArms = 1;
    while(i<5){
      if(bombs[i].explosion.isLive){
        //Center of the bomb
        al_draw_tinted_scaled_rotated_bitmap_region(bombs[i].explosion.entity.sprite, bombs[i].explosion.currFrame*48, 0, 48, 48, al_map_rgb_f(1.0, 1.0, 1.0),
         0, 0, bombs[i].explosion.entity.x*32, bombs[i].explosion.entity.y*32, 0.66, 0.66, 0, 0);

         //Right Arm
         if(bombs[i].explosion.horizontalF != bombs[i].explosion.entity.x){

           while(bombs[i].explosion.horizontalF >=  bombs[i].explosion.entity.x + drawArms){
              //End of the arm
             if(bombs[i].explosion.horizontalF ==  bombs[i].explosion.entity.x + drawArms){
               al_draw_tinted_scaled_rotated_bitmap_region(bombs[i].explosion.entity.sprite, bombs[i].explosion.currFrame*48, 2*48, 48, 48, al_map_rgb_f(1.0, 1.0, 1.0),
                0, 0, (bombs[i].explosion.entity.x + drawArms)*32, bombs[i].explosion.entity.y*32, 0.66, 0.66, 0, 0);
               break;
             }
             al_draw_tinted_scaled_rotated_bitmap_region(bombs[i].explosion.entity.sprite, bombs[i].explosion.currFrame*48, 48, 48, 48, al_map_rgb_f(1.0, 1.0, 1.0),
              0, 0, (bombs[i].explosion.entity.x + drawArms)*32, bombs[i].explosion.entity.y*32, 0.66, 0.66, 0, 0);
              drawArms++;
           }
          drawArms = 1;

        }

        //Left Arm
        if(bombs[i].explosion.horizontalB !=  bombs[i].explosion.entity.x){

         while(bombs[i].explosion.horizontalB <=  bombs[i].explosion.entity.x - drawArms){
            //End of the arm
           if(bombs[i].explosion.horizontalB ==  bombs[i].explosion.entity.x - drawArms){
             al_draw_tinted_scaled_rotated_bitmap_region(bombs[i].explosion.entity.sprite, bombs[i].explosion.currFrame*48, 2*48, 48, 48, al_map_rgb_f(1.0, 1.0, 1.0),
              48,48, (bombs[i].explosion.entity.x - drawArms)*32,bombs[i].explosion.entity.y*32, 0.66, 0.66, 3.1415, 0);
             break;
           }
           al_draw_tinted_scaled_rotated_bitmap_region(bombs[i].explosion.entity.sprite, bombs[i].explosion.currFrame*48, 48, 48, 48, al_map_rgb_f(1.0, 1.0, 1.0),
            48, 48, (bombs[i].explosion.entity.x - drawArms)*32, bombs[i].explosion.entity.y*32, 0.66, 0.66, 3.1415, 0);
            drawArms++;
         }
       }
       drawArms = 1;

       //Upper Arm
       if(bombs[i].explosion.verticalB !=  bombs[i].explosion.entity.y){
       while(bombs[i].explosion.verticalB <=  bombs[i].explosion.entity.y - drawArms){
          //End of the arm
         if(bombs[i].explosion.verticalB ==  bombs[i].explosion.entity.y - drawArms){
           al_draw_tinted_scaled_rotated_bitmap_region(bombs[i].explosion.entity.sprite, bombs[i].explosion.currFrame*48, 2*48, 48, 48, al_map_rgb_f(1.0, 1.0, 1.0),
            48,0, bombs[i].explosion.entity.x*32,(bombs[i].explosion.entity.y - drawArms)*32, 0.66, 0.66, 3.1415/2*3, 0);
           break;
         }
         al_draw_tinted_scaled_rotated_bitmap_region(bombs[i].explosion.entity.sprite, bombs[i].explosion.currFrame*48, 48, 48, 48, al_map_rgb_f(1.0, 1.0, 1.0),
          48, 0, bombs[i].explosion.entity.x*32, (bombs[i].explosion.entity.y - drawArms)*32, 0.66, 0.66, 3.1415/2*3, 0);
          drawArms++;
       }
     }
     drawArms = 1;
     //Down
     if(bombs[i].explosion.verticalF !=  bombs[i].explosion.entity.y){
     while(bombs[i].explosion.verticalF >=  bombs[i].explosion.entity.y + drawArms){
        //End of the arm
       if(bombs[i].explosion.verticalF ==  bombs[i].explosion.entity.y + drawArms){
         al_draw_tinted_scaled_rotated_bitmap_region(bombs[i].explosion.entity.sprite, bombs[i].explosion.currFrame*48, 2*48, 48, 48, al_map_rgb_f(1.0, 1.0, 1.0),
          0,48, bombs[i].explosion.entity.x*32,(bombs[i].explosion.entity.y + drawArms)*32, 0.66, 0.66, 3.1415/2, 0);
         break;
       }
       al_draw_tinted_scaled_rotated_bitmap_region(bombs[i].explosion.entity.sprite, bombs[i].explosion.currFrame*48, 48, 48, 48, al_map_rgb_f(1.0, 1.0, 1.0),
        0, 49, bombs[i].explosion.entity.x*32, (bombs[i].explosion.entity.y + drawArms)*32, 0.66, 0.66, 3.1415/2, 0);
        drawArms++;
     }
   }








      }i++;
    }
}
