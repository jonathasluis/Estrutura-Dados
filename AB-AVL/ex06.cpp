#include <iostream>
#include <queue>
#include <cmath>

typedef int Dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    public:
        Noh (Dado d);
        //~Noh();
        // Verifica se existe sucessor e retorna o valor sucessor, se existir.
        //bool Sucessor(Dado* ptResultado); //(foi utilizado apenas o da classe ABB)
        //"MenorRecursivo" e "FilhoDaDireita" foram movidas para a classe ABB
        int fatorBalanceamento(Noh* umNoh);
        int informaAltura(Noh* umNoh);
        void atualizaAltura(Noh* umNoh);
        
    private:
        Dado valor;
        Noh* esq;
        Noh* dir;
        Noh* pai;
        unsigned altura;
};

class ABB {
    public:
        ABB() { raiz = NULL; }
        ~ABB();
        // Retorna um ponteiro para o nÃ³ de uma chave, ou NULL.
        Noh* Busca(Dado d);
        // Escreve uma Ã¡rvore nÃ­vel a nÃ­vel.
        void EscreverNivelANivel(std::ostream& saida);
        // Insere um dado na Ã¡rvore.
        Noh* Inserir(Noh* umNoh,Dado d);
        // Verifica se um dado tem sucessor e o retorna.
        bool Sucessor(Dado d, Dado* ptResultado);
        Noh* rotacaoEsquerda(Noh* umNoh);
        Noh* rotacaoDireita(Noh* umNoh);
        Noh* arrumaBalanceamento(Noh* umNoh);
        void insere(const Dado& umDado);
    private:
        Noh* raiz;
        void percorrePosOrdemAux(Noh* umNoh);
        // Retorna a menor chave de uma sub-Ã¡rvore.
        Noh* MenorRecursivo(Noh* subArvore);
        // Verifica se um nÃ³ Ã© filho da direita do pai.
        bool FilhoDaDireita(Noh* umNoh);
        Noh* ancestralDireito(Noh* umNoh);
};

using namespace std;
// === Classe Noh ==============================================================
Noh::Noh(Dado d) {
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

/*Noh::~Noh() {
    // implementar Destrutor recursivo!
    // o destrutor recursivo foi implementado no destrutor da ABB
}*/

// === Classe ABB ==============================================================
ABB::~ABB(){
    percorrePosOrdemAux(raiz);
}

void ABB ::percorrePosOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        percorrePosOrdemAux(umNoh->esq);
        percorrePosOrdemAux(umNoh->dir);
        umNoh->atualizaAltura(umNoh);
    }
}

bool ABB::FilhoDaDireita(Noh* umNoh) {
    // implementar
    if(umNoh->dir == NULL)
        return false;
    else
        return true;
}

Noh* ABB::MenorRecursivo(Noh* subArvore) {
    // implementar
    if(subArvore != NULL and subArvore->esq != NULL){
        subArvore = MenorRecursivo(subArvore->esq);
    }
    return subArvore;
}

void ABB::insere(const Dado& umDado) {
    raiz = Inserir(raiz, umDado);
}

Noh* ABB::Inserir(Noh* umNoh,Dado d) {
    // implementar
    if(umNoh == NULL){
        Noh* novo = new Noh(d);
        return novo;
    }else{
        if(d < umNoh->valor){
            umNoh->esq = Inserir(umNoh->esq,d);
        }else{
            umNoh->dir = Inserir(umNoh->dir,d);
        }
    }
    percorrePosOrdemAux(umNoh);
    return arrumaBalanceamento(umNoh);
    
}

bool ABB::Sucessor(Dado d, Dado* ptResultado) {
    // implementar
    Noh* raizSub = Busca(d);

    if(FilhoDaDireita(raizSub)){
        raizSub = MenorRecursivo(raizSub->dir);
        *ptResultado = raizSub->valor;
        return true;
    }else{
        raizSub = ancestralDireito(raizSub);
        if(raizSub != NULL){
            *ptResultado = raizSub->valor;
            return true;
        }else
            return false;
    }
}

Noh* ABB:: ancestralDireito(Noh* umNoh) {
    if (umNoh == NULL){
        return NULL;
    }else if (umNoh->pai == NULL or umNoh->pai->esq == umNoh){
        return umNoh->pai;
    }else{
        return ancestralDireito(umNoh->pai);
    } 
}

Noh* ABB::Busca(Dado d) {
    // implementar
    Noh* atual = raiz;
    while(atual != NULL){
        if(atual->valor == d){
            return atual;
        }else if(atual->valor > d){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }
    return atual;
}

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh noh = Dado();
    Noh* fimDeNivel = &noh; // noh especial para fim de nivel
    filhos.push(raiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        Noh* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << '[';
            if (ptNoh != NULL) {
                saida << ptNoh->valor;
                filhos.push(ptNoh->esq);
                filhos.push(ptNoh->dir);
            }
            saida << ']';
        }
    }
}

Noh* ABB::arrumaBalanceamento(Noh* umNoh) {
    if(umNoh == NULL){
        return umNoh;
    }
    umNoh->atualizaAltura(umNoh);

    int fatorBal = umNoh->fatorBalanceamento(umNoh);

    if((fatorBal >= -1) and (fatorBal <= 1)){
        return umNoh;
    }

    if(fatorBal > 1 and (umNoh->fatorBalanceamento(umNoh->esq) >= 0)){
        return rotacaoDireita(umNoh);
    }else if(fatorBal > 1 and (umNoh->fatorBalanceamento(umNoh->esq) < 0)){
        umNoh->esq = rotacaoEsquerda(umNoh->esq);
        return rotacaoDireita(umNoh);
    }else if(fatorBal < -1 and (umNoh->fatorBalanceamento(umNoh->dir) <= 0)){
        return rotacaoEsquerda(umNoh);
    }else if(fatorBal < -1 and (umNoh->fatorBalanceamento(umNoh->dir) > 0)){
        umNoh->dir = rotacaoDireita(umNoh->dir);
        return rotacaoEsquerda(umNoh);
    }
    //return umNoh;
}


// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
Noh* ABB::rotacaoEsquerda(Noh* umNoh) {
    Noh* aux = umNoh->dir;
    umNoh->dir = aux->esq;
    aux->esq = umNoh;

    umNoh->atualizaAltura(umNoh);
    umNoh->atualizaAltura(aux);

    return aux;
}


// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
Noh* ABB::rotacaoDireita(Noh* umNoh) {
    Noh* aux = umNoh->esq;
    umNoh->esq = aux->dir;
    aux->dir = umNoh;

    umNoh->atualizaAltura(umNoh);
    umNoh->atualizaAltura(aux);

    return aux;
}

int Noh::fatorBalanceamento(Noh* umNoh) {
    int altArvEsq = informaAltura(umNoh->esq);
    int altArvDir = informaAltura(umNoh->dir);
    int fatorBal = altArvEsq - altArvDir;
    return fatorBal;
}

int Noh::informaAltura(Noh* umNoh){
    if(umNoh == NULL)
        return 0;
    else
        return umNoh->altura;
}

void Noh::atualizaAltura(Noh* umNoh){
    int altArvEsq = informaAltura(umNoh->esq);
    int altArvDir = informaAltura(umNoh->dir);
    umNoh->altura = 1 + fmax(altArvEsq, altArvDir);
}

// === Programa ================================================================
int main() {
    ABB arvore;
    Dado chave;
    char operacao;

    // === TESTE ===============================================================*
    /*int c[6] = {300,20,12,430,360,451};

    for (int i = 0;i<6;i++){
        arvore.Inserir(c[i]);
    }*/
    // === FIM TESTE ===========================================================

    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> chave;
                arvore.insere(chave);
                break;
            case 'e': // Escrever
                arvore.EscreverNivelANivel(cout);
                break;
            case 's': { // Sucessor
                cin >> chave;
                Dado sucessor;
                while (arvore.Sucessor(chave, &sucessor)) {
                    cout << sucessor << ' ';
                    chave = sucessor;
                }
                cout << endl;
                break;
            }
        }
    } while (operacao != 'f');
    return 0;
}