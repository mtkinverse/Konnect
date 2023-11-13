#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\NodeTree.cpp"

template <class t>
class AVL{
    NodeT<t>* root;
    public:
    AVL(){
        root = nullptr;
    }
    
    NodeT<t>* Search(t data){
        return Search(root,data);
    }

    NodeT<t>* Search(NodeT<t>* root, t data){
        if(root == nullptr) return root;
        if(root->data < data) return Search(root->right,data);
        else if(root->data > data) return Search(root->left,data);
        else return root;
    }
     
    void Insert(t data){
        root = Insert(root,data);
    }
    
    NodeT<t>* Insert(NodeT<t>* root,t data){
        if(root == nullptr) return new NodeT<t>(data);
        else if (root->GetValue() < data) root->right = Insert(root->right,data);
        else if (root->GetValue() > data) root->left = Insert(root->left,data);
        else return root;

        root->SetHeight(Height(root));

        int left = root->left ? root->left->GetHeight() : 0;
        int right = root->right ? root->right->GetHeight() : 0;

        int balance = left - right;

        if(balance < -1 || balance > 1){
            if(balance < -1 && data > root->right->GetValue()) root = LeftRotation(root);
            else if(balance < -1 && data < root->right->GetValue()){
                root->right = RightRotation(root->right);
                root = LeftRotation(root);
            }
            else if( balance > 1 && data < root->left->GetValue()) root = RightRotation(root);
            else if( balance > 1 && data > root->left->GetValue()){
                root->left = LeftRotation(root->left);
                root = RightRotation(root);
            }
            root->SetHeight(Height(root));
        }
        
        return root;

    }

    void Delete(t data){
        root = Delete(root,data);
    }

    NodeT<t>* Delete(NodeT<t>* root,t data){
        if(root == nullptr) return nullptr;
        else if(root->GetValue() < data) root->right = Delete(root->right,data);
        else if(root->GetValue() > data) root->left = Delete(root->left,data);
        else{
            NodeT<t>* temp;
            if(root->left != nullptr && root->right != nullptr){
                temp = root->left;
                while(temp->right != nullptr) temp = temp->right;
                root->SetValue(temp->GetValue());
                root->left = Delete(root->left,temp->GetValue());
            }
            else{
                temp = root->left ? root->left : root->right;
                if(temp == nullptr) {
                    delete root;
                    return nullptr;
                }
                else{
                    NodeT<t>* p = root;
                    p->left = p->right = nullptr;
                    delete p;
                    root = temp;
                }
            }
        }

        root->SetHeight(Height(root));

        int balance = GetBalanceFactor(root);

        if(balance < -1 || balance > 1){
            if(balance < -1 && GetBalanceFactor(root->right) <= 0) root = LeftRotation(root);
            else if(balance < -1 && GetBalanceFactor(root->right) > 0) {
                root->right = RightRotation(root->right);
                root = LeftRotation(root);
            }
            else if(balance > 1 && GetBalanceFactor(root->left) >= 0) root = RightRotation(root);
            else if(balance > 1 && GetBalanceFactor(root->left) < 0) {
                root->left = LeftRotation(root->left);
                root = RightRotation(root);
            }
            
            root->SetHeight(Height(root));
        }

        return root;
        
    }

    int GetBalanceFactor(NodeT<t>* root){
        int left = root->left ? root->left->GetHeight() : 0;
        int right = root->right ? root->right->GetHeight() : 0;
        return left - right;
    }
    
    NodeT<t>* LeftRotation(NodeT<t>* root){
        
        NodeT<t>* RightSubTree = root->right  ,   * BrokeOne = RightSubTree->left;
        RightSubTree->left = root;
        root->right = BrokeOne;

        return RightSubTree;

    }

    NodeT<t>* RightRotation(NodeT<t>* root){

        NodeT<t>* LeftTree = root->left   ,   *BrokeOne = LeftTree->right;
        LeftTree->right = root;
        root->left = BrokeOne;

        return LeftTree;

    }
    
    int GetHeight(){
        return Height(root);
    }

    int Height(NodeT<t>* root){

        if(root == nullptr) return 0;
        int left = Height(root->left),right = Height(root->right);
        int max = left > right ? left : right;

        root->SetHeight(max + 1);

        return max + 1;

    }

    void Inorder(){
        Inorder(root);
    }

    void Inorder(NodeT<t>* root){

        if(root == nullptr) return;
        Inorder(root->left);
        std::cout << root->GetValue() << " ";
        Inorder(root->right);
        
    }

    t GetStart() const { return root->GetValue(); }

};