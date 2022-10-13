#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct resultat
{
    vector<vector<int>> M,S;
}typedef resultat ;

resultat LCS(string A, string B ){
    int n = A.size();
    int m = B.size();
    resultat res;
    vector<vector<int>> M (n+1, vector<int>(m+1, 0));
    vector<vector<int>> S (n+1, vector<int>(m+1, 0));
    //cout<<M[n][m];
    for(int i = 1; i<= n; i++){
        for(int j = 1; j<=m; j++){
            if(A[i-1] == B[j-1]){
                M[i][j] = 1 + M[i-1][j-1];
                S[i][j] = 1;
            }
            else{
                if(M[i-1][j] > M[i][j-1]){
                    M[i][j] = M[i-1][j];
                    S[i][j] = 2;
                }
                else{
                    M[i][j] = M[i][j-1];
                    S[i][j] = 3;
                }
            }
        }
    }
    //cout<< M[n][m];
    res.M = M;
    res.S = S;

    return res;


}

void Affichage( vector<vector<int>> S, string A, int i , int j, string &res){
    if (i ==0 || j == 0){
        return;
    }
    if (S[i][j] == 1){
        Affichage(S, A, i-1, j-1, res);
        res.push_back(A[i-1]);
    }
    else{ 
        if( S[i][j] == 2){
            Affichage(S, A, i-1, j, res);
        }
        if( S[i][j] == 3){
            Affichage(S, A, i, j-1, res);
        }

    }

}

int main(){
   
    string A = "AGGTAB";
    string B = "GXTXAYB";

    resultat res;
    res = LCS(A,B);
    string a;
    Affichage(res.S, A,A.size(), B.size(), a );

   /*for(int i = 0; i< res.M.size() ; i++){
        for(int j = 0; j< res.M[0].size(); j++){
            cout<< setw(3)<<res.M[i][j]; 
        }
        cout<<endl;
    }*/
    cout<< a<<endl;
    return 0;
}