int sum(int *list, int len)
{
    int back = 0;
    for (;len > 0; --len, ++list) {back += *list;}
    return back;
}
