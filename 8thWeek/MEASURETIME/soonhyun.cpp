#include <iostream> 
#include <vector>
#include <algorithm>
#include <queue> 
#include <string>
#include <unordered_map>
#include <memory.h>
#include <set>
#include <map>
#include <math.h>
#include <assert.h>
#include <unordered_set>

using namespace std;
typedef long long ll;
class SegmentTree {
public:
	vector<int> tree;
	int s; 
	SegmentTree(int n) {
		for (s = 1; s < n; s *= 2) {
		}
		tree.resize(s * 2);
		for (int i = 1; i < s * 2; i++) {
			tree[i] = 0;
		}
	}
	void update(int index, int value) {
		int l = index + s - 1;
		tree[l] = tree[l] + 1;
		while (l > 1) {
			l /= 2;
			tree[l] = tree[l * 2] + tree[l * 2 + 1];
		}
	}
	int getSum(int left, int right) {
		int l = left + s - 1, r = right + s - 1;
		int rval = 0;
		while (l <= r) {
			if (l % 2 == 0) l /= 2;
			else {
				rval += tree[l];
				l = l / 2 + 1;
			}
			if (r % 2 == 1) r /= 2;
			else {
				rval += tree[r];
				r = r / 2 - 1;
			}
		}
		return rval;
	}

};
int arr[500000];
int idx[500000];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		map<int, int> ma;
		SegmentTree Tree(n);
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
			idx[i] = arr[i];
		}
		sort(idx, idx + n);
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if (ma.find(idx[i]) == ma.end()) {
				ma.insert(make_pair(idx[i], ++cnt));
			}
		}
		ll ans = 0;
		for (int i = 0; i < n; i++) {
			int v = ma[arr[i]];
			ans += Tree.getSum(v + 1, n);
			Tree.update(v, 1);
		}
		cout << ans << "\n";
		// A[0, i-1] 구간에 A[i]보다 큰 숫자가 몇개?
		
	}
}
