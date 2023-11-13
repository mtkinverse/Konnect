
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