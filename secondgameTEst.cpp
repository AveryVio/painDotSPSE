#include <iostream>
using namespace std;
#include <stdlib.h>
#include <ctime>
#include <Windows.h>

#define MAXX 256
#define MAXY 128
#define GRAVITY 4
#define AIRDRAG 2
#define MAXVELOCITY 16
#define MAXJUMPHEIGHT 26

char biggerNumber(char numOne, char numTwo){
    if(numOne>numTwo)return numOne;
    return numTwo;
}
char absoluteNumber(char number){
    if(number < 0) return -number;
    return number;
}

class position{
    public:
    int xpos;
    int ypos;
};
class fly{
    public:
    char coords;
    position possibleCoords[6];
    char hardmode;
    fly(){
        //set fly coords
        possibleCoords[0].xpos = 3 * MAXX / 8;
        possibleCoords[0].ypos = MAXY / 8;
        possibleCoords[1].xpos = 5 * MAXX / 8;
        possibleCoords[1].ypos = MAXY / 8;
        possibleCoords[2].xpos = MAXX / 16;
        possibleCoords[2].ypos = 5 * MAXY / 16;
        possibleCoords[3].xpos = MAXX - MAXX / 16;
        possibleCoords[3].ypos = 5 * MAXY / 16;
        possibleCoords[4].xpos = MAXX / 2;
        possibleCoords[4].ypos = MAXY / 2;
        //hard fly coords;
        possibleCoords[5].xpos = MAXX / 2;
        possibleCoords[5].ypos = MAXY;
    }
    void flyRegenerate(bool hardmode){
        if(hardmode) coords = 5;
        else coords = rand() % 5;
    }
};
class player{
    public:
    int score = 0;
    position coords;
    int velocityX;
    int velocityY;
    bool moving;
    char slideCounter;
    player(int x, int y){
        coords.xpos = x;
        coords.ypos = y;
    }
    void jump(char velX, char velY){
        velocityX = velX;
        velocityX = velY;
        moving = true;
    }
        void slide(){
        if(slideCounter == 0) {
            velocityX = 0;
            return;
        }
        coords.xpos += velocityX / 3;
        velocityX /= 3;
        slideCounter--;
    }
    void edgePortal(){
        if(coords.ypos < 0) coords.ypos = MAXY - 1;//gameover
        if(coords.xpos >= MAXX) coords.xpos = 0;
        if(coords.xpos < 0) coords.xpos = MAXX - 1;
        if (coords.ypos >= MAXY) coords.ypos = 3 * MAXY / 5;
    }
    void move();
    void scoring(fly *flyT);
};
class jumpArrow{
    public:
    char direction;
    position coords;
    char hop(player* playerT){
        playerT->jump(MAXJUMPHEIGHT - MAXJUMPHEIGHT * (direction / 60),MAXJUMPHEIGHT * (direction / 60));
    }
};
class platform{
    public:
    position topLeftPos;
    position bottomRightPos;
    char platformClosseness(player* playerT){
        if((playerT->coords.xpos < topLeftPos.xpos - 1) || (playerT->coords.xpos > bottomRightPos.xpos + 1)) return 1;
        if((playerT->coords.ypos < bottomRightPos.ypos - 1) || (playerT->coords.ypos > topLeftPos.ypos + 1)) return 1;
        return 0;
    }
    char sideTouched(player* playerT){
        if((playerT->coords.ypos > bottomRightPos.ypos - 1) && (playerT->coords.ypos < topLeftPos.ypos + 1)){
            if(playerT->coords.xpos == topLeftPos.xpos - 1) return 3;
            else if (playerT->coords.xpos == bottomRightPos.xpos + 1) return 1;
        }
        else if((playerT->coords.xpos < topLeftPos.xpos - 1) || (playerT->coords.xpos > bottomRightPos.xpos + 1)){
            if(playerT->coords.ypos == topLeftPos.ypos + 1) return 0;
            else if (playerT->coords.ypos == bottomRightPos.ypos - 1) return 2;
        }
        return -1;
    }
};
class playfield{
    public:
    platform bottomPlatform;
    platform leftPlatform;
    platform rightPlatform;
    platform topPlatform;
    fly food;
    void setPosition(platform* platform, int topleftX, int topleftY, int bottomrightX, int bottomrightY){
        platform->topLeftPos.xpos = topleftX;
        platform->topLeftPos.ypos = topleftY;
        platform->bottomRightPos.xpos = bottomrightX;
        platform->bottomRightPos.ypos = bottomrightY;
    }
    char platformClosenessCheck(player* playerT){
        if(bottomPlatform.platformClosseness(playerT)) return 1;
        if(leftPlatform.platformClosseness(playerT)) return 1;
        if(rightPlatform.platformClosseness(playerT)) return 1;
        if(topPlatform.platformClosseness(playerT)) return 1;
        return 0;
    }
    void createPlayfield(){
        //generate fly
        food.flyRegenerate(false);
        //create bottom platform
        bottomPlatform.topLeftPos.xpos = MAXX / 4;
        bottomPlatform.topLeftPos.ypos = MAXY / 16;
        bottomPlatform.bottomRightPos.xpos = MAXX - MAXX / 4;
        bottomPlatform.bottomRightPos.ypos = 0;
        //create left platform
        leftPlatform.topLeftPos.xpos = 0;
        leftPlatform.topLeftPos.ypos = MAXY / 4;
        leftPlatform.bottomRightPos.xpos = MAXX / 8;
        leftPlatform.bottomRightPos.ypos = 3 * MAXY / 16;
        //create right platform
        rightPlatform.topLeftPos.xpos = MAXX - MAXX / 8;
        rightPlatform.topLeftPos.ypos = MAXY / 4;
        rightPlatform.bottomRightPos.xpos = MAXX;
        rightPlatform.bottomRightPos.ypos = 3 * MAXY / 16;
        //create top platform
        topPlatform.topLeftPos.xpos = 3 * MAXX / 8;
        topPlatform.topLeftPos.ypos = 7 * MAXY / 16;
        topPlatform.bottomRightPos.xpos = MAXX - 3 * MAXX / 8;
        topPlatform.bottomRightPos.ypos = 3 * MAXY / 8;
        //yes this is nessecary since it's needed to be configutable
    }
};
playfield frogGame;
player frog1(2*MAXX/3,MAXY/2);
player frog2(MAXX/3,MAXY/2);
jumpArrow frog1Arrow;
jumpArrow frog2Arrow;

char bounceCheck(player* PlayerT, platform* platformT){
    char bounceSide = platformT->sideTouched(PlayerT);
    if(bounceSide % 2) PlayerT->velocityY = -PlayerT->velocityY / 5;
    else PlayerT->velocityX = -PlayerT->velocityX / 5;
    return bounceSide;
}
void bounce(player* playerT){
    platform* platformT;
    char bounceResult = 0;
    for (char touchdeti = 0; touchdeti < 4;){
        switch(touchdeti){
            case 0:
            platformT = &frogGame.bottomPlatform;
            break;
            case 1:
            platformT = &frogGame.leftPlatform;
            break;
            case 2:
            platformT = &frogGame.rightPlatform;
            break;
            case 3:
            platformT = &frogGame.topPlatform;
            break;
        }
        bounceResult = bounceCheck(playerT,platformT);
        if(bounceResult == -1) continue;
        if(bounceResult == 0) {
            playerT->moving = 0;
            playerT->slideCounter = 5;
            playerT->velocityY = 0;
            playerT->velocityY = 0;
        }
    }
}
void player::move(){
    if(absoluteNumber(velocityX) <= MAXVELOCITY + velocityX) velocityX -= (AIRDRAG / 2);
    if(absoluteNumber(velocityY) <= MAXVELOCITY + velocityY) velocityY -= (GRAVITY / 2);// to be fixed idk how it doesnt work
    for (char movei = 0; movei < absoluteNumber(biggerNumber(velocityX,velocityY)); movei++){
        if(frogGame.platformClosenessCheck(this) && (velocityY > 0)){
            bounce(this);
            break;
        }
        if(absoluteNumber(velocityX) >= movei){
            if(velocityX < 0) --coords.xpos;
            else if(velocityX > 0) ++coords.xpos;
        }
        if(absoluteNumber(velocityY) >= movei){
            if(velocityY < 0) --coords.ypos;
            else if(velocityY > 0) ++coords.ypos;
        }
    }
}
char flyCheck(player *playerT, fly *flyT){
    if(playerT->coords.xpos != flyT->possibleCoords[flyT->coords].xpos) return 0;
    if(playerT->coords.ypos != flyT->possibleCoords[flyT->coords].ypos) return 0;
    return 1;
}
void player::scoring(fly *flyT){
    if(!flyCheck(this, flyT)) return;
    if(flyT->hardmode)score += 2;
    else score++;
}

void frogGameTick(){
    if(frog1.slideCounter > 0) frog1.slide();
    if(frog1.moving == true) frog1.move();
    frog1.edgePortal();
    if(frog2.slideCounter > 0) frog2.slide();
    if(frog2.moving == true) frog2.move();
    frog2.edgePortal();
}
void frogGameEngine(){
    frogGameTick();
}

void displayPlayfield(playfield& field) {
    // Create a 2D array to represent the playfield
    char playfieldArray[MAXY][MAXX];
    // Initialize the array with empty spaces
    for (int i = 0; i < MAXY; ++i) {
        for (int j = 0; j < MAXX; ++j) {
            playfieldArray[i][j] = ' ';
        }
    }
    for(char i = field.bottomPlatform.bottomRightPos.ypos; i <= field.bottomPlatform.topLeftPos.ypos; i++){
        for(int j = field.bottomPlatform.topLeftPos.xpos; j <= field.bottomPlatform.bottomRightPos.xpos; j++) {
            playfieldArray[i][j] = 'b';
        }
    }
    for(char i = field.leftPlatform.bottomRightPos.ypos; i <= field.leftPlatform.topLeftPos.ypos; i++){
        for(int j = field.leftPlatform.topLeftPos.xpos; j <= field.leftPlatform.bottomRightPos.xpos; j++) {
            playfieldArray[i][j] = 'l';
        }
    }
    for(char i = field.rightPlatform.bottomRightPos.ypos; i <= field.rightPlatform.topLeftPos.ypos; i++){
        for(int j = field.rightPlatform.topLeftPos.xpos; j <= field.rightPlatform.bottomRightPos.xpos; j++) {
            playfieldArray[i][j] = 'r';
        }
    }
    for(char i = field.topPlatform.bottomRightPos.ypos; i <= field.topPlatform.topLeftPos.ypos; i++){
        for(int j = field.topPlatform.topLeftPos.xpos; j <= field.topPlatform.bottomRightPos.xpos; j++) {
            playfieldArray[i][j] = 't';
        }
    }
    playfieldArray[frog1.coords.ypos][frog1.coords.xpos] = '1';
    playfieldArray[frog2.coords.ypos][frog2.coords.xpos] = '2';
    playfieldArray[field.food.possibleCoords[field.food.coords].ypos][field.food.possibleCoords[field.food.coords].xpos] = 'F';
    // You can add similar code for the other platforms, flies, and other elements
    // Display the playfield
    for (int i = 0; i < MAXY; ++i) {
        for (int j = 0; j < MAXX; ++j) {
            std::cout << playfieldArray[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << frog1.coords.xpos << "," << frog1.coords.ypos << ";" << frog2.coords.xpos << "," << frog2.coords.ypos << endl;
    cout << field.food.coords << endl;
}

void startFrogGame(){
    frogGame.createPlayfield();
    do{
        do{
            frog1.coords = frogGame.food.possibleCoords[rand() % 5];
        } while((frog1.coords.xpos == frogGame.food.possibleCoords[frogGame.food.coords].xpos) && (frog1.coords.ypos == frogGame.food.possibleCoords[frogGame.food.coords].ypos));
        do{
            frog2.coords = frogGame.food.possibleCoords[rand() % 5];
        } while((frog2.coords.xpos == frogGame.food.possibleCoords[frogGame.food.coords].xpos) && (frog2.coords.ypos == frogGame.food.possibleCoords[frogGame.food.coords].ypos));
    } while((frog1.coords.xpos == frog2.coords.xpos) && (frog1.coords.ypos == frog2.coords.ypos));
    frog1.moving = false;
    frog2.moving = false;
}
int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    startFrogGame();
    displayPlayfield(frogGame);
    frog1Arrow.hop(&frog1);
    frog2Arrow.hop(&frog2);
    long long int milis = 0;
    for(uint16_t i = 0; i < 100000; i++){
        if(clock() > milis + 50){
            if(GetKeyState('Z') & 0x8000) frog1Arrow.hop(&frog1);
            if(GetKeyState('M') & 0x8000) frog2Arrow.hop(&frog2);
            frogGameEngine();
            system("cls");
            displayPlayfield(frogGame);
            cout<< frog1.velocityY << ","<<frog2.velocityY << endl;
            milis += 50;
        }
    }
    return 0;
}