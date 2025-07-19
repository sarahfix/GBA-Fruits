
#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
// Include any header files for title screen or exit
#include "images/title.h"
#include "images/win.h"
#include "images/gameover.h"
#include "images/player.h"
#include "images/collectible.h"


// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  PLAY,
  WIN,
  LOSE,
} state;

//int score;
//int timerCountdown;
//int framesCounter;

Player gameplayer;

int main(void) {
  initialize();

  while (1) {
      previousButtons = currentButtons;
      currentButtons = BUTTONS;

      switch (state) {
          case START:
              start();
              break;
          case PLAY:
              play();
              break;
          case WIN:
              winState();
              break;
          case LOSE:
              gameoverState();
              break;
      }
    }
    return 0;
}

// set up GBA
void initialize(void) {
  REG_DISPCNT = MODE3 | BG2_ENABLE;
  currentButtons = BUTTONS;
  previousButtons = currentButtons;

  goToStart();
}

void goToStart(void) {
  drawFullScreenImageDMA(title);
  //drawRotatedImageDMA(20, 30, 40, 40, title, 90); // Rotates 90° clockwise
  drawRectDMA(0, 0, 240, 10, WHITE);
  state = START;
}

void start(void) {
  waitForVBlank();
  
  if(textX < 190) {
    // making animated text
    drawRectDMA(0, textX, 51, 10, WHITE);
    drawString(0, textX, "Have fun!", MAGENTA);
    textX++;
  } else if (textX >= 190) {
    textX = -1;
    drawRectDMA(0, 0, 240, 10, WHITE);
    drawString(0, textX, "Have fun!", MAGENTA);
    //textX++;
  } 
  if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
    initializeGame();
    goToPlay();
  }
}

void initializeGame(void) {
  // Initialize game
  gameplayer.width = 16;
  gameplayer.height = 16;
  gameplayer.x = WIDTH/2 - 8;
  gameplayer.y = HEIGHT - 30;
  gameplayer.oldx = gameplayer.x;
  gameplayer.oldy = gameplayer.y;
  gameplayer.image = player;
  
  score = 0;
  time = 0;
  timerCountdown = 50;
  framesCounter = 60;
  
  // Initialize slices
  collectibles.count = 0;
  collectibles.spawnTimer = 60; // Spawn every second
}

void goToPlay(void) {
  fillScreenDMA(BLACK);
  state = PLAY;
}

void spawnCollectible(void) {
  if (collectibles.count < MAX_COLLECTIBLES) {
    Collectible* c = &collectibles.items[collectibles.count];
    c->x = randint(0, WIDTH - 8);
    c->y = -8;
    c->width = 8;
    c->height = 8;
    c->active = 1;
    c->image = collectible;
    collectibles.count++;
  }
}

int checkCollision(Player p, Collectible c) {
  return p.x < c.x + c.width && p.x + p.width > c.x && p.y < c.y + c.height && p.y + p.height > c.y;
}

void play(void) {
  //fillScreenDMA(BLACK);

  // moving player
  gameplayer.oldx = gameplayer.x;
  gameplayer.oldy = gameplayer.y;
  if (KEY_DOWN(BUTTON_UP, currentButtons) && gameplayer.y > 0) {
    gameplayer.y -= 2;
  }
  if (KEY_DOWN(BUTTON_DOWN, currentButtons) && gameplayer.y < HEIGHT - gameplayer.height) {
    gameplayer.y += 2;
  }
  if (KEY_DOWN(BUTTON_LEFT, currentButtons) && gameplayer.x > 0) {
    gameplayer.x -= 2;
  }
  if (KEY_DOWN(BUTTON_RIGHT, currentButtons) && gameplayer.x < WIDTH - gameplayer.width) {
    gameplayer.x += 2;
  }

  // slice spawning
  if (--collectibles.spawnTimer <= 0) {
    spawnCollectible();
    collectibles.spawnTimer = 60;
  }

  // Update existing slices
  for (int i = 0; i < collectibles.count; i++) {
    if (collectibles.items[i].active) {
      Collectible* c = &collectibles.items[i];
      if (c->active) {
          c->oldy = c->y;
          c->y += 1;
          
          if (checkCollision(gameplayer, *c)) {
              score++;
              drawRectDMA(10, 50, 30, 10, BLACK); //fixes tearing w/ updated score
              c->active = 0;
              //remove by swapping with last
              drawRectDMA(c->oldy, c->x, c->width, c->height, BLACK);
              *c = collectibles.items[--collectibles.count];
              i--;
          } else if (c->y > HEIGHT) {
              c->active = 0;
              *c = collectibles.items[--collectibles.count];
              i--;
          }
      }
    }
  }
  
  // Update timer
  framesCounter--;
  if (framesCounter <= 0) {
      framesCounter = 60;
      timerCountdown--;
      time++;
      if (timerCountdown <= 0) {
          state = LOSE;
      }
  }

  waitForVBlank();

  //fillScreenDMA(BLACK);

  // draw active slices
  for (int i = 0; i < collectibles.count; i++) {
    Collectible* c = &collectibles.items[i];
    if (c->active) {
        drawRectDMA(c->oldy, c->x, c->width, c->height, BLACK);
        drawImageDMA(c->y, c->x, c->width, c->height, c->image);
    }
  }
  //erase old watermelon
  drawRectDMA(gameplayer.oldy, gameplayer.oldx, gameplayer.width, gameplayer.height, BLACK);
  //draw watermelon
  drawImageDMA(gameplayer.y, gameplayer.x, gameplayer.width, gameplayer.height, gameplayer.image);

  //draw score
  snprintf(buffer, sizeof(buffer), "Score: %d", score);
  drawString(10, 10, buffer, WHITE);

  if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){
    goToStart();
  }
  // Win condition
  if (score >= 20) {
    goToWin();
  } else if (timerCountdown <= 0) {
    goToGameover();
  }
}


void goToWin(void) {
  drawFullScreenImageDMA(win);
  snprintf(buffer, sizeof(buffer), "Time Elapsed: %d secs", time);
  drawString(130, 53, buffer, BLACK);
  waitForVBlank();
  state = WIN;
}

void winState(void) {
  waitForVBlank();
  if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){
    goToStart();
  }
}

void goToGameover(void) {
  drawFullScreenImageDMA(gameover);
  waitForVBlank();
  state = LOSE;
}

void gameoverState(void) {
  waitForVBlank();
  if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){
    goToStart();
  }
}