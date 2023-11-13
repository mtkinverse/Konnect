#include <iostream>
class User{
    std :: string name,password,email;
    int id;
    float points;

    public:

    User(){
        name = password = email = "";
        id = 0;
        points = 0;
    }
    
    User(std :: string name,std :: string password,std :: string email){
        this->name = name;
        this->password = password;
        this->email = email;
        this->points = 0;
    }// we have to set a method for getting the ids/tokens (last leaved)

    bool operator == (const User& obj){
        return (this->id == obj.id || this->email == obj.email);
    }

    bool operator < ( const User& obj){
        return this->id < obj.id;
    }

    friend std::ostream& operator << (std::ostream& , User& obj){
        std::cout << "User id : " << obj.id << "\nName : " << obj.name << "\nEmail : "<< obj.email << "\nPoints : "<< obj.points << std::endl << std::endl;
    }

};