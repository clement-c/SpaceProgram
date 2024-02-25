#include <string>


struct DataItem
{
	template<typename T>
	static bool Register<T>(std::string const & name);
};
