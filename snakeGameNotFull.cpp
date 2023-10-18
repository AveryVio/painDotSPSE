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
        char movecheck(){// if can move then 1 else 0 /*Tested - fully working as inteded*/
            if((direction == 0) && (headposY == PLAYFIELDY + 1))return 0;
            if((direction == 1) && (headposX == PLAYFIELDX + 1))return 0;
            if((direction == 2) && (headposY == 0))return 0;
            if((direction == 3) && (headposX == 0))return 0;
            return 1;
        }
        void move(){ /*Tested - fully working as inteded*/
            if(((direction == 0) && (headposY + 1 != PLAYFIELDY + 1))||((direction == 1) && (headposY + 1 != PLAYFIELDX + 1))||((direction == 2) && (headposY - 1 != PLAYFIELDY))||((direction == 3) && (headposY - 1 != PLAYFIELDX))){//this is only for testing purposes
                if (lengthStored[0] !=0) {
                    tailX[length + 1] = tailX[length];
                    tailY[length + 1] = tailY[length];
                    length++;
                    for (int i = 4; i > 0; i--) lengthStored[i] = lengthStored[i + 1];
                    lengthStored[5] = 0;
                }
                for(int i = length - 1; i > 0; i--){
                    tailX[i] = tailX[i-1];
                    tailY[i] = tailY[i-1];
                }
                tailX[0] = headposX;
                tailY[0] = headposY;
                if ((direction == 0) && (headposY != PLAYFIELDY + 1)) headposY = headposY + 1;
                else if ((direction == 1) && (headposX != PLAYFIELDX + 1)) headposX = headposX + 1;
                else if ((direction == 2) && (headposY != 0)) headposY = headposY - 1;
                else if ((direction == 3) && (headposX != 0)) headposX = headposX - 1;
            }
        }
        void changeDirection(char requestedDirection){
            if (requestedDirection != direction && (requestedDirection + 2) % 4 != direction) {
                direction = requestedDirection;
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
    for(int v = 5; v > 0; v--) if(playerN.lengthStored[v] == 1) return v;
    return 0;
}
void playerEat(player playerN){ /*Tested - fully working as inteded*/
    if ((foodblock.x == playerN.headposX) && (foodblock.y == playerN.headposY)){
        for (int i = playerFirstStoredLength(playerN); i < 5; i++){
            if(foodblock.nutrition >= 0){
                playerN.lengthStored[i] = 1;
                foodblock.nutrition--;
            }
        }
        regenFood();
    }
}
char biggerPlayerLength(){ /*Tested - fully working as intended*/
    if(Player1.length > Player2.length) return Player1.length;
    return Player2.length;
}
char playercheck(player playerN, player playerT){// if both colide then 2, if asked player then 1 else 0
    if (playerN.headposX == playerT.headposX && playerN.headposY == playerT.headposY) return 2;
    else for (int i = 0; i < playerT.length; i++) {
        if (playerN.headposX == playerT.tailX[i] && playerN.headposY == playerT.tailY[i]) return 2;
        else if(playerN.headposX == playerN.tailX[i] && playerN.headposY == playerN.tailY[i]) return 2;
    }
    int dx = 0;
    int dy = 0;
    if (playerN.direction == 0) dy = 1;
    else if (playerN.direction == 1) dx = 1;
    else if (playerN.direction == 2) dy = -1;
    else if (playerN.direction == 3) dx = -1;
    int checkX = playerN.headposX + dx;
    int checkY = playerN.headposY + dy;
    if (checkX == playerT.headposX && checkY == playerT.headposY) return 0;
    else for (int i = 0; i < playerT.length; i++) {
        if (checkX == playerT.tailX[i] && checkY == playerT.tailY[i]) return 0;
        else if (checkX == playerN.tailX[i] && checkY == playerN.tailY[i]) return 0;
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
    if(player1movecheckResult && player2movecheckResult && playercheck12Result && playercheck21Result){
        Player1.move();
        playerEat(Player1);
        Player2.move();
        playerEat(Player2);
        cout << endl << "nowallnoplayer" << endl;
    }
    else{
        if (player1movecheckResult && player2movecheckResult) cout << "nowall" << endl;
        else{
            if((player1movecheckResult == 0) && (player2movecheckResult == 0)){
                cout << "wall" << endl;
                info.gamestate = 0;
                info.winner = -1;
            }
            else if(player1movecheckResult == 0){
                cout << "1wall" << endl;
                info.gamestate = 0;
                info.winner = 2;
                info.winnerInfo = Player2;
                info.loserInfo = Player1;
            }
            else if(player2movecheckResult == 0){
                cout << "2wall" << endl;
                info.gamestate = 0;
                info.winner = 2;
                info.winnerInfo = Player2;
                info.loserInfo = Player1;
            }
        }
        if(playercheck12Result && playercheck21Result) cout << "noplayer" << endl;
        else{
            if((playercheck12Result == 0) && (playercheck21Result == 0)){
                cout << "player" << endl;
                info.gamestate = 0;
                info.winner = -1;
            }
            else if(playercheck12Result == 0){
                cout << "1player" << endl;
                info.winner = 2;
                info.winnerInfo = Player2;
                info.loserInfo = Player1;
            }
            else if(playercheck21Result == 0){
                cout << "2player" << endl;
                info.winner = 1;
                info.winnerInfo = Player1;
                info.loserInfo = Player2;
            }
        }
    if((player1movecheckResult == 0) && (player2movecheckResult == 0) && (playercheck12Result == 0) && (playercheck21Result == 0)) cout << "idk what happened either" << endl;
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
        for (int i = 0; i <= height; i++) {
            for (int j = 0; j < width; j++) grid[i][j] = 250;
        }
    }
    void updatePlayerPositions(player& p, char symbol) {
        grid[p.headposY][p.headposX] = symbol;
        for (int i = 0; i < p.length; i++) {
            grid[p.tailY[i]][p.tailX[i]] = symbol;
        }
    }
    void predisplay(player player1, player player2, food food){
        updatePlayerPositions(player1, 250);
        updatePlayerPositions(player2, 250);
        grid[food.y][food.x] = 250;
    }
    void display(player player1, player player2, food food) {
    updatePlayerPositions(player1, '1');
    updatePlayerPositions(player2, '2');
    grid[food.y][food.x] = 'F';
    for (int i = height; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            std::cout << grid[i][j] << " ";
        }
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
        //if(clock() > milis + 1000){
            if(j % 4 == 0){
                Player1.changeDirection(rand() % 4);
                Player2.changeDirection(rand() % 4);
            }
            playfield.predisplay(Player1, Player2, foodblock);
            gameTick();
            system("cls");
            playfield.display(Player1, Player2, foodblock);
            printf("\r\n%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
            testGame();
            cout << j << endl;
            milis += 1000;
        }
    }*/
    Player1.direction = 3;
    Player1.headposX = Player2.headposX;
    Player1.headposY = Player2.headposY;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposY = Player2.headposY - 1;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposX = Player2.headposX - 1;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposY = Player2.headposY;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposY = Player2.headposY + 3;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposX = Player2.headposX;
    Player1.headposY = Player2.headposY + 4;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposX = Player2.headposX + 1;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposY = Player2.headposY + 3;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposY = Player2.headposY + 1;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposY = Player2.headposY + 1;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposX = Player1.tailX[2];
    Player1.headposY = Player1.tailY[2];
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposX = Player1.tailX[2] + 1;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    Player1.headposX = Player1.tailX[2] - 1;
    printf("%d,%d\r\n%d,%d\r\n", Player1.movecheck(), Player2.movecheck(), playercheck(Player1,Player2), playercheck(Player2,Player1));
    testGame();
    return 0;
}