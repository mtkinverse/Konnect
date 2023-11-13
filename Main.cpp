#include<iostream>
using namespace std;

#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\List.cpp"
#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\AVL.cpp"

int main(){

    // List<int> list;

    // list.Insert_End(1);    
    // list.Insert_End(3);    
    // list.Insert_End(5);    
    // list.Insert_End(7);
    // list.Traverse();

    // int data = 3;
    // list.Delete_Data(data);
    // list.Traverse();

    // data = 7;    
    // list.Delete_Data(data);
    // list.Traverse();    

    // data = 1;    
    // list.Delete_Data(data);
    // list.Traverse();    
    int n;
    cin >> n;

    AVL<int> avl;
    int *arr = new int[n];

    for(int i=0;i<n;i++){
        int value;
        cin >> value;
        arr[i] = value;
        avl.Insert(value);
        cout << "The current root is : " << avl.GetStart() << endl;
        avl.Inorder();
        cout << endl;
    }

    for(int i=0;i<n;i++){
        avl.Delete(arr[i]);
        cout << "The current "<<i<<"th root is : " << avl.GetStart() << endl;
        avl.Inorder();
        cout << endl;
    }
    

    return 0;
    
}