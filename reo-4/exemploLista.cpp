#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado;

class Noh{
    friend class lista;
    private:
        Dado dado;
        Noh* proximo;
    public:
        Noh (Dado d);
};

Noh::Noh(Dado d){
    dado = d;
    proximo = NULL;
}

class lista{
    private:
        Noh* primeiro;
        Noh* ultimo;
        int tamanho;
        void removeTodos();
        void imprimeReversoAux(Noh* umNoh);
    public:
        lista();
        lista(const lista& umaLista);
        ~lista();
        lista& operator= (const lista& umaLista);//sobrecarga do operador de atribuiçao
        inline void insere(Dado daado);
        void insereNoFim(Dado dado);
        void insereNoInicio(Dado dado);
        void insereNaPosicao(int posicao, Dado dado);
        int procura(int valor);
        void imprime();
        void imprimeReverso();
        inline bool vazia();
};

lista :: lista(){//constroi lista vazia
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

lista :: lista(const lista& umaLista){//construtor de copia
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;

    Noh* aux = umaLista.primeiro;

    while (aux != NULL){
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
}

lista :: ~lista(){
    removeTodos();
}

void lista :: removeTodos(){
    Noh* aux = primeiro;
    Noh* temp;

    while (aux != NULL)
    {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }

    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

lista& lista :: operator=(const lista& umaLista){
    removeTodos();
    Noh* aux = umaLista.primeiro;

    while (aux != NULL){
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }

    return *this;
}

void lista :: insere(Dado dado){
    insereNoFim(dado);
}

void lista :: insereNoFim(Dado dado){
    Noh* novo = new Noh(dado);

    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }else
    {
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

void lista :: insereNoInicio(Dado dado){
    Noh* novo = new Noh(dado);

    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }else
    {
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

void lista :: insereNaPosicao(int posicao,Dado dado){
    Noh* novo = new Noh(dado);

    if ((posicao <= tamanho) and (posicao>=0)){
        if (vazia()){
            primeiro = novo;
            ultimo = novo;
        }else if(posicao == 0){
            novo->proximo = primeiro;
            primeiro = novo;
        }else if(posicao == tamanho){
            ultimo->proximo = novo;
            ultimo = novo;
        }else{
            Noh* aux = primeiro;
            int posAux = 0;

            while (posAux < (posicao-1))
            {
                aux = aux->proximo;
                posAux++;
            }

            novo->proximo = aux->proximo;
            aux->proximo = novo; 
        }
        tamanho++;
    } else {
        cerr << "posica inexistente" << endl;
        exit(EXIT_FAILURE);
    }   
}

int lista :: procura(Dado valor){
    Noh* aux = primeiro;
    int posAux = 0;

    while ((aux != NULL) and (aux->dado != valor))
    {
        posAux++;
        aux = aux->proximo;
    }
    
    if (aux == NULL)
    {
        posAux = -1;
    }
    
    return posAux;
}

void lista :: imprime(){
    Noh* aux = primeiro;

    while (aux != NULL)
    {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    
    cout << endl;
}

void lista :: imprimeReverso(){
    imprimeReversoAux(primeiro);
    cout << endl;
}

void lista :: imprimeReversoAux(Noh* umNoh){
    if(umNoh != NULL){
        imprimeReversoAux(umNoh->proximo);
        cout << umNoh->dado << " "; 
    }
}

inline bool lista :: vazia(){
    return (tamanho == 0);
}

int main(){
    lista minhaLista;

    int valor;
    int num;
    cin >> num;

    for (int i = 0; i < num; i++)
    {
        cin >> valor;
        minhaLista.insere(valor);
    }
    minhaLista.imprime();

    minhaLista.insereNoInicio(55);
    minhaLista.insereNaPosicao(2,3);
    minhaLista.imprime();
    minhaLista.imprimeReverso();

}