
// License

#include <cstdlib>
#include <iostream>
#include "ListAvailableRooms.h"
#include "Map.h"
#include "Dice.h"

using namespace std;

int main(int argc, char** argv) {
    Map map(7);
    //return 0;
    ptr_stanza player = map.getCenter();
    human Player = {'P',3,0,0};
    //map.ShowMap();
    map.stampaMap(player, Player);
    char c;
    while(true){
        //cout << "x: " << player->x << " y: " << player->y << '\n';
        //cout << "x: " << Player.x << " y: " << Player.y << '\n';
        cin >> c;
        switch(c){
            case 'w':
                if(Player.y == 1 && Player.x == 0){
                    if(player->nord!=NULL){
                        player=player->nord;
                        Player.x = 0;
                        Player.y = -1;
                    }
                }else{
                    if(Player.y < 1){
                        Player.y++;
                    }
                }
                break;
            case 's':
                if(Player.y == -1 && Player.x == 0){
                    if(player->sud!=NULL){
                        player=player->sud;
                        Player.x = 0;
                        Player.y = 1;
                    }
                }else{
                    if(Player.y > -1){
                        Player.y--;
                    }
                }
                break;
            case 'd':
                if(Player.y == 0 && Player.x == 1){
                    if(player->est!=NULL){
                        player=player->est;
                        Player.x = -1;
                        Player.y = 0;
                    }
                }else{
                    if(Player.x < 1){
                        Player.x++;
                    }
                }
                break;
            case 'a':
                if(Player.y == 0 && Player.x == -1){
                    if(player->ovest!=NULL){
                        player=player->ovest;
                        Player.x = 1;
                        Player.y = 0;
                    }
                }else{
                    if(Player.x > -1){
                        Player.x--;
                    }
                }
        }
        map.stampaMap(player, Player);
    }
    return 0;
}