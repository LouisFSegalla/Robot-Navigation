//
// Created by thais on 17/10/2020.
//

#ifndef NAVEGACAO_NAVEGAR_H
#define NAVEGACAO_NAVEGAR_H

#include <fstream>
#include <string>
#include "minhaMatriz.h"

class Navegar{
    private:
        minhaMatriz<char> *sala;
        int pos_inicial_x;
        int pos_inicial_y;
        int pos_atual_x;
        int pos_atual_y;
        bool chegou_objetivo;
        int caminhos[4];
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
        void caminha(unsigned int x, unsigned int y);
        int verifica_lados();
        bool verifica_frente();
        bool verifica_direita();
        bool verifica_esquerda();
        bool verifica_atras();
        void Busca_F();
        bool se_objetivo(unsigned int x, unsigned int y);
};


#endif //NAVEGACAO_NAVEGAR_H
