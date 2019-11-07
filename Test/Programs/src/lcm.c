
int gcd(int u, int v)
{
    int mod;
    if (v == 0)
        return u;

    mod = u - u / v * v;
    return gcd(v, mod);
}

int lcm(int a, int b)
{
    int g;
    int m;

    m = a * b;
    g = gcd(a, b);

    return m / g;
}

void main(void)
{
    int x;
    int y;
    x = input();
    y = input();
    output(lcm(x, y));
}