#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct resultat
{
    vector<vector<int>> M, S;
}typedef resultat;

int max(int a,int b){
    if(a<b){
        return b;
    }
    return a;
}
resultat Knapsack(int W, vector<int> poids, vector<int> valeurs){
    int n = poids.size();
    resultat r;
    // initialisation des matrices
    vector<vector<int>> M (n+1, vector<int>(W+1, 0));
    vector<vector<int>> S (n+1, vector<int>(W+1, 0));
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<= W; j++){

            if(j < poids[i-1]){
                M[i][j] = M[i-1][j];
                S[i][j] = j;
            }
            else{
                M[i][j] = max( M[i-1][j], M[i-1][j-poids[i-1]] + valeurs[i-1]);

                if(M[i-1][j]> M[i-1][j-poids[i-1]] + valeurs[i-1]){
                    S[i][j] = j; 
                }
                else{
                    S[i][j] = j - poids[i-1];
                }
            }

        }
    }

    
    r.M = M;
    r.S = S;
    
    return r;
}

vector<int> Solution(vector<vector<int>> S){
    vector<int> res;
    int K = S[1].size()-1;
    for(int i = S.size()-1; i>=1; i--){
        if(S[i][K] != K){
            res.push_back(i);
            K = S[i][K];
        }
    }
    return res;
}
int main(){

    int w = 10;
    vector<int> poids = {2,3,4,4,8};
    vector<int> valeurs = {3,5,6,7,10};
    resultat r;

    r = Knapsack(w, poids, valeurs);

    /*for(int i = 0; i< poids.size() +1; i++){
        for(int j = 0; j< w+1; j++){
            cout<< setw(3)<<r.M[i][j]; 
        }
        cout<<endl;
    }*/

    
    vector<int> vec;

    vec = Solution(r.S);
    for(int i =0; i< vec.size(); i++){
        cout<< vec[i]<<" ";
    }
    cout<<endl;
    
    
    return 0;
}