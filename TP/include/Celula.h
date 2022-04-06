#ifndef CELULA_H
#define CELULA_H

/**
* -Descricao: Esta classe implementa celulas que serao usadas em listas
* e filas. Possui itens do tipo T.
*/
template <class T> 
class Celula {
    public:
        Celula();
        T GetItem();
        T* GetPonteiroItem();
        Celula<T>* GetProx();
        void SetProx(Celula<T>* _prox);
        void SetItem(T _item);
    
    public:
        T item;
        Celula<T>* prox;
};

/**
* -Descricao: construtor padrao
* -Entrada: N/A
* -Saida: N/A
*/
template <class T> 
Celula<T>::Celula(){
    prox = nullptr;
}

/**
* -Descricao: getter do atributo item
* -Entrada: N/A
* -Saida: item
*/
template <class T> 
T Celula<T>:: GetItem(){
    return item;
}

/**
* -Descricao: retorna um ponteiro para item
* -Entrada: N/A
* -Saida:pont
*/
template <class T> 
T* Celula<T>::GetPonteiroItem(){
    T* pont;
    pont = &item;
    return pont;
}

/**
* -Descricao: getter do atributo prox
* -Entrada: N/A
* -Saida: prox
*/
template <class T> 
Celula<T>* Celula<T>::GetProx(){
    return prox;
}

/**
* -Descricao: setter do atributo prox
* -Entrada: _prox
* -Saida: N/A
*/
template <class T> 
void Celula<T>::SetProx(Celula<T>* _prox){
    prox = _prox;
}

/**
* -Descricao: setter do atributo item
* -Entrada: _item
* -Saida: N/A
*/
template <class T> 
void Celula<T>::SetItem(T _item){
    item = _item;
}

#endif