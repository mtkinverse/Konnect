#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>

using namespace std;

char blank[30] = "\0";

struct FriendProto{
    char signature[30];
    int id;
};

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
        else if (root->GetValue()->GetId() < data->GetId()) root->right = Insert(root->right,data);
        else if (root->GetValue()->GetId() > data->GetId()) root->left = Insert(root->left,data);
        else return root;

        root->SetHeight(Height(root));

        int left = root->left ? root->left->GetHeight() : 0;
        int right = root->right ? root->right->GetHeight() : 0;

        int balance = left - right;

        if(balance < -1 || balance > 1){
            if(balance < -1 && data->GetId() > root->right->GetValue()->GetId()) root = LeftRotation(root);
            else if(balance < -1 && data->GetId() < root->right->GetValue()->GetId()){
                root->right = RightRotation(root->right);
                root = LeftRotation(root);
            }
            else if( balance > 1 && data->GetId() < root->left->GetValue()->GetId()) root = RightRotation(root);
            else if( balance > 1 && data->GetId() > root->left->GetValue()->GetId()){
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
        else if(root->GetValue()->GetId() < data->GetId()) root->right = Delete(root->right,data);
        else if(root->GetValue()->GetId() > data->GetId()) root->left = Delete(root->left,data);
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

        std::ifstream file("Posts.bin",std::ios::binary);
        
        while(file.peek() != EOF){
            Post temp;
            file.read((char*)&temp,sizeof(temp));

            if(strcmp(temp.GetSignature(), signature) == 0) posts.Insert_Front(temp);
        
        }

        file.close();
        
    }
    
    void AddPost(char* signature,char* text,char* timeStamp,bool type){
        
        Post temp(signature,text,timeStamp,type);
        std::ofstream file("Posts.bin",std::ios::binary | std::ios::app);
        file.write((char*)&temp,sizeof(temp));
        file.close();
        UpdateHistory((const char*)temp.GetSignature());
        posts.Insert_End(temp);

    }
    
    void AddPost(const Post& post){

        std::ofstream file("Posts.bin",std::ios::binary | std::ios::app);
        file.write((char*)&post,sizeof(post));
        file.close();
        posts.Insert_End(post);

    }
    
    void PrintAllPosts(const char* name){

        Node<Post>* temp = posts.GetHead();
        while(temp != nullptr){
            std::cout << "On "<<temp->data.GetTimeStamp() << " " << name << " posted :\n" << temp->data.GetText() <<std :: endl << std :: endl;
            temp = temp->next;
        } 
    
    }
    
    bool isEmpty() const { return posts.GetHead() == nullptr; }

    void GetTime(char* arr){

        std::string time = __TIMESTAMP__;
        
        for(int i=0;i<time.length();i++) arr[i] = time[i];

    }
    
};

class User{
    char name[30],password[30],email[30];
    History history;
    float points;

    public:

    const char* GetName() const { return this->name; }
    const char* GetPassword() const { return this->password; }
    const char* GetEmail() const { return this->email; }
    History& GetHistory() { return this->history; }
    float GetPoints() { return this->points; }

    void SetName(char* name){ strcpy(this->name,name); }
    void SetPassword(char* password){ strcpy(this->password,password); }
    void SetEmail(char* email){ strcpy(this->email,email); }
    void SetPoints(float val){ this->points = val;}

    User(){
        strcpy(name,"\0");
        strcpy(password,"\0");
        strcpy(email,"\0");
        points = 0;
    }

    User(const User& obj){
        strcmp(name,obj.name);
        strcmp(email,obj.email);
        strcmp(password,obj.password);
        this->history = obj.history;
        this->points = obj.points;
    }
    
    User( char * name,char * password,char * email){

        strcpy(this->name,name);
        strcpy(this->password,password);
        strcpy(this->email,email);
        
        this->points = 0;

    }// we have to set a method for getting the ids/tokens (last leaved)

    bool operator == (const User& obj){
        return !strcmp(this->email,obj.email);
    }

    bool operator < ( const User& obj){
        cout << "User operator < called "<< endl;
        return this->email < obj.email;
    }

    friend std::ostream& operator << (std::ostream& temp, User& obj){
        std::cout << "\nName : " << obj.name << "Email : "<< obj.email << "Points : "<< obj.points << std::endl << std::endl;
        return temp;
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

        if(p1 == nullptr || p2 == nullptr) {
            cout << id1 << " " << id2 << " Cannot be connected\n";
            system("pause");
            return;}
        else if(id1 == id2){
            cout << " -- Cannot connect the same user\n";
        }
        
        p1->ConnectNode(p2);
        adjMatrix[p1->GetId()][p2->GetId()] = 1;
        
        p2->ConnectNode(p1);
        adjMatrix[p2->GetId()][p1->GetId()] = 1;

        // cout << "connecting "<<id1<<"and "<<id2<<" "<< p1->GetData()->GetName()<<" "<< p2->GetData()->GetName() << endl;
        // system("pause");
    }

    void PrintAllNodes(){
        NodeT<NodeG<t>*>* temp = AllNodes.GetRoot();
        PrintAllNodes(temp);
    }

    void PrintAllNodes( NodeT<NodeG<t>*>* temp){
        if(temp == nullptr) return;
        
        PrintAllNodes(temp->left);
        // cout << temp->GetValue()->GetData().GetName() << " : " << temp->GetValue()->GetList().Traverse();
        cout << *(temp->GetValue()->GetData());
        cout << "\n id : "<< temp->GetValue()->GetId() << endl;
        cout << endl;
        Node<NodeG<t>*>* p = temp->GetValue()->GetList().GetHead();
        while(p){
            cout << p->data->GetData()->GetName() << " ";
            p = p->next;
        }
        cout << endl;
        PrintAllNodes(temp->right);

    }

    bool IsFriend(int id1,int id2){
        return adjMatrix[id1][id2];
    }

};

bool checkUser(const User& obj,int &n ) {

	User temp;
	ifstream file("UserData.bin", ios::binary );

	while (file.read((char*)&temp, sizeof(temp))) {
		n++;
		if (temp == obj){
			file.close();
			return true;
	    }
	}
	file.close();
	n = 0;
	return false;
}

class Writer {

public:

	Writer(){}

	// static void simulate();

	static bool Login( User& obj, int &n ) {
		
			
				ifstream file("UserData.bin", ios::binary);
				file.seekg((n-1) * sizeof(User));
				User temp;
				file.read((char*)&temp, sizeof(temp));


				if (strcmp((char*)temp.GetPassword(),(char*)obj.GetPassword()) == 0){
					
					obj = User((char*)temp.GetName(),(char*) temp.GetPassword(),(char*) temp.GetEmail());
					
				file.close();

				    return true;	
				}
				else {
					
					cout << "\n >> Incorrect Password !\n"<< endl;
				file.close();
					return false;
				}
			
	}

	static bool SignUp(const User& obj) {


		int num=0;

		if(!checkUser(obj,num)){

			ofstream file("UserData.bin", ios::binary | ios::app);
			file.write((char*)&obj, sizeof(obj));
			file.close();

			return true;

		}
		else {
			cout << "\nUser already exist please try again with different login id ! \n";
			return false;
		}

	}

	static bool deleteUser(const User& obj) {

		bool deleted = false;
		int n = 0;

		if (checkUser(obj, n)) {

			User tempobj;
			int temp = 0;

			ifstream file("UserData.bin", ios::binary);
			file.seekg((n-1) * sizeof(User));
			file.read((char*)&tempobj, sizeof(tempobj));

			if (strcmp((char*)tempobj.GetPassword(),(char*)obj.GetPassword()) == 0);
			else {
				file.close();
				return false;
			}

			fstream newFile("new.bin", ios::binary|ios::out);
			
			file.seekg(0);
			while (file.read((char*)&tempobj, sizeof(User))) {

				if (temp != (n - 1)) {
					newFile.write((char*)&tempobj, sizeof(tempobj));
				}
				else{
					deleted = true;
			}
					temp++;
			}

			file.close();
			newFile.close();

			remove("UserData.bin");
			int val = rename("new.bin", "UserData.bin");
			
		}
			return deleted;

	}

	static bool UpdateUser(const User& obj1, const User& obj2) {

		// if (deleteUser(obj1)) {

		// 	int n = 0;

		// 	fstream file("UserData.bin", ios::binary | ios::app);
		// 	file.write((char*)&obj2, sizeof(obj2));
		// 	file.close();

		// 	return true;
		// }

        int n = 0;
        bool stat = false;

		User tempobj;
        
		ifstream file("UserData.bin", ios::binary);
		fstream newFile("new.bin", ios::binary|ios::out);
		
		file.seekg(0);
		while (file.read((char*)&tempobj, sizeof(User))) {

			if (strcmp(obj1.GetEmail(),tempobj.GetEmail()) != 0) {
				newFile.write((char*)&tempobj, sizeof(tempobj));
			}
			else{
                stat = true;

                newFile.write((char*)&obj2,sizeof(obj2));
		    }
		}

		file.close();
		newFile.close();
        
		remove("UserData.bin");
		int val = rename("new.bin", "UserData.bin");
		

		return stat;

	}
};

class Simulate{

    Graph<User*> graph;


    void PrintHeader(){
        system("cls");
        
        cout << " |/  [ ] |\\ | |\\ | |``|`` ``|``                                                      https://github.com/mtkinverse/Konnect"<< endl;
        cout << " |\\  [ ] | \\| | \\| |_ |_|   |                                                                                             "<< endl;
        cout << " Your conncetions are valueable\n";

        cout << endl << endl;
    }

    void InitGraph(){
        ifstream file("UserData.bin",std::ios::binary);
        User temp;

        while(file.read((char*)&temp, sizeof(temp)))
        {   
            graph.AddNode(new User((char*)temp.GetName(),(char*)temp.GetPassword(),(char*)temp.GetEmail()));
        }
        file.close();

        ifstream file2("Friends.bin",ios::binary);
        struct FriendProto tempF;
        int n;

        while(file2.read((char*)&tempF,sizeof(tempF))){
            n=0;
            temp.SetEmail(tempF.signature);
            checkUser(temp,n);
            graph.ConnectNodes(n-1,tempF.id);
        }
        
        file2.close();
        
    }

    void SearchMember(User& user){
        PrintHeader();
        User tempUser;
        char temp[30];

        cout << "==>> Enter the email of the user you want to search : ";
        fflush(stdin);
        fgets(blank,30,stdin);
        fgets(temp,30,stdin);

        tempUser.SetEmail(temp);
        
        int n = 0;
        while(!checkUser(tempUser,n)){
        n = 0;
		cout << "\t\t****The user name does not found !****\n\nPlease provide the user name / Login ID again\n Press any Key to continue or enter E to exit !\n";

		char ch;
		fflush(stdin);
		cin >> ch;

		if ( ch == 'E') return;

		fflush(stdin);
		fflush(stdin);
		fgets(blank, 30, stdin);

		cout << "Enter a unique user name : ";

		fgets(temp, 30, stdin);
		tempUser.SetEmail(temp);
		fflush(stdin);
	
	    }

        ifstream file("UserData.bin",ios :: binary);
        file.seekg((n-1) * sizeof(User));
        file.read((char*)&tempUser,sizeof(tempUser));

        cout << " -->> User Found !\n" << tempUser << endl;
        
        int id1 = n - 1;
        n=0;
        checkUser(user,n); // getting the id of the user
       
        if(graph.IsFriend(n-1,id1))
            cout << "\nYou are already friends !\n";        
        else{
            cout << "DO you want to be friends ? Enter 1 for yes or other for No\n\n";
            int num;
            // cin >> num;
            num = getc(stdin);

            if(num == '1'){
                MakeFriend(n-1,id1);
                cout << " -- You guys are now friends !\n";
            }

        }

    }
    
    

    public:
    
    Simulate(){
        InitGraph();
    }
    
    void AskUser(){
        while(1){

            PrintHeader();
            cout << " ==> Select the options as per your desire\n\n> 1 - Login\n> 2 - Singup\n> 3 - exit\n\nEnter your choice : ";
            int n;
            cin >> n;

            switch (n)
            {
                case 1: MakeItLogin();
                    break;

                case 2: MakeItSignup();
                    break;
                case 3: exit(0);
                    break;

                default: cout << "\nKindly be precised while selecting the options !\n\n";
                         system("pause");
            }
        }

    }

    private:

    void MakeItLogin() {

	int n = 0;
	User temp;
	char temparr[2][30];

	system("cls");
PrintHeader();


	cout << "\n -->> Welcome to the login panel\n\n Enter your login Identity : ";

	fflush(stdin);
	fflush(stdin);
	fgets(blank, 30, stdin);
	fgets(temparr[0], 30, stdin);
	temp.SetEmail(temparr[0]);
	fflush(stdin);

	while(!checkUser(temp,n)){
	
		cout << "\t\t****The user name does not found !****\n\nPlease provide the user name / Login ID again\n Press any Key to continue or enter E to exit !\n";

		char ch;
		fflush(stdin);
		cin >> ch;

		if ( ch == 'E') return;

		fflush(stdin);
		fflush(stdin);
		fgets(blank, 30, stdin);

		cout << "Enter a unique user name : ";

		fgets(temparr[0], 30, stdin);
		temp.SetEmail(temparr[0]);
		fflush(stdin);
	
	}

	cout << " Enter Your password : ";
	
	fflush(stdin);
	fgets(temparr[1], 30, stdin);
	fflush(stdin);
	temp.SetPassword(temparr[1]);

	int count = 3;
	
	while (!Writer::Login(temp, n) && count>0) {

		cout << "\n\t**** Incorrect password ! ****\n\nPress any key to continue, or press 'E' to exit\n";

		if (getc(stdin) == 'E')
			exit(0);

		cout << "Enter the password again ("<<count<<"): ";

		fflush(stdin);
		fgets(blank, 30, stdin);
		fgets(temparr[1], 30, stdin);
		fflush(stdin);
		temp.SetPassword(temparr[1]);

		count--;

	}

	if (count <= 0) { 

		cout << "\n\nYou failed to login successfully !\n";
		return;

	}
	else cout << "\n\n\t\t *** Login successful ! ***\n\n\t";

	system("pause");
    
    if(n == 1) return AdminPortal();
    // graph.AddNode(new User((char*)temp.GetName(),(char*)temp.GetPassword(),(char*)temp.GetEmail()));
    else return ShowMenu(temp);

}
    

void ShowMenu(User& user){

    user.GetHistory().UpdateHistory(user.GetEmail());

    while(1){
        
        PrintHeader();

        cout << " ==>> Welcome " << user.GetName() << " - The menu of Konnect offers you following functionalities. Please select the options very precisely\n\n > 1 - Check your feed\n > 2 - View your posts\n > 3 - Search a member\n > 4- Create post\n > 5 - Update Accoount\n > 6 - Delete Account\n > 7 - exit\n\nEnter your choice : ";

        int choice;
        cin >> choice;
        
        switch (choice)
        {
        case 1:
            ShowFeed(user);
        break;
        case 2:
            ShowProfile(user);
        break;
        case 3:
            SearchMember(user);
        break;
        case 4:
            CreatePost(user);
        break;
        case 5:
            UpdateAccount(user);
        break;
        case 6:

            if(deleteUser(user)){
                cout << "\n\t*** User Deleted ***\n\n -->> We value the time and support you provide us. Thanks for using this server\n\n";
                system("pause");
                Simulate();
                return;
            }else cout << "an error occured while deleting\n";
            
        break;
        case 7: return; break;
        default:
            cout << "Kindly be precised !\n";
            system("pause");
            break;
        }

        system("pause");
        system("pause");

    }

}

    void CreatePost(User& user){

        PrintHeader();
        Post temp;
        temp.SetSignature((char*)user.GetEmail());
        user.GetHistory().GetTime((char*)temp.GetTimeStamp());

        cout << " > Enter the text you want to post : ";
        cin.clear();
        fgets(blank,30,stdin);
        fgets((char*)temp.GetText(),500,stdin);

        user.GetHistory().AddPost(temp);
        user.SetPoints(user.GetPoints()+10);
        
    }

    void MakeFriend(int id1,int id2){
        graph.ConnectNodes(id1,id2);
        
        struct FriendProto temp;
        NodeG<User*>* node = graph.Find(id1);
        strcpy(temp.signature ,node->GetData()->GetEmail());
        temp.id = id2;

        ofstream file("Friends.bin",ios :: binary|ios::app);
        file.write((char*)&temp,sizeof(temp));
        file.close();  
        
    }

void ShowFeed(User& user){
    PrintHeader();

    int n = 0;
    checkUser(user,n);

    Post post;
    NodeG<User*>* ng = graph.Find(--n);    
    Node<NodeG<User*>*> *temp, *head = ng->GetList().GetHead();
    
    if(temp == nullptr) {user.GetHistory().PrintAllPosts(user.GetEmail()); system("pause"); return;}

    ifstream file("Posts.bin",ios::binary);
    while(file.read((char*)&post,sizeof(post))){
        

        temp = head;
        
        while(temp){
            if(strcmp(temp->data->GetData()->GetEmail(),post.GetSignature()) == 0 || strcmp(user.GetEmail(),post.GetSignature()) == 0){
                cout << "==\n" << post.GetSignature() << post.GetTimeStamp() << endl << post.GetText() << "==\n";
                break;
            }
            temp = temp->next;
        }
    }
    
    file.close();

    system("pause");

}

void ShowProfile(User& user){
    PrintHeader();

    cout << " - Showing the profile of the user\n";
    cout << user << endl;
    
    user.GetHistory().PrintAllPosts(user.GetName());
    
}

void MakeItSignup() {

	int num= 0;

	system("cls");
PrintHeader();

	User newUser;

	char temps[3][30];

	cout << "\n\n\t\t *** Welcome to the Signup portal !\n\n -> Please provide us information with which you want to signup\n -> keep remember this information to login anytime on Konnect\n\n - Name : ";

	fflush(stdin);
    fgets(blank, 30, stdin);
    fgets(temps[0], 30, stdin);
	cout << " - Login ID : ";
    fgets(temps[1], 30, stdin);
	newUser.SetEmail(temps[1]);
	fflush(stdin);

	while (checkUser(newUser,num)) {

		cout << "The user already exist kindly enter a different login ID\nPress any key to continue or press E to exit ";
        char ch = getc(stdin);
		if (ch == 'E') return;

		fflush(stdin);
		fgets(blank, 30, stdin);
        cout << "Enter a unique user name : ";
		fgets(temps[1], 30, stdin);
		newUser.SetEmail(temps[1]);
		fflush(stdin);

	}

	cout << " - Password : ";
	fflush(stdin);
    fgets(temps[2], 30, stdin);
	fflush(stdin);
	
	newUser = User((char*)temps[0],(char*) temps[2],(char*) temps[1]);

	if (Writer::SignUp(newUser)) {
		cout << "\n\n\t\t *** Signup successful **\n\n";
		system("pause");
        
	}
	else cout << "An error occured while signing up !\n\n";

    graph.AddNode(new User((char*)newUser.GetName(),(char*)newUser.GetPassword(),(char*)newUser.GetEmail()));
    
    return ShowMenu(newUser);

}


void UpdateAccount(const User& obj) {

	User temp = User((char*)obj.GetName(),(char*)obj.GetPassword(),(char*)obj.GetEmail());

    char temparr[30];
    bool EmailUpdated = false;

	system("cls");
PrintHeader();
	cout << "\n --)) What do you want to update \n\n 1 = Name\n 2 = LoginID\n 3 = Password\n\nEnter your choice : ";

	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1 : 
		fgets(blank,30, stdin);
		cout << "Enter the new name : ";
		fgets(temparr,30, stdin);
		temp.SetName((char*)temparr);
	break;

	case 2:

		fgets(blank, 30, stdin);
		cout << "Enter the new Login ID : ";
		fgets(temparr, 30, stdin);
        EmailUpdated = true;
		temp.SetEmail((char*)temparr);

	break;

	case 3 :

		fgets(blank, 30, stdin);
		cout << "Enter the new Password : ";
		fgets(temparr, 30, stdin);
		temp.SetPassword((char*)temparr);

	break;

	default:cout << "Not a valid Entry !\n";
		system("pause");
		break;
	}

	if (Writer::UpdateUser(obj, temp)){

        struct FriendProto frnd;

        if(EmailUpdated){

            ifstream file1("Friends.bin",ios::binary);
            ofstream file2("temp.bin",ios::binary);

            while(file1.read((char*)&frnd,sizeof(frnd))){
                if(strcmp(obj.GetEmail(),frnd.signature) == 0) strcpy(frnd.signature,temp.GetEmail());
                file2.write((char*)&frnd,sizeof(frnd));
            }

            
            file2.close();
            file1.close();

            remove("Friends.bin");
            int val = rename("temp.bin","Friends.bin");

            Post post;
            
            ifstream fileP("Posts.bin",ios::binary);
            ofstream fileP2("post.bin",ios :: binary);

            while(fileP.read((char*)&post,sizeof(post))){
                if(strcmp(post.GetSignature(),obj.GetEmail()) == 0) strcpy((char*)post.GetSignature(),temp.GetEmail());
                fileP2.write((char*)&post,sizeof(post));
            }
            
            fileP2.close();
            fileP.close();

            remove("Posts.bin");
            val = rename("post.bin","Posts.bin");

        }
        
        cout << "\n\n\t\t ****** User Updated Successfully ****** \n\n\n -->> Kindly reload the account to observe the changes ! \n";
        
    }
	else cout << "\n -- An error occured ! \n";
	system("pause");
}

bool deleteUser(const User& obj) {

		bool deleted = false;
		int n = 0;

		if (checkUser(obj, n)) {

			User tempobj;
			int temp = 0;

			ifstream file("UserData.bin", ios::binary);
			file.seekg((n-1) * sizeof(User));
			file.read((char*)&tempobj, sizeof(tempobj));

			fstream newFile("new.bin", ios::binary|ios::out);
			
			file.seekg(0);
			while (file.read((char*)&tempobj, sizeof(User))) {

				if (strcmp(tempobj.GetEmail(),obj.GetEmail()) != 0) {
					newFile.write((char*)&tempobj, sizeof(tempobj));
				}
				else{
					deleted = true;
			}
					temp++;
			}

			file.close();
			newFile.close();

			remove("UserData.bin");
			int val = rename("new.bin", "UserData.bin");
            
            struct FriendProto tempFrnd;
            ifstream frnd("Friends.bin",ios::binary);
            ofstream frnd2("new.bin",ios::binary);

            while(frnd.read((char*)&tempFrnd,sizeof(tempFrnd))){
                if(tempFrnd.id >= n) tempFrnd.id--;
                if(strcmp(tempFrnd.signature,obj.GetEmail()) != 0 && tempFrnd.id != (n - 1)) frnd2.write((char*)&tempFrnd,sizeof(tempFrnd));
            }

            frnd2.close();
            frnd.close();

            remove("Friends.bin");
            val = rename("new.bin","Friends.bin");

            Post tempP;
            ifstream post("Posts.bin",ios::binary);
            ofstream tempPost("TempP.bin",ios::binary);

            while(post.read((char*)&tempP,sizeof(tempP))){
                if(strcmp(tempP.GetSignature(),obj.GetEmail()) != 0) tempPost.write((char*)&tempP,sizeof(tempP));
            }
            
            tempPost.close();
            post.close();
			
            remove("Posts.bin");
            val = rename("TempP.bin","Posts.bin");

		}

			return deleted;

	}

void AdminPortal(){
        int opt,n=0;
        char email[30],new_Name[30],new_Pass[30],new_Email[30];

        while(opt!=5){
            
            PrintHeader();
            
            cout << "Admin access\n\n";
            cout<< "1 Update a user\n";
            cout<< "2 delete a user\n";
            cout<< "3 Show all users\n";
            cout<< "4 View post by a user\n";
            cout<< "5 exit\n";
            cin >> opt;
            if(opt==5) return;
            

            while(opt!=1 && opt!= 2 && opt!=3 && opt!= 4 && opt!= 5){
            cout << "Choose a valid option\n\n";
            cout<< "1 Update a user\n";
            cout<< "2 delete a user\n";
            cout<< "3 Show all users\n";
            cout<< "4 View post by a user\n";
            cout<< "5 exit\n";
            cin >> opt;
            if(opt==5) return;
            }
            if(opt==1){
                cout << "Enter the email of the user you want to update: ";
                fflush(stdin);
                fflush(stdin);
                fgets(blank,30,stdin);
                fgets(email,30,stdin);
                User temp;
                temp.SetEmail(email);
                if(checkUser(temp,n)){
                    ifstream file("UserData.bin", ios::binary);
                    file.seekg((n-1) * sizeof(User));
			        file.read((char*)&temp, sizeof(User));
                    UpdateAccount(temp);
                }
                else{
                    cout << "User not found\n";
                }
            }
            else if(opt==2){

                cout << "Enter the email of the user you want to delete: ";
                fflush(stdin);
                fflush(stdin);
                fgets(blank,30,stdin);
                fgets(email,30,stdin);
                
                User temp;
                temp.SetEmail(email);

                if(checkUser(temp,n)){

                    ifstream file("UserData.bin",ios::binary);
                    
                    file.seekg((n-1)*sizeof(User));
                    file.read((char*)&temp,sizeof(temp));
                    
                    file.close();
                    if(deleteUser(temp)){
                        
                        cout << "\n User deleted successfully\npress any key to return\n";
                        // if(fgetc(stdin)) return;

                    }
                    else{
                        cout << "Error try again\n";
                    }
                }
                else{
                    cout << "User not found\n";
                }

            }
            else if(opt==3){

                cout << endl;
                ifstream file("UserData.bin", ios::binary);
                User temp;
                while (file.read((char*)&temp, sizeof(User))) {
                    cout << "Name: "<< temp.GetName();
                    cout << "Email: "<< temp.GetEmail();
                    cout << endl;
                }
                file.close();

            }
            else if(opt==4){

                cout << "Enter the ID of the user: ";
                fflush(stdin);
                fflush(stdin);
                fgets(blank,30,stdin);
                fgets(email,30,stdin);
                User temp;
                temp.SetEmail(email);
                if(checkUser(temp,n)){
                    
                    temp.GetHistory().UpdateHistory(temp.GetEmail());
                    temp.GetHistory().PrintAllPosts(temp.GetEmail());

                }
                else{
                    cout << "Error try again\n";
                }
            }
            else{
                    cout << "User not found\n";
            }

            system("pause");
        }
    }

};

int main(){

    Simulate s;
    s.AskUser();

    return 0;
    
}
