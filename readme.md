# Programa de Manipulação de Matrizes
##### _Autor: Reginaldo Mota (O Régis)_

Este repositório contém um programa para manipulação de matrizes. Para isso, foi utilizada a linguagem de programação C++ e os conceitos do paradigma orientado a objetos.

## Classes desenvovidas:

### Matrix:
Representa uma matriz.
#### Atributos
|Atributo|Tipo|Descrição|
|:-:|:-:|:-:|
|determinant|double|Armazena o determinante da matriz|
|rows|int|Armazena a quantidade de linhas da matriz|
|collumns|int|Armazena a quantidade de colunas da matriz|
|elements|double**|Armazena os elementos da matriz|

#### Métodos
|Métodos|Parâmetros|Retorno|Descrição|
|:-:|:-:|:-:|:-:|
|Matrix|double** elements, int rows, int collumns|void|Construtor padrão que recebe uma matriz com elementos, a quantidade de linhas e a quantidade de colunas|
|Matrix|int rows, int collumns, bool isRandom = true|void|Construtor que recebe a quantidade de linhas e a quantidade de colunas, e tem um parâmetro opcional que por padrão é setado como true, caso seja true a matriz é criada com elementos aleatórios, caso contrário é criada uma matriz identidade|
|Matrix|const Matrix &toCopy|void|Construtor de cópia|
|~Matrix||void|Destrutor responsável por desalocar a memória da matriz de elementos da matriz|
|getRows||int|Retorna o valor do atributo rows|
|getCollumns||int|Retorna o valor do atributo collumns|
|getElement|int row, int collumn|double|Retorna o elemento armazenado na matriz elements na posição [row, collumn] |
|size||int*|Retorno um vetor de duas posições com os valores de linhas e colunas da matriz|
|getDeterminant||double|Retorna o valor do determinante da matriz|
|transposed||Matrix|Retorna a Matrix transposta|
|getDiagonalProductSum|bool invert_direction = false|double|Retorna a soma dos produtos de diagonais, de acordo com o parâmetro, caso true, o retorno é referente às diagonais principais, caso contrário às diagonais secundárias|
|isSquareMatrix||bool|Retorna se a matriz é quadrada|
|isIdentityMatrix||bool|Retorna se a matriz é identidade|
|cofactor|int row, int collumn|double|Retorna o cofator relacionado ao elemento de posição [row, collumn]|
|cofactorMatrix||Matrix|Retorna a Matrix dos cofatores|
|inverseMatrix||Matrix|Retorna a Matrix inversa|

#### Sobrecarga de Operadores
|Operador|Parâmetro|Retorno|Descrição|
|:-:|:-:|:-:|:-:|
|+|const Matrix& otherMatrix|Matrix|Realiza a soma de duas matrizes|
|-|const Matrix& otherMatrix|Matrix|Realiza a subtração de duas matrizes|
|-||Matrix|Inverte os sinais dos elementos da matriz|
|*|const Matrix& otherMatrix|Matrix|Realiza a multiplicação de duas matrizes|
|*|const double right|Matrix|Realiza a multiplicação de uma constante por uma matriz|
|/|const double right|Matrix|Realiza a divisão dos elementos de uma matriz por uma constante|
|!=|const Matrix& otherMatrix|bool|Verifica se duas matrizes são difetentes|
|==|const Matrix& otherMatrix|bool|Verifica se duas matrizes são iguais|
|<<|ostream& os, const Matrix& otherMatrix|ostream&|Implementa a impressão de uma matriz|
|!||Matrix|Retorna a matriz inversa|