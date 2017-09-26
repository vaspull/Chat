#include <iostream>
#include <string.h>
#include <sha512.h>
#include <fstream>
using namespace std;

int main()
{
    unsigned int count = 0;
    int flagExist = 0;
    char i[10] = "", login[1024] = "", password[1024] = "", summ[1024] = "";
    string findeExistUser, tempwrite, temprewrite, summHash;
    cout << "RegUser programm for Chat-server v0.1.... ";
    FILE* pwd = fopen("pwd.txt", "r");
    if (!pwd) {
        cout << "File pwd.txt does not exist. I'm creating a new file ...\n\n";
    }
    else cout << "Pwd file ok... \n\n";
    cout << "Create new user" << endl;
    cout << "Login:";
    fgets(login, sizeof(login), stdin);
    cout << "Password:";
    fgets(password, sizeof(password), stdin);
    login[strlen(login)-1] = '\0';
    password[strlen(password)-1] = '\0';
    for(; count < strlen(login); count++) summ[count] = login[count];
    for(unsigned int i = 0; i < strlen(password); i++, count++) summ[count] = password[i];
    summHash = sha512(string(summ));
    ifstream summHashChek("pwd.txt", ios_base::out);
    while( getline(summHashChek, findeExistUser) ){
        if( findeExistUser == summHash ){
            cout << "The user " << login <<" is already created, enter 'y' if you want to change his data." << endl;
            fgets(i,sizeof(i),stdin);
            flagExist = 1;
            break;
        }
    }
    summHashChek.close();
    if ((strcmp(i,"y\n") == 0) || (strcmp(i,"Y\n") == 0)){
        summHashChek.open("pwd.txt", ios::in);
        ofstream hashWriteTemp("pwdtemp.txt", ios_base::trunc);
        while( getline(summHashChek, tempwrite) ){
            if ( tempwrite != summHash){
            hashWriteTemp << tempwrite << '\n'; }
        }
        hashWriteTemp.close();
        summHashChek.close();
        ifstream hashWriteTemp2("pwdtemp.txt", ios_base::in);
        ofstream hashWrite("pwd.txt", ios_base::trunc);
        while( getline(hashWriteTemp2, temprewrite) ){
            hashWrite << temprewrite << '\n';
        }
        for(unsigned int a = 0; a < strlen(login); a++) login[a] = '\0';
        for(unsigned int a = 0; a < strlen(password); a++) password[a] = '\0';
        for(unsigned int a = 0; a < strlen(summ); a++) summ[a] = '\0';
        cout << "Login:";
        fgets(login, sizeof(login), stdin);
        cout << "Password:";
        fgets(password, sizeof(password), stdin);
        login[strlen(login)-1] = '\0';
        password[strlen(password)-1] = '\0';
        for(; count < strlen(login); count++) summ[count] = login[count];
        for(unsigned int i = 0; i < strlen(password); i++, count++) summ[count] = password[i];
        count = 0;
        summHash = sha512(string(summ));
        hashWrite << summHash << '\n';
        hashWrite.close();
        hashWriteTemp2.close();
        cout << "User data updated:" << endl << "Login: " << login << endl << "Password: " << password << endl << "Hash: " << summHash << endl;
        return 0;
    }
    if(flagExist == 0){
        ofstream hashWrite("pwd.txt", ios_base::app);
        hashWrite << summHash << '\n';
        hashWrite.close();
        cout << "User data updated:" << endl << "Login: " << login << endl << "Password: " << password << endl << "Hash: " << summHash << endl;
    }
    return 0;
}
