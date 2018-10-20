#include "preprocessamento.h"
#include "montador.h"
#include "ligador.h"

int checaArquivo(string);
void extensaoArquivo(string&, string&, string&, string&);

// Confere se e possivel abrir o arquivo
int checaArquivo (string arquivoEntrada){
	ifstream arquivoEn (arquivoEntrada);
	if(arquivoEn.is_open()){
		arquivoEn.close();
		return 1;
	}
	return 0;
}

// Recebe as strings com os nomes dos arquivos de saida e adiciona a extensao correta
void extensaoArquivo(string &nomeArquivoEntrada, string &nomeArquivoPre, string &nomeArquivoObj, string &nomeArquivoSaida){
	nomeArquivoPre = nomeArquivoSaida;
	nomeArquivoObj = nomeArquivoSaida;
	nomeArquivoEntrada.append(".asm");
	nomeArquivoPre.append(".pre");
	nomeArquivoObj.append(".obj");
}

int main(int argc, char** argv) {

	// Identifica se o numero de argumentos na linha de comando para a execução está correto
	if (argc != 4){
		cout << "\n Coloque o comando no formato: ./a.exe -o nome_arquivo_entrada nome_arquivo_saida" << "\n\n";
		exit(1);
	}

	string tipoOperacao = argv[1];
  	string nomeArquivoEntrada = argv[2];
  	string nomeArquivoSaida	= argv[3];
 	vector<int> linhaOriginalPre;
  	string nomeArquivoPre, nomeArquivoObj;

  	extensaoArquivo(nomeArquivoEntrada, nomeArquivoPre, nomeArquivoObj, nomeArquivoSaida);

	vector<Instrucao> vectorInstrucao = montagemVectorInstrucoes();
	vector<Diretiva> vectorDiretiva = montagemVectorDiretiva();

    // Confere se o arquivo de entrada existe
	if (!checaArquivo(nomeArquivoEntrada)){
		cout << "\n O arquivo de entrada nao existe " << "\n\n";
		exit(1);
	}

	// Verifica se o primeiro argumento esta correto
	if (tipoOperacao.front() != '-'){
		cout << "\n Erro no argumento: -x. Coloque o comando no formato: ./a.exe -x nome_arquivo_entrada nome_arquivo_saida " << "\n\n";
		exit(1);
	}

	switch(tipoOperacao.back()){

		// O preprocessamento retira os comentarios e faz o tratamento de tabulacoes, quebra de linhas e espacos desnecessarios
		// O preprocessamento tambem faz o tratamento das diretivas IF e EQU
		case 'p':
            PreProcessamento(nomeArquivoEntrada, nomeArquivoPre, linhaOriginalPre, vectorInstrucao,vectorDiretiva);
			cout << "\n Preprocessamento realizado " << "\n\n";
			break;
        
        case 'o':
			PreProcessamento(nomeArquivoEntrada, nomeArquivoPre, linhaOriginalPre, vectorInstrucao,vectorDiretiva);
            cout << "\n Montagem realizada " << "\n\n";
			break;
		
		case 'l':
			PreProcessamento(nomeArquivoEntrada, nomeArquivoPre, linhaOriginalPre, vectorInstrucao,vectorDiretiva);
			break;

		default:
			cout << "\n Escolha uma operacao valida (p, o ou l)" << "\n\n";
			break;
	}

	return 0;
}

    