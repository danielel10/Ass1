//
// Created by talpar on 06/11/2021.
//
using namespace std;
#include "../include/Studio.h"

Studio::Studio(const std::string &configFilePath) {
    //here we define the list of trainers and list of workouts plains
    fstream newfilef
    newfile.open(configFilePath,ios::in);
    if (newfile.is_open()){   //checking whether the file is open
        string tp;
        getline(newfile, tp);
        int x;
        sscanf(tp.data(), "%d", &x);
        cout << x << endl;

        //while(getline(newfile, tp)){ //read data from file object and put it into string.

    }
    newfile.close(); //close the file object.
}
