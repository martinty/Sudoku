//
// Created by tysse on 10.08.2018.
//

#ifndef OV12_SUDOKUBOARD_H
#define OV12_SUDOKUBOARD_H


#include <set>
#include <map>

struct position{
    unsigned int pos[3];
};

struct tile{
    int value;
    bool original;
    bool dug;
};

class SudokuBoard {
private:
    int size;
    int sizeSqrt;
    int moveIndex;
    tile* board;
    std::map<int, position> moves;
    std::set <int>* row;
    std::set <int>* col;
    std::set <int>* box;
    bool solved;
public:
    SudokuBoard();
    explicit SudokuBoard(int n);
    ~SudokuBoard();

    void set(unsigned int row, unsigned int col, unsigned int value);
    int get(unsigned int row, unsigned int col) const;
    bool isTileOriginal(unsigned int row, unsigned int col) const;

    void loadBoardFromFile(string fileName);
    void saveBoardToFile(string fileName);

    void updateSet();
    void printSet();
    int findBox(unsigned int row, unsigned int col) const;
    bool illegalSudokuPosition(unsigned int row, unsigned int col, int number) const;
    bool numberAlreadyInPosition(unsigned int row, unsigned int col) const;
    bool setSudokuNumber(unsigned int row, unsigned int col, unsigned int number);
    void printBoard()const;
    bool illegalInput(unsigned row, unsigned col, unsigned number)const;
    void gameHandler();

    void saveMoves(unsigned int row, unsigned int col, unsigned int number);
    void regretMoves(int moveCount);
    void removeMove(unsigned int row, unsigned int col);

    bool onlyOneLegalPosition(unsigned int row, unsigned int col, int number) const;
    position findBoxCoordinates(unsigned int row, unsigned int col) const;

    void solveSudoku(string fileName);
    void solveGame();

    void resetGame();

    void depthFirstSearch(unsigned int row, unsigned int col);
    void depthFirstSearchReversed(unsigned int row, unsigned int col);

    int randomWithLimits(int min, int max);
    void lasVegasAlgorithm();
    void cleanBoardFromPosition(unsigned int row, unsigned int col);

    void diggingHole(int holes);
    void removeNotOriginalNumber();

    friend ostream &operator<<(ostream &os, const SudokuBoard &board);

};


#endif //OV12_SUDOKUBOARD_H
