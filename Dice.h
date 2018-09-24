/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dice.h
 * Author: Simo
 *
 * Created on 11 marzo 2017, 14.31
 */

#ifndef DICE_H
#define DICE_H

class Dice {
protected:
	//valore del dado
	int value;
        //valore incrementale per generare
        //numeri casuali consecutivamente
        int u;
public:
	//inizializzo il dado
	Dice();
	//ritorna un numero a caso compreso tra 0 e i-1
	int RandInt(int i);
        //ritorna una direzione a case tra N S E W
        char RandPos();
};

#endif /* DICE_H */

