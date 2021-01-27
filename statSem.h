#ifndef INC_4280P3_STATSEM_H
#define INC_4280P3_STATSEM_H

/*
Author: Scott Tabaka
CMPSCI 4280 Project3
*/

void errorStatSem1(token t);
void errorStatSem2(token t);
void statSem(node *currentNode,int stack_lvl);
void statSemCheck(const node *currentNode, int stack_lvl);
void declareVars(node *currentNode,int level);
void checkDeclaration(node *currentNode,int level);
bool verify(string s, int e);
int find(string s, int level);

void displaySet(int level);
void debugDisplay(const node *currentNode, int stack_lvl);

#endif
