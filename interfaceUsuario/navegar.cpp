//
// Created by thais on 17/10/2020.
//

#include "navegar.h"
/*
 * Funções que verificam se podem ir para os respectivos lados
 * retorn true se puder e false se não
 * */
bool Navegar::verifica_frente(){
    int y = pos_atual_y + 1;
    if(y < 0){
        std::cout << "Fora dos limites do labirinto\n";
        return false;
    }
    int x = pos_atual_x;
    if(sala->retornaElemento(x, y) == 'a'){
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
        std::cout << "pode anda para esquerda\n";
        return true;
    }
    std::cout << " não pode anda para esquerda\n";
    return false;
}
bool Navegar::verifica_atras(){
    int y = pos_atual_y - 1;
    if(y < 0){
        std::cout << "Fora dos limites do labirinto\n";
        return false;
    }
    int x = pos_atual_x;
    if(sala->retornaElemento(x, y) == 'a'){
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
    if(verifica_frente() == true){caminhos[0] = 1;}
    else{caminhos[0]=0;}

    if(verifica_direita() == true){caminhos[1] = 1;}
    else{caminhos[1]=0;}

    if(verifica_esquerda() == true){caminhos[2] = 1;}
    else{caminhos[2]=0;}

    if(verifica_atras() == true){caminhos[3] = 1;}
    else{caminhos[3]=0;}

    return caminhos;
}

Navegar::~Navegar(){}
/*
    Construtor Padrão que recebe o nome do arquivo que deve ser utilizado para criar o mapa e a posição inical do robô
*/
Navegar::Navegar(std::string nome, int x, int y) {
    std::cout << "Criou o robô!" << std::endl;
    pos_atual_x = pos_inicial_x = x;
    pos_atual_y = pos_inicial_y = y;

    arq_sala = nome;
    iniciaMapa();
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
        sala->insereElemento('R',pos_atual_x,pos_atual_y);//Luis -> Modifiquei para que na hora de inicializarmos a matriz já colocarmos o robô.
        sala->imprime();
}

//Função utilizada para demonstrar o robô caminhando no labirinto
//Entrada: objeto do tipo minhaMatriz que representa o mapa
//         e as coordenadas da posição inicial do robô
//Saída: Nenhuma
/*
 * Luis -> Fiz algumas modificações nessa função para permitir que atualizassemos o mapa só com o robô se movendo
 * e tbm atualizassemos a posição atual dele. No caso estou checando se ele conseguiu mudar a posição do robo.
 * Se sim ele atualiza a posição do robô e apaga a letra R da matriz na posição anterior e atualiza a posição atual
*/
void Navegar::caminha(unsigned int x, unsigned int y)
{
    /*
        Checando a condição do robô tentar se mover para a mesma posição atual
    */
    if(int(x)==pos_atual_x && int(y) == pos_atual_y)
    {
        return;
    }
    /*Verifica se o robô consegue ser inserido na posição
     * se sim atualiza a posição atual e apaga o robô da última posição;
    */
    if(sala->insereElemento('R',x,y))
    {
        sala->insereElemento('a',pos_atual_x,pos_atual_y);
        pos_atual_x = x;
        pos_atual_y = y;
    }
}

void Navegar::imprime()
{
    sala->imprime();
}

void Navegar::autoNavegacao()
{
    int *vecPos = this->verifica_lados();
    bool terminou = false;
    int x = 0;
    int y = 0;
    while(!terminou)
    {

        //if(aux>3){break;}
        while(vecPos[0])
        {
            this->caminha(x,y+1);
            y = y+1;
            this->imprime();
            vecPos = this->verifica_lados();
        }
        std::cout << "Chegou até o final da sala!" << std::endl;

        while(vecPos[3])
        {
            this->caminha(x,y-1);
            y = y-1;
            this->imprime();
            vecPos = this->verifica_lados();
        }
        std::cout << "Voltou até o começo da sala!" << std::endl;

        x = x+1;
        this->caminha(x,y);
        vecPos = this->verifica_lados();
        while(!vecPos[0])
        {
            this->imprime();
            x = x+1;
            this->caminha(x,y);
            vecPos = this->verifica_lados();
        }
        if(x == 10 && y == 0)//Verificação se terminou a limpeza da sala
        {
            std::cout << "Acabou a sala!" << std::endl;
            terminou=true;
        }
    }
}

minhaMatriz<char> * Navegar::retSala()
{
    return sala;
}
