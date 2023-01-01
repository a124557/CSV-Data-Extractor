//
//  main.cpp
//  CSV Analyzer
//
//  Created by Ali Virani on 2023-01-01.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <dirent.h>

int main(int argc, char * argv[]) {
    //check for correct number of arguments
    if(argc != 3){
    std::cerr <<"Usage: extract_column input_directory column_number" << std::endl;
        return 1;
    }
    
    //Read input directory and column number from the command line
    std::string input_dir = argv[1];
    int column_number = std::stoi(argv[2]);
    
    //Open the input directory
    DIR* dir = opendir(input_dir.c_str());
    if(!dir){
        std::cerr << "Error: could not open the directory" << input_dir << std::endl;
        return 1;
    }
    
    //Loop through all files in directory
    dirent* entry;
    while((entry = readdir(dir)) != NULL) {
        //Check that the file is a CSV file
    std::string file_name = entry->d_name;
        if(file_name.size() < 4 || file_name.substr(file_name.size() - 4) != ".csv"){
            continue;
        }
        
        //Open the input file
        std::string input_file = input_dir + "/" + file_name;
        std::ifstream in(input_file);
        
        //Check if the file was opened sucessfully
        if(!in)  {
            std::cerr << "Error: could not open the file " << input_file << std::endl;
            continue;
        }
        
        //Read in the file line by line
        std::string line;
        while(std::getline(in, line)){
            // Split line into fields using stringstream
            std::stringstream line_stream(line);
            std::string field;
            std::vector<std::string> fields;
            while(std::getline(line_stream, field, ',')){
                fields.push_back(field);;
            }
            
            // Extract the specified column and print it
            if(column_number < fields.size() && fields[column_number].length() > 2){
                std::cout << fields[column_number] << std::endl;
            }
        }
        std::cout << "\n";
    }
    
    closedir(dir);
    return 0;
}
