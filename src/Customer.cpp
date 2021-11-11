#include "../include/Customer.h"
#include "../include/Workout.h"
#include <vector>
#include <sstream>
#include <algorithm>

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
    return getName() + ',' + "swt";
}

CheapCustomer::CheapCustomer(std::string name, int id): Customer(name,id){}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> cheapest_customer_workout;
    int cheapest_workout = workout_options[0].getPrice();
    int cheapest_id = workout_options[0].getId();
    for (int i = workout_options.size() - 1; i >= 0; i--) {
        if(cheapest_workout < workout_options[i].getPrice()) {
            cheapest_workout = workout_options[i].getPrice();
            cheapest_id = workout_options[i].getId();
        }
    }
    cheapest_customer_workout.push_back(cheapest_id);
    return cheapest_customer_workout;
}

std::string CheapCustomer::toString() const {
    return getName() + ',' + "chp";
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): Customer(name,id){}

//TODO

//bool compare(const Workout& a, const Workout& b){
//    return a.getPrice() > b.getPrice();
//}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {

    std::vector<Workout> hm_workout;
    for (int i = 0; i < workout_options.size(); ++i) {
        if(workout_options[i].getType() == WorkoutType::ANAEROBIC) {
            hm_workout.push_back(workout_options[i]);
        }
    }

//    std::sort(hm_workout.begin(),hm_workout.end(), compare);

    for (int i = 0; i < hm_workout.size(); ++i) {
        for (int j = i; j < hm_workout.size(); ++j) {
            if (hm_workout[i].getPrice() < hm_workout[j].getPrice()) {
                Workout tmp = hm_workout[i];
                hm_workout[i] = hm_workout[j];
            }

        }

    }



    std::vector<int> ids;
    for (int i = 0; i < hm_workout.size(); ++i) {
        ids.push_back(hm_workout[i].getId());
    }



    return ids;


}

std::string HeavyMuscleCustomer::toString() const {
    return getName() + ',' + "mcl";
}


