//
//  main.cpp
//  XOR-min
//
//  Created by Dennis Mo on 12/14/18.
//  Copyright © 2018 Dennis Mo. All rights reserved.
//

#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
using namespace std;
#define ll long long
inline string convert(int a)
{
    return bitset<32>(a).to_string();
}

string query;
int k1,k2;
int a;
int XOR;
string temp;
string output = "";

struct TrieNode{
    TrieNode *left_child;
    TrieNode *right_child;
    bool isEndWord;
    int index;
};

TrieNode *getNode(void){
    TrieNode *pNode = new TrieNode;
    pNode->isEndWord = false;
    pNode->left_child = NULL;
    pNode->right_child = NULL;
    pNode->index = -1;
    
    return pNode;
}

void insert(TrieNode *root, string key, int index){
    if (key.empty() && (root->isEndWord != true)) {
        root->isEndWord = true;
        root->index = index;
        return;
    }
    if (key.back() == '0') {
        if (root->left_child == NULL) {
            root->left_child = getNode();
        }
        key.pop_back();
        insert(root->left_child,key,index);
        return;
    }
    if(key.back() == '1') {
        if (root->right_child == NULL) {
            root->right_child = getNode();
        }
        key.pop_back();
        insert(root->right_child,key,index);
        return;
    }
    return;
}

void search(TrieNode *root, string key){
    if (key.empty()) {
        output += to_string(root->index);
        output.push_back('\n');
        return;
    }
    if(key.back() == '0'){
        if (root->left_child == NULL) {
            key.pop_back();
            search(root->right_child,key);
            return;
        }
        key.pop_back();
        search(root->left_child,key);
        return;
    }
    if (key.back() == '1') {
        if (root->right_child == NULL) {
            key.pop_back();
            search(root->left_child,key);
            return;
        }
        key.pop_back();
        search(root->right_child,key);
        return;
    }
}

int main() {
    cout << "hi" << endl;
    TrieNode *root = getNode();
    cin >> k1;
    cin >> k2;
    for (int i = 0; i < k1; i++) {
        cin >> a;
        temp = convert(a);
        reverse(temp.begin(), temp.end());
        insert(root, temp, i);
    }
    for (int i = 0; i < k2; i++) {
        cin >> a;
        if (i == 0) {
            XOR = a;
        }
        else{
            XOR = int(XOR^a);
        }
        temp = convert(XOR);
        reverse(temp.begin(), temp.end());
        search(root,temp);
    }
    cout << output;
    return 0;
}
