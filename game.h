#include "incs.h"

#define TILE_SIZE 16
#define MAX_BOMBS 1
#define MAX_TIME 93

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

typedef struct _Bomb{
  ENTITY entity;
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

void InitBombs(BOMBS bombs[5],ALLEGRO_BITMAP* bombSprite);
void PlaceBomb(PLAYER* player, TILES map[15][13]);
void DrawBomb(BOMBS bombs[5]);
void UpdateBomb(BOMBS bombs[5],TILES map[15][13]);
void ExplodeBomb(BOMBS bomb,TILES map[15][13]);
