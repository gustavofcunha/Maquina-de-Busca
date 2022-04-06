#include <iostream>
#include <string>
#include <getopt.h>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "msgassert.h"
#include "Celula.h"
#include "ListaEncadeada.h"
#include "IndiceInvertido.h"
#include "Termo.h"
#include "Hash.h"
#include "Documento.h"

/**
* -Descricao: remove pontuacoes e deixa tudo em caixa baixa
* -Entrada: linha (referencia)
* -Saida: N/A
*/
void filtraLinha(std::string &linha){
    int i,j;

    //todos os caracteres passados para caixa baixo (lower case)
    for(i=0; i<(int)linha.size(); i++){
        linha[i] = std::tolower(linha[i]);
    }

    //remove pontuacoes
    for(j=0; j<10; j++){
        for(i=0; i<(int)linha.size(); i++){
            if(ispunct(linha[i])){
                linha[i] = ' ';
            }
        }
    }

    //remove caracteres especiais
    for(j=0; j<10; j++){
        for(i=0; i<(int)linha.size(); i++){
            if((linha[i] < 97 || linha[i] > 122) && linha[i] != 32){
                //linha[i] = ' ';
                linha.erase(i, 1);
            }
        }
    }

    //remove duplo espaco
    for(j=0; j<10; j++){
        for(i=0; i<(int)linha.size(); i++){
            if(linha[i-1] == 32 && linha[i] == 32){
                linha.erase(i, 1);
            }
        }
    }

}

/**
* -Descricao: conta o numero de termos do corpus recebido como parametro,
*  sem contabilizar stopwords e conta numero D de documentos do corpus
* -Entrada: nomePastaCorpus, stopWords, D (referencia)
* -Saida: M
*/
int contaCorpus(std::string nomePastaCorpus, 
                ListaEncadeada <std::string> *stopWords, int &D){
    
    std::filesystem::path corpus(nomePastaCorpus);
    std::string buf;
    std::ifstream d;
    std::string aux;
    int M = 0;
    ListaEncadeada <std::string>* vocabularioLocal;
    vocabularioLocal = new ListaEncadeada<std::string>;

    //abertura e processamento de todos os arquivos na pasta corpus recebida
    for(const auto& dirFile : std::filesystem::directory_iterator(corpus)) {
        //abertura do arquivo e assercao correspondente
        d.open(dirFile.path());
        D++;
        erroAssert(d.is_open(), "Erro ao abrir o arquivo");

        //obtem todas as linhas do documento atual
        while(getline(d,buf)){
            filtraLinha(buf);

            std::string delimitador = " ";
            size_t pos;

            //processamento e contagem das palavras da linha obtida (exceto stopWords)
            while ((pos = buf.find(delimitador)) != std::string::npos) {
                aux = buf.substr(0, pos);
                if(!stopWords->Contem(aux) && !vocabularioLocal->Contem(aux) && buf != ""){
                    vocabularioLocal->InsereFinal(aux);
                    M++;
                } 
                buf.erase(0, pos + delimitador.length());
            }
            if(!stopWords->Contem(buf) && !vocabularioLocal->Contem(buf) && buf != ""){
                vocabularioLocal->InsereFinal(buf);
                M++;
            } 
        }
        d.close();
    }

    return M;
}

/**
* -Descricao: adiciona ocorrencia de termo a hash
* -Entrada: hash, termo, idDocumento
* -Saida: N/A
*/
void adicionaOcorrencia(Hash *hash, std::string termo, int idDocumento){
    //caso o termo seja uma string vazia ou um espaco, ele nao eh adicionado
    if(termo == "" || termo == " ") return;

    Termo *termoAtual;
    //se termo estiver no hash
    if(hash->Pesquisa(termo)){
        //obtem o termo no hash
        termoAtual = hash->ObtemTermo(termo);

        //obtem o indice referente ao documento atual e incrementa sua frequencia
        IndiceInvertido idc;
        idc.SetIdDocumento(idDocumento);
        idc.SetFrequencia(1);
        
        //caso nao seja a primeira ocorrencia de termo no documento com id idDocumento
        if(termoAtual->GetIndices()->Contem(idc)){
            //incrementa a frequencia
            termoAtual->GetIndices()->ObtemElemento(idc)->IncrementaFrequencia();
        }

        //caso seja a primeira ocorrencia de termo no documento com id idDocumento
        else{
            //adiciona a presente ocorrencia ao indice
            termoAtual->GetIndices()->InsereFinal(idc);
        }
    }

    //se termo nao estiver no hash
    else{
        //instanciacao do novo termo
        Termo *novoTermo;
        novoTermo = new Termo;
        novoTermo->SetTermo(termo);

        //instanciacao do indice correspondente ao novo termo
        IndiceInvertido *novoIndice;
        novoIndice = new IndiceInvertido;
        novoIndice->SetIdDocumento(idDocumento);
        novoIndice->SetFrequencia(1);

        novoTermo->GetIndices()->InsereFinal(*novoIndice);

        //adicionando o novo termo ao hash
        hash->Insere(*novoTermo);
    }
}

/**
* -Descricao: percorre todas as palavras de todos os documentoa e constroi o hash
* -Entrada: hash, nomePastaCorpus, stopWords
* -Saida: N/A
*/
void constroiTabelaHash(Hash *hash, std::string nomePastaCorpus, 
                        ListaEncadeada <std::string> *stopWords,
                        ListaEncadeada <Documento> *documentos){
    std::filesystem::path corpus(nomePastaCorpus);
    std::string buf;
    std::ifstream d;
    std::string aux;
    std::filesystem::path arquivoAtual;
    std::string delimitador = " ";
    size_t pos;
    int idDocumento;
    int cont = 0;


    //percorre todos os documentos d do corpus
    for(const auto& dirFile : std::filesystem::directory_iterator(corpus)) {
        //abertura do arquivo e assercao correspondente
        d.open(dirFile.path());
        erroAssert(d.is_open(), "Erro ao abrir o arquivo");

        //obtencao do indice do arquivo
        arquivoAtual = dirFile;
        aux = arquivoAtual.stem();
        idDocumento = stoi(aux);
        Documento novoDocumento;
        novoDocumento.SetId(idDocumento);
        documentos->InsereFinal(novoDocumento);
        

        //obtem todas as linhas do documento atual
        while(getline(d,buf)){
            cont++;
            filtraLinha(buf);

            //processamento das palavras da linha obtida
            while ((pos = buf.find(delimitador)) != std::string::npos) {
                aux = buf.substr(0, pos);
                
                //caso aux seja uma stop word, nao sera processada
                if(stopWords->Contem(aux)){
                    buf.erase(0, pos + delimitador.length());
                    continue;
                } 
                
                else{
                    if(!novoDocumento.GetVocabularioLocal()->Contem(aux)){
                        novoDocumento.GetVocabularioLocal()->InsereFinal(aux);
                    }
                    adicionaOcorrencia(hash, aux, idDocumento);
                    
                }

                buf.erase(0, pos + delimitador.length());
            }
            
            //processamento da ultima palavra da linha
            if(!stopWords->Contem(buf)){
                adicionaOcorrencia(hash, buf, idDocumento);
                if(!novoDocumento.GetVocabularioLocal()->Contem(buf)){
                    novoDocumento.GetVocabularioLocal()->InsereFinal(buf);
                }
            } 

        }
        d.close();
    }
}

/**
* -Descricao: obtem, processa e armazena as palavras da consulta em 
*  uma lista encadeada e ignora stopWords
* -Entrada: arquivoConsulta, palavrasConsulta, stopWords
* -Saida: N/A
*/
void processaPalavrasConsulta(std::ifstream &arquivoConsulta,
                              ListaEncadeada <std::string> *palavrasConsulta,
                              ListaEncadeada <std::string> *stopWords){
    std::string buf, aux;

    //obtem todas as linhas do documento
    while(getline(arquivoConsulta, buf)){
        filtraLinha(buf);

        std::string delimitador = " ";
        size_t pos;

        //processamento e contagem das palavras da linha obtida (exceto stopWords)
        while ((pos = buf.find(delimitador)) != std::string::npos) {
            aux = buf.substr(0, pos);
            if(!stopWords->Contem(aux) && !palavrasConsulta->Contem(aux)){
                palavrasConsulta->InsereFinal(aux);
            } 
            buf.erase(0, pos + delimitador.length());
        }
        if(!stopWords->Contem(buf) && !palavrasConsulta->Contem(buf)){
            palavrasConsulta->InsereFinal(buf);
        } 
    }
}

/**
* -Descricao: calculo da materica de similaridade entre documento e consulta
* -Entrada: hash, documento, D, palavrasConsulta
* -Saida: similaridade
*/
float calculaSimilaridade(Hash *hash, Documento documento, int D, float Wd,
                          ListaEncadeada <std::string> *palavrasConsulta){
    float similaridade = 0;
    float aux;

    Celula <std::string> *p;
    p = documento.GetVocabularioLocal()->GetPrimeiro()->GetProx();

    //navega por todas as palavras do vocabulario local
    while (p != nullptr) {
        aux = hash->calcula_w_td(p->GetItem(), documento.GetId(), D);
        similaridade += (aux*((int)palavrasConsulta->Contem(p->GetItem())));
        

        p = p->GetProx();
    }

    return similaridade/Wd;
}


/**
* -Descricao: funcao auxiliar do metodo sort que define quando um Documento deve
*  preceder outro na ordem desejada
* -Entrada: a, b
* -Saida: true (se a deve preceder b)
*         false (se b deve preceder a)
*/
bool ordena(Documento a, Documento b){
    //caso possuam mesma similaridade com a consulta, a ordenacao sera pelo id
    if((float)a.GetSimilaridade() == (float)b.GetSimilaridade()){
        if(a.GetId() < b.GetId()) return true;
        return false;
    }

    //caso contrario, ordenacao se dara, de fato, pela similaridade
    else{
        if((float)a.GetSimilaridade() > (float)b.GetSimilaridade()) return true;
        return false;
    }
}

/**
* -Descricao: funcao principal: abertura, processamento e fechamento
*  dos arquivos envolvidos, construcao do indice invertido e calculo
*  de similaridades
* -Entrada: argc, argv
* -Saida: 0
*/
int main(int argc, char **argv){
    std::cout << std::endl << "Processando parametros recebidos..."<< std::endl;
    //variaveis auxiliares
    int c;
    int nEntradas = 0;
    extern char *optarg;
    std::string nomeArqConsulta, nomeArqRanking, buf;
    std::string nomePastaCorpus, nomeArqStopWords;
    std::ifstream arquivoConsulta, arquivoStopWords; //entrada
    std::ofstream arquivoSaidaRanking; //saida

    //processamento dos parametros obrigatorios de execucao de entrada
    while ((c = getopt(argc, argv, "i:o:c:s:")) != EOF){
        switch (c){
            case 'i':
                nomeArqConsulta = optarg;
                nEntradas++;
                break;
            case 'o':
                nomeArqRanking = optarg;
                nEntradas++;
                break;
            case 'c':
                nomePastaCorpus = optarg;
                nEntradas++;
                break;
            case 's':
                nomeArqStopWords = optarg;
                nEntradas++;
                break;
            default:
                erroAssert(false, "Parametro de entrada invalida");
        }
    }

    erroAssert(nEntradas == 4, 
    "Parametros obrigatorios para execucao do programa faltantes na entrada");



    std::cout << std::endl << "Processando stop words..."<< std::endl;
    arquivoStopWords.open(nomeArqStopWords);
    erroAssert(arquivoStopWords.is_open(), "Erro ao abrir o arquivo");

    //vetor de stop words com base no arquivo de entrada referente
    ListaEncadeada <std::string> *stopWords;
    stopWords = new ListaEncadeada<std::string>();

    while(getline(arquivoStopWords, buf)){
        stopWords->InsereFinal(buf);
    }

    arquivoStopWords.close();



    std::cout << std::endl << "Processando tamanho do vocabulario e corpus..."<< std::endl;
    //descobrindo o tamanho do vocabulario e quantidade D de documentos do corpus
    int D = 0;
    int M = contaCorpus(nomePastaCorpus, stopWords, D);
    
    //lista de documentos
    ListaEncadeada <Documento> *documentos;
    documentos = new ListaEncadeada<Documento>();

    //tabela Hash
    Hash *hash;
    hash = new Hash((int)(M + (0.5*M)));

    std::cout << std::endl << "Construindo tabela Hash..."<< std::endl;
    constroiTabelaHash(hash, nomePastaCorpus, stopWords, documentos);



    std::cout << std::endl << "Processando consulta..."<< std::endl;
    arquivoConsulta.open(nomeArqConsulta);
    erroAssert(arquivoConsulta.is_open(), "Erro ao abrir o arquivo");
    
    //vetor de palavras da consulta (arquivo referente)
    ListaEncadeada <std::string> *palavrasConsulta;
    palavrasConsulta = new ListaEncadeada<std::string>();

    processaPalavrasConsulta(arquivoConsulta, palavrasConsulta, stopWords);

    arquivoConsulta.close();



    std::cout << std::endl << "Calculando similaridades..."<< std::endl;
    Documento ranking[D];
    Celula <Documento> *p;
    p = documentos->GetPrimeiro()->GetProx();

    float Wd, similaridade;
    int id;
    
    //calculo das similaridades de cada documento e atribuicoes ao vetor ranking
    for(int i=0; i<D; i++){
        Wd = hash->calcula_Wd(p->GetItem(), D);
        similaridade = calculaSimilaridade(hash, p->GetItem(), D, Wd, palavrasConsulta);
        id = p->GetItem().GetId();

        ranking[i].SetId(id);
        ranking[i].SetSimilaridade(similaridade);

        p = p->GetProx();
    }

    std::cout << std::endl << "Processando ordenacao e rankeamento..."<< std::endl;
    //ordenacao dos documentos em ranking com base no atributo similaridade
    std::sort(&ranking[0], &ranking[D], ordena);

    arquivoSaidaRanking.open(nomeArqRanking);
    erroAssert(arquivoSaidaRanking.is_open(), "Erro ao abrir o arquivo");

    //impressao dos ids dos documentos mais similares a consulta, 
    //exceto aquelas cuja similaridade eh igual a zero
    for(int i=0; i<10; i++){
        if(ranking[i].GetSimilaridade() != 0 && i<D){
            arquivoSaidaRanking << ranking[i].GetId() << " ";
        }
    }

    arquivoSaidaRanking.close();

    //impressao para visualizacao de resultados (opcional)
    /*for(int i=0; i<30; i++){
        if(ranking[i].GetSimilaridade() > 0){
            std::cout << std::endl << "documento " << ranking[i].GetId() << 
            "com similaridade: " << ranking[i].GetSimilaridade() <<std::endl;
        }
    }*/

    //desalocacao de memoria alocada dinamicamente
    delete(hash);
    delete(stopWords);
    delete(palavrasConsulta);
    delete(documentos);
    
    return 0;
}