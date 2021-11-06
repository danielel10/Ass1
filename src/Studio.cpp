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
        //parse the first line - number of trainers
        getline(newfile, tp);
        int NumOfTrainers;
        sscanf(tp.data(), "%d", &NumOfTrainers);
//        cout << NumOfTrainers << endl;
        //parse the second line - trainers capacity
        getline(newfile, tp); //string of the trainers (6,6,4,5) for example
        int n = tp.length();
        char Trainers_Capacitys[n+1];
        strcpy(Trainers_Capacitys, tp.c_str()); //here we change the trainers capacity string into char array
        for(int i = 0; i <n ; i++){
            int char_to_num = (Trainers_Capacitys[i] - '0');
            if(char_to_num != -4) {
                trainers.push_back(new Trainer(char_to_num)); //convert char to int and insert to trainer vectos
            }
        }

        //-------------check for later------------
//        for(int i = 0; i<=NumOfTrainers; i++) {
//                            cout << trainers[i]->getCapacity() << endl;
//        }
        //parse the last line - Workouts
        int id = 0;
        while(getline(newfile, tp)){
            vector<string> curr_row;
            stringstream s_stream(tp);
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ',');
                curr_row.push_back(substr);
            }
            //---------------need to check whats going on--------------
            string name;
            string stype;
            string sprice;
            for (int (i) = 0; (i) < curr_row.size(); ++(i)) {
                if(i==0)
                    name = curr_row[i];
                if(i==1)
                    stype = curr_row[i];
                if(i==2)
                    sprice = curr_row[i];
            }
            WorkoutType type;
            if(stype == "Anerobic"){
                type = WorkoutType::ANAEROBIC;
            }
            if(stype == "Mixed"){
                type = WorkoutType::MIXED;
            }
            if(stype == "Cardio"){
                type = WorkoutType::CARDIO;
            }
            int price = stoi(sprice);
//            Workout test = new Workout(id,name,price,type);
            workout_options.push_back(Workout(id,name,price,type));
            id++;

        }
    }
    newfile.close(); //close the file object.
}

void Studio::start() {
    std::cout <<"Studio is now open!" << std::endl;
}

