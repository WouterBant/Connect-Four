#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <set>
#include <iostream>

enum class States {
    EMPTY,
    CROSS,
    CIRCLE
};

class Board {
private:
    int height, width;
    std::vector<std::vector<States>> board;

public:
    Board();
    Board(const int x, const int y);
    void show_board();
    std::set<int> available_positions();
    int place_stone(int col, States state);
    bool is_solved(int row, int col, States state);
};

#endif