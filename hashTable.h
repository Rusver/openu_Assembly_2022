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

/**
 * int function that parses a key into hashcode
 * @param key - number to parse
 * @return int value
 */
int hashCode(int key);
/**
 * struct function that searches by a key number
 * @param key - key to search by
 * @return struct value
 */
struct DataItem* search_by_key(int key);
/**
 * struct function that searches by a string
 * @param key - key to search by
 * @return struct value
 */
struct DataItem* search_by_string(char* data);
/**
 * void function that inserts into list
 * @param data - list
 * @param key - key to search by
 * @param type - type
 */
void insert(char* data ,int key, int type);
/**
 * struct function that deletes item from list
 * @param item - list to delete the item from
 * @return struct value
 */
struct DataItem* delete(struct DataItem* item);
/**
 * void function that prints
 */
void display();


#endif /*OPENU_ASSEMBLY_2022_HASHTABLE_H*/

