#include <string>
#include <vector>
#include <iostream>


int main(){

  // return a number
  int result = []()->int {return 4;}();

  cout << result << endl;



  return 0;
}
