#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

void etapaPreProcessamento(string, string);

void etapaPreProcessamento(string nomeArquivoEntrada, string nomeArquivoPre){

	// Leitura do arquivoEntrada e escrita no arquivoPreproc //
	ifstream arquivoEntrada (nomeArquivoEntrada);
	ofstream arquivoPreproc (nomeArquivoPre);

    string line;

    // Copia o que tem no arquivo de entrada para o arquivo de PreProcessamento
    // Modificar para excluir comentarios
    while(getline(arquivoEntrada,line)){
        arquivoPreproc << line << "\n";
    }


	// Fecha os arquivos de entrada e saida
	arquivoEntrada.close();
	arquivoPreproc.close();

	return;
}