// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include "train.h"

using namespace std;
using namespace std::chrono;

void fillTrain(Train& train, int n, const string& mode) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(0, 1);

  for (int i = 0; i < n; ++i) {
    if (mode == "off") {
      train.addCar(false);
    }
    else if (mode == "on") {
      train.addCar(true);
    }
    else {
      train.addCar(dist(gen));
    }
  }
}

int main() {
  vector<int> sizes = { 2000, 4000, 6000, 8000, 10000 };

  cout << "mode,n,ops,time_us\n";

  for (const string& mode : { "off", "on", "random" }) {
    for (int n : sizes) {
      Train train;
      fillTrain(train, n, mode);

      auto start = high_resolution_clock::now();
      train.getLength();
      auto end = high_resolution_clock::now();

      long long duration = duration_cast<microseconds>(end - start).count();
      int ops = train.getOpCount();

      cout << mode << "," << n << "," << ops << "," << duration << "\n";
    }
  }

  return 0;
}
