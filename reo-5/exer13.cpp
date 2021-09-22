/* avl - Árvore Binária de Busca com Balanceamento AVL
 *
 * by Joukim, Outubro de 2020 - Estrutura de Dados (GCC216)
 * Caracteristicas de implementação outubro de 2019:
 * -> tratamento de exceção
 * -> usa dado na forma chave/valor
 * -> uso de métodos recursivos
 * -> sem duplo encadeamento
 * -> invés de transplanta, usa removeMenor
 */

#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;
#include <stdexcept>

struct dado {
    unsigned ano; // ano é a chave para ordenação na AVL
    string cidadeRealizacao;
    unsigned qtdadeFilmesApresentados;   
};

ostream& operator<<(ostream& saida, const dado& e) {
    saida << "(" << e.ano << "," << e.cidadeRealizacao << "," << e.qtdadeFilmesApresentados << ")";
    return saida;
}

istream& operator>>(istream& entrada, dado& e) {
    entrada >> e.ano >> e.cidadeRealizacao >> e.qtdadeFilmesApresentados;
    return entrada;
}
typedef unsigned tipoChave;

class noh {
    friend class avl;
    private:
        dado elemento;
        noh* esq;
        noh* dir;
        unsigned altura;
    public:
        noh(const dado& umDado):
            elemento(umDado),  esq(NULL), dir(NULL), altura(1) { }
        ~noh() { }
        int fatorBalanceamento(noh* umNoh);
        int informaAltura(noh* umNoh);
        void atualizaAltura(noh* umNoh);
};

int noh::fatorBalanceamento(noh* umNoh) {
    if(umNoh != NULL){
        int altArvEsq = informaAltura(umNoh->esq);
        int altArvDir = informaAltura(umNoh->dir);
        int fatorBal = altArvEsq - altArvDir;
        return fatorBal;
    }else
        return 0;

}

int noh::informaAltura(noh* umNoh){
    if(umNoh == NULL)
        return 0;
    else
        return umNoh->altura;
}

void noh::atualizaAltura(noh* umNoh){
    if(umNoh != NULL){
        int altArvEsq = informaAltura(umNoh->esq);
        int altArvDir = informaAltura(umNoh->dir);
        umNoh->altura = 1 + fmax(altArvEsq, altArvDir);
    }
}

class avl {
    friend ostream& operator<<(ostream& output, avl& arvore);
    private:
        noh* raiz;
        // percorrimento em ordem da árvore
        void percorrePosOrdemAux(int opcao,noh* umNoh);
        dado percorreEmOrdemAux(noh* umNoh,dado &d);
        // funções auxiliares para remoção
        noh* encontraMenor(noh* raizSub);
        noh* removeMenor(noh* raizSub);
        // funções auxiliares para inserção e remoção usando método recursivo
        // retorna o nó para ajustar o pai ou o raiz
        noh* insereAux(noh* umNoh, const dado& umDado);
        noh* removeAux(noh* umNoh, tipoChave chave);
        // métodos para manutenção do balanceamento
        noh* rotacaoEsquerda(noh* umNoh);
        noh* rotacaoDireita(noh* umNoh);
        noh* arrumaBalanceamento(noh* umNoh);
        // busca, método iterativo
        noh* buscaAux(tipoChave chave);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* meuNoh);
        void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);
        //void levantamentoAux(noh* umNoh, unsigned* ptrAnoProcurado, unsigned* ptrMaiorNumFilmesApres);
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();
        // inserção e remoção são recursivos
        void insere(const dado& umDado);
        void remove(tipoChave chave);
        // inserção e remoção, métodos recursivos
        // busca retorna uma cópia do objeto armazenado
        dado busca(tipoChave chave);
        // efetua levantamento do ano com maior número de filmes apresentados
        unsigned levantamento();
        void acao(int opcao,noh* umNoh);
        void percorreEmOrdem2();
        void percorreEmOrdemAux2(noh* umNoh);
};

// destrutor
avl::~avl() {
    percorrePosOrdemAux(1,raiz);
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::percorrePosOrdemAux(int opcao,noh* umNoh) {
    if(umNoh != NULL){
        percorrePosOrdemAux(opcao,umNoh->esq);
        percorrePosOrdemAux(opcao,umNoh->dir);
        acao(opcao,umNoh);
    }
}

void avl::insere(const dado& umDado) {
    raiz = insereAux(raiz, umDado);
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux(noh* umNoh, const dado& umDado) {
    if(umNoh == NULL){
        noh* novo = new noh(umDado);
        return novo;
    }else{
        if(umDado.ano < umNoh->elemento.ano){
            umNoh->esq = insereAux(umNoh->esq,umDado);
        }else{
            umNoh->dir = insereAux(umNoh->dir,umDado);
        }
    }
    return arrumaBalanceamento(umNoh);
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários
noh* avl::arrumaBalanceamento(noh* umNoh) {
    if(umNoh == NULL){
        return umNoh;
    }
    percorrePosOrdemAux(2,raiz);

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
    return umNoh;
}


// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoEsquerda(noh* umNoh) {
    if(umNoh != NULL){ 
        noh* aux = umNoh->dir;
        umNoh->dir = aux->esq;
        aux->esq = umNoh;

        umNoh->atualizaAltura(umNoh);
        umNoh->atualizaAltura(aux);

        return aux;
    }else
        return umNoh;
}


// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoDireita(noh* umNoh) {
    if(umNoh != NULL){
        noh* aux = umNoh->esq;
        umNoh->esq = aux->dir;
        aux->dir = umNoh;

        umNoh->atualizaAltura(umNoh);
        umNoh->atualizaAltura(aux);

        return aux;
    }else
        return umNoh;
}


// método de busca auxiliar (retorna o nó), iterativo
noh* avl::buscaAux(tipoChave chave) {
    noh* atual = raiz;
    while(atual != NULL){
        if(atual->elemento.ano == chave){
            return atual;
        }else if(atual->elemento.ano > chave){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }
    return atual;
}
// busca elemento com uma dada chave na árvore e retorna o registro completo
dado avl::busca(tipoChave chave) {
    noh* resultado = buscaAux(chave);
    if (resultado != NULL)
        return resultado->elemento;
    else
        throw runtime_error("Erro na busca: elemento não encontrado!");
}


// nó mínimo (sucessor) de subárvore com raiz em raizSub (folha mais à esquerda)
noh* avl::encontraMenor(noh* raizSub) {
    if(raizSub->esq != NULL and raizSub != NULL){
        raizSub = encontraMenor(raizSub->esq);
    }
    return raizSub;
}

// procedimento auxiliar para remover o sucessor substituíndo-o pelo
// seu filho à direita
noh* avl::removeMenor(noh* raizSub) {
    if(raizSub->esq == NULL){
        return raizSub->dir;
    }else{
        raizSub->esq = removeMenor(raizSub->esq);
        return arrumaBalanceamento(raizSub);
    }
}

// remoção recursiva
void avl::remove(tipoChave chave) {
    raiz = removeAux(raiz, chave);
}

noh* avl::removeAux(noh* umNoh, tipoChave chave) {
    noh* novaRaizSubArvore = umNoh;
    if(chave < umNoh->elemento.ano){
        umNoh->esq = removeAux(umNoh->esq,chave);
    }else if(chave > umNoh->elemento.ano){
        umNoh->dir = removeAux(umNoh->dir, chave);
    }else{
        if(umNoh->esq == NULL){
            novaRaizSubArvore = umNoh->dir;
        }else if(umNoh->dir == NULL){
            novaRaizSubArvore = umNoh->esq;
        }else{
            novaRaizSubArvore = encontraMenor(umNoh->dir);
            novaRaizSubArvore->dir =removeMenor(umNoh->dir);
            novaRaizSubArvore->esq = umNoh->esq;
        }
        delete umNoh;
    }
    return arrumaBalanceamento(novaRaizSubArvore);
}


// compara os elementos da AVL
dado avl::percorreEmOrdemAux(noh* umNoh,dado &d) {
    if(umNoh != NULL){
        percorreEmOrdemAux(umNoh->esq,d);
        if(d.qtdadeFilmesApresentados < umNoh->elemento.qtdadeFilmesApresentados){
            d = umNoh->elemento;
        }
        percorreEmOrdemAux(umNoh->dir,d);
    }
    return d;
}

ostream& operator<<(ostream& output, avl& arvore) {
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirDir(const std::string& prefixo, const noh* meuNoh)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << meuNoh->elemento.ano << "," << meuNoh->elemento.cidadeRealizacao << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    " , meuNoh->esq , meuNoh->dir==nullptr );
        imprimirDir( prefixo + "    " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo ;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─" ;
        else
            std::cout << "├e─";

        std::cout << "(" << meuNoh->elemento.ano << "," << meuNoh->elemento.cidadeRealizacao << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   " , meuNoh->esq, meuNoh->dir==nullptr );
        imprimirDir( prefixo + "│   " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir()
{
    if( this->raiz != nullptr )
    {
        std::cout << "(" << this->raiz->elemento.ano << "," << this->raiz->elemento.cidadeRealizacao << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->esq, this->raiz->dir==nullptr );
        imprimirDir( " " , this->raiz->dir );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

void avl::acao(int opcao,noh* umNoh){//decida qual acao sera realizada no metodo percorrePosOrdemAux (deletar ou atualizar)
    if(opcao == 1)
        delete umNoh;
    else
        umNoh->atualizaAltura(umNoh);
}

unsigned avl::levantamento(){
    dado d;
    d.ano = 0;
    d.qtdadeFilmesApresentados = 0;
    d = percorreEmOrdemAux(raiz,d);
    return d.ano;
}

void avl ::percorreEmOrdem2(){
    percorreEmOrdemAux2(raiz);
}

void avl ::percorreEmOrdemAux2(noh* umNoh){
    if(umNoh != NULL){
        percorreEmOrdemAux2(umNoh->esq);
        cout << umNoh->elemento.ano << " ";
        percorreEmOrdemAux2(umNoh->dir);
    }
}

int main() {
    avl arvore;
    tipoChave chave;
    dado umDado;
    unsigned ano;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe nome, cidade e quantidade de filmes apresentados
                    cin >> umDado;
                    arvore.insere(umDado);
                    break;
                case 'r': // Remover recursivamente
                    cin >> chave;
                    arvore.remove(chave);
                    break;
                case 'b': // Buscar
                    cin >> chave; // ler a chave
                    umDado = arvore.busca(chave); // escrever os dados do festival
                    cout << "Elemento buscado: " << umDado << endl;
                    break;
                case 'l': // Levantamento pelo ano com maior número de filmes apresentados
                    ano = arvore.levantamento( );
                    cout << "Edição com maior quantidade de filmes apresentados: " << ano << endl;
                    break;
                case 'e': // Escrever tudo (em ordem)
                    cout << arvore;
                    //arvore.percorreEmOrdem2();
                    break;
                case 'f': // Finalizar execução
                    break;
                default:
                    cout << "Comando invalido!\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (operacao != 'f');

    return 0;
}
