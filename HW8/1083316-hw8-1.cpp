#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h> 
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( char( *program )[ 100 ], int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( char sourceLine[] );

// deletes all string constants from sourceLine
void delStrConsts( char sourceLine[] );

// deletes all character constants from sourceLine
void delCharConsts( char sourceLine[] );

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers );

// stores all non-keyword strings in the array identifiers into a text file
void store( char ( *identifiers )[ 32 ], int numIdentifiers );

// returns true if and only if str is a C++ keyword
bool keyword( char str[] );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( char ( *identifiers )[ 32 ], int pos );

const char keywords[][ 20 ] = { "auto", "break", "case", "char", "const",
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
   char ( *program )[ 100 ] = new char[ 500 ][ 100 ]();
   int numLines = 0;

   // reads in a C++ program from a cpp file, and put it to the array program
   load( program, numLines );

   char ( *identifiers )[ 32 ] = new char[ 500 ][ 32 ]();
   int numIdentifiers = 0;

   for( int i = 0; i < numLines; i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      if( strcmp( program[ i ], "" ) != 0 )
         extractIdentifiers( program[ i ], identifiers, numIdentifiers );
         // extracts all identifiers from program[ i ], and put them into the array identifiers
   }

   // stores all non-keyword strings in the array identifiers into a text file
   store( identifiers, numIdentifiers );

   delete[] program; 
   delete[] identifiers;

	system( "pause" );
}

void load( char( *program )[ 100 ], int &numLines )
{
	ifstream inFile("test.cpp", ios::in);
	if (!inFile)
	{
		cout << "File could not be opened!\n";
		exit(1);
		return;
	}
	while (inFile.getline(program[numLines], 100))
		numLines++;
	return;
}

void delComment( char sourceLine[] )
{
	int c = 0;
	for (unsigned int i = 0; i < strlen(sourceLine); i++)
		if (sourceLine[i] != ' ')
		{
			c = 1;
			break;
		}

	if (c == 1)
	{
		for (unsigned int i = 0; i < strlen(sourceLine) - 1; i++)
			if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
			{
				for (unsigned int j = i; j < strlen(sourceLine); j++)
					sourceLine[j] = ' ';
				return;
			}
	}
	else
		return;
}

void delStrConsts( char sourceLine[] )
{
    int start = -1, end = -1;

    for(unsigned int i = 0; i < strlen(sourceLine); i++)
	{
        if (sourceLine[i] == '\"' )
		{
			if (start == -1)
				start = i;
			else if (end == -1)
				end = i;

			if (start != -1 && end != -1)
			{
				for (int j = start; j <= end; j++)
					sourceLine[j] = ' ';
				return;
            }
        }
    }
}

void delCharConsts( char sourceLine[] )
{
	int start = -1, end = -1;

	for (unsigned int i = 0; i < strlen(sourceLine); i++)
	{
		if (sourceLine[i] == '\'')
		{
			if (start == -1)
				start = i;
			else if (end == -1)
				end = i;

			if (start != -1 && end != -1)
			{
				for (int j = start; j <= end; j++)
					sourceLine[j] = ' ';
				return;
			}
		}
	}
}

void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers )
{
   int start = -1, end = -1;

    for(unsigned int i = 0; i < strlen(sourceLine); i++)
	{
		start = -1, end = -1;
        for(unsigned int j=i; j < strlen(sourceLine); j++)
		{
			if (sourceLine[j] == '_' || (sourceLine[j] >= 'a' && sourceLine[j] <= 'z') || (sourceLine[j] >= 'A' && sourceLine[j] <= 'Z'))
			{
				if (start == -1)
					start = j;
			}
			else if (sourceLine[j] == '_' || (sourceLine[j] >= '0' && sourceLine[j] <= '9'))
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
            for(int j = 0; j < end - start; j++)
			{
				identifiers[numIdentifiers][j] = sourceLine[start + j];
				sourceLine[start + j] = ' ';
            }
			numIdentifiers++;
        }
    }
}

void store( char ( *identifiers )[ 32 ], int numIdentifiers )
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

bool keyword( char str[] )
{
	unsigned int j = 0;
	for (unsigned int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
	{
		if (strlen(str) != strlen(keywords[i]))
			continue;

		for (j = 0; j < strlen(str); j++)
			if (str[j] != keywords[i][j])
				break;

		if (j == strlen(str))
			return true;
	}
	return false;
}

bool duplicate( char ( *identifiers )[ 32 ], int pos )
{
	unsigned int j = 0;
    for(int i = 0; i < pos; i++)
	{
        if (strlen(identifiers[pos]) != strlen(identifiers[i]))
            continue;

        for(j = 0; j < strlen(identifiers[pos]); j++)
			if (identifiers[pos][j] != identifiers[i][j])
				break;

        if (j == strlen(identifiers[pos]))
            return true;
    }
    return false;
}
