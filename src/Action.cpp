#include "../include/Action.h"
#include "../include/Studio.h"

BaseAction::BaseAction() {

}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(std::string errorMsg) {
    this->errorMsg = errorMsg;
    status = ActionStatus::ERROR;

}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}


OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id) {
    for (int i = 0; i < customersList.size(); ++i) {
        customers.push_back(customersList[i]);
    }
}

void OpenTrainer::act(Studio &studio) {
    if(trainerId > studio.getNumOfTrainers() | studio.getTrainer(trainerId)->isOpen()) {
        error("Workout session does not exist or is already open.");
    }
    else {
        complete();
    }

}

//TODO

std::string OpenTrainer::toString() const {
    if (ActionStatus::COMPLETED) {
        string msg;
        for (int i = 0; i < customers.size(); ++i) {

        }
    }
}





