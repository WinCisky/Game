/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "Map.h"
#include "ListAvailableRooms.h"
#include "Dice.h"

using namespace std;

Map::Map(int rooms) {
    //creo il liv 0
    home = new stanza;
    home->x = 0;
    home->y = 0;
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
    insertTail(l,'N', 0, 0);
    insertTail(l,'S', 0, 0);
    insertTail(l,'E', 0, 0);
    insertTail(l,'W', 0, 0);
    Dice d;
    cout << getLength(l) << '\n';
    stampa(l);
    cout << '\n';
    //creo le altre stanze
    for (int i = 0; i < rooms; i++) {
        //scelgo un elemento dalla lista
        int item = d.RandInt(getLength(l)) + 1;
        //cout << item;
        ptr elem = getElement(l, item);
        cout << elem->dir << '\n';
        //rimuovo l'elemento dalla lista
        deletePos(l, item);
        //creo la stanza
            //TODO
            //cerco dove attaccarla
            //controllo se ci sono collegamenti da fare
            //creo la nuova stanza
            InsertRoom(home, elem->dir, false);
        //aggiungo gli altri elementi alla lista
        add_elements(l, elem->dir ,elem->x, elem->y);
        //stampa(l);
        cout << '\n';
    }
    stampa(l);
}

ptr_stanza Map::SearchRoom(int x, int y){
    //devo cercare nelle 4 direzioni
    //TODO
    return NULL;
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
            newRoom->x = actual_room->x - 1;
            newRoom->y = actual_room->y;
            break;
        case 'W':
            actual_room->ovest = newRoom;
            newRoom->est = actual_room;
            newRoom->x = actual_room->x + 1;
            newRoom->y = actual_room->y;
            break;
    }
    return newRoom;
}

void Map::CreateLevel(ptr_stanza actual_room, int rooms) {

}

void Map::ShowRoom(char room[][3]) {

}

