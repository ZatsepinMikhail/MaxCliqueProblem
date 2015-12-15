#include "AlgorithmMCQ.h"

vector<int> AlgorithmMCQ::FindMaxClique() {
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
  std::cout << "MCQ: It took me " << time_span.count() << " seconds with " << current_iteration_ << " iterations\n";
  return max_clique_;
}

void AlgorithmMCQ::RecursiveFindMaxClique(vector<int>& current_clique,
                                          list<int>& candidate_set) {
  ++current_iteration_;
  vector<int> candidate_colours(vertex_number_, 0);

  PaintCandidates(candidate_set, candidate_colours);

  while(!candidate_set.empty()) {

    int new_vertex = candidate_set.front();
    if (current_clique.size() + candidate_colours[new_vertex] <= max_clique_.size()) {
      return;
    }

    current_clique.push_back(new_vertex);

    list<int> new_candidate_set;
    for (auto it = candidate_set.begin(); it != candidate_set.end(); ++it) {
      if (adjacency_matrix_[new_vertex][*it]) {
        new_candidate_set.push_back(*it);
      }
    }

    if (new_candidate_set.empty() && current_clique.size() > max_clique_.size()) {
      SaveMaxClique(current_clique);
    } else {
      RecursiveFindMaxClique(current_clique, new_candidate_set);
    }
    current_clique.pop_back();
    candidate_set.pop_front();
  }
}

void AlgorithmMCQ::PaintCandidates(list<int>& candidate_set,
                                   vector<int>& candidate_colours) {
  vector<list<int>> vertex_colour_classes(vertex_number_);

  for (int i = 0; i < vertex_number_; ++i) {
    vertex_colour_classes[i].clear();
  }

  int colour_class_number = 0;

  for (auto curr_vertex = candidate_set.begin(); curr_vertex != candidate_set.end(); ++curr_vertex) {
    int curr_colour_class = 0;

    while(ExistAdjacentVertex(*curr_vertex, vertex_colour_classes[curr_colour_class])) {
      ++curr_colour_class;
    }
    vertex_colour_classes[curr_colour_class].push_back(*curr_vertex);
    if (curr_colour_class > colour_class_number) {
      colour_class_number = curr_colour_class;
    }
  }
  candidate_set.clear();
  for (int i = colour_class_number; i >= 0; --i) {
    for (auto element = vertex_colour_classes[i].begin();
              element != vertex_colour_classes[i].end(); ++element) {
      candidate_set.push_back(*element);
      candidate_colours[*element] = i + 1;
    }
  }
}

bool AlgorithmMCQ::ExistAdjacentVertex(const int vertex, list<int>& colour_class) {
  for (auto it = colour_class.begin(); it != colour_class.end(); ++it) {
    if (adjacency_matrix_[*it][vertex]) {
      return true;
    }
  }
  return false;
}


