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
int CalculatePatternLength(string* Patterns,int PatternNumber)
{
	int PatternLength=0;
	for (int i = 0; i < PatternNumber; i++) {
		string str= Patterns[i];
		if (str[0]!='l'&&str[0]!='r'&&str[0]!='c')
		{
			str=str.substr(1,str.length()-1);
			PatternLength += stoi(str);
		}
	}
	return PatternLength;
}
bool GenerateRefrenceIndex(string FAddress) {
	string IndexFileAddress = FAddress + ".kmdx";
	if (!FileExist(FAddress)) {
		cout << "Reference file not found" << endl;
		return false;
	}
	if (FileExist(IndexFileAddress)) {
		cout << "index file found" << endl;
		return true;
	}

	cout << "XGenerating index file for :" << FAddress << endl;
	//Read file
	ifstream file(FAddress);
	string line;

	//Output index
	ofstream outputFile(FAddress + ".kmdx");
	bool InChromosom = false;
	long CC = 0;
	while (file >> line) {

		//cout<<endl<<"SALAAAAAM."<<flush;
		//break;
		if (line.at(0) == '>') {
			cout << "Generating index for " << line << endl << flush;
			long pos = ((long) file.tellg() - (long) line.length());
			if (!InChromosom) {
				outputFile << line << "\t" << pos;
				InChromosom = true;
			} else {
				outputFile << "\t" << pos - 1 << endl << flush;
				;
				InChromosom = false;
			}
		}

		CC += line.length() + 1;
	}
	if (InChromosom) {
		outputFile << "\t" << CC - 1 << flush;
		;
	}
	cout << "CONTENT:" << line;
	file.close();
	outputFile.close();
	return true;
}
long* GetReferenceBoundry(string chr, string FAddress) {
	chr = ">" + chr;
	bool RefrenceOK = GenerateRefrenceIndex(FAddress);
	if (!RefrenceOK) {
		long default_arr[2] = { 0, 0 };
		return default_arr;
	}
	string IndexFileAddress = FAddress + ".kmdx";
	ifstream file(IndexFileAddress);
	string chr_l;
	long pos_start = 0;
	long pos_end = 0;

	while (file >> chr_l >> pos_start >> pos_end) {
		if (chr_l.compare(chr) == 0) {
			break;
		}
	}
	file.close();
	long Res[2];
	Res[0] = pos_start;
	Res[1] = pos_end;
	if (pos_end == 0) {
		cout << "Chromosome not found or index file is not complete." << endl;
	} else {
		cout << "Chr boundry" << pos_start << "-" << pos_end << endl;
	}
	return Res;
}
void PrintChromosome(string chr, long Boundry[], string FAddress) {
	long StartIndex = Boundry[0];
	long EndIndex = Boundry[1];
	ifstream file(FAddress);
	file.seekg(StartIndex, file.beg);
	string content;
	string ChrAddr = GetFileDirectory(FAddress) + chr + "."
			+ GetFileName(FAddress) + ".fa";
	ofstream outputFile(ChrAddr);
	cout << "Generating chromosome in range:" << StartIndex << "-" << EndIndex
			<< endl;
	//outputFile<<"<chr21";
	while (file >> content && file.tellg() <= EndIndex) {
		//cout<<"1";
		outputFile << content << endl;
	}
	outputFile << content << endl;
	file.close();
	outputFile.close();
}
unsigned long LongRandom(long low, long high) {


	typedef boost::uniform_real<> NumberDistribution;
	typedef boost::mt19937 RandomNumberGenerator;
	typedef boost::variate_generator<RandomNumberGenerator&,
			NumberDistribution> Generator;
	NumberDistribution distribution(low, high);
	RandomNumberGenerator generator;
	Generator numberGenerator(generator, distribution);
	generator.seed(std::time(0)); // seed with the current time

	long val= numberGenerator() ;
	return val;
	////2///////////
	//    typedef boost::mt19937 RNGType;
	//
	//    RNGType rng( time(0)*time(0)%50 *time(0) );
	//     boost::uniform_int<> one_to_six( low, high );
	//     boost::variate_generator< RNGType, boost::uniform_int<> >
	//                   dice(rng, one_to_six);
	//
	//         int n  = dice();
	//     return n;

	////////1///////////
	//	long Diff = high - low;
	//	srand(time(0));
	//
	//	long RNDDDD = rand();
	//
	//	cout<<"GENERATINH RANDOM:"<<RNDDDD<<endl;
	//	long RandNum = low + (long) (RNDDDD % Diff);
	//	return RandNum;
}

string RemoveCharFromString(char c, string str) {
	//cout <<endl<<"Data:"<<str.length()<<str<<endl;
	str.erase(std::remove(str.begin(), str.end(), c), str.end());
	return str;
}
string RemoveCharFromCharArray(char c, char arr[]) {

	char Res[strlen(arr)];
	int Xindex = 0;
	for (int i = 0; arr[i] != '\0'; i++) {

		if (arr[i] != c) {
			Res[Xindex++] = arr[i];
		}
	}
	Res[Xindex] = '\0';
	Res[Xindex + 1] = '\n';
	cout << "After remove:" << Res << endl;
	return Res;
}
string ReadPosition(string Chr, int StartIndex, int EndIndex, string FAddr) {
	cout << "Generating chromosome in range:" << StartIndex << "-" << EndIndex
			<< endl;
	StartIndex += Chr.length() + 2;
	EndIndex += Chr.length() + 2;

	ifstream file(FAddr);
	file.seekg(StartIndex, file.beg);
	file.clear();
	string content;
	string Res = "";
	char * buffer = new char[EndIndex - StartIndex];
	for (int i = 0; i < EndIndex - StartIndex + 1; i++) {
		buffer[i] = '\0';
	}
	file.read(buffer, EndIndex - StartIndex);

	return buffer;
}

std::string ReplaceString(std::string subject, const std::string& search,
		const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}
void GenerateOverlappedReads_RandomSize(int TotalReads, long CenterIndex,
		string chr, string FAddress) {

}
int CountWhiteSpace(string str) {
	int sum = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '\n')
			sum++;
	}
	return sum;
}
char FindVariant(char c) {
	return 'X';
	if (c == 'A' || c == 'a')
		return 'C';
	else if (c == 'T' || c == 't')
		return 'A';
	else if (c == 'C' || c == 'c')
		return 'G';
	else if (c == 'G' || c == 'g')
		return 'T';
	return c;
}

string GenerateQualityForRead(string Read,string Quality)
{

	if (Quality.length()==0)
	{
		Quality="~";
	}
	if (Quality.length()==Read.length())
	{
		return Quality;
	}
	else
	{
		string QualityStr="";
		for (int i=0;i<Read.length();i++)
		{
			QualityStr+=Quality[0];
		}
		return QualityStr;
	}

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

//

