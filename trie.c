#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "trie.h"

/*
cretae a new node and reset it with the letter the function gets, return the address of the node
*/
node * new_child(char n_letter,node* par)
{
    node * n_node = (node*)malloc(sizeof(node));
    if  (n_node == NULL)
    {
      return NULL;
    }
    n_node->letter = n_letter;
    n_node->word_count = 0;
    n_node->parent = par;
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        n_node->children[i] = NULL;
    }
    return n_node;
}

/*
check if a current nide have any children return 1 if there is chrldren to the node, else 0
*/
int has_children(node* current_node)
{
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (current_node->children[i] != NULL)
        {
            return 1;
        }
    }
    return 0;
    
}

/*
this function go all over the trie and free all of the nodes in the trie , but not the root
*/
int free_them_all(node * current_node)
{
   if(has_children(current_node) == 1)
   {
     for (int i = 0; i < NUM_LETTERS; i++)
     {
       if (current_node->children[i] != NULL)
       {
         free_them_all(current_node->children[i]);
         current_node->children[i] = NULL;
       }
     }
   }
   free(current_node);
   return 0;
}

/*
reset the node ponter to the root of the trie and
call an inner function that free all the nodes in the trie
*/
int free_all(node * current_node)
{
  while(current_node->letter != '$')
  {
    current_node = current_node->parent;
  }
  for (int i = 0; i < NUM_LETTERS; i++)
  {
    if (current_node->children[i] != NULL)
    {
      free_them_all(current_node->children[i]);
    }
    
  }
  return 0;
}

/*
gets a word from the user and insert the word to a trie
*/
int get_word(node *root)
{
    int flag = 1, finish = 0;
    char g_char = '\n',char_change = '\n';
    node * temp_node;
    temp_node = root;
    while(flag == 1)
    {
        if(scanf("%c",&g_char) == EOF)
           finish =1;
        if (g_char == ' ' || g_char == '\n' || g_char == EOF || g_char == '\r'|| g_char == '\0')
        {
            flag = 0;
            if(temp_node->letter != '$')
            {
                temp_node->word_count++;
            }
        }
        // if the char is a letter insert it to the trie
        else if((g_char <= 90 && g_char >= 65) || (g_char <= 122 && g_char >= 97))
        {
            char_change = tolower(g_char);
            if (temp_node->children[char_change - 'a'] == NULL)
            {
                temp_node->children[char_change - 'a'] = new_child(char_change,temp_node);
                // if there is no more space in memory , free all memory and exit
                if(temp_node->children[char_change - 'a'] == NULL)
                {
                  free_all(temp_node);
                  finish = 2;
                  flag = 0;
                }
            }
            if(temp_node != NULL)
            {
            temp_node = temp_node->children[char_change - 'a'];
            }
        }
    }
    return finish;
     
}

/*
get a text from the user and insert each word to a trie
*/
int get_text(node * root)
{
    char go_on = 0;
   while(go_on != 1 && go_on != 2)
   {
      go_on = get_word(root);
   }
   if(go_on == 2)
    {return 1;}
    else
    {
      return 0;
    }
    
}

/*
go from the current node up to check for nodes it can free, nodes with no children
*/
int free_par_to_par(node *current_node)
{
  node * parent_temp;
  if(current_node->letter == '$')
  return 0;
  while(has_children(current_node) == 0 && current_node->letter != '$')
  {
    parent_temp = current_node->parent;
    parent_temp->children[current_node->letter - 'a'] = NULL;
    free(current_node);
    current_node = parent_temp;
  }
  return 0;
}

/*
print the next word in the alphabetical order and free the memory if needed
*/
  int print_z_to_a_word(node * root)
{
  
  int flag = 1,go_on;
  node * temp_node;
  node * parent_temp;
  temp_node = root;
  while (flag == 1)
  {
    //if the nde is not the root
     if(temp_node->letter != '$')
     {
       // print as word if even one word ends here
         if (temp_node->word_count>0)
         {
             printf("%c %ld\n",temp_node->letter ,temp_node->word_count);
             temp_node->word_count = 0;
             // if the node have no cildren free it and check his prev
             if(has_children(temp_node) == 0)
               {
              parent_temp = temp_node->parent;
               parent_temp->children[temp_node->letter - 'a'] = NULL;
               free(temp_node);
               free_par_to_par(parent_temp);
               flag = 0;
               }
         }
         else
         {
           printf("%c",temp_node->letter);
           go_on = 1;
                for (int i = NUM_LETTERS-1; i >= 0 && go_on == 1; i--)
                  {
                   if (temp_node->children[i] != NULL)
                    {
                     temp_node = temp_node->children[i];
                     go_on = 0;
                    }
                  } 
         }         
     }
     else
     {go_on = 1;
       for (int i = NUM_LETTERS-1; i >= 0 && go_on == 1; i--)
         {
          if (temp_node->children[i] != NULL)
            {
              temp_node = temp_node->children[i];
               go_on = 0;
            }
         } 
     }
    }
  return 0;
}

/*
print the next word in the reverse alphabetical order and free the memory if needed
*/
  int print_a_to_z_word(node * root)
{
  
  int flag = 1,go_on;
  node * temp_node;
  node * parent_temp;
  temp_node = root;
  while (flag == 1)
  {
    //if the nde is not the root
     if(temp_node->letter != '$')
     {
       // print as word if even one word ends here
         if (temp_node->word_count>0)
         {
             printf("%c %ld\n",temp_node->letter,temp_node->word_count);
             temp_node->word_count = 0;
             // if the node have no cildren free it and check his prev
             if(has_children(temp_node) == 0)
               {
               parent_temp = temp_node->parent;
               parent_temp->children[temp_node->letter - 'a'] = NULL;
               free(temp_node);
               free_par_to_par(parent_temp);
               flag = 0;
               }
              else
              {
                /* code */
              }
              
         }
         else
         {
           printf("%c",temp_node->letter);
           go_on = 1;
                for (int i = 0; i < NUM_LETTERS && go_on == 1; i++)
                  {
                   if (temp_node->children[i] != NULL)
                    {
                     temp_node = temp_node->children[i];
                     go_on = 0;
                    }
                  } 
         }         
     }
     else
     {go_on = 1;
       for (int i = 0; i < NUM_LETTERS && go_on == 1; i++)
         {
          if (temp_node->children[i] != NULL)
            {
              temp_node = temp_node->children[i];
               go_on = 0;
            }
         } 
     }
     }
 return 0;
}

/*
print the words in an alphabetical order and free the memory
*/
int print_lower_to_high(node * root)
{
  while (has_children(root) == 1)
    {
        print_a_to_z_word(root);
    }
  return 0;
}

/*
print the words in a reverse alphabetical order and free the memory
*/
int print_higher_to_low(node * root)
{
  while (has_children(root) == 1)
    {
        print_z_to_a_word(root);
    }
  return 0;
}

