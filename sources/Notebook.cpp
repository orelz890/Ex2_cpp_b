#include <iterator>
#include <algorithm>
#include "Notebook.hpp"

using ariel::Direction;
using ariel::Notebook;


void Notebook::fill_with_under_score(int page, int row, int col, Direction direction, int action_len){
    if (direction == Direction::Horizontal){
        // Filling the empty spaces with under score
        for (int i = Notebook::last_row_filled; i <= row; i++){
            // notebook.insert({page, unordered_map<int, char[LINE_LEN]>()});
            for (int j = 0; j <= LINE_LEN; j++){
                // If its a new char cel fill with under score
                char current_char = Notebook::get_char_at(page, i, j);
                // cout << current_char << flush;
                if (current_char == '\0'){

                    Notebook::set_notebook(page, i, j, '_');
                }
            }
        }
    }
    // Verticacl
    else{
        // Filling the empty spaces with under score
        for (int i = Notebook::last_row_filled; i <= row + action_len; i++){
            // notebook.insert({page, unordered_map<int, char[LINE_LEN]>()});
            for (int j = 0; j <= LINE_LEN; j++){
                // If its a new char cel fill with under score
                char current_char = Notebook::get_char_at(page, i, j);
                // cout << current_char << flush;
                if (current_char == '\0'){

                    Notebook::set_notebook(page, i, j, '_');
                }
            }
        }
    }
}

void Notebook::write(int page, int row, int col, Direction direction, string data){

    int data_len = data.length();
    if(page < MIN_PAGE || row < ZERO || col < ZERO){
        throw runtime_error("page & row & column position most be positive!");
    }
    if(col >= LINE_LEN || (direction == Direction::Horizontal && col + data_len >= LINE_LEN)){
        throw runtime_error("Writing in illegal columns!");
    }
    for (int i = 0; i < data_len; i++){
        // int char_value = data[(unsigned int)i];
        if (data[(unsigned int)i] < MIN_CHAR || data[(unsigned int)i] > MAX_CHAR || data[(unsigned int)i] == '~'){
            throw runtime_error("The char u picked is not printable!");
        }
        if (direction == Direction::Horizontal){
            // Char is legal & not under score, means we cant write! 
            if (Notebook::get_char_at(page, row, col+i) >= MIN_CHAR && Notebook::get_char_at(page, row, col+i) <= MAX_CHAR && Notebook::get_char_at(page, row, col+i) != '_'){
                throw runtime_error("Cant over write!");
            }
        }
        // Vertical
        else if(Notebook::get_char_at(page, row+i, col) >= MIN_CHAR && Notebook::get_char_at(page, row+i, col) <= MAX_CHAR && Notebook::get_char_at(page, row+i, col) != '_'){
            throw runtime_error("Cant over write!");
        }
    }
    // Fill the empty spaces with an under score
    fill_with_under_score(page, row, col, direction, data_len);

    if (direction == Direction::Horizontal){
        for (int i = 0; i < data_len; i++){
            // int char_value = data[(unsigned int)i];
            Notebook::set_notebook(page, row, col+i, data[(unsigned int)i]);
        }      
    }
    // Verticacl
    else{
        for (int i = 0; i < data_len; i++){
            // int char_value = data[(unsigned int)i];
            Notebook::set_notebook(page, row+i, col, data[(unsigned int)i]);
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
    fill_with_under_score(page,row,col,direction, readLength);
    string ans;
    for (int i = 0; i < readLength; i++){
        if (direction == Direction::Horizontal){
            // ans += notebook[page][row][col+i];
            ans += Notebook::get_char_at(page,row,col+i);  

        }
        else{
            // ans += notebook[page][row+i][col];
            ans += Notebook::get_char_at(page, row+i, col);
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
    // for (int i = 0; i < eraselength; i++){
    //     // if (direction == Direction::Horizontal && notebook[page][row][col+i] == '~' ||
    //     if (direction == Direction::Horizontal && Notebook::get_char_at(page, row, col+i) == '~' ||
    //             direction == Direction::Vertical && Notebook::get_char_at(page, row+i, col) == '~'){
    //         throw runtime_error("Cant erase the same place twice");
    //     }
    // }
    
    // Fill the empty spaces with an under score
    fill_with_under_score(page, row, col, direction, eraselength);
    
    for (int i = 0; i < eraselength; i++){
        if (direction == Direction::Horizontal){
            // notebook[page][row][col+i] = '~';
            Notebook::set_notebook(page, row, col+i, '~');
        }
        else{
            Notebook::set_notebook(page, row+i, col, '~');
        }
    }
}


void Notebook::show(int page){
    if (page < 0){
        throw runtime_error("The page u chose don't exist!");
    }
    std::cout << "\n==================\nPage " << page << ":" << "\n==================\n";
    for (auto row_it = notebook.cbegin()->second.cbegin(); row_it != notebook.cbegin()->second.cend(); ++row_it){
        for (int i = 0; i < LINE_LEN; i++){
            std::cout << row_it->second[i];
        }
        std:: cout << "\n";
    }

}
