//
// Created by Sam Roggeman on 3/05/2023.
//

#ifndef CODE_ABSTRACTPROCESS_H
#define CODE_ABSTRACTPROCESS_H


#include "Subject.h"
#include <vector>

class AbstractProcess : public Subject {
    int id;
    int state = 0;
public:
    explicit AbstractProcess(int id) : id(id) {}
    explicit AbstractProcess(int id, Observer* observer) : Subject(observer), id(id) {}
    virtual void execute(std::vector<int>& programma_variabelen){
        while (! isDone()){
            doStep(programma_variabelen);
        }
    }

    int getState() const {
        return state;
    }
    virtual void nextState() = 0;
    virtual bool isDone() = 0;
    virtual void doStep(std::vector<int>& programma_variabelen) = 0;

    int getId() {
        return id;
    }

    void setState(int i) {
        this->state = i;
//        this->notify();
    }
};



#endif //CODE_ABSTRACTPROCESS_H
