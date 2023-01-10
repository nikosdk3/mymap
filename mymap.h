// mymap.h
//
// Author: Nikos Kotsopulos
// Description: map implementation using a binary search tree within a class called mymap.
#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <typename keyType, typename valueType>
class mymap
{
private:
	struct NODE
	{
		keyType key;	 // used to build BST
		valueType value; // stored data for the map
		NODE *left;		 // links to left child
		NODE *right;	 // links to right child
		int nL;			 // number of nodes in left subtree
		int nR;			 // number of nodes in right subtree
		bool isThreaded;
	};
	NODE *root; // pointer to root node of the BST
	int size;	// # of key/value pairs in the mymap

	//
	// iterator:
	// This iterator is used so that mymap will work with a foreach loop.
	//
	struct iterator
	{
	private:
		NODE *curr; // points to current in-order node for begin/end

	public:
		iterator(NODE *node)
		{
			curr = node;
		}

		keyType operator*()
		{
			return curr->key;
		}

		bool operator==(const iterator &rhs)
		{
			return curr == rhs.curr;
		}

		bool operator!=(const iterator &rhs)
		{
			return curr != rhs.curr;
		}

		bool isDefault()
		{
			return !curr;
		}

		//
		// operator++:
		//
		// This function should advance curr to the next in-order node.
		// O(logN)
		//
		iterator operator++()
		{
			if (curr->isThreaded == true)
			{
				curr = curr->right;
			}
			else
			{
				curr = curr->right;
				while (curr->left != nullptr)
					curr = curr->left;
			}
			return iterator(curr); // TODO: Update this return.
		}
	};

public:
	// helper for toString function
	void toStringHelper(ostream &output, NODE *node)
	{
		if (node == nullptr)
			return;
		toStringHelper(output, node->left); // recursion to left
		output << "key: " << node->key << " value: " << node->value << endl;
		if (node->isThreaded == false)
			toStringHelper(output, node->right); // recursion to right
		else
			return;
	}
	//
	// default constructor:
	//
	// Creates an empty mymap.
	// Time complexity: O(1)
	//
	mymap()
	{
		root = nullptr;
		size = 0;
	}

	//helper for copy constructor function
	void _copy(NODE *node)
	{
		if (node == nullptr)
			return;
		put(node->key, node->value);
		_copy(node->left);
		if (node->isThreaded == false)
			_copy(node->right);
	}

	//
	// copy constructor:
	//
	// Constructs a new mymap which is a copy of the "other" mymap.
	// Sets all member variables appropriately.
	// Time complexity: O(nlogn), where n is total number of nodes in threaded,
	// self-balancing BST.
	//
	mymap(const mymap &other)
	{
		root = nullptr;
		size = 0;
		_copy(other.root);
	}

	//
	// operator=:
	//
	// Clears "this" mymap and then makes a copy of the "other" mymap.
	// Sets all member variables appropriately.
	// Time complexity: O(nlogn), where n is total number of nodes in threaded,
	// self-balancing BST.
	//
	mymap &operator=(const mymap &other)
	{
		this->clear();
		_copy(other.root);
		return *this;
	}

	void postOrderClear(NODE *node)
	{
		if (node == nullptr)
			return;
		postOrderClear(node->left);
		postOrderClear((node->isThreaded) ? nullptr : node->right);
		delete node;
		node = nullptr;
		size--;
	}

	// clear:
	//
	// Frees the memory associated with the mymap; can be used for testing.
	// Time complexity: O(n), where n is total number of nodes in threaded,
	// self-balancing BST.
	//
	void clear()
	{
		NODE *curr = root;
		postOrderClear(curr);
		size = 0;
		root = nullptr;
	}
	//
	// destructor:
	//
	// Frees the memory associated with the mymap.
	// Time complexity: O(n), where n is total number of nodes in threaded,
	// self-balancing BST.
	//
	~mymap()
	{
		postOrderClear(root);
		root = nullptr;
		size = 0;
	}

	// Helper function for insertNODE to find the location of insertion in the BST
	void findInsertLoc(keyType &key, valueType &value, NODE *&prev, NODE *&cur)
	{
		while (cur != nullptr) // loop to find if key already exists in map
		{
			if (cur->key == key)
			{
				cur->value = value;
				return;
			}
			else if (cur->key > key) // key is smaller than current node's key, go to the left
			{
				prev = cur;
				cur->nL++;
				cur = cur->left;
			}
			else // key is bigger than current node's key, go to the right
			{
				prev = cur;
				cur->nR++;
				if (cur->isThreaded)
					cur = nullptr;
				else
					cur = cur->right;
			}
		}
	}

	// Helper function to insert node
	void insertNODE(keyType insertKey, valueType insertValue)
	{
		NODE *cur = root;	  // reference to root node
		NODE *previous = cur; // keep track of previous node
		if (root == nullptr)  // first check if bst is empty
		{
			NODE *temp = new NODE; // make new node for insertion if there is nothing in the BST
			temp->key = insertKey;
			temp->value = insertValue;
			temp->right = nullptr;
			temp->left = nullptr;
			temp->nL = 0;
			temp->nR = 0;
			temp->isThreaded = true;
			root = temp; // set root to be the first node
			size++;		 // increment size
			return;
		}

		// find where node should be placed
		findInsertLoc(insertKey, insertValue, previous, cur);

		NODE *insert = new NODE;	   // if key is not in map already, insert it. New node created to insert.
		if (previous->key > insertKey) // inserting to the left of where loop left off
		{
			previous->left = insert;
			insert->right = previous;
		}
		else if (previous->key < insertKey) // inserting to the right of where loop left off
		{
			insert->right = previous->right;
			previous->right = insert;
			previous->isThreaded = false;
		}
		insert->key = insertKey;
		insert->value = insertValue;
		insert->left = nullptr;
		insert->nL = 0;
		insert->nR = 0;
		insert->isThreaded = true;
		size++; // increment size
	}

	// Helper function to check if there is an existing key
	bool checkExistingKey(NODE *&node, keyType checkKey)
	{
		NODE *temp = node;
		while (temp != nullptr) // loop to find if key already exists in map
		{
			if (temp->key == checkKey) // if key already exists in map, update value at that key
			{
				node = temp;
				return true;
			}
			else if (temp->key > checkKey) // key is smaller than current temp's key, go to the left
			{
				temp = temp->left;
			}
			else // key is bigger than current temp's key, go to the right
			{
				if (temp->isThreaded)
					temp = nullptr;
				else
					temp = temp->right;
			}
		}
		return false;
	}

	// helper function to find the violator
	NODE *findViolator(NODE *node)
	{
		if (node == nullptr)
			return nullptr;
		if (max(node->nL, node->nR) > 2 * min(node->nL, node->nR) + 1) // check the seasaw property
			return node;											   // if it does not pass, this node is the violator

		// preorder recursion to find violating node
		findViolator(node->left);
		if (node->isThreaded == false)
			findViolator(node->right);
		return nullptr;
	}

	// helper function to find the violator's parent
	NODE *findViolatorParent(NODE *parent, NODE *node)
	{
		if (parent == nullptr || (parent->left == nullptr && parent->right == nullptr)) // base case
			return nullptr;
		if ((parent->right != nullptr && parent->right->key == node->key) || (parent->left != nullptr && parent->left->key == node->key))
		{ // start from root and check left and right and right pointers to see if they match the violator's key
			return parent;
		}
		// if this is not the case, advance the root until it is a parent of the violator
		// usual recursion
		if (parent->key > node->key)
			return findViolatorParent(parent->left, node);
		if (parent->key < node->key)
		{
			if (parent->isThreaded)
				return nullptr;
			return findViolatorParent(parent->right, node);
		}
	}

	// helper function to store nodes of violator subtree into vector
	void pushNodesToRebalance(NODE *node, vector<NODE *> &rebalance)
	{
		// same function as _toVector except with vector<NODE*> data type instead of a pair
		if (node == nullptr)
			return;
		pushNodesToRebalance(node->left, rebalance);
		rebalance.push_back(node);
		if (node->isThreaded)
			return;
		pushNodesToRebalance(node->right, rebalance);
	}

	// helper function for _rebalance to reconnect the threads
	void reconnectThreads(NODE *rebalanceRoot, NODE *subRootParent)
	{
		if (rebalanceRoot == nullptr)
			return;
		reconnectThreads(rebalanceRoot->left, subRootParent);
		rebalanceRoot->isThreaded = false;
		if (rebalanceRoot->right == nullptr)
			rebalanceRoot->right = subRootParent;
		reconnectThreads(rebalanceRoot->right, subRootParent);
	}

	// helper function for rebalance
	NODE *_rebalance(vector<NODE *> subTree, int start, int end, NODE *parent, NODE *violatingParent)
	{
		int mid = (start + end) / 2;

		// base case 1
		if (subTree.size() == 0)
			return nullptr;
		// base case 2
		if (subTree.size() == 1)
		{
			NODE *subTreeRoot = subTree.at(mid);
			subTreeRoot->nL = 0;
			subTreeRoot->nR = 0;
			subTreeRoot->left = nullptr;
			subTreeRoot->right = parent->right;
			subTreeRoot->isThreaded = true;
			return subTreeRoot;
		}

		NODE *subTreeRoot = subTree.at(mid);
		subTreeRoot->nL = 0;
		subTreeRoot->nR = 0;
		subTreeRoot->left = nullptr;
		subTreeRoot->right = nullptr;
		if (start <= mid - 1)
		{
			subTreeRoot->left = _rebalance(subTree, start, mid - 1, subTreeRoot, violatingParent);
			subTreeRoot->nL = subTreeRoot->left->nL + subTreeRoot->left->nR + 1;
		}

		reconnectThreads(subTreeRoot, violatingParent);

		if (mid + 1 >= end)
		{
			subTreeRoot->right = _rebalance(subTree, mid + 1, end, subTreeRoot, violatingParent);
			subTreeRoot->nR = subTreeRoot->right->nL + subTreeRoot->right->nR + 1;
		}
		return subTreeRoot;
	}

	// function to balance nodes from violating vector
	NODE *rebalance(vector<NODE *> &violatingVector, NODE *parent)
	{
		int left = 0;
		int right = violatingVector.size() - 1;
		int mid = (left + right) / 2;
		NODE *violatingTreeRoot = _rebalance(violatingVector, left, right, violatingVector.at(mid), parent);
	}

	//
	// put:
	//
	// Inserts the key/value into the threaded, self-balancing BST based on
	// the key.
	// Time complexity: O(logn + mlogm), where n is total number of nodes in the
	// threaded, self-balancing BST and m is the number of nodes in the
	// sub-tree that needs to be re-balanced.
	// Space complexity: O(1)
	//
	void put(keyType key, valueType value)
	{
		// vector<NODE *> nodesToRebalance; // vector to push in nodes of subtree that are not balanced
		NODE *cur = root;
		// NODE *violatorParent = nullptr;
		// NODE *violator = nullptr;
		if (checkExistingKey(cur, key))
		{
			cur->value = value;
			return;
		}

		// function to insert NODE
		insertNODE(key, value);

		// violator = findViolator(cur);
		// if (violator != nullptr)
		// {
		// 	cur = root;
		// 	violatorParent = findViolatorParent(cur, violator);
		// 	nodesToRebalance.clear();
		// 	pushNodesToRebalance(violator, nodesToRebalance);
		// NODE *violatingTreeRoot = rebalance(nodesToRebalance, violatorParent);
		// if (violatorParent != nullptr)
		// {
		// 	if (violatorParent->key > violatingTreeRoot->key)
		// 	{
		// 		violatorParent->left = violatingTreeRoot;
		// 	}
		// 	else if (violatorParent->key < violatingTreeRoot->key)
		// 	{
		// 		violatorParent->right = violatingTreeRoot;
		// 	}
		// 	else
		// 	{ // this will never happen since duplicates keys simply have their value updated. BUt adding just in case.
		// 		violator = violatorParent;
		// 	}
		// }
		// else
		// {
		// 	this->root = violatingTreeRoot;
		// }
		// }
	}

	//
	// contains:
	// Returns true if the key is in mymap, return false if not.
	// Time complexity: O(logn), where n is total number of nodes in the
	// threaded, self-balancing BST
	//
	bool contains(keyType key)
	{
		NODE *cur = root;
		while (cur != nullptr)
		{
			if (cur->key == key) // if key already exists in map return true
			{
				return true; // return true if key is found
			}
			else if (cur->key > key) // key is smaller than current node's key, go to the left
			{
				cur = cur->left;
			}
			else // key is bigger than current node's key, go to the right
			{
				if (cur->isThreaded)
					cur = nullptr;
				else
					cur = cur->right;
			}
		}
		return false; // whole map has been traversed and key not found
	}

	//
	// get:
	//
	// Returns the value for the given key; if the key is not found, the
	// default value, valueType(), is returned (but not added to mymap).
	// Time complexity: O(logn), where n is total number of nodes in the
	// threaded, self-balancing BST
	//
	valueType get(keyType key)
	{
		NODE *cur = root;
		while (cur != nullptr)
		{
			if (cur->key == key) // if key already exists in map return true
			{
				return cur->value;
			}
			else if (cur->key > key) // key is smaller than current node's key, go to the left
			{
				cur = cur->left;
			}
			else if (cur->key < key) // key is bigger than current node's key, go to the right
			{
				if (cur->isThreaded)
					cur = nullptr;
				else
					cur = cur->right;
			}
		}
		return valueType(); // key not found, return data type
	}

	//
	// operator[]:
	//
	// Returns the value for the given key; if the key is not found,
	// the default value, valueType(), is returned (and the resulting new
	// key/value pair is inserted into the map).
	// Time complexity: O(logn + mlogm), where n is total number of nodes in the
	// threaded, self-balancing BST and m is the number of nodes in the
	// sub-trees that need to be re-balanced.
	// Space complexity: O(1)
	//
	valueType operator[](keyType key)
	{
		NODE *cur = root;
		while (cur != nullptr)
		{
			if (cur->key == key) // if key already exists in map return true
			{
				return cur->value;
			}
			else if (cur->key < key) // key is bigger than current node's key, go to the right
			{
				if (cur->isThreaded)
					cur = nullptr;
				else
					cur = cur->right;
			}
			else if (cur->key > key) // key is smaller than current node's key, go to the left
			{
				cur = cur->left;
			}
		}
		put(key, valueType());
		return valueType();
	}

	//
	// Size:
	//
	// Returns the # of key/value pairs in the mymap, 0 if empty.
	// O(1)
	//
	int Size()
	{
		return size;
	}

	//
	// begin:
	//
	// returns an iterator to the first in order NODE.
	// Time complexity: O(logn), where n is total number of nodes in the
	// threaded, self-balancing BST
	//
	iterator begin()
	{
		NODE *curr = root;
		while (curr->left != nullptr)
		{
			curr = curr->left;
		}
		return iterator(curr);
	}

	//
	// end:
	//
	// returns an iterator to the last in order NODE.
	// this function is given to you.
	//
	// Time Complexity: O(1)
	//
	iterator end()
	{
		return iterator(nullptr);
	}

	//
	// toString:
	//
	// Returns a string of the entire mymap, in order.
	// Format for 8/80, 15/150, 20/200:
	// "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
	// Time complexity: O(n), where n is total number of nodes in the
	// threaded, self-balancing BST
	//
	string toString()
	{
		NODE *curr;
		curr = root;
		stringstream ss("");
		toStringHelper(ss, curr);
		return ss.str();
	}

	void _toVector(NODE *node, vector<pair<keyType, valueType>> &map)
	{
		if (node == nullptr)
			return;
		_toVector(node->left, map);
		map.push_back(make_pair(node->key, node->value));
		if (node->isThreaded)
			return;
		_toVector(node->right, map);
	}

	//
	// toVector:
	//
	// Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
	// {{8, 80}, {15, 150}, {20, 200}}
	// Time complexity: O(n), where n is total number of nodes in the
	// threaded, self-balancing BST
	//
	vector<pair<keyType, valueType>> toVector()
	{
		vector<pair<keyType, valueType>> vecMap;
		NODE *cur = root;
		_toVector(cur, vecMap);
		return vecMap; // TODO: Update this return.
	}

	void _checkBalance(NODE *node, ostream &output)
	{
		if (node == nullptr)
			return;
		output << "key: " << node->key
			   << ", nL: " << node->nL
			   << ", nR: " << node->nR << endl;
		_checkBalance(node->left, output);
		if (node->isThreaded)
			return;
		_checkBalance(node->right, output);
	}

	//
	// checkBalance:
	//
	// Returns a string of mymap that verifies that the tree is properly
	// balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
	// function should return a string in this format (in pre-order):
	// "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
	// Time complexity: O(n), where n is total number of nodes in the
	// threaded, self-balancing BST
	//
	string checkBalance()
	{
		NODE *cur = root;
		stringstream ss;

		_checkBalance(cur, ss);
		return ss.str(); // TODO: Update this return.
	}
};
