#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

const string ClientsFileName = "New File of Negm.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false ;
    bool MarkForUpdate = false ;
};
vector<string> SplitString(string , string );
sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";
    // Usage of std::ws will extract all the whitespace character
    // cin.ignore(1,'\n');
    getline(cin >> ws, Client.AccountNumber);
    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance; return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}
sClient ConvertLineToRecord(string line)
{
    //cout << "Line record is:\n" << line << endl;
    sClient client ;
    vector <string> Vstring = SplitString(line ,"#//#");
    client.AccountNumber = Vstring[0];
    client.PinCode = Vstring[1];
    client.Name = Vstring[2];
    client.Phone = Vstring[3];
    client.AccountBalance = stod(Vstring[4]);
    return client;
}
sClient ConvertLinetoRecord(string line)
{
    //cout << "Line record is:\n" << line << endl;
    sClient client ;
    vector <string> Vstring = SplitString(line ,"#//#");
    client.AccountNumber = Vstring[0];
    client.PinCode = Vstring[1];
    client.Name = Vstring[2];
    client.Phone = Vstring[3];
    client.AccountBalance = stod(Vstring[4]);
    return client;
}
void displayclient(sClient s)
{
    cout << "The following is the extracted client record:\n\n";
    cout << "Account number" << ": " << s.AccountNumber << endl;
    cout << "Pin Code: " << s.PinCode << endl;
    cout << "Name: " << s.Name << endl;
    cout << "Phone: " << s.Phone << endl;
    cout << "Account balance: " << s.AccountBalance << endl;
}
string readstring();
struct StClientData
{
    string AccountNumber ;
    short Pincode ;
    string Name ;
    string phone ;
    double AccountBalance ;
};
StClientData GetData()
{
    cout << "Please Enter Client data: \n\n";
    StClientData ClientData ;
    cout << "Enter account number? ";
    getline(cin,ClientData.AccountNumber) ;
    cout << "Enter pinCode? ";
    cin >> ClientData.Pincode ;
    cout << "Enter name? ";
    cin.ignore(1,'\n');
    getline(cin,ClientData.Name) ;
    cout << "Enter phone? ";
    getline(cin,ClientData.phone) ;
    cout << "Enter account balance? ";
    cin >> ClientData.AccountBalance;
    return ClientData ;
}
string DisplayClientData (StClientData st , string delim)
{
    string s = "" ;
    s += st.AccountNumber;
    s += delim ;
    s += to_string(st.Pincode) ;
    s += delim ;
    s += st.Name ;
    s += delim ;
    s += st.phone ;
    s += delim ;
    s += to_string(st.AccountBalance);
    return s ;
}
string JoinInReverse(vector <string>  , string );
string *SpiltString0(string , string );
string reverser(string  , string );
string splitstring(string  , string );
string Replace(string , string , string , string);
string to_lower(string );
string to_upper(string );
string Join(vector <string> vString , string delim)
{
    string s1 = "" ;
    for (int i = 0 ; i < vString.size() ; i++)
    {
        if (i == vString.size() - 1)
            s1 += vString[i];
        else
            s1 += vString[i] + delim ;
    }
    return s1;
}
string  LowerAllString(string S1)
{
    for (short i = 0; i < S1.length(); i++)
    {
        S1[i] = tolower(S1[i]);
    } return S1;
}
/*string ReplaceWordInStringUsingSplit(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
{
    vector<string> vString = SplitString(S1, " ");
    for (string& s : vString)
    {
        if (MatchCase)
        {
            if (s == StringToReplace)
            {
                s = sRepalceTo;
            }
        }
        else
        {
            if (LowerAllString(s) == LowerAllString(StringToReplace))
            {
                s = sRepalceTo;
            }
        }
    }
    return JoinString(vString, " ");
}*/
string ReplaceWordInStringUsingBuiltInFunction(string S1, string StringToReplace, string sRepalceTo)
{
    short pos = S1.find(StringToReplace);
    while (pos != std::string::npos)
    {
        S1 = S1.replace(pos, StringToReplace.length(), sRepalceTo);
        pos = S1.find(StringToReplace);//find next
    }
    return S1;
}
string RemoveAllPunction(string s)
{
    string s1 = "";
    for (short i = 0 ; s[i] != NULL ; i++)
    {
        //if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))
            //s1 += s[i];
        if (s[i] == '\'' || s[i] == '|' || s[i] == '~' || s[i] == '$' || s[i] == '=' || s[i] == '+' || s[i] == '&' || s[i] == '#' || s[i] == '%' || s[i] == '>' || s[i] == '<' || s[i] == '`' || s[i] == '^' || s[i] == '\"' || s[i] == ';' || s[i] == ':' || s[i] == '.' || s[i] == '\\' || s[i] == '!' || s[i] == '@' || s[i] == ',' || s[i] == '[' || s[i] == ']' || s[i] == '*' || s[i] == '/' || s[i] == '-' || s[i] == '{' || s[i] == '}'  || s[i] == '?' || s[i] == '_' || s[i] == '(' || s[i] == ')')
            continue ;
        else
            s1 += s[i] ;
    }
    return s1;
}
string RemovePunctuationsFromString(string S1)
{
    string S2 = "";
    for (short i = 0; i < S1.length(); i++)
        {
            if (!ispunct(S1[i]))
            {
                S2 += S1[i];
            }
        }
    return S2;
}
fstream SaveClienttoFile()
{
    fstream newfileofnogmooa ;
    newfileofnogmooa.open("New File of Nogmooa.txt", ios::out | ios::app);
    char d  = NULL ;
    do
    {
        sClient newclient = ReadNewClient();
        string s = ConvertRecordToLine(newclient);
        if (newfileofnogmooa.is_open())
        {
            newfileofnogmooa << s << endl;
        }
        cout << "Client added successfully , do you want to add more clients?";
        cin >> d ;
    }
    while(d == 'y' || d == 'Y');
    newfileofnogmooa.close();
    return newfileofnogmooa;
}
void LoadDataFromFileToString()
{
    fstream FileName ;
    short counter = 0 ;
    FileName.open(ClientsFileName , ios::in);
    if (FileName.is_open())
    {
        sClient client ;
        string line0;
        while (getline(FileName, line0))
        {
            counter++;
        }
        FileName.close();
    }
    FileName.open(ClientsFileName , ios::in);
    if (FileName.is_open())
    {
        sClient client ;
        string line1;
        cout << setw(50) << "Client list (" << counter << ") Client(s).\n\n" << "________________________________________________________________________________________________________________________\n\n";
        cout << "| Account number" << " | Pincode " << " | Client name\t\t\t\t| phone \t\t| Balance \n\n";
        cout << "________________________________________________________________________________________________________________________\n";
        while (getline(FileName, line1))
        {
            client = ConvertLineToRecord(line1);
            cout << "| " << client.AccountNumber << "\t\t |  " << client.PinCode << "    | ";
            cout << setw(20) << client.Name  << " \t\t\t| "<< setw(11) <<client.Phone << "\t\t|" << client.AccountBalance << endl;
        }
        FileName.close();
    }

}
void LoadDataFromFileToVector(string FileName, vector <string>& vFileContent)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    //read Mode
    if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
                {
                    vFileContent.push_back(Line);
                }
            MyFile.close();
        }
}
void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}
void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}
bool isfound(string Accountnumber ,sClient s)
{
    return (Accountnumber == s.AccountNumber);
}
void checkClient(string Accountnumber , vector <sClient> VsClients)
{
    for (short i = 0 ; i < VsClients.size() ; i++)
    {
        if (isfound(Accountnumber,VsClients[i]))
        {
            displayclient(VsClients[i]) ;
            return ;
        }
    }
}
void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}
vector <sClient> DeleteRecordbyAccountnumber(string AccountNumber , vector <sClient> Vclients)
{
    bool found = 0 ;
    vector <sClient> VClient;
    for (short i = 0 ; i < Vclients.size() ; i++)
    {
        if(isfound(AccountNumber , Vclients[i]))
        {
            found = 1 ;
            PrintClientCard(Vclients[i]);
            char f = NULL;
            cout << "Are you sure you want to delete this client ?y/n? ";
            cin >> f ;
            if (toupper(f) != 'Y')
                VClient.push_back(Vclients[i]);
        }
        else
            VClient.push_back(Vclients[i]);
    }
    if(!found)
        cout << "Client with account number (" << AccountNumber << ") not found!";
    return VClient;
}
void AddnewDataLineToFile(string FileName, vector <sClient> Vsclient)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (int i = 0 ; i < Vsclient.size() ; i++)
        {
            AddDataLineToFile(FileName,ConvertRecordToLine(Vsclient[i],"#//#"));
        }
    }
}
void AddClients()
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        cout << "Adding New Client:\n\n";
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;
    }
    while (toupper(AddMore) == 'Y');
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}
void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientsData(vector <sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
bool FindClientByAccountNumber(string AccountNumber , vector <sClient> vClients , sClient & Client )
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                    //we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
            else if (C.MarkForUpdate == true)
            {
                DataLine = ConvertRecordToLine(ReadNewClient());
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> & vClients)
{
    sClient Client;
[O    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients); //Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!";
        return false;
    }
}
bool MarkClientForUpdateByAccountNumber(string AccountNumber , vector <sClient> & s)
{
    for (sClient & c : s)
    {
        if (c.AccountNumber == AccountNumber)
        {
            c.MarkForUpdate = true ;
            return true ;
        }
    }
    return false ;
}
sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient & C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!";
        return false;
    }
}
void UpdateRecord(string AccountNumber , vector <sClient>&VClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, VClients , Client))
    {
        PrintClientCard(Client);
        cout << "Are you sure you want to update this client? y/n ?";
        cin >> Answer ;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForUpdateByAccountNumber(AccountNumber,VClients);
            SaveCleintsDataToFile(ClientsFileName,VClients);
            VClients = LoadCleintsDataFromFile(ClientsFileName);
            cout << "Client updated successfully \n";
        }
    }
}
int main()
{
    //AddClients();
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateRecord(AccountNumber , vClients);
    DeleteClientByAccountNumber(AccountNumber, vClients);
    AddClients();
    //A150#//#1234#//#Mohammed Abu-Hadhoud#//#5000.000000
    vector <sClient> vs1 = LoadCleintsDataFromFile(ClientsFileName);
    string s = ReadClientAccountNumber();
    PrintAllClientsData(vs1);
    vector <sClient> vs2 = DeleteRecordbyAccountnumber(s,vs1);
    AddnewDataLineToFile(ClientsFileName,vs2);
    //checkClient("A150 ",vs1);
    LoadDataFromFileToString();
    //sClient sa = GetData();

    //string s = readstring();
    /*cout << "Original String : \n" << s << endl << endl;
    cout << "String after puction removal:\n";
    cout << RemoveAllPunction(s) << endl;
    cout << "Original String : \n" << s << endl << endl;
    cout << "String after puction removal:\n";
    cout << RemovePunctuationsFromString(s) << endl ;*/
    //cout << "Original String\n" << s << endl << endl;
    //cout << "String after Replace: \n" <<Replace(s," ","Jordan","Egypt") << endl ;
    /*vector <string> VS = SplitString(s," ");
    string ss = JoinInReverse(VS," ");
    cout << "String after reversing words: \n" << ss;*/
    return 0;
}
string Replace(string S1 , string Delim , string Word , string ss)
{
    vector<string> vString;
    short pos = 0;
    string sWord = "" ;
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord == Word || to_upper(sWord) == to_upper(Word) || to_lower(sWord) == to_lower(Word))
            sWord = ss ;
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }
    if (S1 == Word || to_upper(S1) == to_upper(Word) || to_lower(S1) == Word)
        S1 = ss ;
    if (S1!="")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    string s2 = "";
    s2 = Join(vString , Delim);
    return s2;
}
string readstring()
{
    string s = " " ;
    cout << "Enter string: " ;
    getline(cin,s);
    return s ;
}
string JoinInReverse(vector <string> vString , string delim)
{
    string s1 = "" ;
    for (int i = 1 ; i <= vString.size() ; i++)
    {
            s1 += vString[vString.size() - i] + delim ;
    }
    s1 = s1.substr(0,s1.length() - 1);
    return s1;
}
vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord =S1.substr(0, pos); // store the word
        if (sWord !="")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }
    if (S1!="")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}
string ReverseWordsInString(string S1)
{
    vector<string> vString;
    string S2 = "";
    vString = SplitString(S1, " ");
    // declare iterator
    vector<string>::iterator iter = vString.end();
    while (iter != vString.begin())
    {
        --iter;
        S2 += *iter + " ";
    }
    S2 = S2.substr(0, S2.length() - 1);
     //remove last space.
    return S2;
}
string to_lower(string s)
{
    for (int i = 0 ; s[i] != NULL ; i++)
    {
        if (s[i] >= 65 && s[i] <= 90)
            s[i] += 32 ;
    }
    return s;
}
string to_upper(string s)
{
    for (int i = 0 ; s[i] != NULL ; i++)
    {
        if (s[i] >= 97 && s[i] <= 122)
            s[i] -= 32 ;
    }
    return s;
}
/*string *SpiltString(string s , string delim)
{
    string sWord = "" ;
    char minidelim = delim[0];
    short counter = 1 , ii = 0 ;
    for (int i = 0 ; s[i] != NULL ; i++)
    {
        if (s[i] != minidelim && s[i + 1] == minidelim)
            counter++;
    }
    cout << counter << endl;
    string *ptr ;
    ptr = new string [counter];
    for (int i = 0 ; s[i] != NULL ; i++)
    {
        if (s[i] != minidelim)
            sWord += s[i] ;
        if (s[i] != minidelim && s[i + 1] == minidelim)
        {
            ptr[ii] = sWord ;
            sWord = "" ;
            ii++;
        }
    }
    if (sWord != "")
        ptr[ii] = sWord;
    for (int i = 0 ; i < counter ; i++)
        cout << ptr[i] << endl;
    return ptr[counter];
}
*/


