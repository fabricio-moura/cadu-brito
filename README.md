## Projeto para 3ª Unidade ITP 2019.2 UFRN

Esse projeto é um trabalho realizado para compor a nota da referida unidade para a matéria de Introdução às Técnicas de Programação (Turma 07) da Universidade Federal do Rio Grande do Norte. O foco da disciplina é a linguagem C, e será desenvolvido um software que realiza a digitalização de uma imagem gráfica no formato PPM a partir de um arquivo com as primitivas (comandos) desejadas pelo usuário, resultando em um arquivo P3 com qualidade 255.

O que foi feito e as funções responsáveis (presentes em primitivas.c):
* Criação dos tipos de dados necessários (typedef, structs e enums);
* Modularização do programa;
* Leitura do arquivo de especificação;
* Geração de uma imagem  PPM;
  * image
  > Será lido do arquivo a resolução da imagem e inserido na variável desenho a partir do ponteiro ptr_desenho. O ptr_desenho->Y corresponde a largura e o ptr_desenho->X corresponde a altura. Então, a matriz de pixels que foi alocada inicialmente com tamanho 1, será realocada para o tamanho das variáveis citadas utilizando o método padrão para matrizes alocadas dinamicamente.
  * open
  > Será lido do arquivo o nome da imagem da qual realizará-se a leitura, irá ser verificada se é uma imagem válida a partir do formato e da qualidade e será lida a resolução e inserida nas variáveis ptr_desenho->Y, correspondendo a largura e, ptr_desenho->X correspondendo a altura. Então realocará-se a matriz de pixels para o tamanho da imagem lida e é copiada as cores, pixel por pixel, da imagem para a matriz.
  * save
  > 
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
* Interface gráfica (o design foi iniciado e o funcionamento isolado, mas não teve tempo de aplicar no programa)

O que seria feito diferentemente:
* Não teriam sido utilizadas variáveis globais no arquivo tipos.h para diminuir a utilização de ponteiros e parâmetros em algumas funções
* Desde o início do desenvolvimento do projeto, houve a confusão da posição da altura com largura na leitura e escrita no arquivo input e na imagem. Então foi invertido no arquivo e acabou que a largura virou o eixo y e a altura virou o eixo x, o que acabou ficando confuso e para corrigir isso teria que mudar bastante coisa no código, só que isso não daria tempo.

Como compilar e rodar o projeto:
* Execute o comando `make all` no terminal aberto na pasta com todos os 7 arquivos modularizados;
* (Opcional) Após executar o comando `make all`, execute o comando `make clean` para deletar os arquivos .o desnecessários;
* Será produzido um arquivo chamado `projeto`, execute-o no terminal.
___
| Integrantes      | Atribuições |
| ----------- | ----------- |
| Antonio Higino Bisneto Leite Medeiros      | Lógica, Documentação      |
| Fabrício Moura Jácome   | Lógica, Coding    |
