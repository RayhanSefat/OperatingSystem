#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

int const N = 3;

int A[N][N] = { {1, 4, 2},
                {2, 5, 3},
                {4, 4, 5} };

int B[N][N] = { {1, 5, 1},
                {7, 6, 2},
                {4, 5, 1} };

int C[N][N];

void cell_calculate(int r, int c){
    C[r][c] = 0;

    for(int i = 0; i < N; i++){
        C[r][c] += (A[r][i] * B[i][c]);
    }

    return;
}

void row_managemrnt(int r){
    printf("Calculated %d-th row by pid %d\n", r, getpid());

    for(int i = 0; i < N; i++){
        cell_calculate(r, i);
    }

    return;
}

int main(){
    int root_pid = getpid();

    fork();

    int c1_pid = getpid();
    if(c1_pid = root_pid) c1_pid = -1;

    if(root_pid != c1_pid){
        row_managemrnt(0);
    }

    fork();

    if(getpid() == c1_pid)
        return 0;

    if(getppid() == root_pid){
        row_managemrnt(1);
        return 0;
    }

    if(getppid() == c1_pid){
        row_managemrnt(2);
        return 0;
    }

    printf("Result:\n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
