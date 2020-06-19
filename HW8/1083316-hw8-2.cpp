#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( string *program, int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( string &sourceLine );

// deletes all string constants from sourceLine
void delStrConsts( string &sourceLine );

// deletes all character constants from sourceLine
void delCharConsts( string &sourceLine );

// deletes the first identifier from sourceLine, and returns it
string delFirstIdentifier( string &sourceLine );

// stores all non-keyword strings in the array identifiers into a text file
void store( string *identifiers, int numIdentifiers );

// return true if and only if "str" is a C++ keyword
bool keyword( string str );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( string *identifiers, int pos );

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
   string* program = new string[500]();
   int numLines = 0;

   // reads in a C++ program from a cpp file, and put it to the array program
   load( program, numLines );

   string *identifiers = new string[ 500 ]();
   string firstIdentifier;
   string null;
   int numIdentifiers = 0;

   for( int i = 0; i < numLines; i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      // extracts all identifiers from program[ i ], and put them into the array identifiers
      while( ( firstIdentifier = delFirstIdentifier( program[ i ] ) ) != null )
         identifiers[ numIdentifiers++ ] = firstIdentifier;
   }

   // stores all non-keyword strings in the array identifiers into a text file
   store( identifiers, numIdentifiers );
   delete[]program;
   delete[]identifiers;
	system( "pause" );
}

void load(string* program, int& numLines)
{
	string in;
	ifstream inFile("test.cpp", ios::in);
	if (!inFile)
	{
		cout << "File could not be open!\n";
		exit(1);
	}
	while (getline(inFile, in))
	{
		program[numLines] = in;
		numLines++;
	}
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

void store(string* identifiers, int numIdentifiers)
{
	ofstream outFile("result.txt", ios::out);
	if (!outFile)
	{
		cout << "File could not be open!\n";
		exit(1);
	}
	for (int i = 0; i < numIdentifiers; i++)
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

bool duplicate(string* identifiers, int pos)
{
	for (int i = 0; i < pos; i++)
		if (identifiers[pos] == identifiers[i])
			return true;
	return false;
}
