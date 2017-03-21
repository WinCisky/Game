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
    //il centro del livello attuale è uguale alla prima stanza della mappa
    center = home;
    bool c = (!center);
    bool n = (!center->nord);
    bool s = (!center->sud);
    bool e = (!center->est);
    bool w = (!center->ovest);
    cout << "is: " << c << n << s << e << w << '\n';
    level = 0;
    ptr_stanza newRoom = new stanza;
    newRoom->x = 0;
    newRoom->y = 0;
    //creo la lista delle posizioni disponibili dove ampliare la mappa
    ptr l = new list;
    l->next = NULL;
    //inserisco nella lista le pos
    insertTail(l,'N', 0, 0);
    insertTail(l,'S', 0, 0);
    insertTail(l,'E', 0, 0);
    insertTail(l,'W', 0, 0);
    insert_elem(rooms_list,0,false,false,center);
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
        cout << elem->dir << " " << elem->x << " " << elem->y << '\n';
        //rimuovo l'elemento dalla lista
        deletePos(l, item);
        //creo la stanza
        //TODO
        //cerco dove attaccarla
        //controllo se ci sono collegamenti da fare
        //creo la nuova stanza
        //DIO CANE DEVO INSERIRE LA STANZA DA QUELLA ESTRATTA
        ptr_list_rooms room_to_ins = search_return_elem(rooms_list, elem->x, elem->y);
        if(room_to_ins == NULL){
            cout << "error \n";
        }else{
            //InsertRoom(room_to_ins->room, elem->dir, false);
            //home non va bene dio spolpo
            insert_elem(rooms_list,0,false,false,InsertRoom(room_to_ins->room, elem->dir, false));
            //aggiungo gli altri elementi alla lista
            add_elements(l, elem->dir ,elem->x, elem->y);
            //stampa(l);
            cout << '\n';
        }
    }
    print_list(rooms_list);
    //stampa(l);
    bool c2 = (!center);
    bool n2 = (!center->nord);
    bool s2 = (!center->sud);
    bool e2 = (!center->est);
    bool w2 = (!center->ovest);
    cout << "is: " << c2 << n2 << s2 << e2 << w2 << '\n';
}

bool Map::RoomFound(ptr_stanza stanza, int x, int y){
    bool found = false;
    //cerco a nord
    //cerco a sud
    //cerco ad est
    //cerco ad ovest
    cout << "ok";
    found = (SearchRoom(stanza->nord,'N',x,y)||SearchRoom(stanza->sud,'S',x,y)||SearchRoom(stanza->est,'E',x,y)||SearchRoom(stanza->ovest,'W',x,y));
    return found;
}

bool Map::SearchRoom(ptr_stanza stanza, char dir, int x, int y){
    //devo cercare nelle 4 direzioni
    //TODO
    if(stanza->x == x && stanza->y == y){
        return true;
    }else{
        switch(dir){
            //se sto cercando ad ovest o ad est instanzio solamente un'altra ricerca solo ad ovest o ad est rispettivamente
            //se sto cercando a nord o a sud istanzio una ricerca a nord o a sud ed una ad est ed una ad ovest
            case 'N':
                if(stanza->nord != NULL){
                    return(SearchRoom(stanza->nord, 'N', x, y)||SearchRoom(stanza->nord, 'E', x, y)||SearchRoom(stanza->nord, 'W', x, y));
                }else{
                    return false;
                }
            break;
            case 'S':
                if(stanza->sud != NULL){
                    return(SearchRoom(stanza->sud, 'S', x, y)||SearchRoom(stanza->sud, 'E', x, y)||SearchRoom(stanza->sud, 'W', x, y));
                }else{
                    return false;
                }
            break;
            case 'E':
                if(stanza->est != NULL){
                    return(SearchRoom(stanza->est, 'E', x, y));
                }else{
                    return false;
                }
            break;
            case 'W':
                if(stanza->ovest != NULL){
                    return(SearchRoom(stanza->ovest, 'W', x, y));
                }else{
                    return false;
                }
            break;
        }
    }
}

void Map::CreateConnections(ptr_stanza room_to_connect, ptr l){
    //per ogni stanza cerco se ci sono quelle i cui puntatori sono nulli
    //si-> crea il collegamento.
    //no-> fai nulla.
    //TODO
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

void Map::CreateLevel(ptr_stanza actual_room, int rooms) {

}

void Map::ShowRoom(char room[][3]) {

}

