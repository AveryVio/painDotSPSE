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
    void bounce(platform* platformT);
};
class platform{
    public:
    position topLeftPos;
    position bottomRightPos;
    char platformClosseness(player* playerT){
        if((playerT->coords.xpos < topLeftPos.xpos - 1) || (playerT->coords.xpos > bottomRightPos.xpos + 1)) return 0;
        if((playerT->coords.ypos < bottomRightPos.ypos - 1) || (playerT->coords.ypos > topLeftPos.ypos + 1)) return 0;
        return 1;
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

void player::bounce(platform* platformT){
    if(platformT->platformClosseness(this));
}
void player::move(){
    if(velocityX <= MAXVELOCITY) velocityX -= (AIRDRAG / 2 - 1);
    if(velocityY <= MAXVELOCITY) velocityY += accelerationY / 2;
    accelerationY -= GRAVITY / 2;
    for (char movei = 0; movei < absoluteNumber(biggerNumber(velocityX,velocityY)); movei++){
        
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
