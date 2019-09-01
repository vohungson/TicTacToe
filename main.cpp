//
//  main.cpp
//  TicTacToe
//
//  Created by Vo Hung Son on 1/12/19.
//  Copyright © 2019 Vo Hung Son. All rights reserved.
//

#include <iostream>
#define INF 1000
#define WIN 100
using namespace std;

class Game {
private:
    char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    struct Move { int row, col;};
    char Machine = 'x', Human = 'o';
    bool algorithms = true;//true -> run miniMax; false -> run AnphaBeta
    int step = 0;//The number of steps when the machine evaluate
public:
    void initialize(){
        int number = 0;
        do{
            cout<<"\nThe new board of The Game Tic-Tac-Toe: ";
            guidePlayGame(board);
            cout<<"The Menu:\n1. Human Play Frist";
            cout<<"\n2. Machine Play First with miniMax algorithm";
            cout<<"\n3. Machine Play First with alphaBeta algorithm";
            cout<<"\n4. MiniMax Algorithm play with AlphaBeta algorithm";
            cout<<"\n5. Exit Program\nPlease input the number: ";
            cin>>number;
            switch (number) {
                case 1: humanPlayFirst(); break;
                case 2: algorithms = true; machinePlayFirst(); break;
                case 3: algorithms = false; machinePlayFirst(); break;
                case 4: minimaxPlayWithAlphabeta(); break;
                default: if(number!=5) cout<<"WRONG NUMBER!\n\n"; break;
            }
        }while(number != 5);
    }
    
    void minimaxPlayWithAlphabeta(){
        char result = ' ';//D -> Draw, X -> machine win, O -> human win
        do{
            if(isNextMovesExist()){
                Move bestMove = findTheBestMove();//best move for Minimax
                board[bestMove.row][bestMove.col] = Human;
                algorithms = true;
                cout<<"\nMinimax just played O at position: ";
                cout<<(bestMove.row*3 + bestMove.col + 1);
                cout<<" -> ("<<bestMove.row<<","<<bestMove.col<<")";
                guidePlayGame(board);
                if(isWin(Human)) {result = Human; break;}
            }
            else result = 'D';//Draw
            if(isNextMovesExist()){
                Move bestMove = findTheBestMove();//best move for AlphaBeta
                board[bestMove.row][bestMove.col] = Machine;
                algorithms = false;
                cout<<"\nAlphaBeta just played X at position: ";
                cout<<(bestMove.row*3 + bestMove.col + 1);
                cout<<" -> ("<<bestMove.row<<","<<bestMove.col<<")";
                guidePlayGame(board);
                if(isWin(Machine)) {result = Machine; break;}
            }
            else result = 'D';//Draw
        }while(result == ' ');
        resultOfGame(result);
    }
    
    void humanPlayFirst(){
        cout<<"\nHUMAN PLAY FIRST";
        char result = ' ';//D -> Draw, X -> machine win, O -> human win
        do{
            if(isNextMovesExist()){
                humanPlay();
                guidePlayGame(board);
                if(isWin(Human)) {result = Human; break;}
            }
            else result = 'D';//Draw
            if(isNextMovesExist()){
                Move bestMove = findTheBestMove();//best move for Machine
                board[bestMove.row][bestMove.col] = Machine;
                cout<<"\nMACHINE just played X at position: ";
                cout<<(bestMove.row*3 + bestMove.col + 1);
                cout<<" -> ("<<bestMove.row<<","<<bestMove.col<<")";
                guidePlayGame(board);
                if(isWin(Machine)) {result = Machine; break;}
            }
            else result = 'D';//Draw
        }while(result == ' ');
        resultOfGame(result);
    }
    
    void machinePlayFirst(){
        cout<<"\nMACHINE PLAY FIRST";
        char result = ' ';//D -> Draw, X -> machine win, O -> human win
        do{
            if(isNextMovesExist()){
                Move bestMove = findTheBestMove();//best move for Machine
                board[bestMove.row][bestMove.col] = Machine;
                cout<<"\nMACHINE just played X at position: ";
                cout<<(bestMove.row*3 + bestMove.col + 1);
                cout<<" -> ("<<bestMove.row<<","<<bestMove.col<<")";
                guidePlayGame(board);
                if(isWin(Machine)) {result = Machine; break;}
            }
            else result = 'D';//Draw
            if(isNextMovesExist()){
                humanPlay();
                guidePlayGame(board);
                if(isWin(Human)) {result = Human; break;}
            }
            else result = 'D';//Draw
        }while(result == ' ');
        resultOfGame(result);
    }
    
    void resultOfGame(char result){
        if(result == Machine) cout<<"\nGAME OVER! Winner is Machine";
        if(result == Human) cout<<"\nGAME OVER! Winner is Human";
        if(result == 'D') cout<<"\nGAME OVER! The result is DRAW";
        for(int i = 0; i < 3; i++)//reset to play a new game.
            for(int j = 0; j < 3; j++)
                board[i][j] = ' ';
    }
    
    void humanPlay(){// input the number for O player
        int number;//The value of number is from 1 to 9.
        do{
            cout<<"\nHUMAN! Please Input the numbered Cell: ";
            cin>>number;
        }while(!checkNumber(number));
        board[(number-1)/3][(number-1)-((number-1)/3)*3] = Human;
        cout<<"\nHUMAN just played O at position: "<<number<<" -> ";
        cout<<"("<<((number-1)/3)<<","<<((number-1)-((number-1)/3)*3)<<")";
    }
    
    bool checkNumber(int number){
        bool check = true;
        if(number < 1 || number > 9){
            check = false;
            cout<<"The number of this cell must be from 1 to 9. TRY AGAIN!";
        }
        else {
            if(board[(number-1)/3][(number-1)-((number-1)/3)*3]!=' '){
                cout<<"This cell has already played. TRY AGAIN!";
                check = false;
            }
        }
        return check;
    }
    
    void guidePlayGame(char printBoard[3][3]){
        for(int i = 0; i < 3; i++){
            cout<<"\n  -----------\n"<<" | ";
            for(int j = 0; j < 3; j++){
                if(printBoard[i][j]!=' ') cout<<printBoard[i][j]<<" | ";
                else cout<<char(printBoard[i][j] + 17 + i*3 + j)<<" | ";
            }
        }
        cout<<"\n  -----------\n";
    }
    
    bool isWin(char c){//check row and column and then diagonal line.
        bool win = false;
        for(int i = 0; i < 3; i++){//check row and column
            if(board[i][0]==c && board[i][1]==c && board[i][2]==c) win=true;
            if(board[0][i]==c && board[1][i]==c && board[2][i]==c) win=true;
        }
        if(board[0][0]==c && board[1][1]==c && board[2][2]==c) win=true;
        if(board[0][2]==c && board[1][1]==c && board[2][0]==c) win=true;
        return win;
    }
    
    bool isNextMovesExist(){
        for (int i = 0; i<3; i++)
            for (int j = 0; j<3; j++)
                if (board[i][j]==' ')
                    return true;
        return false;
    }
    
    int anphaBeta(int depth, bool isMax, int alpha, int beta){
        step++;
        if(isWin(Machine)) return WIN;
        if(isWin(Human)) return -WIN;
        if (isNextMovesExist()==false) return 0;
        if (depth >= 3) return 0;// Terminating condition
        if (isMax) {
            int best = -INF;
            for (int i = 0; i<3; i++){// Traverse all cells
                for (int j = 0; j<3; j++){
                    if (board[i][j]==' '){// Check if cell is empty
                        board[i][j] = Machine;// Make the move
                        int value = anphaBeta(depth++, !isMax, alpha, beta);
                        board[i][j] = ' ';// Undo the move
                        best = max(best, value);
                        alpha = max(alpha, best);
                        if (beta <= alpha) break; // Alpha Beta Pruning
                    }
                }
            }
            return best;
        }
        else{
            int best = INF;
            for (int i = 0; i<3; i++){// Traverse all cells
                for (int j = 0; j<3; j++){
                    if (board[i][j]==' '){// Check if cell is empty
                        board[i][j] = Human;// Make the move
                        int value = anphaBeta(depth++, !isMax, alpha, beta);
                        board[i][j] = ' ';// Undo the move
                        best = min(best, value);
                        beta = min(beta, best);
                        if (beta <= alpha) break;// Alpha Beta Pruning
                    }
                }
            }
            return best;
        }
    }
    
    int miniMax(int depth, bool isMax){
        step++;
        if(isWin(Machine)) return WIN;
        if(isWin(Human)) return -WIN;
        if (isNextMovesExist()==false) return 0;
        if(depth>=3) return 0;
        if (isMax){// If this maximizer's move
            int best = -INF;
            for (int i = 0; i<3; i++){// Traverse all cells
                for (int j = 0; j<3; j++){
                    if (board[i][j]==' '){// Check if cell is empty
                        board[i][j] = Machine;// Make the move
                        best = max(best, miniMax(depth++,!isMax) );
                        board[i][j] = ' ';// Undo the move
                    }
                }
            }
            return best;
        }
        else {// If this minimizer's move
            int best = INF;
            for (int i = 0; i<3; i++){// Traverse all cells
                for (int j = 0; j<3; j++){
                    if (board[i][j]==' '){// Check if cell is empty
                        board[i][j] = Human;// Make the move for Human
                        best = min(best, miniMax(depth++,!isMax));
                        board[i][j] = ' ';// Undo the move
                    }
                }
            }
            return best;
        }
    }
    
    Move findTheBestMove(){
        int bestValue = -INF;
        Move bestMove;
        bestMove.row = -1;
        bestMove.col = -1;
        int minStep = 0;
        for (int i = 0; i<3; i++){//Traverse all empty cells to choose best
            for (int j = 0; j<3; j++){
                if (board[i][j]==' '){
                    board[i][j] = Machine;//cout the best move for Machine
                    step = 0;
                    int currentValue;//Run miniMax or AlphaBeta here
                    if(algorithms) currentValue = miniMax(0,false);
                    else currentValue = anphaBeta(0, false, -INF, INF);
                    board[i][j] = ' ';// Undo the move
                    if (currentValue > bestValue){//save the best value
                        bestMove.row = i;
                        bestMove.col = j;
                        bestValue = currentValue;
                        minStep = step;
                        //cout <<"\n-> "<<step<<" ("<<i<<","<<j<<")";
                    }
                    if (currentValue == bestValue && step < minStep){
                        bestMove.row = i;
                        bestMove.col = j;
                        minStep = step;
                        //cout <<"\n=> "<<step<<" ("<<i<<","<<j<<")";
                    }//save the best move with min steps
                }
            }
        }
        return bestMove;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Game TicTacToe;
    TicTacToe.initialize();
    cout<<"\n";
    return 0;
}
