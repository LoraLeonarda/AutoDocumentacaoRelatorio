# Auto Documentação e Relatorio

Dois códigos capazes de automaticamente documentar classes em código C++ e Python e de criar um relatório de funcionamento por classe (atualmente somente em Python)

# Exemplo de saída:

# Documentação do código Documentar.cpp
> Bibliotecas utilizadas:
>>iostream

>>vector

>>fstream

>>random

## Definindo a classe gerador_relatorio

#### Método/Função gerador_relatorio::load_file(string filename)

#### Método/Função gerador_relatorio::traduzir(string tk)

> Para python e C++ (ambos contém operação).
> Para C e C++ (exclusivo).
> Se (linha não conter parenteses ou (conter parentesis e igual)), é uma delcaração de variavel, e não deve ser transofmada no MD.

- essa operação retorna *""*

#### Método/Função gerador_relatorio::gerar_relatorio(bool do_print, string filename)

- essa operação retorna *ret*

#### Método/Função main(int argc, char *argv[])


