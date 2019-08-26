int surface(int base, int height)
{
    return base * height;
}

int perimeter(int base, int height)
{
    int b2s;
    int h2s;

    b2s = 2 * base;
    h2s = 2 * height;

    return b2s + h2s;
}

void main(void)
{
    int base;
    int height;
    int p;
    int s;

    base = input();
    height = input();

    p = perimeter(base, height);
    output(p);

    s = surface(base, height);
    output(s);
}