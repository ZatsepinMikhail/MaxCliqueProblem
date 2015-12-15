#include "AlgorithmMC.h"

AlgorithmMC::AlgorithmMC(const int vertex_number,
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

  max_clique_.reserve(vertex_number_);
}

vector<int> AlgorithmMC::FindMaxClique() {

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


void AlgorithmMC::RecursiveFindMaxClique(vector<int>& current_clique,
                                         list<int>& candidate_set) {
  ++current_iteration_;

  while(!candidate_set.empty()) {

    if (current_clique.size() + candidate_set.size() <= max_clique_.size()) {
      return;
    }

    int new_vertex = candidate_set.front();
    current_clique.push_back(new_vertex);

    //create new candidate set, choose only vertices adjacent to new_vertex
    list<int> new_candidate_set;
    for (auto it = candidate_set.begin(); it != candidate_set.end(); ++it) {
      if (adjacency_matrix_[new_vertex][*it]) {
        new_candidate_set.push_back(*it);
      }
    }

    if (new_candidate_set.empty() && current_clique.size() > max_clique_.size()) {
      SaveMaxClique(current_clique);
    } else if (current_clique.size() + new_candidate_set.size() > max_clique_.size()) {
      RecursiveFindMaxClique(current_clique, new_candidate_set);
    }
    current_clique.pop_back();
    candidate_set.pop_front();
  }
}
