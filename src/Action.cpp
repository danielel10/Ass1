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
    if(trainerId > studio.getNumOfTrainers() || studio.getTrainer(trainerId)->isOpen()) {
        cout << "Workout session does not exist or is already open." << endl;
        error("Workout session does not exist or is already open.");
    }
    else {
        studio.getTrainer(trainerId)->openTrainer();
        for (int i = 0; i < customers.size(); ++i) {
            studio.getTrainer(trainerId)->addCustomer(customers[i]);
        }
        complete();
    }
}


std::string OpenTrainer::toString() const {
    string msg;
    for (int i = 0; i < customers.size(); ++i) {
        msg = "open " + trainerId + customers[i]->toString() + " ";
    }
    if (getStatus() == ActionStatus::COMPLETED) {
        msg = msg + "Completed";
        return msg;
    }
    else {
        msg = msg + "Error: " + getErrorMsg();
        return msg;
    }
}

Order::Order(int id): trainerId(id){}

void Order::act(Studio &studio) {
    if(trainerId > studio.getNumOfTrainers() || !studio.getTrainer(trainerId)->isOpen()) {
        cout << "Trainer does not exist or is not open" << endl;
        error("Trainer does not exist or is not open");
    }
    else {

    }
}

std::string Order::toString() const {

}




