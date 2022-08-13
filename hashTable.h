/*
// Created by Ruslan Ver on 05/08/2022.
*/
#ifndef OPENU_ASSEMBLY_2022_HASHTABLE_H
#define OPENU_ASSEMBLY_2022_HASHTABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 20

struct DataItem {
    char* data;
    int key;
    int type;
};

struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;


int hashCode(int key);
struct DataItem* search_by_key(int key);
struct DataItem* search_by_string(char* data);
void insert(char* data ,int key, int type);
struct DataItem* delete(struct DataItem* item);
void display();


#endif /*OPENU_ASSEMBLY_2022_HASHTABLE_H*/

