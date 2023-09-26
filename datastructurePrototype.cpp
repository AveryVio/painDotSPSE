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
        double maxX = 1600000;
        double maxY = 900000;
};
//interaction
void arrowControls(){
}
void joystickControls(){
}
void controls(){
}
//comuniction
int initialize(){
    //send innit message
    //recive confirmation message
}
int newGame(char gameMode){
    //send star message
    //send panelColour and team mode mesage
}
//main
int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    return 0;
}