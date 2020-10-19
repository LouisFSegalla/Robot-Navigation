//
// Created by thais on 17/10/2020.
//

#ifndef NAVEGACAO_NAVEGAR_H
#define NAVEGACAO_NAVEGAR_H

#include <fstream>
#include <string>
#include "minhaMatriz.h"
#include <stdio.h>
class Navegar{
    private:
        minhaMatriz<char> *sala;
        std::string arq_sala;
        int pos_inicial_x;
        int pos_inicial_y;
        int pos_atual_x;
        int pos_atual_y;
     //   char *bifurcao;

    public:
        ~Navegar();
        Navegar(std::string nome, int x, int y);
        void iniciaMapa();
        void caminha(unsigned int x, unsigned int y);
        int* verifica_lados();
        bool verifica_frente();
        bool verifica_direita();
        bool verifica_esquerda();
        bool verifica_atras();
        void imprime();
        void autoNavegacao();
};


#endif //NAVEGACAO_NAVEGAR_H
