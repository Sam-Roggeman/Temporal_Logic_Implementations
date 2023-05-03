//
// Created by Sam Roggeman on 3/05/2023.
//
#include "Observer.h"
#ifndef CODE_SUBJECT_H
#define CODE_SUBJECT_H



class Subject {
    Observer* observer;
public:
    explicit Subject(Observer* observer) : observer(observer){};
    explicit Subject(){};
    void notify(){
        if (observer){
            observer->notify();
        }
    }
};


#endif //CODE_SUBJECT_H
