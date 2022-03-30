#include <string>
#include <iostream>

typedef char TipoDeItem;

struct Node{
  TipoDeItem valor;
  Node* proximo;
};

class Pilha{
  public:
    Pilha();  //construtor
    ~Pilha(); //destrutor
    bool vazio(); //lista vazia
    bool cheio(); //verifica se o computador tem memoria suficiente para mais elementos
    void inserir (TipoDeItem item); //push
    TipoDeItem remover(); //pop
    void imprimir(); // imprime na tela


  private:
    Node* noTopo;


};