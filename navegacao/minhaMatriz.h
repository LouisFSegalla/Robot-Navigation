#ifndef MINHAMATRIZ_H
#define MINHAMATRIZ_H

#include <iostream>


template<typename T>
class minhaMatriz
{
private:
    T* matriz;
    int x;
    int y;
public:
    minhaMatriz();
    minhaMatriz(int a, int b);
    ~minhaMatriz();
    void resize(int a, int b, T fillElem);
    void insereElemento(T elem, int a, int b);
    T retornaElemento(int a, int b);
    void imprime();
};


template<typename T>
minhaMatriz<T>::minhaMatriz()
{
    x = y = 0;
    matriz = NULL;
}

template<typename T>
minhaMatriz<T>::minhaMatriz(int a, int b)
{
    x = a;
    y = b;
    matriz = new T [a*b*(sizeof (T))];
    for(int i = 0; i < x*y; i++)
    {
        matriz[i] = 0;
    }
}

template<typename T>
minhaMatriz<T>::~minhaMatriz()
{
    x = y = 0;
    delete [] matriz;
}

template<typename T>
void minhaMatriz<T>::resize(int a, int b, T fillElem)
{
    if(x == 0 || y == 0)
    {
        x = a;
        y = b;
        matriz = new T [a*b*(sizeof (T))];
        for(int i = 0; i < x*y; i++)
        {
            matriz[i] = fillElem;
        }
    }
    else
    {
        delete [] matriz;
        x = a;
        y = b;
        matriz = new T [a*b*(sizeof (T))];
        for(int i = 0; i < x*y; i++)
        {
            matriz[i] = 0;
        }
    }
}

template<typename T>
void minhaMatriz<T>::insereElemento(T elem, int a, int b)
{
    if(a < x && b < y)
    {
        matriz[a + b*y] = elem;
    }
    else
    {
        std::cout << "Valores fora dos limites da matriz." << std::endl;
    }
}

template<typename T>
T minhaMatriz<T>::retornaElemento(int a, int b)
{
    return matriz[a + b*y];
}

template<typename T>
void minhaMatriz<T>::imprime()
{
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            std::cout << retornaElemento(i,j) << " ";
        }
        std::cout << std::endl;
    }
}

#endif // MINHAMATRIZ_H
