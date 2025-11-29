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
void gerador_relatorio::load_file(string filename)
{
	ifstream arq(filename);
	string red;
	while(arq >> red){code.push_back(red);}
}
string gerador_relatorio::traduzir(string tk)
{
	//cout << "Processando token: " << tk << endl;
	if(tk == "="){return "será definido como";}
	if(tk == "if"){return "\n\nSe";}
	if(tk == "=="){return "é igual a";}
	if(tk == "!="){return "é diferente de";}
	if(tk == ">"){return "é maior que";}
	if(tk == "<"){return "é menor que";}
	if(tk == ">="){return "é maior ou igual a";}
	if(tk == "<="){return "é menor ou igual a";}
	if(tk == "and"){return "e,";}
	if(tk == "or"){return "ou,";}
	if(tk == "for"){return "\n\nPara cada valor";}
	if(tk == "in"){return "no";}
	if(tk == "{" || tk == "}"){return tk+"\n";}
	if(tk == "#"){return "\n";}
	if(tk == "\"\"\""){return "\n";}
	if(tk == "[]"){return "uma lista vazia\n";}
	if(tk == "def"){return "\n\n\n\tO método";}
	if(tk == "return"){return "encerra a execução retornando";}
	if(tk == "continue"){return "pula iteração do loop\n";}
	if(tk == "while"){return "\n\nEnquanto";}
	if(tk == "import"){return "\n\tvamos utilizar";}
	if(tk == "from"){return "\nDa biblioteca";}
	if(tk == "as"){return "nomeado como";}
	if(tk == "0"){return "inicializado\n";}
	if(tk == "try" || tk == "try:"){return "\nVamos tentar executar o seguinte processo:\n";}
	if(tk == "catch" || tk == "catch:" || tk == "except"){return "\nCaso aconteça um erro:\n";}
	if(tk == ":"){return " então:\n";}
	if(tk.at(tk.size()-1) == ':'){return tk+", então:\n";}
	if(tk.at(tk.size()-1) == ',' && tk.at(tk.size()-2) == ']'){return tk+"\n";}
	
	return tk;
}
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
		ret += " ";
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