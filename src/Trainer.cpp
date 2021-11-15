#include "../include/Trainer.h"
#include <stdexcept>
#include <utility>

Trainer::Trainer(int t_capacity):capacity(t_capacity){}

int Trainer::getCapacity() const{
    return capacity;
}

void Trainer::addCustomer(Customer *customer) {
        customersList.push_back(customer);
        capacity--;
}
void Trainer::removeCustomer(int id) {
    for (int i = 0; i < customersList.size(); ++i) {
        if (customersList[i]->getId() == id)
            customersList.erase(customersList.begin() + i);
    }
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

void Trainer::setCurrSalary(int sal) {
    curr_salary = sal;
}

void Trainer::setTotalSalary(int total) {
    salary = total;
}

int Trainer::getTotalSalary() {
    return salary;
}

int Trainer::getCurrSalary() {
    return curr_salary;
}

bool Trainer::isOpen() {
    if(open == true)
        return true;
    else
        return false;

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

std::string Trainer::get_status() {
    if(isOpen())
        return "open";
    else
        return "closed";
}

//destructor
Trainer::~Trainer() {
    for (Customer *c: customersList) {
        delete c;
    }
}

//TODO - create copy constructor for customer;
//copy constructor
//Trainer::Trainer(const Trainer &other) {
//    salary = other.salary;
//    capacity = other.capacity;
//    open = other.open;
//    for (OrderPair p: other.orderList) {
//        orderList.push_back(p);
//    }
//    for (Customer *c: other.customersList) {
//        if(c->get_workout_type() == "swt"){
//            customersList.push_back(new SweatyCustomer(*c)); //check in compile
//        }
//
//    }
//}
//TODO - fix for each loop!
//move constructor
//Trainer::Trainer(Trainer &&other) {
//    salary = other.salary;
//    capacity = other.capacity;
//    open = other.open;
//    for (OrderPair p: other.orderList) {
//        orderList.push_back(p);
//    }
//    for (Customer *c: other.customersList) {
//        customersList.push_back(c); //check in compile
//        c = nullptr;
//    }
//}

//copy assignment
//Trainer& Trainer:: operator=(const Trainer &other) {
//    if(this != &other){
//        clear(); //here we delete ourself before getting the values
//        salary = other.salary;
//        capacity = other.capacity;
//        open = other.open;
//        for (OrderPair p: other.orderList) {
//            orderList.push_back(p);
//        }
//        for (Customer *c: other.customersList) {
//            customersList.push_back(new Customer(*c)); //check in compile
//        }
//    }
//    return *this;
//}
//TODO - check c null pointer!
//Move assignment
//Trainer &Trainer:: operator=(Trainer &&other) {
//    if(this != &other){
//        clear(); //here we delete ourself before getting the values
//        salary = other.salary;
//        this.capacity = other.capacity;
//        open = other.open;
//        for (OrderPair p: other.orderList) {
//            orderList.push_back(p);
//        }
//        for (Customer *c: other.customersList) {
//            customersList.push_back(c); //check in compile
//            c = nullptr;
//        }
//    }
//    return *this;
//}
//TODO - create rulle of 5 to customer
//void Trainer::clear() {
//    salary = 0;
//    capacity = 0;
//    open = false;
//    orderList.clear();
//    for (Customer *c: customersList) {
//        delete c;
//    }
//}