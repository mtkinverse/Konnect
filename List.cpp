#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\NodeLinear.cpp"

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
        std :: cout << "Inserted\n";
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