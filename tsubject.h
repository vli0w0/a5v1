#ifndef TSUBJECT_H
#define TSUBJECT_H
#include <vector>


template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class TSubject {
    std::vector<Observer<InfoType, StateType>*> Tobservers;
    StateType tState;
protected:
    void setTState(StateType newS);
public:
    void Tattach(Observer<InfoType, StateType> *o);
    void notifyTObservers();
    virtual InfoType getTInfo() const = 0;
    StateType getTState() const;
};

template <typename InfoType, typename StateType>
void TSubject<InfoType, StateType>::Tattach(Observer<InfoType, StateType> *o) {
    Tobservers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void TSubject<InfoType, StateType>::notifyTObservers() {
    for (auto &ob : Tobservers) ob->notify(*this);
}

template <typename InfoType, typename StateType>
void TSubject<InfoType, StateType>::setTState(StateType newS) { tState = newS; }

template <typename InfoType, typename StateType>
StateType TSubject<InfoType, StateType>::getTState() const { return tState; }
#endif
