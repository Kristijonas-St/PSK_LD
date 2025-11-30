#include "main_game.h"

int run_main_game()
{
    // Initialize both players
    User player;
    Computer opponent;

    // Allow user to place his ships
    player.askUserToPlaceShipsAt();
    
    // Initialize row and collumn for user shoot position
    int row = 0;
    int col = 0;
    int user_shot_index = 0;
    int opponent_shot_index = 0;
    bool game_needs_to_proceed = true;
    bool user_hit_opponent = false;
    bool opponent_hit_user = false;

    // Start main game's loop and allow shooting one another
    while(game_needs_to_proceed) {
        display_char_boards(player, opponent);
        
        // Handle User shooting
        get_player_shooting_input(row, col);
        user_shot_index = player.convertShootingInput(row, col);
        opponent.absorbShotAt(user_shot_index, user_hit_opponent);

        // Handle Computer shooting
        opponent_shot_index = opponent.shootUserAt();
        player.absorbShotAt(opponent_shot_index, opponent_hit_user);

        display_one_iteration_info(user_shot_index, user_hit_opponent, opponent_shot_index, opponent_hit_user);

        game_needs_to_proceed = player.stillHaveShipsLeft() && opponent.stillHaveShipsLeft();

    }

    bool player_won = (player.stillHaveShipsLeft() && !opponent.stillHaveShipsLeft());
    bool opponent_won = (!player.stillHaveShipsLeft() && opponent.stillHaveShipsLeft());

    // Print last time to see the board
    display_char_boards(player, opponent);
    display_end_header(player_won, opponent_won);

    return 0;
}