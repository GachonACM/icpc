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
	typedef int dtype;
	vector<dtype> tree;
	int s;
	SegmentTree(int n) {
		for (s = 1; s < n; s *= 2) {}
		tree.resize(s * 2);
		for (int i = 1; i < s * 2; i++) tree[i] = INT32_MAX;
	}
	void update(int idx, int value) {
		int l = idx + s - 1;
		tree[l] = value;
		while (l > 1) {
			l /= 2;
			tree[l] = min(tree[l * 2], tree[l * 2 + 1]);
		}
	}
	int findKth(int k) {
		int l = 1;
		while (l * 2 < tree.size()) {
			if (tree[l * 2] >= k) {
				l = l * 2;
			}
			else {
				k -= tree[l * 2];
				l = l * 2 + 1;
			}
		}
		return l - s + 1;
	}
	int findMIN(int left, int right) {
		int l = left + s - 1, r = right + s - 1;
		int rval = INT32_MAX;
		while (l <= r) {
			if (l % 2 == 0) l /= 2;
			else {
				rval = min(rval, tree[l]);
				l = (l / 2) + 1;
			}
			if (r % 2 == 1) r /= 2;
			else {
				rval = min(rval, tree[r]);
				r = (r / 2) - 1;
			}
		}
		return rval;
	}
};

int depth[200001];
map<int, int> no2serial, serial2no;
map<int, int> locInTrip;
int nextSerial = 1;
vector<vector<int> > child;
void traverse(int here, int d, vector<int>& trip) {
	// cal depth
	depth[here] = d;
	if (locInTrip.find(here) == locInTrip.end()) {
		locInTrip.insert(make_pair(here, (int)trip.size()));
	}
	trip.push_back(no2serial[here]);
	for (int i = 0; i < child[here].size(); i++) {
		traverse(child[here][i], d + 1, trip);
		trip.push_back(no2serial[here]);
	}
}
bool visited[100001];
void init(int here) {
	visited[here] = true;
	if (no2serial.find(here) == no2serial.end()) {
		no2serial.insert(make_pair(here, nextSerial));
		serial2no.insert(make_pair(nextSerial, here));
	}
	++nextSerial;
	for (int i = 0; i < child[here].size(); i++) {
		if (!visited[child[here][i]])
			init(child[here][i]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int tc; cin >> tc;
	while (tc--) {
		int n, q; cin >> n >> q;
		nextSerial = 1;
		child.clear();
		child.resize(n);
		for (int i = 1; i < n; i++) {
			int parent; cin >> parent;
			child[parent].push_back(i);
		}
		memset(visited, false, sizeof(visited));
		init(0);
	
		vector<int> trip;
		traverse(0, 0, trip); //순회가정중 만나는 노드들의 일련 번호
		/*cout << "trips segment : ";
		for (auto seg : trip) {
			cout << seg << " ";
		}
		cout << "\n";*/
		SegmentTree Tree(trip.size());
		for (int i = 0; i < trip.size(); i++) {
			Tree.update(i, trip[i]);
		}
		while (q--) {
			int left, right; cin >> left >> right;
			int l = locInTrip[left];
			int r = locInTrip[right];
			if (l > r) {
				int tmp = r;
				r = l;
				l = tmp;
			} 
			int lca = serial2no[Tree.findMIN(l, r)];
			/*cout << "left=" << left << ",right=" << right << ",lca=" << lca << endl;
			cout << "first left=" << locInTrip[left] << ",first right=" << locInTrip[right] << endl;*/
			cout << depth[left] + depth[right] - 2 * depth[lca] << "\n";
		}
		no2serial.clear();
		serial2no.clear();
		locInTrip.clear();
	}
}
