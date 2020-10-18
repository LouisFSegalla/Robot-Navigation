//
// Created by thais on 17/10/2020.
//

#include "Navegar.h"
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
int* Navegar::verifica_lados(){
    int *caminhos = new int[4];
    if(verifica_frente() == true) caminhos[0] = 1;

    if(verifica_direita() == true) caminhos[1] = 2;

    if(verifica_esquerda() == true) caminhos[2] = 3;

    if(verifica_atras() == true) caminhos[3] = 4;

    return caminhos;
}
Navegar::~Navegar(){}
Navegar::Navegar(std::string nome, int x, int y) {
    pos_inicial_x = x;
    pos_inicial_y = y;
    pos_atual_x = pos_inicial_x;
    pos_atual_y = pos_inicial_y;
    arq_sala = nome;
    iniciaMapa();
    std::cout << "\n\n";
    caminha(pos_inicial_x,pos_inicial_y);
}

//Função Inicializa o labirinto que o robô precisa percorrer
//Entrada: objeto do tipo minhaMatriz que representará o mapa e o nome do arquivo contendo o mapa
//Saída: Nenhuma
void Navegar::iniciaMapa() {

        std::ifstream arq( arq_sala.c_str() );
        if(!arq)
        {
            std::cout << "Não foi possível abrir o arquivo!" << std::endl;
            return;
        }
        int xAux = 0;
        int yAux = 0;

        arq >> xAux >> yAux;//Pego o tamanho da matriz
        sala->resize(xAux,yAux,'a');//Redimensiono o ponteiro para o tamanho do mapa
        char aux;
        for(int j = 0; j < yAux; j++)
        {
            for(int i = 0; i < xAux; i++)
            {
                arq >> aux;
                sala->insereElemento(aux,i,j);
            }
        }
        sala->imprime();
}

//Função utilizada para demonstrar o robô caminhando no labirinto
//Entrada: objeto do tipo minhaMatriz que representa o mapa
//         e as coordenadas da posição inicial do robô
//Saída: Nenhuma
void Navegar::caminha(unsigned int x, unsigned int y)
{
    //Inicializa o robô dentro do labirinto
    sala->insereElemento('R',x,y);
    sala->imprime();
}
