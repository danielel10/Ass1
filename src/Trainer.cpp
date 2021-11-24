#include "../include/Trainer.h"
#include <stdexcept>
#include <utility>

Trainer::Trainer(int t_capacity):capacity(t_capacity),open(false),salary(0),curr_salary(0){}

int Trainer::getCapacity() const{
    return capacity;
}

void Trainer::addCustomer(Customer *customer) {
    if(capacity > 0) {
        customersList.push_back(customer);
        capacity--;
    }
    else {
        delete customer;
        customer = nullptr;
    }
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
    if(open)
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
    for (int i = 0; i < customersList.size(); ++i) {
        delete customersList[i];
        customersList[i] = nullptr;
    }
    customersList.clear();
}

//copy constructor
Trainer::Trainer(const Trainer &other):salary(other.salary), capacity(other.capacity), open(other.open),curr_salary(other.curr_salary) {
    for (OrderPair p: other.orderList) {
        orderList.push_back(p);
    }
    for (Customer *c: other.customersList) {
        if (c->toString().back() =='t' )
            customersList.push_back(new SweatyCustomer(c->getName(),c->getId()));
        if (c->toString().back() =='p' )
            customersList.push_back(new CheapCustomer(c->getName(),c->getId()));
        if (c->toString().back() =='l' )
            customersList.push_back(new HeavyMuscleCustomer(c->getName(),c->getId()));
        if (c->toString().back() =='d' )
            customersList.push_back(new FullBodyCustomer(c->getName(),c->getId()));

    }
}
//move constructor
Trainer::Trainer(Trainer &&other) {
    salary = other.salary;
    capacity = other.capacity;
    open = other.open;
    curr_salary = other.curr_salary;
    for (OrderPair p: other.orderList) {
        orderList.push_back(p);
    }
    for (Customer *c: other.customersList) {
        customersList.push_back(c);
    }
    other.customersList.clear();

}

//copy assignment
Trainer& Trainer:: operator=(const Trainer &other) {
    if(this != &other){
        clear(); //here we delete ourselves before getting the values
        salary = other.salary;
        capacity = other.capacity;
        open = other.open;
        for (OrderPair p: other.orderList) {
            orderList.push_back(p);
        }
        for (Customer *c: other.customersList) {
            customersList.push_back(c);
        }
    }
    return *this;
}
//TODO - check c null pointer!
//Move assignment
Trainer &Trainer:: operator=(Trainer &&other) {
    if(this != &other){
        clear(); //here we delete ourself before getting the values
        salary = other.salary;
        capacity = other.capacity;
        open = other.open;
        for (OrderPair p: other.orderList) {
            orderList.push_back(p);
        }
        for (Customer *c: other.customersList) {
            customersList.push_back(c);
        }
        other.customersList.clear();
    }
    return *this;
}
//TODO - create rulle of 5 to customer
void Trainer::clear() {
    salary = 0;
    curr_salary = 0;
    capacity = 0;
    open = false;
    orderList.clear();
    customersList.clear();
}

