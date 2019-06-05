/*
 * main2.c
 * 
 * Copyright 2019 julio doebeli <julio@julio-N501JW>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>		/* for CHAR_BIT */
#define MAX_SIZE        (100)
#define BUFFER_IN_MAX   (11*MAX_SIZE)
#define BUFFER_PD_MAX   (11*8*MAX_SIZE)
#define BUFFER_ED_MAX   (15*8*MAX_SIZE)
#define BUFFER_OUT_MAX  (15*MAX_SIZE)
void charToBinary(char ch_in, char *ch_out){
	for (int i = 0; i < 8; i++){
		if (ch_in%2 == 0) ch_out[7-i] = '0';
		else              ch_out[7-i] = '1';
		ch_in/=2;
	}
}
void binaryToChar(char *arr_in, char *ch_out){
	*ch_out = 0;	
	for (int i = 0; (i<8); i+=1){
		if      (arr_in[i] == '0') arr_in[i] = 0;
		else if (arr_in[i] == '1') arr_in[i] = 1;
		*ch_out = 2 * (*ch_out) + arr_in[i];
		if      (arr_in[i] == 0) arr_in[i] = '0';
		else if (arr_in[i] == 1) arr_in[i] = '1';
	}
}
void hamming_15_11_block_encoder(char in[11], char *out){
	for (int i = 0; (i<11); i+=1){
		if (in[i] == '0') in[i] = 0;
		if (in[i] == '1') in[i] = 1;
	}
	out[0]  = (in[0]+in[1]+in[3]+in[4]+in[6]+in[8]+in[10])%2;
	out[1]  = (in[0]+in[2]+in[3]+in[5]+in[6]+in[9]+in[10])%2; 
	out[2]  =  in[0];
	out[3]  = (in[1]+in[2]+in[3]+in[7]+in[8]+in[9]+in[10])%2;
	out[4]  =  in[1];
	out[5]  =  in[2];
	out[6]  =  in[3];
	out[7]  = (in[4]+in[5]+in[6]+in[7]+in[8]+in[9]+in[10])%2;
	out[8]  =  in[4];
	out[9]  =  in[5];
	out[10] =  in[6];
	out[11] =  in[7];
	out[12] =  in[8];
	out[13] =  in[9];
	out[14] =  in[10];
	for (int i = 0; (i<11); i+=1){
		if (in[i] == 0) in[i] = '0';
		if (in[i] == 1) in[i] = '1';
	}
	for (int i = 0; i < 15; i++){
		if(out[i] == 0) out[i] = '0';
		if(out[i] == 1) out[i] = '1';
	}
}

int hamming_15_11_block_decoder(char in[15], char out[11]){
	for (int i = 0; (i<15); i+=1){
		if (in[i] == '1') in[i] = 1;
		else if (in[i] == '0') in[i] = 0;
	}
	
	int error_index[4];
	error_index[0] = (in[0] + in[2] + in[4] + in[6]  + in[8]  + in[10] + in[12] + in[14]) % 2;
	error_index[1] = (in[1] + in[2] + in[5] + in[6]  + in[9]  + in[10] + in[13] + in[14]) % 2;
	error_index[2] = (in[3] + in[4] + in[5] + in[6]  + in[11] + in[12] + in[13] + in[14]) % 2;
	error_index[3] = (in[7] + in[8] + in[9] + in[10] + in[11] + in[12] + in[13] + in[14]) % 2;
	int erro_position = 1*error_index[0] + 2*error_index[1] + 4*error_index[2] + 8*error_index[3];
	
	if( (0<erro_position) && (erro_position<15) )	{
		if( in[erro_position-1] == 0)
			in[erro_position-1] = 1;
		else
			in[erro_position-1] = 0;
	}
	
	out[0] = in[2];
		
	out[1] = in[4];
	out[2] = in[5];
	out[3] = in[6];
	
	out[4] = in[8];
	out[5] = in[9];
	out[6] = in[10];
	out[7] = in[11];
	out[8] = in[12];
	out[9] = in[13];
	out[10] = in[14];
	
	for (int i = 0; i < 15; i+=1){
		if (in[i] == 0) in[i] = '0';
		else if (in[i] == 1) in[i] = '1';
	}
	
	for (int i = 0; i < 11; i++){
		if(out[i] == 0) out[i] = '0';
		else if(out[i] == 1) out[i] = '1';
	}
	
	return erro_position;
}
int main(int argc, char **argv){
	int i = 0, j = 0;
	fprintf(stdout,"input file  = %s\n", argv[1]);fflush(stdout);
	fprintf(stdout,"output file = %s\n", argv[2]);fflush(stdout);
	FILE *f_in;  f_in  = fopen(argv[1], "rb");  // r for read,  b for binary
	if (f_in == NULL) {
		fprintf(stdout,"Não foi aberto arquivo de entrada\n");fflush(stdout);
		return -1;
	}
	FILE *f_out; f_out = fopen(argv[2], "wb");  // w for write, b for binary
	if (f_out == NULL) {
		fprintf(stdout,"Não foi aberto arquivo de saida\n");//fflush(stdout);
		return -1;
	}
	int cha = 0;
	fseek(f_in, 0L, SEEK_END);
	int in_size;  in_size = ftell(f_in)-1;
	int pd_size;  pd_size = (8*in_size);
	int ed_size;  ed_size = (8*15*in_size + 10)/11;
	int out_size; out_size= (  15*in_size + 10)/11;
	
	fseek(f_in, 0L, SEEK_SET);
	//fprintf(stdout,"in_size = %d\n",in_size); fflush(stdout);
	//fprintf(stdout,"pd_size = %d\n",pd_size); fflush(stdout);
	//fprintf(stdout,"ed_size = %d\n",ed_size); fflush(stdout);
	//fprintf(stdout,"out_size = %d\n",out_size); fflush(stdout);
	
	char *input_data_buffer   = NULL;
	char *plain_data_buffer   = NULL;
	char *encoded_data_buffer = NULL;
	char *output_data_buffer  = NULL;
	
	input_data_buffer   = (char*)malloc(sizeof(char)*(1 +  in_size));
	plain_data_buffer   = (char*)malloc(sizeof(char)*(1 +  pd_size));
	encoded_data_buffer = (char*)malloc(sizeof(char)*(1 +  ed_size));
	output_data_buffer  = (char*)malloc(sizeof(char)*(1 + out_size));
	
	if (input_data_buffer  == NULL) input_data_buffer  = (char*)malloc(sizeof(char)*(1 +  in_size));
	if (plain_data_buffer   == NULL) plain_data_buffer  = (char*)malloc(sizeof(char)*(1 +  pd_size));
	if (encoded_data_buffer == NULL) input_data_buffer  = (char*)malloc(sizeof(char)*(1 +  ed_size));
	if (output_data_buffer == NULL) output_data_buffer = (char*)malloc(sizeof(char)*(1 + out_size));
	
	for(i = 0; i < (1 +  in_size); i++) input_data_buffer[i]   = '0';
	for(i = 0; i < (1 +  ed_size); i++) encoded_data_buffer[i] = '0';
	for(i = 0; i < (1 +  pd_size); i++) plain_data_buffer[i]   = '0';
	for(i = 0; i < (1 + out_size); i++) output_data_buffer[i]  = '0';
	
	input_data_buffer[   in_size  + 1] = '\0';
	plain_data_buffer[   pd_size  + 1] = '\0';
	encoded_data_buffer[ ed_size  + 1] = '\0';
	output_data_buffer[  out_size + 1] = '\0';
	
	fseek(f_in, 0L, SEEK_SET);
	
	cha = getc(f_in);
	for (i = 0; (i<BUFFER_IN_MAX) && (feof(f_in) == 0); i++){
		//fprintf(stdout,"%c",cha);
		input_data_buffer[i] = (char)cha;
		//fprintf(stdout,"%c",input_data_buffer[i]);
		cha = getc(f_in);
	}
	for (i = 0,j = 0; (i<in_size) && (j<pd_size); i++,j+=8){
		charToBinary(input_data_buffer[i], &plain_data_buffer[j]);
	}
	for (i = 0,j = 0; (i<pd_size) && (j<ed_size); i+=11,j+=15) {
		hamming_15_11_block_encoder(&plain_data_buffer[i], &encoded_data_buffer[j]);
	}
	for (i = 0; (i<ed_size); i+=1){
		if (encoded_data_buffer[i] == 0)        encoded_data_buffer[i] = '0';
		else if (encoded_data_buffer[i] == 1)   encoded_data_buffer[i] = '1';
	}
	/*for (i = 0,j = 0; (i<pd_size) && (j<out_size); i+=8,j+=1) {
		binaryToChar(&encoded_data_buffer[i], &output_data_buffer[j]);
	}*/
	fprintf(stdout, "input_data_buffer  : %s",input_data_buffer);      fflush(stdout);
	fprintf(stdout, "plain_data_buffer  : %s\n",plain_data_buffer);    fflush(stdout);
	fprintf(stdout, "encoded_data_buffer: %s\n",encoded_data_buffer);  fflush(stdout);
	//fprintf(stdout, "output_data_buffer : %s\n\n",output_data_buffer); fflush(stdout);
	
	for (j = 0; j < (in_size*11)/15; j++){
		fprintf(stdout, "%d ",j);
		for (i = 0; i < 11; i++)
			fprintf(stdout, "%c",plain_data_buffer[11*j + i]);
		fprintf(stdout, " ");		
		for (i = 0; i < 15; i++)
			fprintf(stdout, "%c",encoded_data_buffer[15*j + i]);
		fprintf(stdout, "\n");
	}
	
	fwrite(encoded_data_buffer, 1, ed_size, f_out); fflush(f_out);
	//fprintf(f_out, "%s",output_data_buffer); fflush(stdout);
	
	fclose(f_in);
	fclose(f_out);
	
}
