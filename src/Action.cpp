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

//here we just initail the action and later check if it is legal
OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id) {
    for (int i = 0; i < customersList.size(); ++i) {
        customers.push_back(customersList[i]);
    }
}

//this is where we preform the action
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
            //each customer get the ids of workouts he get
            vector<int> workout_ids = studio.getTrainer(trainerId)->getCustomers()[i]->order(studio.getWorkoutOptions());
            int id = studio.getTrainer(trainerId)->getCustomers()[i]->getId();
            studio.getTrainer(trainerId)->order(id,workout_ids,studio.getWorkoutOptions());
        }
        complete();
    }
}


std::string OpenTrainer::toString() const {
    string msg = "open " + to_string(trainerId);
    for (int i = 0; i < customers.size(); ++i) {
        string tmp = customers[i]->toString();
        msg = msg + " " + tmp;
    }
    if (getStatus() == ActionStatus::COMPLETED) {
        msg = msg + " Completed";
        return msg;
    }
    else {
        msg = msg + " Error: " + getErrorMsg();
        return msg;
    }
}
//here we just initail the action and later check if it is legal
Order::Order(int id): trainerId(id){}

//this is where we preform the action
void Order::act(Studio &studio) {
    if(trainerId > studio.getNumOfTrainers() || !studio.getTrainer(trainerId)->isOpen()) {
        cout << "Trainer does not exist or is not open" << endl;
        error("Trainer does not exist or is not open");
    }
    else {
        for (int i = 0; i < studio.getTrainer(trainerId)->getOrders().size(); ++i) {
            int id = studio.getTrainer(trainerId)->getOrders()[i].first; //get the id of the customer
            string name = studio.getTrainer(trainerId)->getCustomer(id)->getName();
            Workout workout = studio.getTrainer(trainerId)->getOrders()[i].second;
            string workout_name = workout.getName();
            cout << name + " " + "Is " + "Doing " + workout_name + "\n";
        }
    }
}

std::string Order::toString() const {
    string msg = "order " + to_string(trainerId);
    if (getStatus() == ActionStatus::COMPLETED) {
        msg = msg + " Completed";
        return msg;
    }
    else {
        msg = msg + " Error: " + getErrorMsg();
        return msg;
    }

}

//here we just initail the action and later check if it is legal
MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTrainer(src), dstTrainer(dst), id(customerId) {}

//this is where we preform the action
void MoveCustomer::act(Studio &studio) {
    //we check if the move is legal
    if (studio.getTrainer(srcTrainer)->isOpen() || studio.getTrainer(dstTrainer)->isOpen() || srcTrainer > studio.getNumOfTrainers() ||
    dstTrainer > studio.getNumOfTrainers() || studio.getTrainer(srcTrainer)->getCustomer(id) == nullptr || studio.getTrainer(dstTrainer)->getCapacity() == 0) {
        cout << "Cannot move customer" << endl;
        error("Cannot move customer");
    }
    else {
        Customer *tmp = studio.getTrainer(srcTrainer)->getCustomer(id); //we get the customer before we delete it
        studio.getTrainer(srcTrainer)->removeCustomer(id);
        studio.getTrainer(srcTrainer)->getOrders().clear(); // we redo the order list for src_trainer
        for (int i = 0; i < studio.getTrainer(srcTrainer)->getCustomers().size(); ++i) {
            vector<int> workout_ids = studio.getTrainer(srcTrainer)->getCustomers()[i]->order(studio.getWorkoutOptions());
            int id = studio.getTrainer(srcTrainer)->getCustomers()[i]->getId();
            studio.getTrainer(srcTrainer)->order(id,workout_ids,studio.getWorkoutOptions());
        }
        //here we add the trainer and add it to the order of dest_trainer.
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
    string msg = "move " + to_string(srcTrainer) + " " + to_string(dstTrainer) + " " + to_string(id);
    if (getStatus() == ActionStatus::COMPLETED) {
        msg = msg + " Completed";
        return msg;
    }
    else {
        msg = msg + " Error: " + getErrorMsg();
        return msg;
    }
}

Close::Close(int id): trainerId(id) {}

void Close::act(Studio &studio) {
    if (trainerId > studio.getNumOfTrainers() || !studio.getTrainer(trainerId)->isOpen()) {
        cout << "Trainer does not exist or is not open" << endl;
        error("Trainer does not exist or is not open");
    }
    else {
        int salary = studio.getTrainer(trainerId)->getSalary();
        int size = studio.getTrainer(trainerId)->getCustomers().size();
        vector<int> customers_ids;
        for (int i = 0; i < size; ++i) {
            customers_ids.push_back(studio.getTrainer(trainerId)->getCustomer(i)->getId());
        }
        for (int i = 0; i < customers_ids.size(); ++i) {
            studio.getTrainer(trainerId)->removeCustomer(i);
        }
        studio.getTrainer(trainerId)->getOrders().clear();
        studio.getTrainer(trainerId)->closeTrainer();
        cout << "Trainer " + to_string((trainerId)) + " closed. " + "Salary " + to_string(studio.getTrainer(salary)->getSalary());
    }

}

std::string Close::toString() const {
    string msg = "close " + to_string(trainerId);
    if (getStatus() == ActionStatus::COMPLETED) {
        msg = msg + " Completed";
        return msg;
    }
    else {
        msg = msg + " Error: " + getErrorMsg();
        return msg;
    }
}

//TODO - need to debug the error
CloseAll::CloseAll() {}

void CloseAll::act(Studio &studio) {
    for (int trainerId = 0; trainerId < studio.getNumOfTrainers(); ++trainerId) {
        if(studio.getTrainer(trainerId)->isOpen()) {
            int salary = studio.getTrainer(trainerId)->getSalary();
//            int size = studio.getTrainer(trainerId)->getCustomers().size();
//            vector<int> customers_ids;
//            for (int i = 0; i < size; ++i) {
//                customers_ids.push_back(studio.getTrainer(trainerId)->getCustomer(i)->getId());
//            }
//            for (int i = 0; i < customers_ids.size(); ++i) {
//                studio.getTrainer(trainerId)->removeCustomer(i);
//            }
//            studio.getTrainer(trainerId)->getOrders().clear();
//            studio.getTrainer(trainerId)->closeTrainer();
            cout << "Trainer " + to_string((trainerId)) + " closed. " + "Salary " + to_string(salary) + "NIS";
        }
    }
    studio.close_studio();


}

std::string CloseAll::toString() const {
    return "closeall";
}

PrintWorkoutOptions::PrintWorkoutOptions() {}

void PrintWorkoutOptions::act(Studio &studio) {
    for (int i = 0; i < studio.getWorkoutOptions().size(); ++i) {
        cout << studio.getWorkoutOptions()[i].getName() + ", " + to_string(studio.getWorkoutOptions()[i].getType()) +  ", "
        + to_string(studio.getWorkoutOptions()[i].getPrice()) + "\n";
    }
}

std::string PrintWorkoutOptions::toString() const {
    return "workout_options";
}



