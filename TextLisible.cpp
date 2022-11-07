#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<list>

using namespace std;



map<string,bool> CreateDico(){
    
    ifstream Flux("liste_francais.txt");// flux sur le fichier 'liste_francais.txt' en lecture
    string mot;                         // un mot est sur une ligne dans le fichier
    
    map<string,bool> dico;
    
    if(Flux){                           // ouverture du fichier
        while (getline(Flux, mot)){         // lecture de la ligne et stockage dans la variable mot
                                            // on sort du while quant on atteind la fin du fichier
            
            dico[mot] = true;               // stockage du mot dans le dictionnaire
        }
        Flux.close();
        
    }else{
        cout<<"Erreur l'or de l'ouverture du fichier"<<endl;
    }
    
    return dico;
}

struct sol
{
    bool lisible;
    list<vector<int>> position;
};


sol TexLisible(string text, map<string,bool> dico){
    int n = text.size();
    sol solution;
  
    vector<bool> S(n+1);
    list<vector<int>> L;
    
    S[0] = true;
    bool b1,b2;
    for(int i = 1; i<= n; i++){
        b1 = false;
        vector<int> pos;
        for(int j = 0; j <= i-1; j++){
            b2 = S[j] and (dico.find(text.substr(j,i-j)) != dico.end());
            b1 = b1 or b2;

            if(b2){
                pos.push_back(j+1);
            }
        }
        S[i] = b1;
        L.push_back(pos);
    }

    solution.lisible = S[n];
    solution.position = L;
    return solution;
}

bool searcVector(int val, vector<int> T){
    bool trouve = false;
    int i = 0;
    while(!trouve and !T.empty()){
        if(T[i] == val){
            trouve = true;
        }
        i ++;
    }

    return trouve;
}

void AffichageResultat(sol solution){
    if(solution.lisible){
        cout<<"******le texte peut etre lisible"<<endl;
        cout<<"******les positions pour placer les espaces :"<<endl;
        vector<int> pos;
        for (vector<int> v: solution.position){
            for (int j = 0; j < v.size(); j++){
                cout<<v[j]<<" ";
                
    
            }
            
        }
         
    }
    else{
        cout<<"Texte pas lisible"<<endl;
    }
}

int main(){

    map<string,bool> dico = CreateDico();
    string text = "bonjourjesuisundieu";
    //cout<<TexLisible(text, dico)<<endl;
    sol S =    TexLisible(text, dico);
    cout<<"Texte: "<<text<<endl;
   AffichageResultat(S);
    //cout<<(dico.find("bonj") != dico.end()) <<endl;
    //cout<<dico.contains("bonjour");
    return 0;
}