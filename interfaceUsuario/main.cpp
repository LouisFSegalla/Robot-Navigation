/*#include "mainwindow.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QGraphicsItem>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    int height = 10;
    int width = 10;

    int grid_size = 10;

    QGraphicsView w;

    QGraphicsScene *scene = new QGraphicsScene(&w);
    scene->setBackgroundBrush(Qt::blue);

    QGraphicsRectItem *rect = new QGraphicsRectItem(0, 0, 10, 10);
    scene->addItem(rect);

    for (int y = 0; y < grid_size; y++){
        for (int x = 0; x < grid_size; x++){
            QGraphicsRectItem *rect1 = new QGraphicsRectItem(x * width, y * height, width, height,rect);
            if(x%2 == 0){rect1->setBrush(Qt::yellow);}
        }
    }

    QGraphicsRectItem *rect1 = new QGraphicsRectItem(0, 0, width, height,rect);
    rect1->setBrush(Qt::red);

    w.setScene(scene);
    w.resize(1000, 1000);
    w.show();

    return a.exec();
}*/

#include <iostream>

#include "navegar.h"
#include "minhaMatriz.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGridLayout>
#include <QTime>
#include <QTimer>
#include <array>

/*
    Classe criada para guardar alguns dos parâmetros que serão utilizados na hora de montar
    a animação;
*/

class View : public QGraphicsView
{
public:
   View(QWidget *parent = 0) : QGraphicsView(parent) {
      setRenderHint(QPainter::Antialiasing);
   }
   void resizeEvent(QResizeEvent *) {
      fitInView(0, 0, 100, 100, Qt::KeepAspectRatio);
   }
   /*
    Função que lê o arquivos que representa a sala e o arquivo que representa a movimentação do robô e guarda as informações
    Entrada: Duas strings que devem ser respecticvamente o mapa do laberinto e os passos do robô.
    */
   void leArquivo(std::string nome1, std::string nome2);
   minhaMatriz<char> matriz;//Variável onde será guardada o mapa
   int totalPos;//Numero total de posições que o robô visitou
   int itAtual;//Iteração atual das posições visitadas pelo robô

   int *posX;//Ponteiro para um vetor de posições que representa as posições em X que o robô visita
   int *posY;//Ponteiro para um vetor de posições que representa as posições em Y que o robô visita

   int tamX;//Tamanho em X do mapa
   int tamY;//Tamanho em Y do mapa
};

void View::leArquivo(std::string nome1, std::string nome2)
{
    std::ifstream arq1( nome1.c_str() );
    if(!arq1)
    {
        std::cout << "Não foi possível abrir o arquivo 1!" << std::endl;
        tamX = 0;
        tamY = 0;
        return;
    }
    arq1 >> tamX >> tamY;//Pego o tamanho da matriz
    matriz.resize(tamX,tamY,'a');
    char aux;
    for(int j = 0; j < tamY; j++)
    {
        for(int i = 0; i < tamX; i++)
        {
            arq1 >> aux;
            matriz.insereElemento(aux,i,j);
        }
    }
    arq1.close();

    std::ifstream arq2( nome2.c_str() );
    if(!arq2)
    {
        std::cout << "Não foi possível abrir o arquivo 2!" << std::endl;
        totalPos = 0;
        return;
    }
    int tam   = 0;
    int auxI  = 0;
    int auxII = 0;
    arq2 >> tam;
    totalPos = tam;
    posX = new int[tam];
    posY = new int[tam];
    for(int i = 0; i < tam; i++)
    {
        arq2 >> auxI >> auxII;
        posX[i] = auxI;
        posY[i] = auxII;
    }
    arq2.close();
}

/*
    Função responsável por fazer a animação. Ela é chamada a cada tick do timer.
    Entrada: Um vetor de class View. Isso será mudado no futuro, esta implementação está herdando muito do código usado como base

*/
template <typename Container>
void updateScenes(Container & views)
{
   int height = 10;
   int width = 10;

   int grid_size = 10;//Tamanho da grade que vamos usar
   for (auto & view : views) {
      auto scene = view.scene();
      scene->clear();
      scene->setBackgroundBrush(Qt::blue);//Define a cor do backgroud para azul
      QGraphicsRectItem *rect = new QGraphicsRectItem(0, 0, 10, 10);//Cria uma nova figura retangular de 10x10
      scene->addItem(rect);
      for (int y = 0; y < grid_size; y++)
      {
          for (int x = 0; x < grid_size; x++)
          {
              if(view.matriz.retornaElemento(x,y) == 'a')//Se dentro da matriz o espaço for livre deixa o mesmo como um quadrado azul
              {
                  QGraphicsRectItem *rect1 = new QGraphicsRectItem(x * width, y * height, width, height,rect);
              }
              else//caso contrário (se for um obstáculo) definimos ele como um quadrado preto
              {
                  QGraphicsRectItem *rect1 = new QGraphicsRectItem(x * width, y * height, width, height,rect);
                  rect1->setBrush(Qt::black);
              }
              //Nesta ação itera-se pela lista de posições e a posição "atual" do robô é marcada como um quadrado vermelho
              QGraphicsRectItem *rect2 = new QGraphicsRectItem(view.posX[view.itAtual] * width, view.posY[view.itAtual] * height, width, height,rect);
              rect2->setBrush(Qt::red);
          }
      }
      //A função atualiza a iteração atual a fim de progredir as posições
      view.itAtual++;
      if(view.itAtual == view.totalPos)//caso tenha passado por todas as posições ele volta ao início da lista de posições.
      {
          view.itAtual = 0;
      }
   }
}

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   QTimer timer;//define o timer que será utilizado para chamar a função de updateScene
   QWidget window;//cria-se um objeto para a janela que será aberta
   QGridLayout layout(&window);//colaca-se essa janela dentro de um layout
   std::array<View, 1> views;//vetor de objetos view. No caso só uso 1, mas o vetor vem da implementação original que foi usada como base

   std::string nome1 = "/home/luis/Documentos/2020_1/Integrador II/codigosNavegacao/interfaceUsuario/mapa.txt";
   std::string nome2 = "/home/luis/Documentos/2020_1/Integrador II/codigosNavegacao/interfaceUsuario/saida.txt";

   int i = 0;
   for (auto & view : views) {
      view.setScene(new QGraphicsScene(&view));
      view.leArquivo(nome1,nome2);
      view.itAtual = 0;
      layout.addWidget(&view);
      ++ i;
   }

   QObject::connect(&timer, &QTimer::timeout, [&views]{ updateScenes(views); });
   timer.start(100);
   window.show();
   return a.exec();
}
