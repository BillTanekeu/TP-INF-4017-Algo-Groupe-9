#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;


// prototypes des fonctions implementees plus bas

// somme de 02 matrices
vector<vector<int>> sum ( vector<vector<int>> A, vector<vector<int>> B);
// soustraction de 02 matrices
vector<vector<int>> sub ( vector<vector<int>> A, vector<vector<int>> B);
// division d' une matrice 
void split(vector<vector<int>> Parent, vector<vector<int>> &child, int x, int y);
// fusion
void join(vector<vector<int>> &Parent, vector<vector<int>> child, int x, int y);



// Algorithme recursif de strassen pour le produit de 02 matrices carrees
vector<vector<int>> strassen(vector<vector<int>> A, vector<vector<int>> B){

    //taille matrice
    int n = A.size();

    // initialisation matrice resultat (n x n)  avec valeurs nulles
    vector<vector<int>> R (n, vector<int>(n,0));

    // Cas de base 
    // n == 1 on fait le produit de 02 nombres

    if(n == 1){
        R[0][0] = A[0][0] * B[0][0];
    }
    // Dans ce cas il faut diviser chaque matrice en 4 de taille (n/2 x n/2)
    else{
        // Definition des matrices (n/2 x n/2)
        vector<vector<int>> A11 (n/2, vector<int>(n/2,0));
        vector<vector<int>> A12 (n/2, vector<int>(n/2,0));
        vector<vector<int>> A21 (n/2, vector<int>(n/2,0));
        vector<vector<int>> A22 (n/2, vector<int>(n/2,0));
        
        vector<vector<int>> B11 (n/2, vector<int>(n/2,0));
        vector<vector<int>> B12 (n/2, vector<int>(n/2,0));
        vector<vector<int>> B21 (n/2, vector<int>(n/2,0));
        vector<vector<int>> B22 (n/2, vector<int>(n/2,0));

        // remplissage des matrices (n/2, n/2)

        split(A, A11, 0, 0);
        split(A, A12, 1,0);
        split(A, A21, 0,1);
        split(A, A22, 1, 1);

        split(B, B11, 0, 0);
        split(B, B12, 1,0);
        split(B, B21, 0,1);
        split(B, B22, 1, 1);

        // utilisation des formules de l' algorithme pour calculer les 7 produits recursivement

        vector<vector<int>> M1 = strassen(sum(A11, A22), sum(B11, B22));
        vector<vector<int>> M2 = strassen(sum(A21, A22), B11);
        vector<vector<int>> M3 = strassen(A11, sub(B12, B22));
        vector<vector<int>> M4 = strassen(A22, sub(B21, B11));
        vector<vector<int>> M5 = strassen(sum(A11, A12), B22);
        vector<vector<int>> M6 = strassen(sub(A21, A11), sum(B11, B12));
        vector<vector<int>> M7 = strassen(sub(A12, A22), sum(B21, B22));


        // differents resultats
        vector<vector<int>> C11 = sum(sub(sum(M1, M4), M5), M7);
        vector<vector<int>> C12 = sum(M3, M5);
        vector<vector<int>> C21 = sum(M2, M4);
        vector<vector<int>> C22 = sum(sub(sum(M1, M3), M2), M6);

        //fusionner les resultats

        join(R, C11, 0, 0);
        join(R, C12, 1, 0);
        join(R, C21, 0, 1);
        join(R, C22, 1, 1);

    }
    // retourner le resultat
    return R;

}



int main(){

    vector<vector<int>> A ={    { 1, 2, 3, 4 },
                                { 4, 3, 0, 1 },
                                { 5, 6, 1, 1 },
                                { 0, 2, 5, 6 } };
    
    
    vector<vector<int>> B = {   { 1, 0, 5, 1 },
                                { 1, 2, 0, 2 },
                                { 0, 3, 2, 3 },
                                { 1, 2, 1, 2 } };
    vector<vector<int>> C;

    
    C = strassen(A, B);

    for (int i = 0; i < C.size(); i++){
            for(int j=0; j< C.size(); j++){
                cout << setw(3) << C[i][j] ;
            }
            cout<<endl;
        }
    cout<<endl;
    

    return 0;
}


vector<vector<int>> sum ( vector<vector<int>> A, vector<vector<int>> B){

    vector<vector<int>> C(A.size(), vector<int>(A.size(), 0));  

    if(A.size() != B.size() ){
        cout<< "impossible d'effectuer l'addition ";
    }
    else{

        for (int i = 0; i < C.size(); i++){
            for(int j=0; j< C.size(); j++){
                C[i][j] = A[i][j] + B[i][j];
            }
        }
    }

    return C;
}


vector<vector<int>> sub ( vector<vector<int>> A, vector<vector<int>> B){

    vector<vector<int>> C(A.size(), vector<int>(A.size(), 0));  

    if(A.size() != B.size() ){
        cout<< "impossible d'effectuer la soustraction ";
    }
    else{

        for (int i = 0; i < C.size(); i++){
            for(int j=0; j< C.size(); j++){
                C[i][j] = A[i][j] - B[i][j];
            }
        }
    }

    return C;
}


void split(vector<vector<int>> Parent, vector<vector<int>> &child, int x, int y){
    
    for (int i = 0; i < child.size(); i++){
        for(int j = 0; j < child.size(); j++ ){
            child[i][j] = Parent[i+ (y*child.size())][j + (x*child.size())];
        }
    }
}


void join(vector<vector<int>> &Parent, vector<vector<int>> child, int x, int y){
    
    
    for (int i = 0; i < child.size(); i++){
        for(int j = 0; j < child.size(); j++ ){
            Parent[i + (y*child.size())][j + (x*child.size())] = child[i][j];
        }
    }
}
