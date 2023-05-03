//
// Created by Sam Roggeman on 3/05/2023.
//

#ifndef CODE_MUTEX_H
#define CODE_MUTEX_H
#include <iostream>
#include <vector>
#include <future>
#include "Utils/Observer.h"
#include "Utils/AbstractProcess.h"


class ExampleProcess1 : public AbstractProcess{
public:
    explicit ExampleProcess1() : AbstractProcess(1) {

    }

    void execute(std::vector<int> &programma_variabelen) override {
        AbstractProcess::execute(programma_variabelen);
    }



    void nextState() override {
        this->setState(this->getState()+1) ;
    }

    explicit ExampleProcess1(int id, Observer* observer) : AbstractProcess(id, observer) {}

    virtual bool isDone() override{
        return this->getState() == 2;
    }

    void doStep(std::vector<int>& programma_variabelen) override {

        int &x = programma_variabelen[0];
        if (getState() == 0){
            if (x > 0) {
                x = x - 1;
                nextState();
            }
        }
        else if (getState() == 1){
            x += 1;
            nextState();
        }
        this->notify();
    }
};



class MutExModel : public Observer{
    std::vector<int> programma_variabelen = {1};
    ExampleProcess1 P1 {1,this};
    ExampleProcess1 P2 {2,this};
public:
    MutExModel() {
    }
    bool isDone(){
        return P1.isDone() && P2.isDone();
    }
    std::string getState() {
        std::string state = "<";
        bool first = true;
        std::vector<AbstractProcess *> processes = {&P1, &P2};
        for (AbstractProcess *process: processes) {
            if (!first) {
                state += ",";
            }
            first = false;
            state += "m_" + std::to_string(process->getId());
            state += std::string(process->getState(), '\'');
        }
        state += ";";

        for (const auto& prog_var: programma_variabelen) {
            state+=std::to_string(prog_var);
        }
        state += ">";
        return state;
    }
    void notify() override{
        std::cout <<this->getState();
    }
    void execute(){
        auto p1 = std::async(std::launch::async, [this]() {
            P1.execute(programma_variabelen);
        });
        auto p2 = std::async(std::launch::async, [this]() {
            P2.execute(programma_variabelen);
        });
        p1.wait();
        p2.wait();


    }
};

void mutEx1(){
    MutExModel mutExModel {};
    mutExModel.notify();
    mutExModel.execute();
}

#endif //CODE_MUTEX_H
