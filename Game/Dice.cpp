/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Dice.h"

using namespace std;

Dice::Dice() {
	value = 0;
        u = 0;
}

int Dice::RandInt(int i){
    srand(time(0) + u);
    value = (rand()%i);
    u += value;
    //durante i vari test ho riscontrato che ogni volta che si genera 
    //il numero 1 questo continua a riproporsi fino al secondo successivo
    if(value==1){
        u = 0;
    }
    return value;
}

char Dice::RandPos(){
    srand(time(0) + u++);
    value = (rand()%4);
    switch(value){
        case 0:
            return 'N';
            break;
        case 1:
            return 'S';
            break;
        case 2:
            return 'E';
            break;
        case 3:
            return 'W';
            break;
    }
}