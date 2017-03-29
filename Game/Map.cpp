/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "Map.h"
#include "ListAvailableRooms.h"
#include "Dice.h"
#include "ListRooms.h"

#define V '|'
#define H '-'
const int pos = 13;

using namespace std;

Map::Map(int rooms) {
    ptr_list_rooms rooms_list = new(list_rooms);
    rooms_list->next = NULL;
    //creo il liv 0
    home = new stanza;
    home->nord = NULL;
    home->sud = NULL;
    home->est = NULL;
    home->ovest = NULL;
    home->x = 0;
    home->y = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            home->room[i][j]=' ';
        }
    }
    //il centro del livello attuale è uguale alla prima stanza della mappa
    center = home;
    level = 0;
    ptr_stanza newRoom = new stanza;
    newRoom->x = 0;
    newRoom->y = 0;
    //creo la lista delle posizioni disponibili dove ampliare la mappa
    ptr l = new list;
    l->next = NULL;
    //inserisco nella lista le pos
    insertTail(l, 'N', 0, 0);
    insertTail(l, 'S', 0, 0);
    insertTail(l, 'E', 0, 0);
    insertTail(l, 'W', 0, 0);
    insert_elem(rooms_list, 0, false, false, center);
    Dice d;
    //cout << getLength(l) << '\n';
    //stampa(l);
    //cout << '\n';
    //creo le altre stanze
    for (int i = 0; i < rooms; i++) {
        //scelgo un elemento dalla lista
        int item = d.RandInt(getLength(l)) + 1;
        //cout << item;
        ptr elem = getElement(l, item);
        //cout << "Chosen room to add to the map: " << " " << elem->x << " " << elem->y << " -> " << elem->dir << '\n';
        //rimuovo l'elemento dalla lista
        deletePos(l, item);
        //creo la stanza
        //TODO
        //cerco dove attaccarla
        //controllo se ci sono collegamenti da fare
        //creo la nuova stanza
        //DIO CANE DEVO INSERIRE LA STANZA DA QUELLA ESTRATTA
        ptr_list_rooms room_to_ins = search_return_elem(rooms_list, elem->x, elem->y);
        if (room_to_ins == NULL) {
            cout << "error \n";
        } else {
            bool stairs = (rooms-i == 1);
            
            //InsertRoom(room_to_ins->room, elem->dir, false);
            insert_elem(rooms_list, 0, stairs, false, InsertRoom(room_to_ins->room, elem->dir, false));
            //aggiungo gli altri elementi alla lista delle possibili posizioni dalle quali scegliere la stanza

            //DEVO CONTROLLARE CHE NON CI SIANO LE STANZE (SE CI SONO NON LE DEVO AGGIUNGERE ALLA LISTA)

            ptr_doors next_doors = search_next_doors(rooms_list, elem->x, elem->y, elem->dir);
            add_elements(l, elem->dir, elem->x, elem->y, (next_doors->nord != NULL), (next_doors->sud != NULL), (next_doors->est != NULL), (next_doors->ovest != NULL));
            //stampa(l);
        }
    }
    //print_list(rooms_list);
    //stampa(l);
}

bool Map::RoomFound(ptr_stanza stanza, int x, int y) {
    bool found = false;
    //cerco a nord
    //cerco a sud
    //cerco ad est
    //cerco ad ovest
    cout << "ok";
    found = (SearchRoom(stanza->nord, 'N', x, y) || SearchRoom(stanza->sud, 'S', x, y) || SearchRoom(stanza->est, 'E', x, y) || SearchRoom(stanza->ovest, 'W', x, y));
    return found;
}

bool Map::SearchRoom(ptr_stanza stanza, char dir, int x, int y) {
    //devo cercare nelle 4 direzioni
    //TODO
    if (stanza->x == x && stanza->y == y) {
        return true;
    } else {
        switch (dir) {
                //se sto cercando ad ovest o ad est instanzio solamente un'altra ricerca solo ad ovest o ad est rispettivamente
                //se sto cercando a nord o a sud istanzio una ricerca a nord o a sud ed una ad est ed una ad ovest
            case 'N':
                if (stanza->nord != NULL) {
                    return (SearchRoom(stanza->nord, 'N', x, y) || SearchRoom(stanza->nord, 'E', x, y) || SearchRoom(stanza->nord, 'W', x, y));
                } else {
                    return false;
                }
                break;
            case 'S':
                if (stanza->sud != NULL) {
                    return (SearchRoom(stanza->sud, 'S', x, y) || SearchRoom(stanza->sud, 'E', x, y) || SearchRoom(stanza->sud, 'W', x, y));
                } else {
                    return false;
                }
                break;
            case 'E':
                if (stanza->est != NULL) {
                    return (SearchRoom(stanza->est, 'E', x, y));
                } else {
                    return false;
                }
                break;
            case 'W':
                if (stanza->ovest != NULL) {
                    return (SearchRoom(stanza->ovest, 'W', x, y));
                } else {
                    return false;
                }
                break;
        }
    }
}

ptr_stanza Map::InsertRoom(ptr_stanza actual_room, char direction, bool has_stairs) {
    //TO TEST
    ptr_stanza newRoom = new stanza;
    newRoom->nord = NULL;
    newRoom->sud = NULL;
    newRoom->est = NULL;
    newRoom->sud = NULL;
    //i puntatori sono null?
    if (has_stairs) {
        newRoom->room[1][1] = 'S';
    }
    switch (direction) {
        case 'N':
            actual_room->nord = newRoom;
            newRoom->sud = actual_room;
            newRoom->x = actual_room->x;
            newRoom->y = actual_room->y + 1;
            break;
        case 'S':
            actual_room->sud = newRoom;
            newRoom->nord = actual_room;
            newRoom->x = actual_room->x;
            newRoom->y = actual_room->y - 1;
            break;
        case 'E':
            actual_room->est = newRoom;
            newRoom->ovest = actual_room;
            newRoom->x = actual_room->x + 1;
            newRoom->y = actual_room->y;
            break;
        case 'W':
            actual_room->ovest = newRoom;
            newRoom->est = actual_room;
            newRoom->x = actual_room->x - 1;
            newRoom->y = actual_room->y;
            break;
    }
    return newRoom;
}

void Map::ShowMap() {
    cout << "The Map: \n" << center->x << " " << center->y << "\n";
    center->visited = true;
    if (center->nord != NULL) {
        mostraMappa(center->nord);
    }
    if (center->sud != NULL) {
        mostraMappa(center->sud);
    }
    if (center->est != NULL) {
        mostraMappa(center->est);
    }
    if (center->ovest != NULL) {
        mostraMappa(center->ovest);
    }
}

void Map::mostraMappa(ptr_stanza stanza) {
    if (!stanza->visited) {
        cout << stanza->x << " " << stanza->y << "\n";
        stanza->visited = true;

        if (stanza->nord != NULL) {
            mostraMappa(stanza->nord);
        }
        if (stanza->sud != NULL) {
            mostraMappa(stanza->sud);
        }
        if (stanza->est != NULL) {
            mostraMappa(stanza->est);
        }
        if (stanza->ovest != NULL) {
            mostraMappa(stanza->ovest);
        }
    }
}

// MAP PRINT FUNCTIONS

void Map::resetMap() {
    int i, j;
    for (i = 0; i < pos; i++) {
        for (j = 0; j < pos; j++) {
            stampa_mappa[i][j] = ' ';
        }
    }
}

void Map::initMap(char dir, ptr_stanza room) {
    
    //se ci sono le stanze le mostro altrimenti metto i muri
    switch(dir){
        //devo inserire il contenuto delle stanze 
        //in stampa_mappa alla relativa posizione
        case 'C':
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    stampa_mappa[7-j][5+i]=room->room[i][j];
                    if(room->room[i][j]=='S'){
                        cout << "C" << '\n';
                    }
                }
            }
            stampa_mappa[4][5] = H;
            stampa_mappa[4][7] = H;
            stampa_mappa[8][5] = H;
            stampa_mappa[8][7] = H;
            stampa_mappa[5][4] = V;
            stampa_mappa[5][8] = V;
            stampa_mappa[7][4] = V;
            stampa_mappa[7][8] = V;
            if(room->nord==NULL){
                stampa_mappa[4][6] = H;
            }
            if(room->sud==NULL){
                stampa_mappa[8][6] = H;
            }
            if(room->est==NULL){
                stampa_mappa[6][8] = V;
            }
            if(room->ovest==NULL){
                stampa_mappa[6][4] = V;
            }
            break;
        case 'W':
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    stampa_mappa[7-j][1+i]=room->ovest->room[i][j];
                    if(room->ovest->room[i][j]=='S'){
                        cout << "W" << '\n';
                    }
                }
            }
            stampa_mappa[4][1] = H;
            stampa_mappa[4][3] = H;
            stampa_mappa[8][1] = H;
            stampa_mappa[8][3] = H;
            stampa_mappa[5][0] = V;
            stampa_mappa[7][0] = V;
            if(room->ovest->ovest==NULL){
                stampa_mappa[6][0] = V;
            }
            if(room->ovest->nord==NULL){
                stampa_mappa[4][2] = H;
            }
            if(room->ovest->sud==NULL){
                stampa_mappa[8][2] = H;
            }
            break;
        case 'E':
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    stampa_mappa[7-j][9+i]=room->est->room[i][j];
                    if(room->est->room[i][j]=='S'){
                        cout << "E" << '\n';
                    }
                }
            }
            stampa_mappa[4][9] = H;
            stampa_mappa[4][11] = H;
            stampa_mappa[8][9] = H;
            stampa_mappa[8][11] = H;
            stampa_mappa[5][12] = V;
            stampa_mappa[7][12] = V;
            if(room->est->est==NULL){
                stampa_mappa[6][12] = V;
            }
            if(room->est->nord==NULL){
                stampa_mappa[4][10] = H;
            }
            if(room->est->sud==NULL){
                stampa_mappa[8][10] = H;
            }
            break;
        case 'S':
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    stampa_mappa[11-j][5+i]=room->sud->room[i][j];
                    if(room->sud->room[i][j]=='S'){
                        cout << "S" << '\n';
                    }
                }
            }
            stampa_mappa[9][4] = V;
            stampa_mappa[9][8] = V;
            stampa_mappa[11][4] = V;
            stampa_mappa[11][8] = V;
            stampa_mappa[12][5] = H;
            stampa_mappa[12][7] = H;
            if(room->sud->sud==NULL){
                stampa_mappa[12][6] = H;
            }
            if(room->sud->est==NULL){
                stampa_mappa[10][8] = V;
            }
            if(room->sud->ovest==NULL){
                stampa_mappa[10][4] = V;
            }
            break;
        case 'N':
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    stampa_mappa[3-j][5+i]=room->nord->room[i][j];
                    if(room->nord->room[i][j]=='S'){
                        cout << "N" << '\n';
                    }
                }
            }
            stampa_mappa[0][5] = H;
            stampa_mappa[0][7] = H;
            stampa_mappa[1][4] = V;
            stampa_mappa[1][8] = V;
            stampa_mappa[3][4] = V;
            stampa_mappa[3][8] = V;
            if(room->nord->nord==NULL){
                stampa_mappa[0][6] = H;
            }
            if(room->nord->est==NULL){
                stampa_mappa[2][8] = V;
            }
            if(room->nord->ovest==NULL){
                stampa_mappa[2][4] = V;
            }
            break;
    }
    
    /*
    
    for (int i = 0; i < pos; i++) {
        if (i % 4 == 0) {
            stampa_mappa[i][5] = H;
            stampa_mappa[i][7] = H;

            stampa_mappa[5][i] = V;
            stampa_mappa[7][i] = V;
        }
    }

    for (int i = 0; i < pos; i++) {
        if (i % 2 == 1) {
            stampa_mappa[4][i] = H;
            stampa_mappa[8][i] = H;

            stampa_mappa[i][4] = V;
            stampa_mappa[i][8] = V;
        }
    }
    */
}

void Map::fillMap(ptr_stanza room){
    //ATTENZIONE LE DIREZIONI SONO INVERTITE!
    //TO FIX
    initMap('C', room);
    if(room->nord!=NULL){
        initMap('N', room);
    }
    if(room->sud!=NULL){
        initMap('S', room);
    }
    if(room->est!=NULL){
        initMap('E', room);
    }
    if(room->ovest!=NULL){
        initMap('W', room);
    }
    
}

void Map::stampaMap(ptr_stanza room, human Player) {
    resetMap();
    
    fillMap(room);
    
    stampa_mappa[6-Player.y][6+Player.x]=Player.name;
    
    int h, b;
    for (h = 0; h < pos; h++) {
        for (b = 0; b < pos; b++) {
            cout << stampa_mappa[h][b] << " ";
        }
        cout << "\n";
    }
}

// MAP PRINT FUNCTIONS


ptr_stanza Map::getCenter(){
    return center;
}

void Map::CreateLevel(ptr_stanza actual_room, int rooms) {

}

