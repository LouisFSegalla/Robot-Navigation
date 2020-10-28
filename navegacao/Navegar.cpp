//
// Created by thais on 17/10/2020.
//

#include "Navegar.h"
#include <list>
#include <tuple>
#include <stdio.h>
#include <iostream>
/*
 * Funções construtora e destrutura
 * */
using namespace std;
Navegar::~Navegar(){}
Navegar::Navegar(minhaMatriz<char> *labirinto, unsigned int x, unsigned int y){
    sala = labirinto;
 //   pos_inicial_x = x;
 //   pos_inicial_y = y;
    pos_atual_x = x;
    pos_atual_y = y;
    pos_atual = make_tuple(x,y);
    bifurcacao = false;
    chegou_objetivo = false;
    caminha(pos_atual);
}

/*
 * Funções que verificam se podem ir para os respectivos lados
 * retorn true se puder e false se não
 * */
bool Navegar::verifica_frente(){
    int y = pos_atual_y - 1;
    if(y < 0){
        std::cout << "Fora dos limites do labirinto\n";
        return false;
    }
    char frente;
    int x = pos_atual_x;
    frente = sala->retornaElemento(x, y);
    if(frente == 'a'){
        std::cout << "pode anda para frente\n";
        return true;
    }
    std::cout << "não pode anda para frente\n";
    return false;
}
bool Navegar::verifica_direita(){
    int x = pos_atual_x + 1;
    if(x < 0){
        std::cout << "Fora dos limites do labirinto\n";
        return false;
    }
    int y = pos_atual_y;
    if(sala->retornaElemento(x, y) == 'a'){
        std::cout << "pode anda para direita\n";
        return true;
    }
    std::cout << " não pode anda para direita\n";
    return false;
}
bool Navegar::verifica_esquerda(){
    int x = pos_atual_x - 1;
    if(x < 0){
        std::cout << "Fora dos limites do labirinto\n";
        return false;
    }
    int y = pos_atual_y;
    if(sala->retornaElemento(x, y) == 'a'){
        std::cout << "pode anda para ESQUERDA\n";
        return true;
    }
    std::cout << " não pode anda para esquerda\n";
    return false;
}
bool Navegar::verifica_atras(){
    int y = pos_atual_y + 1;
    if(y < 0){
        std::cout << "Fora dos limites do labirinto\n";
        return false;
    }
    char frente;
    int x = pos_atual_x;
    frente = sala->retornaElemento(x, y);
    if(frente == 'a'){
        std::cout << "pode anda para atras\n";
        return true;
    }
    std::cout << " não pode anda para atras\n";
    return false;

}

/*
 * Chama as funções de cada um dos lados e guarda em caminhos
 *  retornar os caminhos possíveis
 *  OBS: tem que rever ta estranho esse retorno e tentar colocar como variável da classe
 * */
std::list<int> Navegar::verifica_lados(){
    std::list<int> caminhos;
    if(verifica_frente()){
        caminhos.push_back(1);

    }

    if(verifica_direita()){
        caminhos.push_back(2);

    }

    if (verifica_esquerda()) {
        caminhos.push_back(3);

    }

    if (verifica_atras()){
        caminhos.push_back(4);

    }
    return caminhos;

}



bool Navegar::se_objetivo(unsigned int x, unsigned int y){

    if(sala->retornaElemento(x, y) == 'F') return true;

    else return false;
}
//Função utilizada para demonstrar o robô caminhando no labirinto
//Entrada: objeto do tipo minhaMatriz que representa o mapa
//         e as coordenadas da posição inicial do robô
//Saída: Nenhuma
void Navegar::caminha(tuple<int,int> t )
{
    int x = get<0>(t);
    int y = get<1>(t);
    if(se_objetivo(x,y) == true){
        chegou_objetivo = true;
    }
    //Inicializa o robô dentro do labirinto
    sala->insereElemento('R',x,y);

    if(pos_atual_x != x|| pos_atual_y != y ){
        sala->insereElemento('x',pos_atual_x,pos_atual_y);
    }
   // pos_atual_x = x;
    //pos_atual_y = y;
    pos_atual = t;
    sala->imprime();


}

tuple<int,int> Navegar::Posicao_andar(int lado)
{
    tuple<int,int> posicao;
    //frente
    if(lado == 1){
        posicao = make_tuple(pos_atual_x, pos_atual_y-1);
    }
    //direita
    if(lado == 2){
        posicao = make_tuple(pos_atual_x+1, pos_atual_y);
    }
    //esquerda
    if(lado == 3){
        posicao = make_tuple(pos_atual_x-1, pos_atual_y-1);
    }
    //atras
    if(lado == 4){
        posicao = make_tuple(pos_atual_x, pos_atual_y+1);
    }
    return posicao;
}
//versao simplificada, labirintos complexos ele vai se perder se fizermos isso
//vamos testar essa e depois ajeitamos para labirintos complexos
void Navegar::Busca_F(){
    tuple<int, int> posicao;
     std::list<int> caminhos;
    while(chegou_objetivo == false){
        caminhos = verifica_lados();

        //se chegou no objetivo
        if (chegou_objetivo == true){
          //  esvazia a lista de visitados
          for(int i =0; i<visitados.size(); i++){
              visitados.pop_front();
          }
            //    para a acao
            return;

        }
       // se o tamanho caminhos = 1
       if(caminhos.size() == 1){
           //Coloca a proxima posição lista visitados
            posicao = Posicao_andar(caminhos.front());
            visitados.push_back(posicao);
           //     anda para  proxima posição
           caminha(posicao);

           //      veriica_lados
       }


       // se o tamanho de caminhos > 1
       if(caminhos.size() > 1){
           //     atualiza a posicao da entrada da bifurcaco
           //     coloca na fila de bifurcados
           lista_bifurcacao.push_back(pos_atual);
           //     muda variavel controle bifurcação para true
           bifurcacao = true;
           posicao = Posicao_andar(caminhos.front());
            visitados.push_back(posicao);
           //     anda para  proxima posição
           caminha(posicao);

       }



       // se o tamanhos de caminhos = 0
       if(caminhos.size() == 0){
           while(pos_atual != lista_bifurcacao.back()){
               //percorre a lista de visitados até chegar na bifurcacao
               caminha(visitados.back());
               // se Posicao  do  robo  ==  posic̃ao  da  ultimabifurcac̃ao
               if(pos_atual == lista_bifurcacao.back()){
                   list<int> aux = verifica_lados();
                   if(aux.size()> 0){
                       //     anda para  proxima posição
                       posicao = Posicao_andar(caminhos.front());
                       visitados.push_back(posicao);

                       caminha(posicao);
                   }
                   else{
                       lista_bifurcacao.pop_back();//remove da fila
                   }
                   if(lista_bifurcacao.empty()) bifurcacao = false;
               }

           }

       }
       // limpa a lista para ser realocada e não perder memoria
       //caminhos.clear();
    }

}