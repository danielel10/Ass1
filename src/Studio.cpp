//
// Created by talpar on 06/11/2021.
//
using namespace std;
#include "../include/Studio.h"



Studio::Studio(const std::string &configFilePath) {
    //here we define the list of trainers and list of workouts plains
    fstream newfile;
    newfile.open(configFilePath,ios::in);
    if (newfile.is_open()){   //checking whether the file is open
        string tp;
        getline(newfile, tp);
        int NumOfTrainers;
        sscanf(tp.data(), "%d", &NumOfTrainers);
        getline(newfile, tp); //string of the trainers (6,6,4,5) for example
        cout << NumOfTrainers << endl;
        int n = tp.length();
        char Trainers_Capasitys[n+1];
        strcpy(Trainers_Capasitys, tp.c_str()); //here we change the trainers capasity string into char array
        for(int i = 0; i <n ; i++){
          trainers.push_back(new Trainer(Trainers_Capasitys[i] - '0')); //convert char to int and insert to trainer vectos
            cout << trainers[i]->getCapacity() << endl;
        }

        //while(getline(newfile, tp)){ //read data from file object and put it into string.

    }
    newfile.close(); //close the file object.
}

void Studio::start() {
    std::cout <<"Studio is now open!" << std::endl;
}

