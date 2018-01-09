#include <iostream>
using namespace std;

int main()
{
    auto func = [] () { cout << "Hello world\n"; };
    func(); // now call the function
}
