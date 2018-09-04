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


vector<int> preorder, inorder, postorder;
int n; 
void go(int pnum, vector<int> s) {
	int rootnode = preorder[pnum];  
	vector<int> left, right;
	int idx = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == rootnode) {
			idx = i;
			break;
		}
		left.push_back(s[i]);
	}
	for (int i = idx + 1; i < s.size(); i++) {
		right.push_back(s[i]);
	}


	if (left.size()) {
		go(pnum+1, left);
	} 
	if (right.size()) {
		go(pnum + idx + 1, right);
	}
	cout << rootnode << " ";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); 
	int tc; cin >> tc;
	while (tc--) {
		preorder.clear();
		inorder.clear();
		cin >> n;   
		for (int i = 0; i < n; i++) {
			int node; cin >> node;
			preorder.push_back(node);
		}
		for (int i = 0; i < n; i++) {
			int node; cin >> node;
			inorder.push_back(node);
		}
		go(0, inorder);
		cout << "\n";
	} 
}
