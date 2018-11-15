/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>
#include <iostream>

// Representation of an ordering of cities
class Cities {
 public:
  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>;

  // An ordering of the cities in cities_t. Each value represents a unique index
  // into the current city ordering.
  using permutation_t = std::vector<unsigned int>;

  // Given a permutation, return a new Cities object where the order of the
  // cities reflects the original order of this class after reordering with
  // the given ordering. So for example, the ordering { 1, 0 } simply swaps
  // the first two elements (coordinates) in the new Cities object.
  Cities reorder(const permutation_t& ordering) const;

  // For a given permutation of the cities in this object,
  // compute how long (distance) it would take to traverse all the cities in the
  // order of the permutation, and then returning to the first city.
  // The distance between any two cities is computed as the Euclidean 
  // distance on a plane between their coordinates.
  double total_path_distance(const permutation_t& ordering) const;


  // For reading in values from stringstreams. Uses standard old is >> int_var.
  // Does all the normal splitting >> normally does for ints. If the input is an
  // odd number of ints, the last one disappears into the aether.
  friend std::istream& operator>>(std::istream& is, Cities& cs);

  // For printing out the city list.
  friend std::ostream& operator<<(std::ostream &output, Cities& cs);


  // Setter. Don't see any need for a getter. If I do at some point, city_list_
  // is definitely going to get made public.
  void add_to_city_list_(coord_t c) { city_list_.push_back(c);}

  // random_permutation needs to know the length of the city list.
  int size() {return city_list_.size();}

 private:
  // List of city positions. Which is actually a vector. But it feels like a
  // list, and it's the feeling that counts.
  std::vector<coord_t> city_list_;
  // Private method which is called by total_path_distance. Perhaps if I were
  // feeling snarky I would make this public. But I am not, and so if the
  // customer wants to call this method, they will have to call
  // total_path_distance of the identity permutation.
  double own_path_distance();
};

Cities::permutation_t random_permutation(unsigned len);
Cities::permutation_t identity_permutation(unsigned len);

