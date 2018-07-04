//
//  MiniMax.cpp
//  Checkers
//
//  Created by Bhavish Bhattar on 6/28/18.
//  Copyright © 2018 Bhavish Bhattar. All rights reserved.
//
#define MIN -10000
#define MAX 10000

#include "MiniMax.hpp"

Minimax::Minimax(){
    
}

Minimax::Minimax(Checkers master){
   _master = master;
   // cout<<"calling\n";
   miniMax(9, getMoves(_master, _master._turn), _master, _master._turn, MIN, MAX);
    

}
pair<bool,vector<pair<int,int>>> Minimax::getMoves(Checkers game, int turn){
    pair<bool,vector<pair<int,int>>> moves;
    moves.first = false;
    pair<bool,vector<pair<int,int>>> Cutting_moves;
    Cutting_moves.first = true;
    bool isCutting = false;
    
    for(int i = 0; i < 32; i++){
        pair<bool,vector<int>> curr_moves;
        if(game.isOccupied(i) && game.getType(i) == turn){
           curr_moves = game.possibleMoves(i, game.canCut(i));
            if(curr_moves.first)
                isCutting = true;
            if(isCutting == false ||(isCutting && curr_moves.first)){
            for(vector<int>::iterator it = curr_moves.second.begin(); it != curr_moves.second.end(); ++it){
                if(!isCutting)
                    moves.second.push_back(make_pair(i,*it));
                else
                    Cutting_moves.second.push_back(make_pair(i,*it));
            }
                
            }
        }
        
    }
    if(isCutting)
        return Cutting_moves;
    else
        return moves;
}

int Minimax::getScore(Checkers game){
    int score = 0;
    int red = 0;
    int black = 0;
    int rking = 0;
    int bking = 0;
    
    for(int i = 0; i < 32; i++){
        if(game.isOccupied(i)){
            if(game.Board_[i].has_Bpiece){
                black++;
                if(game.Board_[i].has_Bking)
                    bking++;
            }
            if(game.Board_[i].has_Rpiece){
                red++;
                if(game.Board_[i].has_Rking)
                    rking++;
            }
            
        }
    }
    score = bking + 2*(12-red) - rking - 2*(12-black);
    return score;
}

int Minimax::miniMax(int depth, pair<bool,vector<pair<int,int>>> moves, Checkers currGame, int turn, int alpha, int beta){
    steps++;
    if(depth == 0 || moves.second.empty()){
        int a = getScore(currGame);
       // cout<<"Steps: "<<steps<<"score" <<getScore(currGame)<<"\n";
        return a;
    }
   
    if(turn){
        
        int bestValue = MIN;
                //for each possible move at this level
        vector<int> finMoves;
        vector<int> nodeMoves;
        for(vector<pair<int,int>>::iterator it = moves.second.begin(); it != moves.second.end(); ++it){
            
            
            Checkers nextgame = currGame;
            nextgame.move((*it).first, (*it).second);
            //if Cutting
            if(moves.first){
                int dest = (*it).second;
                nextgame.killPiece(nextgame.findCutPiece((*it).first, (*it).second));
                pair<bool,vector<int>> secondaryMoves = nextgame.canCut((*it).second);
               
                while(secondaryMoves.first){
                    
                    //This needs to be edited to consider ALL secondary moves if they exist
                    int nextDest = secondaryMoves.second[0];
                    nodeMoves.push_back(nextDest);
                    nextgame.move(dest, nextDest);
                    nextgame.killPiece(nextgame.findCutPiece(dest, nextDest));
                    secondaryMoves = nextgame.canCut(nextDest);
                }
                
            }
            
            //dive into tree
            pair<bool,vector<pair<int,int>>> nextMoves = getMoves(nextgame, 0);
            int value = miniMax(depth - 1, nextMoves , nextgame, 0 , alpha, beta);
            if(value > bestValue){
                finMoves.clear();
                finMoves.push_back((*it).first);
                finMoves.push_back((*it).second);
                for(int i = 0; i < nodeMoves.size(); i++)
                    finMoves.push_back(nodeMoves[i]);
            }
            bestValue = max(bestValue, value);
            alpha = max(alpha, bestValue);
            
            
           
            if( beta <= alpha){
                break;
            }
  
        }
        _move = finMoves;
        return bestValue;
    }
    else
    {
        int bestValue = MAX;
        
        //for each possible move at this level
        for(vector<pair<int,int>>::iterator it = moves.second.begin(); it != moves.second.end(); ++it){
            Checkers nextgame = currGame;
            nextgame.move((*it).first, (*it).second);
            //if Cutting
            if(moves.first){
                int dest = (*it).second;
                nextgame.killPiece(nextgame.findCutPiece((*it).first, (*it).second));
                pair<bool,vector<int>> secondaryMoves = nextgame.canCut((*it).second);
                
                while(secondaryMoves.first){
                    
                    //This needs to be edited to consider ALL secondary moves if they exist
                    int nextDest = secondaryMoves.second[0];
                    
                    
                    nextgame.move(dest, nextDest);
                    nextgame.killPiece(nextgame.findCutPiece(dest, nextDest));
                    secondaryMoves = nextgame.canCut(nextDest);
                }
                
            }
            
            //dive into tree
            pair<bool,vector<pair<int,int>>> nextMoves = getMoves(nextgame, 1);
            int value = miniMax(depth - 1, nextMoves , nextgame, 1 , alpha, beta);
            bestValue = min(bestValue, value);
            beta = min(beta, bestValue);
            
            if( beta <= alpha)
                break;
            
            
        }
        
        return bestValue;
        
    }
    
}
