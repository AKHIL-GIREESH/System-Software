#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
{
 	printf("pass 2");
	char opcode[10],mnemonic[3],operand[10],label[10],code[10],leng[10],finalAddress[10],locctr[10],left[10],right[10],stringg[100],stringgg[100];
	int start,length,c,string_length,set=0,j=0;
	FILE *fin,*fop,*f_final,*fsym,*f_leng;
	fin=fopen("inter.txt","r");
	fop=fopen("optab.txt","r");
	fsym=fopen("symtab.txt","r");
	f_final=fopen("object_code.txt","w");
	f_leng=fopen("len.txt","r");
	fscanf(fin,"%s%s%s",label,opcode,finalAddress);
	if(strcmp(opcode,"START")==0)
	{
		start=atoi(operand);
		fprintf(f_final,"H^");
		fprintf(f_final,"%s 00%s ",label,finalAddress);
		fscanf(f_leng,"%s",leng);
		fprintf(f_final,"%s\n",leng);
		fprintf(f_final,"T^%s ",finalAddress);
		
		while(strcmp(opcode,"END")!=0)
		{
			fscanf(fin,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
			
			rewind(fop);
			while(!feof(fop))
			{
				fscanf(fop,"%s%s",code,mnemonic);
				if(strcmp(opcode,code)==0)
				{
					strcat(stringg,mnemonic);
					rewind(fsym);
					while(!feof(fsym))
					{
						fscanf(fsym,"%s%s",left,right);
						if(strcmp(left,operand)==0)
						{
							strcat(stringg,right);
							break;
						}
					}
					break;
				}
			}
			if(strcmp(opcode,"WORD")==0)
			{
				strcat(stringg,"00000");
				strcat(stringg,operand);
			}else if(strcmp(opcode,"BYTE")==0){
				string_length=strlen(stringg);
				stringg[string_length]=operand[2];
				stringg[string_length+1]=operand[3];
			}
	}
	string_length=strlen(stringg);
	string_length=string_length/2;
	sprintf(leng,"%X",string_length);
	fprintf(f_final,"%s ",leng);
	for(int i=0;i<strlen(stringg);i++){
		stringgg[j]=stringg[i];
		j++;
		set++;
		if(set==6){
			set=0;
			stringgg[j]=' ';
			j++;
		}
	}
	fprintf(f_final,stringgg);
	fprintf(f_final,"\nE^00%s",finalAddress);
	}
		fclose(fin);
		fclose(fop);
		fclose(f_final);
		fclose(f_leng);
		fclose(fsym);
}

