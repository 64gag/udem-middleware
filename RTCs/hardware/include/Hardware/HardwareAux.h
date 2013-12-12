#ifndef HARDWAREAUX
#define HARDWAREAUX

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
std::vector<float> string2floats(std::string s);
std::vector<float> extractFloats(std::string s, std::string f, char token);

#endif
