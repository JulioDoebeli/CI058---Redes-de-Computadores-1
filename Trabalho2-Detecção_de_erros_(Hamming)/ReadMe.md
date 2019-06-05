## Trabalho 2 - Deteção de erros com Código Hamming(15,11)
### Especificação e Objetivo do Trabalho 
  - Peso: 1,0.
  - Pode ser feito em dupla ou individual.
  - Entrega e apresentação: 05/06/2019.  
  - Implementar o Codificador e Decodificador Hamming(15,11).
  
## Relatório de Entega
  Implementei dois programas Txt2HammingCode.c e HammingCode2Txt.c. 
  - O programa Txt2HammingCode.c recebe uma entrada texto ASCII e gera uma saida Binaria codficada em Hamming(15,11).
  - O programa Txt2HammingCode.c recebe uma entrada Binaria codficada em Hamming(15,11) e gera uma saida texto ASCII e gera na tela do terminal um relatório de execusão.
  
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

Caso hajam erros trataveis ou corrigiveis no código hamming eles devem ser corrigidos e enviar uma mensagem de warning deve ser enviada para o a saida stderr e continuar com a execução.
Caso hajam erros in-trataveis ou incorrigiveis no código hamming deve-se enviar uma mensagem de ERRO deve ser enviada para a saida stderr e continuar com a execução, mas não gerar arquivo de saída.

```
if(arcv >= 1){
  FILE entrada_arquivo_texto = fopen(argv[1],"r");
}else if(arcv == 2){
  FILE entrada_arquivo_texto = fopen(argv[2],"r");
}

int ch = fgetchar(entrada_arquivo_texto);
int aux1, aux2;
 while( !eof(ch) ){
    
    aux1 = ((ch/16)%16);
    if      ( 0<= aux1 && aux1<= 9) aux1 += '0';
    else if (10<= aux1 && aux1<=15) aux1 += 'A';
    else{
      fprintf(stderr,"ERRO aux1 = %d\n",aux1);
      Return ERROR;
    }
    
    aux2 = ch%16;
    if      ( 0<= aux2 && aux2<= 9) aux1 += '0';
    else if (10<= aux2 && aux2<=15) aux1 += 'A';
    else{
      fprintf(stderr,"ERRO aux2 = %d\n",aux1);
      Return ERROR;
    }
    
    fprintf(stdout,"%c%c",(char)aux1,(char)aux2);
  }
```
