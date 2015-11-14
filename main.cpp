#include <iostream>

#include "AlgorithmMC.h"
#include "AlgorithmMCQ.h"
#include <fstream>

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
      adjacency_matrix[i][j] = (rand() % 10 > 0);
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

  /*std::ifstream fin("/home/mikhail/ClionProjects/MaxCliqueProblem/input.csv");
  if (fin.fail()) {
    throw std::invalid_argument("This file can't be openned.");
  }

  string one_string;
  vector<bool> one_row;
  int current_size = 0;

  while(!(fin >> one_string).eof()) {

    for (int i = 0; i < one_string.size(); ++i) {

      //only 1 or 0 can be at even positions
      if (i % 2 == 0) {
        switch(one_string[i]) {
          case '1':
            one_row.push_back(true);
            break;
          case '0':
            one_row.push_back(false);
            break;
          default:
            throw std::invalid_argument("The format of file is wrong.");
          }
      } else if (i % 2 == 1 && one_string[i] != ',') {
        throw std::invalid_argument("The format of file is wrong.");
      }
    }

    //check for rectangle
    if (adjacency_matrix.size() == 0) {
      current_size = one_row.size();
    } else if (current_size != one_row.size()) {
      throw std::invalid_argument("Field in file isn't rectangle.");
    }
    adjacency_matrix.push_back(one_row);
    one_row.clear();
  }*/

  AlgorithmMC mc_max_clique(adjacency_matrix.size(), adjacency_matrix);
  AlgorithmMC mcq_max_clique(adjacency_matrix.size(), adjacency_matrix);
  vector<int> mc_max_clique_result = mc_max_clique.FindMaxClique();
  vector<int> mcq_max_clique_result = mcq_max_clique.FindMaxClique();
  for (int i = 0; i < mc_max_clique_result.size(); ++i) {
    cout << mc_max_clique_result[i] << " ";
  }
  cout << "\n";

  for (int i = 0; i < mcq_max_clique_result.size(); ++i) {
    cout << mcq_max_clique_result[i] << " ";
  }
  cout << "\n";
  return 0;
}