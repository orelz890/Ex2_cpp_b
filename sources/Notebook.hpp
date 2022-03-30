#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <stdexcept>
#include "Direction.hpp"

#include <locale>
#include <cctype>

const int MIN_CHAR = 32;
const int MAX_CHAR = 126;
const int LINE_LEN = 100;
const int MIN_PAGE = 0;
const int ZERO = 0;

using namespace std;

namespace ariel{
    class Notebook{
    private:
        map <int, map<int, char[100]>> notebook;

    public:
        Notebook(/*args*/){}
        ~Notebook(){}

        int last_row_filled = 0;
        void write(int page, int row, int col, Direction direction, string data);
        string read(int page, int row, int col, Direction direction, int readLength);
        void erase(int page, int row, int col, Direction direction, int eraselength);
        void show(int page);
        void set_notebook(int page, int row, int col, char c){
            notebook[page][row][col] = c;
            if (row > last_row_filled){
                last_row_filled = row;
            }
            
        }
        char get_char_at(int page, int row, int col){
            return notebook[page][row][col];
        }
    };

};
