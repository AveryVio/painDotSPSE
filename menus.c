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
#endif
#if(LANGUAGE == CZ)
#define PLAY "Hrat"
#define BACK "Zpet"
#define SLEEP "Spat"
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

menu mainScreen;
menu snakeScreen;
menu frogScreen;
menu pongScreen;

void setButton(button buttonT, char* nameT, uint16_t startXT, uint16_t startYT, uint16_t widthT, uint16_t heightT){
    strcpy(buttonT.text,nameT);
    buttonT.startX = startXT;
    buttonT.startY = startXT;
    buttonT.width = widthT;
    buttonT.height = heightT;
}

#define setMenu(menuNameref, button1ref, button2ref, button3ref, gameName, button1Name, button2Name, button3Name) \
    strcpy(menuNameref,gameName);\
    setButton(button1ref, button1Name, 43*MAXX/128, 4*MAXY/128, 43, 13);\
    setButton(button2ref, button2Name, 43*MAXX/128, 16*MAXY/128, 43, 13);\
    setButton(button3ref, button3Name, 43*MAXX/128, 28*MAXY/128, 43, 13);

int main(){
    //main menu
    setMenu(mainScreen.menuName,mainScreen.buttons[0],mainScreen.buttons[1],mainScreen.buttons[2],ARCADENAME,SNAKENAME,FROGNAME,SLEEP)
    //snake menu
    setMenu(snakeScreen.menuName,snakeScreen.buttons[0],snakeScreen.buttons[1],snakeScreen.buttons[2],SNAKENAME,PLAY,BACK,SLEEP)
    //frog menu
    setMenu(frogScreen.menuName,frogScreen.buttons[0],frogScreen.buttons[1],frogScreen.buttons[2],SNAKENAME,PLAY,BACK,SLEEP)
    //pong menu
    setMenu(pongScreen.menuName,pongScreen.buttons[0],pongScreen.buttons[1],pongScreen.buttons[2],SNAKENAME,PLAY,BACK,SLEEP)
    return 0;
}