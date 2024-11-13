int sum(list,len)
int *list;
{
    int back;
    back = 0;
    for (;len > 0; --len, ++list) {back += *list;}
    return back;
}
