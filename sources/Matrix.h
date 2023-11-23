//
// Created by toxic on 7/08/2023.
//

#ifndef VISUALISER_MATRIX_H
#define VISUALISER_MATRIX_H
#include "raylib.h"


float dot(Vector2 a, Vector2 b) {
    return a.x * b.x + a.y * b.y;
}

Vector2 sub(Vector2 a, Vector2 b) {
    return Vector2{a.x - b.x, a.y - b.y};
}

Vector2 mult(Vector2 a, float b) {
    return Vector2{a.x * b, a.y * b};
}

Vector2 mult(Vector2 a, Vector2 b) {
    return Vector2{a.x * b.x, a.y * b.y};
}

Vector2 mult(Vector2 a, Matrix b){
    return Vector2{a.x * b.m0 + a.y*b.m4, a.x*b.m1 + a.y*b.m5};
}



#endif //VISUALISER_MATRIX_H
