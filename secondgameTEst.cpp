#include <iostream>
using namespace std;

#define MAXX 256
#define MAXY 128
#define GRAVITY 4
#define AIRDRAG 2

class position{
    public:
    int xpos;
    int ypos;
};
class player{
    public:
    position coords;
    int velocityX;
    int velocityY;
    int accelerationX;
    int accelerationY;
    bool moving;
    void changeVelocity(){
        velocityX += accelerationX - AIRDRAG * 0.4;
        velocityY += accelerationY - GRAVITY * 0.4;
    }
    void jump(){
        accelerationX = 10;
        accelerationY = 8;
        moving = true;
    }
    void changePosition(){
        
    }
};
void player::changeVelocity(){

}
player playe;
int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    return 0;
}
