#include "console_display.h"


void display_board(int arg, bool char_board, User player, Computer computer)
{    
    std::array<int, BOARD_SIZE * BOARD_SIZE> temporary_board;
    temporary_board = (arg == 0) ? player.ships_board : computer.ships_board;

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(arg == 1) {
                if(char_board) {
                    if(computer.ships_board[i * BOARD_SIZE + j] == DAMAGED_BATTLESHIP_PART) {
                        std::cout << "\033[31m1\033[0m";
                    } else if(computer.ships_board[i * BOARD_SIZE + j] == DAMAGED_CRUISER_PART) {
                        std::cout << "\033[31m2\033[0m";
                    } else if(computer.ships_board[i * BOARD_SIZE + j] == DAMAGED_DESTROYER_PART) {
                        std::cout << "\033[31m3\033[0m";
                    } else if(computer.ships_board[i * BOARD_SIZE + j] == MISSED_SHOT_ON_BOARD) {
                        std::cout << "\033[31m.\033[0m";
                    } else {
                        std::cout << '.';
                    }
                } else {
                    std::cout << computer.ships_board[i * BOARD_SIZE + j];
                }
            } else {
                if(char_board) {
                    if(player.ships_board[i * BOARD_SIZE + j] == DAMAGED_BATTLESHIP_PART) {
                        std::cout << "\033[31m1\033[0m";
                    } else if(player.ships_board[i * BOARD_SIZE + j] == DAMAGED_CRUISER_PART) {
                        std::cout << "\033[31m2\033[0m";
                    } else if(player.ships_board[i * BOARD_SIZE + j] == DAMAGED_DESTROYER_PART) {
                        std::cout << "\033[31m3\033[0m";
                    } else if(player.ships_board[i * BOARD_SIZE + j] == EMPTY_BOARD_SPACE) {
                        std::cout << '.';
                    } else if(player.ships_board[i * BOARD_SIZE + j] == MISSED_SHOT_ON_BOARD) {
                        std::cout << "\033[31m.\033[0m";
                    } else {
                        std::cout << player.ships_board[i * BOARD_SIZE + j];
                    }                    
                } 
                
            }

            if(j != BOARD_SIZE - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void display_inf(std::string type_of_information, PlayerBlueprint::Ship user_ship)
{
    std::string ship_name = form_current_ship_name_string(user_ship);
    if(type_of_information == "inf") {
        std::cout << "Iveskite " << ship_name << std::endl;
    } else if(type_of_information == "err") {
        std::cout << ship_name << " buvo pastatytas neteisingai, bandykite darkart..." << std::endl;
    }

}

void clear_and_sleep()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void display_main_header()
{
    std::cout << "                   LAIVU MUSIS" << std::endl;
    std::cout << "   Tikslas: nuskadinti visus 3 oponento laivus" << std::endl;
    std::cout << "               Imanomi penki laivai:" << std::endl;
    std::cout << "   1. Battleship - simbolis " << u8"\xF0\x9F\x98\x83" << ", uzima 4 skylutes" << std::endl;
    std::cout << "   2. Cruiser - simbolis    " << u8"\xF0\x9F\x98\x84" << ", uzima 3 skylutes" << std::endl;
    std::cout << "   3. Destroyer - simbolis  " << u8"\xF0\x9F\x98\x86" << ", uzima 2 skylutes" << std::endl;

    std::cout << "Duomenis iveskite sekancia forma: " << "horizontaliai / vertikaliai, eilute/stulpelis, x koordinate ir y koordinate\n";
    std::cout << "Pavyzdys: h 1 1 3\n\n";
}
 
void display_end_header(bool player_won, bool opponent_won)
{
    if(player_won) {
        std::cout << "SVEIKINAME. Jus sekmingai sunaikinote prieso laivyna!" << std::endl;
    } else if(opponent_won) {
        std::cout << "DEJA, oponentas sunaikino jusu laivyna, sekmes kitakart..." << std::endl;
    }
    
    std::cout << "Zaidimo pabaiga, iseinama is programos..." << std::endl;
}

void display_char_boards(User player, Computer computer)
{
    std::cout << "YOUR BOARD" << std::endl;
    display_board(0, true, player, computer);
    
    std::cout << std::endl << "OPPONENT BOARD" << std::endl;
    display_board(1, true, player, computer);

    std::cout << std::endl;
}

void display_one_iteration_info(int user_shot_index, bool user_hit_opponent, int opponent_shot_index, bool opponent_hit_user)
{
    std::cerr << "User shot at <" << user_shot_index << ">. Was it a hit? " << user_hit_opponent << std::endl;
    std::cerr << "Computer shot at <" << opponent_shot_index << ">. Was it a hit? " << opponent_hit_user << std::endl;

    clear_and_sleep();
}

void get_player_shooting_input(int &row, int &col)
{
    bool input_is_complete = false;    
    std::cout << "Iveskite eilute ir stulpeli i kuri norite sauti, pvz. 2 3 (2 eilute 3 stulpelis)" << std::endl;
    
    while(!input_is_complete) {
        if(std::cin >> row >> col) {
            if(row <= BOARD_SIZE && col <= BOARD_SIZE && row > EMPTY_BOARD_SPACE && col > EMPTY_BOARD_SPACE) {
                return;
            } else {
                std::cout << "Iveskite teisinga eilute ir stulpeli!" << std::endl;
                clear_and_sleep();
            }
        } 
    }

}

UserInput receive_player_input()
{
    UserInput input;

    while (true) {
        std::cout << "> ";

        if (std::cin >> input.azimuth >> input.lane_ind >> input.start_point >> input.end_point) {
            if (input.azimuth == 'v' || input.azimuth == 'h') {
                std::system("clear");
                return input;
            }
        }

        std::cout << "Neteisingas ivedimas! Bandykite is naujo...\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

std::string form_current_ship_name_string(PlayerBlueprint::Ship user_ship)
{
    std::string ship_name = "";
    switch(user_ship) {
        case PlayerBlueprint::BATTLESHIP:
            ship_name = "Battleship";
            break;
        case PlayerBlueprint::CRUISER:
            ship_name = "Cruiser";
            break;
        case PlayerBlueprint::DESTROYER:
            ship_name = "Destroyer";
            break;
        default:
            ship_name = "UknownType";
            break;
    } 
    
    return ship_name;
}

