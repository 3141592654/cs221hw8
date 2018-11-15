/*
 * Tests cities.cc. This is not required, but is nevertheless a good idea.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "cities.hh"
int main() {
  Cities c;
  std::stringstream s;
  // basic io tests
  // note the odd number of inputs
  s << "3 1 4 1 59 26 5 19 7";
  s >> c;
  std::cout << c << std::endl;
  // testing total_path_distance. and also reorder in a sense.
  std::vector<unsigned int> t(0);
  t.push_back(0);
  t.push_back(1);
  t.push_back(2);
  t.push_back(3);
  // this should output
  // 1+(55^2+25^2)^0.5+(54^2+7^2)^0.5+(2^2+18^2)^0.5
  // =133.98.
  std::cout << c.total_path_distance(t) << std::endl;
  std::vector<unsigned int> t2(0);
  t2.push_back(0);
  t2.push_back(2);
  t2.push_back(1);
  t2.push_back(3);
  // this should output
  // =(56^2+25^2)^0.5+(55^2+25^2)^0.5+(1^2+18^2)^0.5+(2^2+18^2)^0.5
  // =157.88.
  std::cout << c.total_path_distance(t2) << std::endl;
  // explicitly testing reorder
  Cities c2;
  c2 = c.reorder(t2);
  std::cout << c2 << std::endl;
  // and to show off functionality that should never be used, but is stil there
  t2.push_back(3);
  t2.push_back(1);
  t2.push_back(2);
  t2.push_back(2);
  c2 = c.reorder(t2);
  std::cout << c2 << std::endl;
  // heck, let's use Eitan's tests too
  auto fin = std::ifstream("five.tsv");
  Cities cities;
  fin >> cities;
  std::cout << cities.total_path_distance({ 0, 1, 2, 3, 4 }) << "\n";
  std::cout << cities.total_path_distance({ 3, 2, 4, 0, 1 }) << "\n";
  // test random permutation
  Cities::permutation_t perm = random_permutation(10);
  for (int i = 0; i < 10; i++) {
    std::cout << perm[i];
  }
  std::cout << std::endl;
  Cities::permutation_t perm2 = random_permutation(10);
  for (int i = 0; i < 10; i++) {
    std::cout << perm2[i];//static_cast<int>(p);
  }
  std::cout << std::endl;
}
