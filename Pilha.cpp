#include <iostream>
#include "Pilha.h"
#include <cstddef> //NULL

using namespace std;

Pilha::Pilha(){//construtor
  noTopo = NULL;
}

Pilha::~Pilha(){ //destrutor
  Node* noTemporario;
  while(noTopo != NULL){
    noTemporario = noTopo;
    noTopo = noTopo->proximo;
    delete noTemporario;
  }
}

bool Pilha::vazio(){ //lista vazia
  return (noTopo == NULL);
}

bool Pilha::cheio(){ //verifica se tem memoria suficiente
  Node* noNovo;
  //crio um novo no apenas para verificar se tem memoria
  try{
    noNovo = new Node;
    delete noNovo;
    return false;

  }catch(bad_alloc exception){
    return true;
  }
}

void Pilha::inserir (TipoDeItem item){ //push
  
  if (cheio()){
    cout << "Pilha cheia" << endl;
    cout << "Nao foi possivel inserir" << endl;
  }else{
    Node* noNovo = new Node;
    noNovo->valor = item;
    noNovo->proximo = noTopo;
    noTopo = noNovo;
  }
}

TipoDeItem Pilha::remover(){ //pop
  if (vazio()){
    cout << "Pilha vazia" << endl;
    cout << "Nao foi possivel remover" << endl;
    return 0;
  }else{
    Node* noTemporario;
    noTemporario = noTopo;
    TipoDeItem item = noTopo->valor;
    noTopo = noTopo->proximo;
    delete noTemporario;
    
    return item;
  }
}

void Pilha::imprimir(){ // imprime na tela
  Node* noTemporario = noTopo;
  cout << "Pilha: [ ";
  while (noTemporario != NULL){
    cout << noTemporario->valor << " ";
    noTemporario = noTemporario->proximo; 
  }
  cout << "]" << endl;
}