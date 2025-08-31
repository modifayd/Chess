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

#include "chess.hpp"


using namespace std;



int main(){


    chess_board board;
    bool is_move_okey = true;
    int termination = 0;

    // decision of begining player
    srand(time(0)); // seed once
    int whos_turn = 1; // 0 for black 1 for white
    if (rand() % 2)  whos_turn = 0;

    while(!termination){

        cout<<" >> Updating Board >>"<< endl;
        sleep(1); // delay 2 seconds

        // print online
        board.print();

        if(whos_turn == 1)
        cout<<"Expecting movement from WHITE !"<<endl;
        else
        cout<<"Expecting movement from BLACK !"<<endl;
        
        string m_old;
        string m_new;

        // take movement from user
        cout << "Enter a movement: ";
        cin >> m_old; 
        if(m_old == "q"); break;
        cin >> m_new; 

        is_move_okey = board.move(m_old, m_new, whos_turn, termination);              

        // swap player
        if(is_move_okey) whos_turn = (1-whos_turn);

    }
    return 0;
}