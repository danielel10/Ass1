#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;


class Studio{		
public:
	Studio();
    Studio(const std::string &configFilePath);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    void insert_action(string action);
    string get_action();

private:
    bool open;
    string curr_action;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};

#endif