#ifndef TRIE_H
#define TRIE_H
#define NUM_LETTERS 26

/*
struct of node, include a letter , number of words that end here and 26 pointers to nodes
*/
typedef struct node{
    char letter;
    long word_count;
    struct node* parent;
    struct node* children [NUM_LETTERS];
    }node;
node * new_child(char n_letter,node* par);
int has_children(node* current_node);
int free_them_all(node * current_node);
int free_all(node * current_node);
int get_word(node *root);
int get_text(node * root);
int free_par_to_par(node *current_node);
int print_z_to_a_word(node * root);
int print_a_to_z_word(node * root);
int print_lower_to_high(node * root);
int print_higher_to_low(node * root);



#endif