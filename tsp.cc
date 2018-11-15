/*
 * Approximately solves the Traveling Salesman Problem.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "cities.hh"
#define NITER 1000000

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "insufficient arguments provided" << std::endl;
    return -1;
  }
  std::string fname(argv[1]);
  auto fin = std::ifstream(fname);
  if (!(fin.is_open())) {
    std::cerr << "input file failed to open" << std::endl;
    return -1;
  }
  Cities cities;
  fin >> cities;
  int s = cities.size();
  std::vector<unsigned int> id = identity_permutation(s);
  double cur_dist = cities.total_path_distance(id);
  Cities::permutation_t temp_permut;
  // produce many random permutations and keep the best one
  for (int i = 1; i <= NITER; i++) {
    temp_permut = random_permutation(s);
    double d = cities.total_path_distance(temp_permut);
    if (d < cur_dist) {
      cities = cities.reorder(temp_permut);
      cur_dist = d;
      std::cout << i << "	" << cur_dist << std::endl;
    }
  }
  std::string foname("shortest.tsv");
  auto fout = std::ofstream(foname);
  if (!(fout.is_open())) {
    std::cerr << "output file failed to open" << std::endl;
    return -1;
  }
  fout << cities;
  return 0;
}
