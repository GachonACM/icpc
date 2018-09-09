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
	SegmentTree(int n) {
		for (s = 1; s < n; s *= 2) {}
		tree.resize(s * 2);
		for (int i = 1; i < s * 2; i++)tree[i] = numeric_limits<dtype>::max();
	}
	void insert(vector<dtype> &d) {
		for (int i = s; i < s + d.size(); i++) {
			tree[i] = d[i - s];
		}
		for (int i = s - 1; i >= 1; i--) {
			tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
		}
	}
	dtype getMin(int Left, int Right) {
		int l = Left + s - 1, r = Right + s - 1;
		dtype rval = numeric_limits<dtype>::max();
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
	int tc;
	cin >> tc;
	while (tc--) {
		int n, a, b; cin >> n >> a >> b;
		int arr[200001];
		arr[0] = 1983;
		Node* bts = NULL;
		bts = insert(bts, new Node(arr[0]));
		ll ans = arr[0];
		for (int i = 1; i < n; i++) {
			arr[i] =(int)(((ll)arr[i - 1] * a + b ) % 20090711);
			bts = insert(bts, new Node(arr[i]));
			int idx = 1 + i / 2;
			Node* k = kth(bts, idx);
			 
			ans = (ans +  k->key) % 20090711;
		}
		cout << ans<<"\n";
	}
	
 
}
