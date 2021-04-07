#include "Board.hpp"
using namespace ariel;
#include <iostream>
using namespace std;
#include <climits>

const int ten = 10;
const int minRow = 0;
const int maxRow = 1;
const int minCol = 2;
const int maxCol = 3;
const int five = 5;

/*  
***********************|*************************|***********************l_
*                      |****public  functions****|                      *l_
***********************|*************************|***********************l_
*/

ariel::Board::Board()
{
    for (int i = 0; i < ten; ++i)
    {
        this->board.push_back(vector<char>(ten, '_'));
    }
}

void ariel::Board::post(unsigned int row, unsigned int col, Direction d, const string &message)
{
    postExceptions(row, col, d, message);
    if (message.length() > 0)
    {
        if (d == Direction::Horizontal)
        {
            checkAndUpdateRows(row);
            checkAndUpdateCols(col + message.length() - 1); //Calculating the last column that will be used.
            for (unsigned int index = 0; index < message.length(); ++index)
            {
                this->board.at(row).at(col + index) = message.at(index);
            }
        }
        else
        {
            checkAndUpdateRows(row + message.length() - 1);
            checkAndUpdateCols(col);
            for (unsigned int index = 0; index < message.length(); ++index)
            {
                this->board.at(row + index).at(col) = message.at(index);
            }
        }
        updatingLimits(row, col, d,message);
    }
}

unsigned int calc(unsigned int i);
string ariel::Board::read(unsigned int row, unsigned int col, Direction d, unsigned int len)
{
    readExceptions(row, col, d, len);
    if (len == 0)
    {
        return "";
    }
    if (row > (this->board.size() - 1) || col > (this->board.at(0).size() - 1))
    {
        string a(len, '_');
        return a;
    }
    string ans = buildingString(row, col, d, len);
    return ans;
}

void ariel::Board::show()
{
    if(!this->limitBreak){
        for(int i=0;i<five;++i){
            for(int j=0;j<five;++j){
                cout << "_";
            }
            cout << endl;
        }
    }else{
        unsigned int temp = this->limits[maxRow];
        unsigned int counter = 0;
        while(temp!=0){
            temp = temp/ten;
            counter++;
        }
        for(unsigned int i = this->limits[minRow];i <=this->limits[maxRow];++i){
            cout << i << ":" << std::string(counter - calc(i), ' ');
            for(unsigned int j=this->limits[minCol];j<=this->limits[maxCol];++j){
                cout << this->board.at(i).at(j);
            }
            cout << endl;
        }
    }
}

/*  
***********************|**************************|***********************l_
*                      |****private  functions****|                      *l_
***********************|**************************|***********************l_
*/

// updating the rows
void ariel::Board::checkAndUpdateRows(unsigned int row)
{
    if (this->board.size() - 1 < row)
    {
        this->board.resize(row + 1, vector<char>(this->board.at(0).size(), '_'));
    }
}

// updating the columns
void ariel::Board::checkAndUpdateCols(unsigned int col)
{
    if (this->board.at(0).size() - 1 < col)
    {
        for (unsigned int i = 0; i < this->board.size(); ++i)
        {
            this->board.at(i).resize(col + 1, '_');
        }
    }
}

// building the string for the "read" function
string ariel::Board::buildingString(unsigned int row, unsigned int col, Direction d, unsigned int len)
{
    string ans;
    unsigned int index = 0;
    if (d == Direction::Horizontal)
    {
        for (; index < len; ++index)
        {
            if ((col + index) < this->board.at(0).size())
            {
                ans += this->board.at(row).at(col + index);
            }
            else
            {
                ans += '_';
            }
        }
    }
    else
    {
        for (; index < len; ++index)
        {
            if ((row + index) < this->board.size())
            {
                ans += this->board.at(row + index).at(col);
            }
            else
            {
                ans += '_';
            }
        }
    }
    return ans;
}

void ariel::Board::updatingLimits(unsigned int row, unsigned int col, Direction d, const string &message)
{
    if (row < this->limits[minRow] || !this->limitBreak)
    {
        this->limits[minRow] = row;
    }
    if (col < this->limits[minCol] || !this->limitBreak)
    {
        this->limits[minCol] = col;
    }
    if (d == Direction::Horizontal)
    {
        if ((col + (message.size() - 1)) > this->limits[maxCol] || !this->limitBreak)
        {
            this->limits[maxCol] = col + (message.size() - 1);
        }
        if (row > this->limits[maxRow] || !this->limitBreak)
        {
            this->limits[maxRow] = row;
        }
    }
    else
    {
        if ((row + (message.size() - 1)) > this->limits[maxRow] || !this->limitBreak)
        {
            this->limits[maxRow] = row + (message.size() - 1);
        }
        if (col > this->limits[maxCol] || !this->limitBreak)
        {
            this->limits[maxCol] = col;
        }
    }
    if(!this->limitBreak){
        this->limitBreak = true;
    }
}

unsigned int calc(unsigned int i){
    if(i==0){
         return 1;
    }
    unsigned int counter = 0;
    unsigned int temp = i;
    while(temp !=0){
        temp = temp/ten;
        counter+=1;
    }
    return counter;
}

/*  
***********************|**************************|***********************l_
*                      |****Handle  exceptions****|                      *l_
***********************|**************************|***********************l_
*/

void ariel::Board::postExceptions(unsigned int row, unsigned int col, Direction d, const string &message)
{
    if (((row + message.length()) > UINT_MAX) && d == Direction::Vertical)
    {
        cout << "err(row + msg_len = " << row << "+" << message.length() << "=" << (row + message.length()) << ")" << endl;
        throw out_of_range{"You are trying to post in a place that you don't have access.\n"};
    }
    if (((col + message.length()) > UINT_MAX) && d == Direction::Horizontal)
    {
        cout << "err(col + msg_len = " << col << "+" << message.length() << "=" << (col + message.length()) << ")" << endl;
        throw out_of_range{"You are trying to post in a place that you don't have access.\n"};
    }
}

void ariel::Board::readExceptions(unsigned int row, unsigned int col, Direction d, unsigned int len)
{
    if (((row + (size_t)len > UINT_MAX) && d == Direction::Vertical))
    {
        cout << "err(row + len = " << row << "+" << (size_t)len << "=" << (row + (size_t)len) << ")" << endl;
        throw out_of_range{"You are trying to read in a place that you don't have access to read.\n"};
    }
    if (((col + (size_t)len > UINT_MAX) && d == Direction::Horizontal))
    {
        cout << "err(col + len = " << col << "+" << (size_t)len << "=" << (col + (size_t)len) << ")" << endl;
        throw out_of_range{"You are trying to read in a place that you don't have access to read.\n"};
    }
}