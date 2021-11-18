#include "../include/Action.h"
#include "../include/Studio.h"
extern Studio* backup;

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
    customersList.clear();
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
        studio.getTrainer(trainerId)->getOrders().clear();
        for (int i = 0; i < studio.getTrainer(trainerId)->getCustomers().size(); ++i) {
            //each customer get the ids of workouts he get
            vector<int> workout_ids = studio.getTrainer(trainerId)->getCustomers()[i]->order(studio.getWorkoutOptions());
            int id = studio.getTrainer(trainerId)->getCustomers()[i]->getId();
            studio.getTrainer(trainerId)->order(id,workout_ids,studio.getWorkoutOptions());
        }
        int curr_salary = 0;
        for (int i = 0; i < studio.getTrainer(trainerId)->getOrders().size(); ++i) {
            curr_salary = curr_salary + studio.getTrainer(trainerId)->getOrders()[i].second.getPrice();
            int id = studio.getTrainer(trainerId)->getOrders()[i].first; //get the id of the customer
            string name = studio.getTrainer(trainerId)->getCustomer(id)->getName();
            Workout workout = studio.getTrainer(trainerId)->getOrders()[i].second;
            string workout_name = workout.getName();
            cout << name + " " + "Is " + "Doing " + workout_name + "\n";
        }
        studio.getTrainer(trainerId)->setCurrSalary(curr_salary); // we calculated already the others that are in the order vector so we remove them
        complete();
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
    if (!studio.getTrainer(srcTrainer)->isOpen() || !studio.getTrainer(dstTrainer)->isOpen() || srcTrainer > studio.getNumOfTrainers() ||
    dstTrainer > studio.getNumOfTrainers() || studio.getTrainer(srcTrainer)->getCustomer(id) == nullptr || studio.getTrainer(dstTrainer)->getCapacity() == 0) {
        cout << "Cannot move customer" << endl;
        error("Cannot move customer");
    }
    else {
        Customer *tmp = studio.getTrainer(srcTrainer)->getCustomer(id); //we get the customer before we delete it
        for (int i = 0; i < studio.getTrainer(srcTrainer)->getOrders().size(); ++i) {
            if (studio.getTrainer(srcTrainer)->getOrders()[i].first == id)
                studio.getTrainer(srcTrainer)->setCurrSalary(studio.getTrainer(srcTrainer)->getCurrSalary() - studio.getTrainer(srcTrainer)->getOrders()[i].second.getPrice());
        }
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
        for (int i = 0; i < studio.getTrainer(dstTrainer)->getOrders().size(); ++i) {
            if (studio.getTrainer(dstTrainer)->getOrders()[i].first == id) {
                int priceinc = studio.getTrainer(dstTrainer)->getOrders()[i].second.getPrice();
                int currpice = studio.getTrainer(dstTrainer)->getCurrSalary();
                studio.getTrainer(dstTrainer)->setCurrSalary(priceinc + currpice);
            }

        }
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
        studio.getTrainer(trainerId)->setTotalSalary(studio.getTrainer(trainerId)->getTotalSalary() + studio.getTrainer(trainerId)->getCurrSalary());
        studio.getTrainer(trainerId)->setCurrSalary(0);
        int salary = studio.getTrainer(trainerId)->getTotalSalary();
        studio.getTrainer(trainerId)->getOrders().clear();
        studio.getTrainer(trainerId)->getCustomers().clear();
        studio.getTrainer(trainerId)->closeTrainer();
        cout << "Trainer " + to_string((trainerId)) + " closed. " + "Salary " + to_string(salary) + "NIS" + "\n";
        complete();
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

CloseAll::CloseAll() {}

void CloseAll::act(Studio &studio) {
    for (int trainerId = 0; trainerId < studio.getNumOfTrainers(); ++trainerId) {

            studio.getTrainer(trainerId)->setTotalSalary(studio.getTrainer(trainerId)->getTotalSalary() + studio.getTrainer(trainerId)->getCurrSalary());
            studio.getTrainer(trainerId)->setCurrSalary(0);
            int salary = studio.getTrainer(trainerId)->getTotalSalary();
            cout << "Trainer " + to_string((trainerId)) + " closed. " + "Salary " + to_string(salary) + "NIS" + "\n";

    }
    cout << "Studio is now closed!";
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
    complete();
}

std::string PrintWorkoutOptions::toString() const {
    return ("workout_options Completed");
}


PrintTrainerStatus::PrintTrainerStatus(int id):trainerId(id) {}

void PrintTrainerStatus::act(Studio &studio) {
    if (!studio.getTrainer(trainerId)->isOpen()) {
        cout << "Trainer " + to_string(trainerId) + " status: " + studio.getTrainer(trainerId)->get_status() + "\n";

    }
     else {
        string msg = "Trainer " + to_string(trainerId) + " status: " + studio.getTrainer(trainerId)->get_status() + "\n" + "Customers:" + "\n";
        string customer_detials;
        for (int i = 0; i < studio.getTrainer(trainerId)->getCustomers().size(); ++i) {
            customer_detials = customer_detials +
                               to_string(studio.getTrainer(trainerId)->getCustomers()[i]->getId()) + " " +
                               studio.getTrainer(trainerId)->getCustomers()[i]->getName() + "\n";
        }
        string order_det;
        for (int i = 0; i < studio.getTrainer(trainerId)->getOrders().size(); ++i) {
            order_det = order_det + studio.getTrainer(trainerId)->getOrders()[i].second.getName() + " " +
                        to_string(studio.getTrainer(trainerId)->getOrders()[i].second.getPrice()) + "NIS" + " " +
                        to_string(studio.getTrainer(trainerId)->getOrders()[i].first) + "\n";
        }
        int salary = studio.getTrainer(trainerId)->getTotalSalary() + studio.getTrainer(trainerId)->getCurrSalary();
        cout << msg + customer_detials + "Orders:\n" + order_det + "Current Trainer's Salary: " + to_string(salary) + "NIS" + "\n";
        complete();
     }


}

std::string PrintTrainerStatus::toString() const {
    return "status " + to_string(trainerId) + " Completed";
}

PrintActionsLog::PrintActionsLog() {}

void PrintActionsLog::act(Studio &studio) {
    for (int i = 0; i < studio.getActionsLog().size(); ++i) {
        cout << studio.getActionsLog()[i]->toString() + "\n";
    }
     complete();
}

std::string PrintActionsLog::toString() const {
    return "log Completed";
}

BackupStudio::BackupStudio() {}

void BackupStudio::act(Studio &studio) {
    backup = new Studio();
    *backup = studio;
    complete();
}

std::string BackupStudio::toString() const {
    return "backup Completed";
}

RestoreStudio::RestoreStudio() {}

void RestoreStudio::act(Studio &studio) {
    if(backup->get_status()) {
        studio = *backup;
        complete();
        delete backup;
        backup = nullptr;
    }
    else {
        cout << "No backup available";
        error("No backup available");
    }
}

std::string RestoreStudio::toString() const {
    string msg = "restore ";
    if( getStatus() == ActionStatus::COMPLETED) {
        msg = msg + "Completed";
    }
    else {
        msg = msg + "Error: " + getErrorMsg();
    }
    return msg;
}






