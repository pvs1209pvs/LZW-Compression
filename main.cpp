#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

void encode(const std::string m){

    std::string msg{std::move(m)};

    std::unordered_map<std::string, int> dict{};
    int code = 255;

    std::string crnt{};
    int next{-1};

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
            }
            else if(crnt.size()>1){
                encoded << dict[crnt] << std::endl;
            }
            
            crnt += msg[next];
            
            //if(crnt.size()==1) std::cout << crnt << std::endl;

            dict.insert(std::pair<std::string, int>{crnt,  crnt.size()==1? (int)crnt[0] : ++code });
            crnt = msg[next];

        }

        
       
    }

    for(auto x : dict){
        std::cout << x.first << " " << x.second << std::endl;
    }

}

int main(){

    encode("banana");

    return 0;
}