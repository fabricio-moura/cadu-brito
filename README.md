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
  > É lido o nome do arquivo que irá ser gerado e nele é inserido o formato (P3), a qualidade (255), que são fixos, e a resolução, que está presente nas variáveis ptr_desenho->Y e ptr_desenho->X. Então é escrito em cada linha do arquivo a cor de cada pixel, caracterizando uma imagem reconhecível pelo formato.
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
* Cores no geral;
  * color
  > Lê do arquivo três valores correspondentes ao RGB e insere na variável global pincel para serem utilizados como cor pelas próximas funções.
  * paint_pixels
  > Uma função que é só um trecho de código que foi muito repetido no projeto. Ele atribui a cor do pincel para o pixel que foi inserido como parâmetro.
  * color_picker
  > Lê do pixel inserido como parâmetro três valores correspondentes ao RGB e insere na variável global pincel_fill para a função fill saber qual cor ela deve pintar.
  * clear
  > Lê do arquivo os valores correspondentes ao RGB e copia essa cor por meio loops para cada pixel da matriz do desenho.
* Preenchimento de cores;
  * fill
  * fill_spread_left
  * fill_spread_right
* Compressão e descompressão de imagem;
  * compress
  > É lido o nome da imagem a ser comprimida e, com esse mesmo nome, é retirada a "extensão" .ppm, inserida a .txt e então aberto um arquivo com esse nome no modo escrita. Da imagem a ser comprimida é lida a resolução e verificados o formato e qualidade e então é printado no arquivo essas informações. Em seguida é lida a cor na primeira linha da imagem e inseridas nas variáveis red, green, blue, red_atual, green_atual, blue_atual e começa um loop. Nesse loop é verificado se a cor (red, green, blue) é diferente da cor atual, se for, é imprimido no arquivo comprimido o contador (quantas vezes a cor atual foi lida) e a cor atual, e também a cor lida vira a cor atual e o contador volta para 1. Além dessa verificação, é verificado se a leitura `fscanf (imagem, "%d %d %d", &red, &green, &blue)  == EOF`, isso faz com que as cores da imagem sejam lidas até os pixels acabarem e, como não tem como comparar a ultima cor, quando chegar no final do arquivo imagem é imprimido no arquivo comprimido o contador e a cor dessa ultima.
  * decompress
  > Lê o nome do arquivo comprimido, transforma esse nome de .txt para .ppm e abre um arquivo descomprimido com esse nome no modo escrita. Então lê a resolução e checa a qualidade e formato e os imprime de maneira reconhecível no arquivo descomprimido. Então, em cada conjunto de cor que o laço de repetição encontrar, ele imprime no descomprimido uma linha da cor na quantidade de vezes do contador que a precede até chegar no fim do arquivo comprimido.
  
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
