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

// Ū��Members.dat�æs�JmemberDetails�A�Y�L���ɫK�s��
void loadMemberDetails(vector< MemberRecord >& memberDetails)
{
	ifstream inFile("Members.dat", ios::binary); // �����ն}��Members.dat
	if (!inFile) // �p�G!inFile��true�N��}�ҥ���(�i�ର���ɮפ��s�b�ɭP)
	{
		inFile.close(); // �N�쥻��inFile����
		ofstream CreateFile("Members.dat", ios::binary); // �H��X���覡�}��Members.dat(�Y�L���ɷ|�۰ʫإ�)
		if (!CreateFile)
		{
			cout << "File could not be opened!";
			exit(1);
		}
		CreateFile.close(); // ����CreateFile
		ifstream inFile("Members.dat", ios::binary); // �HŪ�����覡�}��Members.dat(�S�N�~���|�X��)
	}
	MemberRecord in;

	while (inFile.read((char*)&in, sizeof(MemberRecord))) // Ū��
		memberDetails.push_back(in);
}

// �P�_��J���F��O�_���d�򤺪����
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
	if (!strlen(input)) // �p�GŪ����Ū��N���sŪ��(���[�|�X��)
		cin.getline(input, 80, '\n');
	
	for (unsigned int i = 0; i < strlen(input); i++) // �p�GŪ���쪺�r��t���D�Ʀr���r���N�^��-1
		if (input[i] < '0' || input[i]>'9')
			return -1;
		
	int num = atoi(input); // �Nnum�qchar(a)�নint(i)
	if (num >= begin && num <= end)
		return num;
	
	return -1;
}

// �P�_��J��ID number�Ppassword�O�_�s�b��memberDetails��
void login(const vector< MemberRecord >& memberDetails)
{
	MemberRecord log;
	cout << "Please enter your ID number:";
	cin >> log.IDNumber;
	cout << "Enter your password:";
	cin >> log.password;
	if (!valid(log.IDNumber, log.password, memberDetails)) // �Y��J���~�N���s��J
	{
		cout << "\nInvalid account number or password. Please try again.\n\n";
		return login(memberDetails);
	}
	
	cout << endl;
	return;
}

// �Y��J��ID number�Ppassword�s�b��memberDetails���N�^��True�_�h�^��False
bool valid(char IDNumber[], char password[],
	const vector< MemberRecord >& memberDetails)
{
	if (IDNumber[0] >= 'a' && IDNumber[0] <= 'z') // �Y��J���Ĥ@�Ӧr�����p�g�N�ର�j�g
		IDNumber[0] -= 32;
	for (unsigned int i = 0; i < memberDetails.size(); i++)
		if (!strcmp(password, memberDetails[i].password) && !strcmp(IDNumber, memberDetails[i].IDNumber))
			return true;

	return false;
}

// ���U�@�ӷs�b��
void registration(vector< MemberRecord >& memberDetails)
{
	MemberRecord reg;
	cout << "Input your ID Number:";
	cin >> reg.IDNumber;
	if (!legalID(reg.IDNumber)) // �Y��J��ID number�L��
	{
		cout << "\nThe ID number " << reg.IDNumber << " is illegal.\n\n";
		return;
	}
	else if (existingID(reg.IDNumber, memberDetails)) // �Y��J��ID number�w�g�s�b��memberDetails
	{
		cout << "\nYou are already a member!\n\n";
		return;
	}
	cout << "\nInput your name:";
	cin >> reg.name;
	cout << "\nChoose a password:";
	cin >> reg.password;
	memberDetails.push_back(reg); // �N��Ʀs�JmemberDetails
	cout << "\nRegistration Completed!\n\n";
}

// �Y��J��ID number���ĴN�^��True�_�h�^��False
bool legalID(char IDNumber[])
{
	char keep = IDNumber[0];
	int first = 0, checknum = 0;
	if (IDNumber[0] >= 'a' && IDNumber[0] <= 'z') // �Y�Ĥ@�ӭ^��r�����p�g�h�ন�j�g
		IDNumber[0] -= 32;
	//-----------------------------�N�Ĥ@�ӭ^��r���ন�������Ʀr-------------------------
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
	//-----------------------------�N�Ĥ@�ӭ^��r���ন�������Ʀr-------------------------
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

// �Y��J��ID number�s�b��memberDetails�N�^��True�_�h�^��False
bool existingID(char IDNumber[], const vector< MemberRecord >& memberDetails)
{
	for (unsigned int i = 0; i < memberDetails.size(); i++)
		if (!strcmp(IDNumber, memberDetails[i].IDNumber))
			return true;
		
	return false;
}

// �NmemberDetails������Ʀs�JMembers.dat
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
