/**********************************
 * Name: Daniel Shields
 * Email: dshield2@nd.edu
 * File Name: game.h
 * Date Created: 2/22/2022
 * File Contents: This file contains the function declarations and global variables for PC04
 **********************************/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>

#define VECTOR std::vector
#define COUT std::cout
#define CIN std::cin
#define ENDL std::endl
#define HEIGHT 4
#define WIDTH 4
#define SIZE_T long unsigned int

// Function declarations will go here


 void initialize_board( VECTOR< VECTOR<int> >& game_board);
 void print_board( const VECTOR< VECTOR<int> >& game_board, const int score);
 bool check_board(const VECTOR< VECTOR<int> >& game_board);
 void generate_new_initial( VECTOR< VECTOR<int> >& game_board);
 char get_move_choice();
 void move_left( VECTOR< VECTOR<int> >& game_board, int& score );
 void move_down( VECTOR< VECTOR<int> >& game_board, int& score );
 void move_right(VECTOR< VECTOR<int> >& game_board, int& score);
 void move_up(VECTOR< VECTOR<int> >& game_board, int& score);

#endif