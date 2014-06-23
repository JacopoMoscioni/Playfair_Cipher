/*
    Jacopo Moscioni 27-28/03/2009
    Programma che simula il cifrario playfair
*/

#include <iostream>
using namespace std;
const int x=5,y=5;
char matrice[x][y];

//questa funzione sostituisce con una i tutte le j che trova
string sostituiscij(string stringa){
    for (int i=0;i<stringa.length();i++){
        if (stringa[i]=='j')
            stringa[i]='i';
    }

    return stringa;
}

//questa funzione filtra la chiave togliendo le ripetizioni delle lettere
string filtrachiave(string key){
    int m=key.length();
    char vettore[m];
    for(int i=0;i<m;i++)
        vettore[i]=' ';

    int inc=-1;
    for (int i=0;i<m;i++){
        for (int j=0;j<m;j++){
            if (key[i]==vettore[j])
                break;
            else
            if (j>inc){
                inc++;
                vettore[inc]=key[i];
                break;
            }
        }
    }
    string chiave="";
    for(int i=0;i<m;i++)
        chiave=chiave+vettore[i];

    return chiave;
}

//questa funzione aggiunge il resto dell'alfabeto alla chiave, per poi essere messa nella matrice
string aggiungealfabeto(string key){
    string alfabeto="abcdefghiklmnopqrstuvwxyz";
    key=key+alfabeto;

    return filtrachiave(key);
}

//questa funzione modifica il messaggio da cifrare separando le doppie
string filtramessaggio(string messaggio){
    string mex="";
    int l=messaggio.length();
    for(int i=1;i<l;i++){
        if (i>1)
            messaggio=mex;
        if (messaggio[i-1]==messaggio[i])
            mex=messaggio.substr(0,i)+"x"+messaggio.substr(i);
        else
            mex=messaggio;
    }
    //ora se il messaggio è di lunghezza dispari, bisogna agigungere una x alla fine
    if (mex.length() % 2 != 0)
        mex=mex+"x";

    return mex;
}

//questa funzione trova le coordinate di dove sono le coppie di lettere all'interno della matrice
string identificazione(char prima,char seconda,bool codifica){
    int px,py,sx,sy=sx=py=px=-1;
    for(int i=0; i<x;i++){
        for(int j=0;j<x;j++){
            if (prima==matrice[i][j]){
                px=i;
                py=j;
            }
            if (seconda==matrice[i][j]){
                sx=i;
                sy=j;
            }
        }
    }
    string lettera1,lettera2;
    if (codifica==true){//se si sta codificando un messaggio
        if (px==sx){
            py==4?lettera1=matrice[px][0]:lettera1=matrice[px][py+1];
            sy==4?lettera2=matrice[sx][0]:lettera2=matrice[sx][sy+1];
        }
        else
        if (py==sy){
            px==4?lettera1=matrice[0][py]:lettera1=matrice[px+1][py];
            sx==4?lettera2=matrice[0][sy]:lettera2=matrice[sx+1][sy];
        }
        else
        if (px!=sx &&py!=sy){
            lettera1=matrice[px][sy];
            lettera2=matrice[sx][py];
        }
    }
    else{//se si sta decodificando un messaggio
        if (px==sx){
            py==0?lettera1=matrice[px][4]:lettera1=matrice[px][py-1];
            sy==0?lettera2=matrice[sx][4]:lettera2=matrice[sx][sy-1];
        }
        else
        if (py==sy){
            px==0?lettera1=matrice[4][py]:lettera1=matrice[px-1][py];
            sx==0?lettera2=matrice[4][sy]:lettera2=matrice[sx-1][sy];
        }
        else
        if (px!=sx &&py!=sy){
            lettera1=matrice[px][sy];
            lettera2=matrice[sx][py];
        }
    }

    return lettera1+lettera2;
}

//questa funzione toglie le lettere separatrici e restituisce la parola in chiaro
string ricomponimessaggio(string messaggio){
    int l=messaggio.length();
    for (int i=1;i<l;i++)
        if (messaggio[i]=='x')
            if (messaggio[i-1]==messaggio[i+1])
                messaggio=messaggio.substr(0,i)+messaggio.substr(i+1);

    return messaggio;
}

int main(){
    string chiave,k;
    cout<<"Inserisci la chiave del cifrario\nPer una corretta cifratura, immettere solo caratteri alfabetici\n";
    getline(cin,chiave);
    for(int i=0;i<chiave.length();i++)
        chiave[i]=tolower(chiave[i]);
    chiave=sostituiscij(chiave);
    k=filtrachiave(chiave);
    cout<<"----------------------------------\nchiave filtrata:\n\n"
        <<k<<"\n\n---------------------\n";
    k=aggiungealfabeto(k);
    int inc=-1;
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++){
            inc++;
            matrice[i][j]=k[inc];
        }
    cout<<"Matrice generata:"<<endl<<endl;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++)
            cout<<matrice[i][j]<<" ";
        cout<<endl;
    }
    cout<<"\n----------------------------------\n";
    string risp,messaggio;
    do{
        cout<<"Digita 1 se vuoi cifrare un messaggio\nDigita 2 se vuoi decifrare un messaggio\nDigita 3 per uscire\n";
        cin>>risp;
        if (risp=="1"){
            cout<<"Ora inserisci il messaggio da codificare.\nPer una corretta cifratura, immettere solo caratteri alfabetici(spazi esclusi)\n";
            cin>>messaggio;
            for(int i=0;i<messaggio.length();i++)
                messaggio[i]=tolower(messaggio[i]);
            messaggio=sostituiscij(messaggio);
            string m=filtramessaggio(messaggio), parola="";
            for(int i=1;i<m.length();i+=2)
                parola=parola+identificazione(m[i-1],m[i],true);
            cout<<"\n----------------------------------\nMessaggio codificato:\n\n"
                <<parola<<"\n----------------------------------\n";
        }
        else
        if (risp=="2"){
                string m;
                cout<<"Ora inserisci il messaggio da decodificare.\nPer una corretta cifratura, immettere solo caratteri alfabetici(spazi esclusi)\n";
                cin>>m;
                for(int i=0;i<m.length();i++)
                    m[i]=tolower(m[i]);
                m=sostituiscij(m);
                string parola="";
                for(int i=1;i<m.length();i+=2){
                    parola=parola+identificazione(m[i-1],m[i],false);
            }
            cout<<"\n----------------------------------\nMessaggio decodificato:\n\n"
                <<ricomponimessaggio(parola)<<"\n----------------------------------\n";
        }
        else
        if (risp=="3"){
            cout<<"By The Anonymous";
            exit(0);
        }
    }
    while(risp!="1" && risp!="2" && risp!="3");
    return 0;
}
