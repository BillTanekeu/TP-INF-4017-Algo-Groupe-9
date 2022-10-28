#include<iostream>
#include<iomanip>
#include<vector>
#include<random>

using namespace std;

class Carreau{
    private:
        int couleur;
        int pgcb;
    
    public:
        int getCouleur(){
            return couleur;
        }
        int getPgcb(){
            return pgcb;
        }
        void setCouleur(int col){
            couleur = col;
        }
        void setPgcb(int val){
            pgcb = val;
        }
};

struct Turple  {
    int posX, PosY, pgcb;
}typedef Turple;

Turple Max(vector<vector<Carreau>> Mat){
    Turple max;
    max.pgcb = Mat[0][0].getPgcb();

    for(int i = 0; i < Mat.size(); i++){
        for(int j = 0; j < Mat[0].size(); j++){
            if(Mat[i][j].getPgcb() > max.pgcb){
                max.pgcb = Mat[i][j].getPgcb();
                max.posX = i+1;
                max.PosY = j+1;
            }
        }
    }
    
    return max;
}
int Min(int a, int b, int c){
    if(a > b){
        if(b > c){
            return c;
        }
        else{
            return b;
        }
    }
    else{
        if(a > c){
            return c;
        }
        else{
            return a;
        }
    }

}
Turple PGCB(vector<vector<Carreau>> Mat){
    Turple solution;

    for(int i = 0; i < Mat.size(); i++){
        for(int j = 0; j < Mat[0].size(); j++){

            if(Mat[i][j].getCouleur() == 0){
                Mat[i][j].setPgcb(0);
            }
            else{
                if( i == 0 or j == 0){
                    Mat[i][j].setPgcb(1);
                }
                else{
                    Mat[i][j].setPgcb(1 + Min(Mat[i-1][j].getPgcb(), Mat[i][j-1].getPgcb(), Mat[i-1][j-1].getPgcb()));
                }
            }
        }
    }

    solution = Max(Mat);
    return solution;

}

vector<vector<Carreau>> Init(int n, double p){
    vector<vector<Carreau>> Mat(n, vector<Carreau>(n));
    
    default_random_engine re;
    bernoulli_distribution dist{p};
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            Mat[i][j].setCouleur(dist(re));
        }
    }
    return Mat;
}

void Afficher(vector<vector<Carreau>> Mat){
    for(int i = 0; i < Mat.size(); i++){
        for(int j = 0; j < Mat[0].size(); j++){
            cout<< setw(3)<< Mat[i][j].getCouleur();
        }
        cout<<endl;
    }
}

int main(){

    vector<vector<Carreau>> M;
    Turple S;
    M = Init(16, 0.8);
    S = PGCB(M);

    cout<<"Image :"<<endl;
    Afficher(M);

    cout<<endl;
    cout<<"Le plus grand carré blanc est de taille : "<<S.pgcb<<endl;
    cout<<"La position du pixel en bas à droite est :"<<endl;
    cout<<"PosX = "<< S.posX<<endl;
    cout<<"PosY = "<< S.PosY<<endl;
    

    return 0;
}