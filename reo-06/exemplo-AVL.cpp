#include <iostream>
#include <cmath>

using namespace std;
int cont;

class Noh{
    friend class AVL;
    private:
        int mValor;
        Noh* esquerdo;
        Noh* direito;
        int altura;
    public:
        Noh(int valor);
        int fatorBalanceamento(Noh* umNoh);
        int informaAltura(Noh* umNoh);
        void atualizaAltura(Noh* umNoh);
};

Noh::Noh(int valor){
    mValor = valor;
    esquerdo = NULL;
    direito = NULL; 
    altura = 1;
}

int Noh::fatorBalanceamento(Noh* umNoh) {
    if(umNoh != NULL){
        if(umNoh->esquerdo != NULL and umNoh->direito != NULL)
            cont+=2;
        else if(umNoh->esquerdo != NULL or umNoh->direito != NULL)
            cont++;
        int altArvesquerdo = informaAltura(umNoh->esquerdo);
        int altArvDir = informaAltura(umNoh->direito);
        int fatorBal = altArvesquerdo - altArvDir;
        return fatorBal;
    }else
        return 0;   
}

int Noh::informaAltura(Noh* umNoh){
    if(umNoh == NULL)
        return 0;
    else{
        return umNoh->altura;
    }    
}

void Noh::atualizaAltura(Noh* umNoh){
    if(umNoh != NULL){
        if(umNoh->esquerdo != NULL and umNoh->direito != NULL)
            cont+=2;
        else if(umNoh->esquerdo != NULL or umNoh->direito != NULL)
            cont++;
        int altArvesquerdo = informaAltura(umNoh->esquerdo);
        int altArvDir = informaAltura(umNoh->direito);
        umNoh->altura = 1 + fmax(altArvesquerdo, altArvDir);
    }
}

class AVL{
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
        Noh* rotacaoesquerda(Noh* umNoh);
        Noh* rotacaodireito(Noh* umNoh);
        Noh* arrumaBalanceamento(Noh* umNoh);
    public:
        AVL();
        ~AVL();
        void inserirRecursivamente(int umValor);
        void inserirIterativamente(int umValor);
        int minimo();
        int maximo();
        void percorreEmOrdem();
        void percorrePreOrdem();
        void percorrePosOrdem();
        void removerRecursivamente(int umValor);
        void sucessor(Noh* Noh);
        Noh* buscaAux(int umValor);
};

AVL :: AVL(){
    raiz = NULL;
}

AVL :: ~AVL(){
    percorrePosOrdem();
}

void AVL :: inserirRecursivamente(int umValor){//inicio insercao recursiva
    raiz = inserirRecAux(raiz, umValor);
}

Noh* AVL :: inserirRecAux(Noh* umNoh, int umValor){
    if(umNoh == NULL){
        Noh* novo = new Noh(umValor);
        return novo;
    }else{
        cont++;
        if(umValor < umNoh->mValor){
            umNoh->esquerdo = inserirRecAux(umNoh->esquerdo,umValor);
        }else{
            umNoh->direito = inserirRecAux(umNoh->direito,umValor);
        }
    }
    umNoh->atualizaAltura(umNoh);
    return arrumaBalanceamento(umNoh);
}//fim insercao recursiva

Noh* AVL::arrumaBalanceamento(Noh* umNoh) {
    if(umNoh == NULL){
        return umNoh;
    }
    //percorrePosOrdem(2);

    int fatorBal = umNoh->fatorBalanceamento(umNoh);

    if((fatorBal >= -1) and (fatorBal <= 1)){
        return umNoh;
    }

    if(fatorBal > 1 and (umNoh->fatorBalanceamento(umNoh->esquerdo) >= 0)){
        return rotacaodireito(umNoh);
    }else if(fatorBal > 1 and (umNoh->fatorBalanceamento(umNoh->esquerdo) < 0)){
        umNoh->esquerdo = rotacaoesquerda(umNoh->esquerdo);
        return rotacaodireito(umNoh);
    }else if(fatorBal < -1 and (umNoh->fatorBalanceamento(umNoh->direito) <= 0)){
        return rotacaoesquerda(umNoh);
    }else if(fatorBal < -1 and (umNoh->fatorBalanceamento(umNoh->direito) > 0)){
        umNoh->direito = rotacaodireito(umNoh->direito);
        return rotacaoesquerda(umNoh);
    }
    return umNoh;
}

Noh* AVL::rotacaoesquerda(Noh* umNoh) {
    if(umNoh != NULL){ 
        Noh* aux = umNoh->direito;
        umNoh->direito = aux->esquerdo;
        aux->esquerdo = umNoh;
        cont+=2;

        umNoh->atualizaAltura(umNoh);
        umNoh->atualizaAltura(aux);

        return aux;
    }else
        return umNoh;
}

Noh* AVL::rotacaodireito(Noh* umNoh) {
    if(umNoh != NULL){
        Noh* aux = umNoh->esquerdo;
        umNoh->esquerdo = aux->direito;
        aux->direito = umNoh;
        cont+=2;

        umNoh->atualizaAltura(umNoh);
        umNoh->atualizaAltura(aux);

        return aux;
    }else
        return umNoh;
}

Noh* AVL :: buscaAux(int umValor){
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

int AVL :: minimo(){
    if(raiz == NULL){
        cerr << "arvore vazia" << endl;
        exit(EXIT_FAILURE);
    }else{
        Noh* NohMinimo = minimoAux(raiz);
        return NohMinimo->mValor;
    }
}

Noh* AVL :: minimoAux(Noh* raizSubArvore){
    if(raizSubArvore->esquerdo != NULL and raizSubArvore != NULL){
        raizSubArvore = minimoAux(raizSubArvore->esquerdo);
    }
    return raizSubArvore;
}

int AVL :: maximo(){
    if(raiz == NULL){
        cerr << "arvore vazia" << endl;
        exit(EXIT_FAILURE);
    }else{
        Noh* NohMaximo = maximoAux(raiz);
        return NohMaximo->mValor;
    }
}

Noh* AVL :: maximoAux(Noh* raizSubArvore){
    while(raizSubArvore->direito != NULL ){
        raizSubArvore = raizSubArvore->direito;
    }
    return raizSubArvore;
}

void AVL ::percorreEmOrdem(){
    percorreEmOrdemAux(raiz);
}

void AVL ::percorreEmOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        percorreEmOrdemAux(umNoh->esquerdo);
        cout << umNoh->mValor << " ";
        percorreEmOrdemAux(umNoh->direito);
    }
}

void AVL ::percorrePreOrdem(){
    percorrePreOrdemAux(raiz);
}

void AVL ::percorrePreOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        cout << umNoh->mValor << " ";
        percorrePreOrdemAux(umNoh->esquerdo);
        percorrePreOrdemAux(umNoh->direito);
    }
}

void AVL ::percorrePosOrdem(){
    percorrePosOrdemAux(raiz);
}

void AVL ::percorrePosOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        percorrePosOrdemAux(umNoh->esquerdo);
        percorrePosOrdemAux(umNoh->direito);
        delete umNoh;
    }
}

void AVL:: sucessor(Noh* Noh){
    Noh = minimoAux(Noh->direito);
    cout << Noh->mValor;
}

void AVL :: removerRecursivamente(int umValor){
    raiz = removerRecAux(raiz,umValor);
}

Noh* AVL :: removerRecAux(Noh* umNoh,int umValor){
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
        return arrumaBalanceamento(novaRaizSubArvore);
    }
}

Noh* AVL :: removeMenor(Noh* raizSub){
    if(raizSub->esquerdo == NULL){
        return raizSub->direito;
    }else{
        raizSub->esquerdo = removeMenor(raizSub->esquerdo);
    }
    return raizSub;
}

int main(){
    AVL ar;
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