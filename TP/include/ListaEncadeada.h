#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include <string>
#include <iostream>
#include "Celula.h"
#include "msgassert.h"

/**
* -Descricao: esta classe implementa uma lista encadeada (utiliza apontadores)
*  referente a um host que, por sua vez, possui urls contidos em strings em suas celulas
* -Obs: possui celula cabeca
*/

template <class T>
class ListaEncadeada{

    public:
        ListaEncadeada();
        ~ListaEncadeada();
        int GetTamanho();
        Celula<T>* GetPrimeiro();
        Celula<T>* Posiciona(int pos, bool antes);
        T GetItem(int pos);
        void InsereFinal(T item);
        void Limpa();
        bool Contem(T elemento);
        T* ObtemElemento(T elemento);
        void Imprime();

    private:
        int tamanho;
        Celula<T>* primeiro;
        Celula<T>* ultimo;
};

/**
* -Descricao: Construtor
* -Entrada: N/A
* -Saida: N/A
*/
template <class T>
ListaEncadeada<T>::ListaEncadeada(){
    tamanho = 0;
    primeiro = new Celula<T>;
    ultimo = primeiro;
}

/**
* -Descricao: Destrutor
* -Entrada: N/A
* -Saida: N/A
*/
template <class T>
ListaEncadeada<T>::~ListaEncadeada(){
    /*if(tamanho!=0){
        Limpa();
    }*/
}

/**
* -Descricao: retorna o tamanho da lista encadeada
* -Entrada: N/A
* -Saida: tamanho
*/
template <class T>
int ListaEncadeada<T>::GetTamanho(){
    return tamanho;
}

/**
* -Descricao: retorna ponteiro para a primeira celula da lista encadeada
* -Entrada: N/A
* -Saida: primeiro
*/
template <class T>
Celula<T>* ListaEncadeada<T>::GetPrimeiro(){
    return primeiro;
}

/**
* -Descricao: posiciona um ponteiro em pos
* tambem posiciona uma celula antes, caso antes = true 
* -Entrada: pos, antes
* -Saida: ponteiro para celula em pos
*/
template <class T>
Celula <T>* ListaEncadeada<T>::Posiciona(int pos, bool antes){
    //verifica se a posicao pos eh valida
    erroAssert(pos>0 && pos<=tamanho, "Posicao invalida");
    
    Celula <T>* p; 
    int i;
    
    //faz p apontar para a celula em pos-1
    
    p = primeiro;
    for(i=1; i<pos; i++){
        p = p->GetProx();
    }
    
    //faz p apontar para a celula em pos, caso antes == false
    if(!antes){
        p = p->GetProx();
    }

    return p;
}

/**
* -Descricao: retorna item na posicao pos
* -Entrada: pos
* -Saida: item na posicao pos
*/
template <class T>
T ListaEncadeada<T>::GetItem(int pos){
    //verifica se a posicao pos eh valida
    erroAssert(pos>0 && pos<=tamanho, "Posicao invalida");

    //apontador que recebe a celula na posicao pos
    Celula <T>* p;
    p = Posiciona(pos, false);

    return p->GetItem();
}

/**
* -Descricao: insere item no final da ListaEncadeada
* -Entrada: item
* -Saida: N/A
*/
template <class T>
void ListaEncadeada<T>::InsereFinal(T item){
    //criacao da nova celula
    Celula <T> *nova;
    nova = new Celula <T>();

    //insercao da nova celula no final e setagem de apontadores
    nova->SetItem(item);
    ultimo->SetProx(nova);
    ultimo = nova;
    
    tamanho++;
}

/**
* -Descricao: deleta todas as celulas da lista encadeada
* com excecao da celula cabeca (primeiro)
* -Entrada: N/A
* -Saida: N/A
*/
template <class T>
void ListaEncadeada<T>::Limpa(){
    //verifica se a lista esta vazia
    avisoAssert(tamanho>0, "Lista ja vazia");
    
    Celula <T> *p;
    //ponteiro para a primeira celula valida da lista
    p = primeiro->GetProx();
    
    //caminha pelas celulas da lista, deletando-as
    while (p!=NULL) {
        primeiro->SetProx(p->GetProx());
        delete p;
        p = primeiro->GetProx();
    }

    //setagem de atributos para configuracao de lista vazia
    ultimo = primeiro;
    tamanho = 0;
}

/**
* -Descricao: verifica se lista contem elemento
* -Entrada: elemento
* -Saida: true (caso elemento esteja na lista)
*         false (caso elemento nao esteja na lista)
*/
template <class T>
bool ListaEncadeada<T>::Contem(T elemento){
    Celula <T> *p;
    //ponteiro para a primeira celula valida da lista
    p = primeiro->GetProx();
    
    //caminha pelas celulas da lista procurando elemento
    while (p != nullptr) {
        if(p->GetItem() == elemento){
            return true;
        }
        p = p->GetProx();
    }

    return false;
}

/**
* -Descricao: retorna ponteiro para elemento, caso esteja na lista
* -Entrada: elemento
* -Saida:  ponteiro para elemento (caso elemento esteja na lista)
*/
template <class T>
T* ListaEncadeada<T>::ObtemElemento(T elemento){
    //verifica se o elemento esta na lista
    erroAssert(Contem(elemento), "ERRO: Elemento nao esta na lista");

    //ponteiro auxiliar
    Celula <T> *p;
    p = primeiro->GetProx();
    
    //caminha pelas celulas da lista procurando elemento
    //retorna ponteiro para element, quando o encontra
    while (p != nullptr) {
        if(p->GetItem() == elemento){
            return p->GetPonteiroItem();
        }
        p = p->GetProx();
    }
}

/**
* -Descricao: imprime a estrutura de dados
* -Entrada: N/A
* -Saida: impressao na saida padrao std::cout
*/
template <class T>
void ListaEncadeada<T>::Imprime(){
    //ponteiro auxiliar
    Celula <T> *p;
    p = primeiro->GetProx();
    
    //caminha pelas celulas da lista procurando elemento
    //retorna ponteiro para element, quando o encontra
    while (p != nullptr) {
        p->GetItem().Imprime();
        p = p->GetProx();
    }
}

#endif