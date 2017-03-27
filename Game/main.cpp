
// License

#include <cstdlib>
#include <iostream>
#include "ListAvailableRooms.h"
#include "Map.h"
#include "Dice.h"

using namespace std;

int main(int argc, char** argv) {
    Map map(5);
    ptr_stanza player = map.getCenter();
    map.ShowMap();
    map.stampaMap(player);
    char c;
    while(true){
        cout << "x: " << player->x << " y: " << player->y << '\n';
        cin >> c;
        switch(c){
            case 'w':
                if(player->nord!=NULL){
                    player=player->nord;
                }
                break;
            case 's':
                if(player->sud!=NULL){
                    player=player->sud;
                }
                break;
            case 'd':
                if(player->est!=NULL){
                    player=player->est;
                }
                break;
            case 'a':
                if(player->ovest!=NULL){
                    player=player->ovest;
                }
        }
        map.stampaMap(player);
    }
    return 0;
}