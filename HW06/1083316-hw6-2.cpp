#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>

// returns true if and only if the specified huge integer is zero
bool isZero( int *hugeInt, int size );

void reset( int *&hugeInt, int &size );

// return true if and only if hugeInt1 == hugeInt2
bool equal( int *hugeInt1, int *hugeInt2, int size1, int size2 );

// a recursive function that returns true if and only if hugeInt1 == hugeInt2
// provided that size1 == size2
bool recursiveEqual( int *hugeInt1, int *hugeInt2, int last );

// returns true if and only if hugeInt1 < hugeInt2
bool less( int *hugeInt1, int *hugeInt2, int size1, int size2 );

// a recursive function that returns true if and only if hugeInt1 < hugeInt2
// provided that size1 == size2
bool recursiveLess( int *hugeInt1, int *hugeInt2, int last );

// minuend -= subtrahend
void subtractionAssignment( int *&minuend, int *subtrahend,
                            int &minuendSize, int subtrahendSize );

// product *= multiplicand
void multiplicationAssignment( int *multiplicand, int *&product,
                               int multiplicandSize, int &productSize );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int *dividend, int *divisor, int *&quotient, int *&remainder,
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize );

// hugeInt /= 10
void divideBy10( int *hugeInt, int &size );

const int arraySize = 200;

int main()
{
   int t, a, b;
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a % b != 0 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( ( a - b ) * static_cast< int >( log10( t ) ) > 99 )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         int *dividend = new int[ 1 ]();
         int *divisor = new int[ 1 ]();
         int *quotient = new int[ 1 ]();
         int *remainder = new int[ 1 ]();

         int dividendSize = 1;
         int divisorSize = 1;
         int quotientSize = 1;
         int remainderSize = 1;

         int temp = t;
         int *base = new int[ 10 ]();
         int baseSize = 0;
         while( temp > 0 )
         {
            base[ baseSize++ ] = temp % 10;
            temp /= 10;
         }

         dividend[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiplicationAssignment( base, dividend, baseSize, dividendSize );
            if( dividendSize > arraySize )
               break;
         }

         if( dividendSize > arraySize )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            divisor[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
               multiplicationAssignment( base, divisor, baseSize, divisorSize );

            int oneSize = 1;
            int *one = new int[ 1 ]();
            one[ 0 ] = 1;
            subtractionAssignment( dividend, one, dividendSize, oneSize );
            subtractionAssignment( divisor, one, divisorSize, oneSize );

            division( dividend, divisor, quotient, remainder,
                      dividendSize, divisorSize, quotientSize, remainderSize );

            if( quotientSize < 100 && isZero( remainder, remainderSize ) )
               for( int i = quotientSize - 1; i >= 0; i-- )
                  cout << quotient[ i ];
            else
               cout << "is not an integer with less than 100 digits.";
            cout << endl;
         }
      }
   }
}

// returns true if and only if the specified huge integer is zero
bool isZero( int *hugeInt, int size )
{
   if( size == 1 && hugeInt[ 0 ] == 0 )
      return true;
   return false;
}

void reset( int *&hugeInt, int &size )
{
   size = 1;
   delete[] hugeInt;
   hugeInt = new int[ 1 ]();
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( int *hugeInt1, int *hugeInt2, int size1, int size2 )
{
   if( size1 != size2 )
      return false;

   return recursiveEqual( hugeInt1, hugeInt2, size1 - 1 );
}

// a recursive function that returns true if and only if hugeInt1 == hugeInt2
// provided that size1 == size2
bool recursiveEqual( int *hugeInt1, int *hugeInt2, int last )
{
	if (hugeInt1[last] == hugeInt2[last])
	{
		if (last == 0)
			return true;
		recursiveEqual(hugeInt1, hugeInt2, last - 1);
	}
	else
		return false;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int *hugeInt1, int *hugeInt2, int size1, int size2 )
{
   if( size1 < size2 )
      return true;
   if( size1 > size2 )
      return false;

   return recursiveLess( hugeInt1, hugeInt2, size1 - 1 );
}

// a recursive function that returns true if and only if hugeInt1 < hugeInt2
// provided that size1 == size2
bool recursiveLess( int *hugeInt1, int *hugeInt2, int last )
{
	if (hugeInt1[last] < hugeInt2[last])
		return true;
	else if (hugeInt1[last] > hugeInt2[last])
		return false;

	if (last > 0)
		recursiveLess(hugeInt1, hugeInt2, last - 1);
	else
		return false;
}

// minuend -= subtrahend
void subtractionAssignment( int *&minuend, int *subtrahend, int &minuendSize, int subtrahendSize )
{
	if (equal(minuend, subtrahend, minuendSize, subtrahendSize))
	{
		minuendSize = 1;
		delete[] minuend;
		minuend = new int[minuendSize];
		minuend[0] = 0;
	}
	else
	{
		for (int i = 0; i < subtrahendSize; i++)
			minuend[i] -= subtrahend[i];

		for (int i = 0; i < minuendSize; i++)
			if (minuend[i] < 0)
			{
				minuend[i] += 10;
				minuend[i + 1]--;
			}

		for (int i = minuendSize; minuend[i - 1] == 0; i--)
			minuendSize--;
	}
}

// product *= multiplicand
void multiplicationAssignment( int *multiplicand, int *&product, int multiplicandSize, int &productSize )
{
	if (isZero(multiplicand, multiplicandSize) == 1 || isZero(product, productSize) == 1) {
		productSize = 1;
		delete[] product;
		product = new int[productSize]();
		product[0] = 0;
	}
	else {
		int ptSize = productSize + multiplicandSize;
		int* pt = new int[ptSize]();

		for (int i = 0; i < productSize; i++) 
			for (int j = 0; j < multiplicandSize; j++)
				pt[j + i] += multiplicand[j] * product[i];
		
		for (int i = 0; i < ptSize; i++) 
			if (pt[i] > 9) 
			{
				pt[i + 1] += pt[i] / 10;
				pt[i] %= 10;
			}
		
		for (int i = ptSize-1; pt[i] == 0; i--)
			ptSize--;

		productSize = ptSize;
		delete[] product;
		product = new int[productSize]();
		for (int i = 0; i < ptSize; i++)
			product[i] = pt[i];

		delete[] pt;
	}
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int *dividend, int *divisor, int *&quotient, int *&remainder,
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize )
{
   if( isZero( dividend, dividendSize ) )
   {
      reset( quotient, quotientSize );
      reset( remainder, remainderSize );
      return;
   }
   else if (equal(dividend, divisor, dividendSize, divisorSize))
   {
	   quotientSize = 1;
	   remainderSize = 1;
	   delete[] quotient;
	   delete[] remainder;
	   quotient = new int[quotientSize]();
	   remainder = new int[remainderSize]();
	   quotient[0] = 1;
	   remainder[0] = 0;
	   return;
   }
   else if (less(dividend, divisor, dividendSize, divisorSize))
   {
	   quotientSize = 1;
	   remainderSize = dividendSize;
	   delete[] quotient;
	   delete[] remainder;
	   quotient = new int[quotientSize]();
	   remainder = new int[dividendSize]();
	   quotient[0] = 0;
	   for (int i = 0; i < remainderSize; i++)
		   remainder[i] = dividend[i];
	   return;
   }
   else
   {
	   int n = dividendSize - divisorSize;
	   int bufferSize = dividendSize;
	   remainderSize = dividendSize;
	   int* buffer = new int[bufferSize]();

	   delete[] remainder;
	   remainder = new int[remainderSize]();

	   quotientSize = dividendSize - divisorSize;

	   for (int i = 0; i < remainderSize; i++)
		   remainder[i] = dividend[i];

	   for (int i = 0; i < divisorSize; i++)
		   buffer[i + n] = divisor[i];

	   if (less(dividend, buffer, dividendSize, bufferSize))
		   divideBy10(buffer, bufferSize);
	   else
		   quotientSize++;

	   delete[] quotient;
	   quotient = new int[quotientSize]();

	   for (int k = quotientSize - 1; k >= 0; k--)
	   {
		   while (less(buffer, remainder, bufferSize, remainderSize) || equal(buffer, remainder, bufferSize, remainderSize))
		   {
			   subtractionAssignment(remainder, buffer, remainderSize, bufferSize);
			   quotient[k]++;
		   }
		   if (isZero(remainder, remainderSize))
			   return;
		   divideBy10(buffer, bufferSize);
	   }
	   delete[] buffer;
	   return;
   }

}

// hugeInt /= 10
void divideBy10( int *hugeInt, int &size )
{
   if( size == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      for( int i = 1; i < size; i++ )
         hugeInt[ i - 1 ] = hugeInt[ i ];

      size--;
      hugeInt[ size ] = 0;
   }
}