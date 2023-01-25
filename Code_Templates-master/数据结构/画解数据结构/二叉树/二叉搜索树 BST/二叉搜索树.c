#include <stdio.h>
#include <malloc.h>

#define bool int
#define true 1
#define false 0

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int val);
int BSTFindMin(struct TreeNode* root);
bool BSTFind(struct TreeNode* root, int val);
struct TreeNode* BSTInsert(struct TreeNode* root, int val);
struct TreeNode* BSTDelete(struct TreeNode* root, int val);
struct TreeNode* BSTConstruct(int *vals, int valSize);

struct TreeNode* createNode(int val) { 
    struct TreeNode* node = (struct TreeNode*) malloc( sizeof(struct TreeNode) );
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}
 
 /* ���� 
 * $(1)$ ```BSTFind```����������ڲ�����```now```Ϊ�����������Ƿ����ֵΪ```val```�����㣻
 * $(2)$ �����ǲ����ܴ���ֵΪ```val```�Ľ��ģ�ֱ�ӷ���```false```��
 * $(3)$ һ��������ֵΪ```val```�Ľ�㣬ֱ�ӷ���```true```��
 * $(4)$ ```val```��ֵ С�� **��������ֵ**��˵��```val```��Ӧ�Ľ�㲻�ڸ���㣬Ҳ�����������ϣ���ݹ鷵���������� **����** �����
 * $(5)$ ```val```��ֵ ���� **��������ֵ**��˵��```val```��Ӧ�Ľ�㲻�ڸ���㣬Ҳ�����������ϣ���ݹ鷵���������� **����** �����
 * */
bool BSTFind(struct TreeNode* root, int val) {    // (1) 
    if(root == NULL) {
        return false;                             // (2) 
    }
    if(root->val == val) {
        return true;                              // (3) 
    } 
    if(val < root->val) {
        return BSTFind(root->left, val);          // (4)
    }else {
        return BSTFind(root->right, val);         // (5)
    }
}


/* ���� 
* $(1)$ ```BSTInsert```�������ڽ�ֵΪ```val```�Ľ����뵽��```root```Ϊ�����������У�
* $(2)$ ����ǿ������򴴽�һ��ֵΪ```val```�Ľ�㲢�ҷ��أ�
* $(3)$ ```val```��ֵ ���� **��������ֵ**������ִ�в��룬ֱ�ӷ��ظ���㣻
* $(4)$ ```val```��ֵ С�� **��������ֵ**����ô����λ��һ���� **������**���ݹ�ִ�в����������Ĺ��̣����ҷ��ز�������Ϊ�µ�**������**��
* $(5)$ ```val```��ֵ ���� **��������ֵ**����ô����λ��һ���� **������**���ݹ�ִ�в����������Ĺ��̣����ҷ��ز�������Ϊ�µ�**������**��
* */
struct TreeNode* BSTInsert(struct TreeNode* root, int val){ // (1)
    if(root == NULL) {                              
        return createNode(val);                             // (2)
    }
    if(val == root->val) {
        return root;                                        // (3)
    }
    if(val < root->val) {                                   // (4)
        root->left = BSTInsert(root->left, val);  
    }else {                                                 // (5)
        root->right = BSTInsert(root->right, val);          
    }
    return root;
}

/* ������С����ֵ 
* $(1)$ ������������ڣ���ݹ�����������Ĳ�����С���ӿڣ�
* $(2)$ ��������������ڣ���ǰ������ֵһ������С�ģ�ֱ�ӷ��ؽӿڣ�
*/
int BSTFindMin(struct TreeNode* root) {
    if(root->left)
        return BSTFindMin(root->left);  // (1)
    return root->val;                   // (2)
}



/*
* $(1)$ ���������Ϊ�գ�������������Ϊ�µ�������
* $(2)$ ���������Ϊ�գ�������������Ϊ�µ�������
* $(3)$ ���򣬵�����������Ϊ�ǿ�ʱ������```BSTFindMin```�������������ҳ���С�Ľ�㣬��Ϊ�µĸ�����������������ɾ����Ӧ�Ľ�㣬ɾ�����̾��ǵݹ����```BSTDelete```�Ĺ��̣�
*/
struct TreeNode* Delete(struct TreeNode* root) {
    struct TreeNode *delNode, *retNode;
    if(root->left == NULL) {          // (1)
        delNode = root, retNode = root->right, free(delNode);
    }else if(root->right == NULL) {   // (2)
        delNode = root, retNode = root->left, free(delNode);
    }else {                           // (3)
        retNode = (struct TreeNode*) malloc (sizeof(struct TreeNode));
        retNode->val = BSTFindMin(root->right);
        retNode->right = BSTDelete(root->right, retNode->val);
        retNode->left = root->left;
    }
    return retNode;
}

/*
* $(1)$ ���Ϊ��������ֱ�ӷ��ؿս�㣻
* $(2)$ �����Ҫɾ���Ľ�㣬��������ĸ���㣬��ֱ�ӵ��ýӿ�```Delete```�����Ļ��������ʵ�֣�
* $(3)$ �����Ҫɾ���Ľ���ֵ С�� **��������ֵ**������Ҫɾ���Ľ��ض����������ϣ��ݹ������������ɾ�������ҽ�����ֵ��Ϊ�µ��������ĸ���㣻
* $(4)$ �����Ҫɾ���Ľ���ֵ ���� **��������ֵ**������Ҫɾ���Ľ��ض����������ϣ��ݹ������������ɾ�������ҽ�����ֵ��Ϊ�µ��������ĸ���㣻
* $(5)$ ��󣬷��ص�ǰ���ĸ���㣻
*/ 
struct TreeNode* BSTDelete(struct TreeNode* root, int val){
    if(NULL == root) {
        return NULL;                                  // (1)
    }
    if(val == root->val) {
        return Delete(root);                          // (2)
    }
    else if(val < root->val) {
        root->left = BSTDelete(root->left, val);      // (3)
    }else if(val > root->val) {
        root->right = BSTDelete(root->right, val);    // (4)
    }
    return root;                                      // (5)
}

struct TreeNode* BSTConstruct(int *vals, int valSize) {
    int i;
    struct TreeNode* root = NULL;
    for(i = 0; i < valSize; ++i) {
        root = BSTInsert(root, vals[i]);
    }
    return root;
}






