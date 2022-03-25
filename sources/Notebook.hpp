#include <iostream>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "Direction.hpp"

using namespace std;
using namespace ariel;

#define MIN_CHAR 32
#define MAX_CHAR 126
#define LINE_LEN 100
#define MIN_PAGE 0

int last_row_filled = 0;
int last_row_col_filled = 0;

namespace ariel{
    class Notebook{
    private:
        unordered_map <int, unordered_map<int, char[LINE_LEN]>> notebook;
    public:
        void write(int page, int row, int col, Direction direction, const string & data);
        string read(int page, int row, int col, Direction direction, int readLength);
        void erase(int page, int row, int col, Direction direction, int eraselength);
        void show(int page);

        void open_new_notebook(){
            notebook.clear();
        }
    };
};