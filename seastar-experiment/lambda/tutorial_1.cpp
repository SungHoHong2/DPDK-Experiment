#include <string>
#include <vector>
#include <iostream>
using namespace std;

int main(){

  // return a number
  int result = []()->int {return 4;}();
  cout << result << endl;

  result = [](int input)-> int {return * 2 * input;}(10);
  cout << result << endl;

  return 0;
}
