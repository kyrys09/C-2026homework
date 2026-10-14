#include <iomanip>
#include <iostream>

double Average(const int *array, int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += array[i];
  }
  return (double)sum / n;
}

void MinMax(const int *array, int n, int &minval, int &maxval) {
  minval = array[0];
  maxval = array[0];
  for (int i = 1; i < n; i++) {
    if (array[i] < minval) {
      minval = array[i];
    }
    if (array[i] > maxval) {
      maxval = array[i];
    }
  }
}

int CntLowZero(const int *array, int n) {
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (array[i] < 0) {
      cnt++;
    }
  }
  return cnt;
}

int main() {
  int n;
  std::cin >> n;

  int *array = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> array[i];
  }

  std::cout << std::fixed << std::setprecision(1) << Average(array, n) << "\n";

  int minval, maxval;
  MinMax(array, n, minval, maxval);
  std::cout << minval << ' ' << maxval << "\n";

  std::cout << CntLowZero(array, n);

  delete[] array;
  return 0;
}