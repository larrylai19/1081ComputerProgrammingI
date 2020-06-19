#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace::std;

 // reads in a C++ program from a cpp file, and put it to the vector program
void load( vector< string > &program );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( string &sourceLine );

// deletes all string constants from sourceLine
void delStrConsts( string &sourceLine );

// deletes all character constants from sourceLine
void delCharConsts( string &sourceLine );

// deletes the first identifier from sourceLine, and returns it
string delFirstIdentifier( string &sourceLine );

// stores all non-keyword strings in the vector identifiers into a text file
void store( vector< string > &identifiers );

// return true if and only if "str" is a C++ keyword
bool keyword( string str );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( vector< string > &identifiers, int pos );

const string keywords[] = { "auto", "break", "case", "char", "const",
                            "continue", "default", "define","do", "double",
                            "else", "enum", "extern", "float", "for",
                            "goto", "if", "int", "long", "register",
                            "return", "short", "signed", "sizeof",
                            "static", "struct", "switch", "typedef",
                            "union", "unsigned", "void", "volatile",
                            "while", "bool", "catch", "class",
                            "const_cast", "delete", "dynamic_cast",
                            "explicit", "false", "friend", "inline",
                            "mutable", "namespace", "new", "operator",
                            "private", "protected", "public",
                            "reinterpret_cast", "static_cast", "template",
                            "this", "throw", "true", "try", "typeid",
                            "typename", "using", "virtual", "include" };

int main()
{
   vector< string > program;

   // reads in a C++ program from a cpp file, and put it to the vector program
   load( program );

   vector< string > identifiers;
   string firstIdentifier;
   string null;

   for( unsigned int i = 0; i < program.size(); i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      // extracts all identifiers from program[ i ], and put them into the vector identifiers
      while( ( firstIdentifier = delFirstIdentifier( program[ i ] ) ) != null )
         identifiers.push_back( firstIdentifier );
   }

   // stores all non-keyword strings in the vector identifiers into a text file
   store( identifiers );

	system( "pause" );
}

void load(vector< string >& program)
{
	string in;
	ifstream inFile("test.cpp", ios::in);
	if (!inFile)
	{
		cout << "File could not be open!\n";
		exit(1);
	}
	while (getline(inFile, in))
		program.push_back(in);
}

void delComment(string& sourceLine)
{
	if (sourceLine != "")	
		for (unsigned int i = 0; i < sourceLine.size() - 1; i++)		
			if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
			{
				sourceLine.erase(sourceLine.begin() + i, sourceLine.end());
				return;
			}
	return;
}

void delStrConsts(string& sourceLine)
{
	int start = -1, end = -1;
	for (unsigned int i = 0; i < sourceLine.size(); i++)
		if (sourceLine[i] == '\"')
		{
			if (start == -1)
				start = i;
			else
				end = i;

			if (start != -1 && end != -1)
			{
				sourceLine.erase(sourceLine.begin() + start, sourceLine.begin() + end);
				return;
			}
		}
	return;
}

void delCharConsts(string& sourceLine)
{
	int start = -1, end = -1;
	for (unsigned int i = 0; i < sourceLine.size(); i++)
		if (sourceLine[i] == '\'')
		{
			if (start == -1)
				start = i;
			else
				end = i;
				
			if (start != -1 && end != -1)
			{
				sourceLine.erase(sourceLine.begin() + start, sourceLine.begin() + end);
				return;
			}
		}
	return;
}

string delFirstIdentifier(string& sourceLine)
{
	int start = -1, end = -1;
	if (sourceLine == "")
		return sourceLine;
	else
	{
		for (unsigned int i = 0; i < sourceLine.size(); i++)
		{
			start = -1, end = -1;
			for (unsigned int j = i; j < sourceLine.size(); j++)
			{
				if (sourceLine[j] == '_' || (sourceLine[j] >= 'a' && sourceLine[j] <= 'z') || (sourceLine[j] >= 'A' && sourceLine[j] <= 'Z'))
				{
					if (start == -1)
						start = j;
				}
				else if(sourceLine[j] == '_' || (sourceLine[j] >= '0' && sourceLine[j] <= '9'))
                    continue;
				else
				{
					if (start != -1)
						end = j;
					break;
				}
			}
			if (start != -1 && end != -1)
			{
				string re(sourceLine.begin() + start, sourceLine.begin() + end);
				sourceLine.erase(sourceLine.begin() + start, sourceLine.begin() + end);
				return re;
			}
		}
		return "";
	}
}

void store(vector< string >& identifiers)
{
	ofstream outFile("result.txt", ios::out);
	if(!outFile)
	{
		cout << "File could not be open!\n";
		exit(1);
	}
	for (unsigned int i = 0; i < identifiers.size(); i++)
		if (!keyword(identifiers[i]) && !duplicate(identifiers, i))
		{
			cout << identifiers[i] << endl;
			outFile << identifiers[i] << endl;
		}
}

bool keyword(string str)
{
	for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
		if (str == keywords[i])
			return true;
	return false;
}

bool duplicate(vector< string >& identifiers, int pos)
{
	for (int i = 0; i < pos; i++)
		if (identifiers[pos] == identifiers[i])
			return true;
	return false;
}
