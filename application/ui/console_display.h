#pragma once
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>
#include "../../application/main.h"
// #include "../game/players/computer/computer.h"
// #include "../game/players/user/user.h"
#include "../game/players/player_blueprint.h"

class User;
class Computer;

typedef struct {
    char azimuth;
    int lane_ind;
    int start_point;
    int end_point;
} UserInput;

void clear_and_sleep();
void display_board(int arg, bool char_board, User player, Computer computer);
void display_inf(std::string type_of_information, PlayerBlueprint::Ship user_ship);
void display_main_header();
void display_end_header(bool player_won, bool opponent_won);
void display_char_boards(User player, Computer computer);
void display_one_iteration_info(int user_shot_index, bool user_hit_opponent, int opponent_shot_index, bool opponent_hit_user);

void get_player_shooting_input(int &row, int &col);


std::string form_current_ship_name_string(PlayerBlueprint::Ship user_ship);
UserInput receive_player_input();
