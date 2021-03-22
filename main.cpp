#include <iostream>
#include <string>
#include <unordered_map>
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

    system("echo -n \"\" > encoded.txt");

    std::ofstream encoded{"encoded.txt", std::ios_base::app};

    while(next != (int)msg.size()){

        ++next;
  
        if(dict.find(std::string{crnt+msg[next]}) != dict.end()){
            crnt += msg[next];
        }
        else{
            
            if(crnt.size()==1){
                encoded << (int)crnt[0] << std::endl;
                ++encoded_msg_len;
            }
            else if(crnt.size()>1){
                encoded << dict[crnt] << std::endl;
                ++encoded_msg_len;  
            }
            
            crnt += msg[next];
            
            dict.insert(std::pair<std::string, int>{crnt,  crnt.size()==1? (int)crnt[0] : ++code });
            crnt = msg[next];

        }
       
    }

    return (double)(msg.size()-encoded_msg_len)/msg.size();

}

int main(int argc, char * argv[]){

    if(argc < 2){
        std::cout << "not enough arguments. add message to be encoded." << std::endl;
        return -1;
    }
    
    std::cout << "compressed by " << encode(argv[1])*100 << "%" << std::endl;

    return 0;
}