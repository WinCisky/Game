/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.cpp
 * Author: Simo
 *
 * Created on 10 marzo 2017, 14.01
 */

#include <stdlib.h>
#include <iostream>
#include "ListAvailableRooms.h"

/*
 * Simple C++ Test Suite
 */

void test1() {
    std::cout << "newsimpletest test 1" << std::endl;
}

void test2() {
    std::cout << "newsimpletest test 2" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (newsimpletest) message=error message sample" << std::endl;
}

void listTesting(){
    std::cout << "newsimpletest test 3" << std::endl;
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
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (newsimpletest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (newsimpletest)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (newsimpletest)" << std::endl;
    
    std::cout << "%TEST_STARTED% test2 (newsimpletest)\n" << std::endl;
    listTesting();
    std::cout << "%TEST_FINISHED% time=0 test2 (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

