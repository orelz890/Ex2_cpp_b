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
        // unordered_map <int, unordered_map<int, array<char, LINE_LEN>>> notebook;
        unordered_map <int, unordered_map<int, char[LINE_LEN]>> notebook;

        // unordered_map <int[3], char> notebook;
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
            // notebook[pair<int, int, int>(page, row)][col] = c;
            // int pos[3] = {page, row, col};
            // notebook.insert(pair<int[3],char>(pos, c));
        }
        char get_char_at(int page, int row, int col){
            // char ans = notebook.find(pair<int, int, int>(page, row, col));
            // return ans;
            return notebook[page][row][col];
        }
    };
};