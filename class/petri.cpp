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

PetriNet net;

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
            case 'G': actions[i] = G + (trem); break;
        }
    }

    in.close();
    return actions;
}


void build_net(){
    PetriNet read_net;

    read_net.pre = read_matrix("net/pre.txt");
    read_net.pos = read_matrix("net/pos.txt");
    read_net.actions = read_vector("net/actions.txt");

    read_net.marking.resize(N_PLACES);
    read_net.marking[4] = 1;
    read_net.marking[5] = 1;
    read_net.marking[6] = 1;

    net = read_net;
}

vector <int> sensibilized_transitions(PetriNet pnet){
    bool sensibilized;
    vector <int> transitions;
    transitions.resize(0);

    for (int j=0; j<N_TRANSITIONS; j++){
        sensibilized = true;
        for (int i=0; i<N_PLACES; i++)
            if (pnet.marking[i] < pnet.pre[i][j])
                sensibilized = false;
        if (sensibilized)
            transitions.push_back(j);
    }
    return transitions;

}

PetriNet get_petrinet(){
    return net;
}

void set_petrinet(PetriNet new_net){
    net = new_net;
}

PetriNet execute_pre(PetriNet pnet, int transition){
    cout << transition << endl;
    for (int i=0; i<N_PLACES; i++){
        cout << pnet.marking[i] << " ";
    }
    cout << endl;

    for (int i=0; i<N_PLACES; i++){
        cout << pnet.pre[i][transition] << " ";
    }
    cout << endl;

    for (int i=0; i<N_PLACES; i++){
        pnet.marking[i] -= pnet.pre[i][transition];
        cout << pnet.marking[i] << " ";
    }
    cout << endl;
    return pnet;
}

PetriNet execute_pos(PetriNet pnet, int transition){
    for (int i=0; i<N_PLACES; i++){
        cout << pnet.pos[i][transition] << " ";
    }
    cout << endl;
    for (int i=0; i<N_PLACES; i++){
        pnet.marking[i] += pnet.pos[i][transition];
        cout << pnet.marking[i] << " ";
    }
    cout << endl;
    return pnet;
}
