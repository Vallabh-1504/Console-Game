// Snake Game for Windows Console (UTF-8 Based)
// Author: Vallabh Mahajan
// Description: Classic snake game with real-time input handling, collision detection, and progressive speed increase.

#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

#define maxLength 1000

// Direction characters
const char dirUp = 'U';
const char dirRight = 'R';
const char dirDown = 'D';
const char dirLeft = 'L';

// Unicode representations (can be replaced with ASCII alternatives)
const string WALL = "█";        // "#"
const string SNAKE_HEAD = "◎";  // "@"
const string SNAKE_BODY = "●";  // "O"
const string FOOD = "◉";        // "o"

// Console dimensions
int consoleWidth, consoleHeight;


// Initialize console- capture dimensions and hide cursor
void initScreen(){
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hconsole, &csbi);

    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    CONSOLE_CURSOR_INFO cci = {100, false};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

// 2D point representing coordinates
struct Point{
    int xCoord;
    int yCoord;

    Point(int x = 0, int y = 0){
        xCoord = x;
        yCoord = y;
    }
};

// Move console cursor to (x, y)
void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Snake class
class Snake{
    int length;
    char direction;
public:
    Point body[maxLength];

    Snake(int x, int y){
        length = 1;
        body[0] = Point(x, y);
        direction = dirRight;
    }

    int getLength(){
        return length;
    }

    // Update direction, prevent direct reversal
    void changeDirection(char newDirection){
        if(newDirection == dirUp && direction != dirDown){
            direction = newDirection;
        }
        else if(newDirection == dirRight && direction != dirLeft){
            direction = newDirection;
        }
        else if(newDirection == dirDown && direction != dirUp){
            direction = newDirection;
        }
        else if(newDirection == dirLeft && direction != dirRight){
            direction = newDirection;
        }

    }

    // Move snake forward, update old tail, detect collisions, handle food
    bool move(Point &food, Point &oldTail){
        oldTail = body[length-1];

        // shift body
        for(int i = length; i > 0; i--){
            body[i] = body[i-1];
        }

        // update head
        if(direction == dirUp){
            body[0].yCoord--;
        }
        else if(direction == dirRight){
            body[0].xCoord++;
        }
        else if(direction == dirDown){
            body[0].yCoord++;
        }
        else if(direction == dirLeft){
            body[0].xCoord--;
        }

        // wall collision
        if(body[0].xCoord <= 0 || body[0].xCoord >= consoleWidth - 1){
            return false;
        }
        if(body[0].yCoord <= 1 || body[0].yCoord >= consoleHeight - 1){
            return false;
        }

        // self collision
        for(int i = 1; i < length; i++){
            if(body[i].xCoord == body[0].xCoord && body[i].yCoord == body[0].yCoord){
                return false;
            }
        }


        // snake eats food
        if(food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord){
            // created next point to tail
            // Beep(1000, 100);
            body[length] = oldTail;
            length++;
        }

        return true;
    }
};

// Game Board
class Board{
    Snake *snake;
    Point food;
    int score;

public:
    Board(){
        snake = new Snake(consoleWidth/2, consoleHeight/2);
        score = 0;
        spawnFood();
    }

    ~Board(){
        delete snake;
    }

    int getScore(){
        return score;
    }

    // place food randomly on empty cell
    void spawnFood(){
        while(true){
            int x = rand() % (consoleWidth - 2) + 1;
            int y = rand() % (consoleHeight - 4) + 3;

            bool conflict = false;
            for(int i = 0; i < snake->getLength(); i++){
                if(x == snake->body[i].xCoord && y == snake->body[i].yCoord){
                    conflict = true;
                    break;
                }
            }
            if(conflict == false){
                food = Point(x, y);
                break;
            }
        }

    }

        // Render board frame, snake, food, and erase tail 
    void draw(Point &oldTail){

        // walls (boundary)
        for(int x = 0; x < consoleWidth; x++){
            gotoxy(x, 1);
            cout << WALL;

            gotoxy(x, consoleHeight);
            cout << WALL;
        }

        for(int y = 1; y < consoleHeight; y++){
            gotoxy(0, y);
            cout << WALL;

            gotoxy(consoleWidth - 1, y);
            cout<< WALL;
        }

        // erase old tail
        gotoxy(oldTail.xCoord, oldTail.yCoord);
        cout<< ' ';


        // draw snake
        for(int i = 0; i < snake->getLength(); i++){
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord); // go to the point on snake body
            if(i == 0) cout << SNAKE_HEAD;
            else cout << SNAKE_BODY;
        }

        // draw food
        gotoxy(food.xCoord, food.yCoord);
        cout << FOOD; 
    }
 
    void displayScore(){
        gotoxy(consoleWidth/2 - 3, 0);
        cout << "Score : " << score << " ";
    }
    
    
    // Progress game state
    bool update(Point &oldTail){
        bool isAlive = snake->move(food, oldTail);

        if(isAlive == false){
            return false;
        }
        
        // Food eaten
        if(food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord){
            score++;
            spawnFood();
        }

        return true;
    }

    // Handle input asynchronously
    void getInput(){
        if(_kbhit()){
            int key = _getch();

            if(key == 'w' || key == 'W'){
                snake->changeDirection(dirUp);
            }
            else if(key == 'd' || key == 'D'){
                snake->changeDirection(dirRight);
            }
            else if(key == 's' || key == 'S'){
                snake->changeDirection(dirDown);
            }
            else if(key == 'a' || key == 'A'){
                snake->changeDirection(dirLeft);
            }
        }
    }

};

// show game intro screen
void startScreen(){
    system("cls");
    int x = consoleWidth / 2;
    int y = consoleHeight / 3;

    gotoxy(x - 15, y - 5);
    cout << "╔═══════════════════════════════════╗";
    gotoxy(x - 15, y - 4);
    cout << "║           SNAKE GAME              ║";
    gotoxy(x - 15, y - 3);
    cout << "╠═══════════════════════════════════╣";
    gotoxy(x - 15, y - 2);
    cout << "║  Controls:                        ║";
    gotoxy(x - 15, y - 1);
    cout << "║   ▸ Use W A S D to move           ║";
    gotoxy(x - 15, y + 0);
    cout << "║   ▸ Eat food to grow              ║";
    gotoxy(x - 15, y + 1);
    cout << "║   ▸ Avoid walls and yourself      ║";
    gotoxy(x - 15, y + 2);
    cout << "╠═══════════════════════════════════╣";
    gotoxy(x - 15, y + 3);
    cout << "║  Press any key to start...        ║";
    gotoxy(x - 15, y + 4);
    cout << "╚═══════════════════════════════════╝";

    _getch();
    system("cls");
}

// show game over screen and prompt replay
bool endScreen(int finalScore){
    system("cls");
    int x = consoleWidth / 2;
    int y = consoleHeight / 3;

    gotoxy(x - 18, y - 3);
    cout << "╔════════════════════════════════╗";
    gotoxy(x - 18, y - 2);
    cout << "║         GAME OVER              ║";
    gotoxy(x - 18, y - 1);
    cout << "╠════════════════════════════════╣";
    gotoxy(x - 18, y + 0);
    cout << "║  Your Score: " << setw(18) << left << finalScore << "║";
    gotoxy(x - 18, y + 1);
    cout << "╠════════════════════════════════╣";
    gotoxy(x - 18, y + 2);
    cout << "║  Play Again? (Y/N):            ║";
    gotoxy(x - 18, y + 3);
    cout << "╚════════════════════════════════╝";
    
    char c = _getch();
    while(true){
        if(c == 'Y' || c == 'y'){
            system("cls");
            return true;
        }
        else if(c == 'n' || c == 'N'){
            system("cls");
            return false;
        }
        else{
            c = _getch();
        }
    }
}

int main(){
    // srand((unsigned)time(nullptr)); // randomize the food positions
    system("chcp 65001 > nul");  // enable UTF-8
    initScreen();
    startScreen();

    while(true){
        char playAgain = 'Y';
        Board board;
        Point oldTail;
        int delay = 100;
        int lastMilestoneScore = 0;

        while(board.update(oldTail)){
            board.getInput();
            board.draw(oldTail);
            board.displayScore();
            Sleep(delay);

            // speed up game after every 2 points
            if(board.getScore() >= lastMilestoneScore + 2 && delay > 30){
                delay -= 15;
                lastMilestoneScore = board.getScore();
            }
        }

        if(endScreen(board.getScore()) == false){
            break;
        }
    }
    return 0;
}
