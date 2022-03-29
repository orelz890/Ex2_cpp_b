#include "Notebook.hpp"

const int MIN_CHAR = 32;
const int MAX_CHAR = 126;
const int LINE_LEN = 100;
const int MIN_PAGE = 0;
const int ZERO = 0;

namespace ariel{

    void Notebook::write(int page, int row, int col, Direction direction, string data){

        int data_len = data.length();
        if(page < MIN_PAGE || row < ZERO || col < ZERO){
            throw runtime_error("page & row & column position most be positive!");
        }
        if(col >= LINE_LEN || (direction == Direction::Horizontal && col + data_len >= LINE_LEN)){
            throw runtime_error("Writing in illegal columns!");
        }
        // Checking for an illigal char
        for (int i = 0; i < data_len; i++){
            char curr_char = data[(unsigned int)i];

            if (curr_char < MIN_CHAR || curr_char > MAX_CHAR || curr_char == '~'){
                throw runtime_error("The char u picked is not printable!");
            }
            if (direction == Direction::Horizontal){
                // Char is legal & not under score, means we cant write! 
                curr_char = notebook[page][row][col+i];    
                if (curr_char != '_' && curr_char != '\0'){
                    throw runtime_error("Cant over write!");
                }
            }
            // Vertical
            else{
                curr_char = notebook[page][row+i][col];
                if(curr_char != '_' && curr_char != '\0'){
                    throw runtime_error("Cant over write!");
                }
            }
        }

        // Putting the new data
        if (direction == Direction::Horizontal){
            for (int i = 0; i < data_len; i++){
                notebook[page][row][col+i] = data[(unsigned int)i];
            }
        }
        // Verticacl
        else{
            for (int i = 0; i < data_len; i++){
                notebook[page][row+i][col] = data[(unsigned int)i];
            }
        }

    }

    string Notebook::read(int page, int row, int col, Direction direction, int readLength){

        if(page < MIN_PAGE || row < MIN_PAGE || col < MIN_PAGE || readLength < MIN_PAGE){
            throw runtime_error("page & row & column & num of char to read most be positive!");
        }
        if(col >= LINE_LEN || (direction == Direction::Horizontal && col + readLength > LINE_LEN)){
            throw runtime_error("Some of the lines you want to read do not exist!");
        }
        string ans;
        char curr_char = ' ';
        if (direction == Direction::Horizontal){
            for (int i = 0; i < readLength; i++){
                curr_char = notebook[page][row][col+i];
                if (curr_char == '\0'){
                    ans += '_';
                }
                else{
                    ans += curr_char;  
                }
            }
        }else{
            for (int i = 0; i < readLength; i++){
                curr_char = notebook[page][row+i][col];
                if (curr_char == '\0'){
                    ans += '_';
                }
                else{
                    ans += curr_char;
                }
            }
        }
        return ans;
    }

    void Notebook::erase(int page, int row, int col, Direction direction, int eraselength){

        if(page < MIN_PAGE || row < MIN_PAGE || col < MIN_PAGE || eraselength < MIN_PAGE){
            throw runtime_error("page & row & column & num of char to erse most be positive!");
        }
        if(col >= LINE_LEN || (direction == Direction::Horizontal && col + eraselength > LINE_LEN)){
            throw runtime_error("Some of the lines you want to erase do not exist!");
        }
        // Fill the empty spaces with an under score
        if (direction == Direction::Horizontal){
            for (int i = 0; i < eraselength; i++){
                notebook[page][row][col+i] = '~';
            }
        }else{
            for (int i = 0; i < eraselength; i++){
                notebook[page][row+i][col] = '~';
            }
        }
    }

    void Notebook::show(int page){

        if (page < 0){
            throw runtime_error("The page u chose don't exist!");
        }
        string ans;
        ans = "\n==================\nPage %d" + to_string(page) + ":\n==================\n";
        for (auto row_it = notebook.cbegin()->second.cbegin(); row_it != notebook.cbegin()->second.cend(); ++row_it){
            for (int i = 0; i < LINE_LEN; i++){
                ans+= row_it->second[i];
            }
            ans+= "\n";
        }
        cout<< ans;
    }
}
