#include <limits.h>
#include <stdio.h>
// Function to calculate the optimal parenthesization and the number of scalar multiplications required for the given matrix-chain product.
int matrix_chain_multiplication(int p[], int n) {
  // Create the M-table and S-table.
  int m[n + 1][n + 1];
  int s[n + 1][n + 1];

  // Initialize the M-table and S-table.
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      m[i][j] = 0;
      s[i][j] = 0;
    }
  }

  // Fill in the M-table and S-table.
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      if (i == j) {
        m[i][j] = 0;
      } else {
        m[i][j] = INT_MAX;
        for (int k = i; k < j; k++) {
          int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
          if (q < m[i][j]) {
            m[i][j] = q;
            s[i][j] = k;
          }
        }
      }
    }
  }

  // Find the optimal parenthesization.
  int optimal_parenthesization[n];
  void print_optimal_parenthesization(int i, int j) {
    if (i == j) {
      optimal_parenthesization[i - 1] = i;
    } else {
      int k = s[i][j];
      optimal_parenthesization[i - 1] = '(';
      print_optimal_parenthesization(i, k);
      printf(" * ");
      print_optimal_parenthesization(k + 1, j);
      optimal_parenthesization[i - 1] = ')';
    }
  }

  print_optimal_parenthesization(1, n);

  // Return the number of scalar multiplications required.
  return m[1][n];
}

int main() {
  // Get the dimensions of the matrices from the user.
  int n;
  printf("PRATEEK RAJ\n21052010\n");
  printf("Enter number of matrices: ");
  scanf("%d", &n);

  int p[2 * n];
  for (int i = 0; i < 2 * n; i++) {
    printf("Enter row and col size of A%d: ", i + 1);
    scanf("%d %d", &p[i], &p[i + 1]);
  }

  // Calculate the number of scalar multiplications required.
  int number_of_scalar_multiplications = matrix_chain_multiplication(p, n);

  // Print the result.
  printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", number_of_scalar_multiplications);

  return 0;
}