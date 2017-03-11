/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <ctime>
#include <cstdlib>

#include "Dice.h"

Dice::Dice() {
	value = 0;
        u = 0;
}

int Dice::RandInt(int i){
    srand(time(0) + u++);
    value = (rand()%i);
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