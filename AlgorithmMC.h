#ifndef MAXCLIQUEPROBLEM_MC_ALGORITHM_H
#define MAXCLIQUEPROBLEM_MC_ALGORITHM_H

#include <iostream>
#include <algorithm>
#include <exception>
#include <list>
#include <vector>
#include <chrono>

using std::exception;
using std::list;
using std::vector;

class AlgorithmMC {

public:
  AlgorithmMC(const int vertex_number,
              const vector<vector<bool>>& adjacency_matrix);

  vector<int> FindMaxClique();

  void RecursiveFindMaxClique(vector<int>& current_clique,
                              list<int>& candidate_set);
protected:
  void SaveMaxClique(const vector<int>& new_max_clique) {
    max_clique_ = new_max_clique;
  }

  int current_iteration_;
  int vertex_number_;
  vector<vector<bool>> adjacency_matrix_;

  vector<int> max_clique_;
};


#endif //MAXCLIQUEPROBLEM_MC_ALGORITHM_H
