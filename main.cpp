#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

const int width = 30;
const int height = 20;

class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

class Wall {
public:
    bool isWall(int x, int y) const {
        return (x == 0 || x == width - 1 || y == 0 || y == height - 1);
    }
};

class Food {
public:
    Point position;
    Food() { generate(); }
    void generate() {
        position.x = rand() % (width - 2) + 1;
        position.y = rand() % (height - 2) + 1;
    }
};

class Snake {
public:
    vector<Point> body;
    char direction;
    bool alive;
    int speed;

    Snake() {
        body.push_back(Point(width / 2, height / 2));
        direction = 'L';
        alive = true;
        speed = 100;
    }

    void move() {
        Point newHead = body[0];
        switch (direction) {
            case 'U': newHead.y--; break;
            case 'D': newHead.y++; break;
            case 'L': newHead.x--; break;
            case 'R': newHead.x++; break;
        }

        // Warp through walls instead of dying
        if (newHead.x < 0) newHead.x = width - 1;
        else if (newHead.x >= width) newHead.x = 0;
        if (newHead.y < 0) newHead.y = height - 1;
        else if (newHead.y >= height) newHead.y = 0;

        for (auto& segment : body)
            if (newHead.x == segment.x && newHead.y == segment.y)
                alive = false;

        if (alive) {
            body.insert(body.begin(), newHead);
            body.pop_back();
        }
    }

    void grow() {
        body.push_back(body.back());
        if (speed > 50) speed -= 5;
    }
};

class Game {
public:
    Snake snake;
    Food food;
    Wall wall;
    bool gameOver;
    int score;

    Game() {
        gameOver = false;
        score = 0;
    }

    void draw() {
        system("cls");
        cout << "Score: " << score << endl;
        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (wall.isWall(x, y)) {
                    cout << "#";
                } else if (x == food.position.x && y == food.position.y) {
                    cout << "F";
                } else {
                    bool printed = false;
                    for (auto& segment : snake.body) {
                        if (x == segment.x && y == segment.y) {
                            cout << "O";
                            printed = true;
                            break;
                        }
                    }
                    if (!printed) cout << " ";
                }
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;
    }

    void input() {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
                case 'w': if (snake.direction != 'D') snake.direction = 'U'; break;
                case 's': if (snake.direction != 'U') snake.direction = 'D'; break;
                case 'a': if (snake.direction != 'R') snake.direction = 'L'; break;
                case 'd': if (snake.direction != 'L') snake.direction = 'R'; break;
            }
        }
    }

    void logic() {
        snake.move();
        if (!snake.alive || score >= 40) gameOver = true;
        if (snake.body[0].x == food.position.x && snake.body[0].y == food.position.y) {
            snake.grow();
            food.generate();
            score += 10;
        }
    }

    void run() {
        while (!gameOver) {
            draw();
            input();
            logic();
            Sleep(snake.speed);
        }
        cout << (score >= 40 ? "You Win! " : "Game Over! ") << "Final Score: " << score << endl;
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
