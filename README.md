# Bank-Systems-OOP  
### 🎓 *Based on Course: 11 - OOP as it Should Be (Applications)*

**Bank Systems OOP** is a console-based bank management system built using **Object-Oriented Programming (OOP)** principles in C++.  
It provides essential banking functionalities for clients and admin users, with a secure and structured system architecture.


## ✨ Features

- 🔐 **Login Screen** – for secure access

---

## 🖥️ Main Screen Features

### 📋 Show Client List  
Allows authorized users to view client information from the Clients file.  
Unauthorized users will be denied access.

### ➕ Add New Client  
Allows authorized users to add a new client and save their information to the Clients file.

### ✏️ Update Client Information  
Allows authorized users to update existing client data and reflect the changes in the Clients file.

### 🔍 Find Client  
Allows authorized users to search for a client by account number and display their information from the Clients file.

---

## 💰 Transactions Menu 
Allows authorized users to access the transactions screen.  
Unauthorized users will be denied access.

### 💵 Deposit  
Enables users to help clients deposit money into their accounts.

### 🏧 Withdraw  
Allows clients to withdraw money if they have sufficient balance.  
The system will block the operation if the balance is insufficient.

### 📊 Total Balances  
Displays the total balance of all clients.

### 🔄 Transfer  
Allows clients to transfer money between accounts, given sufficient funds in the sender's account.

### 🧾 Transfer Log  
Displays a log of all completed transfers.

### 🏠 Return to Main Menu  
Returns the user to the main screen.

---

## 👤 Managing Users

### 📄 List Users  
Allows authorized users to view all user information from the Users file.

### ➕ Add New User  
Allows authorized users to add a new user and save their data to the Users file.

### ❌ Delete User  
Allows authorized users to delete a user (except the admin) by locating their data in the Users file.

### ✏️ Update User  
Enables authorized users to update a user's information and save the changes to the Users file.

### 🔍 Find User  
Allows authorized users to search for a specific user in the Users file.

### 🏠 Return to Main Menu  
Returns the user to the main screen.

---

## 🧩 Other Features

### 📝 Login Register  
Records every successful login attempt in the system.

### 💱 Currency Exchange  
Allows users to convert between different currencies.

### 🚪 Logout  
Exit the system securely.

## 📁 Project Structure

```text
BankSystem/
├── Core/
│   ├── clsBankClient.h
│   ├── clsCurrency.h
│   ├── clsPerson.h
│   ├── clsUser.h
│   └── InterfaceCommunication.h
├── Lib/
│   ├── clsDate.h
│   ├── clsInputValidate.h
│   ├── clsString.h
│   └── clsUtility.h
├── Screens/
│   ├── clsEmployee.h
│   ├── clsMainMenu.h
│   ├── clsScreen.h
│   ├── Global.h
│   ├── Client/
│   │   ├── clsAddNewClientsScreen.h
│   │   ├── clsClientListScreen.h
│   │   ├── clsDeleteClientScreen.h
│   │   ├── clsFindClientScreen.h
│   │   ├── clsTransactionsMenuScreen.h
│   │   ├── clsTransfersLogScreen.h
│   │   ├── clsUpdateClientScreen.h
│   │   └── Transactions/
│   │       ├── clsDepositScreen.h
│   │       ├── clsTotalBalanceScreen.h
│   │       ├── clsTransferScreen.h
│   │       └── clsWithdrawScreen.h
│   ├── User/
│   │   ├── clsAddNewUsersScreen.h
│   │   ├── clsDeleteUserScreen.h
│   │   ├── clsFindUserScreen.h
│   │   ├── clsListUsersScreen.h
│   │   ├── clsLoginScreen.h
│   │   ├── clsManageUsersMenuScreen.h
│   │   ├── clsShowLoginRegisterScreen.h
│   │   └── clsUpdateUserScreen.h
│   └── Currencies/
│       ├── clsCurrenciesListScreen.h
│       ├── clsCurrencyCalculatorScreen.h
│       ├── clsCurrencyExchangeMainScreen.h
│       ├── clsFindCurrency.h
│       └── clsUpdateCurrencyRateScreen.h