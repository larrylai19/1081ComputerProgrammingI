#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstring> 

using namespace::std;

struct Date
{
   int year;
   int month;
   int day;
   int hour;
};

struct MemberRecord
{
   char IDNumber[ 12 ];   // account number
   char password[ 24 ];   // password
   char name[ 8 ];        // name
};

struct ReservationRecord
{
   char IDNumber[ 12 ]; // account number
   int branchCode;      // branch code
   Date date;           // reservation date
   int numCustomers;    // number of customers
};

char branchNames[ 17 ][ 24 ] = { "", "Taipei Dunhua South", "Taipei SOGO",
                                     "Taipei Songjiang",    "Taipei Nanjing",
                                     "Taipei Linsen",       "Taipei Zhonghua New",
                                     "Banqiao Guanqian",    "Yonghe Lehua",
                                     "Taoyuan Zhonghua",    "Taoyuan Nankan",
                                     "Zhongli Zhongyang",   "Hsinchu Beida",
                                     "Taichung Ziyou",      "Chiayi Ren'ai",
                                     "Tainan Ximen",        "Kaohsiung Zhonghua New" };

// input memberDetails from the file Members.dat
void loadMemberDetails( vector< MemberRecord > &memberDetails );

// input reservations from the file Reservations.dat
void loadReservations( vector< ReservationRecord > &reservations );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// login and display the submenu
void login( const vector< MemberRecord > &memberDetails,
            vector< ReservationRecord > &reservations );

// there exists a member with specified IDNumber and password
bool valid( char IDNumber[], char password[],
            const vector< MemberRecord > &memberDetails );

// add a new reservation for the member with specified IDnumber
void reservation( char IDNumber[], vector< ReservationRecord > &reservations );

// compute the current date
void compCurrentDate( Date &currentDate );

// compute 7 dates which is starting from the current date
void compAvailableDates( Date currentDate, Date availableDates[] );

// display all fields of reservation
void output( ReservationRecord reservation );

// display all reservations for the member with specified IDnumber,
// then let the member to choose one of them to delete
void queryDelete( char IDNumber[], vector< ReservationRecord > &reservations );

// add a new member
void registration( vector< MemberRecord > &memberDetails );

// return true if IDNumber is a legal ID number
bool legalID( char IDNumber[] );

// return true if IDNumber belongs to memberDetails
bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails );

// output all memberDetails into the file Members.dat
void saveMemberDetails( const vector< MemberRecord > &memberDetails );

// output all reservations into the file Reservations.dat
void saveReservations( const vector< ReservationRecord > &reservations );

int main()
{
   vector< MemberRecord > memberDetails; // member details for all members
   vector< ReservationRecord > reservations; // all reservations

   loadMemberDetails( memberDetails );
   loadReservations( reservations );

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
         login( memberDetails, reservations );
         break;

      case 2:
         registration( memberDetails );
         break;

      case 3:
         saveMemberDetails( memberDetails );
         saveReservations( reservations );
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

// Ū��Reservations.dat�æs�Jreservations�A�Y�L���ɫK�s��
void loadReservations(vector< ReservationRecord >& reservations)
{
	ifstream inFile("Reservations.dat", ios::binary); // �����ն}��Reservations.dat
	if (!inFile) // �p�G!inFile��true�N��}�ҥ���(�i�ର���ɮפ��s�b�ɭP)
	{
		inFile.close(); // �N�쥻��inFile����
		ofstream CreateFile("Reservations.dat", ios::binary); // �H��X���覡�}��Reservations.dat(�Y�L���ɷ|�۰ʫإ�)
		if (!CreateFile)
		{
			cout << "File could not be open!";
			exit(1);
		}
		CreateFile.close(); // ����CreateFile
		ifstream inFile("Reservations.dat", ios::binary); // �HŪ�����覡�}��Reservations.dat(�S�N�~���|�X��)
	}
	ReservationRecord in;
	while (inFile.read((char*)&in, sizeof(ReservationRecord))) // Ū��
		reservations.push_back(in);
}

// �P�_��J���F��O�_���d�򤺪����
int inputAnInteger(int begin, int end)
{
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
	else
		return -1;
}

// �P�_��J��ID number�Ppassword�O�_�s�b��memberDetails��
void login(const vector< MemberRecord >& memberDetails, vector< ReservationRecord >& reservations)
{
	MemberRecord log;
	cout << "Please enter your ID number:";
	cin >> log.IDNumber;
	cout << "Enter your password:";
	cin >> log.password;
	if (!valid(log.IDNumber, log.password, memberDetails)) // �Y��J���~�N���s��J
	{
		cout << "\nInvalid account number or password. Please try again.\n\n";
		return login(memberDetails, reservations);
	}

	int choice = 0;
	
	while (true) // �i�J�U�@�h���
	{
		cout << "\n1 - Make Reservation\n";
		cout << "2 - Reservation Enquiry/Canceling\n";
		cout << "3 - End\n";
		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		switch (choice)
		{
		case 1:

			reservation(log.IDNumber, reservations);

			break;

		case 2:
		
			queryDelete(log.IDNumber, reservations);

			break;

		case 3:

			cout << endl;
			return;

			break;

		default:

			cout << "\nIncorrect choice!\n";

			break;
		}
	}
}

// �Y��J��ID number�Ppassword�s�b��memberDetails���N�^��True�_�h�^��False
bool valid(char IDNumber[], char password[], const vector< MemberRecord >& memberDetails)
{
	if (IDNumber[0] >= 'a' && IDNumber[0] <= 'z') // �Y��J���Ĥ@�Ӧr�����p�g�N�ର�j�g
		IDNumber[0] -= 32;
	for (unsigned int i = 0; i < memberDetails.size(); i++)
		if (!strcmp(password, memberDetails[i].password) && !strcmp(IDNumber, memberDetails[i].IDNumber))
			return true;

	return false;
}

// �s�W�q��ܫ��w���Ȥ�b�᤺
void reservation(char IDNumber[], vector< ReservationRecord >& reservations)
{
	cout << endl;
	for (int i = 1; i <= 16; i++) // �C�X�Ҧ������Ψ�������s��
		cout << setw(2) << i << ". " << branchNames[i] << endl;
	int choice;
	do cout << "\nEnter your choice (0 to end): "; // ��ܤ���; 0 ������
	while ((choice = inputAnInteger(0, 16)) == -1);

	switch (choice)
	{
	case 0:

		cout << endl;

		return;
		break;

	default:

		ReservationRecord in;
		Date currentTime, availableDates[8];
		strcpy_s(in.IDNumber, IDNumber); // �N�ثe�n�J��ID Number�s�J
		in.branchCode = choice; // �N��ܪ������s���s�J

		compCurrentDate(currentTime); // �p���e�ɶ�

		// �L�X��e�ɶ�
		cout << "\nThe current hour is " << currentTime.year << "/" << currentTime.month << "/"
			<< currentTime.day << ":" << currentTime.hour << endl << endl << "Available days:\n\n";

		compAvailableDates(currentTime, availableDates); // �p��i�w�w����� ( ��e�����C�� )

		for (int i = 1; i <= 7; i++) // �L�X�i�w�w���ɶ�
			cout << i << ". " << availableDates[i].year << "/" << availableDates[i].month << "/" << availableDates[i].day << endl;
		do cout << "\nEnter your choice (0~end): "; // ��ܭq����; 0 ������
		while ((choice = inputAnInteger(0, 7)) == -1);
		switch (choice)
		{
		case 0:

			cout << endl;
			return;

			break;

		default:

			// �N��ܪ������Ʀs�J
			in.date.year = availableDates[choice].year;
			in.date.month = availableDates[choice].month;
			in.date.day = availableDates[choice].day;
			in.date.hour = availableDates[choice].hour;

			do cout << "\nEnter hour (" << in.date.hour << "~23):";
			while ((choice = inputAnInteger(in.date.hour, 23)) == -1);

			in.date.hour = choice; // �N��ܪ��ɶ��s�J
			do cout << "\nEnter the number of customers (1~30, 0 to end):"; // ��ܭq��H��; 0 ������
			while ((choice = inputAnInteger(0, 30)) == -1);

			switch (choice)
			{
			case 0:

				cout << endl;
				return;

				break;

			default:

				in.numCustomers = choice; // �N��ܪ��H�Ʀs�J

				// �L�X�q����
				cout << endl << setw(30) << "Branch" << setw(15) << "Date" << setw(8) << "Hour"
					<< setw(20) << "No of Customers\n" << setw(3) << "";
				output(in);

				reservations.push_back(in); // �s�J�q����
				cout << "\nReservation Completed!\n";
				return;

				break;
			}
			return;

			break;
		}
		return;

		break;
	}
}

// �p���e����B�ɶ�
void compCurrentDate(Date& currentDate)
{
	tm structuredTime;
	time_t rawTime = time(0);
	localtime_s(&structuredTime, &rawTime);
	currentDate.year = structuredTime.tm_year + 1900;
	currentDate.month = structuredTime.tm_mon + 1;
	currentDate.day = structuredTime.tm_mday;
	currentDate.hour = structuredTime.tm_hour;
}

// �p��i�w�w����� ( ��e�����C�� )
void compAvailableDates(Date currentDate, Date availableDates[])
{
	int days[13] = { 0, 31,28,31,30,31,30,31,31,30,31,30,31 }; // �C�Ӥ몺�Ѽ�
	if (currentDate.year % 4 == 0 && (currentDate.year % 100 != 0 || currentDate.year % 400 == 0)) // �p�G��e�O�|�~
		days[2] = 29; // �N2��]��29��
	if (currentDate.hour == 23) // �p�G��e�ɶ��w�W�L23�I�A�Y�L�k�w�w���
	{
		availableDates[1].day = currentDate.day + 1;
		availableDates[1].hour = 0;
		availableDates[1].year = currentDate.year;
		availableDates[1].month = currentDate.month;
	}
	else // �i�w�w�ɶ�����e�ɶ���@�p��
	{
		availableDates[1].day = currentDate.day;
		availableDates[1].hour = currentDate.hour + 1;
		availableDates[1].year = currentDate.year;
		availableDates[1].month = currentDate.month;
	}

	for (int i = 2; i <= 7; i++) // �]�w�᭱���Ѫ����
	{
		availableDates[i].day = availableDates[i - 1].day + 1;
		availableDates[i].year = availableDates[i - 1].year;
		availableDates[i].month = availableDates[i - 1].month;
		availableDates[i].hour = 0;
	}

	for (int i = 1; i <= 7; i++) // �p�G�i�w�w���ɶ���V���
		if (availableDates[i].day > days[availableDates[i].month])
		{
			availableDates[i].day -= days[availableDates[i].month];
			availableDates[i].month++;
			if (availableDates[i].month > 12) // �p�G�i�w�w���ɶ���V�~��
			{
				availableDates[i].month -= 12;
				availableDates[i].year++;
			}
		}
}

// �L�X�q����
void output(ReservationRecord reservation)
{
	cout << setw(27) << branchNames[reservation.branchCode] << setw(9) << reservation.date.year << "-"
		<< setw(2) << reservation.date.month << "-" << setw(2) << reservation.date.day
		<< setw(8) << reservation.date.hour << setw(19) << reservation.numCustomers << endl;
}

// �L�X��e�b�᪺�Ҧ��q��A�ô��ѧR�����x�s�����
void queryDelete(char IDNumber[], vector< ReservationRecord >& reservations)
{
	cout << endl << setw(30) << "Branch" << setw(15) << "Date" << setw(8) << "Hour" << setw(20) << "No of Customers\n";
	vector<int> del; // �x�s��e�b��q���ƽs�������Ҧ��q���ƪ��s���H�K�R��
	int num = 0, choice;
	for (unsigned int i = 0; i < reservations.size(); i++) // �L�X��e�b�᤺���Ҧ��q����
		if (!strcmp(reservations[i].IDNumber, IDNumber))
		{
			num++;
			cout << setw(2) << num << ".";
			output(reservations[i]);
			del.push_back(i);
		}

	do cout << "\nChoose a reservation to cancel (0: keep all reservations): "; // ��ܱ��R�����q����; 0 ������
	while ((choice = inputAnInteger(0, num)) == -1);

	switch (choice)
	{
	case 0:

		return;

		break;

	default:

		reservations.erase(reservations.begin() + del[choice - 1]);

		break;

	}
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
	cout << "Input your name:";
	cin >> reg.name;
	cout << "Choose a password:";
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
	outFile.close();
	return;
}

// �Nreservations������Ʀs�JReservations.dat
void saveReservations(const vector< ReservationRecord >& reservations)
{
	ofstream outFile("Reservations.dat", ios::binary);
	if (!outFile)
	{
		cout << "File could not be opened!\n";
		exit(1);
	}
	for (unsigned int i = 0; i < reservations.size(); i++)
		outFile.write((char*)&reservations[i], sizeof(ReservationRecord));
	outFile.close();
	return;
}