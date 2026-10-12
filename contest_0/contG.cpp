#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  long long s;
  std::cin >> s;
  int na;
  int nb;
  int nc;
  std::cin >> na;
  std::vector<int> a(na);
  for (int i = 0; i < na; i++)
    std::cin >> a[i];
  std::cin >> nb;
  std::vector<int> b(nb);
  for (int i = 0; i < nb; i++)
    std::cin >> b[i];
  std::cin >> nc;
  std::vector<int> c(nc);
  for (int i = 0; i < nc; i++)
    std::cin >> c[i];
  std::vector<std::pair<int, int>> sb, sc;
  for (int i = 0; i < nb; i++)
    sb.push_back({b[i], i});
  for (int i = 0; i < nc; i++)
    sc.push_back({c[i], i});
  std::sort(sb.begin(), sb.end());
  std::sort(sc.begin(), sc.end());
  std::vector<std::pair<int, int>> uc;
  for (int i = 0; i < nc;)
  {
    int val = sc[i].first;
    int mn = sc[i].second;
    int j = i + 1;
    while (j < nc && sc[j].first == val)
    {
      mn = std::min(mn, sc[j].second);
      j++;
    }
    uc.push_back({val, mn});
    i = j;
  }
  for (int i = 0; i < na; i++)
  {
    long long t = s - a[i];
    int p = 0, q = nc - 1;
    int bestj = -1;
    while (p < nb && q >= 0)
    {
      long long sum = (long long)sb[p].first + sc[q].first;
      if (sum == t)
      {
        if (bestj == -1 || sb[p].second < bestj)
          bestj = sb[p].second;
        p++;
      }
      else if (sum > t)
      {
        q--;
      }
      else
      {
        p++;
      }
    }
    if (bestj != -1)
    {
      long long need = t - b[bestj];
      int lo = 0, hi = (int)uc.size() - 1, k = -1;
      while (lo <= hi)
      {
        int mid = (lo + hi) / 2;
        if (uc[mid].first == need)
        {
          k = uc[mid].second;
          break;
        }
        else if (uc[mid].first < need)
        {
          lo = mid + 1;
        }
        else
        {
          hi = mid - 1;
        }
      }
      if (k != -1)
      {
        std::cout << i << " " << bestj << " " << k << "\n";
        return 0;
      }
    }
  }
  std::cout << -1;
}