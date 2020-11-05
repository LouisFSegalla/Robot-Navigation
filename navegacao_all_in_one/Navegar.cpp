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
    pos_atual.push_back(x);
    pos_atual.push_back(y);


    caminha(pos_atual[0],pos_atual[1]);

    isBifurcacao    = false;
    chegou_objetivo = false;
}

/*
 * Funções que verificam se podem ir para os respectivos lados
 * retorn true se puder e false se não
 * */
bool Navegar::verifica_frente(){//pq pra frente é -1 e pra trás +1 ?
    int y = pos_atual_y - 1;
    if(y < 0){
        return false;
    }
    int x = pos_atual_x;
    if(sala->retornaElemento(x, y) == 'a' || sala->retornaElemento(x, y) == 'F'){
        return true;
    }
    return false;
}
bool Navegar::verifica_direita(){
    int x = pos_atual_x + 1;
    if(x < 0){
        return false;
    }
    int y = pos_atual_y;
    if(sala->retornaElemento(x, y) == 'a' || sala->retornaElemento(x, y) == 'F'){
        return true;
    }
    return false;
}
bool Navegar::verifica_esquerda(){
    int x = pos_atual_x - 1;
    if(x < 0){
        return false;
    }
    int y = pos_atual_y;
    if(sala->retornaElemento(x, y) == 'a' || sala->retornaElemento(x, y) == 'F'){
        return true;
    }
    return false;
}
bool Navegar::verifica_atras(){
    int y = pos_atual_y + 1;
    if(y < 0){
        return false;
    }
    int x = pos_atual_x;
    if(sala->retornaElemento(x, y) == 'a' || sala->retornaElemento(x, y) == 'F'){
        return true;
    }
    return false;

}

/*
 * Chama as funções de cada um dos lados e guarda em caminhos
 *  retornar os caminhos possíveis
 *  OBS: tem que rever ta estranho esse retorno e tentar colocar como variável da classe
 * */
void Navegar::verifica_lados() {
    caminhos.clear();//inicio o método limpando todo o conteúdo da lista
    if(verifica_frente()){
        caminhos.push_front(1);
    }

    if(verifica_direita()){
        caminhos.push_front(2);
    }

    if (verifica_esquerda()) {
        caminhos.push_front(3);
    }

    if (verifica_atras()){
        caminhos.push_front(4);
    }
}



bool Navegar::se_objetivo(unsigned int x, unsigned int y){

    if(sala->retornaElemento(x, y) == 'F')
    {
        return true;
    }

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

    if(pos_atual_x != x || pos_atual_y != y ){
        sala->insereElemento('x',pos_atual_x,pos_atual_y);
    }
    pos_atual_x = x;
    pos_atual_y = y;
    pos_atual[0] = x;
    pos_atual[1] = y;
    visitados.push_back(pos_atual);
}

std::vector<int> Navegar::Posicao_andar(int lado)
{
    std::vector<int> posicao;
    //frente
    if(lado == 1){
        posicao.push_back(pos_atual_x);
        posicao.push_back(pos_atual_y-1);
    }
    //direita
    if(lado == 2){
        posicao.push_back(pos_atual_x+1);
        posicao.push_back(pos_atual_y);

    }
    //esquerda
    if(lado == 3){
        posicao.push_back(pos_atual_x-1);
        posicao.push_back(pos_atual_y);
    }
    //atras
    if(lado == 4){
        posicao.push_back(pos_atual_x);
        posicao.push_back(pos_atual_y+1);
    }
    return posicao;
}

//versao simplificada, labirintos complexos ele vai se perder se fizermos isso
//vamos testar essa e depois ajeitamos para labirintos complexos
void Navegar::Busca_F()
{
    int contador = 0;
    /*
        A treta parece estar na hora que precisamos selecionar os caminhos
        a ordem que eles são colocados na lista parece importar!
    */
    while(!chegou_objetivo)
    {
        verifica_lados();
        if(contador == 100)//apenas uma precaução para o programa não rodar infinitamente
        {
            break;
        }
        if(caminhos.size() == 1)//preciso verificar qual o lado disponível
        {
            std::list<int>::iterator it = caminhos.begin();
            std::vector<int> posicao;
            posicao = Posicao_andar(*it);
            caminha(posicao[0],posicao[1]);
        }

        if(caminhos.size() > 1)
        {
            //atualiza a posição da entrada da bifurcacao
            bifurcacao.push_back(pos_atual);
            isBifurcacao = true;//acho q esse passo é desnecssário
            //Faz caminhar em uma das posições possíveis dentro da bifurcação
            std::list<int>::iterator it = caminhos.begin();
            std::vector<int> posicao;
            posicao = Posicao_andar(*it);
            caminha(posicao[0],posicao[1]);

        }

        if(caminhos.size() == 0)
        {
            //Pegando o primeiro elemento da lista de bifurcações, que no caso seria
            //a última bifurcação encontrada
            std::list< std::vector<int> >::iterator itBif = bifurcacao.end();
            itBif--;
            std::vector<int> auxBif = *itBif;//v é a variável auxiliar para guardar a posição da última bifurcação
            std::list< std::vector<int> >::iterator itVis = visitados.end();
            itVis--;
            std::vector<int> auxVis = *itVis;
            while(pos_atual != auxBif)//enquanto não volta para a bifurcação
            {
                itVis--;//pula uma posição na lista de visitados
                auxVis = *itVis;
                caminha(auxVis[0],auxVis[1]);//voltamos para a posição anterior
                if(pos_atual == auxBif)
                {
                    verifica_lados();//confere agora os novos possíveis lados
                    if(caminhos.size() > 0)//Se ele tiver para onde ir o robô se move
                    {
                        std::list<int>::iterator it = caminhos.begin();
                        std::vector<int> posicao;
                        posicao = Posicao_andar(*it);
                        caminha(posicao[0],posicao[1]);
                        break;
                    }
                    else//Caso ao voltar para a bifurcação ele já tenha tentado todos os caminhos possíveis ele deve voltar para a bifurcação anterior
                    {
                        bifurcacao.pop_back();//retira a bifurcação atual dos valores válidos à serem procurados porque extinguiram-se as possibilidades de caminhos a serem seguidos
                    }
                    if(bifurcacao.empty()){isBifurcacao=false;}
                }
                //visitados.pop_back();//não iremos mais descartar os valores da lista de visitados.
            }

        }
        contador++;

    }
}

std::list< std::vector<int> > Navegar::retornaVisitados()
{
    return visitados;
}
