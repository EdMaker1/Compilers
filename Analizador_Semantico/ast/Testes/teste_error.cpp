/* Este programa debe generar un error */

int main()
{
    float x;
    int y;
    
    x = 3.14;
    y = 5;
    
    // Esto deberia funcionar (si habilitamos float->bool)
    if (x)
    {
        y = 10;
    }
}
