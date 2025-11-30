#include "player_blueprint.h"


void PlayerBlueprint::markNewlyHitShip()
{

}

void PlayerBlueprint::absorbShotAt(int shot_index, bool &hit_something)
{
    hit_something = true;
    int spot_shot_at = PlayerBlueprint::ships_board[shot_index];
    
    switch(spot_shot_at) {
        case EMPTY_BOARD_SPACE:
            PlayerBlueprint::ships_board[shot_index] = MISSED_SHOT_ON_BOARD;
            hit_something = false;
            break;
        case BATTLESHIP_PART:
            PlayerBlueprint::ships_board[shot_index] = DAMAGED_BATTLESHIP_PART;
            break;
        case CRUISER_PART:
            PlayerBlueprint::ships_board[shot_index] = DAMAGED_CRUISER_PART;
            break;
        case DESTROYER_PART:
            PlayerBlueprint::ships_board[shot_index] = DAMAGED_DESTROYER_PART;
            break;
    }   
}

bool PlayerBlueprint::stillHaveShipsLeft()
{
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(PlayerBlueprint::ships_board[i * BOARD_SIZE + j] == BATTLESHIP_PART ||
                PlayerBlueprint::ships_board[i * BOARD_SIZE + j] == CRUISER_PART ||
                PlayerBlueprint::ships_board[i * BOARD_SIZE + j] == DESTROYER_PART) {
                    return true;
                }
        }
    }

    return false;
}