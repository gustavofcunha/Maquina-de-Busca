#ifndef TERMO_H
#define TERMO_H

#include <string>
#include "IndiceInvertido.h"
#include "ListaEncadeada.h"

/**
* -Descricao: Esta classe representa um termo (string) e
*  possui seus respetivos indices invertidos encadeados em uma lista
*/
class Termo{
    public:
        Termo();
        ~Termo();
        std::string GetTermo();
        ListaEncadeada<IndiceInvertido>* GetIndices();
        void SetTermo(std::string _termo);
        bool operator==(Termo _termo);
        void Imprime();

    private:
        std::string termo;
        ListaEncadeada <IndiceInvertido> *indices;
};

/**
* -Descricao: construtor padrao da classe Termo
* -Entrada: N/A
* -Saida: N/A
*/
Termo::Termo(){
    termo = "";
    indices = new ListaEncadeada<IndiceInvertido>();
}

/**
* -Descricao: destrutor da classe Termo
* -Entrada: N/A
* -Saida: N/A
*/
Termo::~Termo(){}

/**
* -Descricao: getter do atributo termo
* -Entrada: N/A
* -Saida: termo
*/
std::string Termo::GetTermo(){
    return termo;
}

/**
* -Descricao: getter do atributo indices
* -Entrada: N/A
* -Saida: indices
*/
ListaEncadeada <IndiceInvertido>* Termo::GetIndices(){
    return indices;
}

/**
* -Descricao: setter do atributo termo
* -Entrada: _termo
* -Saida: N/A
*/
void Termo::SetTermo(std::string _termo){
    termo = _termo;
}

/**
* -Descricao: definicao do operador de igualdade para a classe Termo
* -Entrada: _termo
* -Saida: true (se igual)
          false (se diferente)
*/
bool Termo::operator==(Termo _termo){
    if(termo == _termo.GetTermo()) return true;
    return false;
}

/**
* -Descricao: imprime a estrutura de dados
* -Entrada: N/A
* -Saida: impressao na saida padrao std::cout
*/
void Termo::Imprime(){
    std::cout << std::endl << "[" << termo << "] => ";
    indices->Imprime();
}

#endif