#include "matrix.hpp"

using namespace std;

int main()
{
    Matrix m(3, 4);
    m.Random();

    cout << m;

    return 0;
}
