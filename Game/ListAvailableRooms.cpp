/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ListAvailableRooms.h"

void insertTail(ptr l, char c, int x, int y) {
    if (l->next == NULL) {
        //inserisco l'elemento
        //nel caso in cui la lista sia vuota
        //(il primo elemento è e rimane vuoto)
        ptr temp = l;
        temp->next = new list;
        temp = temp->next;
        temp->dir = c;
        temp->x = x;
        temp->y = y;
        temp->next = NULL;
    } else {
        //scorro la lista e lo metto in fondo
        ptr temp = l;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new list;
        temp = temp->next;
        temp->dir = c;
        temp->x = x;
        temp->y = y;
        temp->next = NULL;
    }
}

int getLength(ptr l) {
    ptr p = l;
    int count = 0;
    //siccome la lista ha il primo elemento nullo
    //controllo se il puntatore al prossimo elemento
    //è null.
    while (p->next != NULL) {
        p = p->next;
        count++;
    }
    return count;
}

ptr getElement(ptr l, int pos) {
    ptr temp = l;
    //il primo elemento non è accessibile
    if (pos < 1 || pos > getLength(l)) {
        cout << "Err: "
                "tentativo di ricerca di un elemento inesistente \n";
    } else {
        for (int i = 0; i < pos; i++) {
            temp = temp->next;
        }
    }
    //ritorno il puntatore all'elemento
    return temp;
}

void deletePos(ptr l, int pos) {
    ptr temp = l;
    //il primo elemento non è accessibile
    if (pos < 1 || pos > getLength(l)) {
        cout << "Err: "
                "tentativo di eliminazione di un'elemento inesistente \n";
    } else {
        //elimina l'n-esimo elemento presente nella lista
        //(segue l'ordine in cui sono stati inseriti)
        //ad ogni rimozione la posizione degli elementi
        //successivi a quello cancellato diminuisce automaticamente
        //(fare attenzione ai cancellamenti futuri)
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next;
        }
        ptr support = temp->next->next;
        temp->next->next = NULL;
        temp->next = support;
    }
}

void stampa(ptr l) {
    //parto a stampare dal secondo elemento
    //(il primo è nullo)
    ptr p = l->next;
    //ciclo fino a quando non trovo un elemento nullo
    //(fine della lista)
    while (p != NULL) {
        cout << "{[" << p->dir << "]\t";
        cout << "[" << p->x << "]\t";
        cout << "[" << p->y << "]}\n";
        p = p->next;
    }
}

