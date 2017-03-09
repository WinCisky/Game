
// License

#include <cstdlib>
#include <iostream>
#include "ListAvailableRooms.h"

using namespace std;

int main(int argc, char** argv) {
    ptr l = new list;
    l->next = NULL;
    insertTail(l, 'S', 0, 5);
    insertTail(l, 'M', 1, 2);
    insertTail(l, 'N', 4, 3);
    stampa(l);
    deletePos(l,3);
    deletePos(l,1);
    deletePos(l,1);
    insertTail(l, 'S', 0, 5);
    stampa(l);
    return 0;
}