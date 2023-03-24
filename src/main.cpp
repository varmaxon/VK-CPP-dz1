#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "utils.hpp"


class File_tsv
{
public:
    std::ifstream file;

    File_tsv() {}

    File_tsv(const std::string & fname) {
        file.open(fname);
        if (!file.is_open()) {
            std::cout << "ERROR - File not found" << std::endl;
        }
    }

    File_tsv( const File_tsv & ) = delete;
    File_tsv& operator=( const File_tsv & ) = delete;

    ~File_tsv() {
        file.close();
    }
};


std::vector<std::string> is_adult(File_tsv& file_titles, std::vector<std::string>& movies_id) {
    file_titles.file.seekg(0);
    std::string line, str;
    std::vector<std::string> result_id, vec;
    while (getline(file_titles.file, line)) {
        str = "";
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == '\t') {
                vec.push_back(str);
                str = "";
            }
            else
                str += line[i];
        }
        vec.push_back(str);

        for (unsigned int i = 0; i < movies_id.size(); i++) {
            if ((vec.at(1) == "movie") && (vec.at(4) == "0") && (vec.at(0) == movies_id.at(i))) {
                result_id.push_back(vec.at(0));
                break;
            }
        }
        vec.clear();
    }
    return result_id;
}


void search_movies(File_tsv& file_movies, std::vector<std::string>& movies_id) {
    file_movies.file.seekg(0);
    std::string line, str;
    std::vector<std::string> vec;
    bool flag = false;
    while (getline(file_movies.file, line)) {
        str = "";
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == '\t') {
                vec.push_back(str);
                str = "";
            }
            else
                str += line[i];
        }
        vec.push_back(str);

        for (unsigned int i = 0; i < movies_id.size(); i++) {
            if (((vec.at(4) == "ru") || (vec.at(3) == "RU")) && (vec.at(0) == movies_id.at(i))) {
                std::cout << vec.at(2) << std::endl;
                flag = true;
                break;
            }
        }
        vec.clear();
    }
    if (!flag) { std::cout << "NOT FOUND" << std::endl; }
    return;
}


std::vector<std::string> search_character(File_tsv& file_characters, std::string character) {
    file_characters.file.seekg(0);
    std::string line, str;
    std::vector<std::string> result_id, vec;
    while (getline(file_characters.file, line)) {
        str = "";
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == '\t') {
                vec.push_back(str);
                str = "";
            }
            else
                str += line[i];
        }
        vec.push_back(str);

        if (((vec.at(5).find('"' + character + '"')) != std::string::npos) && (vec.at(3) == "actor")) {
            result_id.push_back(vec.at(0));
        }
        vec.clear();
    }
    return result_id;
}


int main(int argc, char** argv)
{
    print_hello();
    // u_int8_t flag = 0;
    // std::string character = "";
    // std::string file_name = "";
    // for (int i = 1; i < argc; i++) {
    //     file_name += argv[i];
    //     if (flag >= 3) {
    //         character.size() == 0 ? character += argv[i] : character += (" " + file_name);
    //     }
    //     else {
    //         if (file_name == "title.principals.tsv") {
    //             flag++;
    //             File_tsv title_principals("title.principals.tsv");
    //         }
    //         if (file_name == "title.basics.tsv") {
    //             flag++;
    //             File_tsv title_basics("title.basics.tsv");
    //         }
    //         if (file_name == "title.akas.tsv") {
    //             flag++;
    //             File_tsv title_akas("title.akas.tsv");
    //         }
    //     }
    //     file_name.clear();
    // }

    // if ((flag >= 3) && (character.size() > 0)) {
    //     File_tsv title_principals("title.principals.tsv");  // поиск фильмов с данным персонажем
    //     File_tsv title_basics("title.basics.tsv");  // оставим из них фильмы НЕ для взрослых
    //     File_tsv title_akas("title.akas.tsv");  // поиск их русских названий

    //     std::vector<std::string> characters = search_character(title_principals, character);
    //     std::vector<std::string> not_adults = is_adult(title_basics, characters);
    //     search_movies(title_akas, not_adults);
    // }
    // else {
    //     std::cout << "ERROR: Введены не все необходимые данные." << std::endl;
    // }

    
}
