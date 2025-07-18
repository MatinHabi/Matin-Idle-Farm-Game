#include <iostream>
#include <fstream>
#include <string>

int main(){
    std::string name;
    std::string message;

    std::cout<<"What is the name of the file: ";
    std::getline(std::cin, name);

    std::cout<<"\nWhat is the message: ";
    std::getline(std::cin, message);

    std::string fileName = name + ".txt";

    std::ofstream out(fileName);
    if(!out){
        std::cerr<<"Error: could not create file ' " << fileName << " '\n";
        return 1;
    }

    out << message << "\n";
    out.close();

    std::cout<< "Success in creating file!\n";

    std::ifstream in(fileName);

    if(!in){
        std::cerr << "Error could not open!\n";
        return 2;
    }

    std::string line;
    bool found = false;
    while(getline(in, line)){
        if(line.find("hello") != std::string::npos){
            found = true;
            break;
        }
    }

    if(found){
        std::cout<<"Found!\n";
    }else{
        std::cout<<"Not Found!\n";
    }

    return 0;


}