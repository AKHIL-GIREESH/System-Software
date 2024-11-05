#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
{
	printf("pass 1");
	char opcode[10],mnemonic[3],operand[10],label[10],code[10],val[10],symbol[10];
	int locctr,start,length,c,flg=0;
	FILE *fpin1,*fop,*fpin2,*fsym,*fp2,*fp3;
	fpin1=fopen("input.txt","r");
	fop=fopen("optab.txt","r");
	fsym=fopen("symtab.txt","w+");
	fpin2=fopen("inter.txt","w+");
	fp2=fopen("len.txt","w+");
	fp3=fopen("len2.txt","w+");
	fscanf(fpin1,"%s%s%s",label,opcode,operand);
	if(strcmp(opcode,"START")==0)
	{
		start=atoi(operand);
		locctr=start;
		fprintf(fpin2,"\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(fpin1,"%s%s%s",label,opcode,operand);
	}
	else
	{
		locctr=0;
	}
	while(strcmp(opcode,"END")!=0)
	{
		fprintf(fpin2,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
		if(strcmp(label,"**")!=0)
		{
			fprintf(fsym,"%s\t%d\n",label,locctr);
		}
		rewind(fop);
		c=0;
		while(!feof(fop))
		{
			fscanf(fop,"%s%s",code,mnemonic);
			if(strcmp(opcode,code)==0)
			{
				locctr+=3;
				c++;
				break;
			}
		}	
		if(strcmp(opcode,"WORD")==0)
		{
			locctr+=3;
		}
		else if(strcmp(opcode,"RESW")==0)
		{
			locctr+=3*(atoi(operand));
		}
		else if(strcmp(opcode,"RESB")==0)
		{
			locctr+=atoi(operand);
		}
		else if(strcmp(opcode,"BYTE")==0)
		{
			if(operand[0]=='C')
			{
				locctr+=(strlen(operand-3));
			}
			else
			{
				locctr+=1;
			}
		}
		else if(c==0)
		{
			fprintf(fpin2,"ERROR\n");
			exit(0);
		}
		fscanf(fpin1,"%s%s%s",label,opcode,operand);
	}
	fprintf(fpin2,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
	length=locctr-start;
	fprintf(fpin2,"the length of the program is: %d",length);
	fprintf(fp2,"%d",length);
	fprintf(fp3,"%X",length);
	fclose(fpin1);
	fclose(fop);
	fclose(fp2);
	fclose(fp3);
	fclose(fpin2);
	fclose(fsym);
}

