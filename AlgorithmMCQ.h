//
// Created by mikhail on 14.11.15.
//

#ifndef MAXCLIQUEPROBLEM_ALGORITHMMCQ_H
#define MAXCLIQUEPROBLEM_ALGORITHMMCQ_H

#include "AlgorithmMC.h"

class AlgorithmMCQ : public AlgorithmMC{

public:
  AlgorithmMCQ(const int vertex_number, const vector<vector<bool>>& adjacency_matrix) : AlgorithmMC(
      vertex_number, adjacency_matrix) {
    vertex_colours_.resize(vertex_number_);
  }

  vector<int> FindMaxClique() {
    vector<int> current_clique;
    current_clique.reserve(vertex_number_);

    list<int> candidate_set;
    for (int i = 0; i < vertex_number_; ++i) {
      candidate_set.push_back(i);
    }

    RecursiveFindMaxClique(current_clique, candidate_set);
    return max_clique_;
  }


  void RecursiveFindMaxClique(vector<int>& current_clique,
                              list<int>& candidate_set) {
    ++current_iteration_;
    vector<int> candidate_colours(candidate_set.size(), 0);
    ColourCandidates(candidate_set, candidate_colours);

    for (auto it = candidate_set.begin(); it != candidate_set.end(); it = candidate_set.erase(it)) {
      int new_vertex = *it;
      if (current_clique.size() + candidate_colours[new_vertex] <= max_clique_.size()) {
        return;
      }

      current_clique.push_back(new_vertex);

      list<int> new_candidate_set;
      for (auto inner_it = candidate_set.begin(); inner_it != candidate_set.end(); ++inner_it) {
        if (adjacency_matrix_[new_vertex][*inner_it]) {
          new_candidate_set.push_back(*inner_it);
        }
      }

      if (new_candidate_set.empty()) {
        if (current_clique.size() > max_clique_.size()) {
          SaveMaxClique(current_clique);
        }
      } else {
        RecursiveFindMaxClique(current_clique, new_candidate_set);
      }
      current_clique.pop_back();
    }
  }

  void ColourCandidates(list<int>& candidate_set, vector<int>& candidate_colours) {
    for (int i = 0; i < vertex_number_; ++i) {
      vertex_colours_[i].clear();
    }

    int colour_class_number = 0;
    for (auto it = candidate_set.begin(); it != candidate_set.end(); ++it) {
      int curr_colour_class = 0;
      while(ExistAdjacentVertex(*it, vertex_colours_[curr_colour_class])) {
        ++curr_colour_class;
      }
      vertex_colours_[curr_colour_class].push_back(*it);
      if (curr_colour_class > colour_class_number) {
        colour_class_number = curr_colour_class;
      }
    }
    candidate_set.clear();
    for (int i = colour_class_number; i >= 0; --i) {
      for (auto element = vertex_colours_[i].begin(); element != vertex_colours_[i].end(); ++i) {
        candidate_set.push_back(*element);
        candidate_colours[*element] = i + 1;
      }
    }
  }

  bool ExistAdjacentVertex(const int vertex, list<int>& colour_class) {
    for (auto it = colour_class.begin(); it != colour_class.begin(); ++it) {
      if (adjacency_matrix_[*it][vertex]) {
        return true;
      }
    }
    return false;
  }

protected:
  void SaveMaxClique(const vector<int>& new_max_clique) {
    max_clique_.clear();
    for (int i = 0; i < new_max_clique.size(); ++i) {
      max_clique_.push_back(new_max_clique[i]);
    }
  }
  vector<list<int>> vertex_colours_;
};


#endif //MAXCLIQUEPROBLEM_ALGORITHMMCQ_H
