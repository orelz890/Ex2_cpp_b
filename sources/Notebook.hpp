#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <stdexcept>
#include "Direction.hpp"

#include <locale>
#include <cctype>

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
    };

};
