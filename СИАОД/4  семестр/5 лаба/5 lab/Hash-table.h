#include <string>
using namespace std;

namespace myLab
{
	class MyHashTable
	{
	private:
		typedef struct
		{
			std::string data;
			bool status;
		}str;
		str* table;
		int size;
	public:
		explicit MyHashTable(int _size);
		~MyHashTable();
		unsigned int hash_function(std::string _data);
		bool set_new(std::string _data);
		int find_elem(std::string _data);
		bool delete_elem(std::string _data);
		bool print_table();
	};
}