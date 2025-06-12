# Biblioteka Metod Numerycznych w C++
Jest to zbiór funkcji w języku C++, implementujących popularne metody numeryczne. Biblioteka została stworzona w celu dostarczenia gotowych do użycia narzędzi do rozwiązywania licznych problemów matematycznych i inżynierskich, które często wymagają podejścia numerycznego. Każda funkcja jest zaprojektowana z myślą o łatwości użycia w projektach akademickich, naukowych lub hobbystycznych.

# Spis Treści
0.  [`Instalacja`](#Instalacja)
1.  [`Przykład użycia`](#Przykład_użycia)
2.  [`approximate`](#approximate)
3.  [`solve_diff_eq`](#solve_diff_eq)
4.  [`solve_lin_eq`](#solve_lin_eq)
5.  [`interpolate`](#interpolate)
6.  [`solve_nonlin_eq`](#solve_nonlin_eq)
7.  [`integrate`](#integrate)

---

## Instalacja
Pobrać pełny folder num-lib i umieścić w swoim folderze bibliotek. Następnie w kodzie zaimportować "num-lib/num-lib.hpp".

```cpp
#include "num-lib/num-lib.hpp"

int main(){
    ...
    output = approximate(ab, f1);
    ...
}
```

W celu rekompilacji wywołać polecenie:
```bash
>> make
```

## Przykład_użycia
Przykład ten oraz dodatkowy można znaleźć w folderze examples/.

```cpp
void example_interpolate(){
    std::cout << "--------------------- RUNNING INTERPOLATION EXAMPLE --------------------------" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "--- Example: Interpolation (interpolate) ---" << std::endl;
    std::cout << "This example interpolates a temperature value based on a given set of measurements." << std::endl;
    std::vector<double> hours = {0.0, 2.0, 4.0, 6.0};
    std::vector<double> temps = {15.0, 19.0, 18.0, 22.0};
    double hour_to_check = 3.5;

    std::cout << "Input data (hours): ";
    for(double h : hours) std::cout << h << "h ";
    std::cout << std::endl;
    
    std::cout << "Input data (temperatures): ";
    for(double t : temps) std::cout << t << "C ";
    std::cout << std::endl;

    double interpolated_temp = interpolate(hours, temps, hours.size(), hour_to_check);
    std::cout << "\nEstimated temperature at hour " << hour_to_check << " is: " << interpolated_temp << " C" << std::endl;
    std::cout << "--------------------------------------------------\n" << std::endl;
}
```

# Dokumentacja

## `approximate`

Funkcja ta znajduje prostszy wielomian, który jak najlepiej naśladuje podaną, potencjalnie bardziej skomplikowaną funkcję `f(x)` na zadanym przedziale.

```cpp
std::vector<double> approximate(
    std::pair<double, double> ab,
    double (*f)(double),
    int N
);
```

### Jak działa?
Funkcja tworzy i rozwiązuje układ równań liniowych. Rozwiązanie tego układu daje współczynniki szukanego wielomianu, który będzie przebiegał jak najbliżej oryginalnej funkcji `f(x)`.

### Parametry
*   `ab`: Para liczb `(a, b)` określająca przedział, na którym funkcja ma być przybliżana.
*   `f`: Wskaźnik na funkcję `f(x)`, którą chcemy przybliżyć.
*   `N`: Liczba współczynników wielomianu. Wielomian będzie miał stopień `N-1`.

### Zwracana wartość
*   `std::vector<double>`: Wektor współczynników wielomianu. Na przykład, jeśli wektor to `{c0, c1, c2}`, wielomian ma postać `c0 + c1*x + c2*x^2`.

---

## `solve_diff_eq`

Rozwiązuje równanie różniczkowe typu `y' = f(x, y)`. Znając pochodną funkcji (`y'`) i jej punkt startowy, funkcja odtwarza jej przybliżony przebieg.

```cpp
std::vector<double> solve_diff_eq(
    int N,
    std::pair<double, double> ab,
    double y0,
    double (*f)(double, double)
);
```

### Jak działa?
Funkcja dzieli przedział `[a, b]` na `N` małych kroków. Zaczynając od punktu startowego `(a, y0)`, w każdym kroku oblicza wartość funkcji w następnym punkcie. Robi to uśredniając nachylenie funkcji w kilku miejscach w obrębie kroku, co daje bardzo dokładny wynik.

### Parametry
*   `N`: Liczba kroków, na które zostanie podzielony przedział. Więcej kroków oznacza większą dokładność. Domyślnie przyjmuje wartość `100`.
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
    const std::vector<std::vector<double>>& matrix,
    const std::vector<double>& b
);
```

### Jak działa?
Funkcja używa metody eliminacji Gaussa. Przekształca ona układ równań do prostszej, "schodkowej" formy. W tej formie ostatnie równanie ma tylko jedną niewiadomą. Po jej obliczeniu, funkcja "cofa się" i wylicza kolejne niewiadome jedna po drugiej.

### Parametry
*   `matrix`: Macierz `A` współczynników przy niewiadomych.
*   `b`: Wektor `b` wyrazów wolnych.

### Zwracana wartość
*   `std::vector<double>`: Wektor `x`, czyli rozwiązanie układu równań.

---

## `interpolate`

Na podstawie zestawu znanych punktów `(x, f(x))` funkcja szacuje, jaką wartość miałaby funkcja w nowym, nieznanym punkcie `xp`.

```cpp
double interpolate(
    std::vector<double> x,
    std::vector<double> f,
    int n,
    double xp
);
```

### Jak działa?
Działa poprzez "przeciągnięcie" gładkiej krzywej (wielomianu) przez wszystkie podane punkty. Następnie odczytuje z tej idealnie dopasowanej krzywej wartość dla zadanego punktu `xp`.

### Parametry
*   `std::vector<double> x`: Wektor znanych argumentów (współrzędnych x).
*   `std::vector<double> f`: Wektor znanych wartości funkcji (współrzędnych y), odpowiadających punktom z wektora `x`.
*   `int n`: Liczba punktów z wektorów `x` i `f`, które mają zostać użyte do interpolacji. Domyślnie przyjmuje wszystkie punkty.
*   `double xp`: Punkt, dla którego chcemy oszacować wartość funkcji.

### Zwracana wartość
*   `double`: Oszacowana wartość funkcji w punkcie `xp`.

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

---

## `integrate`

Funkcja ta oblicza całkę oznaczoną (czyli pole pod wykresem) z wielomianu na zadanym przedziale `[a, b]`, wykorzystując **metodę Simpsona**.

```cpp
double integrate(
    std::vector <double> ai,
    std::pair <double, double> ab,
    int n=100
);
```

### Jak działa?
Funkcja przyjmuje wielomian zdefiniowany przez jego współczynniki. Aby obliczyć pole pod jego wykresem, stosuje numeryczną metodę Simpsona. Działa to w następujący sposób:

1.  Przedział całkowania `[a, b]` jest dzielony na bardzo dużą liczbę (`2*n`) małych, równych sobie podprzedziałów.
2.  Zamiast traktować krzywą na tych małych odcinkach jako linię prostą, metoda Simpsona przybliża ją za pomocą fragmentów parabol. Jest to znacznie dokładniejsze niż prostsze metody.
3.  Funkcja sumuje pola powierzchni pod tymi wszystkimi małymi parabolami, co w efekcie daje bardzo dobre przybliżenie całkowitego pola pod wykresem wielomianu.

### Parametry
*   `std::vector<double> ai`: Wektor współczynników wielomianu, który ma być scałkowany. Kolejność jest kluczowa, np. wektor `{a0, a1, a2}` reprezentuje wielomian `W(x) = a0 + a1*x + a2*x^2`.
*   `std::pair<double, double> ab`: Para liczb `(a, b)` określająca przedział całkowania.
*   `int n` (opcjonalny): Liczba podziałów użytych w metodzie Simpsona. Im większa wartość `n`, tym dokładniejszy wynik. Domyślnie wynosi `100`.

### Zwracana wartość
*   `double`: Obliczona, przybliżona wartość całki z wielomianu na przedziale `[a, b]`.