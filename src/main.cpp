#include <algorithm>
#include <iostream>
#include "eigen.h"

using namespace std;

int main(){
  Matrix mat(3,3);
  mat << 1, 2, 5,
         2, 1, -4,
         0, 0, 3;

pair<Vector, Matrix> sarasa = get_first_eigenvalues(mat, 3, 5000, 1e-16);
cout << sarasa.first << endl;
cout << sarasa.second << endl;


return 0;
}

