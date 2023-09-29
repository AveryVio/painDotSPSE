#include <iostream>
using namespace std;

//game
class panel{
    public:
        bool hierarchy;
        bool gameState;
};
class gameInfo{
    public:
        bool gameWinner; // true if master, false if slave
        char gameMode;
};
class playfield{
    public:
        char maxX = 64;
        char maxY = 32;
};
class player{
    char headposX;
    char headposY;
    char tailX[128];
    char tailY[128];
    char direction;
    char length;
    player(char pheadposX, char pheadposY, char pdirection, char plenght){
        headposX = pheadposX;
        headposY = pheadposY;
        direction = pdirection;
        length = plenght;
    };
    void move(char headX, char headY, char X[128], char Y[128], char direction, char plength){
        for(int i = plength; i >= 0; i--){
            X[i] = X[i-1];
            Y[i] = Y[i-1];
        }
        if (direction == 0) headY = headY + 1;
        else if (direction == 1) headX = headX + 1;
        else if (direction == 2) headY = headY - 1;
        else if (direction == 3) headX = headX - 1;
    }
};
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