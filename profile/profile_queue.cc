/**
 * @file profile_queue.cc
 * @author Omar A Serrano
 * @date 2016-04-03
 */

#include <queue>
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>

#include "queue.hh"

using namespace std;
using namespace chrono;

using high_resolution_time_point = high_resolution_clock::time_point;

inline double getSeconds
  (const high_resolution_time_point &t2,
   const high_resolution_time_point &t1)
{
  return duration_cast<duration<double>>(t2 - t1).count();
}

int main()
{
  int seed = 31;
  auto randEngine = default_random_engine(seed);
  auto uniDist = uniform_int_distribution<>();

  // get times for STL's priority queue
  vector<double> stlValues;
  stlValues.reserve(10000);

  for (int i = 0; i < 10000; ++i)
  {
    priority_queue<int> stlQueue;
    auto t1 = high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j)
    {
      auto r = unitDist(randEngine);
      stlQueue.push_back(r);
    }
    auto t2 = high_resolution_clock::now();
    stlValues.push_back(getSeconds(t2, t1));
  }

  // re-seed the engine
  randEngine.seed(seed);

  // get times for my implementation
  vector<double> osppValues;
  osppValues.reserve(10000);

  for (int i = 0; i < 10000; ++i)
  {
    priority_queue<int> osppQueue;
    auto t1 = high_resolution_clock::now();
    for (int j = 0; j < 10000; ++j)
    {
      auto r = unitDist(randEngine);
      osppQueue.push_back(r);
    }
    auto t2 = high_resolution_clock::now();
    osppValues.push_back(getSeconds(t2, t1));
  }

  // compute min, max, and mean for STL
  auto stlMinMax = minmax_element(stlValues.begin(), stlValues.end());
  auto stlMean = accumulate(stlValues.begin(), stlValues.end()) / stlValues.size();

  // compute min, max, and mean for OSPP
  auto osppMinMax = minmax_element(osppValues.begin(), osppValues.end());
  auto osppMean =
    accumulate(osppValues.begin(), osppValues.end()) / osppValues.size();

  // output for STL
  cout << "--------- STL" << endl;
  cout << "min:  " << (*stlMin.first) << endl;
  cout << "max:  " << (*stlMin.second) << endl;
  cout << "mean: " << stlMean << endl;

  // output for STL
  cout << "--------- OSPP" << endl;
  cout << "min:  " << (*osppMin.first) << endl;
  cout << "max:  " << (*osppMin.second) << endl;
  cout << "mean: " << osppMean << endl;

  return EXIT_SUCCESS;
}
