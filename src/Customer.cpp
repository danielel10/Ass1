#include "../include/Customer.h"
#include <vector>
#include <sstream>

Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id){}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

SweatyCustomer::SweatyCustomer(std::string name, int id): Customer(name,id){}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> sweaty_customer_workout;
    for (int i = 0; i < workout_options.size(); ++i) {
        if(workout_options[i].getType() == WorkoutType::CARDIO) {
            sweaty_customer_workout.push_back(workout_options[i].getId());
        }
    }
}

std::string SweatyCustomer::toString() const {
    std::string sid = std::to_string(getId());
    return sid + " " + getName();
}

