#include <iostream>
#include <stdlib.h>
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
        char lengthStored[10];
        player(char playernumber){
            headposX = rand() % ((playfieldX / 2) + 1);
            headposY = rand() % (playfieldY + 1);
            direction = rand() * 2;
            length = 3;
            if (playernumber == 0){
                for (int i = 0; i < length; i++) {
                    tailX[i] = headposX;
                    tailY[i] = headposY - i;
                }
            }
            else {
                for (int i = length; i > 0; i--) {
                    tailX[i] = headposX;
                    tailY[i] = headposY + i;
                }
            }
        };
        char wallcheck(char pdir){// if wall then 0 else 1
            if((pdir == 0) && (headposY == playfieldY))return 0;
            else if((pdir == 1) && (headposX == playfieldX))return 0;
            else if((pdir == 2) && (headposY == 0))return 0;
            else if((pdir == 3) && (headposX == 0))return 0;
            else return 1;
        }
        char movecheck(){// if can move then 0 else 1
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
player Player1(0);
player Player2(1);
food foodblock(rand() % (playfieldX + 1), rand() % (playfieldY + 1), rand() % 3);
void regenFood() {
    foodblock.nutrition = rand() % 3;
    foodblock.x = rand() % (playfieldX + 1);
    foodblock.y = rand() % (playfieldY + 1);
}
void playersEat(){
    if ((foodblock.x == Player1.headposX) && (foodblock.y == Player1.headposY)){
        for (int i = foodblock.nutrition; i > 0; i--) Player1.lengthStored[i]= 1;
        regenFood();
    }
    else if ((foodblock.x == Player2.headposX) && (foodblock.y == Player2.headposY)){
        for (int i = foodblock.nutrition; i > 0; i--) Player2.lengthStored[i]= 1;
        regenFood();
    }
}
char biggerPlayerLength(){
    if(Player1.length > Player2.length) return Player1.length;
    else return Player2.length;
}
char playercheck(){// if players colide then 0 else 1
        if(Player1.direction == 0){
            for(int i = biggerPlayerLength(); i > 0; i--) if ((Player1.headposY + 1 == Player2.tailY[i]) || (Player1.headposY + 1 == Player1.tailY[i])) return 0;
        }
        else if(Player1.direction == 1){
            for(int i = biggerPlayerLength(); i > 0; i--) if ((Player1.headposX + 1 == Player2.tailX[i]) || (Player1.headposX + 1 == Player1.tailX[i])) return 0;
        }
        else if(Player1.direction == 2){
            for(int i = biggerPlayerLength(); i > 0; i--) if ((Player1.headposY - 1 == Player2.tailY[i]) || (Player1.headposY - 1 == Player1.tailY[i])) return 0;
        }
        else if(Player1.direction == 3){
            for(int i = biggerPlayerLength(); i > 0; i--) if ((Player1.headposX - 1 == Player2.tailX[i]) || (Player1.headposX - 1 == Player1.tailX[i])) return 0;
        }
};
void gameTick(){
    if (playercheck()){
        if(Player1.movecheck()) Player1.move();
        if(Player2.movecheck()) Player2.move();
        playersEat();
    }
    else{
    }
}
//main
int main(){
    cout << "This device is sponsored by the dotSPSE project" << endl;
    srand (66756362064740000);
    return 0;
}