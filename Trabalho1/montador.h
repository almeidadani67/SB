struct Instrucao{
    string nomeInstrucao;
    int opcode, numeroOperandos;
};

struct Diretiva{
    string nomeDiretiva;
};

vector<Instrucao> montaVectorInstrucoes(){
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
	
    //So conferindo os valores e posicoes das instrucoes - PODE APAGAR ESSA IMPRESSAO
    for(int i=0;i<vectorInstrucao.size();i++){
        cout<<vectorInstrucao[i].nomeInstrucao<<", "<<vectorInstrucao[i].opcode<<", "<<vectorInstrucao[i].numeroOperandos<<endl;
    }

    return vectorInstrucao;
}

vector<Diretiva> montaVectorDiretiva(){
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
	
    //So conferindo os valores e posicoes das diretivas - PODE APAGAR ESSA IMPRESSAO
    for(int i=0;i<vectorDiretiva.size();i++){
        cout<<vectorDiretiva[i].nomeDiretiva<<endl;
    }

    return vectorDiretiva;
}
