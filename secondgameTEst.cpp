#include <iostream>
using namespace std;

#define MAXX 256
#define MAXY 128
#define GRAVITY 4.5
#define AIRDRAG 3.2

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
};
player playe;
int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    return 0;
}
