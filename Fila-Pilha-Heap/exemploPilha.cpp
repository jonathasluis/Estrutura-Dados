#include <iostream>
using namespace std;

class Noh
{
friend class Pilha;
private:
   int mValor;
   Noh* mAbaixo;
public:
    Noh(int valor);
};

Noh::Noh(int valor)
{
    mValor = valor;
    mAbaixo = NULL; 
}

class Pilha
{
private:
    Noh* mTopo;
    int mTamanho;
public:
    Pilha(/* args */);
    ~Pilha();
    int tamanho();
    void empilha(int valor);
    void desempilha();
    void limpaPilha();
    bool vazia();
};

Pilha::Pilha(/* args */)
{
    mTopo = NULL;
    mTamanho = 0;
}

Pilha::~Pilha()
{
    limpaPilha();
}

void Pilha::limpaPilha(){
    while (mTamanho > 0)
    {
        desempilha();
    } 
}

int Pilha::tamanho(){
    return mTamanho;
}

bool Pilha::vazia(){
    return (mTamanho == 0);
}

void Pilha::empilha(int valor){
    Noh* novo = new Noh (valor);
    novo->mAbaixo = mTopo;
    mTopo = novo;
    mTamanho++;
}

void Pilha::desempilha(){
    //int valor = mTopo->mValor;
    Noh* temp = mTopo;
    cout <<  temp->mValor << " ";
    mTopo = mTopo->mAbaixo;
    delete temp;
    mTamanho--;
    //return valor;
}

int main(){
    Pilha p1;
    int num;
    cin >> num;

    while (num >= 0)
    {
        p1.empilha(num);
        cin>>num;
    }
    
    cout << "tamanho: " << p1.tamanho() << endl;

    while (not p1.vazia())
    {
        p1.desempilha();
    }
    

}