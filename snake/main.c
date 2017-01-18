//
//  main.c
//  snake
//
//  Created by Jonathan Hattab on 16/01/2017.
//  Copyright © 2017 Jonathan Hattab. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "game.h"

int onTick();
void *thread_1(void *arg);

int n = 8;
int p = 8;
int direction = 0;
int size = 3;
int* board;
int* snake;
char c;
int game_status;

int main(int argc, const char * argv[]) {
    srand((int) time(NULL));

    board = getLinearBoard(n, p);
    snake = placeSnake(board, n, p, direction, size);
    placeCandy(board, n, p);
    printLinearBoard(board, n, p);
    printSnake(snake, size);
    game_status = 1;

    pthread_t thread1;
    
    printf("Avant la création du thread.\n");
    
    if(pthread_create(&thread1, NULL, thread_1, NULL) == -1) {
        perror("pthread_create");
        return EXIT_FAILURE;
    }

    while(game_status == 1){
        c = getchar();
        if(direction != 2 && c == -128) direction = 0;
        if(direction != 3 && c == -125) direction = 1;
        if(direction != 0 && c == -127) direction = 2;
        if(direction != 1 && c == -126) direction = 3;
    }

    return EXIT_SUCCESS;
}

void *thread_1(void *arg){
    printf("Nous sommes dans le thread.\n");
    
    while(onTick() > 0){
        sleep(1);
        printf("\n");
    }
    
    game_status = 0;
    
    /* Pour enlever le warning */
    (void) arg;
    pthread_exit(NULL);
}

int onTick(){
    int nextPos = getNextHeadPosition(snake, board, n, p, size, direction);
    
    if(nextPos < 0) return 0;
    
    if(board[nextPos] == 1){
        printf("You lost !");
        return 0;
    }
    else if(board[nextPos] == 2){
        snake = enlargeSnake(snake, board, size, nextPos);
        size++;
        placeCandy(board, n, p);
    }
    else if(board[nextPos] == 0){
        translateSnake(snake, board, size, nextPos);
    }
    
    printLinearBoard(board, n, p);
    
    return 1;
}
