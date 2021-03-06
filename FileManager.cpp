//
// Created by Ben Cradick on 2019-03-11.
//

#include "FileManager.h"

void errorCheckHelper();
bool isEmpty(std::fstream&);
FileManager::FileManager(int argc, char **argv)
{
    if(argc < 2)
    {
        fileName = "out.sp19";
        inputFile.open(fileName, std::fstream::ate | std::fstream::out | std::fstream::in | std::fstream::app); // ate = At The End, meaning write to end of the file.


        std::string keyBuffer;
        std::cin >> keyBuffer;
        inputFile << keyBuffer;

        inputFile.close();
        inputFile.open(fileName, std::fstream::in);
        errorCheckHelper();
        tempFile = true;
        if(isEmpty(inputFile)){
            std::cerr << "Empty input stream" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fileName = argv[1];
        inputFileName = fileName + ".sp19";
        inputFile.open(inputFileName);
        errorCheckHelper();
        if(isEmpty(inputFile)){
            std::cerr << "Empty input file: " + inputFileName << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}


void errorCheckHelper()
{
    if(errno != 0)
    {
        perror("Failed to read input: ");
        exit(EXIT_FAILURE);
    }
}
FileManager::~FileManager() {
    if(tempFile){
        inputFile.close();
        std::remove(inputFileName.c_str());
    }
}
bool isEmpty(std::fstream& file){
    return file.peek() == std::fstream::traits_type::eof();
}
