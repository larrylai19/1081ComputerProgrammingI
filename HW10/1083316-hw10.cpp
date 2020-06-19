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

// 讀取Reservations.dat並存入reservations，若無此檔便新建
void loadReservations(vector< ReservationRecord >& reservations)
{
	ifstream inFile("Reservations.dat", ios::binary); // 先嘗試開啟Reservations.dat
	if (!inFile) // 如果!inFile為true代表開啟失敗(可能為此檔案不存在導致)
	{
		inFile.close(); // 將原本的inFile關閉
		ofstream CreateFile("Reservations.dat", ios::binary); // 以輸出的方式開啟Reservations.dat(若無此檔會自動建立)
		if (!CreateFile)
		{
			cout << "File could not be open!";
			exit(1);
		}
		CreateFile.close(); // 關閉CreateFile
		ifstream inFile("Reservations.dat", ios::binary); // 以讀取的方式開啟Reservations.dat(沒意外不會出錯)
	}
	ReservationRecord in;
	while (inFile.read((char*)&in, sizeof(ReservationRecord))) // 讀檔
		reservations.push_back(in);
}

// 判斷輸入的東西是否為範圍內的整數
int inputAnInteger(int begin, int end)
{
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
	else
		return -1;
}

// 判斷輸入的ID number與password是否存在於memberDetails內
void login(const vector< MemberRecord >& memberDetails, vector< ReservationRecord >& reservations)
{
	MemberRecord log;
	cout << "Please enter your ID number:";
	cin >> log.IDNumber;
	cout << "Enter your password:";
	cin >> log.password;
	if (!valid(log.IDNumber, log.password, memberDetails)) // 若輸入錯誤就重新輸入
	{
		cout << "\nInvalid account number or password. Please try again.\n\n";
		return login(memberDetails, reservations);
	}

	int choice = 0;
	
	while (true) // 進入下一層選單
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

// 若輸入的ID number與password存在於memberDetails內就回傳True否則回傳False
bool valid(char IDNumber[], char password[], const vector< MemberRecord >& memberDetails)
{
	if (IDNumber[0] >= 'a' && IDNumber[0] <= 'z') // 若輸入的第一個字母為小寫就轉為大寫
		IDNumber[0] -= 32;
	for (unsigned int i = 0; i < memberDetails.size(); i++)
		if (!strcmp(password, memberDetails[i].password) && !strcmp(IDNumber, memberDetails[i].IDNumber))
			return true;

	return false;
}

// 新增訂位至指定的客戶帳戶內
void reservation(char IDNumber[], vector< ReservationRecord >& reservations)
{
	cout << endl;
	for (int i = 1; i <= 16; i++) // 列出所有分店及其對應的編號
		cout << setw(2) << i << ". " << branchNames[i] << endl;
	int choice;
	do cout << "\nEnter your choice (0 to end): "; // 選擇分店; 0 為取消
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
		strcpy_s(in.IDNumber, IDNumber); // 將目前登入的ID Number存入
		in.branchCode = choice; // 將選擇的分店編號存入

		compCurrentDate(currentTime); // 計算當前時間

		// 印出當前時間
		cout << "\nThe current hour is " << currentTime.year << "/" << currentTime.month << "/"
			<< currentTime.day << ":" << currentTime.hour << endl << endl << "Available days:\n\n";

		compAvailableDates(currentTime, availableDates); // 計算可預定的日期 ( 當前日期後七天 )

		for (int i = 1; i <= 7; i++) // 印出可預定的時間
			cout << i << ". " << availableDates[i].year << "/" << availableDates[i].month << "/" << availableDates[i].day << endl;
		do cout << "\nEnter your choice (0~end): "; // 選擇訂位日期; 0 為取消
		while ((choice = inputAnInteger(0, 7)) == -1);
		switch (choice)
		{
		case 0:

			cout << endl;
			return;

			break;

		default:

			// 將選擇的日期資料存入
			in.date.year = availableDates[choice].year;
			in.date.month = availableDates[choice].month;
			in.date.day = availableDates[choice].day;
			in.date.hour = availableDates[choice].hour;

			do cout << "\nEnter hour (" << in.date.hour << "~23):";
			while ((choice = inputAnInteger(in.date.hour, 23)) == -1);

			in.date.hour = choice; // 將選擇的時間存入
			do cout << "\nEnter the number of customers (1~30, 0 to end):"; // 選擇訂位人數; 0 為取消
			while ((choice = inputAnInteger(0, 30)) == -1);

			switch (choice)
			{
			case 0:

				cout << endl;
				return;

				break;

			default:

				in.numCustomers = choice; // 將選擇的人數存入

				// 印出訂位資料
				cout << endl << setw(30) << "Branch" << setw(15) << "Date" << setw(8) << "Hour"
					<< setw(20) << "No of Customers\n" << setw(3) << "";
				output(in);

				reservations.push_back(in); // 存入訂位資料
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

// 計算當前日期、時間
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

// 計算可預定的日期 ( 當前日期後七天 )
void compAvailableDates(Date currentDate, Date availableDates[])
{
	int days[13] = { 0, 31,28,31,30,31,30,31,31,30,31,30,31 }; // 每個月的天數
	if (currentDate.year % 4 == 0 && (currentDate.year % 100 != 0 || currentDate.year % 400 == 0)) // 如果當前是閏年
		days[2] = 29; // 將2月設為29天
	if (currentDate.hour == 23) // 如果當前時間已超過23點，即無法預定當天
	{
		availableDates[1].day = currentDate.day + 1;
		availableDates[1].hour = 0;
		availableDates[1].year = currentDate.year;
		availableDates[1].month = currentDate.month;
	}
	else // 可預定時間為當前時間後一小時
	{
		availableDates[1].day = currentDate.day;
		availableDates[1].hour = currentDate.hour + 1;
		availableDates[1].year = currentDate.year;
		availableDates[1].month = currentDate.month;
	}

	for (int i = 2; i <= 7; i++) // 設定後面六天的資料
	{
		availableDates[i].day = availableDates[i - 1].day + 1;
		availableDates[i].year = availableDates[i - 1].year;
		availableDates[i].month = availableDates[i - 1].month;
		availableDates[i].hour = 0;
	}

	for (int i = 1; i <= 7; i++) // 如果可預定的時間跨越月份
		if (availableDates[i].day > days[availableDates[i].month])
		{
			availableDates[i].day -= days[availableDates[i].month];
			availableDates[i].month++;
			if (availableDates[i].month > 12) // 如果可預定的時間跨越年分
			{
				availableDates[i].month -= 12;
				availableDates[i].year++;
			}
		}
}

// 印出訂位資料
void output(ReservationRecord reservation)
{
	cout << setw(27) << branchNames[reservation.branchCode] << setw(9) << reservation.date.year << "-"
		<< setw(2) << reservation.date.month << "-" << setw(2) << reservation.date.day
		<< setw(8) << reservation.date.hour << setw(19) << reservation.numCustomers << endl;
}

// 印出當前帳戶的所有訂位，並提供刪除或儲存的選擇
void queryDelete(char IDNumber[], vector< ReservationRecord >& reservations)
{
	cout << endl << setw(30) << "Branch" << setw(15) << "Date" << setw(8) << "Hour" << setw(20) << "No of Customers\n";
	vector<int> del; // 儲存當前帳戶訂位資料編號對應所有訂位資料的編號以便刪除
	int num = 0, choice;
	for (unsigned int i = 0; i < reservations.size(); i++) // 印出當前帳戶內的所有訂位資料
		if (!strcmp(reservations[i].IDNumber, IDNumber))
		{
			num++;
			cout << setw(2) << num << ".";
			output(reservations[i]);
			del.push_back(i);
		}

	do cout << "\nChoose a reservation to cancel (0: keep all reservations): "; // 選擇欲刪除的訂位資料; 0 為取消
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
	cout << "Input your name:";
	cin >> reg.name;
	cout << "Choose a password:";
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
	outFile.close();
	return;
}

// 將reservations內的資料存入Reservations.dat
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