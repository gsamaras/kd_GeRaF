/** \example main_manual.cpp (may produce compiler errors)
 * This is an example of how to use serial building of the forest
 * and then search it efficiently, by using the manual Random_kd_forest.h, and not the auto one.
 * It doesn't employ all of the power or kd-GeRaF, but it's a good starting point.
 */
 
/**
@mainpage

This project provides approximate and exact nearest neighbor search for high dimensions.

@author Georgios Samaras
@date 03/01/2017
@version 1.0
*/

#include <string>
#include "../source/Random_kd_forest.h"
#include "../source/IO.h"

#define T float

int main(int argc, char *argv[]) {
  int N = 11, D = 10, Q = 1;
  int k = 2;
  double epsilon = 0.0;
  std::string datafile = "test_files/data.txt", queryfile = "test_files/query.txt";
  std::vector< std::vector<std::pair<float, int> > > res;

  size_t points_per_leaf = 1;
  int trees_no = 1;
  int t = 1;
  int max_leaf_check = 3;
  int sample_size = N;

  Division_Euclidean_space<T> ds(N, D);
  readDivisionSpace<T>(ds, N, D, datafile.c_str());

  Random_kd_forest<T> RKDf(ds, sample_size, points_per_leaf, trees_no, t);

  // read the queries
  std::vector<std::vector<T> > q;
  read_points<T>(q, Q, D, queryfile.c_str());
  
  // perform the search
  std::vector<std::vector<std::pair<float, int> > > results;
  results.resize(Q);
  for (unsigned int i = 0; i < Q; ++i) {
        search_nn_prune(q[i], results[i], max_leaf_check, k, epsilon);
  }

  std::cout << "\nRESULTS\n";
  for (std::vector<std::pair<float, int> >::const_iterator it = res[0]
      .begin(); it != res[0].end(); ++it)
    std::cout << it->first << ", index = " << it->second << std::endl;

  std::cout << "main_manual successfully terminated" << std::endl;
  return 0;
}
