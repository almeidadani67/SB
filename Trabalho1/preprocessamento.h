#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

void etapaPreProcessamento(string, string);

//A etapa de prepreocessamento retira os comentarios, passa tudo para maiusculo e faz o tratamento de tabulacoes, quebra de linhas e espacos desnecessarios
void etapaPreProcessamento(string nomeArquivoEntrada, string nomeArquivoPre, vector<int> &linhaOriginalPre){

	// Leitura do arquivoEntrada e escrita no arquivoPreproc //
	ifstream arquivoEntrada (nomeArquivoEntrada);
	ofstream arquivoPreproc (nomeArquivoPre);
    
	int i=1;

    while(!arquivoEntrada.eof()){
		string line;
		getline(arquivoEntrada, line);
		stringstream linha (line);

		//Retira os comentarios 
		getline(linha, line, ';');
		
		//Passa para maiusculo
		transform (line.begin(), line.end(), line.begin(), ::toupper);

		//Retira os espacos desnecessarios entre tokens
		linha.str(line);
		linha.clear();
		vector<string> tokens; // Cria um vector do tipo string para receber os tokens
		while (!linha.eof()){
			string auxiliar;
			linha >> auxiliar;
			tokens.push_back(auxiliar); // Coloca no vector os tokens
			}
		line.clear(); // Limpa a linha
		unsigned int i;
		for(i = 0; i<tokens.size(); i++){
			line = line + tokens[i] + ' ';
			}
	
		// Retira quebra de linha, tabulacoes e espacos em branco do final
		while (line.back() == '\n' || line.back() == '\t' || line.back() == ' '){
			line.pop_back();
			}


		// Retira quebra de linha, tabulacoes e espacos em branco do comeco
		while (line.front() == '\n' || line.front() == '\t' || line.front() == ' '){
			line = line.substr(1);
			}

        // Copia a linha no arquivo de preprocessamento caso a linha nao esteja vazia
		if (!line.empty()){
			arquivoPreproc << line << "\n";
			linhaOriginalPre.push_back(i);
		}

		i=i++;
    }

	// Fecha os arquivos de entrada e saida
	arquivoEntrada.close();
	arquivoPreproc.close();

	return;
}