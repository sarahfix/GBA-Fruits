#ifndef MAIN_H
#define MAIN_H
#define MAX_COLLECTIBLES 10

#include "gba.h"

// TODO: Create any necessary structs
// the watermelon
typedef struct {
    int x, y;
    int oldx, oldy;
    int width, height;
    const u16* image;
} Player;

// a slice
typedef struct {
    int x, y;
    int oldx, oldy;
    int width, height;
    int active;
    const u16* image;
} Collectible;

// the slices
typedef struct {
    Collectible items[MAX_COLLECTIBLES];
    int count;
    int spawnTimer;
} CollectibleSystem;
CollectibleSystem collectibles;

int score;
int time;
int textX;
int timerCountdown;
int framesCounter;

// moved from main.c
u32 currentButtons;
u32 previousButtons;

//enum gba_state state = START;
char buffer[50]; // for dynamic texts

void initialize(void);
void goToStart(void);
void start(void);
void initializeGame(void);
void goToPlay(void);
void play(void);
void goToWin(void);
void winState(void);
void goToGameover(void);
void gameoverState(void);
void spawnCollectible(void); 
int checkCollision(Player p, Collectible c);

#endif
