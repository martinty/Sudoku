//
// Created by tysse on 10.08.2018.
//
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <set>
#include <iterator>
#include <map>
#include <cstdlib>
using namespace std;
#include "SudokuBoard.h"

SudokuBoard::SudokuBoard() {
    size = 3*3;
    sizeSqrt = 3;
    moveIndex = 0;
    board = new tile[size*size];
    row = new ::set <int>[size];
    col = new ::set <int>[size];
    box = new ::set <int>[size];
    solved = false;
}

SudokuBoard::SudokuBoard(int n) {
    size = n*n;
    sizeSqrt = n;
    moveIndex = 0;
    board = new tile[size*size];
    row = new ::set <int>[size];
    col = new ::set <int>[size];
    box = new ::set <int>[size];
    solved = false;
}

SudokuBoard::~SudokuBoard() {
    delete[] board;
    delete[] row;
    delete[] col;
    delete[] box;
    board = nullptr;
    row = nullptr;
    col = nullptr;
    box = nullptr;
    moveIndex = 0;
    size = 0;
    sizeSqrt = 0;
    solved = false;
}

void SudokuBoard::set(unsigned int row, unsigned int col, unsigned int value) {
    board[row*size + col].value = value;
}

int SudokuBoard::get(unsigned int row, unsigned int col) const {
    return board[row*size + col].value;
}

bool SudokuBoard::isTileOriginal(unsigned int row, unsigned int col) const {
    return board[row*size + col].original;
}

ostream &operator<<(ostream  &os, const SudokuBoard &board){
    unsigned int x = 0;
    unsigned int y = 0;
    os << setfill('-') << setw(board.size*2 + (board.sizeSqrt+1)*2) << "\n";
    for (unsigned int row = 0; row < board.size; row++){
        os << "| ";
        for(unsigned int col = 0; col < board.size; col++){
         os << board.get(row, col) << " ";
         x++;
         if (x == board.sizeSqrt){
             os << "| ";
             x = 0;
         }
        }
        os << "\n";
        y++;
        if (y == board.sizeSqrt){
            os << setfill('-') << setw(board.size*2 + (board.sizeSqrt+1)*2) << "\n";
            y = 0;
        }
    }
    return os;
}

void SudokuBoard::loadBoardFromFile(string fileName) {
    ifstream inStream;
    inStream.open(fileName);
    if (inStream.fail()){
        cout << "File do not exist" << endl;
    }
    else{
        char nextChar;
        int nextNumber;
        int n = 0;
        inStream.get(nextChar);
        while (!inStream.eof()){
            nextNumber = int(nextChar) - 48;
            if (nextNumber >= 1 && nextNumber <= 9 ){
                board[n].value = nextNumber;
                board[n].original = false;
                board[n].dug = false;
                n++;
            }
            else if (nextNumber == 0){
                board[n].value = nextNumber;
                board[n].original = false;
                board[n].dug = false;
                n++;
            }

            inStream.get(nextChar);
        }
        inStream.close();
    }
}

void SudokuBoard::saveBoardToFile(string fileName) {
    ofstream outStream(fileName);
    for (unsigned int row = 0; row < size ; ++row) {
        for (unsigned int col = 0; col < size; ++col) {
            outStream << get(row, col);
        }
        outStream << "\n";
    }
}

void SudokuBoard::updateSet() {
    for(unsigned int i = 0; i < size; i++){
        for (unsigned int j = 0; j < size  ; j++) {
            row[i].insert(this->get(i,j));
        }
    }
    for(unsigned int i = 0; i < size; i++){
        for (unsigned int j = 0; j < size  ; j++) {
            col[i].insert(this->get(j,i));
        }
    }
    int x = 0;
    int y = 0;
    for (unsigned int i = 0; i < size ; i++) {
        for (unsigned int j = 0; j < sizeSqrt ; j++) {
            for (unsigned int k = 0; k < sizeSqrt ; k++) {
                box[i].insert(this->get(j+y*sizeSqrt, k+x*sizeSqrt));
            }
        }
        x++;
        if(x == 3){
            y++;
            x=0;
        }
    }
}

void SudokuBoard::printSet() {
    ::set <int> :: iterator itr;
    cout << "Box set" << endl;
    for (unsigned i = 0; i < size ; i++) {
        cout << i << ": ";
        for (itr = box[i].begin(); itr != box[i].end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Row set" << endl;
    for (unsigned i = 0; i < size ; i++) {
        cout << i << ": ";
        for (itr = row[i].begin(); itr != row[i].end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Col set" << endl;
    for (unsigned i = 0; i < size ; i++) {
        cout << i << ": ";
        for (itr = col[i].begin(); itr != col[i].end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
    }
}

int SudokuBoard::findBox(unsigned int row, unsigned int col) const {
    int x = 0;
    int y = 0;
    for (unsigned int i = 0; i < size ; i++) {
        for (unsigned int j = 0; j < sizeSqrt ; j++) {
            for (unsigned int k = 0; k < sizeSqrt ; k++) {
                if(row == j+y*sizeSqrt && col == k+x*sizeSqrt){
                    return i;
                }
            }
        }
        x++;
        if(x == 3){
            y++;
            x=0;
        }
    }
    return -1;
}

bool SudokuBoard::illegalSudokuPosition(unsigned int row, unsigned int col, int number) const {
    ::set <int> :: iterator setValue;
    for (setValue = this->row[row].begin(); setValue != this->row[row].end(); ++setValue) {
        if( *setValue == number){
            return true;
        }
    }
    for (setValue = this->col[col].begin(); setValue != this->col[col].end(); ++setValue) {
        if( *setValue == number){
            return true;
        }
    }
    for (setValue = this->box[findBox(row, col)].begin(); setValue != this->box[findBox(row, col)].end(); ++setValue) {
        if( *setValue == number){
            return true;
        }
    }
    return false;
}

bool SudokuBoard::numberAlreadyInPosition(unsigned int row, unsigned int col) const {
    return bool(get(row, col));
}

bool SudokuBoard::setSudokuNumber(unsigned int row, unsigned int col, unsigned int number) {
    if(!illegalSudokuPosition(row,col,number) && !numberAlreadyInPosition(row,col)){
        set(row,col,number);
        saveMoves(row, col, number);
        updateSet();
        return true;
    }
    return false;

}

void SudokuBoard::printBoard() const {
    unsigned int x = 0;
    unsigned int y = 0;
    cout << setfill('*') << setw(size*2 + (sizeSqrt+1)*2 + 4) << "\n";
    cout << "    ";
    for (unsigned int i = 0; i < size ; i++) {
        if(x == sizeSqrt){
            cout << "  ";
            x = 0;
        }
        cout << i+1 << " ";
        x++;
    }
    x = 0;
    cout << "\n  " << setfill('-') << setw(size*2 + (sizeSqrt+1)*2) << "\n";
    for (unsigned int row = 0; row < size; row++){
        cout << row+1 << " | ";
        for(unsigned int col = 0; col < size; col++){
            cout << get(row, col) << " ";
            x++;
            if (x == sizeSqrt){
                cout << "| ";
                x = 0;
            }
        }
        cout << "\n";
        y++;
        if (y == sizeSqrt){
            cout << "  " << setfill('-') << setw(size*2 + (sizeSqrt+1)*2) << "\n";
            y = 0;
        }
    }
    cout << setfill('*') << setw(size*2 + (sizeSqrt+1)*2 + 4) << "\n";
}

bool SudokuBoard::illegalInput(unsigned row, unsigned col, unsigned number) const {
    if(number < 0 || number > size){
        return true;
    }
    else if(row < 0 || row >= size){
        return true;
    }
    else if(col < 0 || col >= size){
        return true;
    }
    return false;
}

void SudokuBoard::gameHandler() {

    unsigned int row, col;
    unsigned int number = 0;
    int regret = 0;

    cout << "Play Sudoku!" << endl;
    cout << "Number > size*size = quit and save" << endl;
    loadBoardFromFile("simpleSudoku.txt");
    updateSet();
    printBoard();

    while(number <= size*size){
        cout << "Set new number on board [row   col    number]: ";
        cin >> row;
        cin >> col;
        cin >> number;
        row--;
        col--;
        if(!illegalInput(row, col, number)){
            if(!setSudokuNumber(row, col, number)){
                cout << "Can't set " << number << " in position (" << row+1 << ", " << col+1 << ")" << endl;
            }
            else{
                printBoard();
            }
        }
        else {
            cout << "Illegal input! Try again" << endl;
        }
        cout << "Regret moves [0 = no    >0 = yes]: ";
        cin >> regret;
        regretMoves(regret);
    }
    saveBoardToFile("simpleSudokuAnswer");
    cout << "Game end!" << endl << endl;
}

void SudokuBoard::saveMoves(unsigned row, unsigned col, unsigned number) {
    position move;
    move.pos[0] = row;
    move.pos[1] = col;
    move.pos[2] = number;
    moveIndex++;
    moves[moveIndex] = move;
}

void SudokuBoard::regretMoves(int moveCount) {
    position move;
    for(int i = moveIndex; i > moveIndex-moveCount; i--){
        move = moves[i];
        set(move.pos[0], move.pos[1], 0);
        moves.erase(i);
        row[move.pos[0]].erase(move.pos[2]);
        col[move.pos[1]].erase(move.pos[2]);
        box[findBox(move.pos[0],move.pos[1])].erase(move.pos[2]);
    }
    moveIndex -= moveCount;
    printBoard();
}

void SudokuBoard::removeMove(unsigned int row, unsigned int col) {
    this->row[row].erase(get(row, col));
    this->col[col].erase(get(row, col));
    box[findBox(row,col)].erase(get(row, col));
    set(row, col, 0);
}

bool SudokuBoard::onlyOneLegalPosition(unsigned int row, unsigned int col, int number) const {

    bool rowStatus = true;
    bool colStatus = true;
    bool boxStatus = true;
    bool nakedSingle = false;

    //Check row
    for (unsigned int i = 0; i < size ; i++) {
        if(i != row){
            if(!numberAlreadyInPosition(i, col)){
                if(!illegalSudokuPosition(i, col, number)){
                    rowStatus = false;
                }
            }
        }
    }
    //Check col
    for (unsigned int i = 0; i < size ; i++) {
        if(i != col){
            if(!numberAlreadyInPosition(row, i)){
                if(!illegalSudokuPosition(row, i, number)){
                    colStatus = false;
                }
            }
        }
    }
    //Check box
    position coordinates = findBoxCoordinates(row, col);
    unsigned int x = coordinates.pos[1];
    unsigned int y = coordinates.pos[0];
    for (unsigned int j = 0; j < sizeSqrt ; j++) {
        for (unsigned int k = 0; k < sizeSqrt ; k++) {
            if(!(j+y*sizeSqrt == row && k+x*sizeSqrt == col)){
                if(!numberAlreadyInPosition(j+y*sizeSqrt, k+x*sizeSqrt)){
                    if(!illegalSudokuPosition(j+y*sizeSqrt, k+x*sizeSqrt, number)){
                        boxStatus = false;
                    }
                }
            }
        }
    }

    //Check if only one value from all 3 set combined is missing (naked single)
    ::set <int> :: iterator itr;
    ::set <int> checkSet;
    for (itr = box[findBox(row, col)].begin(); itr != box[findBox(row, col)].end(); ++itr) {
        checkSet.insert(*itr);
    }
    for (itr = this->row[row].begin(); itr != this->row[row].end(); ++itr) {
        checkSet.insert(*itr);
    }
    for (itr = this->col[col].begin(); itr != this->col[col].end(); ++itr) {
        checkSet.insert(*itr);
    }
    if(checkSet.size() == size){
        nakedSingle = true;
        for(itr = checkSet.begin(); itr != checkSet.end(); ++itr){
            if(*itr == number){
                nakedSingle = false;
            }
        }
    }

    if (boxStatus || rowStatus || colStatus || nakedSingle){
        return true;
    }
    return false;
}

position SudokuBoard::findBoxCoordinates(unsigned int row, unsigned int col) const {
    position coordinates;
    unsigned int x = 0;
    unsigned int y = 0;
    for (unsigned int i = 0; i < size ; i++) {
        for (unsigned int j = 0; j < sizeSqrt ; j++) {
            for (unsigned int k = 0; k < sizeSqrt ; k++) {
                if(row == j+y*sizeSqrt && col == k+x*sizeSqrt){
                    coordinates.pos[0] = y;
                    coordinates.pos[1] = x;
                    return coordinates;
                }
            }
        }
        x++;
        if(x == 3){
            y++;
            x=0;
        }
    }
}

void SudokuBoard::solveSudoku(string fileName) {
    loadBoardFromFile(fileName);
    updateSet();
    printBoard();
    for (int i = 0; i < size*size; i++) {
        for (unsigned int row = 0; row < size; row++) {
            for (unsigned int col = 0; col < size; col++) {
                for (unsigned int number = 1; number <= size; number++) {
                    if(!numberAlreadyInPosition(row, col)){
                        if(onlyOneLegalPosition(row, col, number)){
                            if(!illegalSudokuPosition(row, col, number)){
                                set(row, col, number);
                                cout << "Row: " << row+1 << "     Col: " << col+1 << "      Number: " << number << endl;
                                updateSet();
                            }
                        }
                    }
                }
            }
        }
    }
    printBoard();
}

void SudokuBoard::solveGame() {
    for (int i = 0; i < size*size; i++) {
        for (unsigned int row = 0; row < size; row++) {
            for (unsigned int col = 0; col < size; col++) {
                for (unsigned int number = 1; number <= size; number++) {
                    if(!numberAlreadyInPosition(row, col)){
                        if(onlyOneLegalPosition(row, col, number)){
                            if(!illegalSudokuPosition(row, col, number)){
                                set(row, col, number);
                                updateSet();
                            }
                        }
                    }
                }
            }
        }
    }
}

void SudokuBoard::resetGame() {
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < size; ++j) {
            if(!isTileOriginal(i,j)){
                removeMove(i,j);
            }
        }
    }
    solved = false;
}

void SudokuBoard::depthFirstSearch(unsigned int row, unsigned int col) {
    if (!numberAlreadyInPosition(row, col) && !solved) {
        for (unsigned int i = 1; i <= size; ++i) {
            if (setSudokuNumber(row, col, i) && !solved) {
                if (col != size - 1) {
                    depthFirstSearch(row, col + 1);
                }
                else {
                    if(row+1 < size){
                        depthFirstSearch(row + 1, 0);
                    }
                    else{
                        solved = true;
                    }
                }
                if(!solved){
                    removeMove(row, col);
                }
            }
        }
    }
    else{
        if (col != size - 1) {
            depthFirstSearch(row, col + 1);
        }
        else {
            if(row+1 < size){
                depthFirstSearch(row + 1, 0);
            }
            else{
                solved = true;
            }
        }
    }
}

void SudokuBoard::depthFirstSearchReversed(unsigned int row, unsigned int col) {
    if (!numberAlreadyInPosition(row, col) && !solved) {
        for (unsigned int i = size; i >= 1; --i) {
            if (setSudokuNumber(row, col, i) && !solved) {
                if (col != size - 1) {
                    depthFirstSearchReversed(row, col + 1);
                }
                else {
                    if(row+1 < size){
                        depthFirstSearchReversed(row + 1, 0);
                    }
                    else{
                        solved = true;
                    }
                }
                if(!solved){
                    removeMove(row, col);
                }
            }
        }
    }
    else{
        if (col != size - 1) {
            depthFirstSearchReversed(row, col + 1);
        }
        else {
            if(row+1 < size){
                depthFirstSearchReversed(row + 1, 0);
            }
            else{
                solved = true;
            }
        }
    }
}

int SudokuBoard::randomWithLimits(int min, int max) {
    return rand() % (max+1-min) + min ;
}

void SudokuBoard::lasVegasAlgorithm() {
    for (unsigned int row = 0; row < size; ++row) {
        for (unsigned int col = 0; col < size; ++col) {
            while(!solved){
                if(get(row, col)){
                    removeMove(row, col);
                }
                if(setSudokuNumber(row, col, randomWithLimits(1, size))){
                    depthFirstSearch(0,0);
                }
            }
            solved = false;
            cleanBoardFromPosition(row, col);
        }
    }
}

void SudokuBoard::cleanBoardFromPosition(unsigned int row, unsigned int col) {
    for (unsigned int y = 0; y < size; ++y) {
        for (unsigned int x = 0; x < size; ++x) {
            if(y == row){
                if(x > col){
                    removeMove(y, x);
                }
            }
            else if(y > row){
                removeMove(y, x);
            }
        }
    }
}

void SudokuBoard::diggingHole(int holes) {
    for (int i = 0; i < size*size ; ++i) {
        board[i].original = true;
    }
    int n = 0;
    while(n < holes){
        unsigned int row = randomWithLimits(0,size-1);
        unsigned int col = randomWithLimits(0, size-1);
        if(!board[row*size+col].dug){
            int solutionOne[size*size];
            int solutionTwo[size*size];
            int number = get(row, col);
            board[row*size + col].original = false;
            removeNotOriginalNumber();
            depthFirstSearch(0,0);
            if(solved){
                solved = false;
                for (int i = 0; i < size*size; ++i) {
                    solutionOne[i] = board[i].value;
                }
                removeNotOriginalNumber();
                depthFirstSearchReversed(0,0);
                solved = false;
                for (int i = 0; i < size*size; ++i) {
                    solutionTwo[i] = board[i].value;
                }
                bool uniqueSolution = true;
                for (int i = 0; i < size*size; ++i) {
                    if(solutionOne[i] != solutionTwo[i]){
                        uniqueSolution = false;
                    }
                }
                removeNotOriginalNumber();
                if(!uniqueSolution) {
                    set(row, col, number);
                    updateSet();
                    board[row*size + col].original = true;
                }
                else{
                    n++;
                    board[row*size + col].dug = true;
                }
            }
            else{
                removeNotOriginalNumber();
                set(row, col, number);
                updateSet();
                board[row*size + col].original = true;
            }
        }
    }
}

void SudokuBoard::removeNotOriginalNumber() {
    for (unsigned int row = 0; row < size ; ++row) {
        for (unsigned int col = 0; col < size ; ++col) {
            if(!isTileOriginal(row, col)){
                removeMove(row, col);
            }
        }
    }
}