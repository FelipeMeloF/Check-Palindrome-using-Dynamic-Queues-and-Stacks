#include <string>
#include <iostream>

using namespace std;

typedef char TipoDeItem;

struct No{
  TipoDeItem valor;
  No* proximo;
  No* anterior;
};

class Fila{
  public:
    Fila();  //construtor
    ~Fila(); //destrutor
    bool vazio(); //lista vazia
    bool cheio(); //verifica se o computador tem memoria suficiente para mais elementos
    void inserir (TipoDeItem item); //push
    TipoDeItem remover(); //pop
    void imprimir(); // imprime na tela

  private:
    No* primeiro;
    No* ultimo;
};
