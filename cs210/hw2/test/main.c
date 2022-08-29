#include <stdio.h>
#include <stdlib.h>
#include "json.tab.h"
#include "tree.h"
extern FILE *yyin;
extern char *yytext;
char *yyfilename;

void print_tree(struct treenode *n);
void add_node(struct treenode *n, int prodrule, int kids,  struct treenode *kids0, struct treenode *kids1, struct treenode *kids2);

TreePtr rootPtr = NULL;

int main(int argc, char *argv[])
{
   int i;
   if (argc < 2) { printf("usage: iscan file.dat\n"); exit(-1); }
   yyin = fopen(argv[1],"r");
   if (yyin == NULL) { printf("can't open/read '%s'\n", argv[1]); exit(-1); }
   yyfilename = argv[1];
   if ((i=yyparse()) != 0) {
      printf("parse failed\n");
      }
   else {
	printf("no errors\n");
	printf("Json\n");
	print_tree(rootPtr);
   }
   return 0;
}

void print_tree(struct treenode *n)
{
  int i;
  if (n == NULL) return; /* don't segfault on NULLs */
  //printf("node %d\n", n->label);
  if(n->label == 0)
	printf("Element\n");
  if(n->label == 1)
        printf("Value\n");
  if(n->label == 2)
        printf("Object\n");
  if(n->label == 3)
        printf("Array\n");
  if(n->label == 4)
        printf("String\n");
  if(n->label == 5)
        printf("Number\n");
  if(n->label == 6)
        printf("True\n");
  if(n->label == 7)
        printf("False\n");
  if(n->label == 8)
        printf("NULL\n");
  if(n->label == 9)
        printf("Members\n");
  if(n->label == 10)
        printf("Member\n");
  if(n->label == 11)
        printf("Member ',' Members\n");
  if(n->label == 12)
        printf("String ':' Element\n");
  if(n->label == 13)
        printf("'[' Elements ']'\n");
  if(n->label == 14)
        printf("Element\n");
  if(n->label == 15)
        printf("Element ',' Elements\n");
  if(n->label == 16)
        printf("NUM\n");
  if(n->label == 17)
        printf("Negative\n");
  if(n->label == 18)
        printf("Exponent\n");
  if(n->label == 19)
        printf("'-' NUM\n");
  if(n->label == 20)
        printf("Number 'e' Number\n");
  if(n->label == 21)
        printf("Number 'E' Number\n");

  if (n->nkids==0) {
     /* print stuff about leaf */
     }
     else {
	 for(i=0;i<n->nkids;i++) print_tree(n->kids[i]);
     }
}

void add_node(struct treenode *n, int prodrule, int kids,  struct treenode *kids0, struct treenode *kids1, struct treenode *kids2)
{
  if(prodrule == 0)//json starting symbol
  {
	rootPtr = n;
  }
  n->nkids = kids;
  n->label = prodrule;
  n->kids[0] = kids0;
  n->kids[1] = kids1;
  n->kids[2] = kids2;
}
