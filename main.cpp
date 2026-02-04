#include<iostream>
#include"Visitor.hpp"
#include<fstream>



int main(int argc,char* argv[])
{
    if (argc != 2)
    {
        std::cerr<<"La cantidad de argumentos que se deben dar son 2.\n";
        std::cerr<<"Intente denuevo.\n";
        return EXIT_FAILURE;
    }

    Tokenizer tokenThis{argv[1]};
    tokenThis.tokenize();
    auto t = tokenThis.getTokens();

    Parser parseThis{t};
    parseThis.globalParse();
    auto s = parseThis.getStatements();

    analyseAndGenerate(s);

    std::cout<<"\n";
    std::cout<<"Su compilacion fue exitosa, su codigo fue guardado en assembly.asm\n";
    std::cout<<"Usar nasm para asemblar y su linker adecuado.\n";


    return 0;
}
