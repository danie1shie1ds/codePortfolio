/**********************************
 * Name: Daniel Shields
 * Email: dshield2@nd.edu
 * File Name: game.cpp
 * Date Created: 2/22/2022
 * File Contents: This file contains the function definitions for PC04
 **********************************/

#include "../include/game.h"

void initialize_board( VECTOR<VECTOR<int>>& board){
   SIZE_T randLoc = rand() % 16;
   SIZE_T firsti = randLoc / HEIGHT;
   SIZE_T firstj = randLoc % HEIGHT;
   board[firsti][firstj] = 2;
   COUT << "Initial Location: (" << firsti << ", " << firstj << ")" << ENDL;
}

void print_board( const VECTOR< VECTOR<int> >& board, const int score){
   COUT << "Score: " << score << ENDL;
   SIZE_T i, j, dash;
   for(i = 0; i < board.size(); i++){
      for(dash = 0; dash < 1 + 5*board.size(); dash++){
         COUT << "-";
      }
      COUT << ENDL;
      for(j = 0; j < WIDTH; j++){
         COUT << '|';
         if(board[i][j] == 0) COUT << "    ";
         else COUT << std::setfill(' ') << std::setw(4) << board[i][j];
      }
      COUT << '|' << ENDL;
   }
   for(dash = 0; dash < 1 + 5*board.size(); dash++){
         COUT << "-";
   }
   COUT << ENDL;
}

bool check_board(const VECTOR< VECTOR<int> >& board){
   SIZE_T i, j;
   bool keepgoing = false;
   for(i = 0; i < board.size(); i++){
      for(j = 0; j < WIDTH; j++){
         if(board[i][j] == 0) keepgoing = true;
         if(board[i][j] >= 2048){
            keepgoing = false;
            return keepgoing;
         }
      }
   }
   return keepgoing;
}

void generate_new_initial( VECTOR< VECTOR<int> >& board){
   SIZE_T randLoc = rand() % 16;
   SIZE_T newi = randLoc / HEIGHT;
   SIZE_T newj = randLoc % HEIGHT;
   while(board[newi][newj] != 0){
      randLoc = rand() % 16;
      newi = randLoc / HEIGHT;
      newj = randLoc % HEIGHT;
   }
   board[newi][newj] = 2;
   COUT << "New 2 placed at: (" << newi << ", " << newj << ")" << ENDL;
   print_board(board, 0);
}

char get_move_choice(){
   char userChoice = 'x';
   COUT << "Move left, right, up, or down:" << ENDL;
   COUT << "Enter(l, r, u, d)" << ENDL;
   CIN >> userChoice;
   return userChoice;
}

void move_left( VECTOR< VECTOR<int> >& board, int& score ){
   SIZE_T i;
   SIZE_T j, k;
   
   for(i = 0; i < board.size(); i++){
      //Shift all values to the left if a zero is to the left of it
      for(j = WIDTH - 1; j > 0; j--){
         if(board[i][j-1] == 0){
            board[i][j-1] = board[i][j];
            board[i][j] = 0;
            for(k = j; k < WIDTH - 1; k++){
               if(board[i][k] == 0){
                  board[i][k] = board[i][k+1];
                  board[i][k+1] = 0;
               }
            }
         }
      }


      // Check to see if adjacent values are equal and increase score
      for(j = 0; j < WIDTH - 1; j++){
         if(board[i][j] != 0 && board[i][j+1] == board[i][j]){
            board[i][j] *= 2;
            score += board[i][j];
            board[i][j+1] = 0;
            
            // Backtrack to move elements after addition
            for(k = j + 1; k < WIDTH - 1; k++){
               
               if(board[i][k] == 0){
                  board[i][k] = board[i][k+1];
                  board[i][k+1] = 0;
               }
            }
         }
      }
   }
}

 void move_down( VECTOR< VECTOR<int> >& board, int& score ){
   SIZE_T i, j, k;
   for(j = 0; j < board.size(); j++){
      //Shift all values to the left if a zero is to the left of it
      for(i = 0; i < HEIGHT - 1; i++){
         if(board[i+1][j] == 0){
            board[i+1][j] = board[i][j];
            board[i][j] = 0;
            for(k = i; k > 0; k--){
               if(board[k][j] == 0){
                  board[k][j] = board[k-1][j];
                  board[k-1][j] = 0;
               }
            }
         }
      }


      // Check to see if value above is equal and increase score
      for(i = HEIGHT - 1; i > 0; i--){
         if(board[i][j] != 0 && board[i-1][j] == board[i][j]){
            board[i][j] *= 2;
            score += board[i][j];
            board[i-1][j] = 0;
            
            // Backtrack to move elements after addition
            for(k = i - 1; k > 0; k--){
               
               if(board[k][j] == 0){
                  board[k][j] = board[k-1][j];
                  board[k-1][j] = 0;
               }
            }
         }
      }
   }
 }

 void move_right(VECTOR< VECTOR<int> >& board, int& score){
   SIZE_T i, j, k;
   for(i = 0; i < HEIGHT; i++){
      //Shift all values to the left if a zero is to the left of it
      for(j = 0; j < WIDTH - 1; j++){
         if(board[i][j+1] == 0){
            board[i][j+1] = board[i][j];
            board[i][j] = 0;
            for(k = j; k > 0; k--){
               if(board[i][k] == 0){
                  board[i][k] = board[i][k-1];
                  board[i][k-1] = 0;
               }
            }
         }
      }


      // Check to see if value above is equal and increase score
      for(j = WIDTH - 1; j > 0; j--){
         if(board[i][j] != 0 && board[i][j-1] == board[i][j]){
            board[i][j] *= 2;
            score += board[i][j];
            board[i][j-1] = 0;
            
            // Backtrack to move elements after addition
            for(k = j - 1; k > 0; k--){
               
               if(board[i][k] == 0){
                  board[i][k] = board[i][k-1];
                  board[i][k-1] = 0;
               }
            }
         }
      }
   }
 }

 void move_up(VECTOR< VECTOR<int> >& board, int& score){
   SIZE_T i;
   SIZE_T j, k;
   
   for(j = 0; j < board.size(); j++){
      //Shift all values to the left if a zero is to the left of it
      for(i = HEIGHT - 1; i > 0; i--){
         if(board[i-1][j] == 0){
            board[i-1][j] = board[i][j];
            board[i][j] = 0;
            for(k = i; k < HEIGHT - 1; k++){
               if(board[k][j] == 0){
                  board[k][j] = board[k+1][j];
                  board[k+1][j] = 0;
               }
            }
         }
      }


      // Check to see if adjacent values are equal and increase score
      for(i = 0; i < HEIGHT - 1; i++){
         if(board[i][j] != 0 && board[i+1][j] == board[i][j]){
            board[i][j] *= 2;
            score += board[i][j];
            board[i+1][j] = 0;            
            // Backtrack to move elements after addition
            for(k = i + 1; k < HEIGHT - 1; k++){
               
               if(board[k][j] == 0){
                  board[k][j] = board[k+1][j];
                  board[k+1][j] = 0;
               }
            }
         }
      }
   }
 }