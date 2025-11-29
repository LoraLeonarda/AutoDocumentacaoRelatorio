#include <iostream>
#include <vector>
#include <fstream>
#include <random>
using namespace std;

//--------------------------------------------------
// CLASSE DO GERADOR DE RELATÓRIO DE ARQUIVOS PYTHON
//--------------------------------------------------
class gerador_relatorio
{
	private:
		vector<string> code;
		string traduzir(string tk);
		
	public:
		void load_file(string filename);
		string gerar_relatorio(bool do_print);
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
string gerador_relatorio::traduzir(string tk)
{
	// remover os tabs do inicio da linha e verificações adicionais
	if(tk.empty()) return "";
	while(!tk.empty() && tk[0] == '\t'){tk = tk.substr(1);}
	if(tk.empty()) return "";

	
	// trocar e manter tokens
	
	// para python
	if(tk.at(0) == '#'){return "-" + tk.substr(1, tk.substr(1).size()-1) + "\n";}
	else if(tk.substr(0, 3) == "\"\"\""){return tk.substr(3, tk.substr(3).size()-2) + "\n";}
	else if(tk.substr(0, 3) == "def"){return ">Método" + tk.substr(3, tk.substr(3).size()-2) + "\n\n";}
	else if(tk.substr(0, 5) == "class"){return "## Definindo a classe" + tk.substr(5, tk.substr(5).size()-1) + "\n";}
	else if(tk.substr(0, 6) == "return"){return ">>essa operação retorna *" + tk.substr(7, tk.substr(7).size()-1) + "*\n\n";}
	else if(tk.substr(0, 6) == "import"){return ">>Vamos utilizar" + tk.substr(6, tk.substr(6).size()-2) + "\n";}
	else if(tk.substr(0, 4) == "from"){return ">Da biblioteca" + tk.substr(4, tk.substr(4).size()-2) + "\n";}
	else if(tk.substr(0, 3) == "try"){return ">Ele irá tentar executar o processo, se tiver sucesso:\n";}
	else if(tk.substr(0, 5) == "catch" ||tk.substr(0, 6) == "except"){return ">Caso um erro acontecer, então:\n";}
	
	// para C e C++
	else if(tk.substr(0, 2) == "//"){return "-" + tk.substr(2, tk.substr(2).size()-1) + "\n";}
	else if(tk.substr(0, 3) == "int"){return ">Método" + tk.substr(3, tk.substr(3).size()-1) + "\n\n";}
	else if(tk.substr(0, 6) == "string"){return ">Método" + tk.substr(6, tk.substr(6).size()-1) + "\n\n";}
	else if(tk.substr(0, 4) == "void"){return ">Método" + tk.substr(4, tk.substr(4).size()-1) + "\n\n";}
	else if(tk.substr(0, 6) == "vector"){return ">Método" + tk.substr(6, tk.substr(6).size()-1) + "\n\n";}
	else if(tk.substr(0, 4) == "bool"){return ">Método" + tk.substr(4, tk.substr(4).size()-1) + "\n\n";}
	
	return "";
}

// Método principal para gerar o relatório
string gerador_relatorio::gerar_relatorio(bool do_print)
{
	// variaveis
	string ret = "";
	string token;
	
	// processo principal
	for(int i=0 ; i<code.size() ; i++)
	{
		// obter token
		token = code[i];
		ret += traduzir(token);
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
	gerador_relatorio gr;
	gr.load_file(argv[1]);
	gr.gerar_relatorio(true);
}