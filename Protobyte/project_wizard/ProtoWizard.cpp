//http://en.cppreference.com/w/cpp/algorithm/transform

#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    
    
    // .h
    std::string hFile(argv[1]);
    // .cpp
    std::string cppFile(argv[1]);

    std::string className(argv[1]);
    std::string ifndefTitle ("__" + hFile + "_H__");
    std::transform(ifndefTitle.begin(), ifndefTitle.end(), ifndefTitle.begin(), std::ptr_fun<int, int>(std::toupper));
    

    // path to source directory
    std::string path("../src/");

    // .h
    hFile+=".h";

    // ensure filename doesn't already exist
    ifstream ifile(std::string(path+hFile).c_str());
    if (ifile) {
      // The file exists, and is open for input
          std::cout << "ERROR: Project Creation Failure:\nREASON: Project name already exists.\nFIX: Please use a unique name." << std::endl;
          return 0;
    } else {
         std::cout << "Project "<< className << " (files:"<< className<<".h"<<", "<< className<<".cpp) successfully created." << std::endl;

    }


    // safe to create project files
    ofstream outH(std::string(path+hFile).c_str());
    outH << "\n" <<
        "#ifndef " << ifndefTitle << "\n" <<
        "#define " << ifndefTitle << "\n" <<
        "\n" <<
        "#include <iostream>\n" <<
        "#include \"appProtobyte/ProtoBaseApp.h\"" <<
        "\n" <<
        "\n" <<
        "using namespace ijg;\n" <<
        "\n" <<
        "class " << className <<" : public ProtoBaseApp {\n" <<
        "\n" <<
        "public:\n" <<
            "void init();\n" <<
            "void run();\n" <<
            "void display();\n" <<
        "\n" <<
        "private:\n" << 
        "};\n" <<
        "\n" <<         
        "#endif //" << ifndefTitle << "\n";



 // .cpp
    cppFile+=".cpp";
    ofstream outCpp(std::string(path+cppFile).c_str());
    outCpp<< "\n" <<
        "#include " << "\"" << hFile << "\""<< "\n" <<
        "\n" <<
        "void " << className << "::init() {\n" <<
        "}\n" <<
        "\n" <<
        "void " << className << "::run() {\n" <<
        "}\n" <<
        "\n" <<
        "void " << className << "::display() {\n" <<
        "}";




    return 0;
}
