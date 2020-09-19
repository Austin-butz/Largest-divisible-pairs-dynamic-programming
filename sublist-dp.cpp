#include <vector>
#include <iostream>
#include <string> //for string operators
#include <algorithm> //for vector sort
#include <set>
#include <assert.h>
using namespace std;

string vec_to_string(vector<int> v) {
  string output = "[";
  output.insert(output.size(), to_string(v[0]));
  for (int i = 1; i < v.size(); i++)
    {
      output.insert(output.size(), ", ");
      output.insert(output.size(), to_string(v[i]));
    }
  output.insert(output.size(), "]");

  return output;
}

vector<int> largest_divisible_pairs(vector<int> input) {
  vector<vector<int>> table(input.size(), vector<int>(1));
  int b;
  for (int i = 0; i < input.size(); i++) {
    bool check = false;
    for (b = i; b >= 0; b--) {
      if (table[b].back() != 0 && input[i] % table[b].back() == 0) {
        check = true;
        break;
      }
    }
    if (check == true) { //if the previous loop finds a vector to fill table[i]'s terms it will use b to find which vector and fill it appropriately
      table[i][0] = table[b][0];
      for (int e = 0; e < table[b].size(); e++) {
        table[i].push_back(table[b][e+1]);
      }
      table[i].back() = input[i];
    }
    if (check == false) { //fills vector[i] with input up to i terms because there was no previous vector for use in dynamic programming
      table[i].resize(i+1);
      for (int j = 0; j <= i; j++) {
      table[i][j] = input[j]; 
      }
      for (int u = table[i].size()-1; u > 0; u--) {
        if (table[i][u] % table[i][u-1] != 0) {
          table[i].erase(table[i].begin() + u - 1); //iterates back to front removing items that don't divide evenly into the previous number
        }
      }
    }
  }
  int ans = 0;
  for (int i = 1; i < table.size(); i++) {
    if (table[i].size() > table[ans].size()) ans = i; 
  }
  return table[ans];
}

int main() {
  vector<int> values = {2, 6, 11, 22, 24 ,44, 48}; /////edit input here/////
  sort(values.begin(), values.end());
  vector<int> ans = largest_divisible_pairs(values);

  cout << "input: " << vec_to_string(values) << endl;
  cout << "output: " << vec_to_string(ans) << endl << endl;

  set<int> soln = {2, 6, 24, 48}; /////edit expected output here/////

  set<int> answerSet(ans.begin(), ans.end());
  assert(answerSet == soln);

  return 0;
}
