#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <vector>

int main()
{
    std::ifstream file{"dic/word.txt", std::ios_base::in};
    int numberOfLine{};

    if(!file)
    {
        std::cerr << "Please check if word.txt is in this directory './dic/word.txt'" << std::endl;
        return -1;
    }
    else 
    {
        while(file.ignore(4, '\n'))
            numberOfLine++;
    }

    bool quit{false};
    bool correctInput{false};
    int streamUserInput{};
    char fileByte{};


    std::random_device seed{};
    std::mt19937 gen{seed()};
    std::uniform_int_distribution<int> dis(0, numberOfLine+1);
    std::vector<std::string> syllables{};

    while(!quit)
    {
        std::cout << "=======================" << std::endl;
        std::cout << "= 1. Show Dictionnary =" << std::endl;
        std::cout << "= 2. Generate a word  =" << std::endl;
        std::cout << "= 3. Quit             =" << std::endl; 
        std::cout << "=======================" << std::endl;

        std::cout << "/> ";
        std::cin >> streamUserInput;
  
        switch(streamUserInput)
        {
            case 1:
                file.clear();
                file.seekg(0, std::ios::beg);
                while(file.get(fileByte))
                {
                    std::cout << fileByte;
                }
                std::cout << std::endl << "Number of line : " << numberOfLine << std::endl;
                break;
            case 2:
            
                do 
                {
                    std::cout << "/ Number of sylable> ";
                    if(std::cin >> streamUserInput)
                    {
                        if(streamUserInput < 0)
                        {
                            std::cerr << "Please enter a positive value !" << std::endl; 
                        }
                        else 
                        {
                            correctInput = true;
                        }
                     }
                    else 
                    {
                        std::cerr << "Please do not enter a text !" << std::endl;
                    }
                }while(!correctInput);

 
                for(std::size_t i {}; i < streamUserInput; i++)
                {
                    file.clear();
                    file.seekg(0, std::ios::beg);

                    auto max = dis(gen);
                    std::string copy{};
                    for(std::size_t j{}; j < max; j++)
                    {
                        std::getline(file, copy);
                    }
                    
                    copy[copy.size()] = '\0';
                    syllables.push_back(copy);
                }   
                
                std::cout << "Generate : ";
                for(const auto& data:syllables)
                    std::cout << data;
                std::cout << std::endl;
                syllables.clear();
                break;
            case 3:
                std::cout << "Thank you for using this programms !" << std::endl; 
                quit = true;
                break;
            default:
                std::cerr << "Unknow choice !" << std::endl;
                break;
        }
    }
 
    return 0;
}