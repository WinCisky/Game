/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <stdlib.h>
#include <valarray> 
#include "Map.h"
#include "ListAvailableRooms.h"
#include "Dice.h"
//#include "ListRooms.h"
#include "ListEnemies.h"

#define V '|'//■
#define H '-'//■
const int pos = 13;

using namespace std;


Dice d1;

void Map::increaseXp(human player, int amount) {
    int exp = player.xp;
    int total_exp = exp + amount;
    if (total_exp < 100) {
        player.xp = total_exp;
    } else {
        while (total_exp > 100) {
            total_exp -= 100;
            player.atk++;
            player.xp = 0;
            player.level++;
            player.life = 10 + (player.level * 3);
        }
        player.xp = total_exp;
    }
}

void Map::increaseHp(human player, int amount) {
    if (player.life + amount >= (10 + (player.level * 3))) {
        player.life = (10 + (player.level * 3));
    } else {
        player.life += amount;
    }
}

void Map::decreaseHp(human player, int amount) {
    if (player.life - amount <= 0) {
        GameOver = true;
    } else {
        player.life -= amount;
    }
}

Map::Map(int rooms) {
    GameOver = false;
    Victory = false;
    n_basic_rooms = rooms;
    ptr_list_rooms rooms_list = new(list_rooms);
    rooms_list->next = NULL;
    //inizializzo la lista dei nemici
    initializeList(headListEnemy);
    pointerListEnemy = headListEnemy;
    //creo il liv 0
    home = new stanza;
    home->nord = NULL;
    home->sud = NULL;
    home->est = NULL;
    home->ovest = NULL;
    home->x = 0;
    home->y = 0;
    home->up = NULL;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            home->room[i][j] = ' ';
        }
    }
    //il centro del livello attuale è uguale alla prima stanza della mappa
    center = home;
    current_level = 1;
    total_levels = 1;
    //creo la lista delle posizioni disponibili dove ampliare la mappa
    ptr l = new list;
    l->next = NULL;
    //inserisco nella lista le pos
    insertTail(l, 'N', 0, 0);
    insertTail(l, 'S', 0, 0);
    insertTail(l, 'E', 0, 0);
    insertTail(l, 'W', 0, 0);
    
    listEnemies = new Node;
    listEnemies = initializeList(listEnemies);
    
    listEnemies = insert_elem(rooms_list, total_levels, false, false, center, listEnemies, true);
    Dice d;
    //cout << getLength(l) << '\n';
    //stampa(l);
    //cout << '\n';
    //creo le altre stanze
    for (int i = 0; i < rooms; i++) {
        //scelgo un elemento dalla lista
        int item = d.RandInt(getLength(l)) + 1;
        //cout << item << "\n";
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
            bool stairs = (rooms - i == 1);

            //InsertRoom(room_to_ins->room, elem->dir, false);
            // NEMICI .
            listEnemies = insert_elem(rooms_list, total_levels, stairs, false, InsertRoom(room_to_ins->room, elem->dir, false),listEnemies,false);
            //aggiungo gli altri elementi alla lista delle possibili posizioni dalle quali scegliere la stanza

            //DEVO CONTROLLARE CHE NON CI SIANO LE STANZE (SE CI SONO NON LE DEVO AGGIUNGERE ALLA LISTA)

            ptr_doors next_doors = search_next_doors(rooms_list, elem->x, elem->y, elem->dir);
            add_elements(l, elem->dir, elem->x, elem->y, (next_doors->nord != NULL), (next_doors->sud != NULL), (next_doors->est != NULL), (next_doors->ovest != NULL));
            //stampa(l);
        }
    }
    //print_list(rooms_list);
    //stampa(l);
    cout << "LEVEL " << total_levels << " CREATED!" << '\n';
}

bool Map::RoomFound(ptr_stanza stanza, int x, int y) {
    bool found = false;
    //cerco a nord
    //cerco a sud
    //cerco ad est
    //cerco ad ovest
    //cout << "ok";
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
    switch (dir) {
            //devo inserire il contenuto delle stanze 
            //in stampa_mappa alla relativa posizione
        case 'C':
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    stampa_mappa[7 - j][5 + i] = room->room[i][j];
                    if (room->room[i][j] == 's') {
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
            if (room->nord == NULL) {
                stampa_mappa[4][6] = H;
            }
            if (room->sud == NULL) {
                stampa_mappa[8][6] = H;
            }
            if (room->est == NULL) {
                stampa_mappa[6][8] = V;
            }
            if (room->ovest == NULL) {
                stampa_mappa[6][4] = V;
            }
            break;
        case 'W':
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    stampa_mappa[7 - j][1 + i] = room->ovest->room[i][j];
                }
            }
            stampa_mappa[4][1] = H;
            stampa_mappa[4][3] = H;
            stampa_mappa[8][1] = H;
            stampa_mappa[8][3] = H;
            stampa_mappa[5][0] = V;
            stampa_mappa[7][0] = V;
            if (room->ovest->ovest == NULL) {
                stampa_mappa[6][0] = V;
            }
            if (room->ovest->nord == NULL) {
                stampa_mappa[4][2] = H;
            }
            if (room->ovest->sud == NULL) {
                stampa_mappa[8][2] = H;
            }
            break;
        case 'E':
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    stampa_mappa[7 - j][9 + i] = room->est->room[i][j];
                }
            }
            stampa_mappa[4][9] = H;
            stampa_mappa[4][11] = H;
            stampa_mappa[8][9] = H;
            stampa_mappa[8][11] = H;
            stampa_mappa[5][12] = V;
            stampa_mappa[7][12] = V;
            if (room->est->est == NULL) {
                stampa_mappa[6][12] = V;
            }
            if (room->est->nord == NULL) {
                stampa_mappa[4][10] = H;
            }
            if (room->est->sud == NULL) {
                stampa_mappa[8][10] = H;
            }
            break;
        case 'S':
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    stampa_mappa[11 - j][5 + i] = room->sud->room[i][j];
                }
            }
            stampa_mappa[9][4] = V;
            stampa_mappa[9][8] = V;
            stampa_mappa[11][4] = V;
            stampa_mappa[11][8] = V;
            stampa_mappa[12][5] = H;
            stampa_mappa[12][7] = H;
            if (room->sud->sud == NULL) {
                stampa_mappa[12][6] = H;
            }
            if (room->sud->est == NULL) {
                stampa_mappa[10][8] = V;
            }
            if (room->sud->ovest == NULL) {
                stampa_mappa[10][4] = V;
            }
            break;
        case 'N':
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    stampa_mappa[3 - j][5 + i] = room->nord->room[i][j];
                }
            }
            stampa_mappa[0][5] = H;
            stampa_mappa[0][7] = H;
            stampa_mappa[1][4] = V;
            stampa_mappa[1][8] = V;
            stampa_mappa[3][4] = V;
            stampa_mappa[3][8] = V;
            if (room->nord->nord == NULL) {
                stampa_mappa[0][6] = H;
            }
            if (room->nord->est == NULL) {
                stampa_mappa[2][8] = V;
            }
            if (room->nord->ovest == NULL) {
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


void Map::showEnemies(ptr_stanza r){
    ptrN e;
    e = getEnemy(listEnemies, r->x, r->y,current_level);
    if(e!=NULL){
        //cout << "The enemy name is: " << e->enemy.name<< " and the position is: " << e->enemy.x << ","<<e->enemy.y<< "\n";
        stampa_mappa[6 - e->enemy.y][6 + e->enemy.x] = e->enemy.name;
    }
    if (r->nord != NULL) {
        e = getEnemy(listEnemies,r->nord->x,r->nord->y,current_level);
        if(e!=NULL){
            stampa_mappa[2 - e->enemy.y][6 + e->enemy.x] = e->enemy.name;
        }
    }
    if (r->sud != NULL) {
        e = getEnemy(listEnemies,r->sud->x,r->sud->y,current_level);
        if(e!=NULL){
            stampa_mappa[10 - e->enemy.y][6 + e->enemy.x] = e->enemy.name;
        }
    }
    if (r->est != NULL) {
        e = getEnemy(listEnemies,r->est->x,r->est->y,current_level);
        if(e!=NULL){
            stampa_mappa[6 - e->enemy.y][10 + e->enemy.x] = e->enemy.name;
        }
    }
    if (r->ovest != NULL) {
        e = getEnemy(listEnemies,r->ovest->x,r->ovest->y,current_level);
        if(e!=NULL){
            stampa_mappa[6 - e->enemy.y][2 + e->enemy.x] = e->enemy.name;
        }
    }
}

void Map::fillMap(ptr_stanza room) {
    //ATTENZIONE LE DIREZIONI SONO INVERTITE!
    //TO FIX
    initMap('C', room);
    if (room->nord != NULL) {
        initMap('N', room);
    }
    if (room->sud != NULL) {
        initMap('S', room);
    }
    if (room->est != NULL) {
        initMap('E', room);
    }
    if (room->ovest != NULL) {
        initMap('W', room);
    }
    
    //MOSTRO I NEMICI
    
    showEnemies(room);

}

bool Distance1(human a, human b){
    if(a.room_x==b.room_x&&a.room_y==b.room_y){
        if(a.y==b.y){
            if(abs(b.x)+abs(a.x)==1){
                //cout << "Distance is 1" << "\n";
                return true;
            }
        }else if(a.x==b.x){
            if(abs(b.y)+abs(a.y)==1){
                //cout << "Distance is 1" << "\n";
                return true;
            }
        }
    }else{
        if((a.room_x-b.room_x==1)&&(a.room_y-b.room_y==0)){
            if(a.x==-1&&a.y==0&&b.x==1&&b.y==0){
                //cout << "Distance is 1" << "\n";
                return true;
            }
        }else if((a.room_x-b.room_x==-1)&&(a.room_y-b.room_y==0)){
            if(a.x==1&&a.y==0&&b.x==-1&&b.y==0){
                //cout << "Distance is 1" << "\n";
                return true;
            }
        }else if((a.room_x-b.room_x==0)&&(a.room_y-b.room_y==1)){
            if(a.x==0&&a.y==-1&&b.x==0&&b.y==1){
                //cout << "Distance is 1" << "\n";
                return true;
            }
        }else if((a.room_x-b.room_x==0)&&(a.room_y-b.room_y==-1)){
            if(a.x==0&&a.y==1&&b.x==0&&b.y==-1){
                //cout << "Distance is 1" << "\n";
                return true;
            }
        }
    }
    return false;
}

human Map::MoveEnemies(ptrN enemy,human player){
    //FORSE DOVREI METTERCI UN PO DI LOGICA
    //TIPO VAI VERSO IL PERSONAGGIO
    if(!empty(enemy)){
        ptrN p = enemy->next;
        while(p!=enemy){
            if(p->floor==current_level){   
                /*
                if(p->enemy.x<1){
                    p->enemy.x++;
                }
                */
                if(Distance1(player,p->enemy)){
                    //attacca il giocatore
                    player.life -= p->enemy.atk;
                    cout << "Watch out you have been hit! \n";
                    if(player.life <= 0){
                        GameOver = true;
                    }
                    //cout << "player attacked: " << p->enemy.atk << " " << player.life << "\n" ;
                }else if(p->enemy.name!='E'){
                    //muoviti a caso all'interno della stanza
                    int direction_of_movement = d1.RandInt(4);
                    bool moved = false;
                    while(!moved){
                        switch(direction_of_movement){
                            case 0://up
                                if(p->enemy.y<1){
                                    moved = true;
                                    p->enemy.y++;
                                }else{
                                    direction_of_movement++;
                                }
                                break;
                            case 1://down
                                if(p->enemy.y>-1){
                                    moved = true;
                                    p->enemy.y--;
                                }else{
                                    direction_of_movement++;
                                }
                                break;
                            case 2://left
                                if(p->enemy.x>-1){
                                    moved = true;
                                    p->enemy.x--;
                                }else{
                                    direction_of_movement++;
                                }
                                break;
                            case 3://right
                                if(p->enemy.x<1){
                                    moved = true;
                                    p->enemy.x++;
                                }else{
                                    direction_of_movement=0;
                                }
                                break;
                        }
                    }
                }
            }
            p=p->next;
        }
    }
    return player;
}

BigPlayer Map::stampaMap(ptr_stanza room, human Player) {
    //SCALE
    //cambio livello
    if (stampa_mappa[6 - Player.y][6 + Player.x] == 'S') {
        if (room->up == NULL) {
            //creo il livello successivo
            CreateLevel(room);
        }
        //il giocatore si ritrova al liv successivo
        room = room->up;
        current_level++;
        room->room[1][1] = 's';
        //cout << room->x << " " << room->y << " " << level << '\n';
    } else if (stampa_mappa[6 - Player.y][6 + Player.x] == 's') {
        room = room->down;
        current_level--;
    }
    //AZIONI NEMICI
    Player.room_x = room->x;
    Player.room_y = room->y;
    Player = MoveEnemies(listEnemies,Player);
    //MOSTRO LA SITUAZIONE AGGIORNATA
    if (!GameOver) { //ho perso?
        cout << "Lvl: " << Player.level << "\t \t Attack: " << Player.atk << "\t Hp: " << Player.life << "\n";
        cout << "Kills: " << Player.enemies_slained << "\t Exp: " << Player.xp << "/100" << "\t Floor: " << current_level << "\n";
        //mappa vuota
        resetMap();
        //pareti & scale & nemici
        fillMap(room);
        stampa_mappa[6 - Player.y][6 + Player.x] = Player.name;

        int h, b;
        for (h = 0; h < pos; h++) {
            for (b = 0; b < pos; b++) {
                cout << stampa_mappa[h][b] << " ";
            }
            cout << "\n";
        }
        BigPlayer result;
        result.playerRoom = room;
        result.playerStats = Player;
        return result;
    } else {
        if(!Victory){
            cout << "DEAD END! \n";
        }else{
            cout << "CONGRATULATIONS YOU CLEARED THE GAME! \n";
        }
        BigPlayer p;
        return p;
    }

}

BigPlayer Map::EvalutatePlayerMovemet(char c, ptr_stanza player, human Player) {
    // !!!TO DO :
    // devo valutare se il personaggio incontra un nemico
    // se la nuova posizione del giocatore corrisponde alla pos di un nemico della
    // lista allora non faccio muovere il giocatore ma vado a diminuire la vita del 
    // nemico (-atk)
    bool has_attacked = false;
    if(!empty(listEnemies)){
        ptrN p = listEnemies->next;
        while(p!=listEnemies){
            if(p->floor==current_level){
                if(Distance1(p->enemy,Player)){
                    p->enemy.life -= Player.atk;
                    cout << "Enemy slained! \n";
                    if(p->enemy.life<=0){
                        if(p->enemy.name=='E'){
                            GameOver = true;
                            Victory = true;
                        }else{
                            p->floor = -1;
                            //nemico sconfitto
                            //aumenta xp
                            Player.enemies_slained++;
                            Player.xp += 25;
                            if(Player.xp >= 100){
                                Player.level++;
                                Player.atk += 1;
                                //cout << "level of the player: " << Player.level << "\n";
                                Player.life += Player.level*2;
                                Player.xp = 0;
                            }
                        }
                    }
                    has_attacked =true;
                }
            }
            p=p->next;
        }
    }
    if(!has_attacked){
        switch (c) {
            case 'w':
                if (Player.y == 1 && Player.x == 0) {
                    if (player->nord != NULL) {
                        player = player->nord;
                        Player.x = 0;
                        Player.y = -1;
                    }
                } else {
                    if (Player.y < 1) {
                        Player.y++;
                    }
                }
                break;
            case 's':
                if (Player.y == -1 && Player.x == 0) {
                    if (player->sud != NULL) {
                        player = player->sud;
                        Player.x = 0;
                        Player.y = 1;
                    }
                } else {
                    if (Player.y > -1) {
                        Player.y--;
                    }
                }
                break;
            case 'd':
                if (Player.y == 0 && Player.x == 1) {
                    if (player->est != NULL) {
                        player = player->est;
                        Player.x = -1;
                        Player.y = 0;
                    }
                } else {
                    if (Player.x < 1) {
                        Player.x++;
                    }
                }
                break;
            case 'a':
                if (Player.y == 0 && Player.x == -1) {
                    if (player->ovest != NULL) {
                        player = player->ovest;
                        Player.x = 1;
                        Player.y = 0;
                    }
                } else {
                    if (Player.x > -1) {
                        Player.x--;
                    }
                }
        }
    }
    //return di due valori
    //(posizione giocatore e stanza)
    BigPlayer summary;
    summary.playerRoom = player;
    summary.playerStats = Player;
    return summary;
}

// MAP PRINT FUNCTIONS

ptr_stanza Map::getCenter() {
    return center;
}

void Map::CreateLevel(ptr_stanza actual_room) {
    if(total_levels==9){
        //BOSS FIGHT
        //Aggiorno il livello
        total_levels++;
        //Creo le due stanze
        ptr_stanza newRoom = new stanza;
        ptr_stanza bossRoom = new stanza;
        newRoom->x = 0;
        newRoom->y = 0;
        newRoom->down = actual_room;
        actual_room->up = newRoom;
        newRoom->nord = bossRoom;
        newRoom->sud = NULL;
        newRoom->est = NULL;
        newRoom->ovest = NULL;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                newRoom->room[i][j] = ' ';
            }
        }
        center = newRoom;
        bossRoom->x = 0;
        bossRoom->y = 1;
        bossRoom->down = NULL;
        bossRoom->up = NULL;
        bossRoom->nord = NULL;
        bossRoom->sud = newRoom;
        bossRoom->est = NULL;
        bossRoom->ovest = NULL;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                bossRoom->room[i][j] = ' ';
            }
        }
        //Creo il boss
        human boss = {'E', 0, 100, 0, 50, 0, 0, bossRoom->x, bossRoom->y, 0};
        //aggiungilo alla lista dei nemici
        insert(listEnemies, boss, total_levels);
    }else{
        int rooms = (n_basic_rooms + (++total_levels * 2));
        ptr_list_rooms rooms_list = new(list_rooms);
        rooms_list->next = NULL;
        ptr_stanza newRoom = new stanza;
        newRoom->x = 0;
        newRoom->y = 0;
        newRoom->down = actual_room;
        actual_room->up = newRoom;
        newRoom->nord = NULL;
        newRoom->sud = NULL;
        newRoom->est = NULL;
        newRoom->ovest = NULL;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                newRoom->room[i][j] = ' ';
            }
        }
        center = newRoom;
        ptr l = new list;
        l->next = NULL;
        insertTail(l, 'N', 0, 0);
        insertTail(l, 'S', 0, 0);
        insertTail(l, 'E', 0, 0);
        insertTail(l, 'W', 0, 0);    
        listEnemies = insert_elem(rooms_list, total_levels, false, false, center, listEnemies,true);
        Dice d;
        for (int i = 0; i < rooms; i++) {
            int item = d.RandInt(getLength(l)) + 1;
            ptr elem = getElement(l, item);
            deletePos(l, item);
            ptr_list_rooms room_to_ins = search_return_elem(rooms_list, elem->x, elem->y);
            if (room_to_ins == NULL) {
                cout << "error \n";
            } else {
                bool stairs = (rooms - i == 1);
                // NEMICI .
                listEnemies = insert_elem(rooms_list, total_levels, stairs, false, InsertRoom(room_to_ins->room, elem->dir, false),headListEnemy,false);
                ptr_doors next_doors = search_next_doors(rooms_list, elem->x, elem->y, elem->dir);
                add_elements(l, elem->dir, elem->x, elem->y, (next_doors->nord != NULL), (next_doors->sud != NULL), (next_doors->est != NULL), (next_doors->ovest != NULL));
            }
        }
        //cout << "\n";
        //print(listEnemies);
        cout << "LEVEL " << total_levels << " CREATED!" << '\n';
    }
}



//LISTENEMIES FUNCTIONS
ptrN initializeList(ptrN head) {
    head->floor = -1;
    head->next = head;
    head->prev = head;
    return head;
}

ptrN insert(ptrN h, human human, int floor) {
    ptrN n = new Node;
    n->enemy = human;
    n->floor = floor;
    n->next = h;
    h->prev->next = n;
    h->prev = n;
    return n;
}

bool empty(ptrN h) {
    return ((h->next == h)&&(h->prev == h));
}

ptrN next(ptrN p) {
    return p->next;
}

ptrN prev(ptrN p) {
    return p->prev;
}

human read(ptrN p) {
    return p->enemy;
}

void write(ptrN p, human human, int v) {
    p->enemy = human;
    p->floor = v;
}

ptrN remove(ptrN l,ptrN p) {
    if(!empty(l)){
        ptrN p2 = l->next;
        while(p2!=l){
            if(p2==p){
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }
            p2 = p2->next;
        }
    }
    return l;
}

ptrN getEnemy(ptrN enemy, int x, int y, int level){
    if(!empty(enemy)){
        ptrN p = enemy->next;
        //cout << "pos x,y: " << enemy->enemy.x <<","<<enemy->enemy.y<< "\n";
        bool found = false;
        while(p!=enemy&&!found){
            if(p->floor==level){
                if(p->enemy.room_x==x&&p->enemy.room_y==y){    
                    return p;
                }
            }
            p=p->next;
        }
        return NULL;
    }else{
        return NULL;
    }
}

ptrN firstEnemy(ptrN enemy, int liv) {
    ptrN p = enemy;
    if (!empty(p)) {
        //1) sono gia su un nemico col livello giusto
        //2) sono piu' avanti
        while (p->floor >= liv) {
            p = p->prev;
        }
        while (p->next->floor < liv) {
            p = p->next;
        }
        return p->next;
        //3) sono piu' indietro
    } else {
        return NULL;
    }
}

// -- da correggere --

int enemiesLeft(ptrN h, int level) {
    if (h != NULL) {
        ptrN p = h;
        int count = 0;
        while (p->next != NULL && p->floor <= level) {
            if (p->floor == level) {
                count++;
            }
            p = p->next;
        }
        if (p->floor == level) {
            count++;
        }
        return count;
    } else {
        return 0;
    }
}
// -- !da correggere --

//stampo la lista

void print(ptrN h) {
    if (h != NULL) {
        ptrN n = h->next;
        while (n != h) {
            cout << n->enemy.name << " floor: " << n->floor << "pos x,y:" << n->enemy.x << "," << n->enemy.y << " \n";
            n = n->next;
        }
    }
}

//!LISTENEMIES FUNCTIONS

//LISTROOMS FUNCTIONS

ptrN insert_elem(ptr_list_rooms list, int l, bool up, bool down, stanza* r, ptrN listEnemy, bool firstRoom) {
    
    //cout << "Inserting element: " << r->x << " " << r->y << '\n';
    ptr_list_rooms newElement = new (list_rooms);
    newElement->has_stairs_up = up;
    newElement->has_stirs_down = down;
    newElement->room = r;
    newElement->level = l;
    newElement->next = NULL;
    //devo cercare se ha i vicini
    //cout << "Searching for possible neighbors \n";
    ptr_doors doors = search_doors(list, r->x, r->y);
    //cout << "N: " <<(r->nord==NULL)<< " S: " <<(r->sud==NULL)<< " E: " <<(r->est==NULL)<< " W: " <<(r->ovest==NULL)<< "\n";
    //cout << "N: " <<(doors->nord==NULL)<< " S: " <<(doors->sud==NULL)<< " E: " <<(doors->est==NULL)<< " W: " <<(doors->ovest==NULL)<< "\n";
    newElement->room->nord = doors->nord;
    newElement->room->sud = doors->sud;
    newElement->room->est = doors->est;
    newElement->room->ovest = doors->ovest;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            newElement->room->room[i][j] = ' ';
        }
    }
    
    //cout << r->x << " " << r->y << "\n";
    
    if (up) {
        //posizione delle scale 
        //cout << r->x << " " << r->y << '\n';
        newElement->room->room[1][1] = 'S';
        //sto creando la nuova stanza, questa non deve avere una casella sovrastante in quanto questa verrà creata
        //quando si passa sulle scale per la prima volta
        newElement->room->up = NULL;
    }else{ // non genero nemici nella prima stanza e nella stanza dove ci sono le scale
        if((!firstRoom&&!down)&&!up){
            //CREO A CASO DEI NEMICI
            int item = d1.RandInt(100) + 1;
            //cout << item << "\n";
            //cout << item << " <-(random number)\n";
            if (item < 80) {
                //crea il nemico
                human enemy = {'e', 0, 1*l, 0, 1*l, 0, 0, r->x, r->y, 0};
                //aggiungilo alla lista dei nemici
                insert(listEnemy, enemy, l);
                //cout << item << " is at level " << l << "\n";
                //cout << getEnemy(listEnemy,r->x,r->y) << " " << (getEnemy(listEnemy,r->x,r->y) == NULL) << "\n";
            }
        }
    }
    ptr_list_rooms lista = list;
    while (lista->next != NULL) {
        lista = lista->next;
    }
    lista->next = newElement;
    update_neighbours(r, doors);
    
    return listEnemy;
}

ptr_list_rooms search_return_elem(ptr_list_rooms head, int x, int y) {
    bool found = false;
    ptr_list_rooms elem = head;
    ptr_list_rooms found_elem = NULL;
    while (!found && (elem->next != NULL)) {
        elem = elem->next;
        //cout << "Searching: " << x << " " << y << " found: " << elem->room->x << " " << elem->room->y;
        if ((elem->room->x == x) && (elem->room->y == y)) {
            found = true;
            found_elem = elem;
            //cout << " yey! \n";
        } else {
            //cout << '\n';
        }
    }
    return found_elem;
}

ptr_doors search_next_doors(ptr_list_rooms list, int x, int y, char dir) {
    ptr_doors final_door = new(doors);
    final_door->est = NULL;
    final_door->nord = NULL;
    final_door->ovest = NULL;
    final_door->sud = NULL;
    switch (dir) {
        case 'N':
            final_door = search_doors(list, x, y + 1);
            break;
        case 'S':
            final_door = search_doors(list, x, y - 1);
            break;
        case 'E':
            final_door = search_doors(list, x + 1, y);
            break;
        case 'W':
            final_door = search_doors(list, x - 1, y);
            break;
    }
    return final_door;
}

ptr_doors search_doors(ptr_list_rooms list, int x, int y) {
    ptr_list_rooms lista = list;
    ptr_doors found_doors = new(doors);
    found_doors->est = NULL;
    found_doors->ovest = NULL;
    found_doors->nord = NULL;
    found_doors->sud = NULL;
    while (lista->next != NULL) {
        lista = lista->next;
        int fx, fy;
        fx = lista->room->x;
        fy = lista->room->y;
        if (fx == (x + 1)) {
            if (fy == y) {
                //est
                found_doors->est = lista->room;
            }
        } else if (fx == (x - 1)) {
            if (fy == y) {
                //ovest
                found_doors->ovest = lista->room;
            }
        } else if (fx == x) {
            if (fy == (y + 1)) {
                //nord
                found_doors->nord = lista->room;
            } else if (fy == (y - 1)) {
                //sud
                found_doors->sud = lista->room;
            }
        }
    }
    return found_doors;
}

void update_neighbours(ptr_stanza r, ptr_doors d) {
    if (d->nord != NULL) {
        r->nord->sud = r;
    }
    if (d->sud != NULL) {
        r->sud->nord = r;
    }
    if (d->est != NULL) {
        r->est->ovest = r;
    }
    if (d->ovest != NULL) {
        r->ovest->est = r;
    }
}

void print_list(ptr_list_rooms l) {
    ptr_list_rooms list = l;
    while (list->next != NULL) {
        list = list->next;
        cout << list->room->x << " " << list->room->y << '\n';
    }
}

//!LISTROOMS FUNCTIONS
