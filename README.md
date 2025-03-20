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

Ou copie e cole os arquivos unity.c e unity.h no diretórios onde serão feito os testes referenciando no arquivo de testes apenas com (#include "unity.h").

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

## Ferramentas de cobertura

O Unity não tem testes de cobertura de código, mas pode ser intregados a ferramentas que tem o teste de cobertura (Ceedling por exemplo).
O proprio compilador GCC tem ferramentas nativas de lcov e gcov.

## Particularidade da ferramenta

Pode ser usado para testes de sistemas embarcados, segue um algortmo de exemplo:

```cpp #ifdef UNIT_TEST
#include "unity.h"
#else
#include <Arduino.h>
#endif

#define LED_PIN 13
#define SENSOR_PIN A0

// Função da aplicação: determina o estado do LED
// Retorna HIGH se o valor do sensor for menor que 10, caso contrário retorna LOW.
int computeLEDState(int sensorValue) {
    return (sensorValue < 10) ? HIGH : LOW;
}

#ifdef UNIT_TEST
// ====================
// Bloco de Testes Unitários
// ====================

// setUp() é executado antes de cada teste
void setUp(void) {}

// tearDown() é executado depois de cada teste
void tearDown(void) {}

// Teste 1: Se o valor do sensor for 5 (< 10), o LED deve acender (HIGH)
void test_LEDState_WhenSensorValueIsLessThan10(void) {
    TEST_ASSERT_EQUAL_INT(HIGH, computeLEDState(5));
}

// Teste 2: Se o valor do sensor for 10 ou maior, o LED deve estar apagado (LOW)
void test_LEDState_WhenSensorValueIsGreaterOrEqual10(void) {
    TEST_ASSERT_EQUAL_INT(LOW, computeLEDState(15));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_LEDState_WhenSensorValueIsLessThan10);
    RUN_TEST(test_LEDState_WhenSensorValueIsGreaterOrEqual10);
    return UNITY_END();
}

#else

// Código da aplicação
```  

No exemplo acima a flag "#ifdef UNIT_TEST" executa o código até a flag "#else" caso na build do firmware tenha a tag -DUNIT_TEST, então o código executa o trecho acima e retorma uma mensagem na serial com o resultado do teste. Para rodar o código normalmente basta tirar o -DUNIT_TEST da build do firmware.

 
