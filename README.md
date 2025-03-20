# Tutorial de como usar o Unity (framework de testes embarcados)

O Unity pode ser utilizado com qualquer projeto em c, mas devido a sua compatibilidade e baixo overhead, é amplamente utilizado em testes de sistemas embarcados onde o poder de processamento é baixo.
  

## Organizando o ambiente

Primeiramente é necessário baixar a biblioteca no site (https://github.com/ThrowTheSwitch/Unity/archive/refs/heads/master.zip)   
Obs: O link acima instala a biblioteca Unity diretamente.

Após instalar, extraia a pasta para o diretório desejado, não precisa ser no diretório do projeto.  

No diretório onde está o projeto, será necessário fazer o um include dos arquivos unity.c e unity.h,
que podem ser referenciados da seguinte forma:

"  
#include <stdio.h> // includes necessários para o teste  
#include <assert.h>  
#include "C:\caminho-do-arquivo\src\unity.h" // caminho onde esta a biblioteca unity  
#include "C:\caminho-do-arquivo\src\unity.c"  

// bloco de testes  
"  

Ou copie e cole os arquivos unity.c e unity.h no diretórios onde serão feito os testes referenciando-os no arquivo de testes apenas com (#include "unity.h").

## Ferramentas do Unity (setUp e Teardown)

No Unity existem funções predeterminadas para fazer o setup e teardown , essas funções tem sintaxe predeterminada:

void setUp (void) {] // Realiza o processamento previo caso precise.  
void tearDown () {} //  Realiza o processamento após cada teste.  

Então o algoritmo do Unity verifica se existem essas duas funções e faz o processamento necessário antes e depois de cada teste. 

## Ferramentas de asserts

No unity.h tem detalhado todos os asserts, Segue alguns asserts importantes:

TEST_ASSERT_EQUAL_INT(expected, actual) // verifica 2 valores, se o resultado for igual o teste passa, se não o teste falha.  
TEST_ASSERT_EQUAL_INT(i+j, add(i,j)); // Pode ser usado funções e expressões numéricas no expected e actual.  

TEST_ASSERT_EQUAL_UINT8(expected, actual) // O Unity converte os valores para o tipo especificado antes de fazer o teste (assim como nos tests acima).  

TEST_FAIL() // Utilizado para fazer manualmente os testes, executando algoritmos e determinando se o teste falhou.  
TEST_IGNORE(): // Ignora o teste, nem passa e nem falha.

## Ferramentas de cobertura

O Unity não tem testes de cobertura de código, mas pode ser intregados a ferramentas que tem o teste (Ceedling por exemplo).  
O próprio compilador GCC tem ferramentas nativas de lcov e gcov.

## Particularidade da ferramenta

Pode ser usado em testes de sistemas embarcados, segue um algortmo de exemplo:

```cpp
#ifdef UNIT_TEST
#include "unity.h"
#else
#include <Arduino.h>
#endif

#define LED_PIN 13
#define SENSOR_PIN A0

// Retorna HIGH se o valor do sensor for menor que 10, caso contrário retorna LOW.
int computeLEDState(int sensorValue) {
    return (sensorValue < 10) ? HIGH : LOW;
}

#ifdef UNIT_TEST

void setUp(void) {}

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

No exemplo acima, caso na build do firmware tenha a tag -DUNIT_TEST, o codigo executa da flag "#ifdef UNIT_TEST" até a flag "#else", retornando uma mensagem na serial com o resultado do teste e parando a execução. Para rodar o código normalmente basta tirar o -DUNIT_TEST da build do firmware.

## Resultados do teste 

Os resultados do teste ficam da seguinte forma:

PS C:\Users\peusu\Desktop\Stellantis\automacaoTestes\Projeto Final (Unity)> .\test_sum.exe  
test_sum.c:31:test_AddPositiveNumbers:PASS  
test_sum.c:32:test_AddNegativeNumbers:PASS  
test_sum.c:33:test_AddMixedNumbers:PASS  
test_sum.c:34:test_AddZero:PASS  
test_sum.c:35:test_AddLargeNumbers:PASS  

5 Tests 0 Failures 0 Ignored  
OK

Exemplo com falha:

PS C:\Users\peusu\Desktop\Stellantis\automacaoTestes\Projeto Final (Unity)> .\test_sum2  
test_example.c:31:test_add:PASS  
test_example.c:24:test_add_2:FAIL  

2 Tests 1 Failures 0 Ignored    
FAIL

Detalho a build no diretório exemplo.

## Desvantagens de usar o Unity

O Unity é um framework simples e minimalista. Acaba sendo necessário a integração com outras ferramentas (por exemplo, CMock) para essas funcionalidades mais complexas.

Configurar o ambiente de build para compilar, linkar e carregar os testes no hardware (sistemas embarcados) ou em simuladores pode ser trabalhoso, principalmente para quem está começando.

Os relatórios gerados pelo Unity são geralmente simples e baseados em saída serial ou texto, o que pode ser menos amigável comparado a frameworks com interfaces visuais ou relatórios integrados.
