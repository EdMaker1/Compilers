## Compilador AST con Análisis Semántico

> Compilador que implementa conversiones automáticas de tipo int→bool, siguiendo la semántica de C/C++

[![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat&logo=c%2B%2B)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com)

---

## Descripción

Este proyecto es un **compilador front-end** completo que procesa un lenguaje simplificado similar a C. Implementa las tres fases principales de análisis:

- **Análisis Léxico**: Tokenización del código fuente
- **Análisis Sintáctico**: Construcción del árbol sintáctico abstracto (AST)
- **Análisis Semántico**: Verificación de tipos con conversiones automáticas

### Característica Principal

**Conversiones Automáticas int→bool**: El compilador convierte implícitamente valores enteros a booleanos siguiendo la regla:
- `0` → `false`
- `≠ 0` → `true`

Esto permite escribir código natural como:
```cpp
int x = 5;
if (x) {  // x se convierte automáticamente a bool
    // código
}
```

---

## Inicio Rápido

### Requisitos Previos

- **Compilador C++** con soporte para C++17 o superior
  - GCC 7.0+ o Clang 5.0+
- **Make** (opcional, pero recomendado)

### Instalación

```bash
# Clonar el repositorio
git clone https://github.com/EdMaker1/Compilers/Analizador_Semantico
cd ast

# Compilar el proyecto
make

# Ejecutar un ejemplo
./traductor Testes/teste1.cpp
```

### Compilación Manual

Si no tienes `make`, compila manualmente:

```bash
g++ -std=c++17 -Wall -Wextra -c traductor.cpp lexer.cpp parser.cpp ast.cpp symtable.cpp error.cpp checker.cpp
g++ -std=c++17 -Wall -Wextra -o traductor *.o
```

---

## Uso

### Sintaxis Básica

```bash
./traductor <archivo.cpp>
```

### Ejemplos

```bash
# Programa básico
./traductor Testes/teste1.cpp

# Programa con conversiones automáticas
./traductor Testes/teste3.cpp

# Guardar salida en archivo
./traductor Testes/teste2.cpp > output.txt
```

---

## Documentación

### Gramática del Lenguaje

El compilador soporta un subconjunto de C con la siguiente gramática:

```
program  → type main() block
block    → { decls stmts }

stmts    → stmt stmts | ε
stmt     → local = bool;
         | if (bool) stmt
         | while (bool) stmt
         | do stmt while (bool);
         | block

bool     → bool || join | join
join     → join && equality | equality
equality → equality == rel | equality != rel | rel
rel      → rel < ari | rel <= ari | rel > ari | rel >= ari | ari
ari      → ari + term | ari - term | term
term     → term * unary | term / unary | unary
unary    → !unary | -unary | factor
factor   → (bool) | local | integer | real | true | false
```

### Tipos Soportados

| Tipo | Descripción | Ejemplos |
|------|-------------|----------|
| `int` | Números enteros | `0`, `42`, `-10` |
| `float` | Números de punto flotante | `3.14`, `-2.5` |
| `bool` | Valores booleanos | `true`, `false` |

### Operadores

| Categoría | Operadores | Asociatividad |
|-----------|-----------|---------------|
| Lógicos | `&&`, `\|\|`, `!` | Izquierda |
| Relacionales | `<`, `<=`, `>`, `>=`, `==`, `!=` | Izquierda |
| Aritméticos | `+`, `-`, `*`, `/` | Izquierda |

---

## Conversiones Automáticas

### Regla de Conversión

```cpp
int → bool:
    0       →  false
    ≠ 0     →  true
```

### Contextos Donde se Aplican

#### 1. Estructuras de Control

```cpp
int x = 5;

if (x) { }           // x convertido a true
while (x) { }        // x convertido a true
do { } while (x);    // x convertido a true
```

#### 2. Operadores Lógicos

```cpp
int a = 1, b = 0;

if (a && b) { }      // a→true, b→false
if (a || b) { }      // a→true, b→false
if (!b) { }          // b→false, !false→true
```

#### 3. Expresiones Complejas

```cpp
int x = 5, y = 0, z = 10;

if ((x || y) && z) { }  // Todas las conversiones aplicadas
```

### Visualización en el AST

El compilador muestra explícitamente las conversiones:

```
Entrada:  if (x)
Salida:   <IF> <CONVERSION:int->bool> x </CONVERSION> ... </IF>
```

---

## Estructura del Proyecto

```
ast/
│
├── README.md              # Documentación principal
├── Makefile               # Script de compilación
├── LICENSE                # Licencia MIT
│
├── traductor.cpp          # Programa principal
├── lexer.cpp/h            # Analizador léxico
├── parser.cpp/h           # Analizador sintáctico
├── ast.cpp/h              # Árbol sintáctico abstracto
├── symtable.cpp/h         # Tabla de símbolos
├── error.cpp/h            # Manejo de errores
├── checker.cpp/h          # Visualizador del AST
│
└── Testes/
    ├── teste1.cpp         # Programa básico
    ├── teste2.cpp         # Programa complejo
    ├── teste3.cpp         # Conversiones básicas
    ├── teste4.cpp         # Conversiones completas
    └── teste_error.cpp    # Casos de error
```

### Descripción de Componentes

| Componente | Responsabilidad | LOC |
|------------|----------------|-----|
| **Lexer** | Tokenización del código fuente | ~300 |
| **Parser** | Construcción del AST, aplicación de conversiones | ~700 |
| **AST** | Definición de nodos, verificación de tipos | ~200 |
| **SymTable** | Gestión de símbolos y ámbitos | ~50 |
| **Checker** | Recorrido y visualización del AST | ~150 |
| **Error** | Excepciones y mensajes de error | ~30 |

---

## Ejemplos Completos

### Ejemplo 1: Programa Básico

**Código: `teste1.cpp`**
```cpp
int main()
{
    int i;
    int j;
    bool z;

    i = 15;
    j = 30;
    z = i > 10 && j <= 20;
}
```

**Salida del AST:**
```
<SEQ> <ASSIGN> i = 15 </ASSIGN>
<SEQ> <ASSIGN> j = 30 </ASSIGN>
<SEQ> <ASSIGN> z = <LOG> <REL> i > 10 </REL> && <REL> j <= 20 </REL> </LOG> </ASSIGN>
</SEQ> </SEQ> </SEQ>
```

### Ejemplo 2: Conversiones Automáticas

**Código: `teste3.cpp`**
```cpp
int main()
{
    int x;
    int y;
    bool flag;
    
    x = 5;
    y = 0;
    
    // x (5) → true, y (0) → false
    if (x) {
        flag = true;
    }
    
    // Conversión en operadores lógicos
    if (x && y) {
        flag = false;
    }
    
    // Conversión con operador NOT
    if (!y) {
        x = 10;
    }
    
    // Conversión en while
    while (x) {
        x = x - 1;
    }
}
```

**Salida del AST:**
```
<IF> <CONVERSION:int->bool> x </CONVERSION>
    <ASSIGN> flag = true </ASSIGN>
</IF>

<IF> <LOG> <CONVERSION:int->bool> x </CONVERSION> && <CONVERSION:int->bool> y </CONVERSION> </LOG>
    <ASSIGN> flag = false </ASSIGN>
</IF>

<IF> <UNARY> ! <CONVERSION:int->bool> y </CONVERSION> </UNARY>
    <ASSIGN> x = 10 </ASSIGN>
</IF>

<WHILE> <CONVERSION:int->bool> x </CONVERSION>
    <ASSIGN> x = <ARI> x - 1 </ARI> </ASSIGN>
</WHILE>
```

---

## Pruebas

### Suite de Pruebas

| Archivo | Descripción | Resultado |
|---------|-------------|-----------|
| `teste1.cpp` | Asignaciones y expresiones básicas | ✅ PASS |
| `teste2.cpp` | Estructuras complejas, arreglos, loops | ✅ PASS |
| `teste3.cpp` | Conversiones en if, while | ✅ PASS |
| `teste4.cpp` | Conversiones en todos los contextos | ✅ PASS |
| `teste_error.cpp` | Conversión float→bool (opcional) | ✅ PASS |

### Ejecutar Todas las Pruebas

```bash
# Script de pruebas
for file in Testes/*.cpp; do
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "Probando: $file"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    ./traductor "$file"
    echo ""
done
```

### Crear Nuevas Pruebas

```cpp
// Testes/mi_prueba.cpp
int main()
{
    // Tu código de prueba aquí
}
```

```bash
./traductor Testes/mi_prueba.cpp
```

---

## Solución de Problemas

### Errores Comunes

#### Error: `variable "x" no declarada`

```cpp
// Incorrecto
x = 10;

// Correcto
int x;
x = 10;
```

#### Error: `tipos diferentes en asignación`

```cpp
// Incorrecto
int x;
float y;
x = y;

// ✅ Correcto
int x;
int y;
x = y;
```

#### Error: Conversiones no funcionan

Asegúrate de estar usando la versión con conversiones (Grupo 2). Verifica que `CheckBoolContext()` esté implementado en `parser.cpp`.

---

## Desarrollo

### Compilación en Modo Debug

```bash
g++ -std=c++17 -Wall -Wextra -g -O0 traductor.cpp lexer.cpp parser.cpp \
    ast.cpp symtable.cpp error.cpp checker.cpp -o traductor_debug

# Depurar con GDB
gdb ./traductor_debug
(gdb) run Testes/teste1.cpp
(gdb) break Parser::Bool
(gdb) continue
```

### Agregar Nueva Funcionalidad

1. Modificar gramática si es necesario
2. Actualizar `parser.cpp` con nuevas reglas
3. Agregar nodos al AST en `ast.h` y `ast.cpp`
4. Actualizar `checker.cpp` para visualización
5. Crear casos de prueba
6. Documentar cambios en README

### Estilo de Código

- **Indentación**: 4 espacios
- **Nombres de clases**: PascalCase (`SymTable`)
- **Nombres de métodos**: PascalCase (`CheckBoolContext`)
- **Variables**: camelCase (`lookahead`, `symtable`)
- **Comentarios**: Español, descriptivos

---

## Contribuir

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/nueva-funcionalidad`)
3. Commit tus cambios (`git commit -am 'Agrega nueva funcionalidad'`)
4. Push a la rama (`git push origin feature/nueva-funcionalidad`)
5. Abre un Pull Request

### Guías

- Mantener tests para toda funcionalidad nueva
- Seguir el estilo de código existente
- Documentar cambios en el README
- Incluir ejemplos de uso

---

## Licencia

Este proyecto está bajo la Licencia MIT. Ver archivo [LICENSE](LICENSE) para más detalles.

```
MIT License - Copyright (c) 2025
```

---

## Autor

**Eduardo Ccama**
- GitHub: (https://github.com/EdMaker1/Compilers)
- Email: edwined574@gmail.com

---

## Agradecimientos

- Profesores del curso de Compiladores
- Autores del Dragon Book (Aho, Lam, Sethi, Ullman)
- Comunidad de C++ y compiladores

---

## 📊 Estadísticas del Proyecto

- **Lenguaje**: C++17
- **Líneas de código**: ~1,500
- **Archivos**: 14
- **Casos de prueba**: 5
- **Cobertura**: Alta

---

## 🗺️ Roadmap

- [x] Análisis léxico completo
- [x] Parser recursivo descendente
- [x] Tabla de símbolos con ámbitos
- [x] Verificación de tipos
- [x] Conversiones automáticas int→bool
- [ ] Conversiones float→bool
- [ ] Generación de código intermedio (IR)
- [ ] Optimización de código
- [ ] Generación de código ensamblador

---

**Si este proyecto te fue útil, considera darle una estrella en GitHub**

*Última actualización: Nov 2025*

</div>
