int main()
{
    int x;
    int y;
    bool flag;
    
    x = 5;
    y = 0;
    
    // Conversión automática: x (5) -> true, y (0) -> false
    if (x)
    {
        flag = true;
    }
    
    // Conversión en operador lógico
    if (x && y)
    {
        flag = false;
    }
    
    // Conversión con NOT
    if (!y)
    {
        x = 10;
    }
    
    // While con conversión
    while (x)
    {
        x = x - 1;
    }
}