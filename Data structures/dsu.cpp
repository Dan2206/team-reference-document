const int M = 2 * N;
int p[N], sz[N];
void init() {
    for (int i = 0; i < N; i++) {
        sz[i] = 1;
        p[i] = i;
    }
}
int get_leader(int v) {
    if (v == p[v]) return v;
    return (p[v] = get_leader(p[v]));
    // для откатов return get_leader(p[v])
}
int val[M];
int* where[M];
int state = 0;
void change(int& x, int y) {
    val[state] = x;
    where[state] = &x;
    state++;
    x = y;
}
void rollback_to(int a) {
    while(state > a) {
        state--;
        (*where[state]) = val[state];
    }
}
bool merge(int v, int u) {
    v = get_leader(v);
    u = get_leader(u);
    if (v == u) return false;
    if (sz[v] > sz[u]) swap(v, u);
    change(p[v], u);
    change(sz[u], sz[u] + sz[v]);
    return true;
}
