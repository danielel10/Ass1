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
//    FullBodyCustomer c1("baranov", 3);
//    c1.order(studio.getWorkoutOptions());

    //here will be the while loop untill msg = "close all"
    // - msg = string that goes in
    //if first word is "action_name" than do the action
    // studio.get_action(msg)
    // we preform the action

    string msg;
    while (msg != "close all") {
        cin >> msg;
        studio.insert_action(msg);
        string action = msg.substr(0,msg.find(" "));
        if(action == "open") {
            stringstream s_stream(msg);
            vector<string> curr_action;
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ' ');
                curr_action.push_back(substr);
            }
            int trainer_id = stoi(curr_action[1]);
            int id;
            vector<Customer *> curr_cus;
            //we create the customers
            for (int i = 2; i < curr_action.size() ; ++i) {
                string name = curr_action[i].substr((curr_action[i].find(","))-1);
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
            OpenTrainer a(trainer_id,curr_cus);
            a.act(studio);
        }
    }

    /*
    studio.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
     */
    return 0;
}
