# 🏦 Banking Management System

A console-based **Banking Management System** developed in **C++**. The application allows bank employees to manage client accounts,
perform banking transactions, and manage system users through a role-based permission system. All data is stored in text files using file handling.

---

 Features

 Client Management

* Display all clients.
* Add a new client.
* Update client information.
* Delete a client.
* Search for a client by account number.

 Transactions

* Deposit money into a client account.
* Withdraw money from a client account.
* Display all client balances.
* Calculate the total balance of all client accounts.

 User Management

* User login authentication.
* Display all users.
* Add new users.
* Update existing users.
* Delete users (except the Admin account).
* Search for users by username.

 Permission System

Each user can be assigned permissions for specific operations:

* Show Client List
* Add Client
* Delete Client
* Update Client
* Find Client
* Transactions
* Manage Users

The **Admin** user has full access to all system features.

---

 Project Structure

```text
Banking-Management-System/
│
├── BankSystem.cpp
├── Clients.txt
├── Users.txt
└── README.md
```

---

 Data Storage

The project stores data in text files.

 Clients.txt

Each client is stored in the following format:

```text
AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance
```

Example:

```text
1001#//#1234#//#John Smith#//#0123456789#//#5000
```

 Users.txt

Each user is stored in the following format:

```text
Username#//#Password#//#Permissions
```

Example:

```text
Admin#//#1234#//#-1
```

`-1` represents full system permissions.

---

 Main Menu

```text
1. Show Client List
2. Add New Client
3. Delete Client
4. Update Client
5. Find Client
6. Transactions
7. Manage Users
8. Logout
```

---

 Transactions Menu

```text
1. Deposit
2. Withdraw
3. Total Balances
4. Main Menu
```

---

 Manage Users Menu

```text
1. List Users
2. Add New User
3. Delete User
4. Update User
5. Find User
6. Main Menu
```

---

 Technologies Used

* C++
* Standard Template Library (STL)
* File Handling (`fstream`)
* Vectors
* Structures (`struct`)
* Console Application

---

 How to Run

 Clone the repository

```bash
git clone https://github.com/R00T-0X0/Banking-Management-System.git
```
 Compile

Using g++:

```bash
g++ BankSystem.cpp -o BankingSystem
```

Run

Windows:

```bash
BankingSystem.exe
```

Linux/macOS:

```bash
./BankingSystem
```

---

 Project Objectives

This project demonstrates the practical use of:

* File handling in C++
* CRUD operations
* Authentication and authorization
* Menu-driven applications
* Data persistence using text files
* Functions and modular programming
* Vectors and structures
* String processing

---

 Future Improvements

* Improve input validation.
* Encrypt user passwords.
* Store data in a database instead of text files.
* Add transaction history.
* Refactor the project using Object-Oriented Programming (OOP).
* Develop a graphical user interface (GUI).

---

 Author
Developed by Bashar Al-Madhaji.

GitHub: https://github.com/R00T-0X0
