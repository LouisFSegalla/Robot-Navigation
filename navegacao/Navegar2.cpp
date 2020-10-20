//
// Created by thais on 17/10/2020.
//

#include "Navegar.h"
/*
 * Funções construtora e destrutura
 * */
Navegar::~Navegar(){}
Navegar::Navegar(minhaMatriz<char> *labirinto, unsigned int x, unsigned int y){
    sala = labirinto;
    pos_inicial_x = x;
    pos_inicial_y = y;
    pos_atual_x = x;
    pos_atual_y = y;

    caminha(pos_inicial_x,pos_inicial_y);
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
int Navegar::verifica_lados() {
    int contador = 0;
    if(verifica_frente()){
        caminhos[0] = 1;
        contador++;
    }

    if(verifica_direita()){
        caminhos[1] = 2;
        contador++;
    }

    if (verifica_esquerda()) {
        caminhos[2] = 3;
        contador++;
    }

    if (verifica_atras()){
        caminhos[3] = 4;
        contador++;
    }
    return contador;

}



bool Navegar::se_objetivo(unsigned int x, unsigned int y){

    if(sala->retornaElemento(x, y) == 'F') return true;

    else return false;
}
//Função utilizada para demonstrar o robô caminhando no labirinto
//Entrada: objeto do tipo minhaMatriz que representa o mapa
//         e as coordenadas da posição inicial do robô
//Saída: Nenhuma
void Navegar::caminha(unsigned int x, unsigned int y)
{
    if(se_objetivo(x,y) == true){
        chegou_objetivo = true;
    }
    //Inicializa o robô dentro do labirinto
    sala->insereElemento('R',x,y);

    if(pos_atual_x != x|| pos_atual_y != y ){
        sala->insereElemento('x',pos_atual_x,pos_atual_y);
    }
    pos_atual_x = x;
    pos_atual_y = y;
    sala->imprime();


}
//versao simplificada, labirintos complexos ele vai se perder se fizermos isso
//vamos testar essa e depois ajeitamos para labirintos complexos
void Navegar::Busca_F(){
    /*int *caminhos = new int(4);
    verifica_lados(caminhos);
    while(chegou_objetivo == false){

        se o tamanho caminhos = 1
            Coloca lista visitados
            anda
            veriica_lados

        se o tamanho de caminhos > 1
            atualiza a posicao da entrada da bifurcaco
            coloca na fila de bifurcados
            variavel controle bifurcação para true
            movimenta
            coloca na fila


        se o tamanhos de caminhos = 0
            volta até chegar na posicao da ultima bifurcacao(while pos_atula!=pos_bifurcacao)
            se verifica_lados na bifucacao é validos
                caminha
            se nao
                tirar da lista de bifucacao
                e volta para linha 166
            se lista bifurcacao está vazia
                 variavel controle bifurcação para false

        se chegou no objetivo
            esvazia a lista de visitados
            para a acao

    }
*/}