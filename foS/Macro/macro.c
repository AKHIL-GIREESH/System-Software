#include <stdio.h>
#include <string.h>
void main()
{
    FILE *fp_in, *fp_name, *fp_def, *fp_arg, *fp_out;
    int len, i, pos = 1;
    char arg[20], mne[20], op[20], label[20], macname[20], mne1[20], op1[20], str1[20], str2[20];
    fp_in = fopen("input.txt", "r");
    fp_name = fopen("namtab.txt", "w+");
    fp_def = fopen("deftab.txt", "w+");
    fp_arg = fopen("argtab.txt", "w+");
    fp_out = fopen("out.txt", "w+");
    fscanf(fp_in, "%s\t%s\t%s", label, mne, op);
    while (strcmp(mne, "END") != 0)
    {
        if (strcmp(mne, "MACRO") == 0)
        {
            printf("\n inside macro\n");
            fprintf(fp_name, "%s\n", label);
            fseek(fp_name, SEEK_SET, 0);
            fprintf(fp_def, "%s\t%s\n", label, op);
            printf("entering macro prototype in deftab\n");
            fscanf(fp_in, "%s\t%s\t%s", label, mne, op);
            while (strcmp(mne, "MEND") != 0)
            {
                if (op[0] == '&')
                {
                    sprintf(str1, "%d", pos);
                    strcpy(str2, "?");
                    strcpy(op, strcat(str2, str1));
                    pos = pos + 1;
                    fprintf(fp_def, "%s\t%s\n", mne, op);
                }
                else

                    fprintf(fp_def, "%s\t%s\n", mne, op);

                printf("entering the macro defn in deftab\n");
                fscanf(fp_in, "%s\t%s\t%s", label, mne, op);
                printf("reached MEND");
            }
            fprintf(fp_def, "%s", mne);
        }
        else
        {
            fscanf(fp_name, "%s", macname);
            if (strcmp(mne, macname) == 0)
            {
                len = strlen(op);
                for (i = 0; i < len; i++)
                {
                    if (op[i] != ',')
                        fprintf(fp_arg, "%c", op[i]);
                    else
                        fprintf(fp_arg, "\n");
                }
                fseek(fp_def, SEEK_SET, 0);
                fprintf(fp_out, "**\t.%s\t%s\n", mne, op);
                printf("entering comment macro invocation\n");
                printf("**\t.%s \t %s \n", mne, op);
                fscanf(fp_def, "%s\t%s", mne, op1);
                fseek(fp_arg, SEEK_SET, 0);

                while (strcmp(mne1, "MEND") != 0)
                {
                    if (op1[0] == '?')
                    {
                        fscanf(fp_arg, "%s", arg);
                        printf("%s", arg);
                        fprintf(fp_out, "**\t%s\t%s\n", mne1, arg);
                        printf("\nreplace arguments in  input\n");
                        printf("**\t%s\t%s\n", mne1, arg);
                    }
                    else if (op1[0] != '&')
                    {
                        fprintf(fp_out, "**\t%s\t%s\n", mne1, op1);
                        printf("**\t%s\t%s\n", mne1, op1);
                    }
                    fscanf(fp_def, "%s%s", mne1, op1);
                }
            }
            else
            {
                fprintf(fp_out, "%s\t%s\t%s\n", label, mne, op);
                printf("\nline from input code\n");
                printf("%s\t%s\t%s\n", label);
            }
        }
        fscanf(fp_in, "%s\t%s\t%s", label, mne, op);
    }
    printf("\nline from inputt code\n");
    fprintf(fp_out, "%s\t%s\t%s", label, mne, op);
    printf("%s\t%s\t%s\n", label, mne, op);
    fclose(fp_in);
    fclose(fp_name);
    fclose(fp_def);
    fclose(fp_arg);
    fclose(fp_out);
}

/*line from input code
SAMPLE	(null)	H=

 inside macro
entering macro prototype in deftab
entering the macro defn in deftab
reached MENDentering the macro defn in deftab
reached MENDentering the macro defn in deftab
reached MENDentering comment macro invocation
**	.EX1 	 N1,N2
N1
replace arguments in  input
**	LDA	N1
N2
replace arguments in  input
**	STA	N2
**	CLEAR	C

line from input code
N1	(null)	H=

line from input code
N2	(null)	H=

line from inputt code
**	END	**
*/