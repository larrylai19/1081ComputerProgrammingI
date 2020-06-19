#include <iostream>
#include <cstring>
using namespace std;

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size );

// product = multiplicand * multiplier
void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandSize, int multiplierSize, int &productSize );

const int arraySize = 501;

int main()
{


   return 0;
}

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size )
{
   for( int i = 0; i < size; i++ )
      if( hugeInt[ i ] != 0 )
         return false;
   return true;
}

// product = multiplicand * multiplier
void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandSize, int multiplierSize, int &productSize )
{

}