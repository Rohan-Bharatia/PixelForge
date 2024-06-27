# Matrix Class
## Overview
The ```Mat<T>``` class is designed to create matricies with a row size of ```R``` and a column size of ```C```

--------------------------------------------------------------------

## ```Mat<R, C>```
Create a matrix
```cpp
Mat(std::array<std::array<float, R>, C> data);
```

### Parameters
 * ```data```: The data inputed into the class

### Implementation
```cpp
pf::Mat<5, 5> matrix(1f, 2f, 3f, 4f, 5f,      \
                     6f, 7f, 8f, 9f, 10f,     \
                     11f, 12f, 13f, 14f, 15f, \
                     16f, 17f, 18f, 19f, 20f, \
                     21f, 22f, 23f, 24f, 25f);
```

--------------------------------------------------------------------

## ```value```
Return a value of the matrix
```cpp
float value(size_t idx_r, float idx_c);
```

### Parameters
 * ```idx_r```: The index of the matrix row that is being returned
 * ```idx_c```: The index of the matrix column that is being returned

### Implementation
```cpp
#include <iostream>

pf::Mat<5, 5> matrix(1f, 2f, 3f, 4f, 5f,      \
                     6f, 7f, 8f, 9f, 10f,     \
                     11f, 12f, 13f, 14f, 15f, \
                     16f, 17f, 18f, 19f, 20f, \
                     21f, 22f, 23f, 24f, 25f);

std::cout << matrix.value(2, 4); // [3rd, 5th] index
```

--------------------------------------------------------------------

# Preset Matricies
## ```Mat2x2```
Create a 2d matrix
```cpp
Mat2x2(float aa, float ab,
       float ba, float bb);
```

### Parameters
 * ```aa```: The aa position of the matrix
 * ```ab```: The ab position of the matrix
 * ```ba```: The ba position of the matrix
 * ```bb```: The bb position of the matrix

### Implementation
```cpp
pf::Mat2x2 matrix(1, 2,
                  3, 4);
```

--------------------------------------------------------------------

## ```Mat3x3```
Create a 3d matrix
```cpp
Mat3x3(float aa, float ab, float ac,
       float ba, float bb, float bc,
       float ca, float cb, float cc);
```

### Parameters
 * ```aa```: The aa position of the matrix
 * ```ab```: The ab position of the matrix
 * ```ac```: The ac position of the matrix
 * ```ba```: The ba position of the matrix
 * ```bb```: The bb position of the matrix
 * ```bc```: The bc position of the matrix
 * ```ca```: The ca position of the matrix
 * ```cb```: The cb position of the matrix
 * ```cc```: The cc position of the matrix

### Implementation
```cpp
pf::Mat3x3 matrix(1, 2, 3,
                  4, 5, 6,
                  7, 8, 9);
```

--------------------------------------------------------------------

## ```Mat4x4```
Create a 4d matrix
```cpp
Mat4x4(float aa, float ab, float ac, float ad,
       float ba, float bb, float bc, float bd,
       float ca, float cb, float cc, float cd,
       float da, float db, float dc, float dd);
```

### Parameters
 * ```aa```: The aa position of the matrix
 * ```ab```: The ab position of the matrix
 * ```ac```: The ac position of the matrix
 * ```ad```: the ad position of the matrix
 * ```ba```: The ba position of the matrix
 * ```bb```: The bb position of the matrix
 * ```bc```: The bc position of the matrix
 * ```bd```: the bd position of the matrix
 * ```ca```: The ca position of the matrix
 * ```cb```: The cb position of the matrix
 * ```cc```: The cc position of the matrix
 * ```cd```: the cd position of the matrix
 * ```da```: The da position of the matrix
 * ```db```: The db position of the matrix
 * ```dc```: The dc position of the matrix
 * ```dd```: the dd position of the matrix

### Implementation
```cpp
pf::Mat4x4 matrix(1, 2,  3,  4,
                  5, 6,  7,  8,
                  9, 10, 11, 12);
```

--------------------------------------------------------------------

## Full Implementation
```cpp
#include <iostream>

int main(int argc, char* argv[])
{
    pf::Mat2x2 m2x2(1, 2,
                    3, 4);
    pf::Mat3x3 m3x3(1, 2, 3,
                    4, 5, 6,
                     7, 8, 9);
    pf::Mat4x4 m4x4(1, 2,  3,  4,
                    5, 6,  7,  8,
                    9, 10, 11, 12);
    pf::Mat<5, 5> m5x5(1,  2,  3,  4,  5,
                       6,  7,  8,  9,  10,
                       11, 12, 13, 14, 15,
                       16, 17, 18, 19, 20,
                       21, 22, 23, 24, 25);
    
    std::cout << m2x2.value(0, 1) + m5x5.value(4, 2) << std::endl;

    return 0;
}
```