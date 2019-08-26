int surface(int biggerBase, int smallerBase, int height){
    int temp;

    temp = biggerBase + smallerBase;
    temp = temp * height;
    temp = temp / 2;

    return temp;
}

void main(void){
    int biggerBase;
    int smallerBase;
    int height;
    int s;

    biggerBase = input();
    smallerBase = input();
    height = input();

    s = surface(biggerBase, smallerBase, height);

    output(s);
}