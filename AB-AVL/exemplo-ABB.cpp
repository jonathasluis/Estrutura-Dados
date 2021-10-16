#include <iostream>
#include <cmath>

using namespace std;
int cont;

class Noh{
    friend class ABB;
    private:
        int mValor;
        Noh* esquerdo;
        Noh* direito;
        Noh* pai;
    public:
        Noh(int valor);
};

Noh::Noh(int valor){
    mValor = valor;
    esquerdo = NULL;
    direito = NULL; 
}

class ABB{
    private:
        Noh* raiz;

        Noh* inserirRecAux(Noh* umNoh, int umValor);
        Noh* minimoAux(Noh* raizSubArvore);
        Noh* maximoAux(Noh* raizSubArvore);
        void percorreEmOrdemAux(Noh* umNoh);
        void percorrePreOrdemAux(Noh* umNoh);
        void percorrePosOrdemAux(Noh* umNoh);
        Noh* removerRecAux(Noh* umNoh, int umValor);
        Noh* removeMenor(Noh* raizSub);
    public:
        ABB();
        ~ABB();
        void inserirRecursivamente(int umValor);
        int minimo();
        int maximo();
        void percorreEmOrdem();
        void percorrePreOrdem();
        void percorrePosOrdem();
        void removerRecursivamente(int umValor);
        void sucessor(Noh* noh);
        Noh* buscaAux(int umValor);
};

ABB :: ABB(){
    raiz = NULL;
}

ABB :: ~ABB(){
    percorrePosOrdem();
}

void ABB :: inserirRecursivamente(int umValor){//inicio insercao recursiva
    raiz = inserirRecAux(raiz, umValor);
}

Noh* ABB :: inserirRecAux(Noh* umNoh, int umValor){//ABB
    Noh* novo;

    if (umNoh == NULL){
        novo = new Noh(umValor);
        return novo;
    }else{
        cont++;
        if(umValor < umNoh->mValor){
            umNoh->esquerdo = inserirRecAux(umNoh->esquerdo,umValor);
            umNoh->esquerdo->pai = umNoh;
        }else{
            umNoh->direito = inserirRecAux(umNoh->direito,umValor);
            umNoh->direito->pai = umNoh;
        }
    }
    return umNoh;
}//fim insercao recursiva

Noh* ABB :: buscaAux(int umValor){
    Noh* atual = raiz;
    while(atual != NULL){
        cont++;
        if(atual->mValor == umValor){
            return atual;
        }else if(atual->mValor > umValor){
            atual = atual->esquerdo;
        }else{
            atual = atual->direito;
        }
    }
    return atual;
}

int ABB :: minimo(){
    if(raiz == NULL){
        cerr << "arvore vazia" << endl;
        exit(EXIT_FAILURE);
    }else{
        Noh* nohMinimo = minimoAux(raiz);
        return nohMinimo->mValor;
    }
}

Noh* ABB :: minimoAux(Noh* raizSubArvore){
    if(raizSubArvore->esquerdo != NULL and raizSubArvore != NULL){
        raizSubArvore = minimoAux(raizSubArvore->esquerdo);
    }
    return raizSubArvore;
}

int ABB :: maximo(){
    if(raiz == NULL){
        cerr << "arvore vazia" << endl;
        exit(EXIT_FAILURE);
    }else{
        Noh* nohMaximo = maximoAux(raiz);
        return nohMaximo->mValor;
    }
}

Noh* ABB :: maximoAux(Noh* raizSubArvore){
    while(raizSubArvore->direito != NULL ){
        raizSubArvore = raizSubArvore->direito;
    }
    return raizSubArvore;
}

void ABB ::percorreEmOrdem(){
    percorreEmOrdemAux(raiz);
}

void ABB ::percorreEmOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        percorreEmOrdemAux(umNoh->esquerdo);
        cout << umNoh->mValor << " ";
        percorreEmOrdemAux(umNoh->direito);
    }
}

void ABB ::percorrePreOrdem(){
    percorrePreOrdemAux(raiz);
}

void ABB ::percorrePreOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        cout << umNoh->mValor << " ";
        percorrePreOrdemAux(umNoh->esquerdo);
        percorrePreOrdemAux(umNoh->direito);
    }
}

void ABB ::percorrePosOrdem(){
    percorrePosOrdemAux(raiz);
}

void ABB ::percorrePosOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        percorrePosOrdemAux(umNoh->esquerdo);
        percorrePosOrdemAux(umNoh->direito);
        delete umNoh;
    }
}

void ABB:: sucessor(Noh* noh){
    noh = minimoAux(noh->direito);
    cout << noh->mValor;
}

void ABB :: removerRecursivamente(int umValor){
    raiz = removerRecAux(raiz,umValor);
}

Noh* ABB :: removerRecAux(Noh* umNoh,int umValor){
    if(umNoh == NULL){
        cerr << "no nao encontrado" << endl;
        exit(EXIT_FAILURE);
    }else{
        Noh* novaRaizSubArvore = umNoh;
        if(umValor < umNoh->mValor){
            umNoh->esquerdo = removerRecAux(umNoh->esquerdo, umValor);
        }else if(umValor > umNoh->mValor){
            umNoh->direito = removerRecAux(umNoh->direito,umValor);
        }else{
            if(umNoh->esquerdo == NULL){
                novaRaizSubArvore = umNoh->direito;
            }else if(umNoh->direito == NULL){
                novaRaizSubArvore = umNoh->esquerdo;
            }else{
                novaRaizSubArvore = minimoAux(umNoh->direito);
                novaRaizSubArvore->direito = removeMenor(umNoh->direito);
                novaRaizSubArvore->esquerdo = umNoh->esquerdo;
            }
            delete umNoh;
        }
        return novaRaizSubArvore;
    }
}

Noh* ABB :: removeMenor(Noh* raizSub){
    if(raizSub->esquerdo == NULL){
        return raizSub->direito;
    }else{
        raizSub->esquerdo = removeMenor(raizSub->esquerdo);
    }
    return raizSub;
}

int main(){
    ABB ar;
    int c[30] = {80,90,76,119,30,67,58,29,8,41,99,104,26,3,39,77,35,59,20,79,22,31,1,100,61,97,62,57,72,2};
    for (int i = 0;i<30;i++)
    {
        cont = 0;
        ar.inserirRecursivamente(c[i]);
        cout << c[i] << "-"<< cont << " ";
    }

    cout << endl << endl;

    int b[30] = {1,35,57,29,77,8,20,26,61,99,104,30,3,2,79,13,51,40,93,105,85,16,32,86,37,78,40,63,91,4};
    for (int i = 0; i < 30; i++)
    {
        cont=0;
        ar.buscaAux(b[i]);
        cout << b[i] << "-"<< cont << " ";
    }  
}