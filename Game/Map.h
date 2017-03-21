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

#include "ListAvailableRooms.h"

struct stanza{
	int x,y;
	char room[CELL_SIZE][CELL_SIZE];
	stanza* nord;
	stanza* sud;
	stanza* est;
	stanza* ovest;
        //up e down sono dei booleani
        //TO MODIFY
	stanza* up;
	stanza* down;
};

typedef stanza* ptr_stanza;

class Map{
protected:
	int level;
        ptr_stanza home;
        ptr_stanza center;
public:
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
	void CreateLevel(ptr_stanza actual_room, int rooms);
        
        //ogni volta che inserisco una stanza devo assicurarmi che tutti i possibili collegamenti siano effettuati
        //devo anche rimuovere dalla lista delle stanze instanziabili quelle collegate
        void CreateConnections(ptr_stanza room_to_connect, ptr l);

	//ritorno una stanza (modifico il vettore dato come parametro)
	void ShowRoom(char room[][3]);

	/*
	//aggiorno il gioco in base all'azione dell'utente
	void PlayerUpdate(char action);

	//aggiorno la mappa (Ai to develop)
	void MapUpdate();
	*/
};

#endif /* MAP_H */

