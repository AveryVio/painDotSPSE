////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//included libraries
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <inttypes.h>
#include <string.h>
//#include <cstring>
#include <Windows.h>//for windows console
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CZ 0
#define EN 1
#define LANGUAGE EN

#if(LANGUAGE == EN)
    #define PLAY "Play"
    #define BACK "Back"
    #define SLEEP "Sleep mode"
    #define RESTART "New game"
    #define PLAYER1WIN "Player 1 wins!"
    #define PLAYER2WIN "Player 2 wins!"
    #define NOPLAYERWIN "It's a tie!"
#elif(LANGUAGE == CZ)
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//definitions for usefull to update stuff
#define MAXX 32
#define MAXY 16
#define MAXSNAKELENGTH 256
#define SNAKESTARTLENGTH 3
#define FOODRANDCALC (2 * (rand() % 1)) + (rand() % 2) + (rand() % 3)
//variables for state management
bool gameON;
char gameChioce;
//variables for preformance increases
char snakecheck12Result;
char snakecheck21Result;
char snake1movecheckResult;
char snake2movecheckResult;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄    ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄   ▄▄▄▄▄▄ ▄▄▄     //////////////////////////////////////////
/////////////////////////////█       █       █  █  █ █       █   ▄  █ █      █   █    //////////////////////////////////////////
/////////////////////////////█   ▄▄▄▄█    ▄▄▄█   █▄█ █    ▄▄▄█  █ █ █ █  ▄   █   █    //////////////////////////////////////////
/////////////////////////////█  █  ▄▄█   █▄▄▄█       █   █▄▄▄█   █▄▄█▄█ █▄█  █   █    //////////////////////////////////////////
/////////////////////////////█  █ █  █    ▄▄▄█  ▄    █    ▄▄▄█    ▄▄  █      █   █▄▄▄ //////////////////////////////////////////
/////////////////////////////█  █▄▄█ █   █▄▄▄█ █ █   █   █▄▄▄█   █  █ █  ▄   █       █//////////////////////////////////////////
/////////////////////////////█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄█  █▄▄█▄▄▄▄▄▄▄█▄▄▄█  █▄█▄█ █▄▄█▄▄▄▄▄▄▄█//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void * Memcpy(void* dst, const void* src, unsigned int cnt){
    char *pszDest = (char *)dst;
    const char *pszSource =( const char*)src;
    if((pszDest!= NULL) && (pszSource!= NULL)){
        while(cnt){
            *(pszDest++)= *(pszSource++);
            --cnt;
        }
        *pszDest = '\0';
    }
    return dst;
}
char textlen(char* textIn){
    char len = 0;
    for(;(*textIn); textIn++) len++;
    return len;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// ▄▄   ▄▄ ▄▄▄▄▄▄▄ ▄▄    ▄ ▄▄   ▄▄ /////////////////////////////////////////////////////
//////////////////////////////////////////█  █▄█  █       █  █  █ █  █ █  █/////////////////////////////////////////////////////
//////////////////////////////////////////█       █    ▄▄▄█   █▄█ █  █ █  █/////////////////////////////////////////////////////
//////////////////////////////////////////█       █   █▄▄▄█       █  █▄█  █/////////////////////////////////////////////////////
//////////////////////////////////////////█       █    ▄▄▄█  ▄    █       █/////////////////////////////////////////////////////
//////////////////////////////////////////█ ██▄██ █   █▄▄▄█ █ █   █       █/////////////////////////////////////////////////////
//////////////////////////////////////////█▄█   █▄█▄▄▄▄▄▄▄█▄█  █▄▄█▄▄▄▄▄▄▄█/////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct menuButton{
    char text[16];
    uint16_t startX;
    uint16_t startY;
    uint16_t width;
    uint16_t height;
} button;
typedef struct userMenu{
    char menuName[16];
    button primaryButton;
    button secondaryButton;
    button ternaryButton;
    uint8_t selected;
} menu;
typedef struct deathScreen{
    char deathMessage[32];
    button restartButton;
    button backButton;
    uint8_t selected;
} death;

menu menuScreen;
death deathScreen;

void ButtonPos(button* buttonT, uint16_t startXT, uint16_t startYT, uint16_t widthT, uint16_t heightT){
    buttonT->startX = startXT;
    buttonT->startY = startXT;
    buttonT->width = widthT;
    buttonT->height = heightT;
}

void setButton(button *buttonT, const char* nameT){
    Memcpy(buttonT->text,nameT,sizeof(nameT) * 4);
}

void setMenu(const char* gameName, const char* button1Name, const char* button2Name, const char* button3Name){
    Memcpy(menuScreen.menuName,gameName,sizeof(gameName) * 5);
    setButton(&menuScreen.primaryButton, button1Name);
    setButton(&menuScreen.secondaryButton, button2Name);
    setButton(&menuScreen.ternaryButton, button3Name);
}
void setDeathMessage(const char* dMessage){
    Memcpy(deathScreen.deathMessage,dMessage,sizeof(dMessage) * 5);
}
void updateMenu(const char* gameName, const char* button1Name, const char* button2Name, const char* button3Name){
    Memcpy(menuScreen.menuName,gameName,sizeof(gameName) * 5);
    setButton(&menuScreen.primaryButton, button1Name);
    setButton(&menuScreen.secondaryButton, button2Name);
    setButton(&menuScreen.ternaryButton, button3Name);
    ButtonPos(&menuScreen.primaryButton, 43*MAXX/128, 28*MAXY/64, 43*MAXX/128, 13*MAXY/64);
    ButtonPos(&menuScreen.secondaryButton, 43*MAXX/128, 16*MAXY/64, 43*MAXX/128, 13*MAXY/64);
    ButtonPos(&menuScreen.ternaryButton, 43*MAXX/128, 4*MAXY/64, 43*MAXX/128, 13*MAXY/64);
}

void innitMenus(){
    //menu screen
    setMenu(ARCADENAME,SNAKENAME,FROGNAME,SLEEP);
    ButtonPos(&menuScreen.primaryButton, 43*MAXX/128, 28*MAXY/64, 43*MAXX/128, 13*MAXY/64);
    ButtonPos(&menuScreen.secondaryButton, 43*MAXX/128, 16*MAXY/64, 43*MAXX/128, 13*MAXY/64);
    ButtonPos(&menuScreen.ternaryButton, 43*MAXX/128, 4*MAXY/64, 43*MAXX/128, 13*MAXY/64);
    //main menu
    /*//snake menu
    setMenu(SNAKENAME,PLAY,BACK,SLEEP);
    //frog menu
    setMenu(FROGNAME,PLAY,BACK,SLEEP);
    //pong menu
    setMenu(PONGNAME,PLAY,BACK,SLEEP);*/
    //
    //death screen
    setButton(&deathScreen.restartButton, RESTART);
    setButton(&deathScreen.backButton, BACK);
    ButtonPos(&deathScreen.restartButton, 43*MAXX/128, 39*MAXY/64 , 43*MAXX/128, 13*MAXY/64);
    ButtonPos(&deathScreen.backButton, 43*MAXX/128, 22*MAXY/64 , 43*MAXX/128, 13*MAXY/64);
    //player 1 win
    setDeathMessage(PLAYER1WIN);
    //player 2 win
    /*setDeathMessage(PLAYER2WIN);
    //no player win
    setDeathMessage(NOPLAYERWIN);*/
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// ▄▄▄▄▄▄▄ ▄▄    ▄ ▄▄▄▄▄▄ ▄▄▄   ▄ ▄▄▄▄▄▄▄ /////////////////////////////////////////////////
///////////////////////////////////////█       █  █  █ █      █   █ █ █       █/////////////////////////////////////////////////
///////////////////////////////////////█  ▄▄▄▄▄█   █▄█ █  ▄   █   █▄█ █    ▄▄▄█/////////////////////////////////////////////////
///////////////////////////////////////█ █▄▄▄▄▄█       █ █▄█  █      ▄█   █▄▄▄ /////////////////////////////////////////////////
///////////////////////////////////////█▄▄▄▄▄  █  ▄    █      █     █▄█    ▄▄▄█/////////////////////////////////////////////////
/////////////////////////////////////// ▄▄▄▄▄█ █ █ █   █  ▄   █    ▄  █   █▄▄▄ /////////////////////////////////////////////////
///////////////////////////////////////█▄▄▄▄▄▄▄█▄█  █▄▄█▄█ █▄▄█▄▄▄█ █▄█▄▄▄▄▄▄▄█/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
Double The Length, Double the lag.

version: 0.0.2
usage compatibility: console

functionality information:
    game engine functional (probably)
    render options
        console(buggy, not fixing since it wont be in produced versions anyway)
        pure numbers
    input - not implemented
*/
//classes
class food{//class for food objects
    public:
        char x;
        char y;
        char nutrition;
        food(char x, char y, char val){// constructor for food
            x = x;
            y = y;
            nutrition = val;
        }
};
//class for snakes
class snake{
    public:
    char headposX;
    char headposY;
    char tailX[MAXSNAKELENGTH];
    char tailY[MAXSNAKELENGTH];
    char direction;
    char length;
    char lengthStored[5];
    snake(char snakenumber){// consstructor for snake
        if(snakenumber == 0) headposX = rand() % ((MAXX / 2) + 1);
        else headposX = (MAXX / 2) + rand() % ((MAXX / 2) + 1);
        headposY = ((MAXY + 1) / 8) + rand() % ((MAXY + 1) / 4);
        length = SNAKESTARTLENGTH;
        if(snakenumber == 0) direction = 0;
        else direction = 2;
        for (char i = 0; i <= 5; i++) lengthStored[i] = 0;
        if (snakenumber == 0){//snake1 tail
            for (char i = 0; i < length; i++) {
                tailX[i] = headposX;
                tailY[i] = headposY - i - 1;
            }
            return;
        }
        //snake2 tail
        for (char i = length - 1; i >= 0; i--) {
            tailX[i] = headposX;
            tailY[i] = headposY + i + 1;
        }
    }
    char movecheck(){// if snake can move if yes then 1 else 0
        if(direction == 0) if(headposY == MAXY + 1)return 0;
        if(direction == 1) if(headposX == MAXX + 1)return 0;
        if(direction == 2) if(headposY == 0)return 0;
        if(direction == 3) if(headposX == 0)return 0;
        return 1;
    }
    void addLength(){//ads length from stored length to snake
        tailX[length + 1] = tailX[length];
        tailY[length + 1] = tailY[length];
        length++;
        for (char i = 0; i < 4; i++) lengthStored[i] = lengthStored[i + 1];
        lengthStored[4] = 0;
    }
    void move(){//moves the snake
        if(((direction == 0) && (headposY + 1 != MAXY + 1))||((direction == 1) && (headposY + 1 != MAXX + 1))||((direction == 2) && (headposY - 1 != MAXY))||((direction == 3) && (headposY - 1 != MAXX))){//this is only for testing purposes
            if (lengthStored[0] != 0) addLength();
            //move tail
            for(char i = length - 1; i > 0; i--){
                tailX[i] = tailX[i-1];
                tailY[i] = tailY[i-1];
            }
            tailX[0] = headposX;
            tailY[0] = headposY;
            //move head
            if ((direction == 0) && (headposY != MAXY + 1)) headposY = headposY + 1;
            else if ((direction == 1) && (headposX != MAXX + 1)) headposX = headposX + 1;
            else if ((direction == 2) && (headposY != 0)) headposY = headposY - 1;
            else if ((direction == 3) && (headposX != 0)) headposX = headposX - 1;
        }
    }
    void changeDirection(char requestedDirection){
        if (requestedDirection != direction && (requestedDirection + 2) % 4 != direction) direction = requestedDirection;
    }
    char foodColiding();
    char firstStoredLength(){//returns higherst stored length
        for(char v = 5; v >= 0; v--) if(lengthStored[v] == 1) return v;
        return 0;
    }
    void snakeEat();
};
//objects
snake Snake1(0);//player 1
snake Snake2(1);//player 2
food foodblock(rand() % (MAXX + 1), rand() % (MAXY + 1), FOODRANDCALC);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char biggerSnakeLength(){//returns length of the bigger snake
    if(Snake1.length > Snake2.length) return Snake1.length;
    return Snake2.length;
}
char snake::foodColiding(){
    if (foodblock.x == headposX && foodblock.y == headposY) return 1;
    else for (int i = 0; i < length; i++) if(foodblock.x == tailX[i] && foodblock.y == tailY[i]) return 1;
    else return 0;
}
void regenFood() {//respawns food at another location
    do{
        foodblock.nutrition = (rand() % 1) + (rand() % 3) + (rand() % 1);
        foodblock.x = rand() % (MAXX + 1);
        foodblock.y = rand() % (MAXY + 1);
    } while(Snake1.foodColiding() || Snake2.foodColiding());
}
void snake::snakeEat(){//checks if snake can eat if yes, eats the whole food and respawns it
    if ((foodblock.x == headposX) && (foodblock.y == headposY)){
        for (char n = firstStoredLength(); n <= 5; n++){
            if(foodblock.nutrition > 0){
            lengthStored[n] = 1;
            foodblock.nutrition--;
        }
    }
    regenFood();
    }
}
char snakecheck(snake snakeN, snake snakeT){// if both colide then 2, if asked snake then 1 else 0
    //offset based on direction
    char dx = 0;
    char dy = 0;
    if (snakeN.direction == 0) dy = 1;
    else if (snakeN.direction == 1) dx = 1;
    else if (snakeN.direction == 2) dy = -1;
    else if (snakeN.direction == 3) dx = -1;
    //use offset
    int checkX = snakeN.headposX + dx;
    int checkY = snakeN.headposY + dy;
    //actual checking
    if (checkX == snakeT.headposX && checkY == snakeT.headposY) return 0;//if heads colide
    else if((checkX + dx == snakeT.headposX && checkY + dy == snakeT.headposY) && ((snakeN.direction % 2) == (snakeT.direction % 2))) return 0;//if snakes colide face to face (this is an edge case)
    else for (int i = 0; i < snakeT.length; i++) {//if head colides body
        if (checkX == snakeT.tailX[i] && checkY == snakeT.tailY[i]) return 0;
        else if (checkX == snakeN.tailX[i] && checkY == snakeN.tailY[i]) return 0;
    }
    return 1;
};
class gameInfo{// class of information for cloud backup
    public:
        uint32_t gemeid;
        char gamestate;
        char winner;
        snake winnerInfo;
        snake loserInfo;
        gameInfo(char gamestatep) : winnerInfo(-1), loserInfo(-1){
            gamestate = gamestatep;
        }
        void winnerReporter(char winner){//sets the winner and the loser for sending to the cloud
            winner = winner;
            if(winner == 1){
                winnerInfo = Snake1;
                loserInfo = Snake2;
            }
            else if(winner == 0) {
                winnerInfo = Snake2;
                loserInfo = Snake1;
            }
        }
};
gameInfo info(0);
void gameTick(){//exactly what the name says
    Snake1.move();
    Snake1.snakeEat();
    Snake2.move();
    Snake2.snakeEat();
    cout << endl << "nowallnosnake" << endl;
}
void AbsoluteSolver(){// manages the game engine and win/loose conitions
    //checks all nessecary stuff
    snakecheck12Result = snakecheck(Snake1, Snake2);
    snakecheck21Result = snakecheck(Snake2, Snake1);
    snake1movecheckResult = Snake1.movecheck();
    snake2movecheckResult = Snake2.movecheck();
    //if no collision happened then uses game tick
    if(snake1movecheckResult && snake2movecheckResult && snakecheck12Result && snakecheck21Result)gameTick();
    //else stops the game and prepares winner
    else{
        info.gamestate = 0;
        if (snake1movecheckResult && snake2movecheckResult) cout << "nowall" << endl;
        else{
            if((snake1movecheckResult == 0) && (snake2movecheckResult == 0)){
                cout << "wall" << endl;
                info.winnerReporter(-1);
            }
            else if(snake1movecheckResult == 0){
                cout << "1wall" << endl;
                info.winnerReporter(2);
            }
            else if(snake2movecheckResult == 0){
                cout << "2wall" << endl;
                info.winnerReporter(1);
            }
        }
        if(snakecheck12Result && snakecheck21Result) cout << "nosnake" << endl;
        else{
            if((snakecheck12Result == 0) && (snakecheck21Result == 0)){
                cout << "snake" << endl;
                info.winnerReporter(-1);
            }
            else if(snakecheck12Result == 0){
                cout << "1snake" << endl;
                info.winnerReporter(2);
            }
            else if(snakecheck21Result == 0){
                cout << "2snake" << endl;
                info.winnerReporter(1);
            }
        }
    if((snake1movecheckResult == 0) && (snake2movecheckResult == 0) && (snakecheck12Result == 0) && (snakecheck21Result == 0)) cout << "idk what happened either" << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// ▄▄▄▄▄▄▄ ▄▄▄▄▄▄   ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄   ▄▄▄▄▄▄ ▄▄   ▄▄ ///////////////////////////////////////////
///////////////////////////█       █   ▄  █ █       █       █   ▄  █ █      █  █▄█  █///////////////////////////////////////////
///////////////////////////█    ▄  █  █ █ █ █   ▄   █   ▄▄▄▄█  █ █ █ █  ▄   █       █///////////////////////////////////////////
///////////////////////////█   █▄█ █   █▄▄█▄█  █ █  █  █  ▄▄█   █▄▄█▄█ █▄█  █       █///////////////////////////////////////////
///////////////////////////█    ▄▄▄█    ▄▄  █  █▄█  █  █ █  █    ▄▄  █      █       █///////////////////////////////////////////
///////////////////////////█   █   █   █  █ █       █  █▄▄█ █   █  █ █  ▄   █ ██▄██ █///////////////////////////////////////////
///////////////////////////█▄▄▄█   █▄▄▄█  █▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄█  █▄█▄█ █▄▄█▄█   █▄█///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getInput(){//get player input
    //player 1 input
    if(GetKeyState('W') & 0x8000)Snake1.changeDirection(0);
    if(GetKeyState('A') & 0x8000)Snake1.changeDirection(3);
    if(GetKeyState('S') & 0x8000)Snake1.changeDirection(2);
    if(GetKeyState('D') & 0x8000)Snake1.changeDirection(1);
    //player 2 input
    if(GetKeyState('I') & 0x8000)Snake2.changeDirection(0);
    if(GetKeyState('J') & 0x8000)Snake2.changeDirection(3);
    if(GetKeyState('K') & 0x8000)Snake2.changeDirection(2);
    if(GetKeyState('L') & 0x8000)Snake2.changeDirection(1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int width = MAXX;
static const int height = MAXY;
char grid[height][width];

void testGame(){//for testing only - prints most needed values of the game
    printf("Snake1: x= %d, y= %d, direction= %d  tail: \r\nlength= %d, first6x= %d, %d, %d, %d, %d, %d, first6y= %d, %d, %d, %d, %d, %d \r\nlengthStored= %d, %d, %d, %d, %d\r\n\n", Snake1.headposX, Snake1.headposY, Snake1.direction, Snake1.length, Snake1.tailX[0], Snake1.tailX[1], Snake1.tailX[2], Snake1.tailX[3], Snake1.tailX[4], Snake1.tailX[5], Snake1.tailY[0], Snake1.tailY[1], Snake1.tailY[2], Snake1.tailY[3], Snake1.tailY[4], Snake1.tailY[5], Snake1.lengthStored[0], Snake1.lengthStored[1], Snake1.lengthStored[2], Snake1.lengthStored[3], Snake1.lengthStored[4]);
    printf("Snake2: x= %d, y= %d, direction= %d  tail: \r\nlength= %d, first6x= %d, %d, %d, %d, %d, %d, first6y= %d, %d, %d, %d, %d, %d \r\nlengthStored= %d, %d, %d, %d, %d\r\n\n", Snake2.headposX, Snake2.headposY, Snake2.direction, Snake2.length, Snake2.tailX[0], Snake2.tailX[1], Snake2.tailX[2], Snake2.tailX[3], Snake2.tailX[4], Snake2.tailX[5], Snake2.tailY[0], Snake2.tailY[1], Snake2.tailY[2], Snake2.tailY[3], Snake2.tailY[4], Snake2.tailY[5], Snake2.lengthStored[0], Snake2.lengthStored[1], Snake2.lengthStored[2], Snake2.lengthStored[3], Snake2.lengthStored[4]);
    printf("Food: x= %d, y= %d, nutrition: %d", foodblock.x, foodblock.y, foodblock.nutrition);
    printf("\r\n------------------------------------------------------------------------------------------------------");
    printf("\r\n\n\n");
}
class Playfield {//for testing only - used to display the playfield
public:
    Playfield() {//playfield constructor
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) grid[i][j] = 250;
        }
    }
    void updateSnakePositions(snake& p, char symbol) {//updated snake postions
        grid[p.headposY][p.headposX] = symbol;
        for (int i = 0; i < p.length; i++) {
            grid[p.tailY[i]][p.tailX[i]] = symbol;
        }
    }
    void displayGrid() {// displaying playfield
        //updates postions
        if(gameON){
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) grid[i][j] = 250;
            }
            updateSnakePositions(Snake1, '1');
            updateSnakePositions(Snake2, '2');
            grid[foodblock.y][foodblock.x] = 'F';
        }
        //prints playfield
        for (int i = height; i >= 0; i--) {
            for (int j = 0; j < width; j++){
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};
Playfield playfield;


void addButton(button buttonT) {
    #define posy buttonT.startY// - height
    #define posx buttonT.startX// - width

    char textLength = textlen(buttonT.text);
    char spacesBefore = (buttonT.width - textLength) / 2;
    char spacesAfter = buttonT.width - textLength - spacesBefore;

    for (int widths = 0; widths <= buttonT.width; widths++) grid[buttonT.height + posy][widths + posx] = '#';
    for (int i = 0; i < buttonT.height; ++i) {
        grid[i + posy][posx] = '#';
        if (i == buttonT.height / 2) {
            for(char widths = 0; widths <= spacesBefore; widths++) grid[i + posy][widths + posx + 1] = 250;
            for(char widths = 0; widths <= textLength; widths++) grid[i + posy][widths + posx + spacesBefore + 1] = buttonT.text[widths];
            for(char widths = 0; widths <= spacesAfter; widths++) grid[i + posy][widths + posx + spacesBefore + textLength + 1] = 250;
        }
        else {
            for (char j = 1; j < buttonT.width; j++) grid[i + posy][j + posx] = 250;
        }
        grid[i + posy][buttonT.width + posx] = '#';
    }
    for (int widths = 0; widths <= buttonT.width; widths++) grid[posy][widths + posx] = '#';
}
void updateMenus(bool deathOrMenu){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) grid[i][j] = 250;
    }
    if (deathOrMenu){
        addButton(menuScreen.primaryButton);
        addButton(menuScreen.secondaryButton);
        addButton(menuScreen.ternaryButton);
    }
    else if (!deathOrMenu){
        addButton(deathScreen.restartButton);
        addButton(deathScreen.backButton);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void innitSnake(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    info.gamestate = 1;
}
void snakeEngine(){//manages all snake game processes
    AbsoluteSolver();//game engine
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄   ▄▄▄//////////////////////////////////////////////////////////
//////////////////////////////////////////█  █▄█  █      █   █  █  █ █//////////////////////////////////////////////////////////
//////////////////////////////////////////█       █  ▄▄  █   █   █▄█ █//////////////////////////////////////////////////////////
//////////////////////////////////////////█       █ █▄▄█ █   █       █//////////////////////////////////////////////////////////
//////////////////////////////////////////█       █      █   █  ▄    █//////////////////////////////////////////////////////////
//////////////////////////////////////////█ ██▄██ █  ▄▄  █   █ █ █   █//////////////////////////////////////////////////////////
//////////////////////////////////////////█▄█   █▄█▄█  █▄█▄▄▄█▄█  █▄▄█//////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    srand(69420);
    //gamestart
    testGame();
    long long int milis = 0;
    innitMenus();
    innitSnake();
    updateMenus(1);
    playfield.displayGrid();
    //updateMenus(true);
    //gameON = true;
    /*while(1){z
        if(clock() > milis + 250){
            getInput();
            if(!gameON) updateMenus();
            if(gameON) snakeEngine();
            system("cls");//clears terminal
            //playfield.displaySnake(Snake1, Snake2, foodblock);//display the game
            testGame();//print game info
            milis += 250;
        }
    }*/
    return 0;
}