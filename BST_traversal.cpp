#include "BSTNode.hh"

using namespace std;
void postorder_rec(p_BSTnode node) {
    cout<<"Postorder:"<<endl;
    if(node->left) postorder_rec(node->left);
    if(node->right) postorder_rec(node->right);
    if(node->left == NULL && node->right == NULL)
        printf("L%ld\n", node->getdata());
    else
        printf("%ld\n", node->getdata());
}

void inorder_iter(p_BSTnode root) {
    stack<p_BSTnode> travstk;
    p_BSTnode node=root;
    cout<<"Inorder:"<<endl;
    while(node || travstk.empty() == false) {
        if(node) {
            travstk.push(node);
            node=node->left;
            continue;
        }
        else {
            node=travstk.top();
            travstk.pop();
            cout<<node->getdata()<<",";
            node=node->right;
        }
    }
    cout<<endl;
}

void levelorder(p_BSTnode root) {
    p_BSTnode node = root;
    queue< pair<char,p_BSTnode> > travq;
    pair<char, p_BSTnode> p;

    cout<<"Levelorder:"<<endl;
    while(node->left || node->right || travq.empty() == false) {
        if(travq.empty())   travq.push(make_pair('h',node));
        else {
            p=travq.front();
            node=p.second;
            travq.pop();
            if(node->left)
                travq.push(make_pair('l',node->left));
            if(node->right)
                travq.push(make_pair('r',node->right));
            cout<<p.first<<":"<<node->getdata()<<" , ";
        }
    }
    cout<<endl;
}

void makemirror(p_BSTnode root) {
    p_BSTnode node, tmp;
    stack<p_BSTnode> stk;

    stk.push(root);
    while(stk.empty() == false) {
        node=stk.top();
        stk.pop();
        tmp=node->left;
        node->left=node->right;
        node->right=tmp;
        if(node->left) stk.push(node->left);
        if(node->right)stk.push(node->right);
    }
    levelorder(root);
}

int main() {

    long arr[10] = {300, 600, 150, 450, 500, 50, 700, 200, 75, 100};
    //long arr[4] = {300, 600, 450, 150};
    int height =0;
    p_BSTnode head = new _bstnode;
    _avlnode *avlhead = new _avlnode;
    _avlnode **rootp= &avlhead;
    if(head == NULL) {
        perror("malloc");
    }
    height = buildBST_from_Arr(head, arr, 10);
    printf("height of tree: %d\n", height);

    //postorder_rec(head);
    levelorder(head);
    inorder_iter(head);
    makemirror(head);
    cout<<"Now AVL tree:"<<endl;
    height = buildAVL_from_Arr(rootp, arr, 10);
    printf("height of tree: %d\n", height);

    //postorder_rec(head);
    levelorder(avlhead);
    inorder_iter(avlhead);
    makemirror(avlhead);
    return 0;
}
