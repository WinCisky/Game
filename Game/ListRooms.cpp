/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ListRooms.h"

void insert_elem(ptr_list_rooms list, int l, bool up, bool down, stanza* r){
    cout << "Inserting element: " << r->x << " " << r->y << '\n';
    ptr_list_rooms newElement = new (list_rooms);
    newElement->has_stairs_up = up;
    newElement->has_stirs_down = down;
    newElement->room = r;
    newElement->level = l;
    newElement->next = NULL;
    //devo cercare se ha i vicini
    cout << "Searching for possible neighbors \n";
    ptr_doors doors = search_doors(list, r->x, r->y);
    cout << "N: " <<(r->nord==NULL)<< " S: " <<(r->sud==NULL)<< " E: " <<(r->est==NULL)<< " W: " <<(r->ovest==NULL)<< "\n";
    cout << "N: " <<(doors->nord==NULL)<< " S: " <<(doors->sud==NULL)<< " E: " <<(doors->est==NULL)<< " W: " <<(doors->ovest==NULL)<< "\n";
    newElement->room->nord=doors->nord;
    newElement->room->sud=doors->sud;
    newElement->room->est=doors->est;
    newElement->room->ovest=doors->ovest;
    ptr_list_rooms lista = list;
    while(lista->next != NULL){
        lista = lista->next;
    }
    lista->next = newElement;
    update_neighbours(r, doors);
}

ptr_list_rooms search_return_elem(ptr_list_rooms head, int x, int y){
    bool found = false;
    ptr_list_rooms elem = head;
    ptr_list_rooms found_elem = NULL;
    while(!found && (elem->next != NULL)){
        elem = elem->next;
        cout << "Searching: " << x << " " << y << " found: " << elem->room->x << " " << elem->room->y;
        if((elem->room->x == x) && (elem->room->y == y)){
            found = true;
            found_elem = elem;
            cout << " yey! \n";
        }else{
            cout << '\n';
        }
    }
    return found_elem;
}

ptr_doors search_next_doors(ptr_list_rooms list, int x, int y, char dir){
    ptr_doors final_door = new(doors);
    final_door->est=NULL;
    final_door->nord=NULL;
    final_door->ovest=NULL;
    final_door->sud=NULL;
    switch(dir){
        case 'N':
            final_door = search_doors(list, x, y+1);
            break;
        case 'S':
            final_door = search_doors(list, x, y-1);
            break;
        case 'E':
            final_door = search_doors(list, x+1, y);
            break;
        case 'W':
            final_door = search_doors(list, x-1, y);
            break;
    }
    return final_door;
}

ptr_doors search_doors(ptr_list_rooms list, int x, int y){
    ptr_list_rooms lista = list;
    ptr_doors found_doors = new(doors);
    found_doors->est=NULL;
    found_doors->ovest=NULL;
    found_doors->nord=NULL;
    found_doors->sud=NULL;
    while(lista->next != NULL){
        lista = lista->next;
        int fx,fy;
        fx = lista->room->x;
        fy = lista->room->y;
        if(fx==(x+1)){
            if(fy==y){
                //est
                found_doors->est=lista->room;
            }
        }else if(fx==(x-1)){
            if(fy==y){
                //ovest
                found_doors->ovest=lista->room;
            }
        }else if(fx==x){
            if(fy==(y+1)){
                //nord
                found_doors->nord=lista->room;
            }else if(fy==(y-1)){
                //sud
                found_doors->sud=lista->room;
            }
        }
    }
    return found_doors;
}

void update_neighbours(ptr_stanza r, ptr_doors d){
    if(d->nord!=NULL){
        r->nord->sud=r;
    }
    if(d->sud!=NULL){
        r->sud->nord=r;
    }
    if(d->est!=NULL){
        r->est->ovest=r;
    }
    if(d->ovest!=NULL){
        r->ovest->est=r;
    }
}

void print_list(ptr_list_rooms l){
    ptr_list_rooms list = l;
    while(list->next != NULL){
        list=list->next;
        cout << list->room->x << " " << list->room->y << '\n';
    }
}