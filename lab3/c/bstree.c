#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include "global.h"
#include "bstree.h"


// a=b -> 0 ; a>b -> + ; a<b -> -
int compare(Value_Type a, Value_Type b) {
    return strcmp(a,b);
}

struct bstree* initialize_set (int size) {
    // An empty tree is represented by NULL
    return NULL;
}

void tidy(struct bstree* tree) {
    if(tree) {
        tidy(tree->left);
        tidy(tree->right);
        // assumes tree owns value memory
        free(tree->value);
        free(tree);
    }
}

Value_Type assign(Value_Type value){
    Value_Type tmp = (Value_Type)malloc(sizeof(value[0]) * (strlen(value)+1));  // value malloc
    strcpy(tmp, value);  // assign
    return tmp;
}

struct bstree* newNode(Value_Type value){
    struct bstree *tmp = (struct bstree*)malloc(sizeof(struct bstree));  // bstree malloc
    tmp->left = tmp->right = NULL;  // left and right subtrees are both NULL
    tmp->value = assign(value);  // assign
    return tmp; // return the bstree struct
}

// different from the height
int size(struct bstree* tree) {
    if(tree){
        return 1 + size(tree->left) + size(tree->right);  // until NULL
    }
    return 0;  // NULL
} 

struct bstree* insert (Value_Type value, struct bstree* tree) {
    if(tree){
        if(!compare(value, tree->value)){  // the root node is exactly matched
            return tree;  // return directly
        }else if(compare(value, tree->value) < 0){  // left subtree
            tree->left = insert(value, tree->left);  // recursive
        }else if(compare(value, tree->value) > 0){  // right subtree
            tree->right = insert(value, tree->right);  // recursive
        }
    } else {
        tree = newNode(value);  // if finally cannot catch , create new one 
      }
    return tree;  // RETURN TREE
}

bool find (Value_Type value, struct bstree* tree) {
    if(tree){
        if(!compare(value, tree->value))  return true;  // CATCH
        else if(compare(value,tree->value) < 0)
            return find(value, tree->left);
        else if(compare(value,tree->value) > 0)
            return find(value, tree->right);
    }
    return false;  // finally, cannot find and return false
}


// Helper functions
void print_set_recursive(struct bstree* tree, int depth) {
    if(tree){
        for(unsigned i=0; i<depth; i++){ printf(" "); }
        printf("%s\n", tree->value);
        print_set_recursive(tree->left, depth+1);
        print_set_recursive(tree->right, depth+1);
    }
} 

void print_set (struct bstree* tree) {
    printf("Tree:\n");
    print_set_recursive(tree,0);
}

double stats(struct bstree* tree, double depth){
    if(!tree) return 0;
    return depth + stats(tree->left,depth+1) + stats(tree->right,depth+1);
}

double Max(double a, double b){
    return a > b ? a : b;
}

int height(struct bstree* tree){
    if(!tree) return 0;
    return 1 + Max(height(tree->left), height(tree->right));
}

void print_stats (struct bstree* tree) {
    printf("Average number of comparisons：");
    printf("%.1lf\n", stats(tree,0.0) / size(tree));
    printf("The height of BST tree:");
    printf("%d\n",height(tree));
}
