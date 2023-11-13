#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\List.cpp"

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
    
};