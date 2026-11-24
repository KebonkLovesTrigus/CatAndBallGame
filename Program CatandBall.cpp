#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void createMap(vector<vector<char>> &map, int baris, int kolom){
    int jumw = kolom;
    int jumb = baris;
    while(jumw>0){
        int b = rand() % baris;
        int k = rand() % kolom;
        if(map[b][k]=='C'){
            map[b][k]='W';
            jumw--;
        }
    }
    while(jumb>0){
        int b = rand() % baris;
        int k = rand() % kolom;
        if(map[b][k]=='C'){
            map[b][k]='B';
            jumb--;
        }
    }
}

void displaymap(vector<vector<char>> &map, int baris, int kolom){
    for(int i=0; i<baris; i++){
        for(int j=0; j<kolom; j++){
            cout<<map[i][j]<<" ";
        }cout<<endl;
    }
}

char hitungw(vector<vector<char>> &map, int baris, int kolom, int b, int k){
    int total = 0;
    for(int i=-1; i<=1; i++){
        for(int j=-1; j<=1; j++){
            if(i==0 && j==0) continue;
            if(b+i >= 0 && b+i < baris && k+j >=0 && k+j < kolom){
                if(map[b+i][k+j]=='W') total++;
            }
        }
    }return total+'0';
}

void areustupid(vector<vector<char>> &map, vector<vector<char>> &mapguess, int baris, int kolom, int &nyawa, int &jumw){
    while(nyawa>0 && jumw<kolom){
        displaymap(mapguess, baris, kolom);
        int b, k;
        do{
            cout<<"Guess the position(row *space* column): ";cin>>b>>k;
        }while(b<0 || k<0 || b>(baris-1) || k>(kolom-1) );
        if(map[b][k]=='W' && mapguess[b][k]=='?'){
            jumw++;
            cout<<"-----------------------------------------------"<<endl;
            cout<<"-----------------------------------------------"<<endl;
            cout<<"Yum! You found a Whiskas"<<endl;
            cout<<"Lives remaining: "<<nyawa<<" Total Whiskas found: "<<jumw<<endl;
            mapguess[b][k]='W';
        }else if(map[b][k]=='C' && mapguess[b][k]=='?'){
            nyawa--;
            cout<<"-----------------------------------------------"<<endl;
            cout<<"-----------------------------------------------"<<endl;
            cout<<"Oops you guessed wrong"<<endl;
            cout<<"Lives remaining: "<<nyawa<<" Total Whiskas found: "<<jumw<<endl;
            cout<<"Whiskas adjacent to your wrongly guessed spot: "<<hitungw(map, baris, kolom, b, k)<<endl;
            mapguess[b][k]=hitungw(map, baris, kolom, b, k);
        }else if(map[b][k]=='B' && mapguess[b][k]=='?'){
            nyawa++;
            cout<<"-----------------------------------------------"<<endl;
            cout<<"-----------------------------------------------"<<endl;
            cout<<"You found an extra life!"<<endl;
            cout<<"Lives remaining: "<<nyawa<<" Total Whiskas found: "<<jumw<<endl;
            mapguess[b][k]='B';
        }else{
            cout<<"-----------------------------------------------"<<endl;
            cout<<"-----------------------------------------------"<<endl;
            cout<<"You already guessed this position."<<endl;
            cout<<"Lives remaining: "<<nyawa<<" Total Whiskas found: "<<jumw<<endl;
        }
    }
}

int main(){
    cout<<"==========================================================================================="<<endl;
    cout<<"   Welcome to the cat and ball game. The goal of the game is to find Whiskas(cat food).    "<<endl;
    cout<<"  The game is played by guessing the position of the target in a NxN area. You can decide  "<<endl;
    cout<<" how wide the map is at the start. If you guess wrongly, a number will appear showing you  "<<endl;
    cout<<"how many Whiskas are around the area you guessed wrongly. You can also obtain an extra life"<<endl;
    cout<<"     if you are lucky. Extra lives are labelled B(ball) and whiskas is W. Good luck!       "<<endl;
    cout<<"==========================================================================================="<<endl;
    int baris, kolom;
    do{
        cout<<"Enter the size of your map, min 3x3, max 10x10 (N *space* N): ";cin>>baris>>kolom;
    }while(baris<3 || kolom<3 || baris>=11 || kolom>= 11);
    vector<vector<char>> maphelo(baris,vector<char>(kolom, 'C'));
    srand(time(0));
    createMap(maphelo, baris, kolom);
    vector<vector<char>> mapnebak(baris,vector<char>(kolom, '?'));
    int nyawa = 3;
    int jumw = 0;
    areustupid(maphelo, mapnebak, baris, kolom, nyawa, jumw);
    if(nyawa==0){
        cout<<"You lost, better luck next time!"<<endl;
    }else{
        cout<<"Nice! You won!"<<endl;
    }
    displaymap(maphelo, baris, kolom);
}