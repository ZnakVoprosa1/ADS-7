// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
  Car* currentCar = first->next;
  if (!first) return;
  while (currentCar != first) {
    Car* temp = currentCar;
    currentCar = currentCar->next;
    delete temp;
  }
  delete first;
}
void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};

  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* lastCar = first->prev;
    lastCar->next = newCar;
    newCar->prev = lastCar;
    newCar->next = first;
    first->prev = newCar;
  }
}
int Train::getLength() {
  countOp = 0;
  Car* currentCar;
  while (true) {
    currentCar = first;
    int countedCars = 0;
    if (!currentCar->light) {
      currentCar->light = true;
    }
    currentCar = currentCar->next;
    countOp += 2;
    while (!currentCar->light) {
      currentCar = currentCar->next;
      countOp += 2;
      countedCars++;
    }
    currentCar->light = false;
    if (!first->light) {
      return countedCars + 1;
    }
  }
}
int Train::getOpCount() {
  return countOp;
}
