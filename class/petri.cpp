/*

Transicao::{
    Pre
    Pos
    funcao{
        anda, para, liga sensor
    }
}

funcao(estado atual){
    transicoes = transicoes_sensibilizadas(estado atual)
    transicao = escolhe(transicoes)
    marcaao atual -= transicao.Pre
    faz transicao.funcao()
    marcaao atual += transicao.Pos
    return marcaao atual
}
*/
#include <iostream>
#include <fstream>
#include "petri.h"
using namespace std;

#define N_TRANSITIONS 18
#define N_PLACES 17

vector <vector <int>> read_matrix(string file){
    vector <vector <int> > matrix;
    matrix.resize(N_PLACES);
    for (int i=0; i<N_PLACES; i++)
        matrix[i].resize(N_TRANSITIONS);

    ifstream in(file);

    if (!in.is_open()){
        cout << file << " not found" << endl;
        exit(1);
    }
    for (int i=0; i<N_PLACES; i++)
        for (int j=0; j<N_TRANSITIONS; j++)
            in >> matrix[i][j];

    in.close();
    return matrix;
}


vector <int> read_vector(string file){
    vector <int> actions;
    actions.resize(N_TRANSITIONS);

    ifstream in(file);

    if (!in.is_open()){
        cout << file << " not found" << endl;
        exit(1);
    }

    char ac;
    int trem;

    for (int i=0; i<N_TRANSITIONS; i++){
        in >> ac >> trem;
        switch(ac){
            case 'N': actions[i] = N; break;
            case 'R': actions[i] = R + (trem - 1); break;
            case 'L': actions[i] = L + (trem - 1); break;
            case 'S': actions[i] = S + (trem - 1); break;
            case 'G': actions[i] = G + (trem - 1); break;
        }
    }

    in.close();
    return actions;
}


PetriNet build_net(){
    PetriNet net;

    net.pre = read_matrix("net/pre.txt");
    net.pos = read_matrix("net/pos.txt");
    net.actions = read_vector("net/actions.txt");

    net.marking.resize(N_PLACES);
    net.marking[4] = 1;
    net.marking[5] = 1;
    net.marking[6] = 1;

    return net;
}

vector <int> sensibilized_transitions(PetriNet net){
    bool sensibilized;
    vector <int> transitions;
    transitions.resize(0);

    for (int j=0; j<N_TRANSITIONS; j++){
        sensibilized = true;
        for (int i=0; i<N_PLACES; i++)
            if (net.marking[i] < net.pre[i][j])
                sensibilized = false;
        if (sensibilized)
            transitions.push_back(j);
    }

    return transitions;

}
