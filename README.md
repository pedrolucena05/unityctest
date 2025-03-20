# Tutorial de como usar o Unity (framework de testes embarcados)

O Unity pode ser utilizado com qualquer projeto em c, mas devido a sua compatibilidade e baixo overhead, é amplamente utilizado em testes de sistemas embarcados onde o poder de processamento é baixo.
  

## Organizando o ambiente

Primeiramente é necessário baixar a biblioteca no site (https://github.com/ThrowTheSwitch/Unity/archive/refs/heads/master.zip) 
Obs: O link acima instala a biblioteca Unity diretamente.

Após instalar extraia a pasta para o diretório desejado, não precisa ser no diretório do projeto.  

No diretório onde esta o projeto que você irá fazer os testes, será necessário fazer o um include dos arquivos .c e .h do framework,
você pode referencia-los no seu arquivo de testes da seguinte forma:

"
#include <stdio.h> // includes necessários para o teste
#include <assert.h>
#include "C:\caminho-do-arquivo\src\unity.h" // caminho onde esta a biblioteca unity
#include "C:\caminho-do-arquivo\src\unity.c"

// bloco de testes
"

Ou copie e cole os arquivos unity.c e unity.h no diretórios onde serão feito os testes refereniando apenas com o (#include "unity.h")

## Ferramentas do Unity (setUp e Teardown)

No Unity existem funções predeterminadas para fazer o setup e teardown , essas funções tem sintaxe predeterminada:

void setUp (void) {] // Realiza o processamento previo caso precise.
void tearDown () {} //  Realiza o processamento após cada teste.

Então o algoritmo do Unity verifica se existem essas duas funções e faz o processamento necessário antes e depois de cada teste. 

## Ferramentas de asserts

No unity.h tem detalhado todos os asserts, Segue alguns asserts importantes:

TEST_ASSERT_EQUAL_INT(expected, actual) // verifica 2 valores, se o resultado for igual o teste passa, se não o teste falha.
TEST_ASSERT_EQUAL_INT(i+j, add(i,j)); // Pode ser usado funções e valores no expected e actual.

TEST_ASSERT_EQUAL_UINT8(expected, actual) // O Unity converte os valores para o tipo especificado antes de fazer o teste.

TEST_FAIL() // Utilizado para fazer manualmente os testes, executando algoritmos e determinando se o teste falhou.
TEST_IGNORE(): // Ignora o teste, nem passa e nem falha.
