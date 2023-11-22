#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\Post.cpp"
#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\List.cpp"
#include "C:\Users\AhsanComputers\OneDrive\Desktop\DS project\User.cpp"
#include<fstream>
#include<string.h>
#include<stdlib.h>

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


int main(){

    char key[30] = "raofc",time[30] = {'\0'},text[500] = "This is the text that was posted by rao\0";
    History h;
    h.GetTime(time);
    Post p(key,text,time,0);
    h.UpdateHistory(key);
    // h.AddPost(key,text,time,0);
    // h.GetTime(time);
    // strcpy(text,"This is the second text posted by rao");
    // h.AddPost(key,text,time,0);

    h.PrintAllPosts("Rao Abdul Hadi");

    // h.UpdateHistory(p.GetSignature());
    
    // h.PrintAllPosts("taha khan");
    return 0;
}