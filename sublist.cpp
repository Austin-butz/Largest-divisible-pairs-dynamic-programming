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


vector<int> ldp(vector<int> input, int size) {
  vector<int> copy(size);  //copy of input modified to be the right size
  for (int i = 0; i < copy.size(); i++) copy[i] = input[i];
  
  for (int i = copy.size()-1; i > 0; i--) {
    if (copy[i] % copy[i-1] != 0) {
      copy.erase(copy.begin() + i - 1); //iterates back to front removing items that don't divide evenly into the previous number
    }
  }
  
  if (size == input.size()) {
    return copy; //base case
  }
  else {
      vector<int> next = ldp(input, size+1); //recursive call to create another vector which is initialized as size+1
      
      if(copy.size() < next.size()) { //checks if it should return its own vector or the recursive call's vector
	return next;
      }
      else {
	return copy;
      }
    }
}

vector<int> largest_divisible_pairs(vector<int> input){ //wrapper function to call ldp
  sort(input.begin(), input.end());
  vector<int> output = ldp(input, 1);
  return output;
}

int main() {
  vector<int> values = {28, 22, 7, 2, 8, 14, 24, 56};
  vector<int> ans = largest_divisible_pairs(values);
  
  cout << "input: " << vec_to_string(values) << endl;
  cout << "output: " << vec_to_string(ans) << endl << endl;
  
  set<int> soln = {56, 14, 7, 28};
  set<int> answerSet(ans.begin(), ans.end());
  assert(answerSet == soln);
  
  return 0;
}
