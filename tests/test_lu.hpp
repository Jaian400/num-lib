#include "../include/lu.hpp"

int test_lu(int c){
    if (c < 2){
        std::cerr << "Brak argumentow.\n";
        return -1;
    }
    std::string data_names [4] = {"LU_gr4.txt", "gauss_elimination_gr4_A.txt", "gauss_elimination_gr4_B.txt",
                                    "gauss_elimination_gr4_C.txt"};
    FunctionData data = load_data(data_names[c]);

    int N = data.x.size();

    double A[MAXN][MAXN+1];
    double A_prim[MAXN][MAXN+1];
    double L[MAXN][MAXN+1];
    double U[MAXN][MAXN+1];
    double b[MAXN];

    int count = 0;
    for(int i = 0; i < N;i++){
        for (int j = 0; j < N; j++)
        {
            A[i][j] = data.fx[count];
            A_prim[i][j] = data.fx[count];
            count++;
        }
        b[i] = data.x[i];
        // A[i][N] = data.x[i];
        A_prim[i][N] = data.x[i];
    }

    std::cout<<"\n\n--------------------------DANE--------------------------\n\n";

    std::cout<<"Wczytano nastepujaca macierz:\n";
    print_matrix(N, A);

    create_matrixes(N, A, L, U);
    std::cout<<"Macierz L:\n";
    print_matrix(N, L);
    std::cout<<"\n";
    std::cout<<"Macierz U:\n";
    print_matrix(N, U);
    std::cout<<"\n";

    double test_multip[MAXN][MAXN+1];

    std::cout<<"Multiplied L x U:\n";
    multiply_matrices(N, L, U, test_multip);
    print_matrix(N, test_multip);

    std::cout<<"\n\n--------------------------ROZWIAZAYWANIE--------------------------\n\n";
    double z[MAXN];
    double x[MAXN];
    // L * U * x = b
    // L * z = b
    // U * x = z
    
    forward_substitution(N, L, b, z);
    backward_substitution(N, U, z, x);

    std::cout << "Zetki: \n";
    for (int i = 0; i < N; i++) {
        std::cout << "z" << i << std::setw(14) << z[i] << "\n";
    }

    std::cout << "Rozwiazania: \n";
    for (int i = 0; i < N; i++) {
        std::cout << "x" << i << std::setw(14) << x[i] << "\n";
    }

    std::cout<<"\n\n--------------------------WERYFIKACJA--------------------------\n\n";

    check_precision_lu(A_prim, N, x);

    return 0;
}
