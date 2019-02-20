#include <vector>
#include <string>

int searchRecursive(std::vector<std::string> &data, std::string query){
	if (data.back() == query){
		return data.size();
	}
	else{
		data.pop_back();
		return searchRecursive(data, query);
	}
}

int searchIterative(std::vector<std::string> &data, std::string query){
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == query) {
			return i;
		}
	}
	return -1;
}
