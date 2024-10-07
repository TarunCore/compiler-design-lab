#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Node{
    int val;
    struct Node* next;
};

int main(){
    char *arr = {"df","Fd"};
    execv("./e2", arr);
    printf("PID: %d", getpid());
    
    
    return 0;
}