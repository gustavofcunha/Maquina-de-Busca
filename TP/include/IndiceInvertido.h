#ifndef INDICE_INVERTIDO_H
#define INDICE_INVERTIDO_H

/**
* -Descricao: Esta classe implementa um par ordenado que contem,
*  respetivamente, idDocumento e frequencia
*/
class IndiceInvertido{
    public:
        IndiceInvertido();
        int GetIdDocumento();
        int GetFrequencia();
        void SetIdDocumento(int _idDocumento);
        void SetFrequencia(int _frequencia);
        void IncrementaFrequencia();
        bool operator==(IndiceInvertido _indice);
        void Imprime();
    private:
        int idDocumento;
        int frequencia;
};

/**
* -Descricao: construtor padrao da classe IndiceInvertido
* -Entrada: N/A
* -Saida: N/A
*/
IndiceInvertido::IndiceInvertido(){
    idDocumento = -1;
    frequencia = -1;
}

/**
* -Descricao: getter do atributo idDocumento
* -Entrada: N/A
* -Saida: idDocumento
*/
int IndiceInvertido::GetIdDocumento(){
    return idDocumento;
}

/**
* -Descricao: getter do atributo frequencia
* -Entrada: N/A
* -Saida: frequencia
*/
int IndiceInvertido::GetFrequencia(){
    return frequencia;
}

/**
* -Descricao: setter do atributo idDocumento
* -Entrada: _idDocumento
* -Saida: N/A
*/
void IndiceInvertido::SetIdDocumento(int _idDocumento){
    idDocumento = _idDocumento;
}

/**
* -Descricao: setter do atributo frequencia
* -Entrada: _frequencia
* -Saida: N/A
*/
void IndiceInvertido::SetFrequencia(int _frequencia){
    frequencia = _frequencia;
}

/**
* -Descricao: incremeta em 1 unidade o atributo frequencia
* -Entrada: N/A
* -Saida: N/A
*/
void IndiceInvertido::IncrementaFrequencia(){
    frequencia++;
}

/**
* -Descricao: definicao do operador de igualdade para a classe IndiceInvertido
* -Obs: o criterio de igualdade para esta classe eh apenas avaliado pelo atributo
*  idDocumento, que eh distinto em todo o corpus
* -Entrada: _indice
* -Saida: true (se igual)
          false (se diferente)
*/
bool IndiceInvertido::operator==(IndiceInvertido _indice){
    if(idDocumento == _indice.GetIdDocumento()){
        return true;
    }
    return false;
}

/**
* -Descricao: imprime a estrutura de dados
* -Entrada: N/A
* -Saida: impressao na saida padrao std::cout
*/
void IndiceInvertido::Imprime(){
    std::cout << "(" << idDocumento << "," << frequencia << "), ";
}

#endif