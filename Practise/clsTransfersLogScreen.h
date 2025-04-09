#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsBankClient.h";
#include <iomanip>

class clsTransfersLogScreen : protected clsScreen
{
private:
    static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
    {
        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferLogRecord.Date_Time;
        cout << "| " << setw(8) << left << TransferLogRecord.SourceAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.DestinationAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.srcBalanceAfter;
        cout << "| " << setw(10) << left << TransferLogRecord.destBalanceAfter;
        cout << "| " << setw(8) << left << TransferLogRecord.UserName;
    }

public:
    static void ShowTransfersLogScreen()
    {

        vector<clsBankClient::stTransferLogRecord>vTransferLogRecord = clsBankClient::GetTransfersLogList();

        string Title = "\t Transfer Log List Screen ";
        string SubTitle = "\t\t(" + to_string(vTransferLogRecord.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << setw(25) << left << "Date/Time";
        cout << "| " << setw(8) << left << "s.No";
        cout << "| " << setw(8) << left << "d.No";
        cout << "| " << setw(8) << left << "Amount";
        cout << "| " << setw(10) << left << "s.Balance";
        cout << "| " << setw(10) << left << "d.Balance";
        cout << "| " << setw(8) << left << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t No Transfer  Available In The Sysstem!" << endl;
        else
        {
            for (clsBankClient::stTransferLogRecord& Record : vTransferLogRecord)
            {
                _PrintTransferLogRecordLine(Record);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

};

