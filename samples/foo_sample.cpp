#include "foo.hpp"

#include <iostream>

using namespace std;

int main()
{
    Foo foo;

    cout << "Name of the class: " << foo.GetName() << endl;

    return 0;
}
