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
        velocityX += accelerationX / 2 - AIRDRAG * 0.4;
        velocityY += accelerationY / 2 - GRAVITY * 0.4;
        if(accelerationX > 1) accelerationX /= 4;
        else accelerationX -= 1;
        if(accelerationY > 1) accelerationY /= 4;
        else accelerationY -= 1;
        coords.xpos += velocityX;
        coords.ypos += velocityY;
    }
};

int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    return 0;
}
