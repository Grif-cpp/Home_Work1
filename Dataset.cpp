// Dataset.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
int num;
std::string type;
float conv(std::string &s) {
	return atof(s.c_str());
}
bool comp(std::vector<std::string>&a,std::vector<std::string> &b) {
	if(type=="string")return (a[num] < b[num]);
	else if (type == "int")
	{
		int l1, l2;
		l1 = a[num].length();
		l2 = b[num].length();
		if (l1==l2)
			return (a[num] < b[num]);
		else return (l1 < l2);
	}
	if (type == "float")
	{
		float f1, f2;
		f1 = conv(a[num]);
		f2 = conv(b[num]);
		return(f1 < f2);
	}
}
int main()
{
	std::string path;
	std::cin >> path;
	std::cin >> num;
	std::cin >> type;
	//path = "Tester.csv";
	//num = 1;
	//type = "float";
	std::fstream fs;
	fs.open(path);
	int num;
	std::string s1, sv;
	std::vector<std::vector<std::string>>a;
	int j = 0;
    bool u = 0;
	while (!fs.eof() && std::getline(fs,s1)) {
		a.resize(a.size() + 1);
		int l = 0;
		s1 += '\n';
		for (int i = 0; i < s1.length(); i++) {
			if (u==0&&(s1[i]==',' || s1[i]== '\n')&&(i>l)) {
				sv = s1.substr(l, i - l);
				a[j].push_back(sv);
				l = i + 1;
			}
			if (s1[i] == '"') {
				if (u == 1) {
					sv = s1.substr(l, i - l+1);
					a[j].push_back(sv);
					l = i + 2;
				}
				u = 1 - u;
			}
		}
		j++;
	}
	fs.close();
	sort(a.begin(), a.end(), comp);
	path.resize(path.length() - 4);
	path += "_sorted.csv";
	std::ofstream ofs(path);
	ofs.close();
	fs.open(path);
	for (int i = 0; i < a.size();i++) {
		for (auto j:a[i]) {
			fs << j << ';';
		}
		fs << std::endl;
	}
	fs.close();
	return 0;
}