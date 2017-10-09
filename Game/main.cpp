
// License

#include <cstdlib>
#include <iostream>
#include "ListAvailableRooms.h"
#include "Map.h"
#include "Dice.h"
#include "ListEnemies.h"

using namespace std;

int main(int argc, char** argv) {    
    //creo la mappa con n stanze iniziali
    Map map(7);
    //posiziono la stanza del giocatore al centro
    ptr_stanza player = map.getCenter();
    //creo il giocatore con le statistiche iniziali
    human Player = {'P',1,5,0,1,0,0,0,0,0};
    cout << "Player spawned at pos x: " << Player.x << " y: " << Player.y << '\n';
    //mostro la mappa subito dopo la creazione
    BigPlayer result = map.stampaMap(player, Player);
    Player = result.playerStats;
    player = result.playerRoom;
    //input giocatore
    char c;
    //ciclo di gioco
    while(!map.GameOver){
            //debug
            //cout << "x: " << player->x << " y: " << player->y << '\n';
            //leggo il movimento del giocatore
            cin >> c;
            //muovo il giocatore
            BigPlayer summary = map.EvalutatePlayerMovemet(c, player, Player);
            player = summary.playerRoom;
            Player = summary.playerStats;
            //mostro la mappa aggiornata
            BigPlayer result = map.stampaMap(player, Player);
            Player = result.playerStats;
            player = result.playerRoom;
            //^ aggiungere i nemici, armi, attacco, difesa, vite
    }
    
    //aspetto l'input finale (faccio vedere il risultato del gioco prima di chiuderlo)
    cin >> c;
    
    return 0;
}