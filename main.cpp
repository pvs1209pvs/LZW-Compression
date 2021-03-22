#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>

const std::string WHITESPACE = " \n\r\t\f\v";
 
std::string ltrim(const std::string& s){
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string& s){
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string& s){
    return rtrim(ltrim(s));
}

/**
 * Utilizes Lempel-Ziv-Welch algorithm to compress the message.
 * @param input_file Textfile containing the plain text.
 * @param output_file Textfile containing the encoded text.
 * @return Compression percentage. 
 */
double encode(const std::string input_file, const std::string output_file){

    std::ifstream msg_file{input_file};
    std::string r{};
    std::string msg{};

    while(std::getline(msg_file, r)){
        msg += r;
    }

    msg_file.close();
    

    std::unordered_map<std::string, int> dict{};
    int code = 255;
    std::string crnt{};
    int next{-1};

    size_t encoded_msg_len{0};

    std::ofstream dictonary{"dict.txt"};

    system(std::string{"echo -n \"\" > " + output_file}.c_str());
    
    std::ofstream encoded{output_file, std::ios_base::app};

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

/**
 * Utilizes Lempel-Ziv-Welch algorithm to decompress the encoded text.
 * @param input_file Textfile containing the encoded text.
 * @param output_file Textfile containing the decoded text.
 */
void decode(const std::string input_file, const std::string output_file){

    std::ifstream dict_file{"dict.txt"};
    std::string r{};

    std::unordered_map<int, std::string> dict{};

    while(std::getline(dict_file, r)){    
        std::string ops{r};
        std::reverse(ops.begin(), ops.end());

        dict.insert(std::pair<int, std::string>{
            std::stoi(r.substr(r.size()-ops.find(" "), r.npos)),
            r.substr(0, r.size()-ops.find(" ")-1)
        });
    }

    dict_file.close();


    std::ifstream encode_file(input_file);
    r = std::string{};

    std::vector<int> encoded_msg{};

    while(std::getline(encode_file, r)){
        encoded_msg.push_back(std::stoi(r));
    }

    encode_file.close();


    std::ofstream decoded{output_file};
    for(auto e : encoded_msg){
        decoded << ((e < 256) ? std::string{(char)e} : dict[e]);
    }

}

int main(int argc, char * argv[]){

    switch (argc){
        case 4: {
            if(strcmp(argv[1], "-e")==0){
                std::cout << "compressed by " << encode(argv[2], argv[3])*100 << "%" << std::endl;
            }
            else if(strcmp(argv[1], "-d")==0){
                decode(argv[2], argv[3]);
            }
            else{
                std::cout << "illegal arguments." << std::endl;
                return -1;
            }
            break;
        }
        default:{
            std::cout << "not enough arguments." << std::endl;
            return -1;
        }

    }

    return 0;

}