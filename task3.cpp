#include <iostream>

char b[9] = {'1','2','3','4','5','6','7','8','9'};
char p = 'X';
int m;

void showBoard() {
    std::cout << b[0] << " " << b[1] << " " << b[2] << "\n";
    std::cout << b[3] << " " << b[4] << " " << b[5] << "\n";
    std::cout << b[6] << " " << b[7] << " " << b[8] << "\n";
}

void move() {
    std::cout << "Player " << p << ", enter move (1-9): ";
    std::cin >> m;
    if (b[m-1] != 'X' && b[m-1] != 'O') b[m-1] = p;
    else {
        std::cout << "Invalid move! Try again.\n";
        move();
    }
}

bool win() {
    return (b[0] == b[1] && b[1] == b[2]) || (b[3] == b[4] && b[4] == b[5]) || (b[6] == b[7] && b[7] == b[8]) || 
           (b[0] == b[3] && b[3] == b[6]) || (b[1] == b[4] && b[4] == b[7]) || (b[2] == b[5] && b[5] == b[8]) ||
           (b[0] == b[4] && b[4] == b[8]) || (b[2] == b[4] && b[4] == b[6]);
}

bool draw() {
    for (int i = 0; i < 9; i++) {
        if (b[i] != 'X' && b[i] != 'O') return false;
    }
    return true;
}

void switchPlayer() {
    p = (p == 'X') ? 'O' : 'X';
}

int main() {
    while (true) {
        showBoard();
        move();
        if (win()) {
            showBoard();
            std::cout << "Player " << p << " wins!\n";
            break;
        }
        if (draw()) {
            showBoard();
            std::cout << "It's a draw!\n";
            break;
        }
        switchPlayer();
    }
    return 0;
}