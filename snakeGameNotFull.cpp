/*
Double The Length, Double the lag.

version: 0.0.2
usage compatibility: console

functionality information:
    game engine functional (probably)
    render options
        console(buggy, not fixing since it wont be in produced versions anyway)
        pure numbers
    input - not implemented
*/

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <Windows.h>//for windows console
//definitions for usefull to update stuff
#define PLAYFIELDX 32
#define PLAYFIELDY 16
#define MAXSNAKELENGTH 256
#define SNAKESTARTLENGTH 3
#define FOODRANDCALC (2 * (rand() % 1)) + (rand() % 2) + (rand() % 3)
//variables for preformance increases
char snakecheck12Result;
char snakecheck21Result;
char snake1movecheckResult;
char snake2movecheckResult;
//code
class food{//class for food objects
    public:
        char x;
        char y;
        char nutrition;
        food(char x, char y, char val){// constructor for food
            x = x;
            y = y;
            nutrition = val;
        }
};
class snake{// class fo both snakes
    public:
        char headposX;
        char headposY;
        char tailX[MAXSNAKELENGTH];
        char tailY[MAXSNAKELENGTH];
        char direction;
        char length;
        char lengthStored[5];
        snake(char snakenumber){// consstructor for snake
            if(snakenumber == 0) headposX = rand() % ((PLAYFIELDX / 2) + 1);
            else headposX = (PLAYFIELDX / 2) + rand() % ((PLAYFIELDX / 2) + 1);
            headposY = ((PLAYFIELDY + 1) / 8) + rand() % ((PLAYFIELDY + 1) / 4);
            length = SNAKESTARTLENGTH;
            if(snakenumber == 0) direction = 0;
            else direction = 2;
            for (char i = 0; i <= 5; i++) lengthStored[i] = 0;
            if (snakenumber == 0){//snake1 tail
                for (char i = 0; i < length; i++) {
                    tailX[i] = headposX;
                    tailY[i] = headposY - i - 1;
                }
                return;
            }
            //snake2 tail
            for (char i = length - 1; i >= 0; i--) {
                tailX[i] = headposX;
                tailY[i] = headposY + i + 1;
            }
        }
        char movecheck(){// if snake can move if yes then 1 else 0
            if(direction == 0) if(headposY == PLAYFIELDY + 1)return 0;
            if(direction == 1) if(headposX == PLAYFIELDX + 1)return 0;
            if(direction == 2) if(headposY == 0)return 0;
            if(direction == 3) if(headposX == 0)return 0;
            return 1;
        }
        void addLength(){//ads length from stored length to snake
            tailX[length + 1] = tailX[length];
            tailY[length + 1] = tailY[length];
            length++;
            for (char i = 0; i < 4; i++) lengthStored[i] = lengthStored[i + 1];
            lengthStored[4] = 0;
        }
        void move(){//moves the snake
            if(((direction == 0) && (headposY + 1 != PLAYFIELDY + 1))||((direction == 1) && (headposY + 1 != PLAYFIELDX + 1))||((direction == 2) && (headposY - 1 != PLAYFIELDY))||((direction == 3) && (headposY - 1 != PLAYFIELDX))){//this is only for testing purposes
                if (lengthStored[0] != 0) addLength();
                //move tail
                for(char i = length - 1; i > 0; i--){
                    tailX[i] = tailX[i-1];
                    tailY[i] = tailY[i-1];
                }
                tailX[0] = headposX;
                tailY[0] = headposY;
                //move head
                if ((direction == 0) && (headposY != PLAYFIELDY + 1)) headposY = headposY + 1;
                else if ((direction == 1) && (headposX != PLAYFIELDX + 1)) headposX = headposX + 1;
                else if ((direction == 2) && (headposY != 0)) headposY = headposY - 1;
                else if ((direction == 3) && (headposX != 0)) headposX = headposX - 1;
            }
        }
        void changeDirection(char requestedDirection){
            if (requestedDirection != direction && (requestedDirection + 2) % 4 != direction) direction = requestedDirection;
        }
        char foodColiding();
        char firstStoredLength(){//returns higherst stored length
            for(char v = 5; v >= 0; v--) if(lengthStored[v] == 1) return v;
            return 0;
        }
        void snakeEat();
};
snake Snake1(0);
snake Snake2(1);
food foodblock(rand() % (PLAYFIELDX + 1), rand() % (PLAYFIELDY + 1), FOODRANDCALC);
char biggerSnakeLength(){//returns length of the bigger snake
    if(Snake1.length > Snake2.length) return Snake1.length;
    return Snake2.length;
}
char snake::foodColiding(){
    if (foodblock.x == headposX && foodblock.y == headposY) return 1;
    else for (int i = 0; i < length; i++) if(foodblock.x == tailX[i] && foodblock.y == tailY[i]) return 1;
    else return 0;
}
void regenFood() {//respawns food at another location
    do{
        foodblock.nutrition = (rand() % 1) + (rand() % 3) + (rand() % 1);
        foodblock.x = rand() % (PLAYFIELDX + 1);
        foodblock.y = rand() % (PLAYFIELDY + 1);
    } while(Snake1.foodColiding() || Snake2.foodColiding());
}
void snake::snakeEat(){//checks if snake can eat if yes, eats the whole food and respawns it
    if ((foodblock.x == headposX) && (foodblock.y == headposY)){
        for (char n = firstStoredLength(); n <= 5; n++){
            if(foodblock.nutrition > 0){
            lengthStored[n] = 1;
            foodblock.nutrition--;
        }
    }
    regenFood();
    }
}
char snakecheck(snake snakeN, snake snakeT){// if both colide then 2, if asked snake then 1 else 0
    //offset based on direction
    char dx = 0;
    char dy = 0;
    if (snakeN.direction == 0) dy = 1;
    else if (snakeN.direction == 1) dx = 1;
    else if (snakeN.direction == 2) dy = -1;
    else if (snakeN.direction == 3) dx = -1;
    //use offset
    int checkX = snakeN.headposX + dx;
    int checkY = snakeN.headposY + dy;
    //actual checking
    if (checkX == snakeT.headposX && checkY == snakeT.headposY) return 0;//if heads colide
    else if((checkX + dx == snakeT.headposX && checkY + dy == snakeT.headposY) && ((snakeN.direction % 2) == (snakeT.direction % 2))) return 0;//if snakes colide face to face (this is an edge case)
    else for (int i = 0; i < snakeT.length; i++) {//if head colides body
        if (checkX == snakeT.tailX[i] && checkY == snakeT.tailY[i]) return 0;
        else if (checkX == snakeN.tailX[i] && checkY == snakeN.tailY[i]) return 0;
    }
    return 1;
};
class gameInfo{// class of information for cloud backup
    public:
        uint32_t gemeid;
        char gamestate;
        char winner;
        snake winnerInfo;
        snake loserInfo;
        gameInfo(char gamestatep) : winnerInfo(-1), loserInfo(-1){
            gamestate = gamestatep;
        }
        void winnerReporter(char winner){//sets the winner and the loser for sending to the cloud
            winner = winner;
            if(winner == 1){
                winnerInfo = Snake1;
                loserInfo = Snake2;
            }
            else if(winner == 0) {
                winnerInfo = Snake2;
                loserInfo = Snake1;
            }
        }
};
gameInfo info(0);
void gameTick(){//exactly what the name says
    Snake1.move();
    Snake1.snakeEat();
    Snake2.move();
    Snake2.snakeEat();
    cout << endl << "nowallnosnake" << endl;
}
void AbsoluteSolver(){// managed the game engine and win/loose conitions
    //checks all nessecary stuff
    snakecheck12Result = snakecheck(Snake1, Snake2);
    snakecheck21Result = snakecheck(Snake2, Snake1);
    snake1movecheckResult = Snake1.movecheck();
    snake2movecheckResult = Snake2.movecheck();
    //if no collision happened then uses game tick
    if(snake1movecheckResult && snake2movecheckResult && snakecheck12Result && snakecheck21Result)gameTick();
    //else stops the game and prepares winner
    else{
        info.gamestate = 0;
        if (snake1movecheckResult && snake2movecheckResult) cout << "nowall" << endl;
        else{
            if((snake1movecheckResult == 0) && (snake2movecheckResult == 0)){
                cout << "wall" << endl;
                info.winnerReporter(-1);
            }
            else if(snake1movecheckResult == 0){
                cout << "1wall" << endl;
                info.winnerReporter(2);
            }
            else if(snake2movecheckResult == 0){
                cout << "2wall" << endl;
                info.winnerReporter(1);
            }
        }
        if(snakecheck12Result && snakecheck21Result) cout << "nosnake" << endl;
        else{
            if((snakecheck12Result == 0) && (snakecheck21Result == 0)){
                cout << "snake" << endl;
                info.winnerReporter(-1);
            }
            else if(snakecheck12Result == 0){
                cout << "1snake" << endl;
                info.winnerReporter(2);
            }
            else if(snakecheck21Result == 0){
                cout << "2snake" << endl;
                info.winnerReporter(1);
            }
        }
    if((snake1movecheckResult == 0) && (snake2movecheckResult == 0) && (snakecheck12Result == 0) && (snakecheck21Result == 0)) cout << "idk what happened either" << endl;
    }
}
void testGame(){//for testing only - prints most needed values of the game
    printf("Snake1: x= %d, y= %d, direction= %d  tail: \r\nlength= %d, first6x= %d, %d, %d, %d, %d, %d, first6y= %d, %d, %d, %d, %d, %d \r\nlengthStored= %d, %d, %d, %d, %d\r\n\n", Snake1.headposX, Snake1.headposY, Snake1.direction, Snake1.length, Snake1.tailX[0], Snake1.tailX[1], Snake1.tailX[2], Snake1.tailX[3], Snake1.tailX[4], Snake1.tailX[5], Snake1.tailY[0], Snake1.tailY[1], Snake1.tailY[2], Snake1.tailY[3], Snake1.tailY[4], Snake1.tailY[5], Snake1.lengthStored[0], Snake1.lengthStored[1], Snake1.lengthStored[2], Snake1.lengthStored[3], Snake1.lengthStored[4]);
    printf("Snake2: x= %d, y= %d, direction= %d  tail: \r\nlength= %d, first6x= %d, %d, %d, %d, %d, %d, first6y= %d, %d, %d, %d, %d, %d \r\nlengthStored= %d, %d, %d, %d, %d\r\n\n", Snake2.headposX, Snake2.headposY, Snake2.direction, Snake2.length, Snake2.tailX[0], Snake2.tailX[1], Snake2.tailX[2], Snake2.tailX[3], Snake2.tailX[4], Snake2.tailX[5], Snake2.tailY[0], Snake2.tailY[1], Snake2.tailY[2], Snake2.tailY[3], Snake2.tailY[4], Snake2.tailY[5], Snake2.lengthStored[0], Snake2.lengthStored[1], Snake2.lengthStored[2], Snake2.lengthStored[3], Snake2.lengthStored[4]);
    printf("Food: x= %d, y= %d, nutrition: %d", foodblock.x, foodblock.y, foodblock.nutrition);
    printf("\r\n------------------------------------------------------------------------------------------------------");
    printf("\r\n\n\n");
}
class Playfield {//for testing only - used to display the playfield
public:
    static const int width = PLAYFIELDX;
    static const int height = PLAYFIELDY;
    char grid[height][width];
    Playfield() {//playfield constructor
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) grid[i][j] = 250;
        }
    }
    void updateSnakePositions(snake& p, char symbol) {//updated snake postions
        grid[p.headposY][p.headposX] = symbol;
        for (int i = 0; i < p.length; i++) {
            grid[p.tailY[i]][p.tailX[i]] = symbol;
        }
    }
    void predisplay(snake snake1, snake snake2, food food){//fixes visual bug
        updateSnakePositions(snake1, 250);
        updateSnakePositions(snake2, 250);
        grid[food.y][food.x] = 250;
    }
    void display(snake snake1, snake snake2, food food) {// displaying playfield
        //updates postions
        updateSnakePositions(snake1, '1');
        updateSnakePositions(snake2, '2');
        grid[food.y][food.x] = 'F';
        //prints playfield
        for (int i = height; i >= 0; i--) {
            for (int j = 0; j < width; j++){
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
            if(clock() > milis + 333){
            if(GetKeyState('W') & 0x8000)Snake1.changeDirection(0);
            if(GetKeyState('A') & 0x8000)Snake1.changeDirection(3);
            if(GetKeyState('S') & 0x8000)Snake1.changeDirection(2);
            if(GetKeyState('D') & 0x8000)Snake1.changeDirection(1);
            if(GetKeyState('I') & 0x8000)Snake2.changeDirection(0);
            if(GetKeyState('J') & 0x8000)Snake2.changeDirection(3);
            if(GetKeyState('K') & 0x8000)Snake2.changeDirection(2);
            if(GetKeyState('L') & 0x8000)Snake2.changeDirection(1);
            playfield.predisplay(Snake1, Snake2, foodblock);
            AbsoluteSolver();
            system("cls");
            playfield.display(Snake1, Snake2, foodblock);
            //printf("\r\n%d,%d\r\n%d,%d\r\n", Snake1.movecheck(), Snake2.movecheck(), snakecheck(Snake1,Snake2), snakecheck(Snake2,Snake1));
            testGame();
            cout << j << endl;
            milis += 333;
            j++;
        }
    }
    return 0;
}