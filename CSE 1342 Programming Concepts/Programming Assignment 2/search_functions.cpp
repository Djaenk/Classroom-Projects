#include <vector>
#include <string>

int searchRecursive(std::vector<std::string> &data, std::string query){
	if (data.empty()){
		return -1;
	}
	else if (data.back() == query){
		return data.size() - 1;
	}
	else{
		data.pop_back();
		return searchRecursive(data, query);
	}
}

int searchIterative(std::vector<std::string> &data, std::string query){
	for (int index = 0; index < data.size(); index++){
		if (data[index] == query){
			return index;
		}
	}
	return -1;
}
