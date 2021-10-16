#include <iostream>
#include <string>
using namespace std;

/* 1 - Os valores utilizados para definir o tamanho dos arranjos , em lista de artistas e de entusiastas
  foram definidos aleatoriamentede formma para exemplificaçao.

  2 - foi adicionado o metodo "novoArtista" à classe artistas e "novoEntusiasta" na classe Entusiasta.

  3 - foi adicionado o metodo "nome" na clase Artistas que retorna os valores das variaveis da classe.
*/

class Artistas
{
    private:
        string nome_artista;
        string telefone_artista;
        string endereco_artista;
    public:
        Artistas(/* args */);
        ~Artistas();
        void novoArtista();

        string *nome(Artistas x)
        {
            string *dados = new string[3];
            dados[0] = x.nome_artista;
            dados[1] = x.telefone_artista;
            dados[2] = x.endereco_artista;
            return dados;
        }
};

Artistas::Artistas(/* args */)
{
    nome_artista.clear();
    telefone_artista.clear();
    endereco_artista.clear();
}

Artistas::~Artistas()
{
    nome_artista.clear();
    telefone_artista.clear();
    endereco_artista.clear();
}

void Artistas::novoArtista()
{
    cin.ignore();
    cout << "nome: ";
    getline(cin,nome_artista);
    cout << "telefone: ";
    cin >> telefone_artista;
    cin.ignore();
    cout << "endereco: ";
    getline(cin,endereco_artista);
}

class Entusiasta
{
    private:
        string nome_entusiasta;
        string email_entusiasta;
        string nome_ultima_obra;
        float valor_ultima_obra;
    public:
        Entusiasta();
        ~Entusiasta();
        void novoEntusiastas();
};

Entusiasta::Entusiasta()
{
    nome_entusiasta.clear();
    email_entusiasta.clear();
    nome_ultima_obra.clear();
    valor_ultima_obra = 0;
}

Entusiasta::~Entusiasta()
{
    nome_entusiasta.clear();
    email_entusiasta.clear();
    nome_ultima_obra.clear();
    valor_ultima_obra = 0;
}

void Entusiasta::novoEntusiastas()
{
    cin.ignore();
    cout << "nome: ";
    getline(cin,nome_entusiasta);
    cout << "email: ";
    cin >> email_entusiasta;
    cout << "nome da ultima obra: ";
    cin.ignore();
    getline(cin,nome_ultima_obra);
    cout << "valor da ultima obra: ";
    cin >> valor_ultima_obra;
}

class Exposicao
{
    private:
        Entusiasta *entusiasta_participantes;
        Artistas *artistas_participantes;
    public:
        Exposicao(/* args */);
        ~Exposicao();
        int cadastrarArtista(int ultima_pos);
        void buscarDados(string artista_procurado);
        int CadastrarEntusiasta(int ultima_pos);
};

Exposicao::Exposicao(/* args */)
{
    entusiasta_participantes = new Entusiasta[20];
    artistas_participantes = new Artistas[20];
}

Exposicao::~Exposicao()
{
    delete [] entusiasta_participantes;
    delete [] artistas_participantes;
}

int Exposicao::cadastrarArtista(int ultima_pos)
{
    if (ultima_pos < 19)
    {
        artistas_participantes[ultima_pos+1].novoArtista();
    }else
    {
        cout << "limite atingido" << endl;
    }
    
    return ultima_pos+1;
}

void Exposicao::buscarDados(string artista_procurado)
{
    for (int i = 0; i < 20; i++)
    {
        Artistas x;
        if (x.nome(artistas_participantes[i])[0] == artista_procurado)
        {
           cout << x.nome(artistas_participantes[i])[0] << " - " << x.nome(artistas_participantes[i])[1] << " - ";
           cout << x.nome(artistas_participantes[i])[2] << endl;
           i = 21;

        }else if (i== 19)
            cout << "Artista nao encontrado" << endl;
    }
}

int Exposicao::CadastrarEntusiasta(int ultima_pos)
{
    if (ultima_pos < 19)
    {
        entusiasta_participantes[ultima_pos+1].novoEntusiastas();
    }else
    {
        cout << "limite atingido" << endl;
    }
    
    return ultima_pos+1;
}

int main(){
    int ultima_posicao_artista=0;
    int ultima_pos_entusiasta=0;
    Exposicao x;
    int resposta;

    do
    { 
        string nomeArtista;

        cout << "Escolha uma opcao: 1- Cadastrar Artista | 2- Cadastrar Entusiasta | 3- Buscar Artista" << endl;
        cin >> resposta;

        switch (resposta)
        {
        case 1:
            ultima_posicao_artista = x.cadastrarArtista(ultima_posicao_artista);
            break;
        case 2:
            ultima_pos_entusiasta = x.CadastrarEntusiasta(ultima_pos_entusiasta);
            break;
        case 3:
            cin.ignore();
            cout << "Nome do artista procurado: ";
            getline(cin,nomeArtista);
            x.buscarDados(nomeArtista);
        
        default:
            break;
        }

    } while (resposta < 4);
}
