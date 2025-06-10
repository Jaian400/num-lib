# Dokumentacja Funkcji Numerycznych

## `approximate`

Funkcja ta znajduje wielomian stopnia `N-1`, który w sensie najmniejszych kwadratów najlepiej aproksymuje zadaną funkcję `f(x)` na przedziale `[a, b]`.

```cpp
std::vector<double> approximate(
    std::pair<double, double> ab,
    double (*f)(double),
    int N
);
```

### Opis Działania

Celem jest znalezienie współczynników `c_0, c_1, ..., c_{N-1}` wielomianu aproksymującego `W(x) = c_0 + c_1*x + ... + c_{N-1}*x^{N-1}`. Metoda najmniejszych kwadratów minimalizuje całkę kwadratu błędu między funkcją oryginalną `f(x)` a wielomianem `W(x)`:

`Error = ∫[a,b] (f(x) - W(x))^2 dx`

Minimalizacja tego błędu prowadzi do układu `N` równań liniowych `A*c = b`, gdzie `c` jest wektorem szukanych współczynników. Elementy macierzy `A` oraz wektora `b` są zdefiniowane następująco:

-   `A[i][j] = ∫[a,b] x^i * x^j dx = ∫[a,b] x^(i+j) dx`
-   `b[i] = ∫[a,b] f(x) * x^i dx`

Funkcja `approximate`:
1.  Tworzy macierz `A` (`matrix`) i wektor `b`, obliczając powyższe całki numerycznie (przy pomocy niewidocznej w kodzie funkcji `integrate`).
2.  Rozwiązuje powstały układ równań liniowych `A*c = b` za pomocą funkcji `solve_lin_eq`.
3.  Zwraca wektor współczynników `c`.

### Parametry

-   `std::pair<double, double> ab`: Para liczb `(a, b)` definiująca przedział całkowania i aproksymacji.
-   `double (*f)(double)`: Wskaźnik na funkcję `f(x)`, która ma być aproksymowana.
-   `int N`: Stopień wielomianu aproksymującego będzie wynosił `N-1`. Jest to również rozmiar tworzonego układu równań.

### Zwracana wartość

-   `std::vector<double>`: Wektor zawierający `N` współczynników `c_0, c_1, ..., c_{N-1}` wielomianu aproksymującego `W(x)`, gdzie `c_i` jest współczynnikiem przy `x^i`.

---

## `solve_diff_eq_runge_kutty`

Rozwiązuje równanie różniczkowe zwyczajne pierwszego rzędu postaci `y' = f(x, y)` z warunkiem początkowym `y(a) = y_0` na przedziale `[a, b]`, używając **metody Rungego-Kutty 4. rzędu (RK4)**.

```cpp
std::vector<double> solve_diff_eq_runge_kutty(
    int N,
    std::pair<double, double> ab,
    double y0,
    double (*f)(double, double)
);
```

### Opis Działania

Metoda RK4 jest iteracyjną metodą numeryczną do znajdowania przybliżonego rozwiązania równań różniczkowych. Dzieli ona przedział `[a, b]` na `N` kroków o stałej długości `h = (b-a)/N`. W każdej iteracji `i`, wartość `y_{i+1}` jest obliczana na podstawie `y_i` w następujący sposób:

1.  Oblicz krok `h = (b-a)/N`.
2.  Dla każdego kroku `i` od `0` do `N-1`, gdzie `x_i = a + i*h`:
    -   `k1 = h * f(x_i, y_i)`
    -   `k2 = h * f(x_i + h/2, y_i + k1/2)`
    -   `k3 = h * f(x_i + h/2, y_i + k2/2)`
    -   `k4 = h * f(x_i + h, y_i + k3)`
3.  Oblicz następną wartość rozwiązania:
    -   `y_{i+1} = y_i + (k1 + 2*k2 + 2*k3 + k4) / 6`

### Parametry

-   `int N`: Liczba kroków, na które zostanie podzielony przedział `[a, b]`.
-   `std::pair<double, double> ab`: Para liczb `(a, b)` definiująca przedział, na którym szukane jest rozwiązanie.
-   `double y0`: Wartość początkowa `y(a) = y_0`.
-   `double (*f)(double, double)`: Wskaźnik na funkcję `f(x, y)` z prawej strony równania różniczkowego `y' = f(x, y)`.

### Zwracana wartość

-   `std::vector<double>`: Wektor o rozmiarze `N+1` zawierający przybliżone wartości rozwiązania `y(x)` w punktach `x_i = a + i*h`. Element `out[0]` to `y0`, `out[1]` to `y(a+h)`, itd., aż do `out[N]` równego `y(b)`.

---

## `solve_lin_eq`

Rozwiązuje układ `N` równań liniowych postaci `A*x = b` metodą **eliminacji Gaussa z częściowym wyborem elementu podstawowego (partial pivoting)**.

```cpp
std::vector<double> solve_lin_eq(
    std::vector<std::vector<double>> matrix,
    std::vector<double> b,
    int N
);
```

### Opis Działania

Algorytm składa się z dwóch głównych etapów:

1.  **Eliminacja w przód (Forward Elimination)**:
    -   Tworzona jest macierz rozszerzona `[A|b]`.
    -   Macierz jest przekształcana do postaci górnej trójkątnej. W `k`-tym kroku eliminacji, dla `k`-tej kolumny, wyszukiwany jest wiersz (od `k` do `N-1`) z elementem o największej wartości bezwzględnej. Ten wiersz jest zamieniany z wierszem `k`-tym (to jest właśnie *częściowy wybór elementu podstawowego*, co zwiększa stabilność numeryczną).
    -   Następnie, za pomocą operacji elementarnych na wierszach, zerowane są wszystkie elementy w `k`-tej kolumnie poniżej przekątnej.

2.  **Podstawienie wsteczne (Back Substitution)**:
    -   Po uzyskaniu macierzy w postaci górnej trójkątnej, rozwiązanie jest znajdowane poprzez iteracyjne obliczanie niewiadomych, zaczynając od ostatniego równania (które ma tylko jedną niewiadomą `x_{N-1}`) i postępując w górę.
    -   `x_{N-1} = b'_{N-1} / A'_{N-1, N-1}`
    -   `x_i = (b'_i - Σ_{j=i+1}^{N-1} A'_{i,j}*x_j) / A'_{i,i}` dla `i = N-2, ..., 0`.

### Parametry

-   `std::vector<std::vector<double>> matrix`: Macierz `A` układu równań.
-   `std::vector<double> b`: Wektor `b` (wektor wyrazów wolnych).
-   `int N`: Wymiar macierzy (liczba równań i niewiadomych).

### Zwracana wartość

-   `std::vector<double>`: Wektor `x`, który jest rozwiązaniem układu równań `A*x = b`.

---

## `interpolate`

Oblicza wartość interpolowaną w punkcie `userInput` na podstawie zbioru `n` punktów `(x_i, f(x_i))`, używając **wielomianu interpolacyjnego Lagrange'a**.

```cpp
double interpolate(
    const FunctionData& data,
    double userInput,
    int n
);
```

### Opis Działania

Metoda Lagrange'a konstruuje wielomian `P(x)`, który przechodzi dokładnie przez wszystkie podane punkty `(x_i, y_i)`, gdzie `y_i = f(x_i)`. Wielomian ten jest sumą wielomianów bazowych Lagrange'a `L_i(x)` pomnożonych przez odpowiednie wartości funkcji `y_i`:

`P(x) = Σ_{i=0}^{n-1} y_i * L_i(x)`

Każdy wielomian bazowy `L_i(x)` jest zdefiniowany jako:

`L_i(x) = Π_{j=0, j≠i}^{n-1} (x - x_j) / (x_i - x_j)`

Wielomiany bazowe mają kluczową własność: `L_i(x_j) = 1` dla `i=j` i `L_i(x_j) = 0` dla `i≠j`, co gwarantuje, że `P(x_i) = y_i`. Funkcja oblicza wartość `P(userInput)` i ją zwraca.

### Parametry

-   `const FunctionData& data`: Struktura lub klasa przechowująca wektory z danymi: `data.x` (wartości `x_i`) i `data.fx` (wartości `y_i = f(x_i)`).
-   `double userInput`: Punkt `x`, dla którego ma zostać obliczona wartość interpolowana `P(x)`.
-   `int n`: Liczba punktów `(x_i, y_i)`, które zostaną użyte do interpolacji.

### Zwracana wartość

-   `double`: Obliczona, przybliżona wartość funkcji w punkcie `userInput`.

---

## `solve_nonlin_eq`

Znajduje miejsca zerowe (pierwiastki) funkcji nieliniowej `f(x) = 0` w zadanym przedziale `[a, b]`.

```cpp
// Wersja z domyślnym krokiem
std::vector<double> solve_nonlin_eq(
    double (*f)(double),
    std::pair<double, double> ab
);

// Wersja z zadanym krokiem
std::vector<double> solve_nonlin_eq(
    double (*f)(double),
    std::pair<double, double> ab,
    double step
);
```

### Opis Działania

Funkcja działa w dwóch etapach:

1.  **Wstępne poszukiwanie przedziałów (Bracketing)**:
    -   Główny przedział `[a, b]` jest dzielony na mniejsze podprzedziały o długości `step`.
    -   Dla każdego podprzedziału `[x_p, x_0]`, funkcja próbuje znaleźć w nim miejsce zerowe. Takie podejście pozwala zlokalizować wiele pierwiastków w całym zakresie `[a, b]`.

2.  **Znajdowanie pierwiastka (Root Finding)**:
    -   Dla każdego podprzedziału, funkcja wywołuje **metodę siecznych (Regula Falsi / metoda fałszywej prostej)**, aby dokładnie zlokalizować pierwiastek.
    -   Metoda Regula Falsi jest iteracyjna. W każdym kroku `k`, funkcja jest przybliżana linią prostą (sieczną) przechodzącą przez punkty `(x_{k-1}, f(x_{k-1}))` i `(x_k, f(x_k))`. Nowe przybliżenie pierwiastka, `x_{k+1}`, to punkt przecięcia tej prostej z osią OX:
        `x_{k+1} = x_k - f(x_k) * (x_k - x_{k-1}) / (f(x_k) - f(x_{k-1}))`
    -   Proces jest kontynuowany aż do osiągnięcia zadowalającej dokładności.

3.  **Filtrowanie wyników**:
    -   Po znalezieniu potencjalnych pierwiastków, wyniki są filtrowane, aby usunąć wartości niepoprawne (`NaN`), zduplikowane oraz te, które nie leżą w zadanym przedziale `[a, b]` lub dla których wartość `f(x)` nie jest wystarczająco bliska zeru.

### Parametry

-   `double (*f)(double)`: Wskaźnik na funkcję `f(x)`, której miejsca zerowe szukamy.
-   `std::pair<double, double> ab`: Para `(a, b)` definiująca przedział poszukiwań.
-   `double step` (opcjonalny): Długość kroku używanego do podziału przedziału `[a, b]` na mniejsze podprzedziały. Domyślnie wynosi `0.01`.

### Zwracana wartość

-   `std::vector<double>`: Wektor zawierający znalezione i zweryfikowane miejsca zerowe funkcji `f(x)` w przedziale `[a, b]`.