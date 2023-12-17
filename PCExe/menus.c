#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#define MAXX 128
#define MAXY 64

#define LANGUAGE EN

#if(LANGUAGE == EN)
#define PLAY "Play"
#define BACK "Back"
#define SLEEP "Sleep mode"
#define RESTART "New game"
#define PLAYER1WIN "Player 1 wins!"
#define PLAYER2WIN "Player 2 wins!"
#define NOPLAYERWIN "It's a tie!"
#endif
#if(LANGUAGE == CZ)
#define PLAY "Hrat"
#define BACK "Zpet"
#define SLEEP "Spat"
#define RESTART "Nova hra"
#define PLAYER1WIN "Hrac 1 vyhrava!"
#define PLAYER2WIN "Hrac 2 vyhrava!"
#define NOPLAYERWIN "Remiza"
#endif

#define ARCADENAME "testname"
#define SNAKENAME "Double Slither"
#define FROGNAME "Hop O!"
#define PONGNAME "Pong"

typedef struct menuButton{
    char text[16];
    uint16_t startX;
    uint16_t startY;
    uint16_t width;
    uint16_t height;
} button;
typedef struct userMenu{
    char menuName[16];
    button buttons[3];
} menu;
typedef struct deathScreen{
    char deathMessage[32];
    button restartButton;
    button backButton;
} death;

menu menuScreen;
death deathScreen;

void mennuButtonPos(button buttonT, uint16_t startXT, uint16_t startYT, uint16_t widthT, uint16_t heightT){
    buttonT.startX = startXT;
    buttonT.startY = startXT;
    buttonT.width = widthT;
    buttonT.height = heightT;
}

void setButton(button buttonT, char* nameT){
    strcpy(buttonT.text,nameT);
}

#define setMenu(gameName, button1Name, button2Name, button3Name) \
    strcpy(menuScreen.menuName,gameName);\
    setButton(menuScreen.buttons[0], button1Name);\
    setButton(menuScreen.buttons[1], button2Name);\
    setButton(menuScreen.buttons[2], button3Name);
#define setDeathMessage(dMessage) strcpy(deathScreen.deathMessage,dMessage);

int main(){
    //menu screen
    //setup
    mennuButtonPos(menuScreen.buttons[0], 43*MAXX/128, 28*MAXY/64, 43, 13);
    mennuButtonPos(menuScreen.buttons[1], 43*MAXX/128, 16*MAXY/64, 43, 13);
    mennuButtonPos(menuScreen.buttons[2], 43*MAXX/128, 4*MAXY/64, 43, 13);
    //main menu
    setMenu(ARCADENAME,SNAKENAME,FROGNAME,SLEEP)
    //snake menu
    setMenu(SNAKENAME,PLAY,BACK,SLEEP)
    //frog menu
    setMenu(FROGNAME,PLAY,BACK,SLEEP)
    //pong menu
    setMenu(PONGNAME,PLAY,BACK,SLEEP)
    //
    //death screen
    //setup
    setButton(deathScreen.restartButton, RESTART);
    setButton(deathScreen.backButton, BACK);
    mennuButtonPos(deathScreen.restartButton, 43*MAXX/128, 39*MAXY/64 , 43, 13);
    mennuButtonPos(deathScreen.backButton, 43*MAXX/128, 22*MAXY/64 , 43, 13);
    //player 1 win
    setDeathMessage(PLAYER1WIN)
    //player 2 win
    setDeathMessage(PLAYER2WIN)
    //no player win
    setDeathMessage(NOPLAYERWIN)
    return 0;
}