#include "../include/Customer.h"
#include "../include/Workout.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <utility>

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


std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {

    std::vector<Workout> hm_workout;
    for (int i = 0; i < workout_options.size(); ++i) {
        if(workout_options[i].getType() == WorkoutType::ANAEROBIC) {
            hm_workout.push_back(workout_options[i]);
        }
    }

    std::vector<std::pair<int,int>> prices_ids;
    for (int i = 0; i < hm_workout.size(); ++i) {
        prices_ids.push_back(std::make_pair(hm_workout[i].getPrice(),hm_workout[i].getId()));
    }
    std::sort(prices_ids.begin(),prices_ids.end());

    //sort ids if price is the same
    for (int i = 0; i <prices_ids.size() ; ++i) {
        for (int j = i + 1; j < prices_ids.size() ; ++j) {
            if(prices_ids[i].first == prices_ids[j].first)
                if(prices_ids[i].second > prices_ids[j].second) {
                    std::pair<int,int> tmp = prices_ids[i];
                    prices_ids[i] = prices_ids[j];
                    prices_ids[j] = tmp;
                }
        }
    }


    std::vector<int> final;

    for (int i = prices_ids.size() - 1; i >= 0  ; i--) {

        final.push_back(prices_ids[i].second);
    }



    return final;


}

std::string HeavyMuscleCustomer::toString() const {
    return getName() + ',' + "mcl";
}


