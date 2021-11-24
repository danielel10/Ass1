#include "../include/Studio.h"
#include <iostream>
#include <algorithm>

using namespace std;

Studio *backup = nullptr;



int main(int argc, char** argv){
    if(argc!=2){
        std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
//    Studio studio(configurationFile);
    Studio *studio = new Studio(configurationFile);
    studio->start();
    //here will be the while loop untill msg = "close all"
    // - msg = string that goes in
    //if first word is "action_name" than do the action
    // studio.get_action(msg)
    // we preform the action

    // while we dont have close all action we dont close the program
    string msg;
    int id = 0;
    while (studio->get_status()) {
        getline(cin,msg); //here we get the action and the details if needed
        string action = msg.substr(0,msg.find(" ")); // get the first word of the action to know what we need to do.
        //"open trainer" action
        if(action == "open") {
            // read the action
            stringstream s_stream(msg);
            vector<string> curr_action;
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ' ');
                curr_action.push_back(substr);
            }
            int trainer_id = stoi(curr_action[1]);
            vector<Customer *> curr_cus;
            //we create the customers
            for (int i = 2; i < static_cast<int>(curr_action.size()) ; ++i) {
                string name = curr_action[i].substr(0, curr_action[i].find(","));
                string workout = curr_action[i].substr((curr_action[i].find(","))+1);
                if (workout == "swt"){
                    SweatyCustomer *c = new SweatyCustomer(name,id);
                    curr_cus.push_back(c);
                }
                if (workout == "chp"){
                    CheapCustomer *c = new CheapCustomer(name,id);
                    curr_cus.push_back(c);
                }
                if (workout == "mcl"){
                    HeavyMuscleCustomer *c = new HeavyMuscleCustomer(name,id);
                    curr_cus.push_back(c);
                }
                if (workout == "fbd"){
                    FullBodyCustomer *c = new FullBodyCustomer(name,id);
                    curr_cus.push_back(c);
                }
                id ++;
            }
                //create the open order constructor
                OpenTrainer *open_trainer = new OpenTrainer(trainer_id,curr_cus);
                //run the action
                open_trainer->act(*studio);
                studio->add_action_to_log(open_trainer);

        }
        //"order" action
        else if (action == "order") {
            //get the trainer id from the string
            stringstream s_stream(msg);
            vector<string> curr_action;
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ' ');
                curr_action.push_back(substr);
            }
            int trainer_id = stoi(curr_action[1]);
            Order *ordernew = new Order(trainer_id);
            ordernew->act(*studio);
            studio->add_action_to_log(ordernew);
        }
        //"move" action
        else if (action == "move") {
            //get the trainer details and customer from the string
            stringstream s_stream(msg);
            vector<string> curr_action;
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ' ');
                curr_action.push_back(substr);
            }
            int trainer_src = stoi(curr_action[1]);
            int trainer_dst = stoi(curr_action[2]);
            int customer_id = stoi(curr_action[3]);
            MoveCustomer *moveCustomer = new MoveCustomer(trainer_src,trainer_dst,customer_id);
            moveCustomer->act(*studio);
            studio->add_action_to_log(moveCustomer);
        }
        else if (action == "close") {
            //get the trainer details and customer from the string
            stringstream s_stream(msg);
            vector<string> curr_action;
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ' ');
                curr_action.push_back(substr);
            }
            int trainer_id = stoi(curr_action[1]);
            Close *close = new Close(trainer_id);
            close->act(*studio);
            studio->add_action_to_log(close);
        }
        else if (action == "closeall") {
            CloseAll *close = new CloseAll();
            close->act(*studio);
            studio->close_studio();
            delete close;
        }
        else if (action == "workout_options") {
            PrintWorkoutOptions *workoutOptions = new PrintWorkoutOptions();
            workoutOptions->act(*studio);
            studio->add_action_to_log(workoutOptions);
        }
        else if (action == "status") {
            //get the trainer details and customer from the string
            stringstream s_stream(msg);
            vector<string> curr_action;
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ' ');
                curr_action.push_back(substr);
            }
            int trainer_id = stoi(curr_action[1]);
            PrintTrainerStatus *status = new PrintTrainerStatus(trainer_id);
            status->act(*studio);
            studio->add_action_to_log(status);
        }
        else if (action == "log") {
            PrintActionsLog *log = new PrintActionsLog();
            log->act(*studio);
            studio->add_action_to_log(log);
        }
        else if (action == "backup") {
            BackupStudio *back = new BackupStudio();
            studio->add_action_to_log(back);
            back->act(*studio);
        }
        else if (action == "restore") {
            RestoreStudio *r = new RestoreStudio();
            r->act(*studio);
            delete r;
        }

    }

    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    delete studio;
    studio = nullptr;



//    for(int i=0;i<argc;i++)
//        delete argv[i];
//    delete[] argv;
//    configurationFile = nullptr;
//    delete[] argv;
//    argv = nullptr;
    return 0;
}
