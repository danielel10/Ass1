#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "Customer.h"

enum ActionStatus{
    COMPLETED, ERROR
};

//Forward declaration
class Studio;

class BaseAction{
public:
    BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Studio& studio)=0;
    virtual std::string toString() const=0;
protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
private:
    std::string errorMsg;
    ActionStatus status;
};


class OpenTrainer : public BaseAction {
public:
//    std::string getName();
    OpenTrainer(int id, std::vector<Customer *> &customersList);
    void act(Studio &studio);
    std::string toString() const;
private:
//    std::string name;
	const int trainerId;
	std::vector<Customer *> customers;
};


class Order : public BaseAction {
public:
    Order(int id);
//    std::string getName();
    void act(Studio &studio);
    std::string toString() const;
private:
//    std::string name;
    const int trainerId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
//    std::string getName();
    void act(Studio &studio);
    std::string toString() const;
private:
//    std::string name;
    const int srcTrainer;
    const int dstTrainer;
    const int id;
};


class Close : public BaseAction {
public:
    Close(int id);
//    std::string getName();
    void act(Studio &studio);
    std::string toString() const;
private:
//    std::string name;
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
//    std::string getName();
    void act(Studio &studio);
    std::string toString() const;
//private:
//    std::string name;
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
//    std::string getName();
    void act(Studio &studio);
    std::string toString() const;
//private:
//    std::string name;
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
//    std::string getName();
    void act(Studio &studio);
    std::string toString() const;
private:
//    std::string name;
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
//    std::string getName();
    void act(Studio &studio);
    std::string toString() const;
//private:
//    std::string name;
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
//    std::string getName();
    void act(Studio &studio);
    std::string toString() const;
//private:
//    std::string name;
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
//    std::string getName();
    void act(Studio &studio);
    std::string toString() const;

private:
//    std::string name;

};


#endif