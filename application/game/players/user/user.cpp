#include "user.h"

int User::convertShootingInput(int row, int col)
{
    // Decrement input values to mach array indicing
    row--;
    col--;
    
    int converted_input = row * BOARD_SIZE + col;
    return converted_input;
}

int User::askUserToPlaceShipsAt()
{
    int rc = 0 ;
    bool certain_ship_is_placed = false;
    UserInput input;
    Ship ship;
    
    bool selected_ship_was_placed = false;
    static const Ship SHIPS_IN_ORDER[NUM_OF_SHIPS] = {
        BATTLESHIP,
        CRUISER,
        DESTROYER
    };

    for(int i = 0; i < NUM_OF_SHIPS; i++) {
        certain_ship_is_placed = false;

        while(!certain_ship_is_placed) {            
            ship = SHIPS_IN_ORDER[i];
            
            display_inf("inf", ship);
            input = receive_player_input();
            convertUserInputToBoardCoords(ship, input.azimuth, input.lane_ind,
                                            input.start_point, input.end_point);
            
            rc = placeEnteredShip(ship, input.azimuth, input.lane_ind,
                                    input.start_point, input.end_point);
            if(rc) {
                display_inf("err", ship);
                clear_and_sleep();
            } else {
                certain_ship_is_placed = true;
            }
        }
    }

    std::cout << "cruiser " << input.start_point << " " << input.end_point << std::endl;
    return 0;
}

int User::placeEnteredShip(Ship playerEnteredShip, char azimuth, int lane_ind, int start_point, int end_point)
{
    if(enteredCorrectShipLength(playerEnteredShip, azimuth, lane_ind, start_point, end_point) &&
        shipIsInBoardScope(playerEnteredShip, azimuth, lane_ind, start_point, end_point) &&
        shipsDontCross(playerEnteredShip, azimuth, lane_ind, start_point, end_point)) {
        
        repaintBoardAccordingToShip(playerEnteredShip, azimuth, lane_ind, start_point, end_point);

        return 0;
    }

    return 1;
}

void User::convertUserInputToBoardCoords(Ship playerEnteredShip, char azimuth, int lane_ind, int &start_point, int &end_point)
{
    const int depth = 5;
    int extend_vertical_length = 0;
    
    // Decrement coordinate values to fit array indicing
    start_point--;
    end_point--;
    lane_ind--;

    if(azimuth == 'h') {
        start_point = lane_ind * depth + start_point;
        end_point = lane_ind * depth + end_point;
    } else if(azimuth == 'v') {
        int temporary_lenght = end_point - start_point;
        start_point = lane_ind * depth + start_point;
        
        switch(playerEnteredShip) {
            case BATTLESHIP:
                extend_vertical_length = 10;
                break;
            case CRUISER:
                extend_vertical_length = 5;
                break;
            case DESTROYER:
                start_point = end_point = lane_ind * depth + start_point;
                return;
        }

        end_point = start_point + extend_vertical_length;
    }

}

bool User::enteredCorrectShipLength(Ship playerEnteredShip, char azimuth, int lane_ind, int start_point, int end_point)
{
    int horizontal_ship_length = 0;
    int vertical_ship_length = 0;
    
    switch(playerEnteredShip) {
        case BATTLESHIP:
            horizontal_ship_length = BATTLESHIP_HORIZONTAL_LENGTH;
            vertical_ship_length = BATTLESHIP_VERTICAL_LENGTH;
            break;
        case CRUISER:
            horizontal_ship_length = CRUISER_HORIZONTAL_LENGTH;
            vertical_ship_length = CRUISER_VERTICAL_LENGTH;
            break;
        case DESTROYER:
        // Checking if end points matches start point
        // since destroyer length is 1    
        if(end_point == start_point) {
                return true;
            } else {
                return false;
            }    
    }

    if(azimuth == 'h') {
        if(abs(end_point - start_point) == horizontal_ship_length) {
            return true;
        }
    } else if(azimuth == 'v') {
        if(abs(end_point - start_point) == vertical_ship_length) {
            return true;
        }
    }

std::cerr << "Wrong length" << std::endl;
    return false;
}

bool User::shipIsInBoardScope(Ship playerEnteredShip, char azimuth, int lane_ind, int start_point, int end_point)
{
    int h_invalid_pos_begin = 0;
    int h_invalid_pos_end = 0;
    int h_invalid_leap = 0;

    int v_invalid_pos_begin = 0;
    int v_leap = 0;

    switch(playerEnteredShip) {
        case BATTLESHIP:
            h_invalid_pos_begin = battleship_h_invalid_pos_begin;
            h_invalid_pos_end = battleship_h_invalid_pos_end;
            h_invalid_leap = battleship_h_invalid_leap;

            v_invalid_pos_begin = battleship_v_invalid_pos_begin;
            v_leap = v_invalid_leap;
            break;

        case CRUISER:
            h_invalid_pos_begin = cruiser_h_invalid_pos_begin;
            h_invalid_pos_end = cruiser_h_invalid_pos_end;
            h_invalid_leap = cruiser_h_invalid_leap;
            
            v_invalid_pos_begin = cruiser_v_invalid_pos_begin;
            v_leap = v_invalid_leap;
            break;

        case DESTROYER:
            h_invalid_pos_begin = destroyer_h_invalid_pos_begin;
            h_invalid_pos_end = destroyer_h_invalid_pos_end;
            h_invalid_leap = destroyer_h_invalid_leap;
            
            v_invalid_pos_begin = cruiser_v_invalid_pos_begin;
            v_leap = v_invalid_leap;
            break;
    }

    // Iterate through the whole board to check if ship is going out of scope
    for(int i = 0; i < BOARD_SIZE; i++) {
        if(azimuth == 'h') {
            if(start_point == h_invalid_pos_begin && start_point == h_invalid_pos_end) {
                return false;
            }
            h_invalid_pos_begin += h_invalid_leap;
            h_invalid_pos_end += h_invalid_leap;
        } else if(azimuth == 'v') {
            if(start_point == v_invalid_pos_begin) {
                return false;
            }
            v_invalid_pos_begin += v_invalid_leap;
        }
    }

    return true;
}

bool User::shipsDontCross(Ship playerEnteredShip, char azimuth, int lane_ind, int start_point, int end_point)
{
    // const int horizontal_leap = 1;
    // const int vertical_leap = 5;

    int leap = (azimuth == 'h') ? horizontal_leap : vertical_leap;
    for(int board_pos = start_point; board_pos < end_point; board_pos += leap) {
        if(ships_board[board_pos] != 0) {
            return false;
        }
    }

    return true;
}

void User::repaintBoardAccordingToShip(Ship playerEnteredShip, char azimuth, int lane_ind, int start_point, int end_point)
{
    int leap = (azimuth == 'h') ? horizontal_leap : vertical_leap;
    int ship_value_on_board = 0;

    switch(playerEnteredShip) {
        case BATTLESHIP:
            ship_value_on_board = BATTLESHIP_PART;
            break;
        case CRUISER:
            ship_value_on_board = CRUISER_PART;
            break;
        case DESTROYER:
            ships_board[start_point] = DESTROYER_PART;
            return;
    }

    for(int i = start_point; i < end_point; i += horizontal_leap) {
        ships_board[i] = ship_value_on_board;
    }
    
}