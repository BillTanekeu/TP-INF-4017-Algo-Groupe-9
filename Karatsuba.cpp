#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct PairVec{
    vector<int> first, second;
}typedef PairVec;

//****** Algorithme Karatsuba pour la multiplication de 02 polynomes
// un polynome est representé par un vecteur contenant les coefficients de tel sorte que 
        // le dernier element du tableau soit le coefficient d plus haut monome

// calcul du degre d'un polynome
int degre(vector<int> P);
// decoupe un polynome en 2
PairVec decoupe(vector<int> P, int n);
// donne le maximum entre 02 nombres
int Max (int a, int b);
// somme de 02 polynomes
vector<int> somme(vector<int> P, vector<int> Q);
// produit d'un polynome avec un monome (decallage)
vector<int> produit_monome(vector<int> p, int n);
// calcul de -p
vector<int> oppose(vector<int> P);


// produit de 02 polynomes
vector<int> Karatsuba(vector<int> P, vector<int> Q){
    int deg_P = degre(P);
    int deg_Q = degre(Q);

    // cas de base

    if(deg_P == 0){
        vector<int> r;
        for(int i = 0; i< Q.size(); i++){
            r.push_back(Q[i]*P[0]);
        }
        return r;
    }


    if(deg_Q == 0){
        vector<int> v;
        for(int i = 0; i< P.size(); i++){
            v.push_back(P[i]*Q[0]);
        }
        return v;
    }

    int n = (Max(deg_P, deg_Q) + 1) /2;

    PairVec pair1;
    pair1 = decoupe(P, n);

    PairVec pair2;
    pair2 = decoupe(Q, n);

    vector<int> P1 = pair1.first;
    vector<int> P2 = pair1.second;

    vector<int> Q1 = pair2.first;
    vector<int> Q2 = pair2.second;

    vector<int> P1Q1 = Karatsuba(P1, Q1);
    vector<int> P2Q2 = Karatsuba(P2, Q2);

    vector<int> P12Q12 = Karatsuba(somme(P1, P2), somme(Q1, Q2));

    vector<int> R1 = somme(P12Q12, somme(oppose(P1Q1), oppose(P2Q2)) );
    R1 = produit_monome(R1, n);
    vector<int> R2 = produit_monome(P2Q2, 2*n);

    return somme(P1Q1, somme(R1, R2));
    
}

int main(){

    vector<int> P = {1,2};      //2x + 1
    vector<int> Q =     {-1,1};     // x - 1
    /*
    PairVec pair;
    pair = decoupe(P, 4);
    vector<int> p1 = pair.first;
    vector<int> p2 = pair.second;

    cout<< "Degre de P "<< degre(P) <<setw(3) << endl;

    cout<< "vecteur v1"<< setw(3)<< endl;

    for (int i= 0; i< p1.size(); i++){
        cout<< p1[i]<< setw(3);
    }
    cout<< endl;

    cout<< "vecteur v2"<< setw(3)<< endl;
    */
    
    vector<int> res;
    res = Karatsuba(P, Q);      // 2x**2 - x -1
    for (int i= 0; i< res.size(); i++){
        cout<< res[i]<< setw(3);
    }
    cout<< endl;

    return 0;
}




int degre(vector<int> P){
    return (P.size() - 1);
}

PairVec decoupe(vector<int> P, int n){
    PairVec pair;
    int i; 
    
    for (i = 0; i< n; i++){
        pair.first.push_back(P[i]);
        pair.second.push_back(P[n+i]);
    }
    if(i < P.size()/2)
        pair.second.push_back(P[n+i]);
    return pair;

}

int Max (int a, int b){
    if((a - b) > 0 )
        return a;
    return b;
}

vector<int> somme(vector<int> P, vector<int> Q){
    vector<int> res;
    int l = Max(P.size(), Q.size());
    int a, b;
    for(int i = 0 ; i<l; i++){
        if(i > P.size()-1){
            a = 0;
        }
        else{
            a = P[i];
            
        }

        if(i > Q.size()-1){
            b = 0;
        }
        else{
            b = Q[i];
        }

        res.push_back(a+b);
    }

    return res;
}

vector<int> produit_monome(vector<int> p, int n){
    vector<int> res = p;
    for(int i =0; i< n; i++){
        res.insert(res.begin(), 0);
    }

    return res;
}

vector<int> oppose(vector<int> P){
    for(int i=0; i< P.size(); i++){
        P[i] = -P[i];
    }
    return P;
}
