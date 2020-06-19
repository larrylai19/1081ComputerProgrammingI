#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace::std;

struct MemberRecord
{
   char IDNumber[ 12 ];   // account number
   char password[ 24 ];   // password
   char name[ 8 ];        // name
};

// input memberDetails from the file Members.dat
void loadMemberDetails( vector< MemberRecord > &memberDetails );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// login
void login( const vector< MemberRecord > &memberDetails );

// there exists a member with specified IDNumber and password
bool valid( char IDNumber[], char password[],
            const vector< MemberRecord > &memberDetails );

// add a new member
void registration( vector< MemberRecord > &memberDetails );

// return true if IDNumber is a legal ID number
bool legalID( char IDNumber[] );

// return true if IDNumber belongs to memberDetails
bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails );

// output all memberDetails into the file Members.dat
void saveMemberDetails( const vector< MemberRecord > &memberDetails );

int main()
{
   vector< MemberRecord > memberDetails; // member details for all members
   int numMembers = 0;                     // number of members

   loadMemberDetails( memberDetails );

   cout << "Welcome to the Cashbox Party World!\n\n";

   int choice;

   while( true )
   {
      cout << "1 - Login\n";
      cout << "2 - Registration\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch ( choice )
      {
      case 1:
         login( memberDetails );
         break;

      case 2:
         registration( memberDetails );
         break;

      case 3:
         saveMemberDetails( memberDetails );
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;

      default:
         cout << "\nIncorrect choice!\n";
         break;
      }
   }

   system( "pause" );
}

// 讀取Members.dat並存入memberDetails，若無此檔便新建
void loadMemberDetails(vector< MemberRecord >& memberDetails)
{
	ifstream inFile("Members.dat", ios::binary); // 先嘗試開啟Members.dat
	if (!inFile) // 如果!inFile為true代表開啟失敗(可能為此檔案不存在導致)
	{
		inFile.close(); // 將原本的inFile關閉
		ofstream CreateFile("Members.dat", ios::binary); // 以輸出的方式開啟Members.dat(若無此檔會自動建立)
		if (!CreateFile)
		{
			cout << "File could not be opened!";
			exit(1);
		}
		CreateFile.close(); // 關閉CreateFile
		ifstream inFile("Members.dat", ios::binary); // 以讀取的方式開啟Members.dat(沒意外不會出錯)
	}
	MemberRecord in;

	while (inFile.read((char*)&in, sizeof(MemberRecord))) // 讀檔
		memberDetails.push_back(in);
}

// 判斷輸入的東西是否為範圍內的整數
int inputAnInteger(int begin, int end)
{
	/*char input = {}; 
	cin >> input;
	int num = input - '0';
	if (num >= begin && num <= end)
		return num;
	else
		return -1;*/

	char input[80];
	cin.getline(input, 80, '\n');
	if (!strlen(input)) // 如果讀取到空的就重新讀取(不加會出錯)
		cin.getline(input, 80, '\n');
	
	for (unsigned int i = 0; i < strlen(input); i++) // 如果讀取到的字串含有非數字的字元就回傳-1
		if (input[i] < '0' || input[i]>'9')
			return -1;
		
	int num = atoi(input); // 將num從char(a)轉成int(i)
	if (num >= begin && num <= end)
		return num;
	
	return -1;
}

// 判斷輸入的ID number與password是否存在於memberDetails內
void login(const vector< MemberRecord >& memberDetails)
{
	MemberRecord log;
	cout << "Please enter your ID number:";
	cin >> log.IDNumber;
	cout << "Enter your password:";
	cin >> log.password;
	if (!valid(log.IDNumber, log.password, memberDetails)) // 若輸入錯誤就重新輸入
	{
		cout << "\nInvalid account number or password. Please try again.\n\n";
		return login(memberDetails);
	}
	
	cout << endl;
	return;
}

// 若輸入的ID number與password存在於memberDetails內就回傳True否則回傳False
bool valid(char IDNumber[], char password[],
	const vector< MemberRecord >& memberDetails)
{
	if (IDNumber[0] >= 'a' && IDNumber[0] <= 'z') // 若輸入的第一個字母為小寫就轉為大寫
		IDNumber[0] -= 32;
	for (unsigned int i = 0; i < memberDetails.size(); i++)
		if (!strcmp(password, memberDetails[i].password) && !strcmp(IDNumber, memberDetails[i].IDNumber))
			return true;

	return false;
}

// 註冊一個新帳戶
void registration(vector< MemberRecord >& memberDetails)
{
	MemberRecord reg;
	cout << "Input your ID Number:";
	cin >> reg.IDNumber;
	if (!legalID(reg.IDNumber)) // 若輸入的ID number無效
	{
		cout << "\nThe ID number " << reg.IDNumber << " is illegal.\n\n";
		return;
	}
	else if (existingID(reg.IDNumber, memberDetails)) // 若輸入的ID number已經存在於memberDetails
	{
		cout << "\nYou are already a member!\n\n";
		return;
	}
	cout << "\nInput your name:";
	cin >> reg.name;
	cout << "\nChoose a password:";
	cin >> reg.password;
	memberDetails.push_back(reg); // 將資料存入memberDetails
	cout << "\nRegistration Completed!\n\n";
}

// 若輸入的ID number有效就回傳True否則回傳False
bool legalID(char IDNumber[])
{
	char keep = IDNumber[0];
	int first = 0, checknum = 0;
	if (IDNumber[0] >= 'a' && IDNumber[0] <= 'z') // 若第一個英文字母為小寫則轉成大寫
		IDNumber[0] -= 32;
	//-----------------------------將第一個英文字母轉成對應的數字-------------------------
	if (IDNumber[0] >= 'A' && IDNumber[0] <= 'H')
		first = IDNumber[0] - 55;
	if (IDNumber[0] == 'I')
		first = 34;
	if (IDNumber[0] >= 'J' && IDNumber[0] <= 'N')
		first = IDNumber[0] - 56;
	if (IDNumber[0] == 'O')
		first = 35;
	if (IDNumber[0] >= 'P' && IDNumber[0] <= 'V')
		first = IDNumber[0] - 57;
	if (IDNumber[0] == 'W')
		first = 32;
	if (IDNumber[0] >= 'X' && IDNumber[0] <= 'Y')
		first = IDNumber[0] - 58;
	if (IDNumber[0] == 'Z')
		first = 33;
	//-----------------------------將第一個英文字母轉成對應的數字-------------------------
	checknum = first / 10 + first % 10 * 9;
	for (int i = 1; i <= 8; i++)
		checknum += (IDNumber[i] - '0') * (9 - i);
	checknum %= 10;
	if (checknum != 0)
		checknum = 10 - checknum;
	if (IDNumber[9] - '0' == checknum)
		return true;
	
	IDNumber[0] = keep;
	return false;
}

// 若輸入的ID number存在於memberDetails就回傳True否則回傳False
bool existingID(char IDNumber[], const vector< MemberRecord >& memberDetails)
{
	for (unsigned int i = 0; i < memberDetails.size(); i++)
		if (!strcmp(IDNumber, memberDetails[i].IDNumber))
			return true;
		
	return false;
}

// 將memberDetails內的資料存入Members.dat
void saveMemberDetails(const vector< MemberRecord >& memberDetails)
{
	ofstream outFile("Members.dat", ios::binary);
	if (!outFile)
	{
		cout << "File could not be opened!\n";
		exit(1);
	}
	for (unsigned int i = 0; i < memberDetails.size(); i++)
		outFile.write((char*)&memberDetails[i], sizeof(MemberRecord));
}
