/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListRooms.h
 * Author: Simo
 *
 * Created on 16 marzo 2017, 18.32
 */

#ifndef LISTROOMS_H
#define LISTROOMS_H

//(used for print the list)
#include <iostream>
#include "Map.h"

using namespace std;

//1 definire le strutture dati
//2 definire i metodi
//3 buildare il tutto
//4 testing
struct list_rooms{
    int level;
    bool has_stairs_up;
    bool has_stirs_down;
    stanza* room;
    list_rooms* next;
};

typedef list_rooms* ptr_list_rooms;

//insert an element at the end of the list
void insert_elem(ptr_list_rooms list, int l, bool up, bool down, stanza* r);

//search first element of level x

//search element with x y coordinates from level x(pos)
ptr_list_rooms search_return_elem(ptr_list_rooms head, int x, int y);

//is the element in the list? (search from pos)

//print the list
void print_list(ptr_list_rooms l);

#endif /* LISTROOMS_H */

