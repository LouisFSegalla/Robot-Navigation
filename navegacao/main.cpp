//#include "mainwindow.h"
//#include <QApplication>

#include <fstream>
#include <string>
#include "Navegar.h"
#include "minhaMatriz.h" //biblioteca criada para auxiliar na manipulação das matrizes


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
    std::cout << "xAux = " << xAux << "\nyAux = " << yAux << std::endl;
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
}

int main()
{
    minhaMatriz<char> m;

    //MainWindow w;
    //w.show();

    std::string nome = "/home/luis/Documentos/2020_1/Integrador II/codigosNavegacao/navegacaoRobo/mapa.txt";
    //std::cout << nome << std::endl;
    iniciaMapa(&m,nome);

    Navegar robo(&m,0,0);
    std::cout << "\n\nChamando a função de busca!\n\n";
    robo.Busca_F();

    std::list< std::vector<int> > l;
    l = robo.retornaVisitados();

    std::vector<int> aux;
    for(std::list< std::vector<int> >::iterator itList = l.begin(); itList != l.end(); itList++)
    {
        aux = *itList;
        std::cout << aux[0] << " " << aux[1] << std::endl;
    }

}
