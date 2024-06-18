#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void make(const char *comp, const char *princip, const char *lib, const char *out) {
    if (access("Makefile", F_OK) == 0) {
        remove("Makefile");
    }

    FILE *makefile = fopen("Makefile", "w");
    if (makefile == NULL) {
        fprintf(stderr, "Error creating Makefile");
        return;
    }
    
    fprintf(makefile, "CC=%s\n", comp);
    fprintf(makefile, "CCFLAGS=-Wall -Wextra -ffreestanding\n");
    fprintf(makefile, "IN=%s\n", princip);
    fprintf(makefile, "OUT=%s\n", out);
    if (strcmp(lib, "none") != 0) 
        fprintf(makefile, "LIB=%s\n", lib);
    fprintf(makefile, "SRC=src\n");
    fprintf(makefile, "BUILD=build\n\n");

    fprintf(makefile, "fresh:\n");
    fprintf(makefile, "\tmkdir -p $(BUILD)\n");
    if (strcmp(lib, "none") != 0) {
        fprintf(makefile, "\tmkdir -p $(SRC) && touch $(SRC)/$(IN) && touch $(SRC)/$(LIB)\n");
    } else {
        fprintf(makefile, "\tmkdir -p $(SRC) && touch $(SRC)/$(IN)\n");
    }
    fprintf(makefile, "start:\n");
    fprintf(makefile, "\tmkdir -p $(BUILD)\n");
    if (strcmp(lib, "none") != 0) {
        fprintf(makefile, "\tmkdir -p $(SRC) && mv $(IN) $(SRC) && mv $(LIB) $(SRC)\n");
    } else {
        fprintf(makefile, "\tmkdir -p $(SRC) && mv $(IN) $(SRC)\n");
    }
    fprintf(makefile, "all:\n");
    if (strcmp(lib, "none") != 0) {
        fprintf(makefile, "\t$(CC) -o $(BUILD)/$(OUT) $(SRC)/$(IN) $(LIB) $(CCFLAGS)\n");
    } else {
        fprintf(makefile, "\t$(CC) -o $(BUILD)/$(OUT) $(SRC)/$(IN) $(CCFLAGS)\n");
    }
    fprintf(makefile, "run:\n");
    fprintf(makefile, "\t./$(BUILD)/$(OUT)\n");

    fprintf(makefile, "clean:\n");
    fprintf(makefile, "\tmv $(SRC)/$(IN) .\n");
    fprintf(makefile, "\trm -rf $(BUILD) && rm -rf $(SRC)\n");

    fprintf(makefile, "wipe:\n");
    fprintf(makefile, "\trm -rf $(BUILD) && rm -rf $(SRC)\n");

    fclose(makefile);
}

int main(void) {
    char comp[100], princip[100], lib[100], out[100];

    printf("compiler (gcc, clang etc): ");
    scanf("%s", comp);

    printf("main file name with ext (exmpl.c): ");
    scanf("%s", princip);

    printf("library name with ext (exmpl.h) (if no library say 'none'): ");
    scanf("%s", lib);

    printf("output file name with ext/no ext (exmpl): ");
    scanf("%s", out);

    make(comp, princip, lib, out);

    return 0;
}
