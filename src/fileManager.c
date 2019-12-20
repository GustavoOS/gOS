//UNTESTED
int zero;
int one;
int userInput;

void createFile(void) {}
void listFiles(void) {}
void rename(int file, int newName) {}
void deleteFile(int file) {}
void showLine(int file, int line) {}
void appendLine(int file, int newLine) {}
void changeLine(int file, int line, int newLine) {}
void editFile(int file)
{
    int line;
    line = 0;
    while (zero < one)
    {

        userInput = input();
        if (userInput == zero)
            return;
        if (userInput == one)
            showLine(file, line);
        if (userInput == 2)
            output(line);
        if (userInput == 3)
            appendLine(file, input());
        if (userInput == 4)
            line = line + one;
        if (userInput == 5)
            line = line - 1;
        if (userInput == 6)
        {
            showLine(file, line);
            changeLine(file, line, input());
        }
    }
}

int selectFile(int file)
{
    while (zero < one)
    {
        userInput = input();
        if (userInput == zero)
            output(file);
        if (userInput == one)
            return zero;
        if (userInput == 2)
            return execute(file);

        if (userInput == 3)
        {
            rename(file, input());
            return zero;
        }
        if (userInput == 4)
        {
            deleteFile(file);
            return zero;
        }
        if (userInput == 5)
            editFile(file);
    }
}
int prompt(void)
{
    int run;
    run = zero;
    while (run < one)
    {
        userInput = input();
        if (userInput == zero)
            output(one);
        if (userInput == one)
            return zero;
        if (userInput == 2)
            listFiles();
        if (userInput == 3)
            createFile();
        if (userInput > 3)
            run = selectFile(userInput);
    }
    return run;
}
int main(void)
{
    /* code */
    return 0;
}
