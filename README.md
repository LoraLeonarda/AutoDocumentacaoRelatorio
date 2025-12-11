# Auto Documentação e Relatorio

Dois códigos capazes de automaticamente documentar classes em código C++ e Python e de criar um relatório de funcionamento por classe (atualmente somente em Python)

# Exemplo de saída:

## Definindo a classe gerador_relatorio
>Método<string> code;

>Método traduzir(string tk);

>Método load_file(string filename);

>Método gerar_relatorio(bool do_print);

- Carrega um arquivo de código para realizar a operação
>Método gerador_relatorio::load_file(string filename)

- Traduz uma linha de código para um comentário no MD
>Método gerador_relatorio::traduzir(string tk)

- remover os tabs do inicio da linha e verificações adicionais
- trocar e manter tokens
- para python
- e para C e C++
>>essa operação retorna *"";*

- Método principal para gerar o relatório
>Método gerador_relatorio::gerar_relatorio(bool do_print)
>>essa operação retorna *ret;*


