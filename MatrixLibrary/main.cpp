#include "Matrix.h"

int main()
{
    float arr2[] = {
        8, 3, 6,
        0, 0, 1,
        5, 8, 3
    };

    Matrix::mat3x3<float> mat(arr2);

    float arr[] = {
        5, 3, 2,
        1, 0, 0,
        8, 2, 6
    };

    Matrix::mat3x3<float> mat2(arr);

    mat *= mat2;
    
    mat.dump();

    return 0;
}