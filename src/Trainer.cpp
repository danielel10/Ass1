#include "../include/Trainer.h"
#include <stdexcept>
#include <utility>

Trainer::Trainer(int t_capacity):capacity(t_capacity){}

int Trainer::getCapacity() const{
    return capacity;
}

//TODO
void Trainer::addCustomer(Customer *customer) {
        customersList.push_back(customer);
        capacity--;
}
//TODO
void Trainer::removeCustomer(int id) {
    customersList.erase(customersList.begin() + id);
    capacity++;

}

Customer *Trainer::getCustomer(int id) {
    for (int i = 0; i < customersList.size(); ++i) {
        if(customersList[i]->getId() == id)
            return customersList[i];
    }
    return nullptr;

}

std::vector<Customer *> &Trainer::getCustomers() {
    return  customersList;

}


void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for (int i = 0; i < workout_ids.size(); ++i) {
        for (int j = 0; j < workout_options.size(); ++j) {
            if(workout_options[j].getId() == workout_ids[i] ) {
                OrderPair trainer_order = std::make_pair(customer_id, workout_options[j]);
                orderList.push_back(trainer_order);
            }
        }


    }
}

int Trainer::getSalary() {
    int salary;
    for (int i = 0; i < orderList.size(); ++i) {
        salary = salary + orderList[i].second.getPrice();
    }
    return salary;

}

bool Trainer::isOpen() {
    return open;

}


std::vector<OrderPair> &Trainer::getOrders() {
    return orderList;
}

void Trainer::openTrainer() {
    open = true;

}

void Trainer::closeTrainer() {
    open = false;

}