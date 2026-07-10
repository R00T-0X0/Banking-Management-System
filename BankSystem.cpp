#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>


using namespace std;


const string UsersFileName = "Users.txt";
enum enMainMenuOptions { ShowList = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transactions = 6, ManageUsers = 7 , Logout = 8};
enum enTransactoinsOptions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenue = 4 };
enum enManageUserMenuOptions {ListUsers = 1 , AddUser = 2 , Delete_User = 3 , Update_User = 4 , Find_User = 5 , MainMenu = 6};

struct stClient {
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkToDelete = false;
};
struct stUser {
	string Username;
	string Passsword;
	short Permissions = 0;
};

stUser CurrentUser;

const string ClientsFileName = "Clients.txt";

bool CheckPermisson(short Option);

void PrintAccessDenidScreen();

void CheckChoiceWhatToDo(enMainMenuOptions Choice, vector<stClient>& vClients);

void ShowManageUsersMenuScreen();

void Login();

void StartApp();

void PerformTransactions(enTransactoinsOptions Option);

int ReadNumber() {

	int Number;

	cin >> Number;

	return Number;
}

void PrintHaederScreenWithTitle(string Title) {
	cout << "---------------------------------------------------";
	cout << "\n\t\t " << Title;
	cout << "\n---------------------------------------------------\n";
}


enTransactoinsOptions ReadTransactionOption() {
	cout << "Choos what do you want to do ? [1 To 4] ?";
	return (enTransactoinsOptions)ReadNumber();
}



void GoBackToMainMinu() {
	cout << "\n\nPress any key to go back to Mian Menu...";
	system("pause>0");
	StartApp();
}


stClient ChangeClientData(stClient Client) {
	cout << "Enter Pin Code? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance? ";
	cin >> Client.AccountBalance;

	return Client;
}



void PrintClientCard(stClient Client) {
	cout << "\n\nThe following are the client details : \n";
	cout << "__________________________________\n\n";
	cout << "Account Number :" << Client.AccountNumber;
	cout << "\nPin Code :" << Client.PinCode;
	cout << "\nClient Name : " << Client.Name;
	cout << "\nPhone :" << Client.Phone;
	cout << "\nAccount Balance : " << Client.AccountBalance;
	cout << "\n\n__________________________________\n\n";
}



bool FindClientWithAccountNumber(string AccountNumber, vector <stClient>& vClients, stClient& Client) {

	for (stClient& C : vClients) {
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}


void ShowEndScreen() {
	system("cls");
	PrintHaederScreenWithTitle("Program Ends :-)");
}


string ReadAccountNumber() {
	string AccountNumber = "";

	cout << "Enter Account Number ? ";
	cin >> AccountNumber;

	return AccountNumber;
}


bool MarkClientToDelet(string AccountNumber, vector<stClient>& vClients) {
	for (stClient& C : vClients) {
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkToDelete = true;
			return true;
		}
	}
	return false;
}


vector<string> MySplit(string S, string Delim = "#//#") {
	short pos;
	vector <string> vString;
	string Word;

	while ((pos = S.find(Delim)) != string::npos) {
		Word = S.substr(0, pos);
		if (Word != "") {
			vString.push_back(Word);
		}
		S.erase(0, pos + Delim.length());
	}
	if (S != "")
		vString.push_back(S);

	return vString;
}


stClient ConvertOneLineToRecord(string S, string Delim = "#//#") {

	vector <string> vString = MySplit(S);
	stClient Client;

	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalance = stod(vString[4]);

	return Client;
}


bool ClientExistInFile(string AccountNumber, string FileName) {
	fstream File;
	File.open(FileName, ios::in);
	if (File.is_open()) {
		string Line;
		stClient Client;
		while (getline(File, Line)) {
			Client = ConvertOneLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber) {
				File.close();
				return true;
			}
		}
	}
	return false;
}


stClient ReadClientData() {
	stClient Client;

	cout << "Enter Account Number ?";
	cin >> Client.AccountNumber;

	while (ClientExistInFile(Client.AccountNumber, ClientsFileName)) {
		cout << "client with Account Number [" << Client.AccountNumber << "] already exist, enter anothe account number? ";
		cin >> Client.AccountNumber;
	}



	cout << "Enter Pin Code ? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;
}


string ConvertOneRecordToLine(stClient Client, string Delim = "#//#") {

	string Line = "";

	Line = Client.AccountNumber + Delim;
	Line += Client.PinCode + Delim;
	Line += Client.Name + Delim;
	Line += Client.Phone + Delim;
	Line += to_string(Client.AccountBalance);

	return Line;

}





void SaveOneClientDataInAFile(stClient Client) {
	fstream File;
	File.open(ClientsFileName, ios::out | ios::app);
	if (File.is_open()) {
		string Line = ConvertOneRecordToLine(Client);
		File << Line << endl;
		File.close();
	}
}



vector<stClient> LoadAllClientsFromFile(string ClientsFileName) {
	vector<stClient> vClients;
	fstream File;
	File.open(ClientsFileName, ios::in);
	if (File.is_open()) {
		string Line;
		stClient Client;

		while (getline(File, Line)) {
			Client = ConvertOneLineToRecord(Line);
			vClients.push_back(Client);
		}
		File.close();
	}
	return vClients;
}



void AddNewClients(vector<stClient>& vClients) {

	system("cls");

	cout << "---------------------------------------------------";
	cout << "\n\t\t Add New Client Screen";
	cout << "\n---------------------------------------------------\n";
	cout << "\nAdding New Client : \n\n";
	stClient Client;
	char AddMore = 'y';

	do {
		system("cls");

		PrintHaederScreenWithTitle("Add New Client Screen");

		cout << "\nAdding New Client : \n\n";

		Client = ReadClientData();
		SaveOneClientDataInAFile(Client);

		cout << "Client Added Successfully , do you want to add more ? Y / N ?";
		cin >> AddMore;
	} while (tolower(AddMore) == 'y');

	vClients = LoadAllClientsFromFile(ClientsFileName);

	GoBackToMainMinu();
}


void ShowOneClient(stClient Client) {

	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(15) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(15) << Client.Phone;
	cout << "| " << left << setw(15) << Client.AccountBalance;
}



void ShowAllClients(vector<stClient>& vClients) {
	system("cls");
	cout << "\n\t\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n___________________________________________________________";
	cout << "_____________________________________________\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(15) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(15) << "Phone";
	cout << "| " << left << setw(15) << "Balance";
	cout << "\n___________________________________________________________";
	cout << "_____________________________________________\n\n";

	for (stClient& Client : vClients) {
		ShowOneClient(Client);
		cout << endl;
	}
	cout << "\n___________________________________________________________";
	cout << "_____________________________________________\n\n";

	GoBackToMainMinu();
}


enMainMenuOptions ReadChoice() {
	cout << "Choose what do you want to do ? [1 to 8] ? ";
	return(enMainMenuOptions)ReadNumber();
}



void ShowMainMenu() {
	system("cls");
	cout << "=================================================== ";
	cout << "\n\t\t Main Menu Screen";
	cout << "\n===================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "\n===================================================\n";
}



void UpdateClientsFileContent(string FileName, vector<stClient>& vClients) {
	fstream File;
	File.open(FileName, ios::out);
	if (File.is_open()) {
		string Line;
		for (stClient& C : vClients) {
			if (!C.MarkToDelete) {
				Line = ConvertOneRecordToLine(C);
				File << Line << endl;
			}
		}
	}
}


void UpdateCleintData(vector<stClient>& vClients) {
	system("cls");
	PrintHaederScreenWithTitle("Update Client Screen");
	stClient Client;
	char Answer = 'n';
	string AccountNumber = ReadAccountNumber();
	if (FindClientWithAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);

		cout << "Are you sure do you want update this client ? Y/N ? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {
			for (stClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C = ChangeClientData(C);
					break;
				}
			}
			UpdateClientsFileContent(ClientsFileName, vClients);
		}
		cout << "\nClient updated successfully.";
	}
	else {
		cout << "The client with account number (" << AccountNumber << ") is not found.";
	}
	cout << "\n\nPress any key to go back to Mian Menu...";
	system("pause>0");
	StartApp();
}


void DeleteClient(vector<stClient>& vClients) {
	system("cls");
	PrintHaederScreenWithTitle("Delete Client Screen");
	stClient Client;
	char Answer = 'n';
	string AccountNumber = ReadAccountNumber();
	if (FindClientWithAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);

		cout << "Are you sure do you want to delete this client ? Y/N ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			MarkClientToDelet(AccountNumber, vClients);
			UpdateClientsFileContent(ClientsFileName, vClients);
			vClients = LoadAllClientsFromFile(ClientsFileName);
			cout << "\nClient Deleted Successfully.";
		}
	}
	else {
		cout << "the Client with account number (" << AccountNumber << ") is not found";
	}

	GoBackToMainMinu();

}


void FindClient(vector<stClient>& vClients) {
	system("cls");
	PrintHaederScreenWithTitle("Find Client Screen");
	string AccountNumber = ReadAccountNumber();
	stClient Client;
	if (FindClientWithAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with account number (" << AccountNumber << ") is not found";
	}
	GoBackToMainMinu();
}


bool DipositClientBalanceWithAccountNumber(string AccountNumber, double Amount, vector<stClient>& vClients) {
	char Answer = 'n';
	cout << "\n\nAre you sure do you want to do this transaction ? Y/N ? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y') {
		for (stClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += Amount;
				cout << "\n\nDone Successfully,new Balance is : " << C.AccountBalance << endl;
				return true;

			}
		}
	}
	return false;
}

void Deposit() {
	system("cls");
	PrintHaederScreenWithTitle("Deposit Screen");

	string AccountNumber = ReadAccountNumber();
	vector<stClient>vClients = LoadAllClientsFromFile(ClientsFileName);
	stClient Client;
	while (!FindClientWithAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nThe client with account number [" << AccountNumber << "] is not found!\n\n";
		AccountNumber = ReadAccountNumber();
	}

	PrintClientCard(Client);


	double Amount = 0;

	cout << "\nPlease enter deposit amount ? ";
	cin >> Amount;

	DipositClientBalanceWithAccountNumber(AccountNumber, Amount, vClients);
	UpdateClientsFileContent(ClientsFileName, vClients);
}


void PrintClientBalance(stClient Client) {
	cout << "| " << left << setw(25) << Client.AccountNumber;
	cout << "| " << left << setw(50) << Client.Name;
	cout << "| " << left << setw(25) << Client.AccountBalance;
}



void ShowBalances() {
	vector<stClient>vClients;
	vClients = LoadAllClientsFromFile(ClientsFileName);
	system("cls");
	cout << "\n\t\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n___________________________________________________________";
	cout << "_____________________________________________\n\n";
	cout << "| " << left << setw(25) << "Account Number";
	cout << "| " << left << setw(50) << "Client Name";
	cout << "| " << left << setw(25) << "Balance";
	cout << "\n___________________________________________________________";
	cout << "_____________________________________________\n\n";
	double TotalBalances = 0;
	for (stClient& Client : vClients) {
		PrintClientBalance(Client);
		TotalBalances += Client.AccountBalance;
		cout << endl;
	}
	cout << "\n___________________________________________________________";
	cout << "_____________________________________________\n\n";

	cout << "\t\t\t\t\t\tTotal Balances = " << TotalBalances << endl;


}



void Withdraw() {
	system("cls");

	PrintHaederScreenWithTitle("Withdraw Screen");

	string AccountNumber = ReadAccountNumber();
	vector<stClient>vClients = LoadAllClientsFromFile(ClientsFileName);
	char Answer = 'n';
	stClient Client;
	while (!FindClientWithAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nThe client with account number [" << AccountNumber << "] is not found!\n\n";
		AccountNumber = ReadAccountNumber();
	}

	PrintClientCard(Client);


	double Amount = 0;

	cout << "\nPlease enter with amount ? ";
	cin >> Amount;

	while (Client.AccountBalance < Amount) {
		cout << "\n\nAmount Exceeds the balance , you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "\nPlease enter with amount ? ";
		cin >> Amount;
	}

	DipositClientBalanceWithAccountNumber(AccountNumber, -1 * Amount, vClients);
	UpdateClientsFileContent(ClientsFileName, vClients);
}


void ShowTransactionsScreen() {
	system("cls");
	cout << "=================================================== ";
	cout << "\n\t\t Transactions Screen";
	cout << "\n===================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Mian Menue.";
	cout << "\n===================================================\n";
	PerformTransactions(ReadTransactionOption());
}


void GoBackToTransactionsMenue() {
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ShowTransactionsScreen();
}


void PerformTransactions(enTransactoinsOptions Option) {
	switch (Option) {
	case enTransactoinsOptions::eDeposit:
		Deposit();
		GoBackToTransactionsMenue();
		break;
	case enTransactoinsOptions::eWithdraw:
		Withdraw();
		GoBackToTransactionsMenue();
		break;
	case enTransactoinsOptions::eTotalBalances:
		ShowBalances();
		GoBackToTransactionsMenue();
		break;
	case enTransactoinsOptions::eMainMenue:
		StartApp();
		break;

	}
}




void CheckChoiceWhatToDo(enMainMenuOptions Choice, vector<stClient>& vClients) {
	switch (Choice) {
	case enMainMenuOptions::ShowList:
		if (CheckPermisson((short)enMainMenuOptions::ShowList))
			ShowAllClients(vClients);

		else
			PrintAccessDenidScreen();

		break;
	case enMainMenuOptions::Add:
		if (CheckPermisson((short)enMainMenuOptions::Add))
			AddNewClients(vClients);

		else
			PrintAccessDenidScreen();

		break;
	case enMainMenuOptions::Delete:
		if (CheckPermisson((short)enMainMenuOptions::Delete))
			DeleteClient(vClients);

		else
			PrintAccessDenidScreen();

		break;
	case enMainMenuOptions::Update:
		if (CheckPermisson((short)enMainMenuOptions::Update))
			UpdateCleintData(vClients);

		else
			PrintAccessDenidScreen();

		break;
	case enMainMenuOptions::Find:
		if (CheckPermisson((short)enMainMenuOptions::Find))
			FindClient(vClients);

		else
			PrintAccessDenidScreen();
		break;
	case enMainMenuOptions::Transactions:
		if (CheckPermisson((short)enMainMenuOptions::Transactions))
			ShowTransactionsScreen();
		else
			PrintAccessDenidScreen();
		break;
	case enMainMenuOptions::ManageUsers:
		if (CheckPermisson((short)enMainMenuOptions::ManageUsers))
			ShowManageUsersMenuScreen();
		else
			PrintAccessDenidScreen();
		break;
	case enMainMenuOptions::Logout:
		system("cls");
		Login();
		break;
	}
}


void StartApp() {
	vector<stClient> vClients = LoadAllClientsFromFile(ClientsFileName);
	ShowMainMenu();
	enMainMenuOptions Choice = ReadChoice();
	CheckChoiceWhatToDo(Choice, vClients);
}


stUser ReadUserInformation() {
	stUser User;
	
	cout << "Enter Username? ";
	getline(cin >> ws, User.Username);

	cout << "Enter Password? ";
	getline(cin >> ws, User.Passsword);

	return User;
}


stUser ConvertOneLineToUser(string line) {
	vector<string> vInformation = MySplit(line);
	stUser User;

	User.Username = vInformation[0];
	User.Passsword = vInformation[1];
	User.Permissions = stoi(vInformation[2]);

	return User;
}


vector<stUser> GetAllUsers() {
	vector<stUser> vUsers;
	fstream File;
	File.open(UsersFileName, ios::in);
	if (File.is_open()) {
		string line;
		while (getline(File, line)) {
			vUsers.push_back(ConvertOneLineToUser(line));
		}
		File.close();
	}
	return vUsers;
}


bool IsUserExistsByUsernameAndPassword(stUser &User) {
	vector<stUser> vUsers;
	vUsers = GetAllUsers();
	for (stUser& U : vUsers) {
		if (U.Username == User.Username && U.Passsword == User.Passsword) {
			User = U;
			return true;
		}
	}
	return false;
}



enManageUserMenuOptions RaedManageUserChoice() {
	cout << "Choose what do you want to do ? [1 to 6] ? ";
	return(enManageUserMenuOptions)ReadNumber();
}

void ShowOneUser(stUser User) {
	cout << "| " << left << setw(15) << User.Username;
	cout << "| " << left << setw(15) << User.Passsword;
	cout << "| " << left << setw(10) << User.Permissions;
}

void ShowUsersList();
void ShowManageUsersMenuScreen();

void GoBackToManageUsersMenuScreen() {
	cout << "\n\nPress any key to go back to Manage Users Menu...";
	system("pause>0");
	ShowManageUsersMenuScreen();
}


void ShowUsersList() {
	vector<stUser> vUsers = GetAllUsers();
	cout << "\n\t\t\t\t\t\tClient List (" << vUsers.size() << ") User(s).";
	cout << "\n___________________________________________________________";
	cout << "_____________________________________________\n\n";
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(15) << "Password";
	cout << "| " << left << setw(40) << "Permissions";
	cout << "\n___________________________________________________________";
	cout << "_____________________________________________\n\n";

	for (stUser& User : vUsers) {
		ShowOneUser(User);
		cout << endl;
	}
	cout << "\n___________________________________________________________";
	cout << "_____________________________________________\n\n";
	GoBackToManageUsersMenuScreen();
}

bool IsUserExistByUserName(string UserName,stUser &User) {
	vector<stUser> vUsers = GetAllUsers();
	for (stUser& U : vUsers) {
		if (U.Username == UserName)
		{
			User = U;
			return true;
		}
	}
	return false;
}

short ReadPermissions() {
	char Answer = 'y';

	cout << "\nDo you want give full accsess? y/n? ";
	cin >> Answer;
	if (tolower(Answer) == 'y')
		return -1;

	short PermissionsValues[7] = { 1,2,4,8,16,32,64};
	
	short Permissions = 0;

	cout << "\nShow Client List? y/n ?";
	cin >> Answer;

	if (tolower(Answer) == 'y')
		Permissions += PermissionsValues[0];
	
	cout << "\nAdd New Client? y/n ? ";
	cin >> Answer;

	if (tolower(Answer) == 'y')
		Permissions += PermissionsValues[1];

	cout << "\nDelete Client ? y/n ? ";
	cin >> Answer;

	if (tolower(Answer) == 'y')
		Permissions += PermissionsValues[2];

	cout << "\nUpdate Client ? y/n ? ";
	cin >> Answer;

	if (tolower(Answer) == 'y')
		Permissions += PermissionsValues[3];

	cout << "\nFind Client ? y/n ? ";
	cin >> Answer;

	if (tolower(Answer) == 'y')
		Permissions += PermissionsValues[4];

	cout << "\nTransaction ? y/n ? ";
	cin >> Answer;

	if (tolower(Answer) == 'y')
		Permissions += PermissionsValues[5];

	cout << "\nManage Users ? y/n ? ";
	cin >> Answer;
	
	if (tolower(Answer) == 'y')
		Permissions += PermissionsValues[6];
	
	return Permissions;
}

string ConvertUserToOneLine(stUser User) {
	string Line = "", Dilem = "#//#";
	
	Line += User.Username + Dilem;
	Line += User.Passsword + Dilem;
	Line += to_string(User.Permissions);

	return Line;
}

void AddNewUserToUsersFile(stUser User) {
	fstream File;
	File.open(UsersFileName, ios :: out | ios::app);
	if (File.is_open()) {
	string Line = ConvertUserToOneLine(User);
		File << Line <<endl;
		File.close();
	}
}

void AddNewUser() {
	PrintHaederScreenWithTitle("Add New User Screen");

	stUser User;

	char AddMore = 'y';
	do {
		cout << "Adding New User :\n";
		cout << "\nEnter Username? ";
		getline(cin >> ws, User.Username);

		while (IsUserExistByUserName(User.Username,User)) {
			cout << "\nUser with [" << User.Username<< "] already exists, Enter another Username? ";
			getline(cin >> ws, User.Username);
		}

		cout << "Enter Password? ";
		getline(cin >> ws, User.Passsword);

		User.Permissions = ReadPermissions();
		
		AddNewUserToUsersFile(User);

		cout << "\nUser Added Successfuly , do you want to add more Users ? y/n ?";
		cin >> AddMore;
		
	} while (tolower(AddMore) == 'y');
	GoBackToManageUsersMenuScreen();
}

stUser FindUserInUsersFile(string Username) {
	vector<stUser> vUsers = GetAllUsers();

	for (stUser& User : vUsers) {
		if (User.Username == Username)
			return User;
	}

}

void PrintUserCard(stUser User) {

	cout << "\nThe following are the user details : ";
	cout << "\n---------------------------------------------------";
	cout << "\nUsername    :" << User.Username;
	cout << "\nPassword    :" << User.Passsword;
	cout << "\nPermissions :" << User.Permissions;
	cout << "\n---------------------------------------------------"
		 <<endl;

}

void DeleteUserFromUsersFile(string Username) {
	vector<stUser> vUsers;
	vUsers = GetAllUsers();
	fstream File;
	File.open(UsersFileName, ios::out);
	if (File.is_open()) {
		string Line;
		for (stUser& User : vUsers) {
			if (User.Username != Username) {
				Line = ConvertUserToOneLine(User);
				File << Line << endl;
			}
		}
		File.close();
	}
}

void DeleteUser() {
	PrintHaederScreenWithTitle("Delete Users Screen");

	stUser User;
	char Answer = 'y';

	cout << "\nEnter Username? ";
	getline(cin >> ws, User.Username);

	if (User.Username == "Admin") {
		cout << "\nYou can't Delete this user.";
	}

	else if (IsUserExistByUserName(User.Username,User)) {
		PrintUserCard(User);

		cout << "\nAre you sure do you want delete this user ? y/n ? ";
		cin >> Answer;

		if (tolower(Answer) == 'y') {
			DeleteUserFromUsersFile(User.Username);
			cout << "\nUser Deleted Successfully.";
		}
			
	}

	else {
		cout << "\nUser with Username (" << User.Username << ") is not found!";
	}
	GoBackToManageUsersMenuScreen();
}


stUser ReadUpdatedUserInformation(string Username) {
	stUser User;

	User.Username = Username;

	cout << "\nEnter Password? ";
	getline(cin >> ws, User.Passsword);

	User.Permissions =(User.Username == "Admin")? -1 : ReadPermissions();

	if (User.Username == CurrentUser.Username)
		CurrentUser.Permissions = User.Permissions;

	return User;
}

void UpdateUserInformationInUsersFile(string Username) {
	vector<stUser> vUsers;
	vUsers = GetAllUsers();
	fstream File;
	File.open(UsersFileName, ios::out);
	if (File.is_open()) {
		string Line;

		for (stUser& User : vUsers) {
			if (User.Username == Username)
				User = ReadUpdatedUserInformation(Username);

			Line = ConvertUserToOneLine(User);
			File << Line << endl;
		}
		File.close();
	}
}

void UpdateUser() {
	PrintHaederScreenWithTitle("Update Users Screen");

	stUser User;
	char Answer = 'y';
	cout << "\nEnter Username? ";
	getline(cin >> ws, User.Username);

	if (IsUserExistByUserName(User.Username,User)) {
		PrintUserCard(User);

		cout << "\nAre you sure do you want to update this user ? y/n ? ";
		cin >> Answer;

		if (tolower(Answer) == 'y') {
			UpdateUserInformationInUsersFile(User.Username);
			cout << "\nUser Updated Successfully.";
		}
	}
	else {
		cout << "\nUser with Username (" << User.Username << ") is NOT found!";
	}
	GoBackToManageUsersMenuScreen();
}

void FindUser() {
	PrintHaederScreenWithTitle("Find User Screen");

	stUser User;

	cout << "\nEnter Username? ";
	getline(cin >> ws,User.Username);

	if (IsUserExistByUserName(User.Username,User)) {
		PrintUserCard(User);
	}
	else {
		cout << "\nUser with username (" << User.Username << ") is NOT found!";
	}
	GoBackToManageUsersMenuScreen();
}

void PrintAccessDenidScreen() {
	system("cls");
	cout << "---------------------------------------------------";
	cout << "\nAcces Denied, "
		 << "\nYou Don't Have Permission To Do This, "
		 << "\nPlease Conact Your Admin.";
	cout << "\n---------------------------------------------------\n";

	GoBackToMainMinu();
}

bool CheckPermisson(short Option) {
	short Permissions[7] = {1,2,4,8,16,32,64};
	return ((CurrentUser.Permissions & Permissions[Option - 1]) != 0);
}

void CheckManageUserChoice(enManageUserMenuOptions Option) {
	switch (Option) {
	case enManageUserMenuOptions::ListUsers:
		system("cls");
		ShowUsersList();
		break;
	case enManageUserMenuOptions::AddUser:
		system("cls");
		AddNewUser();
		break;
	case enManageUserMenuOptions::Delete_User:
		system("cls");
		DeleteUser();
		break;
	case enManageUserMenuOptions::Update_User:
		system("cls");
		UpdateUser();
		break;
	case enManageUserMenuOptions::Find_User:
		system("cls");
		FindUser();
		break;
	case enManageUserMenuOptions::MainMenu:
		StartApp();
		break;
	}
}


void ShowManageUsersMenuScreen() {
	system("cls");
	cout << "=================================================== ";
	cout << "\n\t\t Manage Users Menu Screen";
	cout << "\n===================================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << "\n===================================================\n";
	enManageUserMenuOptions Choice = RaedManageUserChoice();
	CheckManageUserChoice(Choice);
}

void Login() {
	string Title = "Login Screen";

	PrintHaederScreenWithTitle(Title);

    CurrentUser = ReadUserInformation();

	while (!IsUserExistsByUsernameAndPassword(CurrentUser)) {
		system("cls");

		PrintHaederScreenWithTitle(Title);

		cout << "Invalid Username/Password!\n";
		CurrentUser = ReadUserInformation();

	}

	StartApp();

}

int main() {
	Login();
	system("pause>0");
	return 0;
}


