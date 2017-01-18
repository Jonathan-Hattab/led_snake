//
//  game.c
//  snake
//
//  Created by Jonathan Hattab on 16/01/2017.
//  Copyright © 2017 Jonathan Hattab. All rights reserved.
//

#include "game.h"

int** getBoard(int n, int p){
    int** board = malloc(n * sizeof(int));
    if(board == NULL) exit(0);

    for(int i = 0; i < n; i++){
        int* row = malloc(p * sizeof(int));
        if(row == NULL) exit(0);

        for(int j = 0; j < p; j++){
            row[j] = 0;
        }
        board[i] = row;
    }

    return board;
}

int* getLinearBoard(int n, int p){
    int* board = malloc(n * p * sizeof(int));
    if(board == NULL) exit(0);
    
    for(int i = 0; i < n * p; i++){
        // printf("Inserting %d at [%d]", 0, i);
        board[i] = 0;
    }
    
    return board;
}

void printBoard(int** board, int n, int p){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < p; j++){
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }
}

void printLinearBoard(int* board, int n, int p){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < p; j++){
            printf("%d\t", board[p * i + j]);
        }
        printf("\n");
    }
    
    printf("\n");
}

int* placeSnake(int* board, int n, int p, int direction, int size){
    int* snake = malloc(size * sizeof(int));
    int i = floor(n/2);
    int j = floor(n/2);

         if(direction == 0) i = n - 1;
    else if(direction == 1) j = 0;
    else if(direction == 2) i = 0;
    else if(direction == 3) j = p - 1;
    
    int index = 0;
    while(size > 0){
        board[p * i + j] = 1;
        
        snake[index] = p * i + j;
        
             if(direction == 0) i--;
        else if(direction == 1) j++;
        else if(direction == 2) i++;
        else if(direction == 3) j--;
        
        size--;
        index++;
    }
    
    return snake;
}

void placeCandy(int* board,int n,int p){
    int total = 0;
    int pos;
    for(pos = 0; pos < n * p; pos++){
        if(board[pos] == 0) total++;
    }
    
    printf("Total : %d\n", total);

    int index = floor(rand()/(double)RAND_MAX*total);
    pos = 0;
    do{
        while(pos < n * p && board[pos] > 0) pos++;
        //printf("pos : %d \t Board[pos] : %d \t index : %d \n", pos, board[pos], index);
        if(index > 0){
            index--;
            pos++;
        }
    }while(index > 0 && pos < n * p);
    //printf("Placing candy at %d \n", pos);
    board[pos] = 2;
}

void printSnake(int* snake, int size){
    for(int i = 0; i < size; i++){
        printf("%d\t", snake[i]);
    }
    printf("\n\n");
}

int getNextHeadPosition(int* snake, int* board, int n, int p, int size, int direction){
    int pos = snake[size - 1];
    int i = floor(pos / p);
    int j = pos % p;
    
         if(direction == 0) i--;
    else if(direction == 1) j++;
    else if(direction == 2) i++;
    else if(direction == 3) j--;
    
    if(i < 0 || i >= n || j < 0 || j >= p) return -1;
    
    return p * i + j;
}

void translateSnake(int* snake, int* board, int size, int nextPos){
    board[snake[0]] = 0;
    board[nextPos] = 1;
    for(int i = 0; i < size - 1; i++){
        snake[i] = snake[i + 1];
    }
    snake[size - 1] = nextPos;
}

int* enlargeSnake(int* snake, int* board, int size, int nextPos){
    int* newSnake = malloc((size + 1) * sizeof(int));
    if(newSnake == NULL) exit(0);

    board[nextPos] = 1;
    for(int i = 0; i < size; i++){
        newSnake[i] = snake[i];
    }
    newSnake[size] = nextPos;

    free(snake);

    return newSnake;
}
