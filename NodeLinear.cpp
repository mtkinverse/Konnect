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
