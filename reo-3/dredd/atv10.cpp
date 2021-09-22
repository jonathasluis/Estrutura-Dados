/* Código base para estrutura de dados FilaNormal
 * 
 * by Juliana Galvani Greghi
 *                                nov/2018
 */

#include <iostream>
#include <string>

using namespace std;

class Noh {
    friend class FilaNormal;
    friend class FilaPrioritaria;
    private:
        string dado; // poderia ser outro comando de variável
        Noh *proximo;
    public:
        Noh(string info){
            dado = info;
            proximo = NULL;
        }
        ~Noh(){
            proximo = NULL;
            delete proximo;
        }
};

// fila normal dinamicamente encadeada
class FilaNormal {
    private:
        Noh* nInicio;
        Noh* nFim;
        int nTamanho;

    public:
        FilaNormal();
        ~FilaNormal();
        void limparFilaNormal();
        void enfileiraNormal(string info);
        string desenfileiraNormal();
        bool nEstaVazia(); // verifica se existem elementos na fila     
    };


FilaNormal::FilaNormal() {
    nInicio = NULL;
    nFim = NULL;
    nTamanho = 0;
}

FilaNormal::~FilaNormal() { 
    limparFilaNormal();
}

void FilaNormal::limparFilaNormal(){
    while (nTamanho > 0) {
        desenfileiraNormal();
    } 
}

void FilaNormal::enfileiraNormal(string info) {
    Noh* novo = new Noh (info);
    if (nEstaVazia()){
        nInicio = novo;
    }else{
        nFim->proximo = novo;
    }
    nFim = novo;
    nTamanho++;
}

string FilaNormal::desenfileiraNormal() {
    string valor = nInicio->dado;
    Noh* temp = nInicio;
    nInicio = nInicio->proximo;
    delete temp;
    nTamanho--;
    return valor;
}
    
bool FilaNormal::nEstaVazia() {

   return(nTamanho == 0);

}

// fila prioritaria dinamicamente encadeada
class FilaPrioritaria  {
    private:
        Noh* pInicio;
        Noh* pFim;
        int pTamanho;

    public:
        FilaPrioritaria();
        ~FilaPrioritaria();
        void limparFilaPrioritaria();
        void enfileiraPriori(string info);
        string desenfileiraPriori();
        bool pEstaVazia(); // verifica se existem elementos na fila     
    };


FilaPrioritaria::FilaPrioritaria() {
    pInicio = NULL;
    pFim = NULL;
    pTamanho = 0;
}

FilaPrioritaria::~FilaPrioritaria() { 
    limparFilaPrioritaria();
}

void FilaPrioritaria::limparFilaPrioritaria(){
    while (pTamanho > 0) {
        desenfileiraPriori();
    } 
}

void FilaPrioritaria::enfileiraPriori(string info) {
    Noh* novo = new Noh (info);
    if (pEstaVazia()){
        pInicio = novo;
    }else{
        pFim->proximo = novo;
    }
    pFim = novo;
    pTamanho++;
}

string FilaPrioritaria::desenfileiraPriori() {
    string valor = pInicio->dado;
    Noh* temp = pInicio;
    pInicio = pInicio->proximo;
    delete temp;
    pTamanho--;
    return valor;
}
    
bool FilaPrioritaria::pEstaVazia() {

   return(pTamanho == 0);

}

int atender(FilaNormal& f1,FilaPrioritaria& f2, int contador){

    if((f2.pEstaVazia() == false and contador > 0) or (f2.pEstaVazia() == false and f1.nEstaVazia())){
        cout << f2.desenfileiraPriori() << endl;
        contador--;

    }else if((f1.nEstaVazia() == false and contador <= 0) or (f2.pEstaVazia() and f1.nEstaVazia() == false)){
        cout << f1.desenfileiraNormal() << endl;
        contador = 3;

    }else{
        cout << "AGUARDE" << endl;
    }
    return contador;
}

int main() {
    FilaNormal f1;
    FilaPrioritaria f2;
    string comando;
    string nome;
    int contador = 3;

    do{
        cin >> comando;

        if(comando == "normal"){
            cin >> nome;
            f1.enfileiraNormal(nome);
        }

        if(comando == "prioridade"){
            cin >> nome;
            f2.enfileiraPriori(nome);
        }

        if(comando == "atender"){
            contador = atender(f1,f2,contador);
        }

    } while (comando != "fim");
    
    return 0;
}