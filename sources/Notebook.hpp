#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <stdexcept>
#include "Direction.hpp"

using namespace std;
using namespace ariel;

#define MIN_CHAR 32
#define MAX_CHAR 126
#define LINE_LEN 100
#define MIN_PAGE 0
#define ZERO 0

namespace ariel{
    class Notebook{
        int last_row_filled = 0;
        int last_row_col_filled = 0;
    private:
        map <int, map<int, char[LINE_LEN]>> notebook;
    public:
        // Notebook(){}
        // Notebook();
        // ~Notebook();

        void write(int page, int row, int col, Direction direction, string data);
        string read(int page, int row, int col, Direction direction, int readLength);
        void erase(int page, int row, int col, Direction direction, int eraselength);
        void show(int page);
        void fill_with_under_score(int page, int row, int col, Direction direction, int action_len);
        void open_new_notebook(){
            notebook.clear();
        }
        void set_notebook(int page, int row, int col, char c){
            notebook[page][row][col] = c;
        }
        char get_char_at(int page, int row, int col){
            return notebook[page][row][col];
        }
    };
};
