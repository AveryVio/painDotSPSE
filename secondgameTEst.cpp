#include <iostream>
using namespace std;

#define MAXX 256
#define MAXY 128
#define GRAVITY 4
#define AIRDRAG 3

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
    void changeVelocity(char action, int x, int y);
};
void player::changeVelocity(char action, int x, int y){
    if(action == 'j') {
        velocityX = x;
        velocityY = y;
    }
    else if(action == 'g') velocityY -= (GRAVITY * 0.3 * (0.5 * AIRDRAG));
    else if(action == 'd') velocityX -= (AIRDRAG * 0.5);
}
player playe;
int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    return 0;
}
