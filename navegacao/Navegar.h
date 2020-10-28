//
// Created by thais on 17/10/2020.
//

#ifndef NAVEGACAO_NAVEGAR_H
#define NAVEGACAO_NAVEGAR_H

#include <fstream>
#include <string>
#include "minhaMatriz.h"
#include <list>
#include <tuple>
#include <stdio.h>
#include <iostream>

using namespace std;

class Navegar{
    private:
        minhaMatriz<char> *sala;
        int pos_inicial_x;
        int pos_inicial_y;
        int pos_atual_x;
        int pos_atual_y;
       tuple<int,int> pos_atual;
        bool chegou_objetivo;
        list< tuple<int,int> > visitados;
        list< tuple<int,int> >  lista_bifurcacao;
        bool  bifurcacao;
    //std::list<int> caminhos;
        /*variaveis necessarias para a busca
         *  tuple bifurcação(posição da bifurcação x,y)
         *  lista de visitados
         *  para mais complexas
         *  uma lista temporararia com os caminhos da bifurcacao
         *  bool de bifurcacao
         * */


    public:
        ~Navegar();
        Navegar(minhaMatriz<char> *labirinto, unsigned int x, unsigned int y);
        void caminha(tuple<int,int> t);
        std::list<int>  verifica_lados();
        tuple<int,int> Posicao_andar(int lado);
        bool verifica_frente();
        bool verifica_direita();
        bool verifica_esquerda();
        bool verifica_atras();
        void Busca_F();
        bool se_objetivo(unsigned int x, unsigned int y);

};


#endif //NAVEGACAO_NAVEGAR_H
