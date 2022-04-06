#ifndef HASH_H
#define HASH_H

#include "ListaEncadeada.h"
#include "Termo.h"
#include "Documento.h"
#include <cmath>

//constante para mapeamento hashing
#define P 3

/**
* -Descricao: Esta classe implementa um par ordenado que contem,
*  respetivamente, idDocumento e frequencia
*/
class Hash{
    public:
        Hash();
        Hash(int _M);
        bool Pesquisa(std::string palavra);
        void Insere(Termo novoTermo);
        Termo* ObtemTermo(std::string palavra);
        float calcula_w_td(std::string t, int d, int D);
        float calcula_Wd(Documento d, int D);

    private:
        /**
        * -Descricao: mapeia uma string para um inteiro,
        *  que sera indice do vetor tabela
        * -Entrada: palavra
        * -Saida: map
        */
        long unsigned int hashing(std::string palavra){
            long unsigned int map =0;

            for(int i=0; i<(int)palavra.size(); i++){
                map += (palavra[i]*pow(P,i));
            }
            map = map % M;
            
            return map;
        }

        ListaEncadeada<Termo> *tabela;
        int M;
};

/**
* -Descricao: Construtor vazio
* -Entrada: N/A
* -Saida: N/A
*/
Hash::Hash(){}

/**
* -Descricao: Construtor
* -Entrada: N/A
* -Saida: N/A
*/
Hash::Hash(int _M){
    M = _M;
    tabela = new ListaEncadeada<Termo>[_M];
}

/**
* -Descricao: pesquisa um elemento no Hash
* -Entrada: palavra
* -Saida: true (caso o elemento esteja na lista)
*         false (caso o elemento nao esteja na lista)
*/
bool Hash::Pesquisa(std::string palavra){
    Termo _termo;
    _termo.SetTermo(palavra);
    int pos;
    bool encontrado;
    pos = hashing(palavra); 
    encontrado = tabela[pos].Contem(_termo);
    return encontrado;
}

/**
* -Descricao: insere novoTermo no Hash
* -Entrada: novoTermo
* -Saida: N/A
*/
void Hash::Insere(Termo novoTermo){
    int pos;
    erroAssert(!Pesquisa(novoTermo.GetTermo()), "Erro: Item já está presente");

    pos = hashing(novoTermo.GetTermo());
    tabela[pos].InsereFinal(novoTermo);
}

/**
* -Descricao: retorna termo correspondente a palavra, caso esteja na lista
* -Entrada: palavra
* -Saida: true (caso o elemento esteja na lista)
*         false (caso o elemento nao esteja na lista)
*/
Termo* Hash::ObtemTermo(std::string palavra){
    //verifica se o termo correspondente a palavra esta no hash
    erroAssert(Pesquisa(palavra), 
    "ERRO: Termo correspondente a palavra nao esta no hash");

    Termo aux;
    aux.SetTermo(palavra);

    int pos;
    pos = hashing(palavra);

    Termo *_termo;
    _termo = tabela[pos].ObtemElemento(aux);

    return _termo;
}

/**
* -Descricao: calcula o peso do termo t no documento de id d
* -Entrada: t, d, D(numero de documentos do corpus)
* -Saida: w_td
*/
float Hash::calcula_w_td(std::string t, int d, int D){
    //caso t seja string vazia, o peso w_td sera 0
    if(t == "") return 0;

    Termo *aux;
    IndiceInvertido idc;
    IndiceInvertido *requerido;

    idc.SetIdDocumento(d);
    aux = ObtemTermo(t);
    requerido = aux->GetIndices()->ObtemElemento(idc);
    float frequencia_t_d = requerido->GetFrequencia();
    float f_t = aux->GetIndices()->GetTamanho();

    return frequencia_t_d*(std::log(D/f_t));
}

/**
* -Descricao: calcula o parametro Wd para o documento d
* -Entrada: d, D(numero de documentos do corpus)
* -Saida: Wd
*/
float Hash::calcula_Wd(Documento d, int D){
    float Wd = 0;

    Celula <std::string> *p;
    p = d.GetVocabularioLocal()->GetPrimeiro()->GetProx();
    
    //para cada palavra do vocabulario local,
    //Wd eh somado do quadrado do coef w_td correspondente
    while (p != nullptr) {
        Wd += pow(calcula_w_td(p->GetItem(), d.GetId(), D),2);
        
        p = p->GetProx();
    }

    return sqrt(Wd);
}

#endif