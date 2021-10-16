#include <iostream>
using namespace std;

class Noh
{
friend class Fila;
private:
   int mValor;
   Noh* mProximo;
public:
    Noh(int valor);
};

Noh::Noh(int valor)
{
    mValor = valor;
    mProximo = NULL; 
}

class Fila
{
private:
    Noh* mInicio;
    Noh* mFim;
    int mTamanho;
public:
    Fila(/* args */);
    ~Fila();
    int tamanho();
    void enfileira(int valor);
    int desenfileira();
    void limpaFila();
    bool vazia();
};

Fila::Fila(/* args */)
{
    mInicio = NULL;
    mFim = NULL;
    mTamanho = 0;
}

Fila::~Fila()
{
    limpaFila();
}

void Fila::limpaFila(){
    while (mTamanho > 0)
    {
        desenfileira();
    } 
}

int Fila::tamanho(){
    return mTamanho;
}

bool Fila::vazia(){
    return (mTamanho == 0);
}

void Fila::enfileira(int valor){
    Noh* novo = new Noh (valor);
    if (vazia())
    {
        mInicio = novo;
    }else
    {
        mFim->mProximo = novo;
    }
    mFim = novo;
    mTamanho++;
}

int Fila::desenfileira(){
    int valor = mInicio->mValor;
    Noh* temp = mInicio;
    mInicio = mInicio->mProximo;
    delete temp;
    mTamanho--;
    return valor;
}

int main(){
    Fila f1;
    int num;
    cin >> num;

    while (num >= 0)
    {
        f1.enfileira(num);
        cin>>num;
    }
    
    cout << "tamanho: " << f1.tamanho() << endl;

    while (not f1.vazia())
    {
        cout << f1.desenfileira() << " ";
    }
    

}