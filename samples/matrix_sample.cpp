#include "matrix.hpp"

using namespace std;

int main()
{
    cout << "---------------------------" << endl;

    Matrix m(3, 4);
    m.Random();
    cout << m;

    cout << "---------------------------" << endl;

    return 0;
}
