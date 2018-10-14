#include "preprocessamento.h"
#include "montador.h"

int checaArquivo(string);
void extensaoArquivo(string&, string&, string&, string&);

// Confere se eh possivel abrir o arquivo
int confereArquivo (string arquivoEntrada){
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
	nomeArquivoObj.append(".o");
}

int main(int argc, char** argv) {

	// Identifica se o numero de argumentos na linha de comando para a execução está correto
	if (argc != 4){
		cout << "\n Coloque o comando no formato: ./a.exe -o nome_arquivo_entrada nome_arquivo_saida" << "\n\n";
		exit(1);
	}

	// Cada argumento eh salvo em uma string
	string tipoOperacao = argv[1];
  	string nomeArquivoEntrada = argv[2];
  	string nomeArquivoSaida	= argv[3];

    // String com o nome dos arquivos de entrada e saida
  	string nomeArquivoPre, nomeArquivoObj;

  	// Acrescenta a extensao dos arquivos de entrada e saida
  	extensaoArquivo(nomeArquivoEntrada, nomeArquivoPre, nomeArquivoObj, nomeArquivoSaida);

    // Verifica se o arquivo de entrada existe
	if (!confereArquivo(nomeArquivoEntrada)){
		cout << "\n O arquivo de entrada nao existe " << "\n\n";
		exit(1);
	}

	// Verifica se o primeiro argumento esta correto
	if (tipoOperacao.front() != '-'){
		cout << "\n Erro no argumento: -x. Coloque o comando no formato: ./a.exe -x nome_arquivo_entrada nome_arquivo_saida " << "\n\n";
		exit(1);
	}

	switch(tipoOperacao.back()){

		// A etapa de preprocessamento retira os comentarios e faz o tratamento de tabulacoes, quebra de linhas e espacos desnecessarios
		case 'p':
            etapaPreProcessamento(nomeArquivoEntrada, nomeArquivoPre);
			cout << "\n Etapa de preprocessamento realizada " << "\n\n";
			break;
        
        case 'o':
            break;

		// Modo de operacao diferente de 'p' ou 'o'
		default:
			cout << "\n Escolha uma operacao valida (p ou o)" << "\n\n";
			break;
	}

	return 0;
}

    