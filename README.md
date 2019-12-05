## Projeto para 3ª Unidade ITP 2019.2 UFRN
#### https://github.com/fabricio-moura/cadu-brito

Esse projeto é um trabalho realizado para compor a nota da referida unidade para a matéria de Introdução às Técnicas de Programação (Turma 07) da Universidade Federal do Rio Grande do Norte. O foco da disciplina é a linguagem C, e será desenvolvido um software que realiza a digitalização de uma imagem gráfica no formato PPM a partir de um arquivo com as primitivas (comandos) desejadas pelo usuário, resultando em um arquivo no formato P3 (.ppm) com qualidade (valor máximo para RGB) de 255.
___
### Lista de comandos

|  Comando   | Input                                                                      | Exemplo                                   |
|------------|----------------------------------------------------------------------------|-------------------------------------------|
| image      |  image **_largura altura_**                                                | `image 1920 1080`                         |
| open       | open **_nome_imagem_**                                                     | `open imagem.ppm`                         |
| save       | save **_nome_imagem_**                                                     | `save imagem.ppm`                         |
| compress   | compress **_nome_imagem_**                                                 | `compress imagem.ppm`                     |
| decompress | decompress **_nome_imagem_comprimida_**                                    | `decompress imagem.txt`                   |
| color      | color **_red green blue_**                                                 | `color 255 0 0`                           |
| clear      | clear **_red green blue_**                                                 | `clear 255 255 255`                       |
| fill       | fill **_coordenada_largura coordenada_altura_**                            | `fill 1300 100`                           |
| rect       | rect **_coordenada_largura coordenada_altura largura altura_**             | `rect 1020 300 30 20`                     |
| polygon    | polygon **_numero_pontos coordenada_largura_p1 coordenada_altura_p1 ..._** | `polygon 4 30 400 500 20 300 250 100 100` |
| circle     | circle **_coordenada_largura coordenada_altura raio_**                     | `circle 250 200 50`  |
##### Exemplos de arquivo input
> image 500 500 (cria uma imagem com resolução 500x500)  
clear 255 255 255 (pinta tudo de branco)  
color 0 0 0 (define a cor do píncel de preto)¹  
circle 250 250 50 (desenha um círculo no centro do desenho com raio 50)  
color 255 0 0 (define a cor do píncel de vermelho)  
fill 250 250 (usa o fill a partir do centro do desenho, só pintando o circulo desenhado)  
color 0 0 0 ¹  
rect 0 0 40 40 (desenha um quadrado a partir do primeiro pixel, com lado 40)  
polygon 3 100 360 65 420 135 420 (desenha um triângulo)  
save desenho.ppm (salva o desenho com o nome "desenho.ppm")  
compress desenho.ppm (comprime a imagem para o arquivo "desenho.txt")  

###### OBS: Exemplo anterior presente na pasta inputs.  

>open desenho.ppm (abre a imagem feita no exemplo anterior para ser editada)  
clear 0 0 255 (pinta tudo de azul)  
save desenho.ppm (salva a imagem)  
___
O que foi feito e as funções responsáveis (presentes em primitivas.c):
* Criação dos tipos de dados necessários (typedef, structs e enums);
* Modularização do programa;
* Leitura do arquivo de especificação;
* Geração de uma imagem  PPM;
  * image
  > Será lido do arquivo a resolução da imagem e inserido na variável desenho a partir do ponteiro ptr_desenho. O ptr_desenho->Y corresponde a largura e o ptr_desenho->X corresponde a altura. Então, a matriz de pixels que foi alocada inicialmente com tamanho 1, será realocada para o tamanho das variáveis citadas utilizando o método padrão para matrizes alocadas dinamicamente.
  * open
  > Será lido do arquivo o nome da imagem da qual realizará-se a leitura, será verificada se é uma imagem válida a partir do formato e da qualidade e será lida a resolução e inserida nas variáveis ptr_desenho->Y, correspondendo a largura e, ptr_desenho->X correspondendo a altura. Então realocará-se a matriz de pixels para o tamanho da imagem lida e é copiada as cores, pixel por pixel, da imagem para a matriz.
  * save
  > É lido o nome do arquivo que será gerado e nele é inserido o formato (P3), a qualidade (255), que são fixos, e a resolução, que está presente nas variáveis ptr_desenho->Y e ptr_desenho->X. Então é escrito em cada linha do arquivo a cor de cada pixel, caracterizando uma imagem reconhecível pelo formato.
* Desenho de retas;
  * line
  > Calcula a inclinação a partir da razão entre o delta y e o delta x, calcula um parâmetro de decisão com base no valor absoluto do delta y e do delta x e considera a inclinação como 1 caso o delta y ou o delta x tenha valor 0 para evitar cálculos impossíveis. Então, dependendo do valor da inclinação, uma das três subfunções de line é chamada para traçar a reta.
  * line_straight
  > Pinta o pixel na coordenada recebida no parâmetro e, baseado no valor do x e do y final e inicial, ele realiza uma recursão e se invoca incrementando ou decrementando o valor do y ou do x.
  * line_x
  > Pinta o pixel na coordenada recebida no parâmetro e, se o x ou o y forem diferentes do valor final, ele verifica se algum dos dois é igual, nesse caso chamando a função line_straight, se não, ele analisa a variável de decisão e a incrementa baseada em alguns cálculos, realizando uma recursão e se invocando e, dependendo da decisão tomada e da relação entre o x e o y final e inicial, ele incrementa e/ou decrementa o x e/ou y. A diferença em relação ao line_x é que quando ele só altera um dos eixos, ele só altera o x.
  * line_y
  > Pinta o pixel na coordenada recebida no parâmetro e, se o x ou o y forem diferentes do valor final, ele verifica se algum dos dois é igual, nesse caso chamando a função line_straight, se não, ele analisa a variável de decisão e a incrementa baseada em alguns cálculos, realizando uma recursão e se invocando e, dependendo da decisão tomada e da relação entre o x e o y final e inicial, ele incrementa e/ou decrementa o x e/ou y. A diferença em relação ao line_x é que quando ele só altera um dos eixos, ele só altera o y.
* Desenho de polígonos;
  * rect
  > Recebe um ponto inicial, uma largura e uma altura e verifica se o retângulo cabe na imagem, sendo traçado na ordem de sentido sudeste, nordeste, noroeste, sudoeste. Para isso, ele verifica se a coordenada + medida é menor que o desenho, se for, cabe nesse sentido, se não, ele verifica se cordenada + medida é > desenho e coordenada - medida >= 0 (para não sair do desenho ao traçar para o outro lado). Assim que ele verifica que consegue traçar em algum dos quatro sentidos na ordem, ele chama a função line_straight quatro vezes.
  * polygon
  > Lê no arquivo a quantidade de pontos que o usuário inseriu e realoca o vetor poligono com essa quantidade + 1. Então ele insere no vetor a partir do índice 1 os pontos que está no arquivo input e, quando o loop percebe que chegou no último ponto, ele copia ele último ponto para o índice zero. Assim, quando o polígono for traçado, ele irá ser fechado. Em seguida, o polígono será desenhado a partir dos pontos do vetor de trás para frente com um for iniciando pela quantidade de pontos do polígono. Então é invocada a função line utilizando o índice atual do for e o índice anterior e, em seguida, o vetor é realocado para o valor do índice.
* Desenho de circúlos;
  * circle
  > Recebe do arquivo input um ponto do desenho e um raio e chama uma subfunção (circle_line) que irá desenhar o circulo, enviando para ela alguns parâmetros de decisão que serão utilizados para o cálculo do próximo pixel a ser pintado pela função.
  * circle_line
  > O circle_line recebeu como parâmetro o valor 0 para a variável x e o valor do raio para a variável y, além da variável de decisão. Assim, enquanto o x for menor ou igual ao y, ele vai pintar um pixel em cada um dos oito octantes e vai verificar o parâmetro de decisão. Esse parâmetro será incrementado a partir de determinado cálculo dependendo do seu valor atual, e o y poderá ser decrementado, mas o x sempre será incrementado. Por fim, a função utiliza recursão e se invoca, ou seja, dessa forma ela vai parar quando desenhar todo o perímetro de um octante, que é quando o valor do x e do y vão se encontrar e, como ela está pintando oito pixels por vez, ela já terá pintado o círculo todo.
* Cores no geral;
  * color
  > Lê do arquivo três valores correspondentes ao RGB e insere na variável global pincel para serem utilizados como cor pelas próximas funções.
  * paint_pixels
  > Uma função que é só um trecho de código que foi muito repetido no projeto. Ele atribui a cor do pincel para o pixel que foi inserido como parâmetro.
  * color_picker
  > Lê do pixel inserido como parâmetro três valores correspondentes ao RGB e insere na variável global pincel_fill para a função fill saber qual cor ela deve pintar.
  * clear
  > Lê do arquivo os valores correspondentes ao RGB e copia essa cor por meio de loops para cada pixel da matriz do desenho.
* Preenchimento de cores;
  * fill
  > Lê do arquivo input uma coordenada no desenho, usa a função color_picker nesse ponto para saber qual cor pintar e chama as funções de spread para iniciar o preenchimento.
  * fill_spread_right
  > Pinta o pixel que recebeu como parâmetro e verifica se os três pixels acima, a direita e abaixo estão dentro do desenho e se são da cor do pincel_fill. Caso forem, continua a recursão se invocando para cada uma das verificações.
  * fill_spread_left
  > É um complemento da fill_spread_right, pintando o pixel que recebeu como parâmetro, mas verificando se os três pixels acima, a esquerda e abaixo estão dentro do desenho e se chamando. Porém, para preencher todas as lacunas, essa função também verifica para a direita, mas é a última verificação e a fill_spread_left é chamada depois, sendo que, nessa verificação, ela invoca a fill_spread_right. 
###### Essa divisão de fill_spread foi feita porque uma função só verificando para todas as direções estava causando stack overflow. Dessa forma que foi realizada, além de diminuir as chamadas de uma mesma função, a função que faria mais verificações é chamada por último, então ela necessariamente realiza menos trabalho, e ela invoca a outra função para o seu complemento.
* Compressão e descompressão de imagem;
  * compress
  > É lido o nome da imagem a ser comprimida e, com esse mesmo nome, é retirada a "extensão" .ppm, inserida a .txt e então aberto um arquivo com esse nome no modo escrita. Da imagem a ser comprimida é lida a resolução e verificados o formato e qualidade e então é printado no arquivo essas informações. Em seguida é lida a cor na primeira linha da imagem e inseridas nas variáveis red, green, blue, red_atual, green_atual, blue_atual e começa um loop. Nesse loop é verificado se a cor (red, green, blue) é diferente da cor atual, se for, é imprimido no arquivo comprimido o contador (quantas vezes a cor atual foi lida) e a cor atual, e também a cor lida vira a cor atual e o contador volta para 1. Além dessa verificação, é verificado se a leitura `fscanf (imagem, "%d %d %d", &red, &green, &blue)  == EOF`, isso faz com que as cores da imagem sejam lidas até os pixels acabarem e, como não tem como comparar a ultima cor, quando chegar no final do arquivo imagem é imprimido no arquivo comprimido o contador e a cor dessa ultima.
  * decompress
  > Lê o nome do arquivo comprimido, transforma esse nome de .txt para .ppm e abre um arquivo descomprimido com esse nome no modo escrita. Então lê a resolução e checa a qualidade e formato e os imprime de maneira reconhecível no arquivo descomprimido. Então, em cada conjunto de cor que o laço de repetição encontrar, ele imprime no descomprimido uma linha da cor na quantidade de vezes do contador que a precede até chegar no fim do arquivo comprimido.
  
O que não foi feito:
* Interface gráfica (o design foi iniciado e o funcionamento isolado, mas não teve tempo de aplicar no programa)

O que seria feito diferentemente:
* Não teriam sido utilizadas variáveis globais no arquivo tipos.h para diminuir a utilização de ponteiros e parâmetros em algumas funções;
* Desde o início do desenvolvimento do projeto, houve a confusão da posição da altura com largura na leitura e escrita no arquivo input e na imagem. Então foi invertido no arquivo e acabou que a largura virou o eixo y e a altura virou o eixo x, o que acabou ficando confuso e para corrigir isso teria que mudar bastante coisa no código, só que isso não daria tempo.

Como compilar e rodar o projeto:
* Execute o comando `make all` no terminal aberto na pasta com todos os 7 arquivos modularizados;
* (Opcional) Após executar o comando `make all`, execute o comando `make clean` para deletar os arquivos .o desnecessários;
* Será produzido um arquivo chamado `projeto`, execute-o no terminal.
___
| Integrantes      | Atribuições |
| ----------- | ----------- |
| Antonio Higino Bisneto Leite Medeiros      | Lógica, Documentação      |
| Fabrício Moura Jácome   | Lógica, Coding, Documentação    |
