#include<iostream>
#include<string.h>
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

