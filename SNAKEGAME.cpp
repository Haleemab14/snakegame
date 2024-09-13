#include <iostream>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()

using namespace std;

const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

struct Point {
    int xCoord, yCoord;
    Point(int x = 0, int y = 0) : xCoord(x), yCoord(y) {}
};

class Snake {
public:
    vector<Point> body;
    char direction;
    int length;

    Snake(int x, int y) {
        length = 1;
        body.push_back(Point(x, y));
        direction = DIR_RIGHT;
    }

    void changeDirection(char newDirection) {
        if ((newDirection == DIR_UP && direction != DIR_DOWN) ||
            (newDirection == DIR_DOWN && direction != DIR_UP) ||
            (newDirection == DIR_LEFT && direction != DIR_RIGHT) ||
            (newDirection == DIR_RIGHT && direction != DIR_LEFT)) {
            direction = newDirection;
        }
    }

    bool move(Point food) {
        Point nextHead = body[0];

        switch (direction) {
        case DIR_UP: nextHead.yCoord -= 1; break;
        case DIR_DOWN: nextHead.yCoord += 1; break;
        case DIR_LEFT: nextHead.xCoord -= 1; break;
        case DIR_RIGHT: nextHead.xCoord += 1; break;
        }

        // Move the snake body
        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }
        body[0] = nextHead;

        // Check if snake bites itself
        for (int i = 1; i < length; i++) {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord) {
                return false;  // Snake is dead
            }
        }

        // Check if snake eats food
        if (food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord) {
            body.push_back(Point(body[length - 1].xCoord, body[length - 1].yCoord));
            length++;
            return true;  // Snake eats food
        }

        return true;  // Snake is alive
    }
};

class Board {
public:
    int width, height;
    Snake* snake;
    Point food;
    int score;

    Board(int w, int h) : width(w), height(h), score(0) {
        snake = new Snake(width / 2, height / 2);
        spawnFood();
    }

    ~Board() {
        delete snake;
    }

    void spawnFood() {
        food.xCoord = rand() % width;
        food.yCoord = rand() % height;
    }

    void draw() {
        system("cls");  // Clear the screen (for Windows)

        // Draw the board with snake and food
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                bool isSnake = false;

                for (int i = 0; i < snake->length; i++) {
                    if (snake->body[i].xCoord == x && snake->body[i].yCoord == y) {
                        isSnake = true;
                        break;
                    }
                }

                if (isSnake) {
                    cout << "O";  // Snake body
                }
                else if (x == food.xCoord && y == food.yCoord) {
                    cout << "o";  // Food
                }
                else {
                    cout << ".";  // Empty space
                }
            }
            cout << endl;
        }

        cout << "Score: " << score << endl;
    }

    bool update() {
        if (snake->move(food)) {
            if (snake->body[0].xCoord == food.xCoord && snake->body[0].yCoord == food.yCoord) {
                score++;
                spawnFood();
            }
            return true;  // Snake is still alive
        }
        return false;  // Snake is dead
    }

    void getInput() {
        char key;
        cin >> key;
        switch (key) {
        case 'w': snake->changeDirection(DIR_UP); break;  //for up
        case 'a': snake->changeDirection(DIR_LEFT); break; //for left
        case 's': snake->changeDirection(DIR_DOWN); break;  //for down
        case 'd': snake->changeDirection(DIR_RIGHT); break;  //for right
        }
    }
};

int main() {
    srand(time(0));  // Seed random number generator
    Board board(150, 20);  // Create a 150x20 board
    while (board.update()) {
        board.draw();
        board.getInput();
    }
    cout << "Game Over! Final score: " << board.score << endl;
    return 0;
}


