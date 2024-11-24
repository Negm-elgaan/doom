#pragma once
#include "clsBankClient.h"
#include "clsdate.h"
#include "clsInputValidate.h"
#include "clsDynamicArray.h"
#include "clsMyQueue.h"
#include <math.h>
#include <thread>
class clsLoanClient
{
	private:
		enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
		enMode _Mode;
		string _AccountNumber;
		string _FullName;
		double _Loan;
        double _LoanWithInterest;
		string _LoanBeginDate;
        string _LoanEndDate;
        double _InterestRate = 1.14;
        int _Months;
		bool _MarkedForDelete = false;

        static clsLoanClient _ConvertLinetoLoanClientObject(string Line, string Seperator = "#//#")
        {
            vector<string> vLoanClientData;
            vLoanClientData = clsString::Split(Line, Seperator);

            return clsLoanClient(enMode::UpdateMode, vLoanClientData[0], vLoanClientData[1], stod(vLoanClientData[2]),
                stod(vLoanClientData[3]), vLoanClientData[4] , vLoanClientData[5],stod(vLoanClientData[6]));

        }

        static clsLoanClient _ConvertBankClientObjectToLoanClientObject(clsBankClient BankClient , double Loan , string BeginDate , string EndDate , double InterestRate = 1.14)
        {
            return clsLoanClient(enMode::AddNewMode, BankClient.AccountNumber(), BankClient.FullName(), Loan, 0, BeginDate, EndDate, InterestRate);
        }

        static clsLoanClient _GetEmptyClientObject()
        {
            return clsLoanClient(enMode::EmptyMode, "", "", 0 , 0 , "", "" ,0);
        }
        static string _ConvertLoanClientObjectToLine(clsLoanClient LoanClient, string Seperator = "#//#")
        {

            string stClientRecord = "";
            stClientRecord += LoanClient._AccountNumber + Seperator;
            stClientRecord += LoanClient._FullName + Seperator;
            stClientRecord += to_string(LoanClient._Loan);
            stClientRecord += to_string(LoanClient.GetCurrentLoan());
            stClientRecord += LoanClient._LoanBeginDate + Seperator;
            stClientRecord += LoanClient._LoanEndDate + Seperator;
            stClientRecord += to_string(LoanClient._InterestRate);

            return stClientRecord;

        }



        static  vector <clsLoanClient> _LoadLoanClientsDataFromFile()
        {

            vector <clsLoanClient> vClients;

            fstream MyFile;
            MyFile.open("LoanClients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {

                string Line;


                while (getline(MyFile, Line))
                {

                    clsLoanClient Client = _ConvertLinetoLoanClientObject(Line);

                    vClients.push_back(Client);
                }

                MyFile.close();

            }

            return vClients;

        }

        static void _SaveLoanCleintsDataToFile(vector <clsLoanClient> vClients)
        {

            fstream MyFile;
            MyFile.open("LoanClients.txt", ios::out);//overwrite

            string DataLine;

            if (MyFile.is_open())
            {

                for (clsLoanClient C : vClients)
                {
                    if (C.MarkedForDeleted() == false)
                    {
                        //we only write records that are not marked for delete.  
                        DataLine = _ConvertLoanClientObjectToLine(C);
                        MyFile << DataLine << endl;

                    }

                }

                MyFile.close();

            }

        }


        void _Update()
        {
            vector <clsLoanClient> _vClients;
            _vClients = _LoadLoanClientsDataFromFile();

            for (clsLoanClient& C : _vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = *this;
                    break;
                }

            }

            _SaveLoanCleintsDataToFile(_vClients);

        }
        void _AddNew()
        {

            _AddDataLineToFile(_ConvertLoanClientObjectToLine(*this));
        }
        void _AddDataLineToFile(string  stDataLine)
        {
            fstream MyFile;
            MyFile.open("LoanClients.txt", ios::out | ios::app);

            if (MyFile.is_open())
            {

                MyFile << stDataLine << endl;

                MyFile.close();
            }

        }
        struct stLoanLogRecord;

        static stLoanLogRecord _ConvertLoanLogLineToRecord(string Line, string Seperator = "#//#")
        {
            stLoanLogRecord LoanLogRecord;

            vector <string> vLoanLogRecordLine = clsString::Split(Line, Seperator);
            LoanLogRecord.AccountNumber = vLoanLogRecordLine[0];
            LoanLogRecord.Loan = stod(vLoanLogRecordLine[1]);
            LoanLogRecord.Date = vLoanLogRecordLine[2];
            LoanLogRecord.UserName = vLoanLogRecordLine[3];

            return LoanLogRecord;

        }

        string _PrepareLoanLogRecord(float Amount,
            string UserName, string Seperator = "#//#")
        {
            string LoanLogRecord = "";
            LoanLogRecord += AccountNumber + Seperator;
            LoanLogRecord += to_string(Amount) + Seperator;
            LoanLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
            LoanLogRecord += UserName;

            return LoanLogRecord;
        }

        int CheckIFToApplyInterest()
        {
            clsDate CurrentDate = clsDate::GetSystemDate();
            clsDate BeginDate(_LoanBeginDate);
            int Days = clsDate::GetDifferenceInDays(BeginDate, CurrentDate);
            return Days / 30 == 0 ? 1 : Days / 30 ;
        }
    public:
        clsLoanClient(enMode mode , string AccountNumber , string Name , double Loan  , double LoanWithInterest, string LoanBeginDate , string LoanEndDate , double InterestRate)
        {
            _Mode = mode;
            _AccountNumber = AccountNumber;
            _FullName = Name;
            _Loan = Loan;
            _LoanWithInterest = LoanWithInterest;
            _LoanBeginDate = LoanBeginDate;
            _LoanEndDate = LoanEndDate;
            _InterestRate = InterestRate;
            _LoanWithInterest = GetCurrentLoan();
        }

        struct stLoanLogRecord
        {
            string Date;
            string AccountNumber;
            double Loan;
            string UserName;
        };

        bool IsEmpty()
        {
            return (_Mode == enMode::EmptyMode);
        }

        bool MarkedForDeleted()
        {
            return _MarkedForDelete;
        }

        void SetAccountNumber(string AccountNumber)
        {
            _AccountNumber = AccountNumber;
        }

        string GetAccountNumber()
        {
            return _AccountNumber;
        }

        __declspec(property(get = GetAccountNumber, put = SetAccountNumber)) string AccountNumber;

        void SetFullName(string FullName)
        {
            _FullName = FullName;
        }

        string GetFullName()
        {
            return _FullName;
        }

        __declspec(property(get = GetFullName, put = SetFullName)) string FullName;

        void SetLoanBeginDate(string LoanBeginDate)
        {
            _LoanBeginDate = LoanBeginDate;
        }

        string LoanBeginDate()
        {
            return _LoanBeginDate;
        }

        __declspec(property(get = LoanBeginDate, put = SetLoanBeginDate)) string BeginDate;

        void SetLoanEndDate(string LoanEndDate)
        {
            _LoanEndDate = LoanEndDate;
        }

        string LoanEndDate()
        {
            return _LoanEndDate;
        }

        __declspec(property(get = LoanEndDate, put = SetLoanEndDate)) string EndDate;
        
        void SetInterestRate(double InterestRate)
        {
            _InterestRate = InterestRate;
        }

        double GetInterestRate()
        {
            return _InterestRate;
        }

        __declspec(property(get = GetInterestRate, put = SetInterestRate)) double InterestRate;

        void SetLoan(double loan)
        {
            _Loan = loan;
        }

        double GetLoan()
        {
            return _Loan;
        }

        __declspec(property(get = GetLoan, put = SetLoan)) double Loan;

        double GetIntialLoan()
        {
            return _Loan;
        }

        double GetCurrentLoan()
        {
            _Months = CheckIFToApplyInterest();
            _LoanWithInterest = _InterestRate * _Loan * _Months;
            return _LoanWithInterest;
        }

        clsDynamicArray <thread> SetAll(string AccountNumber , string FullName , string LoanBeginDate , string LoanEndDate , double Loan , double InterestRate)
        {
            clsDynamicArray <thread> DyArTh(6);
            DyArTh.SetItem(0, std::move(thread(&clsLoanClient::SetAccountNumber, this, AccountNumber)));
            DyArTh.SetItem(1, std::move(thread(&clsLoanClient::SetFullName, this, FullName)));
            DyArTh.SetItem(2, std::move(thread(&clsLoanClient::SetLoanBeginDate, this, LoanBeginDate)));
            DyArTh.SetItem(3, std::move(thread(&clsLoanClient::SetLoanEndDate, this, LoanEndDate)));
            DyArTh.SetItem(4, std::move(thread(&clsLoanClient::SetLoan, this, Loan)));
            DyArTh.SetItem(5, std::move(thread(&clsLoanClient::SetInterestRate, this, InterestRate)));


            for (thread& i : DyArTh)
            {
                i.join();
            }

            return DyArTh;
        }

        void Print()
        {
            cout << "\nloan Client Card:";
            cout << "\n___________________";
            cout << "\nAccountNumber   : " << AccountNumber;
            cout << "\nFull Name   : " << FullName;
            cout << "\nLoan   :" << Loan;
            cout << "\nLoan Begin Date       : " << LoanBeginDate();
            cout << "\nLoan End Date       : " << LoanEndDate();
            cout << "\nBalance     : " << InterestRate << "%";
            cout << "\n___________________\n";
        }

        static clsLoanClient Find(string AccountNumber)
        {


            fstream MyFile;
            MyFile.open("LoanClients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsLoanClient Client = _ConvertLinetoLoanClientObject(Line);
                    if (Client.AccountNumber == AccountNumber)
                    {
                        MyFile.close();
                        return Client;
                    }

                }

                MyFile.close();

            }

            return _GetEmptyClientObject();
        }
        /*static clsBankClient Find(string AccountNumber, string PinCode)
        {



            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                    {
                        MyFile.close();
                        return Client;
                    }

                }

                MyFile.close();

            }
            return _GetEmptyClientObject();
        }*/

        enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };


        enSaveResults Save()
        {

            switch (_Mode)
            {
            case enMode::EmptyMode:
            {
                if (IsEmpty())
                {

                    return enSaveResults::svFaildEmptyObject;

                }

            }

            case enMode::UpdateMode:
            {


                _Update();

                return enSaveResults::svSucceeded;

                break;
            }

            case enMode::AddNewMode:
            {
                //This will add new record to file or database
                if (clsBankClient::IsClientExist(_AccountNumber))
                {
                    return enSaveResults::svFaildAccountNumberExists;
                }
                else
                {
                    _AddNew();

                    //We need to set the mode to update after add new
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }

                break;
            }
            }

        }
        static clsLoanClient GetAddNewClientObject(string AccountNumber)
        {
            return clsLoanClient(enMode::AddNewMode, AccountNumber, "", 0 , 0 ,"", "", 0);
        }
        static bool IsClientExist(string AccountNumber)
        {

            clsLoanClient Client1 = clsLoanClient::Find(AccountNumber);
            return (!Client1.IsEmpty());
        }
        bool Delete()
        {
            vector <clsLoanClient> _vClients;
            _vClients = _LoadLoanClientsDataFromFile();

            for (clsLoanClient& C : _vClients)
            {
                if (C.AccountNumber == _AccountNumber)
                {
                    C._MarkedForDelete = true;
                    break;
                }

            }

            _SaveLoanCleintsDataToFile(_vClients);

            *this = _GetEmptyClientObject();

            return true;

        }
        static vector <clsLoanClient> GetLoanClientsList()
        {
            return _LoadLoanClientsDataFromFile();
        }

        /*static float GetTotalBalances()
        {
            vector <clsBankClient> vClients = clsBankClient::GetClientsList();

            double TotalBalances = 0;

            for (clsBankClient Client : vClients)
            {

                TotalBalances += Client.AccountBalance;
            }

            return TotalBalances;

        }*/


        static double GetTotalLoans()
        {
            vector <clsLoanClient> vClients = clsLoanClient::GetLoanClientsList();

            double TotalBalances = 0;

            for (clsLoanClient Client : vClients)
            {

                TotalBalances += Client.GetCurrentLoan();
            }

            return TotalBalances;
        }

        static  vector <stLoanLogRecord> GetTransfersLogList()
        {
            vector <stLoanLogRecord> vTransferLogRecord;

            fstream MyFile;
            MyFile.open("LoanLog.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {

                string Line;

                stLoanLogRecord TransferRecord;

                while (getline(MyFile, Line))
                {

                    TransferRecord = _ConvertLoanLogLineToRecord(Line);

                    vTransferLogRecord.push_back(TransferRecord);

                }

                MyFile.close();

            }

            return vTransferLogRecord;

        }

       

       /* void ProcessCalculations(vector <clsLoanClient>& clients)
        {
            int size = clients.size();
            if (size % 4 != 0)
                return;
            int chunk = size / 4;
            for (int i = 0; i < chunk; i++)
            {
                clsLoanClient C1 = clients[i];
                thread T1(&clsLoanClient::GetCurrentLoan, C1);
                T1.join();
            }
            for (int i = chunk; i < chunk * 2; i++)
            {
                clsLoanClient C2 = clients[i];
                thread T2(&clsLoanClient::GetCurrentLoan, C2);
                T2.join();
            }
            for (int i = chunk * 2; i < chunk * 3; i++)
            {
                clsLoanClient C3 = clients[i];
                thread T3(&clsLoanClient::GetCurrentLoan, C3);
                T3.join();
            }
            for (int i = chunk * 3; i < chunk * 4; i++)
            {
                clsLoanClient C4 = clients[i];
                thread T4(&clsLoanClient::GetCurrentLoan, C4);
                T4.join();
            }

        }*/
        void ProcessCalculations(vector<clsLoanClient>& clients)
        {
            int size = clients.size();
            if (size % 4 != 0) return; // Skip if not divisible by 4

            int chunk = size / 4;
            vector<thread> threads;  // Vector to hold the threads

            // Create and store threads for each chunk
            for (int i = 0; i < chunk; i++)
            {
                clsLoanClient C1 = clients[i];
                threads.push_back(thread(&clsLoanClient::GetCurrentLoan, C1));
            }
            for (int i = chunk; i < chunk * 2; i++)
            {
                clsLoanClient C2 = clients[i];
                threads.push_back(thread(&clsLoanClient::GetCurrentLoan, C2));
            }
            for (int i = chunk * 2; i < chunk * 3; i++)
            {
                clsLoanClient C3 = clients[i];
                threads.push_back(thread(&clsLoanClient::GetCurrentLoan, C3));
            }
            for (int i = chunk * 3; i < chunk * 4; i++)
            {
                clsLoanClient C4 = clients[i];
                threads.push_back(thread(&clsLoanClient::GetCurrentLoan, C4));
            }

            // Join all threads
            for (thread& t : threads)
            {
                t.join();  // Wait for all threads to complete
            }
        }


        static vector <clsLoanClient> GetLoansList()
        {
            return _LoadLoanClientsDataFromFile();
        }

        /**clsLoanClient BTOL(clsBankClient BankClient)
        {
            return _ConvertBankClientObjectToLoanClientObject(BankClient, Loan, LoanBeginDate, LoanEndDate);
        }*/
};
//loan is not probably handled
//loanClient is not done

