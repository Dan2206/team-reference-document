auto func = [&](int i, int j) {
    return s[i] < s[j];
};
vector<int> lis;
vector<int> pr(n, -1);
for (int i = 0; i < n; i++) {
    auto it = lower_bound(lis.begin(), lis.end(), i, func);
    if (it == lis.end()) {
        if (it != lis.begin())
            pr[i] = *(prev(it));
        lis.push_back(i);
    }
    else {
        if (it != lis.begin())
            pr[i] = *(prev(it));
        *it = i;
    }
}
