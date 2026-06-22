#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Replaces every occurrence of s1 with s2, WITHOUT using std::string::replace.
// We scan with find(), copy the chunk before each match, then insert s2.
static std::string	replaceAll(const std::string &content,
							   const std::string &s1, const std::string &s2)
{
	if (s1.empty())            // nothing meaningful to search for
		return (content);

	std::string	result;
	std::size_t	start = 0;
	std::size_t	pos;

	while ((pos = content.find(s1, start)) != std::string::npos)
	{
		result += content.substr(start, pos - start); // text before the match
		result += s2;                                  // the replacement
		start = pos + s1.length();                     // jump past the match
	}
	result += content.substr(start);                   // remaining tail
	return (result);
}

int	main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return (1);
	}

	std::string	filename = argv[1];
	std::string	s1 = argv[2];
	std::string	s2 = argv[3];

	std::ifstream	inFile(filename.c_str());
	if (!inFile.is_open())
	{
		std::cerr << "Error: cannot open file '" << filename << "'" << std::endl;
		return (1);
	}

	// Read the whole file (bytes preserved exactly, newlines included).
	std::stringstream	buffer;
	buffer << inFile.rdbuf();
	inFile.close();
	std::string	content = buffer.str();

	std::string		outName = filename + ".replace";
	std::ofstream	outFile(outName.c_str());
	if (!outFile.is_open())
	{
		std::cerr << "Error: cannot create file '" << outName << "'" << std::endl;
		return (1);
	}

	outFile << replaceAll(content, s1, s2);
	outFile.close();

	return (0);
}
