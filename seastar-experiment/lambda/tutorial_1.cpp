#include <string>
#include <vector>
#include <iostream>
using namespace std;

int main(){

// return a number
  int result = []()->int {return 4;}();
  cout << result << endl;

// []( input_paramter_declaration )->returned_type { body_of_the_lambda_expression }( parameters )
  result = [](int input)-> int {return  2 * input;}(10);
  cout << result << endl;

  result = [](int a, int b)-> int {return a + b;}(2,4);
  cout << result << endl;

  auto func = [](int a, int b) -> int { return a+b; };
  cout << func(2, 3) << endl;

  int n=10;
  vector<int> v(n);

  for(int i = n - 1, j = 0; i >= 0; i--, j++) v[j] = i + 1;

  for(int i = 0; i < n; i++) cout << v[i] << " "; cout << endl;

  // sort the vector
  sort(v.begin(),v.end(),[](int i, int j) -> bool{ return (i < j);});

	for(int i = 0; i < n; i++) cout << v[i] << " "; cout << endl;



  return 0;
}
