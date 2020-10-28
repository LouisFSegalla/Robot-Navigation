//#include "mainwindow.h"

#include "minhaMatriz.h" //biblioteca criada para auxiliar na manipulação das matrizes
#include <fstream>
#include <string>
#include "Navegar.h"
//#include <QApplication>

//Função Inicializa o laberinto que o robô precisa percorrer
//Entrada: objeto do tipo minhaMatriz que representará o mapa e o nome do arquivo contendo o mapa
//Saída: Nenhuma
template <typename T>
void iniciaMapa(minhaMatriz<T> *m, std::string nome)
{
    std::ifstream arq( nome.c_str() );
    if(!arq)
    {
        std::cout << "Não foi possível abrir o arquivo!" << std::endl;
        return;
    }
    int xAux = 0;
    int yAux = 0;

    arq >> xAux >> yAux;//Pego o tamanho da matriz
    m->resize(xAux,yAux,'a');//Redimensiono o ponteiro para o tamanho do mapa
    T aux;
    for(int j = 0; j < yAux; j++)
    {
        for(int i = 0; i < xAux; i++)
        {
            arq >> aux;
            m->insereElemento(aux,i,j);
        }
    }
    m->imprime();
}


int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    minhaMatriz<char> m;

    //MainWindow w;
    //w.show();

    std::string nome = "/home/thais/CLionProjects/navegacao/mapa.txt";
   // std::cout << nome << std::endl;
    iniciaMapa(&m,nome);
    std::cout << "\n\n";
    Navegar robo(&m,0,8);
    std::cout<<  robo.verifica_lados()<< std::endl;

   // robo.caminha(0,8);
   // return a.exec();
}

