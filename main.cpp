#include <iostream>

#include "AlgorithmMC.h"
#include "AlgorithmMCQ.h"

using namespace std;

int main() {
  int vertex_number;
  cin >> vertex_number;
  vector<vector<bool>> adjacency_matrix;

  vector<bool> row(vertex_number);
  adjacency_matrix.resize(vertex_number, row);

  srand(time(NULL));

  for (size_t i = 0; i < vertex_number; ++i) {
    for (size_t j = i + 1; j < vertex_number; ++j) {
      adjacency_matrix[i][j] = (rand() % 5 > 0);
      adjacency_matrix[j][i] = adjacency_matrix[i][j];
    }
    adjacency_matrix[i][i] = 0;
  }

  cout << "  ";
  for (int i = 0; i < vertex_number; ++i) {
    cout << i % 10;
  }
  cout << "\n";
  for (size_t i = 0; i < vertex_number; ++i) {
    cout << i << ":";
    for (size_t j = 0; j < vertex_number; ++j) {
      cout << adjacency_matrix[i][j];
    }
    cout << "\n";
  }

  AlgorithmMC mc_max_clique(adjacency_matrix.size(), adjacency_matrix);
  AlgorithmMCQ mcq_max_clique(adjacency_matrix.size(), adjacency_matrix);
  vector<int> mc_max_clique_result = mc_max_clique.FindMaxClique();
  vector<int> mcq_max_clique_result = mcq_max_clique.FindMaxClique();
  cout << mc_max_clique_result.size() << ":\n";
  for (int i = 0; i < mc_max_clique_result.size(); ++i) {
    cout << mc_max_clique_result[i] << " ";
  }
  cout << "\n";

  cout << mcq_max_clique_result.size() << ":\n";
  for (int i = 0; i < mcq_max_clique_result.size(); ++i) {
    cout << mcq_max_clique_result[i] << " ";
  }
  cout << "\n";
  return 0;
}
