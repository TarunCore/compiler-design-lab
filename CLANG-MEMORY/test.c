#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Node{
    int val;
    struct Node* next;
};

int main(){
    short unsigned int a = 4;
    a+=3;
    
    printf("PID: %d", getpid());
    return 0;
}