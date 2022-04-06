#ifndef DOCUMENTO_H
#define DOCUMENTO_H

class Documento{
    public:
        Documento();
        ~Documento();
        int GetId();
        int GetWd();
        float GetSimilaridade();
        ListaEncadeada <std::string>* GetVocabularioLocal();
        void SetId(int _id);
        void SetWd(int _Wd);
        void SetSimilaridade(float _similaridade);

    private:
        int id;
        int Wd;
        float similaridade;
        ListaEncadeada<std::string> *vocabularioLocal;
};

/**
* -Descricao: construtor padrao
* -Entrada: N/A
* -Saida: N/A
*/
Documento::Documento(){
    vocabularioLocal = new ListaEncadeada<std::string>();
    id = -1;
    Wd = -1;
    similaridade = 0;
}

Documento::~Documento(){}

/**
* -Descricao: getter do atributo id
* -Entrada: N/A
* -Saida: id
*/
int Documento::GetId(){
    return id;
}

/**
* -Descricao: getter do atributo Wd
* -Entrada: N/A
* -Saida: Wd
*/
int Documento::GetWd(){
    return Wd;
}

/**
* -Descricao: getter do atributo similaridade
* -Entrada: N/A
* -Saida: similaridade
*/
float Documento::GetSimilaridade(){
    return similaridade;
}

/**
* -Descricao: getter do atributo vocabularioLocal
* -Entrada: N/A
* -Saida: vocabularioLocal
*/
ListaEncadeada <std::string>* Documento::GetVocabularioLocal(){
    return vocabularioLocal;
}

/**
* -Descricao: setter do atributo id
* -Entrada: _id
* -Saida: N/A
*/
void Documento::SetId(int _id){
    id = _id;
}

/**
* -Descricao: setter do atributo Wd
* -Entrada: _Wd
* -Saida: N/A
*/
void Documento::SetWd(int _Wd){
    Wd = _Wd;
}

/**
* -Descricao: setter do atributo similaridade
* -Entrada: _similaridade
* -Saida: N/A
*/
void Documento::SetSimilaridade(float _similaridade){
    similaridade = _similaridade;
}

#endif