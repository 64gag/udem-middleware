#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

/* Evan Teran's string-splitting code from: http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s); std::string item;
    while (std::getline(ss, item, delim)) { elems.push_back(item); }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems; split(s, delim, elems);
    return elems;
}

/* Split a string of comma-separated floats and stores them in a vector of floats */
std::vector<float> string2floats(std::string s)
{
	std::vector<std::string> str_slopes = split(s, ',');
	std::vector<float> f;
	for(std::vector<std::string>::iterator it = str_slopes.begin(); it != str_slopes.end(); ++it) {
		f.push_back(::atof((*it).c_str()));
	}
	
	return f;
}

/* Extracts float numbers from 's' using format 'f' (where floats are specified by 'token') */
std::vector<float> extractFloats(std::string s, std::string f, char token)
{
	std::vector<float> ret;
	std::vector<std::string> exploded = split(f, token);

	for(unsigned int i=0; i+1 < exploded.size(); i++){
		s = s.substr(exploded[i].length());
		std::size_t notnum = s.find_first_not_of("0123456789.-");
		ret.push_back(::atof(s.substr(0, notnum).c_str()));
		s = s.substr(notnum);
	}
 return ret;
}
