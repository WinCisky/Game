/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.h
 * Author: Simo
 *
 * Created on 11 marzo 2017, 13.43
 */

#ifndef MAP_H
#define MAP_H

#define CELL_SIZE 3

//LISTROOMS LIBRERIES
#include<ctime> // for the time() function
#include<cstdlib>
//(used for print the list)
#include <iostream>
//LISTROOMS LIBRERIES

#include "ListAvailableRooms.h"
#include "ListRooms.h"

using namespace std;

struct stanza {
    int x, y;
    char room[CELL_SIZE][CELL_SIZE];
    stanza* nord;
    stanza* sud;
    stanza* est;
    stanza* ovest;
    //up e down sono dei booleani
    //TO MODIFY
    stanza* up;
    stanza* down;
    bool visited;
};

//definisco la struttura universale per giocatore e npc

struct human {
    char name;
    int level;
    int life;
    int xp;
    int atk;
    int x;
    int y;
    int room_x;
    int room_y;
    int enemies_slained;
};

struct BigPlayer {
    human playerStats;
    stanza* playerRoom;
};

//LIST ENEMIES STRUCT


struct listEnemy {
  human enemy;
  int floor;
  listEnemy* pred;
  listEnemy* succ;
};

typedef listEnemy* ptrEnemy;

struct Node {
    human enemy;
    int floor;
    Node* next;
    Node* prev;
};

typedef Node* ptrN;

//!LISTENEMIES STRUCT

//LISTROOMS STRUCT

struct list_rooms{
    int level;
    bool has_stairs_up;
    bool has_stirs_down;
    stanza* room;
    list_rooms* next;
};

struct doors{
	stanza* nord;
	stanza* sud;
	stanza* est;
	stanza* ovest;
};

//!LISTROOMS STRUCT


typedef stanza* ptr_stanza;

class Map {
protected:
    int current_level, total_levels, n_basic_rooms;
    ptr_stanza home;
    ptr_stanza center;

    char stampa_mappa[13][13];
    
    //testa della lista dei nemici in tutti i livelli
    ptrN headListEnemy;
    //puntatore ad uno dei nemici della mappa
    //(usato per velocizzare la ricerca di un nemico)
    ptrN pointerListEnemy;

    void mostraMappa(ptr_stanza stanza);
    //GESTIONE PERSONAGGIO
    void increaseXp(human player, int amount);
    void decreaseHp(human player, int amount);
    void increaseHp(human player, int amount);
    
    //LISTENEMIES LIST
    ptrN listEnemies;
public:
    //List AllEnemies = new List();
    bool GameOver;
    bool Victory;
    //setup iniziale della mappa con n stanze
    Map(int rooms);

    //aggiungo una stanza
    //ritorn la stanza appena creata a partire dalla stanza data e la posizione alla quale inserirla
    //(ha le scale al prossimo livello?)
    ptr_stanza InsertRoom(ptr_stanza actual_room, char direction, bool has_stairs);

    //cerco la stanza data la pos di questa
    //devo partire dal centro del livello a cercare
    bool SearchRoom(ptr_stanza stanza, char dir, int x, int y);

    bool RoomFound(ptr_stanza stanza, int x, int y);

    //parto dal liv precedente a creare il nuovo livello
    //creo una lista delle pos a partire dalle quali posso creare delle stanza e ne scelgo una a ccaso
    //scelto l'elemento dalla lista (a caso) chiamo la funzione InsertRoom con relativi parametri
    void CreateLevel(ptr_stanza actual_room);

    //mostra le stanze della mappa ricorsivamente
    void ShowMap();

    //RESSETTA LA MAPPA
    void resetMap();
    //INIZIALIZZA LA MAPPA (dir=N -> crea la stanza a nord , S, E, W, C)
    void initMap(char dir, ptr_stanza room);
    //RIEMPIE LA MAPPA
    void fillMap(ptr_stanza room);
    //MOSTRA LA MAPPA
    // è necessario tornare il puntatore per effettuare il cambio di stanza nel caso in cui si trovino le scale
    BigPlayer stampaMap(ptr_stanza room, human Player);

    //support function for initializing the room
    ptr_stanza getCenter();

    //gestico lo spostamento del giocatore
    BigPlayer EvalutatePlayerMovemet(char c, ptr_stanza room, human Player);

    void showEnemies(ptr_stanza r);
    
    human MoveEnemies(ptrN enemy,human player);
};


//LIST ENEMIES FUNCTIONS


// ATTENZIONE: il primo elemento e' vuoto
// per semplificare il primo elemento deve avere livello (-1)


ptrN initializeList(ptrN head);

ptrN insert(ptrN h, human human, int floor);

bool empty(ptrN h);

ptrN next(ptrN p);

ptrN prev(ptrN p);

human read(ptrN p);

void write(ptrN p,human human, int v);

ptrN remove(ptrN l,ptrN p);

ptrN getEnemy(ptrN enemy, int x, int y, int level);

//se non ci sono nemici del livello giusto va in loop
ptrN firstEnemy(ptrN enemy, int liv);

ptrN lastEnemy(ptrN enemy, int liv);

int enemiesLeft(ptrN h, int level);

void print(ptrN h);

//!LISTENEMIES FUNCTIONS

//LISTROOMS FUNCTIONS

typedef list_rooms* ptr_list_rooms;
typedef doors* ptr_doors;
typedef stanza* ptr_stanza;

//insert an element at the end of the list
//useful for creating the enemies in the level
ptrN insert_elem(ptr_list_rooms list, int l, bool up, bool down, stanza* r,ptrN listEnemy, bool firstRoom);

//search first element of level x

//search element with x y coordinates from level x(pos)
ptr_list_rooms search_return_elem(ptr_list_rooms head, int x, int y);

//is the element in the list? (search from pos)

//it seems to be useless because on the Map class there's another function that
//automatically create the bridge between the new room and the old but 
//if the map is large enough this function is able to scan all directions in order
//to find all the possible neighbours
//search for the possible doors(close rooms to the x y pos)
ptr_doors search_doors(ptr_list_rooms list, int x, int y);

//search for the possible doors using the direction to scan for the next door
ptr_doors search_next_doors(ptr_list_rooms list, int x, int y, char dir);

//update the neighbours reference
void update_neighbours(ptr_stanza r, ptr_doors d);

//print the list
void print_list(ptr_list_rooms l);

//!LISTROOMS FUNCTIONS

bool Distance1(human a, human b);

#endif /* MAP_H */