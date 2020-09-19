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
//largest_divisible_pairs using dynamic programming allows for previously calculated lists to be reused by future lists, if the for loop finds a previous vector that can be evenly divided into input[i] it can use that list as a base 
//without having to worry about checking for divisibility, by removing the need to check for divisibility and the added operation of erasing an item from a vector, the time complexity of this version of the code is definitivly lower
//though it may be difficult to notice given how relativly simple these programs are, as neither took any noticible amount of time to complete
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
  vector<int> values = {2, 6, 5, 10, 20, 24, 40, 48, 80, 96, 192, 384, 400, 800, 1600, 3200}; /////edit input here/////
  sort(values.begin(), values.end());
  vector<int> ans = largest_divisible_pairs(values);

  cout << "input: " << vec_to_string(values) << endl;
  cout << "output: " << vec_to_string(ans) << endl << endl;

  set<int> soln = {5, 10, 20, 40, 80, 400, 800, 1600, 3200}; /////edit expected output here/////

  set<int> answerSet(ans.begin(), ans.end());
  assert(answerSet == soln);

  return 0;
}
