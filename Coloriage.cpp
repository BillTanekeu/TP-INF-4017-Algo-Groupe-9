


/*

    ******  Representation d'un graphe
        un graphe est representer par une liste de vecteur où le premier element du vecteur est 
                        le numero du noeud et les autres elements sont les numeros des autres noeuds reliés à lui.
        
        Exemple :    G = {[1,2,4], [2,1], [3, 4], [4, 1,3]}
                    interpretation : le noeud 1 est relié aux noeuds 2 et4
                                    le noeud 2 est relier seulement avec le noeud 1
                                    ....


    ***************************Quelques synthaxes:
    ----------vecteur

    -- vector<int> T;            déclaration d'un vecteur d'entiers
    -- vector<int> T = (n,val);  declaration et initialisaition d'un vecteur avec n elements ayant chacun la valeur val
    -- T.size();                   renvoie la taille du vecteur
    -- T.push_back(val);            Ajoute val à la fin du vecteur
    -- T.insert(T.begin(), val)     Ajoute val au debut du vecteur
    -- T.empty()                    retourne false si le vecteur est vide et true si non
    -- 

    ---------liste

    -- list<int> L;                déclaration d'une liste d'entiers
    -- list<vector<int>> L;        déclaration d'une liste de vecteurs d'entiers
    -- L.front()                   renvoie l'element en tête de liste
    -- L.back()                    renvoie le dernier élément
    -- L.push_back(val)            ajouter val à la fin de liste
    -- L.push_front(val)           ajouter val au debut de la liste
    -- L.begin()                    renvoie le pointeur qui pointe sur la tete de liste
    -- L.end()                      renvoie le pointeur qui pointe sur la fin
    -- L.erase(pos);                supprimer l'element pointé par pos


    --------Dictionnaire

    -- map<string,int> Dico;        declaration d'un dictionaire ayant pour cle une chaine et pour valeur un entier
    -- map<int, int> Dico;          declaration d'un dictionnaire ayant pour cle un entier et pour valeur un entier
    -- dico[cle]                    retourne la valeur de l'element ayant pour cle cle
    -- it<-first                    renvoie la clé de l'itetrateur it
    -- it<-second                   renvoir la valeur de l'iterateur it


    --------Iterateur

    -- list<vector<int>>:: iterator it = L.begin();  declaration et initialisation d'un iterateur qui pointe sur la tete de la liste L 
    -- *it                          renvoie la valeur de la variable sur laquelle it pointe
    -- map<int,int>::iterator it = dico.begin();            declaration et initialisation d'un iterateur qui pointe sur le premier element du dictionnaire dico
    
   
    --------Boucle abregée

    -- for(int g : T){}             pour chaque element g de T (le type des valeurs contenues dant T doit etre specifié ici int)

    
    -------- Quelques Methodes

    -- cout<<"texte affiché"<<enld;         pour afficher du text dans la console

    
    
    
    -------- Fonctions implémentées

    -- segment1(T, a, b)                    prend un tableau et retourne une partie de ce dernier a represente l'indice de debut et b la fin      
    -- segment(L, a, b)                     faire pareil que segment1 mais plutot pour une liste
    -- concate(T, L)                        prend un vecteur T et l'ajoute comme premier element d'une liste L
    -- Fusion(A, B)                         fusionne deux listes A et B (voir Algo tri fusion)
    -- Trifusion(G)                         trie le graphe qui est une liste (voir algorithme tri fusion)
    -- getMincolor(Adj, dico, maxcolor)     renvoie la couleur d'un noeud (voir algorithme du rapport )
    -- SearchColor(dico , col)              renvoie true si la couleur a deja été utilisee par un noeud du graphe et false si c'est une nouvelle couleur
    -- coloriage(G)                          fonction pour colorier le graphe (voir algorithme du rapport) retourne un element de type res (structure definie plus haut)  
    

*/



#include <iostream>  // standart c++ 
#include <vector>
#include <list>
#include <map>      // pour definir le dictionnaire

using namespace std; // permet d'eviter d'ecrire "std::" devant chaque methode ( ex: std::cout<<;)





struct res      // sructure qui contient un dictionnaire et un entier
{
    map<int, int> Dico;             
    int nb;
}typedef res;


vector<int> segment1(vector<int> T, int a, int b){   //retourne une partie d'un vecteur
    vector<int> T1;

    for(int i = a; i< b; i++){              // a c'est le debut et b la fin
        T1.push_back(T[i]);
    }

    return T1;
}

list<vector<int>> segment(list<vector<int>> L, int a, int b){       //retourne une partie d'une liste
    list<vector<int>> L1;                                           // initialisation de la liste retournée
    int i = 0;
    for(list<vector<int>> :: iterator it = L.begin(); it != L.end(); it++){
        if(i == b){
            break;
        }
        if(i >= a ){
            L1.push_back(*it);
        }
        i++;
    }
    return L1;
}

/*
vector<int> concate(int A, vector<int> T){
    T.insert(T.begin(), A);
    return T;
}
*/

list<vector<int>> concate(vector<int> A, list<vector<int>> L){          // ajoute un vecteur au debut de la liste
    L.push_front(A);
    return L;
}

/*
vector<int> Fusion( vector<int> A, vector<int> B){
    if(A.empty()){
        return B;
    }
    else if(B.empty()){
        return A;
    }
    else if(A[0] >= B[0]){
        return concate(A[0], Fusion(segment(A, 1, A.size()), B));
    }
    else{
        return concate(B[0], Fusion(A, segment(B, 1, B.size())));
    }

}
*/
list<vector<int>> Fusion( list<vector<int>> A, list<vector<int>> B){   // voir algorithme tri fusion
    if(A.empty()){
        return B;
    }
    else if(B.empty()){
        return A;
    }
    else if(A.front().size() >= B.front().size()){
        return concate(A.front(), Fusion(segment(A, 1, A.size()), B));      // concate joue le role de + dans l'algorithme (wikipedia)
    }
    else{
        return concate(B.front(), Fusion(A, segment(B, 1, B.size())));
    }

}


/*
vector<int> TriFusion(vector<int> Tab){
    int n = Tab.size();
    if(n <= 1){
        return Tab;
    }
    else{
       return Fusion(TriFusion(segment(Tab, 0, Tab.size()/2)), TriFusion(segment(Tab, Tab.size()/2, Tab.size())));
    }
}
*/
list<vector<int>> TriFusion(list<vector<int>> G){                       // voir algorithme tri fusion
    int n = G.size();
    if(n <= 1){
        return G;
    }
    else{
       return Fusion(TriFusion(segment(G, 0, G.size()/2)), TriFusion(segment(G, G.size()/2, G.size())));
    }
}


int GetMinColor( vector<int> Adj, map<int, int> Dico, int Maxcolor){        // obtenir la couleur d'un noeud (voir algorithme du rapport)
    vector<int> Tab(Maxcolor,0);                                            // initialiser les couleurs à 0

    for(int s : Adj){                                                       // pour chaque sommet s de adjacence 
        Tab [Dico[s]-1] = Dico[s];                                          // marquer sa couleur dans la table
    }

    int i = 0;
    
    while(i < Maxcolor){
        if(Tab[i] == 0){                                                    // si on trouve la plus petite couleur non utilisee on s'arrete
            break;
        }
        i++;
    }
    int col;
    if(i == Maxcolor){
        col = i;
    }
    else{
        col = i+1;
    }

    return col;                                                             // retourner la couleur

}

bool SearchColor(map<int, int> Dico, int color){  // recherche si une couleur est deja utilisee (voir description plus haut) 
     for(map<int, int>::iterator it = Dico.begin(); it != Dico.end(); it++){
        if((it->second - color) == 0){
            return true;
        }
     }
     return false;
}

res Coloriage(list<vector<int>> G){             // algorithme du cloriage du graphe 
    G = TriFusion(G);                       // trier G
    int MaxColor = G.front().size();    // nombre necessaire de couleurs
    vector<int> couleurs;               // vecteurs contenant les couleurs (1, 2, ... ,maxcolor)

    for(int i =1; i<= MaxColor; i++){   // initialisation du vecteurs de couleurs
        couleurs.push_back(i);
    }

    map<int, int> Dico ;                // dictionnaire ayant pour cle le numero du noeud et pour valeur sa couleur
    for(int i = 1; i<= G.size(); i++){     // initialisation du dictionnaire :   couleur = 0
        Dico[i] = 0;
    }

    int nb = 0;                             // nombre de couleurs utilisés pour l'instant
    int col;
    for(vector<int> noeud : G){
        col = GetMinColor(segment1(noeud, 1, noeud.size()), Dico, MaxColor);
        if(SearchColor(Dico, col) == false){                                               // vérifie si la couleur a déja été utilisée dans le graphe
            nb +=1;                                                                   // incremente nb si c'est une nouvelle couleur
        }
        Dico[noeud[0]]  = col;                                                  // colorier le noeud courant
    }

    res result;

    result.Dico = Dico;
    result.nb   = nb;

    return result;              

}
 

int main(){


    map<int, int> dico;

    dico[1] = 1;
    dico[1] = 4;

    
    list<vector<int>> G = {{1,3,4},{2,4},{3,1,4,5}, {4,1,2,3,6}, {5,3} , {6,4}};        // definition d'un graphe
    
   
    
    res result;
    result = Coloriage(G);

    // affichage resultas
    cout<<"On utilise "<< result.nb<< " couleur(s) pour colorier ce graphe."<<"\n\n"<<endl;

    for(map<int, int>::iterator it = result.Dico.begin(); it != result.Dico.end(); it++){
        cout<< "sommet "<< it->first<< " colorié avec la couleur : "<< it->second<<endl;
    }
    

    return 0;
}