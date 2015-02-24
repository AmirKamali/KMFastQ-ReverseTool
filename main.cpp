//============================================================================
// Name        : KMReadGenerator.cpp
// Author      : AmirHossein Kamali
// Version     :
// Copyright   : This project is part of a study in Victor Chang Cardiac Institue
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <boost/tokenizer.hpp>
#include "ReverseComplement.h"


using namespace std;
using namespace boost;


void ReadKeys(int argc, char* argv[])
{
	string InputFileAddress="";
	string Output="";
	bool RewriteNames=true;
	SupportFileFormat FileFormat=FileFormat_FastQ;
	bool IsDebugMode=false;

	 if (argc < 3) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
	        std::cout << "Usage is -fast[a,q] <input read>  -o <output>"<<endl<<endl; // Inform the user of how to use the program
	    } else { // if we got enough parameters...

	        for (int i = 1; i < argc; i+=2) { /* We will iterate over argv[] to get the parameters stored inside.
	                                          * Note that we're starting on 1 because we don't need to know the
	                                          * path of the program, which is stored in argv[0] */
	            if (i + 1 != argc) // Check that we haven't finished parsing already
	                if (strcmp(argv[i] ,"-fasta")==0) {
	                    // We know the next argument *should* be the filename:
	                	InputFileAddress = argv[i + 1];
	                    FileFormat=FileFormat_FastA;
	                }
	                else if (strcmp(argv[i] , "-fastq")==0) {
	                	InputFileAddress = argv[i + 1];
	                    FileFormat=FileFormat_FastQ;
	                }
	                else if (strcmp(argv[i] , "-rename")==0) {
	                	//Change Default Rewrite value
	                	int Rewrite =stoi(argv[i + 1]);
	                    if (Rewrite==0)
	                    {
	                    	cout<<"Disabled";
	                    	RewriteNames=false;
	                    }
	                 }
	                else if (strcmp(argv[i] , "-o")==0)
	                {
	                	Output=argv[i + 1];
	                }
	                else {
	                    std::cout <<"Invalid PARAMETERS:"<< argv[i] << " "<<endl;
	            }

	        }
	    }
	 if (Output.length()==0)
	 {
		 cout <<"Output address is not specified."<<endl;
		 return;
	 }
	 else if (!FileExist(InputFileAddress))
	 {
		 cout <<"Input file address does not exist."<<endl;
		 return;
	 }
	 GenerateReverseComplement(InputFileAddress,FileFormat,Output,RewriteNames);
}

int main(int argc, char* argv[]) {
	cout <<endl<< "Random Read Generator initializing" << endl;
	ReadKeys(argc,argv);
	return 0;
}
