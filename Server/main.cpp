#include <ws2tcpip.h>
#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <string.h>
#include <ctype.h>

using namespace std;

SOCKET Connect;
SOCKET* Connections;
SOCKET Listen;
char key[1024] = "key";
char accden[1024] = "access denied, push enter to continue\n";
int ClientCount = 0;

class SHA512
{
protected:
    typedef unsigned char uint8;
    typedef unsigned int uint32;
    typedef unsigned long long uint64;

    const static uint64 sha512_k[];
    static const unsigned int SHA384_512_BLOCK_SIZE = (1024/8);

public:
    void init();
    void update(const unsigned char *message, unsigned int len);
    void final(unsigned char *digest);
    static const unsigned int DIGEST_SIZE = ( 512 / 8);

protected:
    void transform(const unsigned char *message, unsigned int block_nb);
    unsigned int m_tot_len;
    unsigned int m_len;
    unsigned char m_block[2 * SHA384_512_BLOCK_SIZE];
    uint64 m_h[8];
};


std::string sha512(std::string input);

#define SHA2_SHFR(x, n)    (x >> n)
#define SHA2_ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define SHA2_ROTL(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
#define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA512_F1(x) (SHA2_ROTR(x, 28) ^ SHA2_ROTR(x, 34) ^ SHA2_ROTR(x, 39))
#define SHA512_F2(x) (SHA2_ROTR(x, 14) ^ SHA2_ROTR(x, 18) ^ SHA2_ROTR(x, 41))
#define SHA512_F3(x) (SHA2_ROTR(x,  1) ^ SHA2_ROTR(x,  8) ^ SHA2_SHFR(x,  7))
#define SHA512_F4(x) (SHA2_ROTR(x, 19) ^ SHA2_ROTR(x, 61) ^ SHA2_SHFR(x,  6))
#define SHA2_UNPACK32(x, str)                 \
{                                             \
    *((str) + 3) = (uint8) ((x)      );       \
    *((str) + 2) = (uint8) ((x) >>  8);       \
    *((str) + 1) = (uint8) ((x) >> 16);       \
    *((str) + 0) = (uint8) ((x) >> 24);       \
    }
#define SHA2_UNPACK64(x, str)                 \
{                                             \
    *((str) + 7) = (uint8) ((x)      );       \
    *((str) + 6) = (uint8) ((x) >>  8);       \
    *((str) + 5) = (uint8) ((x) >> 16);       \
    *((str) + 4) = (uint8) ((x) >> 24);       \
    *((str) + 3) = (uint8) ((x) >> 32);       \
    *((str) + 2) = (uint8) ((x) >> 40);       \
    *((str) + 1) = (uint8) ((x) >> 48);       \
    *((str) + 0) = (uint8) ((x) >> 56);       \
    }
#define SHA2_PACK64(str, x)                   \
{                                             \
    *(x) =   ((uint64) *((str) + 7)      )    \
    | ((uint64) *((str) + 6) <<  8)    \
    | ((uint64) *((str) + 5) << 16)    \
    | ((uint64) *((str) + 4) << 24)    \
    | ((uint64) *((str) + 3) << 32)    \
    | ((uint64) *((str) + 2) << 40)    \
    | ((uint64) *((str) + 1) << 48)    \
    | ((uint64) *((str) + 0) << 56);   \
    }


const unsigned long long SHA512::sha512_k[80] = //ULL = uint64
{0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL,
        0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
        0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL,
        0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
        0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
        0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
        0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL,
        0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
        0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL,
        0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
        0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL,
        0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
        0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL,
        0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
        0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
        0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
        0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL,
        0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
        0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL,
        0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
        0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL,
        0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
        0xd192e819d6ef5218ULL, 0xd69906245565a910ULL,
        0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
        0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
        0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
        0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL,
        0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
        0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL,
        0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
        0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL,
        0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
        0xca273eceea26619cULL, 0xd186b8c721c0c207ULL,
        0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
        0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
        0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
        0x28db77f523047d84ULL, 0x32caab7b40c72493ULL,
        0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
        0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL,
        0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL};

void SHA512::transform(const unsigned char *message, unsigned int block_nb)
{
    uint64 w[80];
    uint64 wv[8];
    uint64 t1, t2;
    const unsigned char *sub_block;
    int i, j;
    for (i = 0; i < (int) block_nb; i++) {
        sub_block = message + (i << 7);
        for (j = 0; j < 16; j++) {
            SHA2_PACK64(&sub_block[j << 3], &w[j]);
        }
        for (j = 16; j < 80; j++) {
            w[j] =  SHA512_F4(w[j -  2]) + w[j -  7] + SHA512_F3(w[j - 15]) + w[j - 16];
        }
        for (j = 0; j < 8; j++) {
            wv[j] = m_h[j];
        }
        for (j = 0; j < 80; j++) {
            t1 = wv[7] + SHA512_F2(wv[4]) + SHA2_CH(wv[4], wv[5], wv[6])
                    + sha512_k[j] + w[j];
            t2 = SHA512_F1(wv[0]) + SHA2_MAJ(wv[0], wv[1], wv[2]);
            wv[7] = wv[6];
            wv[6] = wv[5];
            wv[5] = wv[4];
            wv[4] = wv[3] + t1;
            wv[3] = wv[2];
            wv[2] = wv[1];
            wv[1] = wv[0];
            wv[0] = t1 + t2;
        }
        for (j = 0; j < 8; j++) {
            m_h[j] += wv[j];
        }

    }
}

void SHA512::init()
{
    m_h[0] = 0x6a09e667f3bcc908ULL;
    m_h[1] = 0xbb67ae8584caa73bULL;
    m_h[2] = 0x3c6ef372fe94f82bULL;
    m_h[3] = 0xa54ff53a5f1d36f1ULL;
    m_h[4] = 0x510e527fade682d1ULL;
    m_h[5] = 0x9b05688c2b3e6c1fULL;
    m_h[6] = 0x1f83d9abfb41bd6bULL;
    m_h[7] = 0x5be0cd19137e2179ULL;
    m_len = 0;
    m_tot_len = 0;
}

void SHA512::update(const unsigned char *message, unsigned int len)
{
    unsigned int block_nb;
    unsigned int new_len, rem_len, tmp_len;
    const unsigned char *shifted_message;
    tmp_len = SHA384_512_BLOCK_SIZE - m_len;
    rem_len = len < tmp_len ? len : tmp_len;
    memcpy(&m_block[m_len], message, rem_len);
    if (m_len + len < SHA384_512_BLOCK_SIZE) {
        m_len += len;
        return;
    }
    new_len = len - rem_len;
    block_nb = new_len / SHA384_512_BLOCK_SIZE;
    shifted_message = message + rem_len;
    transform(m_block, 1);
    transform(shifted_message, block_nb);
    rem_len = new_len % SHA384_512_BLOCK_SIZE;
    memcpy(m_block, &shifted_message[block_nb << 7], rem_len);
    m_len = rem_len;
    m_tot_len += (block_nb + 1) << 7;
}

void SHA512::final(unsigned char *digest)
{
    unsigned int block_nb;
    unsigned int pm_len;
    unsigned int len_b;
    int i;
    block_nb = 1 + ((SHA384_512_BLOCK_SIZE - 17)
                    < (m_len % SHA384_512_BLOCK_SIZE));
    len_b = (m_tot_len + m_len) << 3;
    pm_len = block_nb << 7;
    memset(m_block + m_len, 0, pm_len - m_len);
    m_block[m_len] = 0x80;
    SHA2_UNPACK32(len_b, m_block + pm_len - 4);
    transform(m_block, block_nb);
    for (i = 0 ; i < 8; i++) {
        SHA2_UNPACK64(m_h[i], &digest[i << 3]);
    }
}

std::string sha512(std::string input)
{
    unsigned char digest[SHA512::DIGEST_SIZE];
    memset(digest,0,SHA512::DIGEST_SIZE);
    SHA512 ctx = SHA512();
    ctx.init();
    ctx.update((unsigned char*)input.c_str(), input.length());
    ctx.final(digest);

    char buf[2*SHA512::DIGEST_SIZE+1];
    buf[2*SHA512::DIGEST_SIZE] = 0;
    for (unsigned int i = 0; i < SHA512::DIGEST_SIZE; i++)
        sprintf(buf+i*2, "%02x", digest[i]);
    return std::string(buf);
}


void reguser()
{
    for(;;Sleep(750)){
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
        }
        if(flagExist == 0){
            ofstream hashWrite("pwd.txt", ios_base::app);
            hashWrite << summHash << '\n';
            hashWrite.close();
            cout << "User data updated:" << endl << "Login: " << login << endl << "Password: " << password << endl << "Hash: " << summHash << endl;
        }
    }
}


void shifr (char *res, char *key)
{
    int reslen = 0, keylen = 0, keydigit = 0, trashlen = 0, itoglen = 0;
    char trash[100000]="", itog[100000]="";
    while(res[reslen]) reslen++;
    for(int i = 0; i <= (reslen*2); i++){
        trash[i] = rand() % 127;
        if(isalnum(trash[i]) == 0) {
            trash[i] = 63;
        }
        i++;
        trash[i] = rand() % 127;
        if(isalnum(trash[i]) == 0) {
            trash[i] = 63;
        }
    }
    trashlen = 0;
    while(trash[trashlen]) trashlen++;
    for(int i = 0, a = 0, j = 0; a < reslen; ){
        itog[i++] = trash[j++];
        itog[i++] = trash[j++];
        itog[i++] = res[a++];
    }
    while(itog[itoglen]) itoglen++;
    for(int i = 0; i < reslen; i++) res[i] = 0;
    for(int i = 0; i < itoglen; i++) res[i] = itog[i];
    while(key[keylen]) keylen++;
    reslen = 0;
    while(res[reslen]) reslen++;
    keydigit = reslen % 4;
    for (int i = 0; i < reslen;){
        for (int a = 0; a < keylen;a++){
            if(i<reslen){
                res[i] = res[i]+key[a]+keydigit;
                i++;
            }
            else{
                break;
            }
        }
    }
}

void deshifr (char *res, char *key)
{
    int reslen = 0, keylen = 0, keydigit = 0, itoglen = 0;
    char itog[100000]="";
    while(res[reslen]) reslen++;
    keydigit = reslen % 4;
    while(key[keylen]) keylen++;
    for (int i = 0; i < reslen;){
        for (int a = 0; a < keylen;a++){
            if(i<reslen){
                res[i] = res[i]-key[a]-keydigit;
                i++;
            }
            else{
                break;
            }
        }
    }
    for(int i = 0, a = 2; i < reslen; i++){
        itog[i] = res[a];
        a += 3;
    }
    while(itog[itoglen]) itoglen++;
    for(int i = 0; i < reslen; i++) res[i] = 0;
    for(int i = 0; i < itoglen; i++) res[i] = itog[i];
}

int valid(char *name, char *pwd)
{
    string strName = string(name);
    string strPwd = string(pwd);
    std::string needString =  strName + strPwd;
    std::string string;
    bool isHave = 0;
    std::ifstream ifstream1("pwd.txt");
    while( std::getline( ifstream1, string ) )
        if( string == needString ){
            isHave = 1;
            break;
        }
    ifstream1.close();
    return isHave;
}

void parce(char (&buffer)[50000], char (&name)[1024], char (&pwd)[1024], char (&text)[50000], char (&res)[50000])
{
    int g = 0, c = 0, namelen = 0, textlen = 0, count = 0;
    if(buffer[0]!='\0'){
        while(buffer[g] != '\n') name[c++] = buffer[g++];
        name[c]='\0';
        g++;
        c=0;
        while(buffer[g] != '\n')pwd[c++] = buffer[g++];
        pwd[c]='\0';
        g++;
        c=0;
        while(buffer[g])text[c++] = buffer[g++];
        text[c]='\0';
        while(name[namelen]) namelen++;
        while(text[textlen]) textlen++;
        for(int i = 0; i < namelen; i++, count++) res[count] = name[count];
        res[count++] = ':';
        for(int i = 0; i < textlen; i++, count++) res[count] = text[i];
    }
}


void SendMessageToClient(int ID)
{
    for ( ; ; Sleep(750))
    {
        ofstream logs("logs.txt", ios_base::app);
        logs.close();
        char buffer[50000] = "";
        for (int clear666 = 0; buffer[clear666] != 0; clear666++) buffer[clear666] = '\0';
        if (recv(Connections[ID], buffer, sizeof(buffer), 0)){
            char buff[1024] = "";
            char res[50000] = "";
            char pwd[1024] = "";
            char name[1024] = "";
            char text[50000] = "";
            deshifr(buffer,key);
            parce(buffer, name, pwd, text, res);
            if(valid(name,pwd) == 0){
                logs.open("logs.txt", ios_base::app);
                logs << "client id: " << ID << "<- NO VALID!!!\n";
                logs.close();
                //printf("client id %d: <- NO VALID!!!\n", ID);
                shifr(accden,key);
                send(Connections[ID],accden, sizeof(accden), 0);
                deshifr(accden,key);
                shutdown(Connections[ID],2);
                while(recv(Connections[ID], buff, sizeof(buff), 0)!=-1);
                closesocket(Connections[ID]);
                //ClientCount--;
                break;
            }
            else if(res[0] != '\0'){
                logs.open("logs.txt", ios_base::app);
                logs << "client id: " << ID << ":" << res;
                logs.close();
//                printf("client id %d: ", ID);
//                printf("client id %d: \n", ClientCount);
//                printf("%s",res);
                for (int i = 0; i < ClientCount; i++) //Отправка каждому подключенному клиенту
                {
                    if (i!=ID){
                        shifr(res,key);
                        send(Connections[i], res, sizeof(res), 0);
                        deshifr(res,key);
                    }
                    else {
                    }
                }
                for (int clear666 = 0; res[clear666] != 0; clear666++) res[clear666] = '\0';
            }
            else {
                logs.open("logs.txt", ios_base::app);
                logs << "client id: " << ID << " <- DISCONNECT!\n";
                logs.close();
                //printf("client id %d: <- DISCONNECT!\n", ID);
                shifr(accden,key);
                send(Connections[ID],accden, sizeof(accden), 0);
                deshifr(accden,key);
                shutdown(Connections[ID],2);
                while(recv(Connections[ID], buff, sizeof(buff), 0)!=-1);
                closesocket(Connections[ID]);
                //ClientCount--;
                break;
            }
            for (int clear666 = 0; buff[clear666] != 0; clear666++) buff[clear666] = '\0';
            for (int clear666 = 0; name[clear666] != 0; clear666++) name[clear666] = '\0';
            for (int clear666 = 0; text[clear666] != 0; clear666++) text[clear666] = '\0';
            for (int clear666 = 0; res[clear666] != 0; clear666++) res[clear666] = '\0';
            for (int clear666 = 0; pwd[clear666] != 0; clear666++) pwd[clear666] = '\0';
        }
        else {
            char buff[1024] = "";
            for (int clear666 = 0; buff[clear666] != 0; clear666++) buff[clear666] = '\0';
            shutdown(Connections[ID],2);
            while(recv(Connections[ID], buff, sizeof(buff), 0)!=-1);
            closesocket(Connections[ID]);
            break;
        }
        for (int clear666 = 0; buffer[clear666] != 0; clear666++) buffer[clear666] = '\0';
    }
}

int main()
{
    ofstream logs("logs.txt", ios_base::app);
    logs.close();
    FILE* pwd = fopen("pwd.txt", "r");
    if (!pwd) {
        printf("File pwd.txt does not exist. Check paths.\n");
    }
    else {
        printf("Pwd file ok... ");
    }
    fclose(pwd);
    setlocale(LC_ALL, "russian");
    WSAData data;
    WORD version = MAKEWORD(2,2);
    int res = WSAStartup(version,&data);
    if(res!=0)  {
        return 0;
    }
    struct addrinfo hints;
    struct addrinfo * result;
    Connections = (SOCKET*)calloc(64,sizeof(SOCKET));
    ZeroMemory(&hints,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    getaddrinfo(NULL,"7770", &hints,&result);
    Listen = socket(result->ai_family, result->ai_socktype,result->ai_protocol);
    bind(Listen,result->ai_addr,result->ai_addrlen);
    listen(Listen,SOMAXCONN);
    freeaddrinfo(result);
    printf("Start server...\n");
    char m_connect[] = "online\n\n";
    shifr(m_connect,key);
    CreateThread(0,0,(LPTHREAD_START_ROUTINE)reguser,0,0,0);
    for(;;Sleep(75)) {
        if((Connect = accept(Listen,0,0)) != SOCKET_ERROR) {
            logs.open("logs.txt", ios_base::app);
            logs << "Client id: " << ClientCount << "connect...\n";
            logs.close();
//          printf("Client id:%d connect...\n", ClientCount);
            Connections[ClientCount] = Connect;
            send(Connections[ClientCount],m_connect,strlen(m_connect),0);
            ClientCount++;
            CreateThread(0,0,(LPTHREAD_START_ROUTINE)SendMessageToClient,(LPVOID)(ClientCount-1),0,0);
        }
    }
    return 1;
}
