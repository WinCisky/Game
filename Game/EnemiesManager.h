/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EnemiesManager.h
 * Author: Simo
 *
 * Created on 27 giugno 2017, 14.05
 */

#ifndef ENEMIESMANAGER_H
#define ENEMIESMANAGER_H

#include "Map.h"

using namespace std;

//creazione durante la creazione del livello
void createEnemy();

//movimento verso il personaggio principale se si è sullo stesso livello
//cambio stanze (se si è vicino alla porta)
//se si è abbastanza vicini attacco

//posiziono il nemico sulla mappa
void showEnemy();

#endif /* ENEMIESMANAGER_H */

