#include <iostream>
using namespace std;

class Noh {
    friend class PilhaAbre;
    private:
        char mValor;
        int mPosicao;
        Noh* mAbaixo;
    public:
        Noh(char valor,int posicao);
};

Noh::Noh(char valor,int posicao) {
    mValor = valor;
    mAbaixo = NULL; 
    mPosicao = posicao;
}

class PilhaAbre {
    private:
        Noh* mTopo;
        int mTamanho;
    public:
        PilhaAbre(/* args */);
        ~PilhaAbre();
        int tamanho();
        void empilha(char valor,int posicao);
        void desempilha();
        void limpaPilha();
        bool vazia();
        int espiaTopo();  
};

PilhaAbre::PilhaAbre(/* args */) {
    mTopo = NULL;
    mTamanho = 0;
}

PilhaAbre::~PilhaAbre() {
    limpaPilha();
}

void PilhaAbre::limpaPilha(){
    while (mTamanho > 0) {
        desempilha();
    } 
}

int PilhaAbre::tamanho(){
    return mTamanho;
}

bool PilhaAbre::vazia(){
    return (mTamanho == 0);
}

void PilhaAbre::empilha(char valor,int posicao){
    Noh* novo = new Noh (valor,posicao);
    novo->mAbaixo = mTopo;
    mTopo = novo;
    mTamanho++;
}

void PilhaAbre::desempilha(){
    Noh* temp = mTopo;
    mTopo = mTopo->mAbaixo;
    delete temp;
    mTamanho--;
}

int PilhaAbre :: espiaTopo(){
    return mTopo->mPosicao;
}

int main(){
    string texto;
    PilhaAbre pAbre;

    getline(cin,texto);
    int tamanhoArrayChar = texto.length();

    for (int i = 0; i < tamanhoArrayChar; i++){
       if (texto[i] == '('){
           pAbre.empilha(texto[i], i);
       }else if (texto[i] == ')'){
           if(pAbre.vazia()){
               cout << i;
               return 0;
           }else{
               pAbre.desempilha();
           }
       }
    } 
    
    if (not pAbre.vazia()){
        cout << pAbre.espiaTopo();
    }else{
        cout << "correto";
    }
    
    return 0;

}