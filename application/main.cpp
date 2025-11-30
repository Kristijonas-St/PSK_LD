#include "main.h"

int main()
{
    int game_end_status = 0;
    
    display_main_header();
    game_end_status = run_main_game();
    if(game_end_status) {
        return 0;
    }
    
}
