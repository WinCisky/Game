/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ListEnemies.h"

using namespace std;
/*
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

ptrN remove(ptrN p) {
    if (!empty(p)) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        return p->next;
    } else {
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
            cout << n->enemy.name << " floor: " << n->floor << " \n";
            n = n->next;
        }
    }
}
 * */