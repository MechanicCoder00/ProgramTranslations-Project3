#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;
#include "node.h"
#include "scanner.h"
#include "statSem.h"


/*
Author: Scott Tabaka
CMPSCI 4280 Project3
*/

/*
    No duplicate var declarations per scope and make sure var is declared before use.

    Todo List:
    In progress:
    1.
    2. Rename level as "stack_lvl"?
    3. Change error function to accomodate scope lvl?

    Questions:
    1. Do all 17 of the functions have to be used?
    2. Can I use a vector of sets? and avoid varcount and stack?
    3.
 */

vector< set<string> > setString(10);    //Vector of sets for scoping each level of the stack

enum switchValue {      //give a numeric value to variables for use in switch
    program,
    block,
    vars,
    expr,
    A,
    N,
    M,
    R,
    stats,
    mStat,
    stat,
    in,
    out,
    if2,
    loop,
    assign,
    RO,
};

static map<string,switchValue> switchMap;   //map declaration

void loadSwitchMap()        //program that assigns strings to a variable for use in switch
{
    switchMap["<program>"] = program;
    switchMap["<block>"] = block;
    switchMap["<vars>"] = vars;
    switchMap["<expr>"] = expr;
    switchMap["<A>"] = A;
    switchMap["<N>"] = N;
    switchMap["<M>"] = M;
    switchMap["<R>"] = R;
    switchMap["<stats>"] = stats;
    switchMap["<mStat>"] = mStat;
    switchMap["<stat>"] = stat;
    switchMap["<in>"] = in;
    switchMap["<out>"] = out;
    switchMap["<if>"] = if2;
    switchMap["<loop>"] = loop;
    switchMap["<assign>"] = assign;
    switchMap["<RO>"] = RO;
}

void errorStatSem1(token t)     //error if variable is already declared within same scope
{
    cout << "\nSTATIC SEMANTIC ERROR: " << tokenNames[t.tokenId] << " \"" << t.tokenInstance << "\" on line number "
    << t.lineNum << " already declared within this scope.\n";
    exit(1);
}

void errorStatSem2(token t)     //error if variable is not declared before use
{
    cout << "\nSTATIC SEMANTIC ERROR: " << tokenNames[t.tokenId] << " \"" << t.tokenInstance << "\" on line "
    << t.lineNum << " not declared.\n";
    exit(1);
}

void statSem(node *currentNode,int stack_lvl)       //main program for checking static semantics called from main
{
    loadSwitchMap();

    statSemCheck(currentNode, stack_lvl);

    cout << "\n***Static Semantics check Successful***\n";
}

void statSemCheck(const node *currentNode, int stack_lvl)   //subprogram for checking static semantics
{
    if (currentNode == NULL)
    {
        return;
    } else {
        switch (switchMap[currentNode->label])      //switch depending on which label is present in current node being traversed
        {
            case program:
//                cout << "program!";
                break;
            case block:
                stack_lvl++;
//                cout << "block!";
                break;
            case vars:
                declareVars(currentNode->child1, stack_lvl);
//                cout << "vars!";
                break;
            case expr:
//                cout << "expr!";
                break;
            case A:
//                cout << "A!";
                break;
            case N:
//                cout << "N!";
                break;
            case M:
//                cout << "M!";
                break;
            case R:
                checkDeclaration(currentNode->child1, stack_lvl);
//                cout << "R!";
                break;
            case stats:
//                cout << "stats!";
                break;
            case mStat:
                if (currentNode->child1 == NULL)     //if end of block
                {
//                    cout << "End of Block";
                    setString[stack_lvl].clear();   //clears all variables within current scope
                    stack_lvl--;                    //lowers number of scopes
                }
//                cout << "mStat!";
                break;
            case stat:
//                cout << "stat!";
                break;
            case in:
                checkDeclaration(currentNode->child1, stack_lvl);
//                cout << "in!";
                break;
            case out:
//                cout << "out!";
                break;
            case if2:
//                cout << "if!";
                break;
            case loop:
//                cout << "loop!";
                break;
            case assign:
                checkDeclaration(currentNode->child1, stack_lvl);
//                cout << "assign!";
                break;
            case RO:
//                cout << "RO!";
                break;
            default:
                break;
        }
//        debugDisplay(currentNode, stack_lvl);

        statSemCheck(currentNode->child1, stack_lvl);   //recursive traversal through nodes
        statSemCheck(currentNode->child2, stack_lvl);
        statSemCheck(currentNode->child3, stack_lvl);
        statSemCheck(currentNode->child4, stack_lvl);
    }
}



void declareVars(node *currentNode,int level)   //function that declares a variable in a scope
{
    if (currentNode == NULL)
    {
        return;
    } else {
        token t = currentNode->node_tk;

        if(verify(t.tokenInstance,level) == false)      //check to make sure variable is not present in current scope
        {
            setString[level].insert(t.tokenInstance);   //insert var into set of current scope level
        } else {
            errorStatSem1(t);
        }
    }
}

void checkDeclaration(node *currentNode,int level)      //function that checks if a variable has been declared
{
    if (currentNode == NULL || currentNode->label != "Identifier")
    {
        return;
    } else {
        token t = currentNode->node_tk;

        if(find(t.tokenInstance,level) < 0)
        {
            errorStatSem2(t);
        }
    }
}

bool verify(string s, int level)    //function that checks if a variable is contained in a set
{
    if (!setString[level].count(s))    //If new string is not in set.
    {
        return false;
    } else {
        return true;
    }
}

int find(string s, int level)       //function that checks if a variable is contained in any scope
{
    for(;level >= 0;level--)
    {
        if(verify(s,level) == true)
        {
            return level;
        }
    }
    return -1;
}

void displaySet(int level)   //scope display for debugging
{
    for(;level >= 0;level--)
    {
        cout << "scope level:" << level << "--> ";
        set<string>::iterator it = setString[level].begin();

        while (it != setString[level].end())
        {
            cout << (*it) << " ";
            it++;
        }
        cout << endl;
    }
}

void debugDisplay(const node *currentNode, int level)   //debug display of nodes
{
    cout << currentNode->label << " ";
    token t = currentNode->node_tk;

    if (t.tokenInstance != "")
    {
        cout << "Token ID: " << tokenNames[t.tokenId] << " \"" << t.tokenInstance << "\"";
    }
    cout << endl;
    displaySet(level);
}