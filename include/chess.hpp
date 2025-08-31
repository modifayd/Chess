#pragma once

#include <iostream>
#include<string.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h> // POSIX only
#include <math.h>
#include <unordered_map>
#include <cctype>    // for tolower
#include <algorithm> // for transform

using namespace std;

#define BOARD_SIZE  8



class chess_pieces{

    public:
    
    // map pieces in num to string correspondings
    unordered_map<int,string> num_to_piece; 

    // Assign each piece with numbers + for white - for black
    int Pawn_w = 1;
    int Bishop_w = 2;
    int Knight_w = 3;
    int Rook_w = 4;
    int Queen_w = 5;
    int King_w = 6;        


    int Pawn_b = -1;
    int Bishop_b = -2;
    int Knight_b = -3;
    int Rook_b = -4;
    int Queen_b = -5;
    int King_b = -6;

    // constructor
    chess_pieces();

};



class chess_board{

    private:
        // main board
        int board[BOARD_SIZE][BOARD_SIZE];

        // castling move check
        bool is_rook_left_w_moved = false;
        bool is_rook_right_w_moved = false;
        bool is_king_w_moved = false;

        bool is_rook_left_b_moved = false;
        bool is_rook_right_b_moved = false;
        bool is_king_b_moved = false;

        // define pieces
        chess_pieces pieces;

        // map from num to pieces
        unordered_map<int,string> num_to_piece = pieces.num_to_piece;


    protected:

        // convert movement given in string(e3 d2 ...) to num(correponding array indexes of of board)
        vector<int> convert_ChessToVec(string m);

        // initialize board
        void init_position();

        // castling condition check
        bool check_castling( vector<int> m_old, vector<int> m_new, int turn);

        // check movement legality
        bool check_move( vector<int> m_old, vector<int> m_new, int turn);

        // pawn reach end 
        void change_pawn(int piece, int turn, vector<int> m_new);

        // check path legality of movement
        bool check_path(vector<int> m_old, vector<int> m_new, int piece);

        // is movement creates "check" condition
        bool is_check(int turn);

        // cehck-mate
        bool is_checkmate(int turn );


    public:
     
        // Constructor
        chess_board();

        // print board
        void print();

        // move pieces
        bool move(string movement_old, string movement_new, int& turn , int& termination);

        


};







