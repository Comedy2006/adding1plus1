#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *value;
}adding;

typedef int (*add)(int, int);
typedef adding* (*createContainer)(int);
typedef int (*calculation)(add, int, int, createContainer);

int addition (int, int);
int calc(add, int, int, createContainer);
adding* functionPointer(int);

adding* functionPointer(int val){
    adding* container = (adding*)malloc(sizeof(adding));
    if(container == NULL){
        fprintf(stderr, "Memory allocation failed (container)\n");
        exit(1);
    }

    container->value=(int*)malloc(sizeof(int));
    if(container->value == NULL){
        fprintf(stderr, "Memory allocation failed (container->value)\n");
        free(container);
        exit(1);
    }

    *(container->value) = val;
    return container;
}

int addition(int a, int b){
    return a+b;
}

int calc(add calculating, int a, int b, createContainer addContainer){
    adding* ptrA = addContainer(a);
    adding* ptrB = addContainer(b);

    int** pointerA = &(ptrA->value);
    int** pointerB = &(ptrB->value);

    int*** pointerptrA = &pointerA;
    int*** pointerptrB = &pointerB;

    int addingResult = calculating(***pointerptrA, ***pointerptrB);

    free(ptrA->value);
    free(ptrA);
    free(ptrB->value);
    free(ptrB);

    return addingResult;
}

int main(int argc, char** argv){
    calculation func = &calc;
    add maths = &addition;
    createContainer newContainer = &functionPointer;

    int adding1plus1 = func(maths, 1, 1, newContainer);

    int* resulting = (int*)malloc(sizeof(int));
    if (resulting == NULL) {
        fprintf(stderr, "Memory allocation failed (resulting)\n");
        exit(1);
    }
    *resulting = adding1plus1;

    int** ptrresulting = (int**)malloc(sizeof(int*));
    if (ptrresulting == NULL) {
        fprintf(stderr, "Memory allocation failed (ptrresulting)\n");
        exit(1);
    }
    *ptrresulting = resulting;

    printf("%d", **ptrresulting);

    free(resulting);
    free(ptrresulting);

    return 0x00;
}