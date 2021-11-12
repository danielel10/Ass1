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

        for (int i = 0; i < studio.getTrainer(trainerId)->getCustomers().size(); ++i) {
            vector<int> workout_ids = studio.getTrainer(trainerId)->getCustomers()[i]->order(studio.getWorkoutOptions());
            int id = studio.getTrainer(trainerId)->getCustomers()[i]->getId();
            studio.getTrainer(trainerId)->order(id,workout_ids,studio.getWorkoutOptions());
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
        for (int i = 0; i < studio.getTrainer(trainerId)->getOrders().size(); ++i) {
            int id = studio.getTrainer(trainerId)->getOrders()[i].first;
            string name = studio.getTrainer(trainerId)->getCustomer(id)->getName();
            Workout workout = studio.getTrainer(trainerId)->getOrders()[i].second;
            string workout_name = workout.getName();
            cout << name + " " + "Is " + "Doing " + workout_name + "\n";
        }
    }
}

std::string Order::toString() const {
    string msg = "order" + trainerId;
    if (getStatus() == ActionStatus::COMPLETED) {
        msg = msg + "Completed";
        return msg;
    }
    else {
        msg = msg + "Error: " + getErrorMsg();
        return msg;
    }

}

MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTrainer(src), dstTrainer(dst), id(customerId) {}

void MoveCustomer::act(Studio &studio) {
    if (studio.getTrainer(srcTrainer)->isOpen() || studio.getTrainer(dstTrainer)->isOpen() || srcTrainer > studio.getNumOfTrainers()) {
//    dstTrainer > studio.getNumOfTrainers() || studio.getTrainer(srcTrainer)->getCustomer(id) == nullptr || studio.getTrainer(dstTrainer)->getCapacity() == 0) {
        cout << "Cannot move customer" << endl;
        error("Cannot move customer");
    }
    else {
        Customer *tmp = studio.getTrainer(srcTrainer)->getCustomer(id);
        studio.getTrainer(srcTrainer)->removeCustomer(id);
        studio.getTrainer(srcTrainer)->getOrders().clear();
        for (int i = 0; i < studio.getTrainer(srcTrainer)->getCustomers().size(); ++i) {
            vector<int> workout_ids = studio.getTrainer(srcTrainer)->getCustomers()[i]->order(studio.getWorkoutOptions());
            int id = studio.getTrainer(srcTrainer)->getCustomers()[i]->getId();
            studio.getTrainer(srcTrainer)->order(id,workout_ids,studio.getWorkoutOptions());
        }
        studio.getTrainer(dstTrainer)->addCustomer(tmp);
        vector<int> workout_ids = studio.getTrainer(dstTrainer)->getCustomers().back()->order(studio.getWorkoutOptions());
        int id = studio.getTrainer(dstTrainer)->getCustomers().back()->getId();
        studio.getTrainer(dstTrainer)->order(id,workout_ids,studio.getWorkoutOptions());
        if (studio.getTrainer(srcTrainer)->getCustomers().size() == 0) {
            studio.getTrainer(srcTrainer)->closeTrainer();
        }

        complete();

    }
}

std::string MoveCustomer::toString() const {
    string msg = "move" + srcTrainer + dstTrainer + id;
    if (getStatus() == ActionStatus::COMPLETED) {
        msg = msg + "Completed";
        return msg;
    }
    else {
        msg = msg + "Error: " + getErrorMsg();
        return msg;
    }
}




