#include "Direction.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "Notebook.hpp"

using ariel::Direction;

namespace ariel{
    
    void Notebook::write(int page, int row, int col, Direction direction, const string & data){
        int data_len = data.length();
        if(page < MIN_POSITION || row < MIN_POSITION || col < MIN_POSITION){throw runtime_error("page & row & column position most be positive!");}
        if(col > LINE_LEN || (direction == Direction::Horizontal && col + data_len > LINE_LEN)){throw runtime_error("Writing in illegal columns!");}
        for (size_t i = 0; i < data_len -1; i++){
            if (data[i] < MIN_CHAR || data[i] > MAX_CHAR){
                throw runtime_error("The char u picked is not printable!");
            }
        }
        if (direction == Direction::Horizontal){   
            // Filling the empty spaces with under score
            for (int i = last_row_filled; i <= row; i++){
                // notebook.insert({page, unordered_map<int, char[LINE_LEN]>()});
                for (int j = 0; j <= LINE_LEN; j++){
                    // If its a new char cel fill with under score
                    if (notebook[page][i][j] < MIN_CHAR && notebook[page][i][j] > MAX_CHAR){
                        notebook[page][i][j] = '_';
                    }
                }
            }
        }
        // Verticacl
        else{
            // Filling the empty spaces with under score
            for (int i = last_row_filled; i <= row + data_len; i++){
                // notebook.insert({page, unordered_map<int, char[LINE_LEN]>()});
                for (int j = 0; j <= LINE_LEN; j++){
                    // If its a new char cel fill with under score
                    if (notebook[page][i][j] < MIN_CHAR && notebook[page][i][j] > MAX_CHAR){
                        notebook[page][i][j] = '_';
                    }
                }
            }
        }

        
    }
    string Notebook::read(int page, int row, int col, Direction direction, int readLength){
        if(page < MIN_POSITION || row < MIN_POSITION || col < MIN_POSITION || readLength < MIN_POSITION){throw runtime_error("page & row & column & num of char to read most be positive!");}
        if(col > LINE_LEN || (direction == Direction::Horizontal && col + readLength > LINE_LEN)){throw runtime_error("Some of the lines you want to read do not exist!");}
        return "";
    }
    void Notebook::erase(int page, int row, int col, Direction direction, int eraselength){
        if(page < MIN_POSITION || row < MIN_POSITION || col < MIN_POSITION || eraselength < MIN_POSITION){throw runtime_error("page & row & column & num of char to erse most be positive!");}
        if(col > LINE_LEN || (direction == Direction::Horizontal && col + eraselength > LINE_LEN)){throw runtime_error("Some of the lines you want to erase do not exist!");}
    }
    void Notebook::show(int page){
        for (auto page_it = notebook.cbegin(); page_it != notebook.cend(); ++page_it){
            std::cout << "\n==================\nPage " << page_it->first << ":" << "\n==================\n";
            for (auto row_it = page_it->second.cbegin(); row_it != page_it->second.cend(); ++row_it){
                for (int i = 0; i < LINE_LEN; i++){
                    std::cout << row_it->second[i];
                }
                std:: cout << "\n";
            }
        }     
    }


}