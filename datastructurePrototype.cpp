#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define playfieldX 64
#define playfieldY 32

//game
class panel{
    public:
        bool gameState = false;
};
panel gamePanel;
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
        char tailX[128];
        char tailY[128];
        char direction;
        char length;
        char lengthStored[5];
        player(char playernumber){
            if(playernumber == 0) headposX = rand() % ((playfieldX / 2) + 1);
            else headposX = (playfieldX / 2) + rand() % ((playfieldX / 2) + 1);
            headposY = rand() % (playfieldY + 1);
            length = 3;
            if(playernumber == 1) direction = 0;
            else direction = 2;
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
        };
        char movecheck(){// if can move then 0 else 1 /*Tested - fully working as inteded*/
            if((direction == 0) && (headposY == playfieldY))return 0;
            if((direction == 1) && (headposX == playfieldX))return 0;
            if((direction == 2) && (headposY == 0))return 0;
            if((direction == 3) && (headposX == 0))return 0;
            return 1;
        }
        void move(){ /*Tested - fully working as inteded*/
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
            if (direction == 0) headposY = headposY + 1;
            else if (direction == 1) headposX = headposX + 1;
            else if (direction == 2) headposY = headposY - 1;
            else if (direction == 3) headposX = headposX - 1;
        }
};
player Player1(0);
player Player2(1);
food foodblock(rand() % (playfieldX + 1), rand() % (playfieldY + 1), rand() % 3);

void regenFood() { /*Tested - mabye working?? not fully sure*/
    foodblock.nutrition = (rand() % 1) + (rand() % 2) + (rand() % 3) + (rand() % 1);
    foodblock.x = rand() % (playfieldX + 1);
    foodblock.y = rand() % (playfieldY + 1);
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
        if((playerN.headposX == playerT.headposX) && (playerN.headposY + 1 == playerT.headposY)) return 1;
        for(int i = 0; i <= biggerPlayerLength(); i++){
            if((playerN.headposX == playerT.tailX[i]) && (playerN.headposY + 1 == playerT.tailY[i])) return 1;
            if((playerN.headposX == playerN.tailX[i]) && (playerN.headposY + 1 == playerN.tailY[i])) return 1;
        }
    }
    if(playerN.direction == 1){
        if((playerN.headposX + 1 == playerT.headposX) && (playerN.headposY == playerT.headposY)) return 1;
        for(int i = 0; i <= biggerPlayerLength(); i++){
            if((playerN.headposX + 1 == playerT.tailX[i]) && (playerN.headposY == playerT.tailY[i])) return 1;
            if((playerN.headposX + 1 == playerN.tailX[i]) && (playerN.headposY == playerN.tailY[i])) return 1;
        }
    }
    if(playerN.direction == 2){
        if((playerN.headposX == playerT.headposX) && (playerN.headposY - 1 == playerT.headposY)) return 1;
        for(int i = 0; i <= biggerPlayerLength(); i++){
            if((playerN.headposX == playerT.tailX[i]) && (playerN.headposY - 1 == playerT.tailY[i])) return 1;
            if((playerN.headposX == playerN.tailX[i]) && (playerN.headposY - 1 == playerN.tailY[i])) return 1;
        }
    }
    if(playerN.direction == 3){
        if((playerN.headposX - 1 == playerT.headposX) && (playerN.headposY == playerT.headposY)) return 1;
        for(int i = 0; i <= biggerPlayerLength(); i++){
            if((playerN.headposX - 1 == playerT.tailX[i]) && (playerN.headposY == playerT.tailY[i])) return 1;
            if((playerN.headposX - 1 == playerN.tailX[i]) && (playerN.headposY == playerN.tailY[i])) return 1;
        }
    }
    return 0;
};
void gameTick(){
    if ((playercheck(Player1, Player2) == 0) && (playercheck(Player2, Player1) == 0)){
        if(Player1.movecheck()) Player1.move();
        if(Player2.movecheck()) Player2.move();
        playersEat();
    }
    else{
        gamePanel.gameState = false;
    }
}
void testGame(){
    printf("Player1: x= %d, y= %d, direction= %d  tail: \r\nlength= %d, first6x= %d, %d, %d, %d, %d, %d, first6y= %d, %d, %d, %d, %d, %d \r\nlengthStored= %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\r\n\n", Player1.headposX, Player1.headposY, Player1.direction, Player1.length, Player1.tailX[0], Player1.tailX[1], Player1.tailX[2], Player1.tailX[3], Player1.tailX[4], Player1.tailX[5], Player1.tailY[0], Player1.tailY[1], Player1.tailY[2], Player1.tailY[3], Player1.tailY[4], Player1.tailY[5], Player1.lengthStored[0], Player1.lengthStored[1], Player1.lengthStored[2], Player1.lengthStored[3], Player1.lengthStored[4]);
    printf("Player2: x= %d, y= %d, direction= %d  tail: \r\nlength= %d, first6x= %d, %d, %d, %d, %d, %d, first6y= %d, %d, %d, %d, %d, %d \r\nlengthStored= %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\r\n\n", Player2.headposX, Player2.headposY, Player2.direction, Player2.length, Player2.tailX[0], Player2.tailX[1], Player2.tailX[2], Player2.tailX[3], Player2.tailX[4], Player2.tailX[5], Player2.tailY[0], Player2.tailY[1], Player2.tailY[2], Player2.tailY[3], Player2.tailY[4], Player2.tailY[5], Player2.lengthStored[0], Player2.lengthStored[1], Player2.lengthStored[2], Player2.lengthStored[3], Player2.lengthStored[4]);
    printf("Food: x= %d, y= %d, nutrition: %d", foodblock.x, foodblock.y, foodblock.nutrition);
    printf("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\r\n\n\n");
}
//main
int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    srand (69);
    //gamestart
    gamePanel.gameState = true;
    for(int nemamradmatiku = 0; nemamradmatiku < 32; nemamradmatiku++){
        printf("\r\n%d,%d\r\n%d,%d\r\n",playercheck(Player1, Player2), playercheck(Player2, Player1), Player1.movecheck(), Player1.movecheck());
        testGame();
        if ((playercheck(Player1, Player2) == 0) && (playercheck(Player2, Player1) == 0)){
            if(!Player1.movecheck()) Player1.move();
            if(!Player2.movecheck()) Player2.move();
        }
    }
    return 0;
}