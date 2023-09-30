#include <iostream>
using namespace std;

//game
class panel{
    public:
        bool hierarchy;
        bool gameState;
};
class playfield{
    public:
        char minX = 0;
        char minY = 0;
        char maxX = 64;
        char maxY = 32;
};
class wall {
    char startX;
    char endX;
    char startY;
    char endY;
    wall(char sX, char eX, char sY, char eY){
        startX = sX;
        endX = eX;
        startY = sY;
        endY = eY;
    }
};
class player{
    public:
        char headposX;
        char headposY;
        char tailX[128];
        char tailY[128];
        char direction;
        char length;
        char lengthStored[10];
        player(char pheadposX, char pheadposY, char pdirection, char plenght){
            headposX = pheadposX;
            headposY = pheadposY;
            direction = pdirection;
            length = plenght;
        };
        void spawn(){
            headposX = headposX;
            headposY = headposY;
            direction = 0;
            length = 3;
        }
        bool wallcheck(){
        }
        void move(){
            if (lengthStored[0] !=0) {
                tailX[length + 1] = tailX[length];
                tailY[length + 1] = tailY[length];
                length++;
                for (int i = 9; i > 0; i--) lengthStored[i] = lengthStored[i + 1];
                lengthStored[10] = 0;
                for(int i = length-1; i >= 0; i--){
                    tailX[i] = tailX[i-1];
                    tailY[i] = tailY[i-1];
                }
            }
            else {
                for(int i = length; i >= 0; i--){
                    tailX[i] = tailX[i-1];
                    tailY[i] = tailY[i-1];
                }
            }
            if (direction == 0) headposY = headposY + 1;
            else if (direction == 1) headposX = headposX + 1;
            else if (direction == 2) headposY = headposY - 1;
            else if (direction == 3) headposX = headposX - 1;
        }
        bool movecheck(){
            if((direction == 0) && (wallcheck() == 0));
            else if((direction == 1) && (wallcheck() == 1));
            else if((direction == 2) && (wallcheck() == 2));
            else if((direction == 3) && (wallcheck() == 3));
        }
};
class food{
    public:
        char x;
        char y;
        char nutrition;
        food(char x, char y, char val){
            x = x;
            y = y;
            nutrition = val;
        }
};
void spawnFood(){
    food food(0,0,0);
}
//interaction
void arrowControls(){
}
void joystickControls(){
}
void controls(){
}
//main
int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    return 0;
}