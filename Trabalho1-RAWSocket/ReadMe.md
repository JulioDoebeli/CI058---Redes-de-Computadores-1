## Trabalho 1 - Comunicação entre dois computadores usando RAWSocket 
  - Peso: 3,0 
  - Entrega e apresentação: 05/06/2019  
  - Função de abertura do RAWSocket em modo Promíscuo - código em C  

### Objetivos do Trabalho 
  Implementar dois programas Txt2HammingCode.c e HammingCode2Txt.c
  
#### Txt2HammingCode.c
O programa Txt2HammingCode.c recebe dois parametros vide modelo abaixo:

```
./Txt2HammingCode <entrada_arquivo_texto.txt> <saida_arquivo_HammingCode.txt>
```
entrada_arquivo_texto.txt e saida_arquivo_HammingCode.txt representam os parametros de chamada do programa, esses parametros são strings que representam o caminho dos arquivos de entrada e saida respectivamente.

#### HammingCode2Txt.c
O programa HammingCode2Txt.c recebe dois parametros vide modelo abaixo:
```
./HammingCode2Txt <entrada_arquivo_HammingCode.txt> <saida_arquivo_texto.txt>
```
entrada_arquivo_texto.txt e saida_arquivo_HammingCode.txt representam os parametros de chamada do programa, esses parametros são strings que representam o caminho dos arquivos de entrada e saida respectivamente.

Caso hajam erros trataveis no código hamming eles devem ser corrigidos e enviar uma mensagem de warning deve ser enviada para o a saida stderr e continuar com a execução.
Caso hajam erros in-trataveis no código hamming deve-se enviar uma mensagem de ERRO deve ser enviada para o a saida stderr e abortar a execução.

#### Txt2Hex.c & HammingCode2Hex.c
O programa Txt2Hex.c e HammingCode2Hex.c são programas auxiliares.
Eles imprimem texto e hamining code em formato Hexadecimal na tela do terminal.
Cada um deles rececem um ou dois parametros de chamada vide modelos abaixo:
```
./Txt2Hex         <entrada_arquivo_texto.txt>
./Txt2Hex         <entrada_arquivo_texto.txt>       <saida_arquivo_Hex.txt>
./HammingCode2Hex <entrada_arquivo_HammingCode.txt>
./HammingCode2Hex <entrada_arquivo_HammingCode.txt> <saida_arquivo_Hex.txt>

```

##### Txt2Hex.c
```
FILE entrada_arquivo_texto = fopen(argv[1],"r");
FILE entrada_arquivo_texto = fopen(argv[1],"r");
int ch = fgetchar(entrada_arquivo_texto);
  while( !eof(ch) ){
    printf(
    
  }

./HammingCode2Hex <entrada_arquivo_HammingCode.txt>
```
