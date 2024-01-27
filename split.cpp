/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>
/* Add a prototype for a helper function here if you need */
void addList(Node*& list, Node*& currNode);

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
  // WRITE YOUR CODE HERE

  // Base case, when the in Node is null, then end the recursion
  if(in == NULL)
  {
    return;
  }
  
  Node* next = in->next;
  in->next = NULL; // disconnects node to place into a list by itself

  // If even, add to evens list
  if(in->value % 2 == 0)
  {
    addList(evens, in);
  }
  else
  {
    addList(odds, in);
  }

  // Recursively continue to add the items to the even or odd lists
  in = next;
  split(in, odds, evens);
}

/* If you needed a helper function, write it here */
void addList(Node*& list, Node*& currNode)
{
  // If the list (either even or odd) is NULL, then make the head the current node
  if(list == NULL)
  {
    list = currNode;
  }
  // Last item in the list should point to the new node being added
  else if(list->next == NULL)
  {
    list->next = currNode;
  }
  // Need to parse to the end of the list by using recursion
  else
  {
    addList(list->next, currNode);
  }
}