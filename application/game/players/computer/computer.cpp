#include <iostream>
#include <cstdlib>
#include <ctime>
#include "computer.h"

void Computer::initializeFixedBoatsPlacement()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // randomise fixed preset of computers ships layout
    int fixed_position_set = rand() % 2 + 1; 

    // indices are fixed to behave as a preset ships layout set
    switch(fixed_position_set) {
        case 1:
            for(int i = 0; i < 3; i++) {
                ships_board[i] = BATTLESHIP_PART;
            }
            for(int i = 15; i < 17; i++) {
                ships_board[i] = CRUISER_PART;
            }
            ships_board[14] = DESTROYER_PART;

            break;
        case 2:
            for(int i = 6; i < 9; i++) {
                ships_board[i] = BATTLESHIP_PART;
            }
            for(int i = 20; i < 22; i++) {
                ships_board[i] = CRUISER_PART;
            }
            ships_board[19] = DESTROYER_PART;

            break;
        default:
            break;
    }
}

int Computer::shootUserAt()
{
    // Simulate computer shooting by randomising the shot
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
     
    while(true) {
        int shot_index = rand() % (BOARD_SIZE * BOARD_SIZE) + 1;
        if(marked_places.count(shot_index)) {
            // shot at this index was made, try again
        } else {
            return shot_index;
        }
    }

    
}