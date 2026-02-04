#include<iostream>
#include"Visitor.hpp"
#include<fstream>



int main()
{

    Tokenizer tokenThis{"./codigo.txt"};
    tokenThis.tokenize();
    auto t = tokenThis.getTokens();

    Parser parseThis{t};
    parseThis.globalParse();
    auto s = parseThis.getStatements();
    printStatements(s);





    return 0;
}
