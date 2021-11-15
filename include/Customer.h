#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Workout.h"

class Customer{
public:
    Customer(std::string c_name, int c_id);
    virtual std::vector<int> order(const std::vector<Workout> &workout_options)=0;
    virtual std::string toString() const = 0;
    void set_workout_type(std::string type);
    std::string getName() const;
    std::string get_workout_type();
    int getId() const;
    //TODO - check if I need to implement that
    Customer(const Customer &other);
    Customer(Customer &&other);
//    Customer& operator=(const Customer &other);
//    Customer& operator=(Customer &&other);
private:
    const std::string name;
    const int id;
    //TODO - refactor trainer
//    std::string workout_type;
};


class SweatyCustomer : public Customer {
public:
	SweatyCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    SweatyCustomer(const SweatyCustomer &other);
    SweatyCustomer(SweatyCustomer &&other);
private:
};


class CheapCustomer : public Customer {
public:
	CheapCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    CheapCustomer(const CheapCustomer &other);
    CheapCustomer(CheapCustomer &&other);
private:
};


class HeavyMuscleCustomer : public Customer {
public:
	HeavyMuscleCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    HeavyMuscleCustomer(const HeavyMuscleCustomer &other);
    HeavyMuscleCustomer(HeavyMuscleCustomer &&other);
private:
};


class FullBodyCustomer : public Customer {
public:
	FullBodyCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    FullBodyCustomer(const FullBodyCustomer &other);
    FullBodyCustomer(FullBodyCustomer &&other);
private:
};


#endif