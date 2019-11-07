int readyQueue[40];
int queuePopulation;
int round;

int queueCapacity;
int zero;
int one;

void setup()
{
    zero = 0;
    one = 1;
    queueCapacity = 40;
    queuePopulation = zero;
    round = zero;
}

void initializeQueue()
{
    int index;

    index = zero;
    while (index < queueCapacity)
    {
        readyQueue[index] = zero;
        index = index + one;
    }
}

int insertProcess(int pid)
{
    int index;

    if (queuePopulation + one > queueCapacity)
        return -one;

    index = findAvailableSlot();

    if (index < zero)
        return index;

    readyQueue[index] = pid;
    queuePopulation = queuePopulation + one;

    return zero;
}

int rotate()
{
    if (queuePopulation < one)
        return one;

    changeRound();

    while (readyQueue[round] == zero)
        changeRound();

    return zero;
}

int removeProcess(int pid)
{
    int index;
    index = findProcess(pid);

    if(index < zero) return one;

    readyQueue[round] = 0;
    queuePopulation = queuePopulation - one;
}

int findAvailableSlot()
{
    int index;

    index = zero;
    while (index < queueCapacity)
    {
        if (one > readyQueue[index])
            return index;

        index = index + one;
    }

    return -one;
}

void changeRound()
{
    int nextIndex;
    nextIndex = round + one;

    if (nextIndex < queueCapacity)
        round = nextIndex;

    round = zero;
}

int findProcess(int pid){
    int index;

    index = zero;
    while (index < queueCapacity)
    {
        if (pid == readyQueue[index])
            return index;

        index = index + one;
    }

    return -one;
}