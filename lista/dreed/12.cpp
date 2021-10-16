#include <iostream>
using namespace std;

class Noh{
    friend class lista;
    private:
        int chave;
        string palavra;
        Noh* proximo;
    public:
        Noh (int chaven,string palavra);
};

Noh::Noh(int chave,string palavra){
    this->chave = chave;
    this->palavra = palavra;
    proximo = NULL;
}

class lista{
    friend class hash;
    private:
        Noh* primeiro;
        Noh* ultimo;
        int tamanho;
        void removeTodos();
    public:
        lista();
        ~lista();
        void insereFim(int chave,string palavra);
        bool VerificaOcorrencia(int valor);
        inline bool vazia();
        void imprime();
        string buscaLista(int chave);
        void insereVazio();
};

lista :: lista(){//constroi lista vazia
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
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

void lista :: insereFim(int chave,string palavra){
    Noh* novo = new Noh(chave,palavra);

    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
       tamanho++;
    }else if((tamanho < 4) and VerificaOcorrencia(chave)){
        ultimo->proximo = novo;
        ultimo = novo;
        tamanho++;
    }else if((tamanho == 4) and (VerificaOcorrencia(chave))){
        cout << "NÚMERO MÁXIMO DE COLISÕES PARA CHAVE!" << endl;
    }else 
        cout << "ITEM JÁ ESTÁ NA TABELA!" << endl;
}

void lista ::insereVazio(){//insere nas posiçoes restantes o "-1"
    for (int i = tamanho; i < 4; i++)
    {
        insereFim(-1,"");
    }
    
}

bool lista :: VerificaOcorrencia(int valor){//verifica se a chave ja esta na lista
    Noh* aux = primeiro;
    bool resultado = true;

    if(valor != -1){
        while ((aux != NULL) and (aux->chave != valor)){
            aux = aux->proximo;
        }
    }
    
    if (aux == NULL){
        resultado = true;
    }else if(valor != -1)
        resultado = false;

    return resultado;
}

string lista :: buscaLista(int valor){//busca a chave informada e retorna o valor
    Noh* aux = primeiro;

    while ((aux != NULL) and (aux->chave != valor))
    {
        aux = aux->proximo;
    }
    if (aux == NULL){
        return "NÃO ENCONTRADO!";
    }else
        return aux->palavra;
}

void lista :: imprime(){//imprime os nós da lista
    Noh* aux = primeiro;

    for (int i=0;i<tamanho;i++)
    {
        cout << "[" << aux->chave << "/" << aux->palavra << "]";
        aux = aux->proximo;
    }
    
    cout << endl;
}

inline bool lista :: vazia(){
    return (tamanho == 0);
}


class Hash {
    private:
        int capacidade;//tamanho da tabela
        lista* tabela;
    public:
        Hash(int cap);
        ~Hash();
        int posicaoHash(int chave);
        void inserirHash(int chave, string palavra);
        string recuperacao(int chave);
        void mostra();
        void insereVazia();
};

Hash :: Hash(int cap)
{
    capacidade = cap;
    tabela = new lista[cap];
}

Hash :: ~Hash()
{
    delete[] tabela;
}

int Hash :: posicaoHash(int chave){//calcula a posicao
    return chave % capacidade;
}

void Hash :: inserirHash(int chave, string palavra){//insere o valor na lista da posicao calculada
    int posicao = posicaoHash(chave);
    tabela[posicao].insereFim(chave,palavra);
}

string Hash :: recuperacao(int valor){//recupera o valor de uma chave buscada
    int posicao = posicaoHash(valor);
    string palavra = tabela[posicao].buscaLista(valor);

    return palavra;
}

void Hash :: mostra(){//mostra os dados do vetor 
    for (int i = 0; i < capacidade; i++)
    {
        cout << i << ":";
        tabela[i].imprime();
    }
    
}

void Hash ::insereVazia(){//insere o -1
    for (int i = 0; i < capacidade; i++)
    {
        tabela[i].insereVazio();
    }
    
}

int main(){
    int capacidade;
    cin >> capacidade;
    Hash *hash = new Hash(capacidade);

    int quantidade;
    cin >> quantidade;
    int chave;
    string palavra;

    for (int i = 0; i < quantidade; i++)
    {
        cin >> chave >> palavra;
        hash->inserirHash(chave,palavra);
    }
    
    int chaveRecuperacao;
    for (int i = 0; i < 4; i++)
    {
        cin >> chaveRecuperacao;
        cout << hash->recuperacao(chaveRecuperacao);
        cout << endl;
    }
    
    hash->insereVazia();
    hash->mostra();
}