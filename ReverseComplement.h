#include <iostream>
using namespace std;
enum SupportFileFormat
{
	FileFormat_FastA,
	FileFormat_FastQ
};
void GenerateReverseComplement(string Input, SupportFileFormat Format,string Output,bool RewriteNames);
bool FileExist(string name);
