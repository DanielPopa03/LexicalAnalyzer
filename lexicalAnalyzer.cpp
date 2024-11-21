#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ostream>

std::unordered_map<std::string, std::string> punctuators = {
    {";", "Semicolon"},
    {",", "Comma"},
    {".", "Dot"},
    {"(", "Left Parenthesis"},
    {")", "Right Parenthesis"},
    {"{", "Left Brace"},
    {"}", "Right Brace"},
    {"[", "Left Bracket"},
    {"]", "Right Bracket"},
};

std::unordered_map<std::string, std::string> operators = {
        // Control flow
        {"+", "Plus"},
        {"-","Minus"},
        {"=","Equal"},
        {"*","Multiplication"},
        {"/","Division"},
        {"%","Modulo"},
        {"++","Increment"},
        {"--","Decrement"},
        {"==","Equal"},
        {"!=","Not Equal"},
        {"<","Less Than"},
        {">","Greater Than"},
        {"<=","Less Than or Equal"},
        {">=","Greater Than or Equal"},
        {"&&","Logical And"},
        {"||","Logical Or"},
        {"!","Logical Not"},
        {"&","Bitwise And"},
        {"|","Bitwise Or"},
        {"^","Bitwise Xor"},
        {"~","Bitwise Not"},
        {"<<","Left Shift"},
        {">>","Right Shift"},
        {"+=","Plus Equal"},
        {"-=","Minus Equal"},
        {"*=","Multiplication Equal"},
        {"/=","Division Equal"},
        {"%=","Modulo Equal"},
        {"&=","Bitwise And Equal"},
        {"|=","Bitwise Or Equal"},
        {"^=","Bitwise Xor Equal"},
        {"<<=","Left Shift Equal"},
        {">>=","Right Shift Equal"},
        {"->","Pointer"},
        {".","Member Access"},
        {"::","Scope Resolution"},
        {"?","Ternary Operator"},
        {":","Ternary Operator"},
        {"&","Address Operator"},
        {"*","Pointer Operator"},
        {"->*","Pointer to Member Operator"},
        {"()","Function Call Operator"},
        {"[]","Subscript Operator"},
        {"{}","Initializer List"},
        {"#","Preprocessor"},
        {"##","Token Pasting"},
};


std::unordered_map<std::string, std::string> keywords = {
        // Control flow
        {"if", "Control Flow"},
        {"else", "Control Flow"},
        {"for", "Control Flow"},
        {"while", "Control Flow"},
        {"do", "Control Flow"},
        {"switch", "Control Flow"},
        {"case", "Control Flow"},
        {"default", "Control Flow"},
        {"break", "Control Flow"},
        {"continue", "Control Flow"},
        {"return", "Control Flow"},
        {"goto", "Control Flow"},

        // Data types
        {"int", "Data Type"},
        {"char", "Data Type"},
        {"float", "Data Type"},
        {"double", "Data Type"},
        {"bool", "Data Type"},
        {"void", "Data Type"},
        {"wchar_t", "Data Type"},
        {"long", "Data Type"},
        {"short", "Data Type"},
        {"signed", "Data Type"},
        {"unsigned", "Data Type"},

        // Storage class specifiers
        {"static", "Storage Class Specifier"},
        {"extern", "Storage Class Specifier"},
        {"mutable", "Storage Class Specifier"},
        {"register", "Storage Class Specifier"},
        {"thread_local", "Storage Class Specifier"},

        // Type modifiers
        {"const", "Type Modifier"},
        {"volatile", "Type Modifier"},

        // Access specifiers (for classes)
        {"private", "Access Specifier"},
        {"public", "Access Specifier"},
        {"protected", "Access Specifier"},

        // Function specifiers
        {"inline", "Function Specifier"},
        {"virtual", "Function Specifier"},
        {"explicit", "Function Specifier"},

        // Exception handling
        {"try", "Exception Handling"},
        {"catch", "Exception Handling"},
        {"throw", "Exception Handling"},

        // Namespace
        {"namespace", "Namespace"},
        {"using", "Namespace"},

        // Others
        {"class", "Class Definition"},
        {"struct", "Struct Definition"},
        {"union", "Union Definition"},
        {"enum", "Enumeration"},
        {"template", "Template"},
        {"typename", "Type Specifier"},
        {"sizeof", "Size Operator"},
        {"new", "Memory Allocation"},
        {"delete", "Memory Deallocation"},
        {"this", "Pointer"},
        {"operator", "Operator Overload"},
        {"friend", "Friend Declaration"},
        {"typedef", "Type Definition"},
        {"decltype", "Type Inference"},
        {"nullptr", "Null Pointer"},
        {"static_assert", "Compile-time Assertion"},
        {"alignas", "Alignment Specifier"},
        {"alignof", "Alignment Operator"},
        {"concept", "Concept Declaration"},
        {"requires", "Requirement Clause"},
        {"co_await", "Coroutine"},
        {"co_yield", "Coroutine"},
        {"co_return", "Coroutine"}
};

enum TypeOfLine{
    Comment,
    String,
    Normal
};

class Token {
private:
    std::string type;
    std::string value;
    std::vector<int> lineNumber;
public:
    
    Token(std::string type, std::string value, std::vector<int> lineNumber) {
        this->type = type;
        this->value = value;
        this->lineNumber = lineNumber;
    }


    static void inspectFile(std::vector<std::string> &lines, std::vector<Token> &tokens){
        TypeOfLine typeOfLine = Normal;
        for(int i = 0; i < lines.size(); i++) {
            switch (typeOfLine)
            {
            case Normal:
                typeOfLine = inspectLine(tokens, lines[i], i+1);
                break;
            case Comment:
                if(i + 1 < lines.size()) {
                typeOfLine = inspectComment(tokens, lines[i], i+1, false);
                } else {
                  typeOfLine = inspectComment(tokens, lines[i], i+1, true);
                }
                break;
            case String:
                typeOfLine = inspectString(tokens, lines[i], i+1);
                break;
            default:
                std::cerr << "Invalid type of line - at line " << i << std::endl;
                break;
            }
        }
    }

    static TypeOfLine inspectLine(std::vector<Token> &vector, std::string &line, int lineNumber) {
        std::cout<<"Normal !!"<<line<<std::endl;
        std::string token = "";
        std::string type = "";
        int  size = line.size();
        for(int i = 0; i < size; i ++ ) { 
            if(line[i] != ' ') {

                if( 'a' <= line[i] && line[i] <= 'z' || 'A' <= line[i] && line[i] <= 'Z' || line[i] == '_') {
                    token.push_back(line[i]);
                    for(int j = i + 1; j < size; j++) {
                        if( 'a' <= line[j] && line[j] <= 'z' || 'A' <= line[j] && line[j] <= 'Z' || line[j] == '_' || '0' <= line[j] && line[j] <= '9' || line[i] == '_') {
                            token.push_back(line[j]);
                        } else {
                            i = j;
                            if(keywords.find(token) != keywords.end()) {
                                type = keywords[token];
                                vector.push_back(Token("Keyword", token, std::vector<int>{lineNumber}));
                            } else {
                                vector.push_back(Token("Identifier", token, std::vector<int>{lineNumber}));
                            }
                            token = ""; type = "";
                            break;
                        }
                    }
                }

                if('0' <= line[i] && line[i] <= '9') {
                    token.push_back(line[i]);
                    if(i + 1 < size && line[i + 1] == 'x') {
                        token.push_back(line[i + 1]);
                        for(int j = i + 2; j < size; j++) {
                            if('0' <= line[j] && line[j] <= '9' || 'a' <= line[j] && line[j] <= 'f' || 'A' <= line[j] && line[j] <= 'F') {
                                token.push_back(line[j]);
                            } else {
                                i = j;
                                vector.push_back(Token("Hexadecimal", token, std::vector<int>{lineNumber}));
                                token = ""; type = "";
                                break;
                            }
                        }
                    } else if(i + 1 < size && line[i + 1] == 'b') {
                        token.push_back(line[i + 1]);
                        if(!(i + 2 < size && line[i + 2] == '0' || line[i + 2] == '1')) {
                            throw std::runtime_error("Invalid binary at line " + std::to_string(lineNumber));
                        }
                        for(int j = i + 2; j < size; j++) {
                            if(line[j] == '0' || line[j] == '1') {
                                token.push_back(line[j]);
                            } else {
                                i = j;
                                vector.push_back(Token("Binary", token, std::vector<int>{lineNumber}));
                                token = ""; type = "";
                                break;
                            }
                        }
                    } else {
                     
                        for(int j = i + 1; j < size; j++) {
                            if('0' <= line[j] && line[j] <= '9' || line[j] == '.') {
                                token.push_back(line[j]);
                            } else {
                                i = j;
                                vector.push_back(Token("Number", token, std::vector<int>{lineNumber}));
                                token = ""; type = "";
                                break;
                            }
                        }
                    }
                }


                if(line[i] == '"') {
                    bool finished = false;
                    token.push_back(line[i]);
                    for(int j = i + 1; j < size; j++) {
                        if(line[j] == '"') {
                            token.push_back(line[j]);
                            vector.push_back(Token("String", token, std::vector<int>{lineNumber}));
                            token = ""; type = "";
                            i = j;
                            finished = true;
                            break;
                        } else {
                            token.push_back(line[j]);
                        }
                    }
                    if(!finished) {
                        for(int z = token.size() - 1; z > -1 ; z--){
                            if(token[i] != ' '){
                            token = token.substr(0, z + 1);
                            break;
                            }
                        }
                        if(token[token.size() - 1] == '\\') {
                            token = token.substr(0, token.size() - 1);
                            vector.push_back(Token("String", token, std::vector<int>{lineNumber}));
                            return String;
                        } else {
                            throw std::runtime_error("Invalid string at line " + std::to_string(lineNumber));
                        }
                    }
                }

                bool isNotTheLastCharacter = (i+1 < size);

                if(isNotTheLastCharacter) {
                    if(line[i] == '/' && line[i + 1] == '/') {
                        return Normal;
                    }
                    if(line[i] == '/' && line[i + 1] == '*') {
                        bool closed = false;
                        for(int j = i + 2; j < size; j++) {
                            if(line[j] == '*' && line[j + 1] == '/') {
                                closed = true;
                                if(j + 2 < size) {
                                    i = j + 2;
                                } else {
                                    return Normal;
                                }
                            }
                        } 
                        if(!closed) {
                            return Comment;
                        }
                    }
                }

                if(operators.find(std::string(1, line[i])) != operators.end()) {
                    if(isNotTheLastCharacter) {
                        if(operators.find(std::string(1, line[i]) + line[i + 1]) != operators.end()) {
                            vector.push_back(Token("Operator", std::string(1, line[i]) + line[i + 1], std::vector<int>{lineNumber}));
                            i++;
                        }
                    } else {
                        vector.push_back(Token("Operator", std::string(1, line[i]), std::vector<int>{lineNumber}));
                    }
                }

                if(punctuators.find(std::string(1, line[i])) != punctuators.end()) {
                    vector.push_back(Token("Punctuation", std::string(1,line[i]), std::vector<int>{lineNumber}));
                    continue;
                }

                if(line[i] == '*') {
                    vector.push_back(Token("Punctuation", std::string(1,line[i]), std::vector<int>{lineNumber}));
                    continue;
                }

            }
        }

        return Normal;
    }

    static TypeOfLine inspectComment(std::vector<Token> &vector, std::string &line, int lineNumber, bool endOfFile) {
        std::cout<<"Comment !!"<<line<<std::endl;
        int size = line.size();
        for(int i = 0; i < size - 1; i++) {
            if(line[i] == '*' && line[i + 1] == '/') {
            std::string lineRemainedUntilEnd = line.substr(i + 1, size - i - 1);
                return inspectLine(vector, lineRemainedUntilEnd, lineNumber);
            }
        }
        if(endOfFile){
            throw std::runtime_error("Invalid comment at line " + std::to_string(lineNumber));
        }
        return Comment;
    }

    static TypeOfLine inspectString(std::vector<Token> &vector, std::string &line, int lineNumber) {
        std::cout<<"String !!"<<line<<std::endl;
        bool firstCharacter = true;
        int size = line.size();
        Token &token = vector[vector.size() - 1];
        std::vector<int> &lineNumbers = token.lineNumber;
        lineNumbers.push_back(lineNumber);
        int positionOfBackSlash = -1;
        int  positionOfFirstNotBlankCharacter = -1;
        std::string bufferForString = "";
        for(int i = 0; i < size; i++) {
            switch (firstCharacter)
            {
            case true:
                if(line[i] != ' ') {
                    std::cout<<line[i]<<std::endl;
                    positionOfFirstNotBlankCharacter = i;
                    firstCharacter = false;
                    if(line[i] == '"') {
                    token.value.push_back('"');
                    std::string lineRemainedUntilEnd = line.substr(i + 1, size - i - 1);
                    return inspectLine(vector, lineRemainedUntilEnd, lineNumber);
                    }
                    if(line[i] == '\\') {
                        positionOfBackSlash = i;
                    }
                    bufferForString.push_back(line[i]);
                }
                break;
            
            case false:
                if(line[i] == '"') {
                    if( i - 1 > 0) {
                        if(line[i - 1] != '\\') {
                            bufferForString.push_back('"');
                            token.value.append(bufferForString);
                            std::string lineRemainedUntilEnd = line.substr(i + 1, size - i - 1);
                            return inspectLine(vector, lineRemainedUntilEnd, lineNumber);
                        }
                    }
                
                }
                if(line[i] == '\\') {
                    positionOfBackSlash = i;
                }
                bufferForString.push_back(line[i]);
                break;
            } 
        }
        for(int i = bufferForString.size() - 1; i > -1 ; i--){
            if(bufferForString[i] != ' '){
               bufferForString = bufferForString.substr(0, i + 1);
                break;
            }
        }
        if(positionOfBackSlash > 0 && bufferForString[bufferForString.size() - 1] == '\\' ) {
            token.value.append(bufferForString);
            return Normal;
        } else throw std::runtime_error("Invalid string at line " + std::to_string(lineNumber));
    }

    friend std::ostream & operator << (std::ostream &out, const Token &token);
};

std::ostream & operator << (std::ostream &out, const Token &c) {
    out <<"Type : "<<c.type << " | "<<"line:"<<c.lineNumber[0];
    if(c.lineNumber.size() > 1)
    out<< "-" << c.lineNumber[c.lineNumber.size() - 1];
    out << " | value : " << c.value << std::endl;
    return out;
}

int main() {
    std::ifstream inputFile("exemplu.txt");  // Open the file for reading
    std::string line;
    std::vector<Token> tokens = std::vector<Token>();
    std::vector<std::string> lines = std::vector<std::string>();
    // Check if the file was opened successfully
    int lineNumber = 0;
    if (inputFile.is_open()) {
        // Read file line by line
        while (std::getline(inputFile, line)) {
            lineNumber++;
            lines.push_back(line);
        }
        inputFile.close();  // Close the file after reading
    } else {
        std::cerr << "Unable to open file!" << std::endl;
    }
    std::cout<<"Ba"<<std::endl;
    Token::inspectFile(lines, tokens);
    std::cout<<"BaExit"<<std::endl;
    for(Token &token : tokens) {
        std::cout << token;
    }
    std::cout<<"FInish"<<std::endl;
    return 0;
}

