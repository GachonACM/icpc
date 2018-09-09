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
struct Node {
	int key;
	int priority, size;
	Node *left, *right;
	Node(const int& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {
	}
	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};

typedef pair<Node*, Node*> NodePair;
NodePair split(Node *root, int key) {
	if (root == NULL) return NodePair(NULL, NULL);
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

Node* insert(Node* root, Node* node) {
	if (root == NULL) return node;
	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if (node->key < root->key) {
		root->setLeft(insert(root->left, node));
	}
	else {
		root->setRight(insert(root->right, node));
	}
	return root;
}
// root  = insert(root, new Node(value));
Node* merge(Node* a, Node* b) {
	if (a == NULL) return b;
	if (b == NULL) return a;
	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

Node* erase(Node* root, int key) {
	if (root == NULL) return root;
	if (root->key == key) {
		Node *ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if (key < root->key) {
		root->setLeft(erase(root->left, key));
	}
	else {
		root->setRight(erase(root->right, key));
	}
	return root;
}

Node* kth(Node* root, int k) {
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
	if(k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1) return root;
	return kth(root->right, k - leftSize - 1);
}

class SegmentTree {
public:
	typedef int dtype;
	vector<dtype> tree;
	int s;
	SegmentTree(int n, int type) {
		for (s = 1; s < n; s *= 2) {}
		tree.resize(s * 2);
		if (type = 1)
			for (int i = 1; i < s * 2; i++) tree[i] = 0;
		else
			for (int i = 1; i < s * 2; i++) tree[i] = 6544321;
	}
	void maxupdate(int idx, int value) {
		int l = idx + s - 1;
		tree[l] += value;
		while (l > 1) {
			l /= 2;
			tree[l] = max(tree[l * 2], tree[l * 2 + 1]);
		}
	}
	void minupdate(int idx, int value) {
		int l = idx + s - 1;
		tree[l] += value;
		while (l > 1) {
			l /= 2;
			tree[l] = min(tree[l * 2], tree[l * 2 + 1]);
		}
	}
	int findKth(int k) {
		int l = 1;
		while (l * 2 < tree.size()) {
			if (tree[l*2] >=k) {
				l = l * 2;
			}
			else {
				k -= tree[l * 2];
				l = l * 2 + 1;
			}
		}
		return l - s + 1;
	} 
	int findMAX(int left, int right) {
		int l = left + s - 1, r = right + s - 1;
		int rval = 0;
		while (l <= r) {
			if (l % 2 == 0) l /= 2;
			else {
				rval = max(rval, tree[l]);
				l = (l / 2) + 1;
			}
			if (r % 2 == 1) r /= 2;
			else {
				rval = max(rval, tree[r]);
				r = (r / 2) - 1;
			}
		}
		return rval;
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); 
	int tc; cin >> tc;
	while (tc--) {
		int n, q; cin >> n >> q;
		SegmentTree MAXTree(n, 1);
		SegmentTree MINTree(n, 2);
		for (int i = 0; i < n; i++) {
			int height; cin >> height;
			MAXTree.maxupdate(i, height);
			MINTree.minupdate(i, height); 
			//initailize segment tree
		}
		for (int query = 0; query < q; query++) {
			int l, r; cin >> l >> r;
			cout << MAXTree.findMAX(l, r) - MINTree.findMIN(l, r) << "\n";
		}
	}
 
}
