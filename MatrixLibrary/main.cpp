#include "Matrix.h"

int main()
{
    float arr2[] = {
        20, 5, 18
    };

    Matrix::mat3x1<float> mat(arr2);

    float arr[] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };

    Matrix::mat3x3<float> mat2(arr);

    mat *= mat2;
    
    mat.dump();

    return 0;
}