#include "/home/talpar/CLionProjects/Ass1/include/Studio.h"
#include <iostream>

using namespace std;

Studio* backup = nullptr;

int main(int argc, char** argv){
    std::cout <<argv[1]<< std::endl;
    if(argc!=2){
        std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
    Studio studio(configurationFile);
    /*
    studio.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
     */
    return 0;
}