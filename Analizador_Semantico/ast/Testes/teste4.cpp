
/* Programa de prueba para conversiones automaticas int->bool */

int main()

{

    int x;

    int y;

    bool flag;

    

    x = 5;

    y = 0;

    

    // Conversion automatica: x (5) -> true

    if (x)

    {

        flag = true;

    }

    

    // Conversion automatica: y (0) -> false

    if (y)

    {

        flag = false;

    }

    

    // Conversion en operador logico: x && y

    if (x && y)

    {

        flag = false;

    }

    

    // Conversion con NOT: !y

    if (!y)

    {

        x = 10;

    }

    

    // While con conversion

    while (x)

    {

        x = x - 1;

    }

}

