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

//TODO - check for trainer rule of 5
//std::string Customer::get_workout_type() {
//    return workout_type;
//
//}
//
//void Customer::set_workout_type(std::string type) {
//    workout_type = type;
//}

//Copy constructors
Customer::Customer(const Customer &other):name(other.name), id(other.id) {}

SweatyCustomer::SweatyCustomer(const SweatyCustomer &other): Customer(other) {}

CheapCustomer::CheapCustomer(const CheapCustomer &other): Customer(other) {}

HeavyMuscleCustomer::HeavyMuscleCustomer(const HeavyMuscleCustomer &other): Customer(other) {}

FullBodyCustomer::FullBodyCustomer(const FullBodyCustomer &other): Customer(other) {}

//move constructors
Customer::Customer(Customer &&other):name(other.name),id(other.id) {}

SweatyCustomer::SweatyCustomer(SweatyCustomer &&other): Customer(other) {}

CheapCustomer::CheapCustomer(CheapCustomer &&other): Customer(other) {}

HeavyMuscleCustomer::HeavyMuscleCustomer(HeavyMuscleCustomer &&other): Customer(other) {}

FullBodyCustomer::FullBodyCustomer(FullBodyCustomer &&other): Customer(other) {}





SweatyCustomer::SweatyCustomer(std::string name, int id): Customer(name,id){}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> sweaty_customer_workout;
    for (int i = 0; i < static_cast<int>(workout_options.size()); ++i) {
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
    for (int i = static_cast<int>(workout_options.size()) - 1; i >= 0; i--) {
        if(cheapest_workout > workout_options[i].getPrice()) {
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

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {

    std::vector<Workout> hm_workout;
    for (int i = 0; i < static_cast<int>(workout_options.size()); ++i) {
        if(workout_options[i].getType() == WorkoutType::ANAEROBIC) {
            hm_workout.push_back(workout_options[i]);
        }
    }

    std::vector<std::pair<int,int>> prices_ids;
    for (int i = 0; i < static_cast<int>(hm_workout.size()); ++i) {
        prices_ids.push_back(std::make_pair(hm_workout[i].getPrice(),hm_workout[i].getId()));
    }
    std::sort(prices_ids.begin(),prices_ids.end());

    //sort ids if price is the same
    for (int i = 0; i <static_cast<int>(prices_ids.size()) ; ++i) {
        for (int j = i + 1; j < static_cast<int>(prices_ids.size()) ; ++j) {
            if(prices_ids[i].first == prices_ids[j].first)
                if(prices_ids[i].second > prices_ids[j].second) {
                    std::pair<int,int> tmp = prices_ids[i];
                    prices_ids[i] = prices_ids[j];
                    prices_ids[j] = tmp;
                }
        }
    }


    std::vector<int> final;

    for (int i = static_cast<int>(prices_ids.size()) - 1; i >= 0  ; i--) {

        final.push_back(prices_ids[i].second);
    }

    return final;

}

std::string HeavyMuscleCustomer::toString() const {
    return getName() + ',' + "mcl";
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id): Customer(name,id) {}


std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {

    std::vector<Workout> fbC_workout;//cheapest cardio
    std::vector<Workout> fbM_workout;//most expensive mix
    std::vector<Workout> fbA_workout; //cheapest anaerobic
    for (int i = 0; i < static_cast<int>(workout_options.size()); ++i) {
        if(workout_options[i].getType() == WorkoutType::CARDIO) {
            fbC_workout.push_back(workout_options[i]);
        }
    }

    for (int i = 0; i < static_cast<int>(workout_options.size()); ++i) {
        if(workout_options[i].getType() == WorkoutType::MIXED) {
            fbM_workout.push_back(workout_options[i]);
        }
    }

    for (int i = 0; i < static_cast<int>(workout_options.size()); ++i) {
        if(workout_options[i].getType() == WorkoutType::ANAEROBIC) {
            fbA_workout.push_back(workout_options[i]);
        }
    }

    std::vector<std::pair<int,int>> pricesC_ids;
    for (int i = 0; i < static_cast<int>(fbC_workout.size()); ++i) {
        pricesC_ids.push_back(std::make_pair(fbC_workout[i].getPrice(),fbC_workout[i].getId()));
    }
    std::vector<std::pair<int,int>> pricesM_ids;
    for (int i = 0; i < static_cast<int>(fbM_workout.size()); ++i) {
        pricesM_ids.push_back(std::make_pair(fbM_workout[i].getPrice(),fbM_workout[i].getId()));
    }
    std::vector<std::pair<int,int>> pricesA_ids;
    for (int i = 0; i < static_cast<int>(fbA_workout.size()); ++i) {
        pricesA_ids.push_back(std::make_pair(fbA_workout[i].getPrice(),fbA_workout[i].getId()));
    }
    std::sort(pricesC_ids.begin(),pricesC_ids.end());
    std::sort(pricesM_ids.begin(),pricesM_ids.end());
    std::sort(pricesA_ids.begin(),pricesA_ids.end());

    //sort ids if price is the same
    for (int i = 0; i <static_cast<int>(pricesC_ids.size()) ; ++i) {
        for (int j = i + 1; j < static_cast<int>(pricesC_ids.size()) ; ++j) {
            if(pricesC_ids[i].first == pricesC_ids[j].first)
                if(pricesC_ids[i].second > pricesC_ids[j].second) {
                    std::pair<int,int> tmp = pricesC_ids[i];
                    pricesC_ids[i] = pricesC_ids[j];
                    pricesC_ids[j] = tmp;
                }
        }
    }
    for (int i = 0; i <static_cast<int>(pricesM_ids.size()) ; ++i) {
        for (int j = i + 1; j < static_cast<int>(pricesM_ids.size()) ; ++j) {
            if(pricesM_ids[i].first == pricesM_ids[j].first)
                if(pricesM_ids[i].second > pricesM_ids[j].second) {
                    std::pair<int,int> tmp = pricesM_ids[i];
                    pricesM_ids[i] = pricesM_ids[j];
                    pricesM_ids[j] = tmp;
                }
        }
    }
    for (int i = 0; i <static_cast<int>(pricesA_ids.size()) ; ++i) {
        for (int j = i + 1; j < static_cast<int>(pricesA_ids.size()) ; ++j) {
            if(pricesA_ids[i].first == pricesA_ids[j].first)
                if(pricesA_ids[i].second > pricesA_ids[j].second) {
                    std::pair<int,int> tmp = pricesA_ids[i];
                    pricesA_ids[i] = pricesA_ids[j];
                    pricesA_ids[j] = tmp;
                }
        }
    }


    std::vector<int> final;

    final.push_back(pricesC_ids[0].second);//cheapest cardio
    final.push_back(pricesM_ids[static_cast<int>(pricesM_ids.size()) -1].second);//most expensive min
    final.push_back(pricesA_ids[0].second);//cheapest anerobic

    return final;

}

std::string FullBodyCustomer::toString() const {
    return getName() + ',' + "fbd";
}


Customer::~Customer() {}


