//
// Created by talpar on 06/11/2021.
//
using namespace std;
#include "../include/Studio.h"
#include "../include/Workout.h"




Studio::Studio(const std::string &configFilePath) {
    //here we define the list of trainers and list of workouts plains
    fstream newfile;
    newfile.open(configFilePath,ios::in);
    if (newfile.is_open()){   //checking whether the file is open
        string tp;
        //parse the first line - number of trainers
        getline(newfile, tp); // first row is "#trainers" dont need it
        while(!tp.empty()){
            //#trainers
            int NumOfTrainers;
            if(tp == "# Number of trainers"){
                getline(newfile, tp); // We get now the data of number of trainers
                sscanf(tp.data(), "%d", &NumOfTrainers); // string to int, because we know what is the second line
                getline(newfile, tp); // We finished with this line and go to the next one
                cout << NumOfTrainers << endl;
            }
            //#capacity

            if(tp == "# Traines") {
//                cout << tp << endl;
                getline(newfile, tp); //We get now the data of trainers capacity
                int n = tp.length();
                char Trainers_Capacitys[n+1];
                strcpy(Trainers_Capacitys, tp.c_str()); //here we change the trainers capacity string into char array
                for(int i = 0; i <n ; i++){
                    int char_to_num = (Trainers_Capacitys[i] - '0');
                    if(char_to_num != -4) {
                        trainers.push_back(new Trainer(char_to_num)); //convert char to int and insert to trainer vectos
                    }
                }
                for (int i = 0; i < trainers.size(); ++i) {
                    cout << trainers[i]->getCapacity() << endl;

                }
                getline(newfile, tp); // We finished with this line and go to the next one
            }
            //#workout
            if(tp == "# Work Options") {
//                cout << tp.length() << endl;
                int Workout_id = 0;
                while(getline(newfile, tp) && !tp.empty()){
                    vector<string> curr_row;
                    stringstream s_stream(tp);
                    while(s_stream.good()) {
                        string substr;
                        getline(s_stream, substr, ',');
                        curr_row.push_back(substr);
                    }
                    string name;
                    string stype;
                    string sprice;
                    for (int i = 0; i < curr_row.size(); i++) {
                        switch(i){
                            case 0:
                                name = curr_row[i];
                                break;
                            case 1:
                                stype = curr_row[i];
                                break;
                            case 2:
                                sprice = curr_row[i];
                                break;
                        }
                    }
                    curr_row.empty();
                    WorkoutType type;

                    if(stype == " Anaerobic"){
                        type = WorkoutType::ANAEROBIC;
                    }
                    else if(stype == " Mixed"){
                        type = WorkoutType::MIXED;
                    }
                    else if(stype == " Cardio"){
                        type = WorkoutType::CARDIO;
                    }
                    int price = stoi(sprice);
                    workout_options.push_back(Workout(Workout_id,name,price,type));
                    Workout_id++;
                }

                for (int i = 0; i < workout_options.size(); ++i) {
                    cout << workout_options[i].getType() << endl;

                }
            }
            //blank line skip
            getline(newfile, tp);

            //exit file when done, AKA we finished with workout types
            if(workout_options.size() > 0) {
                newfile.close(); //close the file object.
                break;
            }

        }

    }



}

void Studio::start() {
    std::cout <<"Studio is now open!" << std::endl;
}

int Studio::getNumOfTrainers() const {
    return  trainers.size();
}

