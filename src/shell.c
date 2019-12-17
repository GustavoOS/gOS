void createFile() {}
void listFiles() {}
void execute(int file) {}
void rename(int file, int newName) {}
void delete (int file) {}
void showLine(int file, int line) {}
void appendLine(int file, int newLine) {}
void changeLine(int file, int line, int newLine) {}
void listProcess() {}
void resume(int process) {}
void kill(int process) {}

int accessProcess(int process)
{
    int userInput;
    while (2 < 3)
    {
        userInput = input();
        if (userInput == 0)
            output(process);
        if (userInput == 1)
            return 0;
        if (userInput == 2)
        {
            resume(process);
            return process;
        }
        if (userInput == 3)
        {
            kill(process);
            return 0;
        }
    }
}

void edit(int file)
{
    int line;
    int userInput;
    line = 0;
    while (2 < 3)
    {

        userInput = input();
        if (userInput == 0)
            return;
        if (userInput == 1)
            showLine(file, line);
        if (userInput == 2)
            output(line);
        if (userInput == 3)
            appendLine(file, input());
        if (userInput == 4)
            line = line + 1;
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
    int userInput;
    while (2 < 3)
    {

        userInput = input();
        if (userInput == 0)
            output(file);
        if (userInput == 1)
            return 0;
        if (userInput == 2)
        {
            execute(file);
            return file;
        }
        if (userInput == 3)
        {
            rename(file, input());
            return 0;
        }
        if (userInput == 4)
        {
            delete (file);
            return 0;
        }
        if (userInput == 5)
            edit(file);
    }
}
int prompt()
{
    int userInput;
    int run = 0;
    while (run < 1)
    {
        userInput = input();
        if (userInput == 0)
            output(1);
        if (userInput == 1)
            return 0;
        if (userInput == 2)
            listFiles();
        if (userInput == 3)
            createFile();
        if (userInput > 3)
            run = selectFile(userInput);
    }
    return run;
}

int main()
{
    int userInput;
    int run = 0;

    while (run < 1)
    {
        userInput = input();

        if (userInput == 0)
            output(0);
        if (userInput == 1)
            run = prompt();
        if (userInput == 2)
            listProcess();
        if (userInput > 3)
            run = accessProcess(userInput);
    }

    return 0;
}