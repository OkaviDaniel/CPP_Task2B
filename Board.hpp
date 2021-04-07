#include <iostream>
#include <vector>
#include "Direction.hpp"
using namespace std;


namespace ariel
{
    class Board
    {
    vector<vector<char>> board;
    unsigned int limits[4] = {0,0,0,0}; // [minRowMinCol, maxRowMinCol, minRowMaxCol, maxRowMaxCol]
    bool limitBreak = false;
    public:
        Board();
        void post(unsigned int row, unsigned int col, Direction d, const string &message);
        string read(unsigned int row, unsigned int col, Direction d, unsigned int len);
        void show();
    private:
        void checkAndUpdateRows(unsigned int row);
        void checkAndUpdateCols(unsigned int col);
        string buildingString(unsigned int row, unsigned int col, Direction d, unsigned int len);
        static void postExceptions(unsigned int row, unsigned int col, Direction d, const string &message);
        static void readExceptions(unsigned int row, unsigned int col, Direction d, unsigned int len);
        void updatingLimits(unsigned int row, unsigned int col, Direction d, const string &message);
    };
}