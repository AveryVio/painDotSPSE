#include <iostream>
using namespace std;
#include <stdlib.h>

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
    private:
    int e;
};
class fly{
    public:
    char coords;
    position possibleCoords[6];
    char pos;
    fly(){
        //set fly coords
        possibleCoords[0].xpos = 3 * MAXX / 8;
        possibleCoords[0].ypos = MAXY / 8;
        possibleCoords[1].xpos = MAXX / 16;
        possibleCoords[1].ypos = MAXY / 8;
        possibleCoords[2].xpos = MAXX - MAXX / 16;
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
class jumpArrow{
    char direction;
    position coords;
    char hop(player* playerT){
        playerT->jump(MAXJUMPHEIGHT * (1 - direction),MAXJUMPHEIGHT * direction);
    }
};
class player{
    public:
    position coords;
    int velocityX;
    int velocityY;
    int accelerationY;
    bool moving;
    char slideCounter;
    player(int x, int y){
        coords.xpos = x;
        coords.ypos = y;
    }
    void jump(char velX, char accY){
        velocityX = velX;
        accelerationY = accY;
        moving = true;
    }
    void move();
    char bounceCheck(platform* platformT);
    void bounce();
    void slide();
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
playfield gameField;

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
        if(bounceResult == 0) {
            moving = 0;
            slideCounter = 5;
            velocityY = 0;
            accelerationY = 0;
        }
    }
}
void player::slide(){
    if(slideCounter == 0) {
        velocityX = 0;
        return;
    }
    coords.xpos += velocityX / 3;
    velocityX /= 3;
    slideCounter--;
}
void player::move(){
    if(slideCounter > 0) slide();
    if(!moving) return;
    if(velocityX <= MAXVELOCITY) velocityX -= (AIRDRAG / 2 - 1);
    if(velocityY <= MAXVELOCITY) velocityY += accelerationY / 2;
    accelerationY -= GRAVITY / 2;
    for (char movei = 0; movei < absoluteNumber(biggerNumber(velocityX,velocityY)); movei++){
        if(gameField.platformClosenessCheck(this) && (velocityY > 0)){
            bounce();
            break;
        }
        if(velocityX >= movei){
            if(velocityX < 0) --coords.xpos;
            else if(velocityX > 0) ++coords.xpos;
        }
        if(velocityY >= movei){
            if(velocityY < 0) --coords.ypos;
            else if(velocityY > 0) ++coords.ypos;
        }
    }
}


int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    return 0;
}