
#include <iostream>
#include <fstream>

int main(){
    std::ifstream f("ExmapleInput (3).txt");

    std::cout <<f.rdbuf();
}