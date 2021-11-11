#include "../include/Studio.h"
#include <iostream>
#include <algorithm>

using namespace std;

Studio* backup = nullptr;



int main(int argc, char** argv){
//    if(argc!=2){
//        std::cout << "usage: studio <config_path>" << std::endl;
//        return 0;
//    }
    string configurationFile = argv[1];
    Studio studio(configurationFile);
    HeavyMuscleCustomer c1("baranov", 3);
    c1.order(studio.getWorkoutOptions());

    /*
    studio.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
     */
    return 0;
}
