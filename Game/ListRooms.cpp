/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ListRooms.h"

void insert_elem(ptr_list_rooms list, int l, bool up, bool down, stanza* r){
    cout << "Element: " << r->x << " " << r->y << '\n';
    ptr_list_rooms newElement = new (list_rooms);
    newElement->has_stairs_up = up;
    newElement->has_stirs_down = down;
    newElement->room = r;
    newElement->level = l;
    newElement->next = NULL;
    ptr_list_rooms lista = list;
    while(lista->next != NULL){
        lista = lista->next;
    }
    lista->next = newElement;
}

ptr_list_rooms search_return_elem(ptr_list_rooms head, int x, int y){
    bool found = false;
    ptr_list_rooms elem = head;
    while(!found && (elem->next != NULL)){
        elem = elem->next;
        cout << "Searching: " << x << " " << y << " found: " << elem->room->x << " " << elem->room->y;
        if((elem->room->x == x) && (elem->room->y == y)){
            found = true;
            cout << " yey! \n";
        }else{
            cout << '\n';
        }
    }
    if(found){
        return elem;
    }else{
        return NULL;        
    }
}

void print_list(ptr_list_rooms l){
    ptr_list_rooms list = l;
    while(list->next != NULL){
        list=list->next;
        cout << list->room->x << " " << list->room->y << '\n';
    }
}