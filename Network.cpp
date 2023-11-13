#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\NodeGraph.cpp"
#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\Stack.cpp"
#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\AVL.cpp"

template <class t>
class Graph{
    
    AVL<NodeG<t>*> AllNodes;
    int ** adjMatrix;
    int NumNodes;

public:

    Graph(){
        adjMatrix = nullptr;
        NumNodes = 0;
    }

    void IncreaseMatrix(){

        int ** temp = new int[NumNodes];
        for(int i=0;i<NumNodes;i++){
            temp[i] = new int[NumNodes] {0};
            if(i < NumNodes - 1){
                for(int j = 0; j<NumNodes ; j++)temp[i][j] = adjMatrix[i][j];
            }
        }

        for(int i=0;i<NumNodes;i++) delete[] adjMatrix[i];
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
    }

};