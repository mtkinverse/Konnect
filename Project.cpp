#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>

using namespace std;

template <class t>

class Node{
    
    public:

    t data;
    Node<t> *next;
    
    Node(){
        next = nullptr;
    }
    
    Node(t data){
        this->data = data;
        next = nullptr;
    }

    void SetValue(t data){ this->data = data; }

    ~Node(){
        next = nullptr;
    }
    
};

template <class t>
class Stack{
    Node<t>* top;
    public:
    
    Stack(){ top == nullptr; }
    
    void Push(t& data){

        Node<t>* temp = new Node<t>(data);
        temp->next = top;
        top = temp;
        
    }

    t Pop(){
        
        if(top == nullptr) return -1;

        Node<t>* temp = top->next;
        top->next = nullptr;
        t val = top->data;
        delete top;
        top = temp;

        return val;

    }

    t Peek(){
        if(top != nullptr) return top->data;
        else return -1;
    }

    void Traverse() const{
        
        Node<t>* temp = top;
        while(temp != nullptr){
            cout << temp->data << " ";
            temp = temp->next;
        }
        
    }
    
};

template <class t>
class List{
    
    Node<t> *head,*tail;

    public:

    List(){ head = tail = nullptr; }

    ~List(){
        Node<t>* temp = head;
        while(temp != nullptr){
            head = head->next;
            temp->next = nullptr;
            delete temp;
            temp = head;
        }
        head = tail = nullptr;
    }
    
    void Insert_End(t data){
        if(tail == nullptr){
            head = tail = new Node<t>(data);
        }
        else{
            tail->next = new Node<t>(data);
            tail = tail->next;
        }
    }

    void Insert_Front(t data){
        Node<t>* temp = new Node<t>(data);
        temp->next = head;
        head = temp;
    }
    
    void Delete_End(){
        if(tail != nullptr){

            Node<t>* temp = head,*prev;
            while(temp->next != nullptr){
                prev = temp;
                temp = temp->next;
            }
            
            
            if(head == tail) head = tail = nullptr;
            else{ 
                tail = nullptr;
                tail = prev;
                tail->next = nullptr;
            }
            delete temp;

        }
    }

    void Delete_Front(){
        if(head != nullptr){
            Node<t>* temp = head->next;
            head->next = nullptr;
            delete head;
            head = temp;
        }
    }
    
    void Delete_At(int pos){

        if(pos < 1 || head == nullptr) return;
        if(pos == 1) return Delete_Front();
        
        Node<t>* temp = head;
        int i;
        for(i=1; i < pos-1 && temp->next != nullptr ; i++) temp = temp->next;

        if(i == pos - 1 && temp != nullptr && temp->next != nullptr){
            Node<t>* p = temp->next;
            temp->next = p->next;
            p->next = nullptr;
            delete p;
        }
        
    }

    void Delete_Data(t& data){

        if(head->data == data) return Delete_Front();
        else if(tail->data == data) return Delete_End();
        else{
            Node<t>* temp = head;
            while(temp != nullptr && temp->next != nullptr && !temp->next->data == data) temp = temp->next;

            Node<t>* p = temp->next;
            temp->next = p->next;
            p->next = nullptr;
            
            delete p;
        }

    }

    Node<t>* GetHead() const { return head; }

    void Traverse() const {
        Node<t>* temp = head;
        while(temp != nullptr){
            std :: cout << temp->data << " ";
            temp = temp->next;
        }
    }

};


template <class t>
class NodeT{
    t data;
    int Height;
public:
    NodeT<t>* left,* right;
    NodeT(t data){
        this->data = data;
        Height = 1;
        left = right = nullptr;
    }
    
    void SetValue(t data){
        this->data = data;
    }
    t GetValue() const { return this->data; }

    void SetHeight(int height){ this->Height = height; }
    int GetHeight() const { return Height; }
    
};


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

    NodeT<t>* GetRoot(){ return root; }

};

class User{

    char name[30],password[30],email[30];
    int id;
    float points;

    public:

    const char* GetName() const { return this->name; }
    const char* GetPassword() const { return this->password; }
    const char* GetEmail() const { return this->email; }

    void SetName(char* name){ strcpy(this->name,name); }
    void SetPassword(char* password){ strcpy(this->password,password); }
    void SetEmail(char* email){ strcpy(this->email,email); }

    User(){
        strcpy(name,"\0");
        strcpy(password,"\0");
        strcpy(email,"\0");
        id = 0;
        points = 0;
    }
    
    User( char * name,char * password,char * email){

        strcpy(this->name,name);
        strcpy(this->password,password);
        strcpy(this->email,email);
        
        this->points = 0;

    }// we have to set a method for getting the ids/tokens (last leaved)

    bool operator == (const User& obj){
        return (this->id == obj.id || this->email == obj.email);
    }

    bool operator < ( const User& obj){
        return this->id < obj.id;
    }

    friend std::ostream& operator << (std::ostream& temp, User& obj){
        std::cout << "User id : " << obj.id << "\nName : " << obj.name << "\nEmail : "<< obj.email << "\nPoints : "<< obj.points << std::endl << std::endl;
        return temp;
    }

    
    
};

class Post{

    char signature[30],text[500],TimeStamp[30];
    bool type;
// Here type 0 post would be a major post while the type 1 post will be the reaction to the type 1 post
    public:

    Post(){
        strcpy(signature,"\0");
        strcpy(text,"\0");
        strcpy(TimeStamp,"\0");
    }
    Post(char* sig,char* text,char* TimeStamp,bool type){

        strcpy(this->text,text);
        strcpy(this->signature,sig);
        strcpy(this->TimeStamp,TimeStamp);
        this->type = type;
        
    }
    
    const char* GetSignature() const { return signature; }
    const char* GetText() const { return this->text; }
    const char* GetTimeStamp() const { return this->TimeStamp; }
    
    void SetSignature(char val[]){ strcpy(this->signature , val); }
    void SetText(char val[]){ strcpy(this->text , val); }
    void SetTimeStamp(char val[]){ strcpy(this->TimeStamp , val); }
    
};

class History{

    List<Post> posts;
    public:
    History(){}

    void UpdateHistory(const char* signature){

        std::ifstream file("Posts.txt",std::ios::binary);
        
        while(file.peek() != EOF){
            Post temp;
            file.read((char*)&temp,sizeof(temp));

            if(strcmp(temp.GetSignature(), signature) == 0) posts.Insert_Front(temp);
        
        }

        file.close();
        
    }
    
    void AddPost(char* signature,char* text,char* timeStamp,bool type){
        
        Post temp(signature,text,timeStamp,type);
        std::ofstream file("Posts.txt",std::ios::binary | std::ios::app);
        file.write((char*)&temp,sizeof(temp));
        file.close();

    }
    
    void AddPost(const Post& post){

        std::ofstream file("Posts.txt",std::ios::binary | std::ios::app);
        file.write((char*)&post,sizeof(post));
        file.close();
        UpdateHistory((const char*)post.GetSignature());

    }
    
    void PrintAllPosts(std::string name){

        Node<Post>* temp = posts.GetHead();
        while(temp != nullptr){
            std::cout << "On "<<temp->data.GetTimeStamp() << " " << name << " posted :\n" << temp->data.GetText() <<std :: endl << std :: endl;
            temp = temp->next;
        } 
    
    }
    
    bool isEmpty() const { return posts.GetHead() == nullptr; }

    void GetTime(char arr[]){

        std::string time = __TIMESTAMP__;
        
        for(int i=0;i<time.length() - 1;i++) arr[i] = time[i];

    }
    
};


template <class t>
class NodeG{
    t data;
    int id;
    List<NodeG<t>*> AdjList;
public:
    NodeG(){ id = 0; AdjList = nullptr; }    
    NodeG(t data,int id){
        this->data = data;
        this->id = id;
    }
    
    t& GetData() { return data; }
    int GetId() const { return id; }
    List<NodeG<t>*>& GetList() { return AdjList; }

    void SetId(int id){ this->id = id; }

    void ConnectNode(NodeG<t>* n){
        AdjList.Insert_End(n);
    }

    void DisConnectNode(NodeG<t>* n){
        AdjList.Delete_Data(n);
    }

    bool operator == (const NodeG& obj){
        return (this->id == id || this->data == data) ;
    }

    bool operator < (const NodeG& obj){
        return this->data < obj.data;
    }

    friend std::ostream& operator<< (std::ostream& temp, const NodeG& obj){
        cout << obj.data << " ";
        return temp;
    }
    
};

template <class t>
class Graph{
    
    AVL<NodeG<t>*> AllNodes;
    bool ** adjMatrix;
    int NumNodes;

public:

    Graph(){
        adjMatrix = nullptr;
        NumNodes = 0;
    }

    void IncreaseMatrix(){

        bool ** temp = new bool*[NumNodes];
        for(int i=0;i<NumNodes;i++){
            temp[i] = new bool[NumNodes];
            if(i < NumNodes - 1){
                for(int j = 0; j<NumNodes - 1 ; j++)temp[i][j] = adjMatrix[i][j];
                temp[i][NumNodes - 1] = 0;
            }
            else for(int j = 0; j<NumNodes; j++)temp[i][j] = 0;
        }

        for(int i=0;i<NumNodes - 1;i++) delete[] adjMatrix[i];
        delete[] adjMatrix;
        adjMatrix = temp;
        
    }

    void AddNode(t data){

        NodeG<t>* temp = new NodeG<t>(data,NumNodes);
        NumNodes++;

        IncreaseMatrix();
        AllNodes.Insert(temp);
    
    }

    void ConnectNodes(NodeG<t>* p1,NodeG<t>* p2){

        p1->AdjList->Insert_End(p2);
        adjMatrix[p1->id][p2->id] = 1;
        
        p2->AdjList->Insert_End(p1);
        adjMatrix[p2->id][p1->id] = 1;

    }

    NodeG<t>* Find(int id){
        return Find(AllNodes.GetRoot(),id);
    }

    NodeG<t>* Find(NodeT<NodeG<t>*>* root,int id){
        if(root == nullptr) return nullptr;
        if(root->GetValue()->GetId() < id) return Find(root->right,id);
        else if(root->GetValue()->GetId() > id) return Find(root->left,id);
        else return root->GetValue();
    }

    void ConnectNodes(int id1,int id2){
        
        NodeG<t> *p1 = Find(id1) , *p2 = Find(id2);

        if(p1 == nullptr || p2 == nullptr) {return};
        
        p1->ConnectNode(p2);
        adjMatrix[p1->GetId()][p2->GetId()] = 1;
        
        p2->ConnectNode(p1);
        adjMatrix[p2->GetId()][p1->GetId()] = 1;

    }

    void PrintAllNodes(){
        NodeT<NodeG<t>*>* temp = AllNodes.GetRoot();
        PrintAllNodes(temp);
    }

    void PrintAllNodes( NodeT<NodeG<t>*>* temp){
        if(temp == nullptr) return;
        
        PrintAllNodes(temp->left);
        // cout << temp->GetValue()->GetData().GetName() << " : " << temp->GetValue()->GetList().Traverse();
        cout << temp->GetValue()->GetData();
        cout << endl;
        Node<NodeG<t>*>* p = temp->GetValue()->GetList().GetHead();
        while(p){
            cout << p->data->GetData().GetName() << " ";
            p = p->next;
        }
        cout << endl;
        PrintAllNodes(temp->right);

    }

};

int main(){

    Graph<User> g;
    char name[] = "Muhammad Taha Khan", email[] = "mtkinverse@gmail.com" , password[] = "mtkinverse";
    g.AddNode(User(name,password,email));

    strcpy(name,"Rao Abdul");
    strcpy(password,"raopass");
    strcpy(email,"raoMail@gmail.com");

    g.AddNode(User(name,password,email));

    strcpy(name,"Hamdan Vohra");
    strcpy(password,"HediPass");
    strcpy(email,"VohraMail@gmail.com");
    g.AddNode(User(name,password,email));

    g.ConnectNodes(0,1);
    g.ConnectNodes(0,2);
    
    g.PrintAllNodes();
    
    return 0;
    
}

