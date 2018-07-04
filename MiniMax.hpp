//
//  MiniMax.hpp
//  Checkers
//
//  Created by Bhavish Bhattar on 6/28/18.
//  Copyright © 2018 Bhavish Bhattar. All rights reserved.
//

#ifndef MiniMax_hpp
#define MiniMax_hpp

#include <stdio.h>
#include <vector>
#include <stack>
#include "GameBoard.h"
#include "Checkers.h"
#include <tuple>
using namespace checkers;
using namespace std;

class Minimax{
public:
    Minimax();
    Minimax(Checkers master);
    //vector<int> _curr_moves;
    vector<int> _move;
    int steps = 0;
private:
    /*
    struct piece_minMax{
        bool isKing = false;
        int type;
        bool isDead = false;
        int tile;
    }; */
   // piece_minMax maxPieces[12];
   // piece_minMax minPieces[12];
    Checkers _master;
    
   // Checkers::Tile Board[32];
    //stack<Checkers> _states; //make this a stack
   /*
    int blackPieces = 12;
    int redPieces = 12;
    int redKings = 0;
    int blackKings = 0;
    */
    pair<bool,vector<pair<int,int>>> getMoves(Checkers game, int turn); //have this return a vector of int pairs to identify source/destination
    
    int getScore(Checkers game);
    
    int miniMax(int depth, pair<bool,vector<pair<int,int>>>, Checkers game, int turn, int alpha, int beta);
    
    
};

#endif /* MiniMax_hpp */
