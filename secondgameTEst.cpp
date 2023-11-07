#include <iostream>
using namespace std;
#include <stdlib.h>

#define MAXX 256
#define MAXY 128
#define GRAVITY 4
#define AIRDRAG 2
#define MAXVELOCITY 16

class position{
    public:
    int xpos;
    int ypos;
};
class fly{
    public:
    position coords;
    position possibleCoords[5];
    char pos;
    fly(int x, int y){
    }
    void regenerate(){
        pos = rand() % 6;
        coords = possibleCoords[pos];
    }
};
class player{
    public:
    position coords;
    int velocityX;
    int velocityY;
    int accelerationY;
    bool moving;
    player(int x, int y){
        coords.xpos = x;
        coords.ypos = y;
    }
    void jump(){
        velocityX = 16;
        accelerationY = 10;
        moving = true;
    }
    void move();
    char bounceCheck(platform* platformT);
    void bounce();
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
    }
};
playfield gameField;

char biggerNumber(char numOne, char numTwo){
    if(numOne>numTwo)return numOne;
    return numTwo;
}
char absoluteNumber(char number){
    if(number < 0) return -number;
    return number;
}
char player::bounceCheck(platform* platformT){
    char bounceSide = platformT->sideTouched(this);
    if(bounceSide % 2) velocityX = -velocityX;
    else velocityY = -velocityY;
    return bounceSide;
}
void player::bounce(){
    platform* platformT;
    char bounceResult = 0;
    for (char touchdeti = 0; touchdeti < 4;){
        switch(touchdeti){
            case 0:
            platformT = &gameField.bottomPlatform;
            break;
            case 1:
            platformT = &gameField.leftPlatform;
            break;
            case 2:
            platformT = &gameField.rightPlatform;
            break;
            case 3:
            platformT = &gameField.topPlatform;
            break;
        }
        bounceResult = bounceCheck(platformT);
        if(bounceResult == -1) continue;
        if(bounceResult == 0) moving = 0;
    }
}
void player::move(){
    if(!moving) return;
    if(velocityX <= MAXVELOCITY) velocityX -= (AIRDRAG / 2 - 1);
    if(velocityY <= MAXVELOCITY) velocityY += accelerationY / 2;
    accelerationY -= GRAVITY / 2;
    for (char movei = 0; movei < absoluteNumber(biggerNumber(velocityX,velocityY)); movei++){
        if(gameField.platformClosenessCheck(this)) bounce();
        if(velocityX >= movei){
            if(velocityX < 0) --coords.xpos;
            else if(velocityX > 0) ++coords.xpos;
        }
        if(velocityY >= movei){
            if(velocityY < 0) --coords.ypos;
            else if(velocityY > 0) ++coords.ypos;
        }
    }
    coords.xpos += velocityX;
    coords.ypos += velocityY;
}


int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    return 0;
}
