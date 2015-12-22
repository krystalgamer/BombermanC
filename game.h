#include "incs.h"

#define TILE_SIZE 16
#define MAX_BOMBS 1
#define MAX_TIME 93


FILE* log;

typedef enum{
  GRASS,
  BLOCK,
  WALL,
  BOMB,
  BOX
}TILES;

//Entities
typedef struct _Entity{
  int x;
  int y;
  ALLEGRO_BITMAP* sprite;
}ENTITY;

typedef struct _Explosion{
  ENTITY entity;
  short radius;
  short currFrame;
  short currDelay;
  short frameDelay;
  short maxFrame;
  bool isLive;
}EXPLOSION;

typedef struct _Bomb{
  ENTITY entity;
  EXPLOSION  explosion;
  short maxTime;
  short currTime;
  short radius;
  bool isLive;

}BOMBS;

typedef struct _Player{
  ENTITY entity;
  BOMBS bombs[5];
  short maxBombs;
}PLAYER;





void TryToMovePlayer(ENTITY *player,int key, TILES map[15][13],PLAYER* pl);
void MoveHorizontal(ENTITY* player,bool forward, TILES map[15][13]);
void MoveVertical(ENTITY* player,bool forward, TILES map[15][13]);

void CreateMap(TILES map[15][13]);//Creates the map
void DrawMap(TILES map[15][13],ALLEGRO_BITMAP* tileMap); //Draws Map

void InitBombs(BOMBS bombs[5],ALLEGRO_BITMAP* bombSprite,ALLEGRO_BITMAP* expSprite);
void PlaceBomb(PLAYER* player, TILES map[15][13]);
void DrawBomb(BOMBS bombs[5]);
void UpdateBomb(BOMBS bombs[5],TILES map[15][13]);
void ExplodeBomb(BOMBS bomb,TILES map[15][13]);

void CreateExplosion(BOMBS bomb, EXPLOSION* explosion);
void UpdateExplosion(BOMBS bombs[5]);
void DrawExplosion(BOMBS bombs[5]);
