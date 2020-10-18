//#include "mainwindow.h"

#include "minhaMatriz.h" //biblioteca criada para auxiliar na manipulação das matrizes
#include <fstream>
#include <string>
#include "Navegar.h"
//#include <QApplication>




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
int main(int argc, char *argv[]){
    std::string nome = "/home/thais/CLionProjects/navegacao/mapa.txt";
    Navegar robo(nome,0,9);



}