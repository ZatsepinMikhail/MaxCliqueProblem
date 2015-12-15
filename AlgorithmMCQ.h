#ifndef MAXCLIQUEPROBLEM_ALGORITHMMCQ_H
#define MAXCLIQUEPROBLEM_ALGORITHMMCQ_H

#include "AlgorithmMC.h"
#include <chrono>

class AlgorithmMCQ : public AlgorithmMC{

public:
  AlgorithmMCQ(const int vertex_number, const vector<vector<bool>>& adjacency_matrix)
      : AlgorithmMC(vertex_number, adjacency_matrix) {}

  vector<int> FindMaxClique();

  void RecursiveFindMaxClique(vector<int>& current_clique,
                              list<int>& candidate_set);

  void PaintCandidates(list<int>& candidate_set, vector<int>& candidate_colours);

  bool ExistAdjacentVertex(const int vertex, list<int>& colour_class);
};

#endif //MAXCLIQUEPROBLEM_ALGORITHMMCQ_H
