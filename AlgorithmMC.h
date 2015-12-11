//
// Created by mikhail on 14.11.15.
//

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
              const vector<vector<bool>>& adjacency_matrix)
      :vertex_number_(vertex_number),
       adjacency_matrix_(adjacency_matrix),
       current_iteration_(0)
      {

        //check for correctness of arguments
        if (vertex_number_ <= 0) {
          throw std::invalid_argument("vertex number should be positive");
        }

        if (vertex_number_ != adjacency_matrix_.size()) {
          throw std::invalid_argument("incorrect adjacency matrix: wrong size");
        }

        for (int i = 0; i < vertex_number_; ++i) {
          if (adjacency_matrix_[i].size() != vertex_number_) {
            throw std::invalid_argument("incorrect adjacency matrix: it's not square matrix");
          }
        }

        for (int i = 0; i < vertex_number_; ++i) {
          for (int j = i + 1; j < vertex_number_; ++j) {
            if (adjacency_matrix_[i][j] != adjacency_matrix_[j][i]) {
              throw std::invalid_argument("incorrect adjacency matrix: it's not symmetric matrix");
            }
          }
        }

        //count degrees of vertices
        vertex_degrees_.resize(vertex_number_, 0);
        for (int i = 0; i < vertex_number_; ++i) {
          for (int j = 0; j < vertex_number_; ++j) {
            vertex_degrees_[i] += adjacency_matrix_[i][j];
          }
        }

        max_clique_.reserve(vertex_number_);
  }

  vector<int> FindMaxClique() {

    vector<int> current_clique;

    //there will be no reallocations
    current_clique.reserve(vertex_number_);

    list<int> candidate_set;
    for (int i = 0; i < vertex_number_; ++i) {
      candidate_set.push_back(i);
    }
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    RecursiveFindMaxClique(current_clique, candidate_set);

    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "MC: It took me " << time_span.count() << " seconds with " << current_iteration_ << " iterations\n";
    return max_clique_;
  }


  void RecursiveFindMaxClique(vector<int>& current_clique,
                              list<int>& candidate_set) {
    ++current_iteration_;

    for (auto it = candidate_set.begin(); it != candidate_set.end(); it = candidate_set.erase(it)) {
      if (current_clique.size() + candidate_set.size() <= max_clique_.size()) {
        return;
      }

      int new_vertex = *it;
      current_clique.push_back(new_vertex);

      //create new candidate set, choose only vertices adjacent to new_vertex
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
      } else if (current_clique.size() + new_candidate_set.size() > max_clique_.size()) {
        RecursiveFindMaxClique(current_clique, new_candidate_set);
      }
      current_clique.pop_back();
    }
  }

protected:
  void SaveMaxClique(const vector<int>& new_max_clique) {
    max_clique_ = new_max_clique;
  }

  int current_iteration_;
  int vertex_number_;
  vector<vector<bool>> adjacency_matrix_;
  vector<int> vertex_degrees_;

  vector<int> max_clique_;
};


#endif //MAXCLIQUEPROBLEM_MC_ALGORITHM_H
