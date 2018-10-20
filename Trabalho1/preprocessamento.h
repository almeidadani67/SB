#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Instrucao{ 
    string nomeInstrucao; 
    int opcode, numeroOperandos; 
}; 
 
struct Diretiva{ 
    string nomeDiretiva; 
}; 
 
struct Rotulos{
	string nomeRotulo;			// Nome dado para o rotulo
	int valorRotulo;			// Valor do rotulo (endereco do rotulo)
	string EQU;					// Definicao da EQU
	Rotulos (){};
	Rotulos (string nome, string equate): nomeRotulo(nome), EQU(equate){};
};

vector<Instrucao> montagemVectorInstrucoes(){ 
    //Criando o vector que armazena o nome da instrucao, seu respectivo opcode e numero de operandos 
    vector<Instrucao> vectorInstrucao; 
 
    //Inserindo os elementos no vector, sendo o primeiro valor o nomeInstrucao, o segundo o opcode e o terceiro o numeroOperandos 
    vectorInstrucao.push_back({"ADD", 1, 1}); 
    vectorInstrucao.push_back({"SUB", 2, 1}); 
    vectorInstrucao.push_back({"MULT", 3, 1}); 
    vectorInstrucao.push_back({"DIV", 4, 1}); 
    vectorInstrucao.push_back({"JMP", 5, 1}); 
    vectorInstrucao.push_back({"JMPN", 6, 1}); 
    vectorInstrucao.push_back({"JMPP", 7, 1}); 
    vectorInstrucao.push_back({"JMPZ", 8, 1}); 
    vectorInstrucao.push_back({"COPY", 9, 2}); 
    vectorInstrucao.push_back({"LOAD", 10, 1}); 
    vectorInstrucao.push_back({"STORE", 11, 1}); 
    vectorInstrucao.push_back({"INPUT", 12, 1}); 
    vectorInstrucao.push_back({"OUTPUT", 13, 1}); 
    vectorInstrucao.push_back({"STOP", 14, 0}); 
	 
    /*So conferindo os valores e posicoes das instrucoes
    for(int i=0;i<vectorInstrucao.size();i++){ 
        cout<<vectorInstrucao[i].nomeInstrucao<<", "<<vectorInstrucao[i].opcode<<", "<<vectorInstrucao[i].numeroOperandos<<endl; 
    } */
 
    return vectorInstrucao; 
} 
 
vector<Diretiva> montagemVectorDiretiva(){ 
    //Criando o vector que armazena o nome da instrucao, seu respectivo opcode e numero de operandos 
    vector<Diretiva> vectorDiretiva; 
 
    //Inserindo os elementos no vector, sendo o primeiro valor o nomeInstrucao, o segundo o opcode e o terceiro o numeroOperandos 
    vectorDiretiva.push_back({"SECTION"}); 
    vectorDiretiva.push_back({"SPACE"}); 
    vectorDiretiva.push_back({"CONST"}); 
    vectorDiretiva.push_back({"PUBLIC"}); 
    vectorDiretiva.push_back({"EQU"}); 
    vectorDiretiva.push_back({"IF"}); 
    vectorDiretiva.push_back({"EXTERN"}); 
    vectorDiretiva.push_back({"BEGIN"}); 
    vectorDiretiva.push_back({"END"}); 
	 
    /*So conferindo os valores e posicoes das diretivas - PODE APAGAR ESSA IMPRESSAO 
    for(int i=0;i<vectorDiretiva.size();i++){ 
        cout<<vectorDiretiva[i].nomeDiretiva<<endl; 
    } */
 
    return vectorDiretiva; 
} 

void PreProcessamento(string, string, vector<int>&, vector<Instrucao>&, vector<Diretiva>&);
int EQUrepete(string&, vector<Rotulos>&, int&);
void substituiEQU(string&, vector<Rotulos>&);
void analiseLinha(string&, ifstream&, int&, vector<Rotulos>&, vector<Instrucao>&, vector<Diretiva>&);
void uneLinha(string& , ifstream&, stringstream&, int&, vector<Rotulos>&);
void validaRotulo(string, vector<Diretiva>&, vector<Instrucao>&, int&);
void executaEQU(string&, stringstream&, vector<Rotulos>&, int&);
void executaIF(ifstream&, stringstream&, int&);
int Inteiro(int &, string);
void tratamentoLinha(string&, vector<Rotulos>&, ifstream&, int&);

//Identifica se o rotulo e valido
void validaRotulo(string nomeRotulo, vector<Diretiva> &vectorDiretiva, vector<Instrucao> &vectorInstrucao, int &contador){
	
	int i;

	for (i=0; i < vectorDiretiva.size(); i++){
		if (vectorDiretiva[i].nomeDiretiva == nomeRotulo){
			cout << "\nErro semantico na linha " << contador << ": Rotulo nao pode possuir o mesmo nome que uma diretiva" << "\n";
		}
	}

	for (i=0; i < vectorInstrucao.size(); i++){
		if (vectorInstrucao[i].nomeInstrucao == nomeRotulo){
			cout << "\nErro semantico na linha " << contador << ": Rotulo nao pode possuir o mesmo nome que uma instrucao" << "\n";
		}
	}

	if (nomeRotulo.front() <= '9' && nomeRotulo.front() >= '0'){
		cout << "\nErro lexico na linha " << contador << ": Rotulo nao pode comecar com numero" << '\n';
	}

	for(i=0; i < nomeRotulo.size(); i++){
		if((nomeRotulo[i] > '9' || nomeRotulo[i] < '0') && (nomeRotulo[i] != '_') && (nomeRotulo[i] > 'Z' || nomeRotulo[i] < 'A')){
			cout << "\nErro lexico na linha " << contador << ": Rotulo possui caracteres invalidos" << '\n';
		}
	}

	if (nomeRotulo.empty()){
		cout << "\nErro sintatico na linha " << contador << ": Rotulo esta vazio" << '\n';
	}

	if (nomeRotulo.size() > 20){
		cout << "\nErro lexico na linha " << contador << ": Rotulo ultrapassa o tamanho maximo" << "\n";
	}
}

int Inteiro(int &inteiroehUM, string valorIF){
	char* d;
	inteiroehUM = strtol(valorIF.c_str(), &d, 10);
	return *d == 0;
}

void executaIF(ifstream &arquivoEntrada, stringstream &streamLinha, int &contador){

	int inteiroehUM;
	int variavelInt;

	string valorIF;
	streamLinha >> valorIF;
	string proximoToken;
	streamLinha >> proximoToken;

	if(valorIF.empty()){
		cout << "\nErro sintatico na linha " << contador << ": IF possui valor em branco" << '\n';
		return;
	}

	if(!proximoToken.empty()){
		cout << "\nErro sintatico na linha " << contador << ": Numero de argumentos invalido" << '\n';
		return;
	}

	// inteiroehum indica se o argumento do IF e 1
	inteiroehUM = 0;
	variavelInt = Inteiro(inteiroehUM, valorIF);

	if(!variavelInt){
		cout << "\nErro sintatico na linha " << contador << ": O argumento do IF nao e um inteiro" << '\n';
		return;
	}else{

		// Caso inteiroehUM seja 0, a linha posterior e descartada
		if (inteiroehUM != 1){
			string linhaDescartada;
			getline(arquivoEntrada, linhaDescartada);
			contador = contador + 1;
		}
	}

}

//Verifica se o rotulo do EQU foi declarado mais de uma vez - retorna 1 se o rotulo nao foi repetido
int EQUrepete(string &line, vector<Rotulos> &vectorRotulos, int &contador){
	unsigned i;	
	stringstream streamLinha (line);
	string primeiroToken;
	string segundoToken;
	streamLinha >> primeiroToken;
	if ((!primeiroToken.empty()) && primeiroToken.back() == ':'){
		streamLinha >> segundoToken;
		if (segundoToken == "EQU"){
			primeiroToken.pop_back();
			for(i=0;i<vectorRotulos.size();i++){
				if(primeiroToken == vectorRotulos[i].nomeRotulo){
					cout << "\nErro semantico na linha " << contador << ": Rotulo declarado mais de uma vez" << '\n';
					return 0;
				}
			}
		}
	}
	return 1;
}

void executaEQU(string &primeiroToken, stringstream &streamLinha, vector<Rotulos> &vectorRotulos, int &contador){
	
	string valorEQU;
	string proximoToken;
	streamLinha >> valorEQU;
	streamLinha >> proximoToken;

	if(valorEQU.empty()){
		cout << "\nErro sintatico na linha " << contador << ": O valor de EQU esta em branco" << "\n";
		return;
	}

	// Coloca no vector de rotulos o valor definido no EQU
	Rotulos rot (primeiroToken, valorEQU);
	vectorRotulos.push_back(rot);

	if (!proximoToken.empty()){
		cout << "\nErro sintatico na linha " << contador << ": Numero de argumentos incorreto" << "\n";
		return;
	}

}

// Substitui o valor dos rotulos que ja foram definidos
void substituiEQU(string &line, vector<Rotulos> &vectorRotulos){

	int i;
	int tamanho;

	for (i=0; i<vectorRotulos.size(); i++){
		tamanho = vectorRotulos[i].nomeRotulo.size();
		size_t posicaoInicial = 0;
		size_t posicaoDoRotulo = line.find(vectorRotulos[i].nomeRotulo, posicaoInicial);

		// Substitui o valor no rotulo definido
		while (posicaoDoRotulo != string::npos){
			if(posicaoDoRotulo == 0){
				if (line[posicaoDoRotulo+tamanho] == ':' || line[posicaoDoRotulo+tamanho] == ' ' || posicaoDoRotulo+tamanho >= line.size() )
					line.replace(posicaoDoRotulo, tamanho, vectorRotulos[i].EQU);
			}else{
				if (line[posicaoDoRotulo-1] == ' ' && (line[posicaoDoRotulo+tamanho] == ' ' || posicaoDoRotulo+tamanho >= line.size())){
					line.replace(posicaoDoRotulo, tamanho, vectorRotulos[i].EQU);
				}
			}
			posicaoInicial = posicaoDoRotulo + 1;
			posicaoDoRotulo = line.find(vectorRotulos[i].nomeRotulo, posicaoInicial);
		}
	}
}

void tratamentoLinha(string &line, vector<Rotulos> &vectorRotulos, ifstream &arquivoEntrada, int &contador){
	//Pega o conteudo do arquivEntrada e coloca em line
	getline(arquivoEntrada, line);
	stringstream linha (line);
	//Retira os comentarios 
	getline(linha, line, ';');
	//Passa para maiusculo
	transform (line.begin(), line.end(), line.begin(), ::toupper);
	//Retira os espacos desnecessarios entre tokens
	linha.str(line);
	linha.clear();
	//Vector que recebe os tokens
	vector<string> tokens;
	while (!linha.eof()){
		string auxiliar;
		linha >> auxiliar;
		tokens.push_back(auxiliar); 
		}
	line.clear(); 
	int i;
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

	int EQUdefinido;
	EQUdefinido = EQUrepete(line, vectorRotulos, contador);

	// Substitui o rotulo pelo valor somente se EQUdefinido = 1 (sem erros)
	if (EQUdefinido){
		substituiEQU(line, vectorRotulos);
		}
}

// Une uma linha com a proxima, caso haja uma quebra de linha na definicao de um rotulo
void uneLinha(string &line , ifstream &arquivoEntrada, stringstream &streamLinha, int &contador, vector<Rotulos> &vectorRotulos){

	string proxima;

	// Enquanto proxima linha ser vazia e o arquivo nao chegar ao fim
	while (!arquivoEntrada.eof() && proxima.size() == 0){
		tratamentoLinha(proxima, vectorRotulos, arquivoEntrada, contador);
		contador = contador + 1;
	}
	// Une a proxima linha com a atual
	line = line + " " + proxima;
	streamLinha.str(proxima);
	streamLinha.clear();
}

// Confere se a linha possui as diretivas IF ou EQU
void analiseLinha(string &line, ifstream &arquivoEntrada, int &contador, vector<Rotulos> &vectorRotulos, vector<Instrucao> &vectorInstrucao, vector<Diretiva> &vectorDiretiva){

	stringstream streamLinha (line);

	string primeiroToken;
	streamLinha >> primeiroToken;

	// Identifica se o rotulo esta sendo definido
	if (primeiroToken.back() == ':'){
		string segundoToken;
		streamLinha >> segundoToken;
		if (segundoToken.empty()){
			uneLinha(line, arquivoEntrada, streamLinha, contador, vectorRotulos);
			streamLinha >> segundoToken;
		}

		if (segundoToken == "EQU"){

			// Retira do primeiro token o símbolo ':'
			primeiroToken.pop_back();
			validaRotulo(primeiroToken, vectorDiretiva, vectorInstrucao, contador);
			executaEQU(primeiroToken, streamLinha, vectorRotulos, contador);
			line.clear();
		}
	} 
	// Caso o primeiro token seja um IF, o programa verifica se a proxima linha deve ser escrita no arquivo de saida
	else if(primeiroToken == "IF"){
			executaIF(arquivoEntrada, streamLinha, contador);
			line.clear();
		}
}

//O prepreocessamento retira os comentarios, passa tudo para maiusculo e faz o tratamento de tabulacoes, quebra de linhas e espacos desnecessarios
// Tambem faz o tratamento das diretivas EQU e IF
void PreProcessamento(string nomeArquivoEntrada, string nomeArquivoPre, vector<int> &linhaOriginalPre, vector<Instrucao> &vectorInstrucao, vector<Diretiva> &vectorDiretiva){

	vector<Rotulos> vectorRotulos;

	//Leitura do arquivoEntrada e escrita no arquivoPreproc
	ifstream arquivoEntrada (nomeArquivoEntrada);
	ofstream arquivoPreproc (nomeArquivoPre);
    
	int contador=1;

    while(!arquivoEntrada.eof()){
		string line;

		tratamentoLinha(line, vectorRotulos, arquivoEntrada, contador);
		analiseLinha(line, arquivoEntrada, contador, vectorRotulos, vectorInstrucao, vectorDiretiva);

        // Copia a linha no arquivo de preprocessamento caso a linha nao esteja vazia
		if (!line.empty()){
			arquivoPreproc << line << "\n";
			linhaOriginalPre.push_back(contador);
		}

		contador=contador+1;
    }

	// Fecha os arquivos de entrada e saida
	arquivoEntrada.close();
	arquivoPreproc.close();

	return;
}