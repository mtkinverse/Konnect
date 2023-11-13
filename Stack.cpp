#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\NodeLinear.cpp"

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
