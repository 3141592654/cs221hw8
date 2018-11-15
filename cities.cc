/*
 * Implementation of cities.hh.
 */

#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "cities.hh"

void Cities::add_to_city_list_(Cities::coord_t c) {
  city_list_.push_back(c);
}

Cities Cities::reorder(const Cities::permutation_t& ordering) const {
  Cities retval;
  // decided to allow including a city twice, as well as not including all
  // cities.
  for (auto o : ordering) {
    // but a city that is not in the list, that shouldn't be possible.
    // (though one could argue it should just do nothing and print a warning.)
    assert(o <= city_list_.size()-1);
    retval.add_to_city_list_(city_list_[o]);
  }
  return retval;
}

double Cities::own_path_distance() {
  double retval = 0;
  uint i;
  for (i = 0; i < city_list_.size()-1; i++) {
    retval += sqrt(pow(city_list_[i].first - city_list_[i+1].first,2) +
                 pow(city_list_[i].second - city_list_[i+1].second,2));
  }
  retval += sqrt(pow(city_list_[i].first - city_list_[0].first,2) +
               pow(city_list_[i].second - city_list_[0].second,2));
  return retval;
}

double Cities::total_path_distance(const Cities::permutation_t& ordering) const {
    return reorder(ordering).own_path_distance();
}

std::istream& operator>>(std::istream& is, Cities& cs) {
  int p1;
  int p2;
  while(true) {
    if (is >> p1) {
      if (is >> p2) {
        Cities::coord_t newcoord = Cities::coord_t(p1,p2);
        cs.add_to_city_list_(newcoord);
      } else {
        break;
      }
    } else {
      break;
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream &os, Cities& cs) {
  for (auto p : cs.city_list_) {
    os << p.first << "," << p.second << " ";
  }
  // debated putting an end line here. ultimately decided against it.
  // since the customer might be used to things like putting << std::endl
  // after everything.
  return os;
}

//REPLACE WITH STL???
Cities::permutation_t random_permutation(unsigned len) {
  Cities::permutation_t retval(0);
  Cities::permutation_t temp(0);
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine gen (seed);
  for (unsigned i = 0; i <len; i++) {
    temp.push_back(i);
  }
  for (int i = len-1; i > 0; i--) {
    // pop a random element from all possible values and push it onto retval
    std::uniform_int_distribution<int> dist(0,i);
    int k = dist(gen);
    unsigned int val = temp[k];
    temp.erase(temp.begin()+k);
    retval.push_back(val);
  }
  retval.push_back(temp[0]);
  return retval;
}

