#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE *fp_in, *fp_name, *fp_def, *fp_arg, *fp_out;
    int len, i, pos = 1;
    char arg[20], mne[20], op[20], label[20], macname[20], mne1[20], op1[20], str1[20], str2[20];
    fp_in = fopen("input.txt", "r");
    fp_name = fopen("namtab.txt", "w+");
    fp_def = fopen("deftab.txt", "w+");
    fp_arg = fopen("argtab.txt", "w+");
    fp_out = fopen("out.txt", "w+");

    fscanf(fp_in, "%s%s%s", label, mne, op);

    while (strcmp(mne, "END") != 0)
    {
        if (strcmp(mne, "MACRO") == 0)
        {
            fprintf(fp_def, "%s\t%s\t%s\n", label, mne, op);
            fprintf(fp_name, "%s\n", label);
            fscanf(fp_in, "%s%s%s", label, mne, op);

            while (strcmp(mne, "MEND") != 0)
            {
                if (op[0] == '&')
                {
                    fprintf(fp_def, "%s\t?%d\n", mne, pos);
                }
                else
                {
                    fprintf(fp_def, "%s\t%s\n", mne, op);
                }
                fscanf(fp_in, "%s%s%s", label, mne, op);
            }
        }
        else
        {
            fscanf(fp_name, "%s", macname);
            if (strcmp(macname, mne) == 0)
            {
                len = strlen(op);
                printf("%d", len);
                for (int i = 0; i < len; i++)
                {
                    if (op[i] == ',')
                    {
                        fprintf(fp_arg, "\n");
                    }
                    else
                    {
                        fprintf(fp_arg, "%c", op[i]);
                    }
                }
            }
        }

        fscanf(fp_in, "%s%s%s", label, mne, op);
    }

    return 0;
}