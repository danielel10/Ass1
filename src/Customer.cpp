#include "../include/Customer.h"
#include "../include/Workout.h"
#include <vector>
#include <sstream>
#include <bits/stdc++.h>

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
    return sweaty_customer_workout;
}

std::string SweatyCustomer::toString() const {
    std::string sid = std::to_string(getId());
    return sid + " " + getName();
}

CheapCustomer::CheapCustomer(std::string name, int id): Customer(name,id){}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> cheapest_customer_workout;
    int cheapest_workout = workout_options[0].getPrice();
    int cheapest_id = workout_options[0].getId();
    for (int i = workout_options.size() - 1; i >= 0; i--) {
        if(cheapest_workout.getPrice() < workout_options[i].getPrice()) {
            cheapest_workout = workout_options[i].getPrice();
            cheapest_id = workout_options[i].getId();
        }
    }
    cheapest_customer_workout.push_back(cheapest_id);
    return cheapest_customer_workout;
}

std::string CheapCustomer::toString() const {
    std::string sid = std::to_string(getId());
    return sid + " " + getName();
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): Customer(name,id){}

//TODO

//to work on
std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    struct Workoutprice {
        int Workout;
    };
    std::vector<Workoutprice> hm_workout;
    bool compareWorkoutprice(, Workout i2)
    {
        return (i1.getPrice() > i2.getPrice);
    }
    for (int i = 0; i < workout_options.size(); ++i) {
        if(workout_options[i].getType() == WorkoutType::ANAEROBIC) {
            hm_workout.push_back(workout_options[i]);
        }
    }
    sort(hm_workout.begin(), hm_workout.end(), compareprice);
}


