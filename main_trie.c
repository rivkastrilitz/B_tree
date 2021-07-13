#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "trie.h"
// main function to create a trie by the text it gets and print it 
int main(int argc, char * argv[])
{
 int ok_input;
 node *root = new_child('$',NULL);
 if(root != NULL)
 {
 ok_input = get_text(root);
 if(ok_input == 0)
 {
 if(argc == 1)
 {
  print_lower_to_high(root);
 }
 else if (argc == 2)
 {
     if(*argv[1] == 'r')
     print_higher_to_low(root);
 }
 }
 free(root);
 return 0;
 }
 else
 {
     return 1;
 }
 

}
