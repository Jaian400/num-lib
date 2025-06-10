# Spis Treści
1.  [`approximate`](#approximate)
2.  [`solve_diff_eq_runge_kutty`](#solve_diff_eq_runge_kutty)
3.  [`solve_lin_eq`](#solve_lin_eq)
4.  [`interpolate`](#interpolate)
5.  [`solve_nonlin_eq`](#solve_nonlin_eq)

---

# Dokumentacja Funkcji Numerycznych

## `approximate`

Funkcja ta znajduje prostszy wielomian, który jak najlepiej naśladuje (aproksymuje) podaną, potencjalnie bardziej skomplikowaną funkcję `f(x)` na zadanym przedziale.

```cpp
std::vector<double> approximate(
    std::pair<double, double> ab,
    double (*f)(double),
    int N
);
```

### Jak działa?
Funkcja tworzy i rozwiązuje specjalny układ równań liniowych. Rozwiązanie tego układu daje współczynniki szukanego wielomianu, który będzie przebiegał jak najbliżej oryginalnej funkcji `f(x)`.

### Parametry
*   `ab`: Para liczb `(a, b)` określająca przedział, na którym funkcja ma być przybliżana.
*   `f`: Wskaźnik na funkcję `f(x)`, którą chcemy przybliżyć.
*   `N`: Liczba współczynników wielomianu. Wielomian będzie miał stopień `N-1`.

### Zwracana wartość
*   `std::vector<double>`: Wektor współczynników wielomianu. Na przykład, jeśli wektor to `{c0, c1, c2}`, wielomian ma postać `c0 + c1*x + c2*x^2`.

---

## `solve_diff_eq_runge_kutty`

Rozwiązuje równanie różniczkowe typu `y' = f(x, y)`. Innymi słowy, znając pochodną funkcji (`y'`) i jej punkt startowy, funkcja odtwarza jej przybliżony przebieg.

```cpp
std::vector<double> solve_diff_eq_runge_kutty(
    int N,
    std::pair<double, double> ab,
    double y0,
    double (*f)(double, double)
);
```

### Jak działa?
Funkcja dzieli przedział `[a, b]` na `N` małych kroków. Zaczynając od punktu startowego `(a, y0)`, w każdym kroku oblicza wartość funkcji w następnym punkcie. Robi to w sprytny sposób, uśredniając nachylenie funkcji w kilku miejscach w obrębie kroku, co daje bardzo dokładny wynik.

### Parametry
*   `N`: Liczba kroków, na które zostanie podzielony przedział. Więcej kroków oznacza większą dokładność.
*   `ab`: Para liczb `(a, b)` określająca przedział, na którym szukamy rozwiązania.
*   `y0`: Wartość funkcji w punkcie startowym `a`.
*   `f`: Wskaźnik na funkcję `f(x, y)` opisującą pochodną szukanej funkcji.

### Zwracana wartość
*   `std::vector<double>`: Wektor zawierający przybliżone wartości funkcji `y` w kolejnych punktach od `a` do `b`.

---

## `solve_lin_eq`

Rozwiązuje układ `N` równań liniowych z `N` niewiadomymi, zapisany w formie macierzowej `A*x = b`.

```cpp
std::vector<double> solve_lin_eq(
    std::vector<std::vector<double>> matrix,
    std::vector<double> b,
    int N
);
```

### Jak działa?
Funkcja używa metody eliminacji Gaussa, znanej ze szkoły średniej. Przekształca ona układ równań do prostszej, "schodkowej" formy. W tej formie ostatnie równanie ma tylko jedną niewiadomą. Po jej obliczeniu, funkcja "cofa się" i wylicza kolejne niewiadome jedna po drugiej.

### Parametry
*   `matrix`: Macierz `A` współczynników przy niewiadomych.
*   `b`: Wektor `b` wyrazów wolnych.
*   `N`: Liczba równań (i niewiadomych).

### Zwracana wartość
*   `std::vector<double>`: Wektor `x`, czyli rozwiązanie układu równań.

---

## `interpolate`

Na podstawie zestawu znanych punktów `(x, y)` funkcja szacuje, jaką wartość miałaby funkcja w nowym, nieznanym punkcie `userInput`.

```cpp
double interpolate(
    const FunctionData& data,
    double userInput,
    int n
);
```

### Jak działa?
Działa poprzez "przeciągnięcie" gładkiej krzywej (wielomianu) przez wszystkie podane punkty. Następnie po prostu odczytuje z tej idealnie dopasowanej krzywej wartość dla zadanego `userInput`.

### Parametry
*   `data`: Struktura danych zawierająca dwa wektory: `data.x` (znane argumenty) i `data.fx` (znane wartości funkcji dla tych argumentów).
*   `userInput`: Punkt `x`, dla którego chcemy oszacować wartość.
*   `n`: Liczba punktów, które mają zostać użyte do stworzenia krzywej.

### Zwracana wartość
*   `double`: Oszacowana wartość funkcji w punkcie `userInput`.

---

## `solve_nonlin_eq`

Znajduje miejsca zerowe funkcji `f(x)` (czyli takie wartości `x`, dla których `f(x) = 0`) w podanym przedziale.

```cpp
std::vector<double> solve_nonlin_eq(
    double (*f)(double),
    std::pair<double, double> ab,
    double step = 0.01 // opcjonalny
);
```

### Jak działa?
Najpierw funkcja "skanuje" duży przedział `[a, b]`, dzieląc go na wiele małych kawałków, aby zlokalizować, gdzie w przybliżeniu mogą znajdować się miejsca zerowe. Następnie dla każdego takiego znalezionego obszaru, używa dokładniejszej metody, aby precyzyjnie "wycelować" w miejsce zerowe. Na koniec filtruje wyniki, aby usunąć duplikaty i niedokładne wartości.

### Parametry
*   `f`: Wskaźnik na funkcję `f(x)`, której miejsc zerowych szukamy.
*   `ab`: Para liczb `(a, b)` określająca przedział poszukiwań.
*   `step` (opcjonalny): Wielkość kroku podczas początkowego skanowania przedziału. Mniejszy krok może znaleźć więcej miejsc zerowych, ale działa wolniej.

### Zwracana wartość
*   `std::vector<double>`: Wektor zawierający znalezione miejsca zerowe funkcji.