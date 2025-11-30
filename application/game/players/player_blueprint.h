#pragma once
#include <set>
#include <array>

#define NUM_OF_SHIPS    3
#define BOARD_SIZE      5

#define BATTLESHIP_PART 1
#define CRUISER_PART    2
#define DESTROYER_PART  3

#define BATTLESHIP_HORIZONTAL_LENGTH    3
#define CRUISER_HORIZONTAL_LENGTH       2
#define DESTROYER_HORIZONTAL_LENGTH     1

#define BATTLESHIP_VERTICAL_LENGTH      10
#define CRUISER_VERTICAL_LENGTH         5
#define DESTROYER_VERTICAL_LENGTH       1

#define EMPTY_BOARD_SPACE               0
#define DAMAGED_BATTLESHIP_PART         11
#define DAMAGED_CRUISER_PART            22
#define DAMAGED_DESTROYER_PART          33
#define MISSED_SHOT_ON_BOARD            -1

class PlayerBlueprint {
protected:
    int remaining_boats = NUM_OF_SHIPS;    
    std::set<int> marked_places;

public:
    std::array<int, BOARD_SIZE * BOARD_SIZE> ships_board = {0};
    typedef enum Ship {
        BATTLESHIP = 1,
        CRUISER,
        DESTROYER
    } Ship;

    void markNewlyHitShip();
    void absorbShotAt(int shot_index, bool &hit_something);
    bool stillHaveShipsLeft();

};