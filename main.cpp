#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <fstream>

/**
 * Utilizes Lempel-Ziv-Welch algorithm to compress the message.
 * @param m Message to be encoded.
 * @return Compression percentage. 
 */
double encode(const std::string m){

    std::string msg{std::move(m)};

    std::unordered_map<std::string, int> dict{};
    int code = 255;
    std::string crnt{};
    int next{-1};

    size_t encoded_msg_len{0};

    std::ofstream dictonary{"dict.txt"};

    system("echo -n \"\" > encoded.txt");
    std::ofstream encoded{"encoded.txt", std::ios_base::app};

    while(next != (int)msg.size()){

        ++next;
  
        if(dict.find(std::string{crnt+msg[next]}) != dict.end()){
            crnt += msg[next];
        }
        else{
            
            if(crnt.size()==1)  encoded << (int)crnt[0] << std::endl;
            else if(crnt.size()>1)  encoded << dict[crnt] << std::endl;        
    
            if(crnt.size() > 0) ++encoded_msg_len; 
            
            crnt += msg[next];
            
            dict.insert(std::pair<std::string, int>{crnt, crnt.size() ==1 ? (int)crnt[0] : ++code });
            crnt = msg[next];

        }
       
    }
    
    for(auto x : dict){
        dictonary << x.first << " " << x.second << std::endl;
    }

    return (double)(msg.size()-encoded_msg_len)/msg.size();

}

void decode(std::string encode_file_name){

    std::ifstream dict_file{"dict.txt"};
    std::string r{};

    std::unordered_map<int, std::string> dict{};

    while(std::getline(dict_file, r)){
        dict.insert(std::pair<int, std::string>{
            std::stoi(r.substr(r.find(" ")+1, r.npos)),
            r.substr(0, r.find(" "))
        });
    }

    dict_file.close();


    std::ifstream encode_file(encode_file_name);
    r = std::string{};

    std::vector<int> encoded_msg{};

    while(std::getline(encode_file, r)){
        encoded_msg.push_back(std::stoi(r));
    }

    encode_file.close();


    std::ofstream decoded{"decoded.txt"};
    for(auto e : encoded_msg){
        decoded << ((e < 256) ? std::string{(char)e} : dict[e]);
    }

}

int main(int argc, char * argv[]){

    if(argc == 3){
        if(strcmp(argv[1], "-e")==0){
            std::cout << "compressed by " << encode(argv[2])*100 << "%" << std::endl;
        }
        else if(strcmp(argv[1], "-d")==0){
            decode(argv[2]);
        }
        else{
            std::cout << "illegal arguments." << std::endl;
            return -1;
        }
    }
    else{
        std::cout << "not enough arguments." << std::endl;
        return -1;
    }
    
    
    return 0;

}