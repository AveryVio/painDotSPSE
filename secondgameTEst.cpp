#include <iostream>
using namespace std;
#include <stdlib.h>

#define MAXX 256
#define MAXY 128
#define GRAVITY 4
#define AIRDRAG 2

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
    int accelerationX;
    int accelerationY;
    bool moving;
    player(int x, int y){
        coords.xpos = x;
        coords.ypos = y;
    }
    void jump(){
        accelerationX = 16;
        accelerationY = 10;
        moving = true;
    }
    void move(){
        velocityX += accelerationX / 2;
        velocityY += accelerationY / 2;
        accelerationX -= AIRDRAG / 2;
        accelerationY -= GRAVITY / 2;
        coords.xpos += velocityX;
        coords.ypos += velocityY;
    }
};
class platform{
    public:
    position topLeftPos;
    position bottomRightPos;
    char platformClosseness(player* playerT){
        if((playerT->coords.xpos < topLeftPos.xpos - 5) || (playerT->coords.xpos > bottomRightPos.xpos + 5)) return -1;
        if((playerT->coords.ypos < bottomRightPos.ypos - 5) || (playerT->coords.ypos > topLeftPos.ypos + 5)) return -1;
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

int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    return 0;
}
