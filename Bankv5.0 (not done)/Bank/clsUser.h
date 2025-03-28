#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsUser : public clsPerson
{
private:

    //static int x;
    //static int y;
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
 
    bool _MarkedForDelete = false;

    static string EncryptText(string Password, short EncryptionKey)
    {
        for (int i = 0; i <= Password.length(); i++)
        {
            Password[i] = char((int)Password[i] + EncryptionKey);
        }
        return Password;
    }

    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += UserName + Seperator;
        LoginRecord += EncryptText(Password,10) + Seperator;
        LoginRecord += to_string(Permissions);
        return LoginRecord;
    }
    
    static string DecryptText(string Password ,short EncryptionKey)
    {
        for (int i = 0; i <= Password.length(); i++)
        {
            Password[i] = char((int)Password[i] - EncryptionKey);
        }
        return Password;
    }
   /*
   static string Encrypt(string password)
    {
        y++;
        for (int i = 0; password[i] != NULL; i++)
        {
            password[i] = char((int)password[i] + x);
        }
        x = (x * 2) + 1;
        return password;
    }

    static string Decrypt(string password)
    {
        int z = x;

        for (int i = 0; i < y; i++)
        {
            z = (z - 1) / 2;
            for (int j = 0; password[j] != NULL; j++)
                password[j] = char((int)password[j] - z);
        }
        cout << x << endl;
        x = (x - 1) / 2;
        y--;
        return password;
    }
    */
    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], DecryptText(vUserData[5],10) ,stoi(vUserData[6]));

    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        //cout << User.EncryptText(User._Password, 10);
        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += EncryptText(User._Password,10) + Seperator;
        UserRecord += to_string(User.Permissions);
        cout << UserRecord;
        
        return UserRecord;

    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    
    /*NOT DONE*/ union Login
    {
        char* _Password;
        char* _Token;
        double _PinCode;

        void _RequestToken(string UserName , int uses = 1)
        {
            clsUser User1 = clsUser::Find(UserName);
            //Part ot the Token will be generated by the current date it got requested
            string Token = clsDate::GetSystemDateTimeString() + User1.UserName[0] + User1.Password[1] + User1.UserName[3] + User1.Password[2];
            
            fstream MyFile;
            MyFile.open("Token.txt", ios::out | ios::app);

            if (MyFile.is_open())
            {
                //string Line = _Token + "#//#" + User1.UserName + "#//#" + to_string(uses);
                string Line = Token + "#//#" + User1.UserName + "#//#" + to_string(uses);

                MyFile << Line;

                MyFile.close();

            }

            return;
        }

        void _RequestPinCode()
        {
            clsDate Date;

            _PinCode = Date.GetYear() * Date.GetMonth() / Date.GetDay();

            return;
        }
    };

public:

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64,
        pLoginRegister = 128 , pRequestToken = 256
    };

    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

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
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
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

    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions == enPermissions::eAll)
            return true;
        if ((Permission & this->Permissions) == Permission)
            return true;
        else
            return false;

    }

    void RegisterLogIn()
    {

        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static struct stLoginRegisterRecord
    {
        string Date;
        string UserName;
        string Password;
        short permission;
    };

    static stLoginRegisterRecord _ConvertLinetoLoginRegisterStructure(string Line,string Seperator = "#//#")
    {
        stLoginRegisterRecord LRR;
        vector <string> LRRData =  clsString::Split(Line, Seperator);
        LRR.Date = LRRData[0];
        LRR.Password = DecryptText(LRRData[2],10);
        LRR.permission = stoi(LRRData[3]);
        LRR.UserName = LRRData[1];
        return LRR;
    }

    static vector <stLoginRegisterRecord> GetLoginRegisterList()
    {
        vector <stLoginRegisterRecord> LRRS;
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);
        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                stLoginRegisterRecord LRR = _ConvertLinetoLoginRegisterStructure(Line);
                LRRS.push_back(LRR);
            }

            MyFile.close();

         }

        return LRRS;
        
    }
    /*
    * void RegisterLogIn()
    {

        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

     static  vector <stLoginRegisterRecord> GetLoginRegisterList()
     {
         vector <stLoginRegisterRecord> vLoginRegisterRecord;

         fstream MyFile;
         MyFile.open("LoginRegister.txt", ios::in);//read Mode

         if (MyFile.is_open())
         {

             string Line;

             stLoginRegisterRecord LoginRegisterRecord;

             while (getline(MyFile, Line))
             {

                 LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

                 vLoginRegisterRecord.push_back(LoginRegisterRecord);

             }

             MyFile.close();

         }

         return vLoginRegisterRecord;

     }
     struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;

    };


};




    */

    void RequestToken(string UserName)
    {
        int Uses = 0;
        cout << "\n\nHow Many times will this token be valid?";
        cin >> Uses;
        Login Log1;
        Log1._RequestPinCode();
    }
};
//int clsUser::x = 1;
//int clsUser::y = 0;

