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
        string _Phone;
        int _CreditScore = 0;

        class clsLoan
        {
            double _Loan;
            double _LoanWithInterest;
            string _LoanBeginDate;
            string _LoanEndDate;
            double _InterestRate = 1.14;
            int _Months;
            string _ID;
            public:
                static enum enLoanMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
                enLoanMode _Mode;
                clsLoan()
                {                  
                    _Loan = 0;
                    _LoanWithInterest = 0;
                    _LoanBeginDate = "";
                    _LoanEndDate = "";
                    _InterestRate = 1.14;
                    _Months = 0;
                    return;
                }

                clsLoan(/*enMode Mode,*/ double Loan, string LoanBeginDate, string LoanEndDate, double InterestRate)
                {
                    //_Mode = Mode;
                    _Loan = Loan;
                    _LoanWithInterest = _Loan;
                    _LoanBeginDate = LoanBeginDate;
                    _LoanEndDate = LoanEndDate;
                    _InterestRate = InterestRate;
                    _Months = 0;
                    return;
                }

                clsLoan(enLoanMode Mode, double Loan, string LoanBeginDate, string LoanEndDate, double InterestRate)
                {
                    _Mode = Mode;
                    _Loan = Loan;
                    _LoanWithInterest = _Loan;
                    _LoanBeginDate = LoanBeginDate;
                    _LoanEndDate = LoanEndDate;
                    _InterestRate = InterestRate;
                    _Months = 0;
                    return;
                }

                static string _ConvertClsLoanObjectToLine(clsLoan LoanObject , string separator = "*//*")
                {
                    string Line = "";
                    Line += to_string(LoanObject.Loan);
                    Line += separator;
                    Line += to_string(LoanObject._LoanWithInterest);
                    Line += separator;
                    Line += LoanObject.BeginDate;
                    Line += separator;
                    Line += LoanObject.EndDate;
                    Line += to_string(LoanObject.InterestRate);
                    Line += to_string(LoanObject._Months);
                    return Line;
                }

                static clsLoan GetEmptyLoanObject()
                {
                    return clsLoan(/**enMode::EmptyMode,*/ 0, "", "", 0);
                }

                static clsLoan _ConvertLineToClsLoanObject(string Line , string separator = "*//*")
                {
                    vector <string> vLoanData = clsString::Split(Line,separator);
                    return clsLoan(/*enMode::UpdateMode,*/ stod(vLoanData[0]), vLoanData[2], vLoanData[3], stod(vLoanData[4]));
                }

                int CheckIFToApplyInterest()
                {
                    clsDate CurrentDate = clsDate::GetSystemDate();
                    clsDate BeginDate(_LoanBeginDate);
                    int Days = clsDate::GetDifferenceInDays(BeginDate, CurrentDate);
                    return Days / 30 == 0 ? 1 : Days / 30;
                }

                double GetCurrentLoan()
                {
                    _LoanWithInterest = _Loan;
                    _Months = CheckIFToApplyInterest();
                    for (int i = 0; i < _Months; i++)
                    {
                        _LoanWithInterest *= _InterestRate;
                    }
                    return _LoanWithInterest;
                }

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

                void SetID(string ID)
                {
                    _ID = ID;
                }

                string GetID()
                {
                    return _ID;
                }

                __declspec(property(get = GetID, put = SetID)) string ID;

                int GetMonths()
                {
                    return _Months;
                }

                bool IsEmpty()
                {
                    return (_Mode == enMode::EmptyMode);
                }

                clsDynamicArray <thread> SetAll(double Loan, string LoanBeginDate, string LoanEndDate, double InterestRate = 1.14)
                {
                    clsDynamicArray <thread> DyArrTh(4);
                    DyArrTh.SetItem(0, std::move(thread(&clsLoan::SetLoan, this, Loan)));
                    DyArrTh.SetItem(1, std::move(thread(&clsLoan::SetLoanBeginDate, this, LoanBeginDate)));
                    DyArrTh.SetItem(2, std::move(thread(&clsLoan::SetLoanEndDate, this, LoanEndDate)));
                    DyArrTh.SetItem(3, std::move(thread(&clsLoan::SetInterestRate, this, InterestRate)));
                }

                void print()
                {
                    cout << "\nLoan:" << _Loan << endl;
                    cout << "\nLoan with Interest: " << GetCurrentLoan() << endl;
                    cout << "\nInterest Rate: " << _InterestRate << endl;
                    cout << "\nLoan Begin Date: " << _LoanBeginDate << endl;
                    cout << "\nLoan End Date: " << _LoanEndDate << endl;
                    cout << "\n_________________\n";
                }


        };
        int _NumOfLoans = 0;
        clsDynamicArray <clsLoan> _LoanList; //pointer list of different loans to same account with same or different interest rate
		bool _MarkedForDelete = false;

        bool _RepayFullLoan(string ID)
        {
            if (IsLoanExist(ID))
            {
                return _LoanList.DeleteItemAt(FindIndexByLoanID(ID));
            }
            
            return false;
        }

        bool CheckCreditScore()
        {
            return _CreditScore >= -120;
        }

        static clsLoanClient _ConvertLinetoLoanClientObject(string Line, string Seperator = "#//#")
        {
            vector<string> vLoanClientData;
            vLoanClientData = clsString::Split(Line, Seperator);

            return clsLoanClient(enMode::UpdateMode, vLoanClientData[0], vLoanClientData[1], vLoanClientData[2],
                clsLoan::_ConvertLineToClsLoanObject(vLoanClientData[3])); // Data is missing

        }

        /*static clsLoanClient _ConvertLinetoLoanClientObject(string Line, string Seperator = "#//#")
        {
            vector<string> vLoanClientData;
            vLoanClientData = clsString::Split(Line, Seperator);

            return clsLoanClient(enMode::UpdateMode, vLoanClientData[0], vLoanClientData[1], stod(vLoanClientData[2]),
                stod(vLoanClientData[3]), vLoanClientData[4] , vLoanClientData[5],stod(vLoanClientData[6]) , vLoanClientData[7] , clsLoan::_ConvertLineToClsLoanObject(vLoanClientData[8]));

        }*/

        static clsLoanClient _ConvertBankClientObjectToLoanClientObject(clsBankClient BankClient)
        {
            return clsLoanClient(enMode::AddNewMode, BankClient.AccountNumber(), BankClient.FullName(), BankClient.Phone);
        }

        /*static clsLoanClient _ConvertBankClientObjectToLoanClientObject(clsBankClient BankClient , double Loan = 0 , string BeginDate = "", string EndDate = "", double InterestRate = 1.14)
        {
            return clsLoanClient(enMode::AddNewMode, BankClient.AccountNumber(), BankClient.FullName(), Loan, 0, BeginDate, EndDate, InterestRate , BankClient.Phone);
        }*/

        static clsLoanClient _GetEmptyClientObject()
        {
            return clsLoanClient(enMode::EmptyMode, "", "", "");
        }

        /*static clsLoanClient _GetEmptyClientObject()
        {
            return clsLoanClient(enMode::EmptyMode, "", "", 0 , 0 , "", "" ,0 , "");
        }*/

        static string _ConvertLoanClientObjectToLine(clsLoanClient LoanClient, string Seperator = "#//#")
        {

            string stClientRecord = "";
            stClientRecord += LoanClient._AccountNumber + Seperator;
            stClientRecord += LoanClient._FullName + Seperator;
            stClientRecord += LoanClient._Phone + Seperator;
            //stClientRecord += to_string(LoanClient._Loan);
            //stClientRecord += to_string(LoanClient.GetCurrentLoan());
            //stClientRecord += LoanClient._LoanBeginDate + Seperator;
            //stClientRecord += LoanClient._LoanEndDate + Seperator;
            //stClientRecord += to_string(LoanClient._InterestRate);
            for (int i = 0; i < LoanClient._LoanList.Size(); i++)
            {
                stClientRecord += LoanClient._LoanList.Getitem(i)._ConvertClsLoanObjectToLine(LoanClient._LoanList.Getitem(i));
            }

            return stClientRecord;

        }

        void ProcessLoanList()
        {
            for (int i = 0; i < _LoanList.Size(); i++)
            {
                _LoanList.Getitem(i).GetCurrentLoan();
            }
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

       /*not done */ static stLoanLogRecord _ConvertLoanLogLineToRecord(string Line, string Seperator = "#//#")
        {
            stLoanLogRecord LoanLogRecord;

            vector <string> vLoanLogRecordLine = clsString::Split(Line, Seperator);
            LoanLogRecord.AccountNumber = vLoanLogRecordLine[0];
            LoanLogRecord.Loan = stod(vLoanLogRecordLine[1]);
            LoanLogRecord.Date = vLoanLogRecordLine[2];
            LoanLogRecord.InterestRate = stod(vLoanLogRecordLine[3]);
            LoanLogRecord.Status = vLoanLogRecordLine[4];
            LoanLogRecord.UserName = vLoanLogRecordLine[5];

            return LoanLogRecord;

        }

       /*not done*/ /*string _PrepareLoanLogRecord(float Amount,
            string UserName , string Status , string Seperator = "#//#")
        {
            string LoanLogRecord = "";
            LoanLogRecord += AccountNumber + Seperator;
            LoanLogRecord += to_string(Amount) + Seperator;
            LoanLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
            LoanLogRecord += UserName;

            return LoanLogRecord;
        }*/

        string _PrepareLoanLogRecord(stLoanLogRecord sLoanLogRecord ,  string Seperator = "#//#")
       {
           string LoanLogRecord = "";
           LoanLogRecord += sLoanLogRecord.Date + Seperator;
           LoanLogRecord += sLoanLogRecord.AccountNumber + Seperator;
           LoanLogRecord += to_string(sLoanLogRecord.Loan) + Seperator;
           LoanLogRecord += to_string(sLoanLogRecord.InterestRate) + Seperator;
           LoanLogRecord += sLoanLogRecord.Status + Seperator;
           //LoanLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
           LoanLogRecord += sLoanLogRecord.UserName;

           return LoanLogRecord;
       }

       
    public:

        clsLoanClient()
        {
            int input = 0;
            cin >> input >> _AccountNumber >> _FullName >> _Phone;
            switch (input)
            {
                case 0:
                    _Mode = enMode::EmptyMode;
                    break;
                case 1:
                    _Mode = enMode::AddNewMode;
                    break;
                case 2:
                    _Mode = enMode::UpdateMode;
                    break;
            }
        }

        clsLoanClient(enMode mode , string AccountNumber , string Name , string Phone , clsLoan LoanObject = clsLoan())
        {
            _Mode = mode;
            _AccountNumber = AccountNumber;
            _FullName = Name;
            /*_Loan = Loan;
            _LoanWithInterest = LoanWithInterest;
            _LoanBeginDate = LoanBeginDate;
            _LoanEndDate = LoanEndDate;
            _InterestRate = InterestRate;*/
            _Phone = Phone;
            //_LoanWithInterest = GetCurrentLoan();
            _LoanList.InsertAtBeginning(LoanObject);
        }

        clsLoanClient(enMode mode, string AccountNumber, string Name, string Phone, double Loan, double LoanWithInterest, string LoanBeginDate, string LoanEndDate, clsLoan::enLoanMode clsLoanMode , double InterestRate = 1.14)
        {
            _Mode = mode;
            _AccountNumber = AccountNumber;
            _FullName = Name;
            _Phone = Phone;
            clsLoan LoanObject(clsLoanMode , Loan, LoanBeginDate, LoanEndDate, InterestRate);
            _LoanList.InsertAtBeginning(LoanObject);
            return;
        }

        static clsLoanClient BankClientToLoanClient(clsBankClient BankClient)
        {
            return _ConvertBankClientObjectToLoanClientObject(BankClient);
        }

        struct stLoanLogRecord
        {
            string Date;
            string AccountNumber;
            double InterestRate;
            double Loan;
            string Status; //Took loan or Repaid Loan
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
        
        void SetPhoneNumber(string Phone)
        {
            _Phone = Phone;
        }

        string GetPhoneNumber()
        {
            return _Phone;
        }

        __declspec(property(get = GetPhoneNumber, put = SetPhoneNumber)) string Phone;

        int GetCreditScore()
        {
            return _CreditScore;
        }

        clsDynamicArray <thread> SetAll(string AccountNumber, string FullName, string PhoneNumber)
        {
            clsDynamicArray <thread> DyArTh(3);
            DyArTh.SetItem(0, std::move(thread(&clsLoanClient::SetAccountNumber, this, AccountNumber)));
            DyArTh.SetItem(1, std::move(thread(&clsLoanClient::SetFullName, this, FullName)));
            DyArTh.SetItem(2, std::move(thread(&clsLoanClient::SetPhoneNumber, this, PhoneNumber)));
            for (thread& i : DyArTh)
            {
                i.join();
            }

            return DyArTh;
        }

        clsDynamicArray <thread> SetAll(clsDynamicArray <string> StDyArr)
        {

        }

        clsDynamicArray <thread> SetAll(clsDynamicArray <string> StDyArr, double Loan, double InterestRate)
        {

        }

       /*not done*/ clsDynamicArray <thread> SetAll(string AccountNumber, string FullName, string PhoneNumber ,  string LoanBeginDate, string LoanEndDate, double Loan, double InterestRate)
        {
            clsDynamicArray <thread> DyArTh(3);
            DyArTh.SetItem(0, std::move(thread(&clsLoanClient::SetAccountNumber, this, AccountNumber)));
            DyArTh.SetItem(1, std::move(thread(&clsLoanClient::SetFullName, this, FullName)));
            DyArTh.SetItem(2, std::move(thread(&clsLoanClient::SetPhoneNumber, this, PhoneNumber)));
            /*DyArTh.SetItem(3, std::move(thread(&clsLoanClient::SetLoanEndDate, this, LoanEndDate)));
            DyArTh.SetItem(4, std::move(thread(&clsLoanClient::SetLoan, this, Loan)));
            DyArTh.SetItem(5, std::move(thread(&clsLoanClient::SetInterestRate, this, InterestRate)));*/


            for (thread& i : DyArTh)
            {
                i.join();
            }

            return DyArTh;
        }

        vector <thread> SetAll2(string AccountNumber, string FullName, string PhoneNumber ,string LoanBeginDate, string LoanEndDate, double Loan, double InterestRate)
        {
            vector <thread> VTh;
            VTh.push_back(thread(&clsLoanClient::SetAccountNumber, this, AccountNumber));
            VTh.push_back(thread(&clsLoanClient::SetFullName, this, FullName));
            VTh.push_back(thread(&clsLoanClient::SetPhoneNumber, this, PhoneNumber));
            /*VTh.push_back(thread(&clsLoanClient::SetLoanEndDate, this, LoanEndDate));
            VTh.push_back(thread(&clsLoanClient::SetLoan, this, Loan));
            VTh.push_back(thread(&clsLoanClient::SetInterestRate, this, InterestRate));*/


            for (thread& i : VTh)
            {
                i.join();
            }

            return VTh;
        }

        thread* SetAll3(string AccountNumber, string FullName, string LoanBeginDate, string LoanEndDate, double Loan, double InterestRate , int Size = 0)
        {
            thread* ptrThread = new thread[Size];
        }

        void Print()
        {
            cout << "\nloan Client Card:";
            cout << "\n___________________";
            cout << "\nAccountNumber   : " << AccountNumber;
            cout << "\nFull Name   : " << FullName;
            cout << "\nPhone   :" << Phone;
            /*cout << "\nLoan Begin Date       : " << LoanBeginDate();
            cout << "\nLoan End Date       : " << LoanEndDate();
            cout << "\nBalance     : " << InterestRate << "%";*/
            cout << "\nLoan Info:";
            for (int i = 0; i < _LoanList.Size(); i++)
            {
                cout << "\n\nLoan number (" << i << "):\n\n";
                _LoanList.Getitem(i).print();
                cout << endl;
            }
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
            return clsLoanClient(enMode::AddNewMode, AccountNumber, "" , "" );
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

        void PrintClientLoan()
        {
            _LoanList.PrintList();
        }

        double GetClientTotalLoans()
        {
            double TotalLoans = 0;

            for (int i = 0; i < _LoanList.Size(); i++)
            {
                TotalLoans += _LoanList.Getitem(i).GetLoan();
            }

            return TotalLoans;
        }

        /*not done */static double GetTotalLoans()
        {
            vector <clsLoanClient> vClients = clsLoanClient::GetLoanClientsList();

            double TotalBalances = 0;

            for (clsLoanClient Client : vClients)
            {

                TotalBalances += Client.GetClientTotalLoans();
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


        /*not done*/ /*void ProcessCalculations(vector<clsLoanClient>& clients)
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
         }*/


static vector <clsLoanClient> GetLoansList()
{
    return _LoadLoanClientsDataFromFile();
}

clsLoanClient BTOL(clsBankClient BankClient)
{
    return _ConvertBankClientObjectToLoanClientObject(BankClient);
}

bool TakeNewLoan(double Loan, string LoanBeginDate, string LoanEndDate, double InterestRate)
{
    if (CheckCreditScore())
    {
        _LoanList.Resize(_LoanList.Size() + 1);
        clsLoan LoanObject(Loan, LoanBeginDate, LoanEndDate, InterestRate);
        _LoanList.InsertAtEnd(LoanObject);
        _CreditScore -= 30;
        return true;
    }

    return false;
}

bool RepayPartOfLoan(string ID, double amount)
{
    for (int i = 0; i < _LoanList.Size(); i++)
    {
        if (_LoanList.Getitem(i).ID == ID)
        {
            int num = _LoanList.Getitem(i).Loan;

            _LoanList.Getitem(i).Loan -= amount;

            if (_LoanList.Getitem(i).Loan == 0)
            {
                _LoanList.DeleteItemAt(FindIndexByLoanID(ID));
            }

            else if (_LoanList.Getitem(i).Loan < 0)
            {
                _LoanList.DeleteItemAt(FindIndexByLoanID(ID));
                amount -= num;

                while (amount > 0)
                {
                    i++;
                    if (_LoanList.Getitem(i).Loan > amount)
                    {
                        _LoanList.Getitem(i).Loan -= amount;
                        return true;
                    }

                    if (_LoanList.Getitem(i).Loan == amount)
                    {
                        _LoanList.DeleteItemAt(i);
                        return true;
                    }

                    amount -= _LoanList.Getitem(i).Loan;
                    _LoanList.DeleteItemAt(i);
                }
             }
                    return true;
        }
    }
            return false;
}

        /*not done*/bool RepayFullLoan(string ID)
        {
            if (_RepayFullLoan(ID))
            {
                _CreditScore += 60;
                return true;
            }

            return false;
        }

        bool RepayFullLoan(int index)
        {
            if (_LoanList.DeleteItemAt(index))
            {
                _CreditScore += 60;
                return true;
            }

            return false;
        }

        bool RepayFullLoan()
        {
            int index = 0;

            cin >> index;

            if (_LoanList.DeleteItemAt(index))
            {
                _CreditScore += 60;
                return true;
            }

            return false;
        }

        

        void RepayAllLoans()
        {
            _LoanList.Clear();
        }

        int FindIndexByLoanID(string ID)
        {
            for (int i = 0; i < _LoanList.Size(); i++)
            {
                if (_LoanList.Getitem(i).ID == ID)
                    return i;
            }

            return 0;
        }

        clsLoan FindLoanByLoanID(string ID)
        {
            for (int i = 0; i < _LoanList.Size(); i++)
            {
                if (_LoanList.Getitem(i).ID == ID)
                    return _LoanList.Getitem(i);
            }

            return clsLoan::GetEmptyLoanObject();
        }

        bool IsLoanExist(string ID)
        {
            for (int i = 0; i < _LoanList.Size(); i++)
            {
                if (_LoanList.Getitem(i).ID == ID)
                    return true;
            }

            return false;
        }
};
//loan is not probably handled
//loanClient is not done


