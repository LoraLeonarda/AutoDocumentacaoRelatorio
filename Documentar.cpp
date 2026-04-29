#include <iostream>
#include <vector>
#include <fstream>
#include <random>
using namespace std;

// detecta se string contem substring
bool contem(string where, string what)
{
	return where.find(what) != string::npos;
}

//--------------------------------------------------
// CLASSE DO GERADOR DE RELATÓRIO DE ARQUIVOS PYTHON
//--------------------------------------------------
class gerador_relatorio
{
	private:
		vector<string> code;
		string traduzir(string tk, bool comentarios);
		
	public:
		void load_file(string filename);
		string gerar_relatorio(bool do_print, string filename, bool comentarios);
};

// Carrega um arquivo de código para realizar a operação
void gerador_relatorio::load_file(string filename)
{
	ifstream arq(filename);
	string red;
	while(getline(arq, red)){code.push_back(red);}
	arq.close();
}

// Traduz uma linha de código para um comentário no MD
string gerador_relatorio::traduzir(string tk, bool comentarios)
{
	// remover os tabs do inicio da linha e verificações adicionais
	if(tk.empty()) return "";
	while(!tk.empty() && tk[0] == '\t'){tk = tk.substr(1);}
	while(!tk.empty() && tk[0] == ' '){tk = tk.substr(1);}
	if(tk.empty()) return "";

	
	// trocar e manter tokens
	
	// detectar inclusão de biblioteca em C e C++
	if(tk.at(0) == '#' && tk.at(1) == 'i'){ return "  - " + tk.substr(10, tk.substr(10).size()-2) + "\n\n";}
	
	// matar strings com :: ou main ou qualquer outra coisa que surja
	else if(contem(tk, "::") || contem(tk, "main")){return "";}
	
	// para python e C++ (ambos contém operação)
	else if(tk.at(0) == '#' and comentarios){return ">" + tk.substr(1, tk.substr(1).size()-1) + "\n";}
	else if(tk.substr(0, 3) == "\"\"\"" and comentarios){return tk.substr(3, tk.substr(3).size()-2) + "\n";}
	else if(tk.substr(0, 3) == "def"){return "#### Função" + tk.substr(3, tk.substr(3).size()-2) + "\n\n";}
	else if(tk.substr(0, 5) == "class"){return "## Definindo a classe" + tk.substr(5, tk.substr(5).size()-1) + "\n";}
	else if(tk.substr(0, 6) == "return"){return "- Retorna" + tk.substr(6);}
	else if(tk.substr(0, 6) == "import"){return "  - " + tk.substr(6, tk.substr(6).size()-2) + "\n";}
	else if(tk.substr(0, 3) == "try"){return "\n\nEle irá tentar executar o processo, se tiver sucesso:\n\n";}
	else if(tk.substr(0, 5) == "catch" ||tk.substr(0, 6) == "except"){return "\n\nCaso um erro acontecer, então:\n\n";}
	
	// para C e C++ (exclusivo)
	else if(tk.substr(0, 2) == "//" and comentarios)
	{
		string ret = tk.substr(2, tk.substr(2).size()-1) + ".\n";
		while(ret[0] == ' '){ret = ret.substr(1);}
		ret[0] = toupper(ret[0]);
		return "> " + ret;
	}
	
	// se (linha não conter parenteses ou (conter parentesis e igual)), é uma delcaração de variavel, e não deve ser transofmada no MD
	bool contem_parentese = false;
	bool contem_igual = false;
	for(char i : tk)
	{
		if(i == '='){contem_igual = true;}
		if(i == '(' || i == ')'){contem_parentese = true;}
	}
	
	bool eh_variavel = !contem_parentese || (contem_parentese && contem_igual);
	
	// se não for varivel, é transformado em MD
	if(!eh_variavel)
	{
		if(tk.substr(0, 3) == "int"){return "#### Função" + tk.substr(3, tk.substr(3).size()-1) + "\n- Retorna um inteiro\n\n";}
		else if(tk.substr(0, 6) == "string"){return "#### Função" + tk.substr(6, tk.substr(6).size()-1) + "\n- Retorna uma string\n\n";}
		else if(tk.substr(0, 4) == "void"){return "#### Função" + tk.substr(4, tk.substr(4).size()-1) + "\n- Executa operação sem retorno\n\n";}
		else if(tk.substr(0, 6) == "vector"){return "#### Função" + tk.substr(6, tk.substr(6).size()-1) + "\n- Retorna um vetor de dados\n\n";}
		else if(tk.substr(0, 4) == "bool"){return "#### Função" + tk.substr(4, tk.substr(4).size()-1) + "\n- Retorna verdadeiro ou falso\n\n";}
	}
	
	return "";
}

// Método principal para gerar o relatório
string gerador_relatorio::gerar_relatorio(bool do_print, string filename, bool comentarios)
{
	// variaveis
	string ret = "";
	string token;
	
	// processo principal
	ret += "# Documentação do código ";
	ret += filename;
	ret += "\n";
	ret += "- Bibliotecas utilizadas e arquivos importados:\n";
	for(int i=0 ; i<code.size() ; i++)
	{
		// obter token
		token = code[i];
		ret += traduzir(token, comentarios);
	}
	
	// terminou, retorna e imprime
	if(do_print){cout << ret << endl;}
	return ret;
}



//--------------------------------------------------
// AMAIN
//--------------------------------------------------
int main(int argc, char *argv[])
{
	if(argc == 3)
	{
		gerador_relatorio gr;
		gr.load_file(argv[1]);
		bool comentarios = false;
		if(argv[2][0] == 't'){comentarios = true;}
		gr.gerar_relatorio(true, argv[1], comentarios);
	}
	else if(argc == 2)
	{
		gerador_relatorio gr;
		gr.load_file(argv[1]);
		gr.gerar_relatorio(true, argv[1], false);
	}
	else
	{
		cout << "ERRO: arquivo não informado, use como:\n\t./Documentar <codigo>\nOu como\n\t./Documentar <codigo> <true|false>" << endl;
	}
}