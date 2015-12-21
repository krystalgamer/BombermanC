#include "game.h"

void CreateMap(TILES map[15][13]){

    for(int x = 0;x<15;x++){
      for(int y = 0;y<13;y++){
        if(!y || !x || x == 14 || y == 12)//Create Walls
          map[x][y] = WALL;
        else if(x%2 == 0 && y%2 == 0)//Intermediate Walls
          map[x][y] = BLOCK;
        else{//Terrain generation
          if(x == 1 && y == 1){
            map[x][y] = GRASS;
            continue;
          }
        map[x][y] = (rand()%3)==2?BOX:GRASS;

        }

      }
    }
}
void DrawMap(TILES map[15][13],ALLEGRO_BITMAP* tileMap){
  for(int x = 0;x<15;x++){
    for(int y = 0;y<13;y++){
      al_draw_tinted_scaled_rotated_bitmap_region(tileMap, map[x][y]*16, 0, 16, 16, al_map_rgb_f(1.0, 1.0, 1.0),
       0, 0, x*32, y*32, 2.0, 2.0, 0, 0);
     }
   }
}
