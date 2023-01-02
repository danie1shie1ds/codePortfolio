/**********************************
 * Name: Daniel Shields
 * Email: dshield2@nd.edu
 * File Name: PC04.cpp
 * Date Created: 2/22/2022
 * File Contents: This file contains the main function for PC04 it runs a version of the 2048 game
 **********************************/

#include "../include/game.h"
 
  
int main(){
    srand((unsigned int)time(0));
    char dir;
    bool keepgoing;
    char cont;
    int score = 0;
    VECTOR<VECTOR<int> > game_board(4, VECTOR<int>(4, 0));
    initialize_board(game_board);
    while(true){
        print_board(game_board, score);
        generate_new_initial(game_board);
        dir = get_move_choice();
        switch (dir){
            case 'l':
                move_left(game_board, score);
                print_board(game_board, score);
                break;
            case 'r':
                move_right(game_board, score);
                print_board(game_board, score);
                break;
            case 'd':
                move_down(game_board, score);
                print_board(game_board, score);
                break;
            case 'u':
                move_up(game_board, score);
                print_board(game_board, score);
                break;
        }
        // Check game conditions
        keepgoing = check_board(game_board);
        if(keepgoing == false){
            COUT << "GAME OVER" << ENDL << "Score: " << score << ENDL;
            break;
        }
        COUT << "Do you want to continue? (y/n): ";
        CIN >> cont;
        if(cont == 'n'){
            COUT << "Thanks for playing" << ENDL;
            break;
        }
    }
    return 0;
}