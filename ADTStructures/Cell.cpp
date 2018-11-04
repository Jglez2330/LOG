//
// Created by Joseph Luis González Pastora on 8/10/18.
//

#include "Cell.h"

template<typename T>
Cell<T>::Cell(T Xpos, T Ypos, int objectID):Xpos(Xpos), Ypos(Ypos){
    if (objectID != 1){
        this->ObjectID = objectID;
    }
    this->previous = nullptr;
}


template<typename T>
int Cell<T>::getObjectID() const {
    return ObjectID;
}

template<typename T>
void Cell<T>::setObjectID(int ObjectID) {
    Cell::ObjectID = ObjectID;
}

template<typename T>
T Cell<T>::getXpos() const {
    return Xpos;
}

template<typename T>
void Cell<T>::setXpos(T Xpos) {
    Cell::Xpos = Xpos;
}

template<typename T>
T Cell<T>::getYpos() const {
    return Ypos;
}

template<typename T>
void Cell<T>::setYpos(T Ypos) {
    Cell::Ypos = Ypos;
}

template<typename T>
int Cell<T>::getHeuristic() const {
    return Heuristic;
}

template<typename T>
void Cell<T>::setHeuristic(int Heuristic) {
    Cell::Heuristic = Heuristic;
}

template<typename T>
int Cell<T>::getG() const {
    return g;
}

template<typename T>
void Cell<T>::setG(int g) {
    Cell::g = g;
}

template<typename T>
Cell<T> *Cell<T>::getPrevious() const {
    return previous;
}

template<typename T>
void Cell<T>::setPrevious(Cell<T> *previous) {
    Cell::previous = previous;
}

template<typename T>
int Cell<T>::getF() const {
    return F;
}

template<typename T>
void Cell<T>::setF(int F) {
    Cell::F = F;
}

template<typename T>
int Cell<T>::getHashKey() const {
    return hashKey;
}

template<typename T>
void Cell<T>::setHashKey(int hashKey) {
    Cell::hashKey = hashKey;
}

template<typename T>
bool Cell<T>::operator<(Cell<int> *cellToCompare) {
    return this->getF() < cellToCompare->getF();
}