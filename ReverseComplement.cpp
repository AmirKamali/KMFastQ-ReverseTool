#include "ReverseComplement.h"

#include <iostream>
#include <fstream>
#include <string>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
using namespace std;
#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif
const int PAIRED_READ_SPACE=50;//50 bp + 1 \n
string GetFileDirectory(string FAddress) {
	return FAddress.substr(0, FAddress.find_last_of("\\/")) + "/";
}
string GetFileName(string filepath) {
	char *ff = const_cast<char*>(filepath.c_str());
	string filename = basename(ff);
	return filename;
}
bool FileExist(string name) {
	ifstream file(name);
	if (!file) // If the file was not found, then file is 0, i.e. !file=1 or true.
		return false;    // The file was not found.
	else
		// If the file was found, then file is non-0.
		return true;     // The file was found.
}

string GetReverseComplementOfQuality(string Read)
{
	string output="";
		for (int i=Read.length()-1;i>=0;i--)
		{
				output+=Read[i];
		}
		return output;
}
string GetReverseComplement(string Read)
{
	string output="";
	for (int i=Read.length()-1;i>=0;i--)
	{
		if (Read[i]=='a')
			output+="t";
		else if (Read[i]=='A')
			output+="T";
		else if (Read[i]=='t')
			output+="a";
		else if (Read[i]=='T')
			output+="A";
		else if (Read[i]=='c')
			output+="g";
		else if (Read[i]=='C')
			output+="G";
		else if (Read[i]=='g')
			output+="c";
		else if (Read[i]=='G')
			output+="C";
		else
			output+=Read[i];
	}
	return output;
}
void ReverseComplementFASTA(string Input, string Output,bool RewriteNames)
{
	cout <<"Reverse Complementing FASTA File :"<<Input<<endl;
}
void ReverseComplementFASTQ(string Input, string Output,bool RewriteNames)
{
	cout <<"Reverse Complementing FASTQ File :"<<Input<<endl;
	ifstream file_input(Input);
	ofstream file_output(Output);
	int Mode=0; //0=Read Name , 1=Read Data , 3=Symbol , 4=Quality
	while (!file_input.eof())
	{
		string Line;
		std::getline(file_input,Line);
		if (Line.length()==0 || Line==" ")
		{

		}
		else if (Mode==0)
		{
			//Nothing to do here;
			if (RewriteNames)
			{
				Line=Line.insert(1,"R-");
			}
			file_output<<Line;
		}
		else if (Mode==1)
		{
			string ReverseComplement=GetReverseComplement(Line);
			file_output<<ReverseComplement;
		}
		else if (Mode==2)
		{
			//Nothing to do here;
			file_output<<Line;
		}
		else if (Mode==3)
		{
			string ReverseComplement_Quality=GetReverseComplementOfQuality(Line);
			file_output<<ReverseComplement_Quality;
			Mode=-1;
		}
		file_output<<endl;
		Mode++;
	}
	file_output.flush();
	file_output.close();
	file_input.close();
	cout <<"Reverse Complementing completed :"<<Output<<endl;

}
void GenerateReverseComplement(string Input, SupportFileFormat Format,string Output,bool RewriteNames) {

	if (Format==FileFormat_FastA)
	{
		ReverseComplementFASTA(Input,Output,RewriteNames);
	}
	else if (Format==FileFormat_FastQ)
	{
		ReverseComplementFASTQ(Input,Output,RewriteNames);
	}
}

