#pragma once
#include <set>
#include "../player_blueprint.h"
#include "../ui/console_display.h"

class User : public PlayerBlueprint
{
public:
    int askUserToPlaceShipsAt();
    int placeEnteredShip(Ship enteredShip, char azimuth, int lane_ind, int start_point, int end_point);
    int convertShootingInput(int row, int col);

private:
    // VALUES for determining correct ship placement HORIZONTALLY
    const int battleship_h_invalid_pos_begin = 3;
    const int battleship_h_invalid_pos_end = 5;
    const int battleship_h_invalid_leap = 5;

    const int cruiser_h_invalid_pos_begin = 4;
    const int cruiser_h_invalid_pos_end = 5;
    const int cruiser_h_invalid_leap = 5;

    /*Scrap values, since len(destoryer) == 1 */
    const int destroyer_h_invalid_pos_begin = 25;
    const int destroyer_h_invalid_pos_end = 25;
    const int destroyer_h_invalid_leap = 25;

    // VALUES for determining correct ship placement VERTICALLY
    const int battleship_v_invalid_pos_begin = 15;
    const int cruiser_v_invalid_pos_begin = 20;
    /*Scrap values, since len(destoryer) == 1 */
    const int destroyer_v_invalid_pos_begin = 25;

    const int v_invalid_leap = 1;

    const int horizontal_leap = 1;
    const int vertical_leap = 5;

    void convertUserInputToBoardCoords(Ship playerEnteredShip, char azimuth, int lane_ind, int &start_point, int &end_point);
    bool enteredCorrectShipLength(Ship enteredShip, char azimuth, int lane_ind, int start_point, int end_point);
    bool shipIsInBoardScope(Ship enteredShip, char azimuth, int lane_ind, int start_point, int end_point);
    bool shipsDontCross(Ship playerEnteredShip, char azimuth, int lane_ind, int start_point, int end_point);
    void repaintBoardAccordingToShip(Ship playerEnteredShip, char azimuth, int lane_ind, int start_point, int end_point);

};