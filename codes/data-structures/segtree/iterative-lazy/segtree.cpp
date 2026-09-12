// LAZY ITERATIVE - implemented for Hash + range assignment
// for reference, see DoubleHashing implementation
// always call rangeUpdate with true on tag
struct segtree {
  struct node {
    struct tag {
      int val = 0; // make sure default values are correct
      bool has = false;
    };
    Hash hash; // custom stuff
    int len = 0;
    tag lazy;
    // combine custom stuff
    static node combine(const node &a, const node &b){}
    void apply(tag t){
      if (!t.has) return;
      // apply tag to custom stuff
      lazy = t; // remember to upd lazy tag
    }
    void push(node &left, node &right){
      if (!lazy.has) return;
      left.apply(lazy);
      right.apply(lazy);
      lazy = tag(); 
    }
    void pull(const node &left, const node &right){
      tag cur = lazy;
      *this = combine(left,right);
      apply(cur);
    }
  };    
  int n, h;
  vector<node> t;
  segtree(const string& a) {
    int sz = a.size();
    n = 1; h = 0;
    while (n < sz) { n*=2; h++; } 
    
    t.assign(2*n, node());
    
    for (int i = 0; i < sz; i++) {
        t[i+n].len = 1; // init custom stuff
        t[i+n].hash.len = 1;
        t[i+n].apply({a[i], true});
    }
    for (int i = n-1; i > 0; i--) t[i].pull(t[i<<1], t[i<<1|1]);
  }
  void build(int p) {
    while (p > 1) p >>= 1, t[p].pull(t[p<<1], t[p<<1|1]);
  }
  void push(int p) {
    for (int s = h; s > 0; s--) {
      int i = p >> s;
      t[i].push(t[i<<1], t[i<<1|1]);
    }
  }
  void rangeUpdate(int l, int r, node::tag v) {
    if (l==r) return;
    l += n, r += n;
    int l0 = l, r0 = r;
    
    push(l0); push(r0-1);
    for (; l < r; l >>= 1, r >>= 1) {
      if (l&1) t[l++].apply(v);
      if (r&1) t[--r].apply(v);
    }
    build(l0); build(r0-1);
  }
  node query(int l, int r) {
    if (l == r) return node();
    l += n, r += n;
    push(l); push(r-1);
    node resL = node(), resR = node();
    for (; l < r; l >>= 1, r >>= 1) {
      if (l&1) resL = node::combine(resL, t[l++]);
      if (r&1) resR = node::combine(t[--r], resR);
    }
    return node::combine(resL, resR);
  }
};