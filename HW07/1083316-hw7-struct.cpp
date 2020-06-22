// Huge integer addition, subtraction, multiplication and division
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <cstring> 

const int numTestCases = 22;
const int arraySize = 200;

// HugeInt struct definition
struct HugeInt
{
   int size = 1;       // the number of digits of the integer; it can never be zero
   int *elems = new int[ 1 ](); // used to store a nonnegative integer, one digit per element
};

// enable user to input a positive huge integer
void input( istream &inFile, HugeInt &hugeInt );

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, HugeInt &hugeInt1, HugeInt &hugeInt2,
              HugeInt &hugeInt3, HugeInt &hugeInt4 );

// outputs hugeInt.elems[ hugeInt.size - 1 .. 0 ]
void output( ostream &outFile, HugeInt &hugeInt );

// a recursive function that outputs hugeInt.elems[ last .. 0 ]
void recursiveOutput( ostream &outFile, HugeInt &hugeInt, int last );

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt &hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveEqual( HugeInt &hugeInt1, HugeInt &hugeInt2, int last );

// return true if and only if hugeInt1 < hugeInt2
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// a recursive function that returns true if and only if hugeInt1 < hugeInt2
// provided that hugeInt1.size == hugeInt2.size
bool recursiveLess( HugeInt &hugeInt1, HugeInt &hugeInt2, int last );

// sum = addend + adder
void addition( HugeInt &addend, HugeInt &adder, HugeInt &sum );

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( HugeInt &minuend,
                  HugeInt &subtrahend, HugeInt &difference );

// product = multiplicand * multiplier
void multiplication( HugeInt &multiplicand,
                     HugeInt &multiplier, HugeInt &product );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( HugeInt &dividend, HugeInt &divisor,
               HugeInt &quotient, HugeInt &remainder );

// hugeInt2 = hugeInt1; assignment
void assign( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// hugeInt /= 10
void divideByTen( HugeInt &hugeInt );

void reset( HugeInt &hugeInt );

int main()
{
   system( "mode con cols=122" );

   ifstream inFile( "Test cases.txt", ios::in );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   ofstream outFile( "Result.txt", ios::out );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   HugeInt hugeInt1;
   HugeInt hugeInt2;
   HugeInt hugeInt3;
   HugeInt hugeInt4;

   for( int i = 0; i < numTestCases; i++ )
   {
      input( inFile, hugeInt1 );
      input( inFile, hugeInt2 );
      perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      reset( hugeInt1 );
      reset( hugeInt2 );
   }

   delete[] hugeInt1.elems;
   delete[] hugeInt2.elems;
   delete[] hugeInt3.elems;
   delete[] hugeInt4.elems;

   inFile.close();
   outFile.close();

   system( "pause" );
}

// enable user to input a positive huge integer
void input( istream &inFile, HugeInt &hugeInt )
{
   char numericString[ arraySize ];

   inFile >> numericString;

   hugeInt.size = strlen( numericString );
   delete[] hugeInt.elems;
   hugeInt.elems = new int[ hugeInt.size ];
   for( int i = 0; i < hugeInt.size; i++ )
      hugeInt.elems[ i ] = numericString[ hugeInt.size - i - 1 ] - '0';
}

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, HugeInt &hugeInt1, HugeInt &hugeInt2,
                                HugeInt &hugeInt3, HugeInt &hugeInt4 )
{
   output( outFile, hugeInt1 );
   output( outFile, hugeInt2 );

   addition( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 + hugeInt2
   output( outFile, hugeInt3 );
   reset( hugeInt3 );

   if( less( hugeInt1, hugeInt2 ) )
   {
      outFile << '-';
      subtraction( hugeInt2, hugeInt1, hugeInt3 ); // hugeInt3 = hugeInt2 - hugeInt1
      output( outFile, hugeInt3 );
   }
   else
   {
      subtraction( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 - hugeInt2
      output( outFile, hugeInt3 );
   }
   reset( hugeInt3 );

   multiplication( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 * hugeInt2
   output( outFile, hugeInt3 );
   reset( hugeInt3 );

   if( isZero( hugeInt2 ) )
   {
      outFile << "DivideByZero!\n";
      outFile << "DivideByZero!\n";
   }
   else
   {
      // hugeInt3 = hugeInt1 / hugeInt2;   hugeInt4 = hugeInt1 % hugeInt2
      division( hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      output( outFile, hugeInt3 );
      output( outFile, hugeInt4 );
      reset( hugeInt3 );
      reset( hugeInt4 );
   }

   outFile << endl;
}

// outputs hugeInt.elems[ hugeInt.size - 1 .. 0 ]
void output( ostream &outFile, HugeInt &hugeInt )
{
	if(isZero(hugeInt))
		outFile << 0;
	else 
		recursiveOutput( outFile, hugeInt, hugeInt.size - 1 );
		
   outFile << endl;
}

// a recursive function that outputs hugeInt.elems[ last .. 0 ]
void recursiveOutput( ostream &outFile, HugeInt &hugeInt, int last )
{
	while(last >=0 )
	{
		outFile << hugeInt.elems[last];
		return recursiveOutput(outFile, hugeInt, last-1);
	}
}

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt &hugeInt )
{
   if( hugeInt.size == 1 && hugeInt.elems[ 0 ] == 0 )
      return true;
   return false;
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
   if( hugeInt1.size != hugeInt2.size )
      return false;

   return recursiveEqual( hugeInt1, hugeInt2, hugeInt1.size - 1 );
}

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveEqual( HugeInt &hugeInt1, HugeInt &hugeInt2, int last )
{
	if(hugeInt1.elems[last] == hugeInt2.elems[last])
	{
		if(last == 0)
			return true;
		recursiveEqual(hugeInt1, hugeInt2, last - 1);
	}
	else
		return false;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
   if( hugeInt1.size < hugeInt2.size )
      return true;
   if( hugeInt1.size > hugeInt2.size )
      return false;

   return recursiveLess( hugeInt1, hugeInt2, hugeInt1.size - 1 );
}

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveLess( HugeInt &hugeInt1, HugeInt &hugeInt2, int last )
{
	if(hugeInt1.elems[last] < hugeInt2.elems[last])
		return true;
	else if(hugeInt1.elems[last] > hugeInt2.elems[last])
		return false;
		
	if(last > 0)
		recursiveLess(hugeInt1, hugeInt2, last-1);
	else
		return false;
}

// sum = addend + adder
void addition( HugeInt &addend, HugeInt &adder, HugeInt &sum )
{
   sum.size = ( addend.size >= adder.size ) ? addend.size + 1 : adder.size + 1;

   delete [] sum.elems;
   sum.elems = new int[ sum.size ]();

   for( int i = 0; i < addend.size; i++ )
      sum.elems[ i ] = addend.elems[ i ];

   for( int i = 0; i < adder.size; i++ )
      sum.elems[ i ] += adder.elems[ i ];

   for( int i = 0; i < sum.size - 1; i++ )
      if( sum.elems[ i ] > 9 ) // determine whether to carry a 1
      {
         sum.elems[ i ] -= 10; // reduce to 0-9
         sum.elems[ i + 1 ]++;
      }

   if( sum.elems[ sum.size - 1 ] == 0 )
      sum.size--;
}

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( HugeInt &minuend,
                  HugeInt &subtrahend, HugeInt &difference )
{
	if(equal(minuend, subtrahend))
		reset(difference);	
	else
	{
		difference.size = ( minuend.size >= subtrahend.size) ? minuend.size : subtrahend.size;
		
		delete[] difference.elems;
		difference.elems = new int[difference.size]();
		
		for(int i = 0; i < minuend.size; i++)
			difference.elems[i] = minuend.elems[i];
			
		for(int i = minuend.size; i < difference.size; i++)
			difference.elems[i] = 0;
			
		for(int i = 0; i < subtrahend.size; i++)
			difference.elems[i] -= subtrahend.elems[i];
		
		for(int i = 0; i < difference.size; i++)
			if(difference.elems[i] < 0)
			{
				difference.elems[i] += 10;
				difference.elems[i+1]--;
			}
		
		for(int i = difference.size; difference.elems[i-1] == 0; i--)
			difference.size--;		
	}
}

// product = multiplicand * multiplier
void multiplication( HugeInt &multiplicand,
                     HugeInt &multiplier, HugeInt &product )
{
	if ((isZero(multiplicand)) == 1 || (isZero(multiplier)) == 1)
		reset(product);
	else
	{
		product.size = multiplicand.size + multiplier.size;

		delete[] product.elems;
		product.elems = new int[product.size]();

		for(int i = 0; i < multiplier.size; i++)
			for (int j = 0; j < multiplicand.size; j++)
			{
				product.elems[j + i] += multiplier.elems[i] * multiplicand.elems[j];
				if (product.elems[j + i] >= 10)
				{
					product.elems[j + i + 1] += product.elems[j + i] / 10;
					product.elems[j + i] %= 10;
				}
			}
		for (int i = product.size; product.elems[i - 1] == 0; i--)
			product.size--;
	}
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( HugeInt &dividend, HugeInt &divisor,
               HugeInt &quotient, HugeInt &remainder )
{
   if( isZero( dividend ) )
   {
      reset( quotient );
      reset( remainder );
      return;
   }
   else if (equal(dividend, divisor))
   {
	   reset(quotient);
	   reset(remainder);
	   quotient.elems[0] = 1;
	   return;
   }
   else if (less(dividend, divisor))
   {
	   reset(quotient);
	   remainder.size = dividend.size;
	   assign(dividend, remainder);
	   return;
   }
   else
   {
	   int n = dividend.size - divisor.size;

	   HugeInt buffer;
	   buffer.size = dividend.size;
	   delete[] buffer.elems;
	   buffer.elems = new int[buffer.size]();

	   quotient.size = dividend.size - divisor.size;

	   assign(dividend, remainder);

	   for (int i = 0; i < divisor.size; i++)
		   buffer.elems[i + n] = divisor.elems[i];

	   if (less(dividend, buffer))
		   divideByTen(buffer);
	   else
		   quotient.size++;

	   delete[] quotient.elems;
	   quotient.elems = new int[quotient.size]();

	   HugeInt temp;
	   temp.size = remainder.size;

	   for (int k = quotient.size - 1; k >= 0; k--)
	   {
		   while (less(buffer, remainder) || equal(buffer, remainder))
		   {
			   delete[] temp.elems;
			   temp.elems = new int[temp.size]();
			   subtraction(remainder, buffer, temp);
			   quotient.elems[k]++;
			   assign(temp, remainder);
		   }
		   if (isZero(remainder))
			   return;
		   divideByTen(buffer);
	   }
   }
}

// hugeInt2 = hugeInt1; assignment
void assign( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
   hugeInt2.size = hugeInt1.size;
   delete[] hugeInt2.elems;
   hugeInt2.elems = new int[ hugeInt2.size ];
   for( int i = 0; i < hugeInt2.size; i++ )
      hugeInt2.elems[ i ] = hugeInt1.elems[ i ];
}

// hugeInt /= 10
void divideByTen( HugeInt &hugeInt )
{
   if( hugeInt.size == 1 )
      hugeInt.elems[ 0 ] = 0;
   else
   {
      for( int i = 1; i < hugeInt.size; i++ )
         hugeInt.elems[ i - 1 ] = hugeInt.elems[ i ];

      hugeInt.size--;
      hugeInt.elems[ hugeInt.size ] = 0;
   }
}

void reset( HugeInt &hugeInt )
{
   hugeInt.size = 1;
   delete[] hugeInt.elems;
   hugeInt.elems = new int[ 1 ]();
}
