//Bibliotecas padrãodo C++
#include <iostream>
#include <array>

//Bibliotecas criadas por nós
#include "Navegar.h"
#include "minhaMatriz.h"

//Bibliotecas para a interface gráfica
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGridLayout>
#include <QTime>
#include <QTimer>

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
   void inicializa(minhaMatriz<char> m, std::list< std::vector<int> > l);
   minhaMatriz<char> matriz;//Variável onde será guardada o mapa
   int totalPos;//Numero total de posições que o robô visitou
   int itAtual;//Iteração atual das posições visitadas pelo robô

   int *posX;//Ponteiro para um vetor de posições que representa as posições em X que o robô visita
   int *posY;//Ponteiro para um vetor de posições que representa as posições em Y que o robô visita

   int tamX;//Tamanho em X do mapa
   int tamY;//Tamanho em Y do mapa
};


void View::inicializa(minhaMatriz<char> m, std::list< std::vector<int> > l)
{
    //Mapa
    m.retornaTamanho(&tamX,&tamY);//Pego o tamanho da matriz
    matriz.resize(tamX,tamY,'a');
    char auxChar;
    for(int j = 0; j < tamY; j++)
    {
        for(int i = 0; i < tamX; i++)
        {
            auxChar = m.retornaElemento(i,j);
            matriz.insereElemento(auxChar,i,j);
        }
    }

    //Lista de visitados
    totalPos = l.size();
    posX = new int[totalPos];
    posY = new int[totalPos];
    std::vector<int> aux;
    int i = 0;
    for(std::list< std::vector<int> >::iterator itList = l.begin(); itList != l.end(); itList++)
    {
        aux = *itList;
        posX[i] = aux[0];
        posY[i] = aux[1];
        i++;
    }
}

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
              if(view.matriz.retornaElemento(x,y) == 'x' || view.matriz.retornaElemento(x,y) == 'a')//Se dentro da matriz o espaço for livre deixa o mesmo como um quadrado azul
              {
                  QGraphicsRectItem *rect1 = new QGraphicsRectItem(x * width, y * height, width, height,rect);
              }
              else if(view.matriz.retornaElemento(x,y) == 'F' || view.matriz.retornaElemento(x,y) == 'R')
              {
                  QGraphicsRectItem *rect1 = new QGraphicsRectItem(x * width, y * height, width, height,rect);
                  rect1->setBrush(Qt::yellow);
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
    arq.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer timer;//define o timer que será utilizado para chamar a função de updateScene
    QWidget window;//cria-se um objeto para a janela que será aberta
    QGridLayout layout(&window);//colaca-se essa janela dentro de um layout
    std::array<View, 1> views;//vetor de objetos view. No caso só uso 1, mas o vetor vem da implementação original que foi usada como base

    minhaMatriz<char> m;
    /*------------------------------------------------------------------------------------------------------------------------------------*/

    std::string nome = "/home/luis/Documentos/2020_1/Integrador II/codigosNavegacao/navegacao_all_in_one/mapa.txt";
    iniciaMapa(&m,nome);

    Navegar robo(&m,0,0);
    robo.Busca_F();

    std::list< std::vector<int> > l;
    l = robo.retornaVisitados();


    int i = 0;
    for (auto & view : views) {
      view.setScene(new QGraphicsScene(&view));
      view.inicializa(m,l);
      view.itAtual = 0;
      layout.addWidget(&view);
      ++ i;
    }

    QObject::connect(&timer, &QTimer::timeout, [&views]{ updateScenes(views); });
    timer.start(250);
    window.show();
    return a.exec();
}
