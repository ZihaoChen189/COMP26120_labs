#include <stdbool.h>

typedef char* Value_Type;

int compare(Value_Type,Value_Type);

struct bstree {
  Value_Type value;
  struct bstree* left;  // left subtree
  struct bstree* right;  // right subtree
};

struct bstree* initialize_set (int size);     
void tidy (struct bstree*); 
int size(struct bstree*);
struct bstree* insert (Value_Type value, struct bstree* set);
bool find (Value_Type value, struct bstree* set); 

// Additional functions
Value_Type assign(Value_Type value);
struct bstree* newNode(Value_Type value); 

// Helper functions
void print_set (struct bstree*);
void print_stats (struct bstree*);
