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
   retval += std::hypot(city_list_[i].first - city_list_[i+1].first,
                      city_list_[i].second - city_list_[i+1].second);
  }
  retval += std::hypot(city_list_[i].first - city_list_[0].first,
                    city_list_[i].second - city_list_[0].second);
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
    os << p.first << "	" << p.second << std::endl;
  }
  return os;
}

// don't think next_permutation from the stl is going to help here, especially
// given the instruction about random numbers
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

Cities::permutation_t identity_permutation(unsigned len) {
 std::vector<unsigned int> retval(0);
  for (unsigned i = 0; i < len; i++){
    retval.push_back(i);
  }
  return retval;
}
