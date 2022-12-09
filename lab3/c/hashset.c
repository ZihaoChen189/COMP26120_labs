#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include <math.h>
#include "global.h"
#include "hashset.h"

// original functions
// a=b -> 0 ; a>b -> + ; a<b -> -
int compare(Value_Type a, Value_Type b){
    return strcmp(a,b);
}

bool isPrime (int n) {
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

int nextPrime(int n) {
    for (; !isPrime(n); n++);
    return n;
}

// memory malloc for each value
Value_Type assign(Value_Type value) {
    Value_Type tmp = (Value_Type)malloc(sizeof(value[0]) * (strlen(value)+1));  // value malloc
    strcpy(tmp, value); // assign
    return tmp;
}

// mode selection and strings converted as hash value
// ready to mod%
int hashcode(Value_Type value) {
    int i;
    int res=0;
    if(mode == 0)
        res = strlen(value);  // the length of string
    else if(mode == 4){
        for(i = 0; i<strlen(value); i++) {
            res = res * 31 + value[i];  // according to the string length, weighted approach
        }
    }
    // value overflow and become positive (because limit of the INT)
    // (LONG) has the precise consideration
    // when meet a same value, this process will operate twice, same place will be found
    if(res < 0) res = -res;
    return res;
}

struct hashset* rehash(struct hashset* set){
    // twice the old hash table size
    struct hashset* newset = initialize_set(set->size * 2);  
    // copy data
    for(int i = 0; i<set->size; i++){
        if(set->cells[i].state == in_use)
            newset = insert(set->cells[i].element, newset);  // make a new hashtable with old data
    }
    tidy(set);  // memory management
    return newset;  // return NEW hash table
}

// new table
struct hashset* initialize_set (int size) {
    struct hashset* set = (struct hashset*)malloc(sizeof(struct hashset));  // hashset malloc
    set->size = nextPrime(size);  // prime
    set->cells = (cell*)malloc(sizeof(cell) * set->size);  // cell malloc
    // zeros
    set->num_entries = 0;
    set->collision = 0;
    for(int i = 0; i<set->size; i++)
        set->cells[i].state = empty;  // every state is empty
    return set;
}

void tidy(struct hashset* set) {
    for(int i=0; i<set->size; i++){
        if(set->cells[i].state == in_use){
            free(set->cells[i].element);
            set->cells[i].state = deleted;
        }
    }
    free(set->cells);
    free(set);
    set = NULL;
}

int size(struct hashset* set) {
    return set->num_entries;
} 

struct hashset* insert (Value_Type value, struct hashset* set) {
    if(find(value, set))  return set;  // if value exists return set
    /*
    size(set) returns the number of palces in used,
    set->size will return the hash table size,
    If more than three-quarters of the table is already used, 
    which means the while loop will run for a long time to catch a specific value, 
    in that case it will directly rehash the hash table.
    */
    if(size(set) >= set->size * 0.75){
        set = rehash(set);
    }
    // similar to the find function
    int index = hashcode(value) % set->size;
    /*
    Use i to record the previous position of index,
    and this index can be any position in the table,
    add the set size to prevent index-1 being negative.
    */
    int i = (index-1+set->size) % set->size;
    while(1){
        // find a free place not in use
        if(set->cells[index].state != in_use){
            set->cells[index].state = in_use;
            set->cells[index].element = assign(value);  // assign
            ++ set->num_entries;
            break;  // BREAK after adding data successfully
        }
        // if in_use, add one collision for each loop
        ++ set->collision;
        // BREAK if connot catch target after one WHOLE loop for the hash table
        if(index == i)  break;
        ++index;  // linear probing
        /*
        Still traverse in the table no matter to the end, 
        in this case, start from 0,
        only one condition to end the loop is "if(index == i)"
        */
        if(index == set->size)  index = 0;
    }  // end while
    return set;
}

bool find (Value_Type value, struct hashset* set) {
    int index = hashcode(value) % set->size;  // index is derived
    /*
    Use i to record the previous position of index,
    and this index can be any position in the table,
    add the set size to prevent index-1 being negative.
    */
    int i = (index-1+set->size) % set->size;
    while(1){
        // if the state in cells[index] is in_use, check the value
        if(set->cells[index].state == in_use) {
            if(!compare(value,set->cells[index].element))  // if same?
                return true;  // we find the value!
        } else break; // when unused place is found, the current value is not in table, return FALSE
        // BREAK if connot catch target after one WHOLE loop for the hash table
        if(index == i) break;
        ++ index;  // linear probing
        /*
        Still traverse in the table no matter to the end, 
        in this case, start from 0,
        only one condition to end the loop is "if(index == i)"
        */
        if(index == set->size) index = 0;
    } // end while
    return false;
}


void print_set (struct hashset* set) {
    int i;
    for(i = 0; i<set->size; i++){
        if(set->cells[i].state == in_use){
        printf("%s\n",set->cells[i].element);
        }
    }
}

void print_stats (struct hashset* set) {
    printf("collision = %d\n",set->collision);
}
