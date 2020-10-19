#include "mainwindow.h"
#include <QApplication>

#include "minhaMatriz.h" //biblioteca criada para auxiliar na manipulação das matrizes
#include <fstream>
#include <string>
#include "navegar.h"


void autoNaveg(Navegar *robo)
{
    int *vecPos = robo->verifica_lados();
    bool terminou = false;
    int aux = 0;
    int x = 0;
    int y = 0;
    while(aux < 2)
    {
        if(x==9 && y == 0){terminou=true;}
        while(vecPos[0])
        {
            std::cout << "Iteração: " << y << std::endl;
            robo->caminha(x,y+1);
            y = y+1;
            robo->imprime();
            vecPos = robo->verifica_lados();
        }
        std::cout << "Chegou até o final da sala!" << std::endl;

        while(vecPos[3])
        {
            std::cout << "Iteração: " << y << std::endl;
            robo->caminha(x,y-1);
            y = y-1;
            robo->imprime();
            vecPos = robo->verifica_lados();
        }
        std::cout << "Voltou até o começo da sala!" << std::endl;
        std::cout << "x: " << x << " | y: " << y << std::endl;
        x = x+1;
        robo->caminha(x,y);
        vecPos = robo->verifica_lados();
        robo->imprime();
        std::cout << "x: " << x << " | y: " << y << std::endl;
        std::cout << "vecPos[0] = " << vecPos[0]
                  << "\nvecPos[1] = " << vecPos[1]
                  << "\nvecPos[2] = " << vecPos[2]
                  << "\nvecPos[3] = " << vecPos[3]
                  << std::endl;
        while(!vecPos[0])
        {
            std::cout << "Iteração: " << x << std::endl;
            robo->caminha(x,y);
            x = x+1;
            robo->imprime();
            vecPos = robo->verifica_lados();
        }
        x=x-1;
        std::cout << "X e Y no final do percurso: \n";
        std::cout << "x: " << x << " | y: " << y << std::endl;
        aux++;
    }
}


/*int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //minhaMatriz<char> m;

    //MainWindow w;
    //w.show();

    std::string nome = "/home/thais/CLionProjects/navegacao/mapa.txt";
   // std::cout << nome << std::endl;
    iniciaMapa(&m,nome);
    std::cout << "\n\n";
    caminha(&m,1,9);
   // return a.exec();
}
*/
int main(){
    std::string nome = "/home/luis/Documentos/2020_1/Integrador II/codigosNavegacao/Robot-Navigation-main/navegacao/mapa.txt";
    Navegar robo(nome,0,0);

    robo.verifica_frente();
    robo.verifica_atras();
    robo.verifica_direita();
    robo.verifica_esquerda();

    robo.imprime();

    robo.autoNavegacao();

}
