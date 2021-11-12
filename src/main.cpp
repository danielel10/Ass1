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
    studio.start();
    //here will be the while loop untill msg = "close all"
    // - msg = string that goes in
    //if first word is "action_name" than do the action
    // studio.get_action(msg)
    // we preform the action

    // while we dont have close all action we dont close the program
    string msg;
    while (msg != "close all") {
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
            int id;
            vector<Customer *> curr_cus;
            //we create the customers
            for (int i = 2; i < curr_action.size() ; ++i) {
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
            open_trainer->act(studio);
            studio.add_action_to_log(open_trainer);
        }
        //"order" action
        else if (action == "order") {
            stringstream s_stream(msg);
            vector<string> curr_action;
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ' ');
                curr_action.push_back(substr);
            }
            int trainer_id = stoi(curr_action[1]);
            Order *ordernew = new Order(trainer_id);
            ordernew->act(studio);
            studio.add_action_to_log(ordernew);

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
