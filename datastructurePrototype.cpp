#include <iostream>
using namespace std;

#define playfieldX 64
#define playfieldY 32

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
        char maxX = playfieldX;
        char maxY = playfieldY;
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
        char wallcheck(char pdir){
            if((pdir == 0) && (headposY + 1 == playfieldY))return 0;
            else if((pdir == 1) && (headposX + 1 == playfieldX))return 0;
            else if((pdir == 2) && (headposY - 1 == 0))return 0;
            else if((pdir == 3) && (headposX - 1 == 0))return 0;
            else return 1;
        }
        char movecheck(){
            if(wallcheck(0) != 1) return 0;
            else if(wallcheck(1) != 1) return 0;
            else if(wallcheck(2) != 1) return 0;
            else if(wallcheck(3) != 1) return 0;
            else return 1;
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