const int LN = 19;
vector<cd> w[LN];
 
int rev(int x, int k) {
  int y = 0;
  for (int i = 0; i < k; i++) {
    y |= (((x >> i) & 1) << (k - i - 1));
  }
  return y;
}
 
void pr() {
  for (int i = 1; i < LN; i++) {
    int j = (1 << i);
    j /= 2;
    w[i].resize(j);
    double ang = 2 * acos(-1) / (1 << i);
    cd cur = { cos(ang), sin(ang) };
    w[i][0] = { 1, 0 };
    for (int k = 1; k < j; k++) {
      w[i][k] = w[i][k - 1] * cur;
    }
  }
}
 
void fft(vector<cd>& a, bool inv = false) {
  int k = 0, n = a.size();
  while ((1 << k) < n) k++;
  for (int i = 0; i < n; i++) {
    int j = rev(i, k);
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 1, d = 0; len < n; len *= 2, d++) {
    for (int pos = 0; pos < n; pos += 2 * len) {
      for (int i = 0; i < len; i++) {
        cd x = a[pos + i];
        cd y = a[pos + i + len] * w[d + 1][i];
        a[pos + i] = x + y;
        a[pos + i + len] = x - y;
      }
    }
  }
  if (inv) {
    reverse(a.begin() + 1, a.end());
    for (int i = 0; i < n; i++) {
      a[i] /= n;
    }
  }
}
 
vector<li> mul(vector<int>& a, vector<int>& b) {
  int n = a.size(), m = b.size();
  int k = 1;
  while (k < n + m + 1) k *= 2;
  vector<cd> aa(k), bb(k);
  for (int i = 0; i < n; i++)
    aa[i] = { a[i] * 1.0, 0.0 };
  for (int i = 0; i < m; i++)
    bb[i] = { b[i] * 1.0, 0.0 };
  fft(aa);
  fft(bb);
  for (int i = 0; i < k; i++)
    aa[i] *= bb[i];
  fft(aa, true);
  vector<li> res(k);
  for (int i = 0; i < k; i++)
    res[i] = llround(aa[i].real());
  while (res.size() > 1 && res.back() == 0)
    res.pop_back();
  return res;
}