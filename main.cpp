#include <iostream>
#include "Matrix.h"
#include <math.h>


int main()
{
    int size = 4;

    Matrix A(size, size);
    Matrix B(size, size);
    
    cout << "Imprime A:" << endl;
    cout << A << endl << endl;

    cout << "Imprime B:" << endl;
    cout << B << endl << endl;

    cout << "Imprime A + B:" << endl;
    cout << A + B << endl << endl;

    cout << "Imprime transposta de A + B:" << endl;
    cout << (A+B).transposed() << endl << endl;

    cout << "Imprime A - B:" << endl;
    cout << A - B << endl << endl;
    
    cout << "Imprime inversa de A - B:" << endl;
    cout << !(A-B) << endl << endl;

    cout << "Imprime A * B:" << endl;
    cout << (A * B) << endl << endl;

    cout << "Imprime A / 10:" << endl;
    cout << (A / 10) << endl << endl;

    cout << "Imprime o determinante de A:" << endl;
    cout << A.getDeterminant() << endl << endl;

    cout << "Imprime o determinante da inversa de A:" << endl;
    cout << (!A).getDeterminant() << endl << endl;

    cout << "Imprime o determinante de B:" << endl;
    cout << (B.getDeterminant()) << endl << endl;

    cout << "Imprime o determinante de A - B:" << endl;
    cout << (A - B).getDeterminant() << endl;

    cout << "Imprime o determinante de B - A:" << endl;
    cout << (B - A).getDeterminant() << endl;

    cout << "Imprime prova da inversa:" << endl;
    cout << A * !A << endl << endl;
}