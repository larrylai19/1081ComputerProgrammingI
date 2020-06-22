#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size );

// return true if and only if hugeInt1 == hugeInt2
bool equal( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// difference = minuend - subtrahend
void subtraction( int minuend[], int subtrahend[], int difference[],
                  int minuendSize, int subtrahendSize, int &differenceSize );

// product *= multiplicand
void multiplication( int multiplicand[], int product[], int multiplicandSize, int &productSize );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize );

// hugeInt /= 10
void divideBy10( int hugeInt[], int &size );

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
         int dividend[ arraySize ] = {};
         int divisor[ arraySize ] = {};
         int quotient[ arraySize ] = {};
         int remainder[ arraySize ] = {};

         int dividendSize = 1;
         int divisorSize = 1;
         int quotientSize = 1;
         int remainderSize = 1;

         int temp = t;
         int base[ arraySize ] = {};
         int baseSize = 0;
         while( temp > 0 )
         {
            base[ baseSize++ ] = temp % 10;
            temp /= 10;
         }

         dividend[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiplication( base, dividend, baseSize, dividendSize );
            if( dividendSize > arraySize )
               break;
         }

         if( dividendSize > arraySize )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            divisor[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
               multiplication( base, divisor, baseSize, divisorSize );

            int oneSize = 1;
            int one[ 10 ] = {};
            one[ 0 ] = 1;
            subtraction( dividend, one, dividend, dividendSize, oneSize, dividendSize );
            subtraction( divisor, one, divisor, divisorSize, oneSize, divisorSize );

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
bool isZero( int hugeInt[], int size )
{
   for( int i = 0; i < size; i++ )
      if( hugeInt[ i ] != 0 )
         return false;
   return true;
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( int hugeInt1[], int hugeInt2[], int size1, int size2 )
{
	if(size1 == size2)
	{
		for(int i = size1; i > 0; i--)
		{
			if(hugeInt1[i-1] != hugeInt2[i-1])
				return false;
		}
		return true;
	}
	else
		return false;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 )
{
	if(size1 > size2)
		return false;
	else if(size1 == size2)
	{
		for(int i = size1; i > 0; i--)
		{
			if(hugeInt1[i-1] < hugeInt2[i-1])
				return true;
			else if(hugeInt1[i-1] > hugeInt2[i-1])
				return false;
		}
		return false;
	}
	else
		return true;
}

// difference = minuend - subtrahend
void subtraction( int minuend[], int subtrahend[], int difference[],
                  int minuendSize, int subtrahendSize, int &differenceSize )
{
	differenceSize = ( minuendSize >= subtrahendSize ) ? minuendSize : subtrahendSize;
	
	for(int i = 0; i < minuendSize; i++)
		difference[i] = minuend[i];
	
	for(int i = minuendSize; i < differenceSize; i++)
		difference[i] = 0;
	
	for(int i = 0; i < subtrahendSize; i++)
		difference[i] -= subtrahend[i];
	
	for(int i = 0; i < differenceSize; i++)
		if(difference[i] < 0)
		{
			difference[i] += 10;
			difference[i+1]--;
		}
	
	for(int i = differenceSize; difference[i-1] == 0;i--)
		differenceSize--;
}

// product = multiplicand * multiplier
void multiplication( int multiplicand[], int product[], int multiplicandSize, int &productSize )
{
	productSize = multiplicandSize + multiplicandSize;
	
	for(int i = 0; i < productSize; i++)
		product[i] = 0;
	
	for(int i = 0; i < multiplicandSize; i++)
		for(int j = 0; j < multiplicandSize; j++)
		{
			product[j+i] += multiplicand[i] * multiplicand[j];
			if(product[j+i] >= 10)
			{
				product[j+i+1] += product[j+i]/10;
				product[j+i] %= 10;
			}
		} 
	for(int i = productSize; product[i-1] == 0; i--)
		productSize--;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize )
{
	if(isZero(dividend, dividendSize))
	{
		quotientSize = 1;
		quotient[0] = 0;
		remainderSize = 1;
		remainder[0] = 0;
		return;
	}
	else if(equal(dividend, divisor, dividendSize, divisorSize))
	{
		quotientSize = 1;
		quotient[0] = 1;
		remainderSize = 1;
		remainder[0] = 0;
		return;
	}
	else if(less(dividend, divisor, dividendSize, divisorSize))
	{
		quotientSize = 1;
		quotient[0] = 0;
		remainderSize = dividendSize;
		for(int i = 0; i < dividendSize; i++)
			remainder[i] = dividend[i];
		return;
	}
	else
	{
		int n = dividendSize - divisorSize;
		int bufferSize = dividendSize;
		remainderSize = dividendSize;
		int buffer[arraySize] = {};
		
		for(int i = 0; i < remainderSize; i++)
			remainder[i] = dividend[i];
		
		for(int i = 0; i < divisorSize; i++)
			buffer[i+n] = divisor[i];

		quotientSize = dividendSize - divisorSize;
		
		if(less(dividend, buffer, dividendSize, bufferSize))
			divideBy10(buffer, bufferSize);
		else
			quotientSize++;
		
		for(int i = 0; i < quotientSize; i++)
			quotient[i] = 0;
			
		for(int k = quotientSize - 1; k >= 0; k--)
		{
			while(less(buffer, remainder, bufferSize, remainderSize) || equal(buffer, remainder, bufferSize, remainderSize))
			{
				subtraction(remainder, buffer, remainder, remainderSize, bufferSize, remainderSize);
				quotient[k] ++;
			}
			if(remainder[0] == 0)
				return;
			divideBy10(buffer, bufferSize);
		}
	}
	return;
}

// hugeInt /= 10
void divideBy10( int hugeInt[], int &size )
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
