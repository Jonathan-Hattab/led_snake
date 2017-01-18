//
//  game.h
//  snake
//
//  Created by Jonathan Hattab on 16/01/2017.
//  Copyright © 2017 Jonathan Hattab. All rights reserved.
//

#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** getBoard(int n, int p);
int* getLinearBoard(int n, int p);
void printBoard(int** board, int n, int p);
void printLinearBoard(int* board, int n, int p);

int* placeSnake(int* board, int n, int p, int direction, int size);
void printSnake(int* snake, int size);
void placeCandy(int* board,int n,int p);
int getNextHeadPosition(int* snake, int* board, int n, int p, int size, int direction);

void translateSnake(int* snake, int* board, int size, int nextPos);
int* enlargeSnake(int* snake, int* board, int size, int nextPos);

#endif /* game_h */
