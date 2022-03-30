#include <iostream>
#include "Fila.h"
#include <cstddef>
#include <new>

using namespace std;

Fila::Fila()  //construtor
{
  primeiro = NULL;
  ultimo = NULL;
}

Fila::~Fila() //destrutor
{
  No* temporario;
  while(primeiro != NULL){
    temporario = primeiro;
    primeiro = primeiro->proximo;
    primeiro->anterior = NULL;
    delete temporario;
  }
  ultimo = NULL;
}

bool Fila::vazio() //lista vazia
{
  return (primeiro == NULL);
}

bool Fila::cheio() //verifica se o computador tem memoria suficiente para mais elementos
{
  No* temporario;
  try{
    temporario = new No;
    delete temporario;
    return false;
  }catch(bad_alloc exception){
    return true;
  }
}

void Fila::inserir (TipoDeItem item) //push
{
  if (cheio()){
    cout << "Fila cheia!" << endl;
    cout << "Nao foi possivel inserir" << endl;
  }else{
    No* noNovo = new No;
    noNovo->valor = item;
    noNovo->proximo = NULL;
    noNovo->anterior = NULL;
    if(primeiro == NULL){
      primeiro = noNovo;
    }else{
      noNovo->anterior = ultimo;
      ultimo->proximo = noNovo;
    }
    ultimo = noNovo;
  }
}

TipoDeItem Fila::remover() //pop
{
  if(vazio()){
    cout << "Fila vazia!" << endl;
    cout << "Nao tem elemento para remover!" << endl;
    return 0;
  }else{
    No* temporario = primeiro;
    TipoDeItem item = primeiro->valor;
    primeiro = primeiro->proximo;
    if (primeiro == NULL){
      ultimo = NULL;
      delete temporario;
      return item;
    }
    primeiro->anterior = NULL;
    delete temporario;
    return item;
  }
}

void Fila::imprimir() // imprime na tela
{
  No* temporario = primeiro;
  cout << "Fila = [ ";
  while(temporario != NULL){
    cout << temporario->valor << " ";
    temporario = temporario->proximo;
  }
  cout << "]" << endl<<endl;
}