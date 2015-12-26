#include "game.h"

/*

BOMB PART

*/
void InitBombs(BOMBS bombs[5],ALLEGRO_BITMAP* bombSprite,ALLEGRO_BITMAP* expSprite, bool first){
  int i = 0;
  while(i<5){
    bombs[i].isLive = bombs[i].explosion.isLive = false;
    bombs[i].maxTime = MAX_TIME;
    bombs[i].currTime = 0;
    bombs[i].radius = bombs[i].explosion.radius = 2;
    if(first){
      bombs[i].explosion.entity.sprite = expSprite;
      bombs[i].entity.sprite = bombSprite;
    }
    bombs[i].explosion.frameDelay = 1;
    bombs[i].explosion.maxFrame = 6;
    bombs[i].explosion.currFrame = bombs[i].explosion.currDelay = 0;
    i++;
  }
}

void PlaceBomb(PLAYER* player, TILES map[15][13]){
  int i=0,j = 0;
  while(i<5){
    if(!(player->bombs[i].isLive)){
      while(j<5){
        if((player->bombs[j].isLive) && player->bombs[j].entity.x == player->entity.x &&
      player->bombs[j].entity.y == player->entity.y)
      {return;}
      j++;

    }
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
void UpdateBomb(BOMBS bombs[5],TILES map[15][13],PLAYER* player){
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
        ExplodeBomb(&bombs[i],map,player);
      }
    }
    i++;
  }
}
void ExplodeBomb(BOMBS *bomb,TILES map[15][13], PLAYER* player){

    bool stopVerticalF = false, stopHorizontalF = false,
    stopVerticalB = false, stopHorizontalB = false;

    int x = 1,y = 1,i = 0;
    bomb->explosion.horizontalF = bomb->explosion.horizontalB = bomb->entity.x;
    bomb->explosion.verticalF = bomb->explosion.verticalB = bomb->entity.y;

    while(x<=bomb->radius){
      if(!stopHorizontalB || !stopHorizontalF){

        if(!stopHorizontalF && (map[bomb->entity.x + x][bomb->entity.y] == BOX
        || map[bomb->entity.x + x][bomb->entity.y] == GRASS)){

          if(map[bomb->entity.x + x][bomb->entity.y] == BOX)
            stopHorizontalF = true;

            map[bomb->entity.x + x][bomb->entity.y] = GRASS;
            bomb->explosion.horizontalF = bomb->entity.x + x;

          }
          else if(!stopHorizontalF && map[bomb->entity.x + x][bomb->entity.y] == BOMB){
              i = 0;
              while(i<5){
                if(player->bombs[i].isLive)
                {

                  if(player->bombs[i].entity.x == bomb->entity.x + x &&
                    player->bombs[i].entity.y == bomb->entity.y){
                      player->bombs[i].currTime = player->bombs[i].maxTime;
                      map[bomb->entity.x + x][bomb->entity.y] = GRASS;
                      UpdateBomb(&(player->bombs[i]), map, player);
                      break;
                    }

                }
                i++;
              }
              stopHorizontalF = true;

          }
        else
          stopHorizontalF = true;

        if(!stopHorizontalB && (map[bomb->entity.x - x][bomb->entity.y] == BOX
        || map[bomb->entity.x - x][bomb->entity.y] == GRASS)){

              if(map[bomb->entity.x - x][bomb->entity.y] == BOX)
                stopHorizontalB = true;
              map[bomb->entity.x - x][bomb->entity.y] = GRASS;
              bomb->explosion.horizontalB = bomb->entity.x - x;

        }
        else if(!stopHorizontalB && map[bomb->entity.x - x][bomb->entity.y] == BOMB){
            i = 0;
            while(i<5){
              if(player->bombs[i].isLive)
              {

                if(player->bombs[i].entity.x == bomb->entity.x - x &&
                  player->bombs[i].entity.y == bomb->entity.y){
                    player->bombs[i].currTime = player->bombs[i].maxTime;
                    map[bomb->entity.x - x][bomb->entity.y] = GRASS;
                    UpdateBomb(&(player->bombs[i]), map, player);
                    break;
                  }

              }
              i++;
            }
            stopHorizontalB = true;

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

            if(map[bomb->entity.x][bomb->entity.y + y] == BOX)
              stopVerticalF = true;
            map[bomb->entity.x][bomb->entity.y + y] = GRASS;
            bomb->explosion.verticalF = bomb->entity.y + y;

          }
          else if(!stopVerticalF && map[bomb->entity.x][bomb->entity.y + y] == BOMB){
              i = 0;
              while(i<5){
                if(player->bombs[i].isLive)
                {

                  if(player->bombs[i].entity.x == bomb->entity.x &&
                    player->bombs[i].entity.y == bomb->entity.y + y){
                      player->bombs[i].currTime = player->bombs[i].maxTime;
                      map[bomb->entity.x][bomb->entity.y + y] = GRASS;
                      UpdateBomb(&(player->bombs[i]), map, player);
                      break;
                    }

                }
                i++;
              }
              stopVerticalF = true;

          }
        else
          stopVerticalF = true;

        if(!stopVerticalB && (map[bomb->entity.x][bomb->entity.y - y] == BOX
        || map[bomb->entity.x][bomb->entity.y - y] == GRASS)){


            if(map[bomb->entity.x][bomb->entity.y - y] == BOX)
                  stopVerticalB = true;
              map[bomb->entity.x][bomb->entity.y - y] = GRASS;
              bomb->explosion.verticalB = bomb->entity.y - y;
            }
            else if(!stopVerticalB && map[bomb->entity.x][bomb->entity.y - y] == BOMB){
                i = 0;
                while(i<5){
                  if(player->bombs[i].isLive)
                  {

                    if(player->bombs[i].entity.x == bomb->entity.x &&
                      player->bombs[i].entity.y == bomb->entity.y - y){
                        player->bombs[i].currTime = player->bombs[i].maxTime;
                        map[bomb->entity.x][bomb->entity.y - y] = GRASS;
                        UpdateBomb(&(player->bombs[i]), map, player);
                        break;
                      }

                  }
                  i++;
                }
                stopVerticalB = true;

            }
          else
            stopVerticalB = true;
      }
      y++;

    }
    CheckIfAlive(player, bomb->explosion);

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
        drawArms = 1;
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

        }

        //Left Arm
        if(bombs[i].explosion.horizontalB !=  bombs[i].explosion.entity.x){
            drawArms = 1;
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

       //Upper Arm
       if(bombs[i].explosion.verticalB !=  bombs[i].explosion.entity.y){
         drawArms = 1;
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

     //Down
     if(bombs[i].explosion.verticalF !=  bombs[i].explosion.entity.y){
       drawArms = 1;
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
