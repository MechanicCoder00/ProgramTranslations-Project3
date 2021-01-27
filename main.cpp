#include <iostream>
#include <fstream>
using namespace std;
#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "node.h"
#include "testTree.h"
#include "statSem.h"


/*
Author: Scott Tabaka
CMPSCI 4280 Project3

Purpose: This project tests the static semantics of a program using local scope.  It will check to make sure all
    variables are declared before use and that duplicate declarations do not happen.  Error messages will be given for
    each if improper use is detected.
*/

string appendFileExtension(string s)             //adds .fs19 file extension if it does not exist
{
    string fileEnding = ".fs19";
    if(s.length() > fileEnding.length())
    {
        if (s.substr(s.length() - 5, 5).compare(fileEnding) != 0)
        {
            s.append(fileEnding);
        }
    }else{
        s.append(fileEnding);
    }
    return s;
}

int main(int argc, char *argv[])
{
    if(argc > 2)                                //checks for correct amount of arguments
    {
        cout << "Usage Error: P1 <filename>" << endl;
        exit(1);
    }

    string inputFilename = "testfile66.fs19";

//    string inputFilename;
//
//    if(argc == 1)       //if there is no command line argument given
//    {
//        inputFilename = "temp.fs19";
//        ofstream output(inputFilename);
//
//        cout << "Please enter valid inputs and press <ctrl+d> when finished\n";
//        output << string(istreambuf_iterator<char>(cin), {});           //inputs user input into the output file
//        cout << endl;
//
//        output.close();
//    }
//    else if (argc == 2)             //if command line argument is given
//    {
//        inputFilename = argv[1];        //use the file name provided by user
//        inputFilename = appendFileExtension(inputFilename); //append .fs19 if not present
//    }
//    else
//    {
//        cout << "Usage Error: P1 <filename>" << endl;		//display for proper usage
//        exit(1);
//    }

    ifstream input(inputFilename);                  //opens input file stream
    if(input)
    {
        node *parseTree = parser(input);            //creates parse tree
//        treePrint(parseTree, 0);                    //print parse tree Preorder
//        cout << "\n---Separator---\n\n";
        statSem(parseTree,0);
    }else{
        cout << "Error: Cannot open file -- " << inputFilename << endl;
    }
    input.close();

    return 0;
}