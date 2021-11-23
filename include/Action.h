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
    int getids();
    OpenTrainer(std::string none, int id);
    OpenTrainer(int id, std::vector<Customer *> &customersList);
    void act(Studio &studio);
    std::string toString() const;
private:
	const int trainerId;
	std::vector<Customer *> customers;
};


class Order : public BaseAction {
public:
    int getids();
    Order(std::string none, int id);
    Order(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class MoveCustomer : public BaseAction {
public:
    std::vector<int> getids();
    MoveCustomer(std::string none, int src,int dst, int id);
    MoveCustomer(int src, int dst, int customerId);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int srcTrainer;
    const int dstTrainer;
    const int id;
};


class Close : public BaseAction {
public:
    int getids();
    Close(std::string none, int id);
    Close();
    Close(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    void act(Studio &studio);
    std::string toString() const;
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions(std::string none);
    PrintWorkoutOptions();
    void act(Studio &studio);
    std::string toString() const;
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(std::string none);
    PrintTrainerStatus(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog(std::string none);
    PrintActionsLog();
    void act(Studio &studio);
    std::string toString() const;
};


class BackupStudio : public BaseAction {
public:
    BackupStudio(std::string none);
    BackupStudio();
    void act(Studio &studio);
    std::string toString() const;
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio(std::string none);
    RestoreStudio();
    void act(Studio &studio);
    std::string toString() const;

private:

};


#endif