#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "board.h"
#include "board.cpp"


int main() {
    Board game(7, 6);

    bool player1 = true;
    std::string col;
    int col_n, row_n;
    States state;

    game.show_board();
    
    while (true) {
        std::set<int> free_positions = game.available_positions();
        do
        {
            std::cout << "Player " << int(player1) << ", enter the column in which you want to place you stone: " << std::endl;
            std::cin >> col;
            col_n = stoi(col);
        } while (free_positions.find(col_n) == free_positions.end());
        
        
        state = player1 ? States::CIRCLE : States::CROSS;
        row_n = game.place_stone(col_n, state);

        game.show_board();
        if (game.is_solved(row_n, col_n, state)) {
            std::cout << "Player " << int(player1) << " won!" << std::endl;
            return 0;
        }

        player1 ^= true;
    }
    
    return 0;
}