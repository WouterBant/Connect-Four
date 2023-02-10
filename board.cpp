#include "board.h"

Board::Board() {
    width = 7;
    height = 6;
    board.resize(height, std::vector<States>(width, States::EMPTY));
}

Board::Board(const int x, const int y) {
    width = x;
    height = y;
    board.resize(height, std::vector<States>(width, States::EMPTY));
}

void Board::show_board() {
    for (const auto &col : board) {
        for (const auto &element : col) {
            if (element == States::EMPTY) {
                std::cout << ". ";
            }
            else if (element == States::CROSS) {
                std::cout << "X ";
            }
            else {
                std::cout << "O ";
            }
        }
        std::cout << std::endl;
    }
}

std::set<int> Board::available_positions() {
    // look which columns are not full
    std::set<int> columns;
    for (int c = 0; c < width; c++) {
        if (board[0][c] == States::EMPTY) columns.insert(c);
    }
    return columns;
}

int Board::place_stone(int col, States state) {
    for (int row = height - 1; row >= 0; row--) {
        if (board[row][col] == States::EMPTY) {
            board[row][col] = state;
            return row;
        }
    }
    return -1;
}

bool Board::is_solved(int row, int col, States state) {
    // down
    bool solved = true;
    if (row <= height - 1 - 3) {
        for (int d = 1; d <= 3; d++) {
            if (board[row+d][col] != state) solved = false;
        }
    }
    else {
        solved = false;
    }
    if (solved) return true;

    // horizontal
    int right = 0, left = 0;
    for (int d = 1; d <=3; d++) {
        if (col + d < width && board[row][col+d] == state) {
            right += 1;
        }
        else break;
    }
    for (int d = 1; d <=3; d++) {
        if (col - d >= 0 && board[row][col-d] == state) {
            left += 1;
        }
        else break;
    }
    if (left + right + 1 >= 4) return true;

    // neg diag
    int topLeft = 0, bottomRight = 0;
    for (int d = 1; d <=3; d++) {
        if (row - d >= 0 && col - d >= 0 && board[row-d][col-d] == state) {
            topLeft += 1;
        }
        else break;
    }
    for (int d = 1; d <=3; d++) {
        if (row + d < height && col + d < width && board[row+d][col+d] == state) {
            bottomRight += 1;
        }
        else break;
    }
    if (topLeft + bottomRight + 1 >= 4) return true;

    // pos diag
    int bottomLeft = 0, topRight = 0;
    for (int d = 1; d <=3; d++) {
        if (row + d < height && col - d >= 0 && board[row+d][col-d] == state) {
            bottomLeft += 1;
        }
        else break;
    }
    for (int d = 1; d <=3; d++) {
        if (row - d >= 0 && col + d < width && board[row-d][col+d] == state) {
            topRight += 1;
        }
        else break;
    }
    if (bottomLeft + topRight + 1 >= 4) return true;

    return false;
}