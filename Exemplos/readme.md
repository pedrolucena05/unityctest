## Como rodar o arquivo de testes

Para executar o código corretamente basta copiar os arquivos unity.c unity.h e unity_internals.h e executar o comando

gcc -DUNIT_TEST -o test_sum2 test_example.c sum.c unity.c -lm

O comando acima irá gerar um executável "test_sum2.exe" usando o arquivo de testes test_example.c

gcc -DUNIT_TEST -o test_sum test_sum.c sum.c unity.c -lm

Já o comando acima irá gerar um excutável "test_sum.exe" usando o arquivo de testes test_sum.c

Para rodar o arquivo de testes basta executar o aquivo .exe gerado com

.\nome-executavel.exe

E se quiser colocar o resultado no relatório faça o seguinte comando

.\nome-executavel.exe > nome-relatorio.txt