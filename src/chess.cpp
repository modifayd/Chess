#include "chess.hpp"


chess_pieces :: chess_pieces(){    

    // White pieces
    num_to_piece[Pawn_w] = "White Pawn";
    num_to_piece[Bishop_w] = "White Bishop";
    num_to_piece[Knight_w] = "White Knight";
    num_to_piece[Rook_w] = "White Rook";
    num_to_piece[Queen_w] = "White Queen";
    num_to_piece[King_w] = "White King";

    // Black pieces
    num_to_piece[Pawn_b] = "Black Pawn";
    num_to_piece[Bishop_b] = "Black Bishop";
    num_to_piece[Knight_b] = "Black Knight";
    num_to_piece[Rook_b] = "Black Rook";
    num_to_piece[Queen_b] = "Black Queen";
    num_to_piece[King_b] = "Black King";


}    


vector<int>  chess_board ::convert_ChessToVec(string m){
    vector<int> res;
    res.push_back(8-((int)m[1]-48));// ASCII Table--> numbers start from 48  check->  https://www.ascii-code.com/
    res.push_back((int)m[0]-97);// ASCII Table--> lowercase letters start from 97  check->  https://www.ascii-code.com/
return res;    
}



void chess_board ::  init_position(){

    // empty board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }

    // pawns
    for (int j = 0; j < BOARD_SIZE; j++) {
        board[1][j] = pieces.Pawn_b; // black pawns
        board[6][j] = pieces.Pawn_w; // white pawns
    }

    // rooks
    board[0][0] = board[0][7] = pieces.Rook_b;
    board[7][0] = board[7][7] = pieces.Rook_w;

    // knights
    board[0][1] = board[0][6] = pieces.Knight_b;
    board[7][1] = board[7][6] = pieces.Knight_w;

    // bishops
    board[0][2] = board[0][5] = pieces.Bishop_b;
    board[7][2] = board[7][5] = pieces.Bishop_w;

    // queens
    board[0][3] = pieces.Queen_b;
    board[7][3] = pieces.Queen_w;

    // kings
    board[0][4] = pieces.King_b;
    board[7][4] = pieces.King_w;

            
    }


    chess_board :: chess_board(){
        init_position();
   }


   void chess_board :: print(){

    for(int i = 0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){

            if(i<2){
                if(j == 0){              
                    cout<<BOARD_SIZE-i<<"|"<<board[i][j]<<"   ";
                }
                else
                cout<<" "<<board[i][j]<<"   ";}
            else{  
                if(j == 0){              
                cout<<BOARD_SIZE-i<<"| "<<board[i][j]<<"   ";
                 }
                 else
                 cout<<"  "<<board[i][j]<<"   ";

                }

        }
        cout<<endl;
        cout<<endl;

    }
    //cout<<"   \u2500     b     c     d     e     f     g     h"<<endl;;
    cout<<"   a     b     c     d     e     f     g     h"<<endl;;

}



bool chess_board :: move(string movement_old, string movement_new, int& turn , int& termination){

    vector<int> m_old = convert_ChessToVec(movement_old);
    vector<int> m_new = convert_ChessToVec(movement_new);

    int piece = board[m_old[0]][m_old[1]];
    
    // check movement colour correctness
    if((turn == 0 && piece<0) || (turn == 1 && piece>0)){
        
        // check castling
        if(check_castling(m_old,m_new,turn)){return true;}

        // check movement legality
        else if(check_move(m_old,m_new,turn)){
        
            if(board[m_new[0]][m_new[1]] != 0)
                {cout<<num_to_piece[board[m_new[0]][m_new[1]]]<<" has fallen "<<endl;}

            int old_p = board[m_old[0]][m_old[1]];
            int new_p = board[m_new[0]][m_new[1]];

            board[m_old[0]][m_old[1]] = 0;
            board[m_new[0]][m_new[1]] = piece;
            
            if(is_check(turn)) {
                cout << "Illegal move! You cannot leave your king in check." << endl;
                board[m_old[0]][m_old[1]] = old_p; 
                board[m_new[0]][m_new[1]] = new_p; 
                return false;
            }

            // check if pawn reaches end
            if(abs(piece) == 1 && (m_new[0] == 0 || m_new[0] == 7)) change_pawn(piece,turn,m_new);      
            
            // check "check" condition 
            if(is_check(1-turn) ) {
                cout << (1-turn ? "White" : "Black")<<"king is in check!" << endl;  
                if(is_checkmate(0)) {termination = 1;cout<<"Game is over"<<endl; return false;}
           
                }
        
            return true;
        }
        else{
            cout<<"!!!!!!! Illegal movement !!!!!!!"<<endl;
            return false; // Play again
        }
        
    }


    else if(piece == 0){
        cout<<"!!!!!!!! No piece in location "<< movement_old << "!!!!!!!!"<<endl;
        return false; // Play again
    }

    
    else{
        cout<<"!!!!!!!! Please play with your pieces !!!!!!!!"<<endl;
        return false; // Play again

    }
}




bool chess_board :: check_castling( vector<int> m_old, vector<int> m_new, int turn){

    // castling 1 white left rook 
    if(turn  == 1 && m_old[1] == 0 && m_old[0] == 7 && m_new[1] == 3  && m_new[0] == 7 && is_rook_left_w_moved == false && is_king_w_moved == false){
        if(board[7][1] == 0 && board[7][2] == 0 && board[7][3] == 0 ) // check path
        board[7][3] = 4;
        board[7][2] = 6;
        board[7][0] = 0; 
        board[7][4] = 0; 
        is_rook_left_w_moved = true;
        is_king_w_moved = true;
        return true;
    }


     // castling 2 black left rook 
    else if(turn  == 0 && m_old[1] == 0 && m_old[0] == 0 && m_new[1] == 3  && m_new[0] == 0 && is_rook_left_b_moved == false && is_king_b_moved == false){
        if(board[0][1] == 0 && board[0][2] == 0 && board[0][3] == 0 ) // check path
        board[0][3] = -4;
        board[0][2] = -6;
        board[0][0] = 0;
        board[0][4] = 0; 
        is_rook_left_b_moved = true;
        is_king_b_moved = true;
        return true;
    }    

    // castling 3 white right rook 
    else if(turn  == 1 && m_old[1] == 7 && m_old[0] == 7 && m_new[1] == 5  && m_new[0] == 7 && is_rook_right_w_moved == false && is_king_w_moved == false){
        if(board[7][5] == 0 && board[7][6] == 0  ) // check path
        board[7][5] = 4;
        board[7][6] = 6;
        board[7][7] = 0; 
        board[7][4] = 0; 
        is_rook_right_w_moved = true;
        is_king_w_moved = true;
        return true;
    }    

      // castling 4 black right rook 
      else if(turn  == 0 && m_old[1] == 7 && m_old[0] == 0 && m_new[1] == 5  && m_new[0] == 0 && is_rook_right_b_moved == false && is_king_b_moved == false){
        if(board[0][5] == 0 && board[0][6] == 0  ) // check path
        board[0][5] = -4;
        board[0][6] = -6;
        board[0][7] = 0; 
        board[0][4] = 0; 
        is_rook_right_b_moved = true;
        is_king_b_moved = true;
        return true;
    }    



return false;
}


bool chess_board :: check_move( vector<int> m_old, vector<int> m_new, int turn){

    // check movement is in board or not
    if(m_new[0] < 0 || m_new[0] > 7 || m_new[1] < 0 || m_new[1] > 7) return false;

    // If there is a piece exit in new place check colour
    if(board[m_new[0]][m_new[1]] != 0 ){
        if(board[m_new[0]][m_new[1]]*(turn-0.5)>0){
            return false;
        }
    }
    
    // coordiante difference dx dy
    int dx =  m_new[1]-m_old[1];
    int dy =  m_new[0]-m_old[0];

    // check each piece movement leglity--swith case
    int piece = abs(board[m_old[0]][m_old[1]]);
    switch(piece){
        
        case(1):// Pawn
                if((turn == 0 && dy <= 0) || (turn == 1 && dy>=0)) return false; // Pawn can only move forward

                else if((board[m_new[0]][m_new[1]] != 0 && abs(dx) == 1 && abs(dy) == 1)) return true; // Take piece 

                else if((board[m_new[0]][m_new[1]] == 0 && abs(dx) == 0 && abs(dy) == 1)) return true; // Move one forward

                else if (dx == 0 && ((turn==1 && m_old[0]==6 && dy==-2 && board[5][m_old[1]]==0) ||  // Forward move 2 from starting position
                    (turn==0 && m_old[0]==1 && dy==2 && board[2][m_old[1]]==0)) &&
                    board[m_new[0]][m_new[1]]==0) return true;

                else return false;

        case(2):// Bishop
                if( (abs(dx) == abs(dy)) && (abs(dx)>0) && (abs(dy)>0) && check_path(m_old, m_new,  piece)) return true; // check dioagnal movement
                else return false;

        case(3):// Knight
                if( ((abs(dx) == 1 && abs(dy) == 2) || (abs(dy) == 1 && abs(dx) == 2))) return true; // check 1x3y 1y3x movement -- L shape
                else return false;
                
        case(4):// Rook
                if(((abs(dx)!=0 && abs(dy) == 0) || (abs(dx)==0 && abs(dy) != 0) ) && check_path(m_old, m_new,  piece)){// check horizaontal/vertical movement

                     // rook moved
                    if(turn == 0 && m_old[1] == 0) is_rook_left_b_moved = true;
                    else if(turn == 0 && m_old[1] == 7) is_rook_left_b_moved = true;
                    else if(turn == 1 && m_old[1] == 0) is_rook_left_w_moved = true;
                    else if(turn == 1 && m_old[1] == 7) is_rook_left_w_moved = true;

                return true;}

                else return false;

        case(5):// Queen
                if(check_path(m_old, m_new,  piece)) return true;
                else return false;

        case(6):// King
                if( ( (abs(dx)+abs(dy))==1 || (abs(dx) == 1 && abs(dy) == 1) )){
                    
                    // king moved
                    if(turn == 0 ) is_king_b_moved = true;
                    if(turn == 1 ) is_king_w_moved = true;
                    return true;}

                else return false;

        
        
        default:
            return false;



    }

}


void chess_board :: change_pawn(int piece, int turn, vector<int> m_new){
    string new_piece;
    cout<< "Please give the name of the piece you want" << endl;
    //cin >> new_piece;
    cin.ignore(); // clear leftover newline
    getline(cin, new_piece);

        // convert to lowercase
    transform(new_piece.begin(), new_piece.end(), new_piece.begin(),
    [](unsigned char c){ return std::tolower(c); });

    // check / replace pawn
    if(new_piece == "pawn") board[m_new[0]][m_new[1]] = 1*(2*turn-1);
    else if(new_piece == "bishop") board[m_new[0]][m_new[1]] = 2*(2*turn-1);
    else if(new_piece == "knight") board[m_new[0]][m_new[1]] = 3*(2*turn-1);
    else if(new_piece == "rook") board[m_new[0]][m_new[1]] = 4*(2*turn-1);
    else if(new_piece == "queen") board[m_new[0]][m_new[1]] = 5*(2*turn-1);
    else{
    cout<<"Invalid selection please select again."<< endl;
    return change_pawn(piece, turn, m_new);
    } 

}




bool chess_board :: check_path(vector<int> m_old, vector<int> m_new, int piece){
     
    // only bishop(2) rook(4) queen(5) needs path check
          
        // coordiante difference dx dy
        int dx =  m_new[1]-m_old[1];
        int dy =  m_new[0]-m_old[0];

         // We have four direction in total (starting from m_old)  --> right-up(+,+), right-down(+,-), left-up(-,+), left-down(-,-)
         int x;
         int y;
         if(dx>0) x = 1; else x = -1;
         if(dy>0) y = 1; else y = -1;


    switch(piece){
        
        case 2: // Bishop
            if (abs(dx) != abs(dy)) return false;
            else{
  
                for(int i = 1;i<abs(dx);i++){

                    if(board[m_old[0]+i*y][m_old[1]+i*x] != 0) return false;

                }
                return true;
            
            }

        case 4: // Rook 
            // dx or dy is zero we are moving along x or y  
            if (dx == 0) x = 0; else y = 0; // project in x or y

            for(int i = 1;i<max(abs(dx),abs(dy));i++){

                if(board[m_old[0]+i*y][m_old[1]+i*x] != 0) return false;

            }

            return true;
        
        case 5: //Queen

            // Act like rook
            if(dx == 0 || dy == 0){
                if (dx == 0) x = 0; else y = 0; // project in x or y

                for(int i = 1;i<max(abs(dx),abs(dy));i++){
    
                    if(board[m_old[0]+i*y][m_old[1]+i*x] != 0) return false;
    
                }
            }
            // Act like bishop
            else{
                    if (abs(dx) != abs(dy)) return false;
                    else{
        
                        for(int i = 1;i<abs(dx);i++){

                            if(board[m_old[0]+i*y][m_old[1]+i*x] != 0) return false;

                        }
                    
                        }

            }


            return true;

        default:
            return false;
            

    }   

}



bool chess_board :: is_check(int turn){
    int king = (turn == 0 ? -6 : 6);  // black king = -6, white king = +6
    int king_i = -1;
    int king_j = -1;

    // find king
    for(int i = 0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE;j++){
            if(board[i][j] == king) {king_i = i; king_j = j; break;};
        }
        if(king_i != -1) break;
    }
    // Check all possible threats

    // check pawn threats
    if (turn == 0) { // black king
        int i = king_i - 1;
        if (i >= 0) {
            if (king_j-1 >= 0 && board[i][king_j-1] == 1) return true;
            if (king_j+1 < BOARD_SIZE && board[i][king_j+1] == 1) return true;
        }
    } else { // white king
        int i = king_i + 1;
        if (i < 8) {
            if (king_j-1 >= 0 && board[i][king_j-1] == -1) return true;
            if (king_j+1 < BOARD_SIZE && board[i][king_j+1] == -1) return true;
        }
    }


    // check knight threats
    int knightMoves[8][2]={{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};
    for(auto &m:knightMoves){
        int i=king_i+m[0], j=king_j+m[1];
        if(i>=0 && i<BOARD_SIZE && j>=0 && j<BOARD_SIZE){
            if(turn==0 && board[i][j]==3) return true;   // white knight
            if(turn==1 && board[i][j]==-3) return true;  // black knight
        }
    }

    // check vertical-horizontal direction threats
    int rookDirs[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
    for(auto &d:rookDirs){
        int i=king_i, j=king_j;
        while(true){
            i+=d[0]; j+=d[1];
            if(i<0||i>=BOARD_SIZE||j<0||j>=BOARD_SIZE) break;
            if(board[i][j]!=0){
                if(turn==0 && (board[i][j]==4||board[i][j]==5)) return true;   // white rook/queen
                if(turn==1 && (board[i][j]==-4||board[i][j]==-5)) return true; // black rook/queen
                break; // blocked
            }
        }
    }

    // check diagonal threats
    int diaog[4][2]={{1,1},{1,-1},{-1,1},{-1,-1}};
    for(auto &d:diaog){
        int i=king_i, j=king_j;
        while(true){
            i+=d[0]; j+=d[1];
            if(i<0||i>=BOARD_SIZE||j<0||j>=BOARD_SIZE) break;
            if(board[i][j]!=0){
                if(turn==0 && (board[i][j]==2||board[i][j]==5)) return true;   // white bishop/queen
                if(turn==1 && (board[i][j]==-2||board[i][j]==-5)) return true; // black bishop/queen
                break; 
            }
        }
    }

    for (int i=-1; i<=1; i++) {
        for (int j=-1; j<=1; j++) {
            if (i==0 && j==0) continue;
            if (king_i+i>=0 && king_i+i<BOARD_SIZE && king_j+j>=0 && king_j+j<BOARD_SIZE) {
                if (turn==0 && board[king_i + i][king_j + j]==6) return true;   // white king
                if (turn==1 && board[king_i + i][king_j + j]==-6) return true;  // black king
            }
        }
    }




return false;
}


bool chess_board :: is_checkmate(int turn ) {
    if(!is_check(turn)) return false; // not even in check

    // try all possible moves of current player
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if((turn==0 && board[i][j]<0) || (turn==1 && board[i][j]>0)){
                // iterate all moves 
                for(int x=0;x<8;x++){
                    for(int y=0;y<8;y++){
                        int new_piece = board[x][y];
                        int old_piece = board[i][j];
                        if(check_move({i,j},{x,y},turn)) { // if legal move
                            board[x][y]=old_piece; board[i][j]=0;
                            bool still_in_check = is_check(turn);
                            board[i][j]=old_piece; board[x][y]=new_piece; // undo
                            if(!still_in_check) return false; // found way out
                        }
                    }
                }
            }
        }
    }
    return true; // no moves exist
}

