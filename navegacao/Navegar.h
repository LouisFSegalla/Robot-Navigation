//
// Created by thais on 17/10/2020.
//
#ifndef NAVEGAR_H
#define NAVEGAR_H

#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "minhaMatriz.h"

class Navegar{
    private:
        minhaMatriz<char> *sala;
        int pos_inicial_x;
        int pos_inicial_y;
        int pos_atual_x;
        int pos_atual_y;
        std::vector<int> pos_atual;
        std::vector<int> Posicao_andar(int lado);


        std::list<int> caminhos; //mudei em vez de usar um vetor para uma lista que pode ser atualizada o tempo todo
        std::list< std::vector<int> > bifurcacao;
        std::list< std::vector<int> > bifurcacaoTemporaria;
        std::list< std::vector<int> > visitados;

        bool isBifurcacao;//Essa variavel aqui tá sobrando, n está sendo utilizada em nenhum lugar
        bool chegou_objetivo;
    public:
        ~Navegar();
        Navegar(minhaMatriz<char> *labirinto, unsigned int x, unsigned int y);
        void caminha(unsigned int x, unsigned int y);
        void verifica_lados();
        bool verifica_frente();
        bool verifica_direita();
        bool verifica_esquerda();
        bool verifica_atras();
        void Busca_F();
        bool se_objetivo(unsigned int x, unsigned int y);
        std::list< std::vector<int> > retornaVisitados();
};
#endif //NAVEGAR_H
