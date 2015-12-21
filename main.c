#include "game.h"

int main(){

  al_init();
  al_init_image_addon();
  al_install_keyboard();


  TILES map[15][13];
  ALLEGRO_DISPLAY* display;
  ALLEGRO_BITMAP* tileMap;
  ALLEGRO_EVENT_QUEUE* eventQueue;
  ALLEGRO_TIMER* drawTimer;

  eventQueue = al_create_event_queue();
  drawTimer = al_create_timer(1/60.0);

  PLAYER player;
  player.entity.x = 1;
  player.entity.y = 1;
  player.entity.sprite = al_load_bitmap("./player.png");
  ALLEGRO_BITMAP* bombSprite = al_load_bitmap("./coise.png");
  al_convert_mask_to_alpha(bombSprite, al_get_pixel(bombSprite, 0, 0));
  player.maxBombs = MAX_BOMBS;
  al_convert_mask_to_alpha(player.entity.sprite, al_map_rgb(255,0,255));

  display = al_create_display(480,416);
  tileMap = al_load_bitmap("./tiles2.png");
  srand(time(NULL));
  CreateMap(map);

  al_register_event_source(eventQueue, al_get_timer_event_source(drawTimer));
  al_register_event_source(eventQueue, al_get_keyboard_event_source());
  al_start_timer(drawTimer);
  bool redraw = false;

  InitBombs(player.bombs,bombSprite);

  while(1){
    while(!al_event_queue_is_empty(eventQueue)){
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        switch(event.type){

          case ALLEGRO_EVENT_TIMER:
                redraw = true;
                UpdateBomb(player.bombs, map);
                break;
          case ALLEGRO_EVENT_KEY_DOWN:
                TryToMovePlayer(&(player.entity),event.keyboard.keycode,map,&player);
                break;

        }

    }
    if(redraw){
      redraw = false;
      DrawMap(map,tileMap);
      DrawBomb(player.bombs);
      al_draw_scaled_bitmap(player.entity.sprite, 0, 0, 16, 16, player.entity.x*32, player.entity.y*32, 32, 32, 0);
      al_flip_display();
    }

  }

  al_rest(900);
  return 0;

}
