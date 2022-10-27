#include <iostream>
#include <fstream>
#include <map>

int main(int argc, char* argv[]){
    std::string input;

    for(int i=1; i<argc; i++){
        std::string val = argv[i];
        if(val == "-i"){
            if(i == argc-1) throw std::runtime_error("Input not provided");
            input = argv[i+1];
        }else if(val == "-o"){
            if(i == argc-1) throw std::runtime_error("Output not provided");
            std::cout << "Output: " << argv[i+1] << std::endl;
        }
    }

    std::ifstream input_file(input);
    if (!input_file.is_open()) {
        throw std::runtime_error("Cannot open input file");
    }

    std::map<char, int> frequencies = {};
    char byte;
    while (input_file.get(byte)) {
        if(frequencies.find(byte) == frequencies.end()){
            frequencies[byte] = 1;
        }else{
            frequencies[byte]++;
        }
    }

    input_file.close();



    return 0;
}