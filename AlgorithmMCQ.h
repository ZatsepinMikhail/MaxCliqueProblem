//
// Created by mikhail on 14.11.15.
//

#ifndef MAXCLIQUEPROBLEM_ALGORITHMMCQ_H
#define MAXCLIQUEPROBLEM_ALGORITHMMCQ_H

#include "AlgorithmMC.h"
#include <chrono>

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

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    RecursiveFindMaxClique(current_clique, candidate_set);

    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "MCQ: It took me " << time_span.count() << " seconds.\n";
    return max_clique_;
  }


  void RecursiveFindMaxClique(vector<int>& current_clique,
                              list<int>& candidate_set) {
    ++current_iteration_;

    vector<int> candidate_colours(candidate_set.size(), 0);
    PaintCandidates(candidate_set, candidate_colours);

    for (auto it = candidate_set.begin(); it != candidate_set.end(); it = candidate_set.erase(it)) {
      int new_vertex = *it;
      if (current_clique.size() + candidate_colours[new_vertex] <= max_clique_.size()) {
        return;
      }

      current_clique.push_back(new_vertex);

      list<int> new_candidate_set;
      for (auto inner_it = candidate_set.rbegin(); inner_it != candidate_set.rend(); ++inner_it) {
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

  void PaintCandidates(list<int>& candidate_set, vector<int>& candidate_colours) {
    for (int i = 0; i < vertex_number_; ++i) {
      vertex_colours_[i].clear();
    }

    int total_class_number = 0;
    for (auto it = candidate_set.begin(); it != candidate_set.end(); ++it) {
      int curr_colour_class = 0;
      while(ExistAdjacentVertex(*it, vertex_colours_[curr_colour_class])) {
        ++curr_colour_class;
      }
      vertex_colours_[curr_colour_class].push_back(*it);
      if (curr_colour_class > total_class_number) {
        total_class_number = curr_colour_class;
      }
    }
    candidate_set.clear();
    for (int i = total_class_number; i >= 0; --i) {
      for (auto element = vertex_colours_[i].begin(); element != vertex_colours_[i].end(); ++element) {
        candidate_set.push_back(*element);
        candidate_colours[*element] = i + 1;
      }
    }
  }

  bool ExistAdjacentVertex(const int vertex, list<int>& colour_class) {
    for (auto it = colour_class.begin(); it != colour_class.end(); ++it) {
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
