/*
// Created by Ruslan Ver on 05/08/2022.
*/
#include "hashTable.h"
#include "pre_and_parcer.h"

int hashCode(int key) {
    return key % SIZE;
}

struct DataItem* search_by_key(int key) {
    /*get the hash*/
    int hashIndex = 0;

    /*move in array until an empty*/
    while(hashArray[hashIndex] != NULL) {

        if(hashArray[hashIndex]->key == key)
            return hashArray[hashIndex];

        /*go to next cell*/
        ++hashIndex;

        /*wrap around the table*/
        hashIndex %= SIZE;
    }

    return NULL;
}

struct DataItem* search_by_string(char* string) {

    int hashIndex = 0;

    /*move in array until an empty*/
    while(hashArray[hashIndex] != NULL) {

        if(!strcmp(hashArray[hashIndex]->data, string))
            return hashArray[hashIndex];

        /*go to next cell*/
        ++hashIndex;

        /*wrap around the table*/
        hashIndex %= SIZE;
    }

    return NULL;
}

void insert(char* data, char** list, int key, int type) {

    int hashIndex = 0;
    int i = 0;

    struct DataItem *item = malloc(sizeof(struct DataItem));
    char** ds = malloc(sizeof(char*));
    char* name = malloc(strlen(data));
    char** temp;

    strcpy(name, data);

    while(list[i] != NULL)
    {
        ds[i] = malloc(strlen(list[i]));
        strcpy(ds[i], list[i]);
        i++;
        temp = realloc(ds, sizeof(char*)*((i+1)));
        if (temp != NULL)
            ds = temp;
    }
    ds[i] = NULL;

    item->data = name;
    item->list = ds;
    item->key = key;
    item->type = type;

    /*move in array until an empty or deleted cell*/
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        /*go to next cell*/
        ++hashIndex;

        /*wrap around the table*/
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = item;
}

struct DataItem* delete(struct DataItem* item) {
    int key = item->key;

    /*get the hash*/
    int hashIndex = hashCode(key);


    /*move in array until an empty*/
    while(hashArray[hashIndex] != NULL) {

        if(hashArray[hashIndex]->key == key) {
            struct DataItem* temp = hashArray[hashIndex];

            /*assign a dummy item at deleted position*/
            free(temp->data);
            free_list(temp->list);
            free(temp->list);
            hashArray[hashIndex] = NULL;
            return temp;
        }

        /*go to next cell*/
        ++hashIndex;

        /*wrap around the table*/
        hashIndex %= SIZE;
    }

    return NULL;
}

void display() {
    int i = 0;

    for(i = 0; i<SIZE; i++) {

        if(hashArray[i] != NULL)
            printf(" (%d,%s)",hashArray[i]->key, hashArray[i]->data);
        else
            printf(" ~~ ");
    }

    printf("\n");
}
