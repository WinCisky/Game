/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListAvailableRooms.h
 * Author: Simo
 *
 * Created on 9 marzo 2017, 23.39
 */

#ifndef LISTAVAILABLEROOMS_H
#define LISTAVAILABLEROOMS_H

//(used for print the list)
#include <iostream>

using namespace std;

struct list {
    char dir;
    int x;
    int y;
    list* next;
};

typedef list* ptr;

void insertTail(ptr l, char c, int x, int y);
int getLength(ptr l);
ptr getElement(ptr l, int pos);
void deletePos(ptr l, int pos);
void stampa(ptr l);
void add_elements(ptr l, char c, int x, int y, bool n, bool s, bool e, bool w);

#endif /* LISTAVAILABLEROOMS_H */

