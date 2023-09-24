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
        int taps;
        bool gameWinner; // true if master, false if slave
        char teamColour; // can be red, blue, green, orange or purple
        char gameMode;
        gameInfo(char colour){
            teamColour = colour;
        }
};
class canvas{
    public:
        double maxX = 1600000;
        double maxY = 900000;
};
//interaction
int tap(double x, double y){
    //place xy
    //send xy to other panel
}
//comuniction
int initialize(){
    //send innit message
    //recive confirmation message
}
int newGame(char panelClour, char gameMode){
    //send star message
    //send panelColour and team mode mesage
}
//main
int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    return 0;
}