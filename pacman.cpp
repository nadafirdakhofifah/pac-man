#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WIDTH = 15;
const int HEIGHT = 7;

char map[HEIGHT][WIDTH] = {
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#'},
    {'#',' ','#','#',' ','#','#',' ','#',' ','#','#',' ','#','#'},
    {'#',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ','#'},
    {'#','#','#',' ','#','#','#',' ','#','#','#','#','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
};

// Posisi umum
struct Position {
    int x, y;
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

// ===== DOT CLASS =====
class Dot {
public:
    Position pos;
    static int totalDots;

    Dot(int x, int y) {
        pos = {x, y};
        totalDots++;
    }

    ~Dot() {
        totalDots--;
    }
};

int Dot::totalDots = 0;

// ===== ABSTRACT CHARACTER =====
class Character {
protected:
    Position pos;
    string symbol;

public:
    Character(int x, int y, string s) : pos{x, y}, symbol(s) {}

    virtual void move(char input = ' ') = 0;
    virtual string getSymbol() const { return symbol; }

    Position getPosition() const { return pos; }

    void setPosition(Position p) { pos = p; }

    bool canMoveTo(int x, int y) {
        return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && map[y][x] != '#';
    }

    virtual ~Character() {
        cout << "Character " << symbol << " destroyed.\n";
    }
};

// ===== PACMAN =====
class Pacman : public Character {
private:
    int score = 0;
    int lives = 3;
    Position startPos;

public:
    Pacman() : Character(1, 1, "P"), startPos{1, 1} {}

    void move(char input) override {
        int newX = pos.x, newY = pos.y;
        if (input == 'w') newY--;
        else if (input == 's') newY++;
        else if (input == 'a') newX--;
        else if (input == 'd') newX++;

        if (canMoveTo(newX, newY)) {
            pos = {newX, newY};
        }
    }

    void addScore(int value) {
        score += value;
    }

    int getScore() const { return score; }

    int getLives() const { return lives; }

    void loseLife() {
        lives--;
        pos = startPos;
    }

    ~Pacman() {
        cout << "Pacman destroyed.\n";
    }
};

// ===== GHOST =====
class Ghost : public Character {
private:
    Position startPos;

public:
    Ghost(int x, int y) : Character(x, y, "G"), startPos{x, y} {}

    void move(char input = ' ') override {
        int dir = rand() % 4;
        int newX = pos.x, newY = pos.y;
        if (dir == 0) newY--;
        else if (dir == 1) newY++;
        else if (dir == 2) newX--;
        else if (dir == 3) newX++;

        if (canMoveTo(newX, newY)) {
            pos = {newX, newY};
        }
    }

    void reset() {
        pos = startPos;
    }

    ~Ghost() {
        cout << "Ghost destroyed.\n";
    }
};

// ===== GAME DISPLAY =====
void draw(Pacman& pacman, Ghost& ghost, vector<Dot*>& dots) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Position current = {x, y};

            if (pacman.getPosition() == current) cout << pacman.getSymbol();
            else if (ghost.getPosition() == current) cout << ghost.getSymbol();
            else {
                bool isDot = false;
                for (auto& dot : dots) {
                    if (dot->pos == current) {
                        cout << '.';
                        isDot = true;
                        break;
                    }
                }

                if (!isDot) cout << map[y][x];
            }
        }
        cout << endl;
    }

    cout << "Skor: " << pacman.getScore()
         << " | Nyawa: " << pacman.getLives()
         << " | Dot tersisa: " << Dot::totalDots << endl;
}

// ===== MAIN GAME =====
int main() {
    srand(time(0));

    Pacman pacman;
    Ghost ghost(WIDTH - 2, HEIGHT - 2);

    vector<Dot*> dots;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == ' ') {
                dots.push_back(new Dot(x, y));
            }
        }
    }

    while (true) {
        draw(pacman, ghost, dots);

        cout << "WASD untuk bergerak: ";
        char input;
        cin >> input;

        pacman.move(input);
        ghost.move();

        // Kena ghost?
        if (pacman.getPosition() == ghost.getPosition()) {
            cout << "Oops! Kamu ketemu hantu! 😱\n";
            pacman.loseLife();
            ghost.reset();
            if (pacman.getLives() <= 0) {
                cout << "Game Over! Nyawamu habis.\n";
                break;
            }
            continue; // lanjut setelah respawn
        }

        // Makan dot
        for (int i = 0; i < dots.size(); i++) {
            if (dots[i]->pos == pacman.getPosition()) {
                delete dots[i];
                dots.erase(dots.begin() + i);
                pacman.addScore(10);
                break;
            }
        }

        if (dots.empty()) {
            draw(pacman, ghost, dots);
            cout << "Selamat! Kamu makan semua dot dan menang!\n";
            break;
        }
    }

    for (auto d : dots) {
        delete d;
    }

    return 0;
}
