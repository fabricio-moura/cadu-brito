## Projeto para 3ª Unidade ITP 2019.2 UFRN

Esse projeto é um trabalho realizado para compor a nota da referida unidade para a matéria de Introdução às Técnicas de Programação (Turma 07) da Universidade Federal do Rio Grande do Norte. O foco da disciplina é a linguagem C, e será desenvolvido um software que realiza a digitalização de uma imagem gráfica no formato PPM a partir de um arquivo com dados de (inserir informações)...

* Antonio Higino Bisneto Leite Medeiros
* Fabrício Moura Jácome

O que foi feito e as funções responsáveis (presentes em primitivas.c):
* Criação dos tipos de dados necessários (typedef, structs e enums);
* Modularização do programa;
* Leitura do arquivo de especificação;
* Geração de uma imagem  PPM;
  * image
  * save
* Desenho de retas;
  * line
  * line_straight
  * line_x
  * line_y
* Desenho de polígonos;
  * polygon
* Desenho de circúlos;
  * circle
  * circle_line
* Preenchimento de cores;
  * fill
  * fill_spread_left
  * fill_spread_right
* Compressão e descompressão de imagem;
  * compress
  * decompress
  
O que não foi feito:



O que seria feito diferentemente:



Como compilar e rodar o projeto:
* Execute o comando `make all` no terminal aberto na pasta com todos os 7 arquivos modularizados;
* (Opcional) Após executar o comando `make all`, execute o comando `make clean` para deletar os arquivos .o desnecessários;
* Será produzido um arquivo chamado `projeto`, execute-o no terminal.
