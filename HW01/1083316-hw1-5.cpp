#include <iostream>
using namespace std;

int main()
{
   int year;
   start: 
   cout << "Enter a year ( 1583-3000 ): ";
   cin >> year;
   if(year>=1583&&year<=3000)
   {
    if(year%4==0&&(year%100!=0||year%400==0))
    cout << "Year " << year << " is a leap year.\n";
    else
    cout << "Year " << year << " is a common year.\n";
    system( "pause" );
   }
   else
   goto start;
}
