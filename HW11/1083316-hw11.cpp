#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
using namespace::std;

char foods[ 14 ][ 48 ] = { "",
                           "Pork XiaoLongBao (12)",
                           "Steamed Vegetable and Ground Pork Dumplings (8)",
                           "Steamed Shrimp and Pork Dumplings (8)",
                           "Steamed Fish Dumplings (8)",
                           "Steamed Vegetarian Mushroom Dumplings (8)",
                           "Steamed Shrimp and Pork Shao Mai (12)",
                           "Pork Buns (5)",
                           "Vegetable and Ground Pork Buns (5)",
                           "Red Bean Buns (5)",
                           "Sesame Buns (5)",
                           "Taro Buns (5)",
                           "Vegetarian Mushroom Buns (5)",
                           "Golden Lava Buns (5)" };

int price[ 14 ] = { 0, 220, 176, 216, 200, 200, 432, 225,
                       225, 200, 200, 225, 250, 225 };

struct Date
{
   int year;
   int month;
   int day;
};

struct Account
{
   char email[ 40 ]; // used as the account number
   char password[ 20 ];
   char name[ 12 ];
   char address[ 80 ];
   char phone[ 12 ];
   int cart[14] = {}; // Cart[i] is the quantity of food #i in the shopping cart
};

struct Order
{
   char orderNumber[ 12 ];
   char email[ 40 ];
   Date deliveryDate;
   Date arrivalDate;
   int quantity[14] = {}; // quantity[i] is the quantity of food #i in the order
};

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// add a new account to the file Accounts.dat
void registration( vector< Account > &accountDetails );

// return true if email belongs to accountDetails
bool exists( char email[], const vector< Account > &accountDetails );

// save all elements in accountDetails to the file Accounts.dat
void saveAllAccounts( const vector< Account > &accountDetails );

// login and call shopping
void login( vector< Account > &accountDetails );

// load all accounts details from the file Accounts.dat
void loadAccountDetails( vector< Account > &accountDetails );

// return true if there exists an account with specified email and password; and
// put the account with specified email and password into account
bool valid( char email[], char password[], Account &account,
            const vector< Account > &accountDetails );

// add chosen Foods to the shopping cart
void shopping( Account &account );

// return true if the shopping cart is empty
bool emptyCart( const Account &account );

// display the shopping cart in account
bool displayCart( const Account &account );

// append account in the file Accounts.dat
void saveAccount( const Account &account );

// update the shopping cart in account
void updateCart( Account &account );

// generate a Bill and reset account.cart
void check( Account &account );

// compute the current date
void compCurrentDate( Date &currentDate );

// open the file Orders.txt and call displayOrderDetails twice
void createOrder( const Account &account, const Order &order );

// write an order to Orders.txt or display it on the output window depending on os
void displayOrderDetails( ostream &os, const Account &account, const Order &order );

int main()
{
   vector< Account > accountDetails; // account details for all accounts

   cout << "Welcome to DintaiFung Shopping Mall!\n";
   srand( static_cast< int >( time( 0 ) ) );

   int choice;

   while( true )
   {
      cout << "\n1 - Registration\n";
      cout << "2 - Login\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch( choice )
      {
      case 1:
         registration( accountDetails );
         break;

      case 2:
         login( accountDetails );
         break;

      case 3:
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;
      }
   }

   system( "pause" );
}

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end)
{
	char input[80];
	cin.getline(input, 80, '\n');

	if (!strlen(input))
		cin.getline(input, 80, '\n');

	for (unsigned int i = 0; i < strlen(input); i++)
		if (input[i] < '0' || input[i] > '9')
			return -1;

	int num = atoi(input);
	if (num >= begin && num <= end)
		return num;

	return -1;
}

// add a new account to the file Accounts.dat
void registration(vector< Account >& accountDetails)
{
	Account reg;

	cout << "Email address (Account number):";
	cin >> reg.email;
	if (exists(reg.email, accountDetails))
	{
		cout << "You are already a member!\n";
		return;
	}
	cout << "Password: ";
	cin >> reg.password;
	cout << "Name: ";
	cin >> reg.name;
	cout << "Shopping address: ";
	cin >> reg.address;
	cout << "Contact phone number: ";
	cin >> reg.phone;
	accountDetails.push_back(reg);
	saveAllAccounts(accountDetails);
	cout << "\nRegistration Completed!\n";
	return;
}

// return true if email belongs to accountDetails
bool exists(char email[], const vector< Account >& accountDetails)
{
	for (unsigned int i = 0; i < accountDetails.size(); i++)
		if (!strcmp(email, accountDetails[i].email))
			return true;

	return false;
}

// save all elements in accountDetails to the file Accounts.dat
void saveAllAccounts(const vector< Account >& accountDetails)
{
	ofstream outFile("Accounts.dat", ios::binary);
	if (!outFile)
	{
		cout << "File could not be open!";
		exit(1);
	}
	for (unsigned int i = 0; i < accountDetails.size(); i++)
		outFile.write((char*)&accountDetails[i], sizeof(Account));
	outFile.close();
	return;
}

// login and call shopping
void login(vector< Account >& accountDetails)
{
	loadAccountDetails(accountDetails);
	Account log;
	while (true)
	{
		cout << "Email address (0 to end): ";
		cin >> log.email;
		if (!strcmp(log.email, "0"))
			break;
		cout << "Password: ";
		cin >> log.password;
		if (valid(log.email, log.password, log, accountDetails))
		{
			shopping(log);
			break;
		}
		else
			cout << "\nInvalid account number or password. Please try again.\n\n";
	}
	return;
}

// load all accounts details from the file Accounts.dat
void loadAccountDetails(vector< Account >& accountDetails)
{
	accountDetails.clear();
	ifstream inFile("Accounts.dat", ios::binary);
	if (!inFile)
	{
		inFile.close();
		ofstream CreateFile("Accounts.dat", ios::binary);
		if (!CreateFile)
		{
			cout << "File could not be open!";
			exit(1);
		}
		CreateFile.close();
		ifstream inFile("Accounts.dat", ios::binary);
	}
	Account in;
	while (inFile.read((char*)&in, sizeof(Account)))
		accountDetails.push_back(in);
	inFile.close();
	return;
}

// return true if there exists an account with specified email and password; and
// put the account with specified email and password into account
bool valid(char email[], char password[], Account& account,
	const vector< Account >& accountDetails)
{
	for(unsigned int i = 0; i < accountDetails.size(); i++)
		if (!strcmp(email, accountDetails[i].email) && !strcmp(password, accountDetails[i].password))
		{
			account = accountDetails[i];
			return true;
		}
	return false;
}

// add chosen Foods to the shopping cart
void shopping(Account& account)
{
	int foodchoice, quantity, choice;
	cout << endl;
	if (emptyCart(account))
	{
		for (int i = 1; i < 14; i++)
			cout << right << setw(2) << i << "." << setw(50) << left << foods[i] << price[i] << endl;

		do cout << "\nEnter your choice (0 to logout): ";
		while ((foodchoice = inputAnInteger(0, 16)) == -1);

		if (foodchoice == 0)
			return;

		cout << "\nEnter the quantity: ";
		cin >> quantity;
		account.cart[foodchoice] += quantity;
		cout << "\nYour Shopping Cart Contents:" << endl;
		displayCart(account);
		saveAccount(account);
	}
	else
	{
		for (int i = 1; i < 14; i++)
			cout << right << setw(2) << i << "." << setw(50) << left << foods[i] << price[i] << endl;
		cout << "\n14. View your shopping cart";
		
		do cout << "\n\nEnter your choice (0 to logout): ";
		while ((foodchoice = inputAnInteger(0, 16)) == -1);

		if (foodchoice == 0)
			return;
		if (foodchoice == 14)
		{
			cout << "\nYour Shopping Cart Contents:\n\n";
			displayCart(account);
		}
		else
		{
			cout << "\nEnter the quantity: ";
			cin >> quantity;
			account.cart[foodchoice] += quantity;
			cout << "\nYour Shopping Cart Contents:\n\n";
			displayCart(account);
			saveAccount(account);
		}
	}
	while (true)
	{
		cout << "1. Continue Shopping\n"; 
		cout << "2. Update Cart\n";
		cout << "3. Check\n";

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			for (int i = 1; i < 14; i++)
				cout << right << setw(2) << i << "." << setw(50) << left << foods[i] << price[i] << endl;
			cout << "\n14. View yout shopping cart";
			do cout << "\n\nEnter your choice (0 to logout): ";
			while ((foodchoice = inputAnInteger(0, 16)) == -1); 
			if (foodchoice == 0)
				return;
			if (foodchoice == 14)
			{
				cout << "\nYour Shopping Cart Contents:\n\n";
				displayCart(account);
				saveAccount(account);
			}
			else
			{
				cout << "\nEnter the quantity: ";
				cin >> quantity;
				account.cart[foodchoice] += quantity;
				cout << "\nYour Shopping Cart Contents:\n\n";
				displayCart(account);
				saveAccount(account);
			}
			continue;
			break;
		case 2:
			updateCart(account);
			continue;
			break;
		case 3:
			check(account);
			return;
			break;
		}
	}
}

// return true if the shopping cart is empty
bool emptyCart(const Account& account)
{
	for (int i = 0; i < 14; i++)
		if (account.cart[i] > 0)
			return false;

	return true;
}

// display the shopping cart in account
bool displayCart(const Account& account)
{
	int total = 0;
	if (!emptyCart(account))
	{
		cout << "\nCode                                            Item  Price  Quantity  Subtotal\n";
		for (int i = 1; i < 14; i++)
			if (account.cart[i] > 0)
			{
				cout << left << setw(4) << i << right << setw(48) << foods[i] << setw(7) << price[i] << setw(10) << account.cart[i]
					<< setw(10) << account.cart[i] * price[i] << endl;
				total += account.cart[i] * price[i];
			}
		cout << "\nTotal Cost:" << total << endl << endl;
	}
	return true;
}

// append account in the file Accounts.dat
void saveAccount(const Account& account)
{
	ifstream inFile("Accounts.dat", ios::binary);
	int j = 0;
	inFile.seekg(0, inFile.end);
	int64_t n = inFile.tellg();
	inFile.seekg(0, inFile.beg); 
	for (int i = 0; i < n; i += sizeof(Account)) 
	{
		char email[40] = {};
		inFile.seekg(i, inFile.beg);
		inFile.read((char*)&email, sizeof(account.email)); 
		if (!strcmp(email, account.email)) 
		{  
			j = i / sizeof(Account);
			break;
		}
	}
	inFile.close();
	unsigned int size = j * sizeof(Account);
	fstream outFile("Accounts.dat", ios::binary | ios::out | ios::in);
	outFile.seekp((size), outFile.beg);
	outFile.write((char*)&account, sizeof(Account));
	outFile.close();
}

// update the shopping cart in account
void updateCart(Account& account)
{
	int food, quantity;
choose:
	cout << "Enter the product code: ";
	cin >> food;
	if (account.cart[food] == 0)
		goto choose;
	cout << "\nEnter the quantity: ";
	cin >> quantity;
	account.cart[food] = quantity;
	displayCart(account);
	saveAccount(account);
	return;
}

// generate a Bill and reset account.cart
void check(Account& account)
{
	Order order;
	srand((unsigned)time(NULL));
	int n = rand() % 26;
	order.orderNumber[0] = 'Z' - n;
	for (int i = 1; i < 10; i++)
	{
		n = rand() % 10;
		order.orderNumber[i] = '9' - n;
	}
	order.orderNumber[10] = '\0';
	compCurrentDate(order.deliveryDate);
	cout << "Enter arrival Date" << endl;
	cout << "year: ";
	cin >> order.arrivalDate.year;
	cout << "month: ";
	cin >> order.arrivalDate.month;
	cout << "day: ";
	cin >> order.arrivalDate.day;
	for (int i = 1; i < 14; i++)
		order.quantity[i] = account.cart[i];

	createOrder(account, order);
	for (int i = 1; i < 14; i++)
		account.cart[i] = 0;
	saveAccount(account);
	return;
}

// compute the current date
void compCurrentDate(Date& currentDate)
{
	tm structuredTime;
	time_t rawTime = time(0);
	localtime_s(&structuredTime, &rawTime);
	currentDate.year = structuredTime.tm_year + 1900;
	currentDate.month = structuredTime.tm_mon + 1;
	currentDate.day = structuredTime.tm_mday;
}

// open the file Orders.txt and call displayOrderDetails twice
void createOrder(const Account& account, const Order& order)
{
	ofstream outFile("Orders.txt", ios::app);
	displayOrderDetails(outFile, account, order);
	displayOrderDetails(cout, account, order);
	outFile.close();
	cout << "An order has been created.\n";
}

// write an order to Orders.txt or display it on the output window depending on os
void displayOrderDetails(ostream& os, const Account& account, const Order& order)
{
	os << "\nOrder number: " << order.orderNumber << endl;
	os << "Delivery Date: " << order.deliveryDate.year << "/" << order.deliveryDate.month << "/" << order.deliveryDate.day << endl;
	os << "Arrival Date: " << order.arrivalDate.year << "/" << order.arrivalDate.month << "/" << order.arrivalDate.day << endl;
	os << "Recipient: " << account.email << endl;
	os << "Contact Phone Number: " << account.phone << endl;
	os << "Shipping address: " << account.address << endl << endl;
	os << "Shopping details:\n\n";
	int total = 0;
	os << "Code" << setw(50) << right << "Item" << setw(8) << "Price" << setw(12) << "Quantity" << setw(10) << "Subtotal" << endl;
	for (int i = 1; i <= 13; i++) 
		if (order.quantity[i] != 0) 
		{
			total += price[i] * account.cart[i];
			os << setw(4) << i << right << setw(50) << foods[i] << setw(8) << price[i] << setw(12) << order.quantity[i] << setw(10) << price[i] * order.quantity[i] << endl;
		}
	os << "\nTotal Cost: " << total << endl << endl;
}
