/*
 * @Author: Kaizyn
 * @Date: 2021-05-17 21:52:43
 * @LastEditTime: 2021-05-17 22:03:45
 */
#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
  TreeNode *lc, *rc;
};

int tree_depth(TreeNode *rt) {
  if (!rt) return 0;
  return max(tree_depth(rt->lc), tree_depth(rt->rc))+1;
}

signed main() {
  return 0;
}