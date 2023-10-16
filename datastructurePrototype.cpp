#include <iostream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <ctime>

#define PLAYFIELDX 32
#define PLAYFIELDY 16
#define MAXPLAYERLENGTH 128
#define PLAYERSTARTLENGTH 3
#define FOODRANDCALC (2 * (rand() % 1)) + (rand() % 2) + (rand() % 3)

char playercheck12Result;
char playercheck21Result;
char player1movecheckResult;
char player2movecheckResult;
//game
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
char playercheck();
class player{
    public:
        char headposX;
        char headposY;
        char tailX[MAXPLAYERLENGTH];
        char tailY[MAXPLAYERLENGTH];
        char direction;
        char length;
        char lengthStored[5];
        player(char playernumber){
            if(playernumber == 0) headposX = rand() % ((PLAYFIELDX / 2) + 1);
            else headposX = (PLAYFIELDX / 2) + rand() % ((PLAYFIELDX / 2) + 1);
            headposY = ((PLAYFIELDY + 1) / 8) + rand() % ((PLAYFIELDY + 1) / 4);
            length = PLAYERSTARTLENGTH;
            if(playernumber == 1) direction = 2;
            else direction = 0;
            for (int i = 0; i <= 5; i++) lengthStored[i] = 0;
            if (playernumber == 0){
                for (int i = 0; i < length; i++) {
                    tailX[i] = headposX;
                    tailY[i] = headposY - i - 1;
                }
            }
            else {
                for (int i = length - 1; i >= 0; i--) {
                    tailX[i] = headposX;
                    tailY[i] = headposY + i + 1;
                }
            }
        }
        char movecheck(){// if can move then 0 else 1 /*Tested - fully working as inteded*/
            if((direction == 0) && (headposY == PLAYFIELDY))return 0;
            if((direction == 1) && (headposX == PLAYFIELDX))return 0;
            if((direction == 2) && (headposY == 0))return 0;
            if((direction == 3) && (headposX == 0))return 0;
            return 1;
        }
        void move(){ /*Tested - fully working as inteded*/
            if(((direction == 0) && (headposY + 1 != PLAYFIELDY))||((direction == 1) && (headposY + 1 != PLAYFIELDX))||((direction == 2) && (headposY - 1 != PLAYFIELDY))||((direction == 3) && (headposY - 1 != PLAYFIELDX))){//this is only for testing purposes
                if (lengthStored[0] !=0) {
                    tailX[length + 1] = tailX[length];
                    tailY[length + 1] = tailY[length];
                    length++;
                    for (int i = 9; i > 0; i--) lengthStored[i] = lengthStored[i + 1];
                    lengthStored[10] = 0;
                    for(int i = length - 1; i > 0; i--){
                        tailX[i] = tailX[i-1];
                        tailY[i] = tailY[i-1];
                    }
                    tailX[0] = headposX;
                    tailY[0] = headposY;
                }
                else {
                    for(int i = length - 1; i > 0; i--){
                        tailX[i] = tailX[i-1];
                        tailY[i] = tailY[i-1];
                    }
                    tailX[0] = headposX;
                    tailY[0] = headposY;
                }
                if ((direction == 0) && (headposY + 1 != PLAYFIELDY)) headposY = headposY + 1;
                else if ((direction == 1) && (headposY + 1 != PLAYFIELDX)) headposX = headposX + 1;
                else if ((direction == 2) && (headposY - 1 != PLAYFIELDY)) headposY = headposY - 1;
                else if ((direction == 3) && (headposY - 1 != PLAYFIELDX)) headposX = headposX - 1;
            }
        }
        void changeDirection(char requestedDirection){
            switch (direction){
            case 0:
                if(requestedDirection == 1) direction = 1;
                if(requestedDirection == 2) direction = 2;
                if(requestedDirection == 3) direction = 3;
            break;
            case 1:
                if(requestedDirection == 0) direction = 0;
                if(requestedDirection == 2) direction = 2;
                if(requestedDirection == 3) direction = 3;
            break;
            case 2:
                if(requestedDirection == 0) direction = 0;
                if(requestedDirection == 1) direction = 1;
                if(requestedDirection == 3) direction = 3;
            break;
            case 3:
                if(requestedDirection == 0) direction = 0;
                if(requestedDirection == 1) direction = 1;
                if(requestedDirection == 2) direction = 2;
            break;
            }
        }
};
player Player1(0);
player Player2(1);
food foodblock(rand() % (PLAYFIELDX + 1), rand() % (PLAYFIELDY + 1), FOODRANDCALC);

void regenFood() { /*Tested - mabye working?? not fully sure*/
    foodblock.nutrition = (rand() % 1) + (rand() % 2) + (rand() % 3) + (rand() % 1);
    foodblock.x = rand() % (PLAYFIELDX + 1);
    foodblock.y = rand() % (PLAYFIELDY + 1);
}
char playerFirstStoredLength(player playerN){//returns higherst stored length
    for(int v = 0; v < 5; v++) if(playerN.lengthStored[v] == 1) return v;
    return 0;
}
void playerEat(player playerN){ /*Tested - fully working as inteded*/
    if ((foodblock.x == playerN.headposX) && (foodblock.y == playerN.headposY)){
        for (int i = playerFirstStoredLength(playerN); i < foodblock.nutrition; i++) playerN.lengthStored[i]= 1;
        regenFood();
    }
}
char biggerPlayerLength(){ /*Tested - fully working as intended*/
    if(Player1.length > Player2.length) return Player1.length;
    return Player2.length;
}
char playercheck(player playerN, player playerT){// if both colide then 2, if asked player then 1 else 0
    if((playerN.headposX == playerT.headposX) && (playerN.headposY == playerT.headposY)) return 2;
    if(playerN.direction == 0){
        if((playerN.headposX == playerT.headposX) && (playerN.headposY + 1 == playerT.headposY)) return 0;
        for(int i = 0; i <= biggerPlayerLength(); i++){
            if((playerN.headposX == playerT.tailX[i]) && (playerN.headposY + 1 == playerT.tailY[i])) return 0;
            if((playerN.headposX == playerN.tailX[i]) && (playerN.headposY + 1 == playerN.tailY[i])) return 0;
        }
    }
    if(playerN.direction == 1){
        if((playerN.headposX + 1 == playerT.headposX) && (playerN.headposY == playerT.headposY)) return 0;
        for(int i = 0; i <= biggerPlayerLength(); i++){
            if((playerN.headposX + 1 == playerT.tailX[i]) && (playerN.headposY == playerT.tailY[i])) return 0;
            if((playerN.headposX + 1 == playerN.tailX[i]) && (playerN.headposY == playerN.tailY[i])) return 0;
        }
    }
    if(playerN.direction == 2){
        if((playerN.headposX == playerT.headposX) && (playerN.headposY - 1 == playerT.headposY)) return 0;
        for(int i = 0; i <= biggerPlayerLength(); i++){
            if((playerN.headposX == playerT.tailX[i]) && (playerN.headposY - 1 == playerT.tailY[i])) return 0;
            if((playerN.headposX == playerN.tailX[i]) && (playerN.headposY - 1 == playerN.tailY[i])) return 0;
        }
    }
    if(playerN.direction == 3){
        if((playerN.headposX - 1 == playerT.headposX) && (playerN.headposY == playerT.headposY)) return 0;
        for(int i = 0; i <= biggerPlayerLength(); i++){
            if((playerN.headposX - 1 == playerT.tailX[i]) && (playerN.headposY == playerT.tailY[i])) return 0;
            if((playerN.headposX - 1 == playerN.tailX[i]) && (playerN.headposY == playerN.tailY[i])) return 0;
        }
    }
    return 1;
};
class gameInfo{
    public:
        uint16_t gemeid;
        char gamestate;
        char winner;
        player winnerInfo;
        player loserInfo;
        gameInfo(char gamestatep) : winnerInfo(-1), loserInfo(-1){
            gamestate = gamestatep;
        }
};
gameInfo info(0);
void gameTick(){/*Tested - fully working as intended*/
    playercheck12Result = playercheck(Player1, Player2);
    playercheck21Result = playercheck(Player2, Player1);
    player1movecheckResult = Player1.movecheck();
    player2movecheckResult = Player2.movecheck();
    if (playercheck12Result && playercheck21Result){
        if(Player1.movecheck()) Player1.move();
        else cout << "1nomove" << endl;
        if(Player2.movecheck()) Player2.move();
        else cout << "2nomove" << endl;
        playerEat(Player1);
        playerEat(Player2);
    }
    else{
        info.gamestate = 0;
        if((playercheck12Result == 0) && (playercheck21Result == 0)) info.winner = -1;
        else if(playercheck12Result == 0){
            info.winner = 2;
            info.winnerInfo = Player2;
            info.loserInfo = Player1;
        }
        else if(playercheck21Result == 0){
            info.winner = 1;
            info.winnerInfo = Player1;
            info.loserInfo = Player2;
        }
        if((player1movecheckResult == 0) && (player2movecheckResult == 0)){
            info.winner = -1;
        }
        else if(player1movecheckResult == 0){
            info.winner = 2;
            info.winnerInfo = Player2;
            info.loserInfo = Player1;
        }
        else if(player2movecheckResult == 0){
            info.winner = 1;
            info.winnerInfo = Player1;
            info.loserInfo = Player2;
        }
        else cout << "nothing happened" << endl;
    }
}          
void testGame(){
    printf("Player1: x= %d, y= %d, direction= %d  tail: \r\nlength= %d, first6x= %d, %d, %d, %d, %d, %d, first6y= %d, %d, %d, %d, %d, %d \r\nlengthStored= %d, %d, %d, %d, %d\r\n\n", Player1.headposX, Player1.headposY, Player1.direction, Player1.length, Player1.tailX[0], Player1.tailX[1], Player1.tailX[2], Player1.tailX[3], Player1.tailX[4], Player1.tailX[5], Player1.tailY[0], Player1.tailY[1], Player1.tailY[2], Player1.tailY[3], Player1.tailY[4], Player1.tailY[5], Player1.lengthStored[0], Player1.lengthStored[1], Player1.lengthStored[2], Player1.lengthStored[3], Player1.lengthStored[4]);
    printf("Player2: x= %d, y= %d, direction= %d  tail: \r\nlength= %d, first6x= %d, %d, %d, %d, %d, %d, first6y= %d, %d, %d, %d, %d, %d \r\nlengthStored= %d, %d, %d, %d, %d\r\n\n", Player2.headposX, Player2.headposY, Player2.direction, Player2.length, Player2.tailX[0], Player2.tailX[1], Player2.tailX[2], Player2.tailX[3], Player2.tailX[4], Player2.tailX[5], Player2.tailY[0], Player2.tailY[1], Player2.tailY[2], Player2.tailY[3], Player2.tailY[4], Player2.tailY[5], Player2.lengthStored[0], Player2.lengthStored[1], Player2.lengthStored[2], Player2.lengthStored[3], Player2.lengthStored[4]);
    printf("Food: x= %d, y= %d, nutrition: %d", foodblock.x, foodblock.y, foodblock.nutrition);
    printf("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\r\n\n\n");
}
class Playfield {
public:
    static const int width = PLAYFIELDX;
    static const int height = PLAYFIELDY;
    char grid[height][width];
    Playfield() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) grid[i][j] = ' ';
        }
    }
    void display(player player1, player player2, food food) {
        system("cls");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) grid[i][j] = 250;
        }
        grid[player1.headposY][player1.headposX] = '1';
        for (int i = 0; i < player2.length; i++) grid[player1.tailY[i]][player1.tailX[i]] = '1';
        grid[player2.headposY][player2.headposX] = '2';
        for (int i = 0; i < player2.length; i++) grid[player2.tailY[i]][player2.tailX[i]] = '2';
        grid[food.y][food.x] = 'F';
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) std::cout << grid[i][j] << ' ';
            std::cout << std::endl;
        }
    }
};
Playfield playfield;       
//main     
int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    srand(69420);
    //gamestart
    testGame();
    long long int milis = 0;
    info.gamestate = 1;
    for(int j= 0; j < 100000;){
        if(clock() > milis + 1000){
            if(j % 2 == 0){
                Player1.changeDirection(rand() % 4);
                Player2.changeDirection(rand() % 4);
            }
            //printf("playerchecks: %d, %d\r\nmovechecks: %d, %d\r\n\n\n\n",(playercheck(Player1, Player2)),(playercheck(Player2, Player1)),(Player1.movecheck()),(Player2.movecheck()));
            //testGame();
            playfield.display(Player1, Player2,foodblock);
            cout << j << endl;
            gameTick();
            milis += 1000;
            j++;
        }
        if(info.gamestate == 0);
        else if(info.gamestate == -1);
    }
    return 0;
}