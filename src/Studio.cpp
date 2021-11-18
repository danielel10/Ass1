
#include "../include/Studio.h"
#include "../include/Workout.h"
#include "../include/Action.h"

using namespace std;

Studio::Studio(): workout_options(){
    open = true;
    trainers.push_back(nullptr);
    actionsLog.push_back(nullptr);
}

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
            }
            //#capacity

            if(tp == "# Traines") {
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
                getline(newfile, tp); // We finished with this line and go to the next one
            }
            //#workout
            if(tp == "# Work Options") {
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

bool Studio::get_status() {
    return open;
}

void Studio::setStatus() {
    open = true;
}

void Studio::close_studio() {
    open = false;
}

void Studio::start() {
    open = true;
    std::cout <<"Studio is now open!" << std::endl;
}

int Studio::getNumOfTrainers() const {
    return  trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    return trainers[tid];
}

vector<Trainer *> &Studio::getTrainers() {
    return trainers;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;

}

void Studio::add_action_to_log(BaseAction *toadd) {
    actionsLog.push_back(toadd);
}


const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return actionsLog;
}

//destructor
Studio::~Studio() {
    for (Trainer *t: trainers) {
        delete t;
        t = nullptr;
    }
    trainers.clear();
    for (BaseAction *b: actionsLog) {
        delete b;
        b = nullptr;
    }
    actionsLog.clear();
    workout_options.clear();
}

//copy constructor
Studio::Studio(const Studio &other):open(other.open), workout_options(other.workout_options) {
    for (Trainer *t: other.trainers) {
        trainers.push_back(new Trainer(*t));
    }
    for (BaseAction *log : other.actionsLog) {
        actionsLog.push_back(log);
    }
}

//move constructor
Studio::Studio(Studio &&other) {
    open = other.open;
    for (Workout w: other.workout_options) {
        workout_options.push_back(w);
    }
    for (Trainer *t: other.trainers) {
        trainers.push_back(new Trainer(*t));
    }
    for (BaseAction *log : other.actionsLog) {
        actionsLog.push_back(log);
    }
}

//copy assignment
Studio &Studio::operator=(const Studio &other) {
    if (this != &other) {
        clear();
        open = other.open;
        for (Workout w: other.workout_options) {
            workout_options.push_back(w);
        }
        for (Trainer *t: other.trainers) {
            trainers.push_back(new Trainer(*t));
        }
        for (BaseAction *log : other.actionsLog) {
            actionsLog.push_back(log);
        }

    }
    return *this;
}

//move assignment
Studio &Studio::operator=(Studio &&other) {
    if(this != &other) {
        clear();
        open = other.open;
        for (Workout w: other.workout_options) {
            workout_options.push_back(w);
        }
        for (Trainer *t: other.trainers) {
            trainers.push_back(new Trainer(*t));
        }
        for (BaseAction *log : other.actionsLog) {
            actionsLog.push_back(log);
        }
        other.trainers.clear();
        other.actionsLog.clear();
    }
    return *this;
}

void Studio::clear() {
    workout_options.clear();
    trainers.clear();
    actionsLog.clear();
}


