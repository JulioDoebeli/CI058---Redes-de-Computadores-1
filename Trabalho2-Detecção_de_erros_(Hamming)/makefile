all: Encode Decode

Encode: 
	gcc -Wall Txt2HammingCode.c -o Txt2HammingCode
Decode:
	gcc -Wall HammingCode2Txt.c -o HammingCode2Txt
run: 
	./Txt2HammingCode ./in.txt ./out.txt
	./HammingCode2Txt ./out.txt ./in3.txt
