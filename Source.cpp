#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <math.h>
#include <sstream>
#include <iterator>
#include <algorithm>


using namespace std;

class Data {
public:
	/* 
		data[0] = veTrai, data[1] = vePhai
		truoc khi su dung bien data, phai goi ham getData()
	*/
	vector<vector<vector<string>>> data;
	vector<string> dictionary;
	void getData();
	string getValue(string);
	string convertToCharacter(string);
	Data(); // contructor tu dong goi ham getData() khi mot bien class duoc tao
	int index;
	vector<vector<string>> inputData();
	void insert(vector<vector<string>>*, string &, vector<string>&);
	vector<vector<string>> Data::convertString(string);
};

void Data::insert(vector<vector<string>>*temp, string &str, vector<string> &element)
{
	str = convertToCharacter(str);
	element.push_back(str);
	str = "";
	temp->push_back(element);
	element.clear();
}

vector<vector<string>> Data::convertString(string stringConvert)
{
	vector<vector<string>> results;
	vector<string> veTrai, vePhai, *temp, vec;
	temp = &veTrai;
	string a, str;
	istringstream iss(stringConvert);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(vec));

	for (int i = 0; i < vec.size(); i++)
	{
		a = vec[i];
		if (a == "NEU")
		{
			temp = &veTrai;
			str = "";
			continue;
		}
		else if (a == "THI")
		{
			str = convertToCharacter(str);
			temp->push_back(str);
			str = "";
			temp = &vePhai;
			continue;
		}
		else if (a == "VA")
		{
			str = convertToCharacter(str);
			temp->push_back(str);
			str = "";
			continue;
		}
		str += (a + " ");
	}
	str = convertToCharacter(str);
	temp->push_back(str);

	results.push_back(veTrai);
	results.push_back(vePhai);

	return results;
}

vector<vector<string>> Data::inputData()
{
	/* Ham nhap mot cau tu console roi dua ve dang ky tu */
	vector<vector<string>> results;
	vector<string> veTrai, vePhai, *temp;
	vector<string> element, vec;
	temp = &veTrai;
	string a, str, test;
	cout << "Nhap cau: ";
	getline(cin, test);
	istringstream iss(test);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(vec));
	
	for(int i = 0; i < vec.size(); i++)
	{
		a = vec[i];
		if (a == "NEU")
		{
			temp = &veTrai;
			str = "";
			continue;
		}
		else if (a == "THI")
		{
			str = convertToCharacter(str);
			temp->push_back(str);
			str = "";
			temp = &vePhai;
			continue;
		}
		else if (a == "VA")
		{
			str = convertToCharacter(str);
			temp->push_back(str);
			str = "";
			continue;
		}
		str += (a + " ");
	}
	str = convertToCharacter(str);
	temp->push_back(str);

	results.push_back(veTrai);
	results.push_back(vePhai);

	return results;
}

Data::Data()
{
	index = 0;
	getData();
}

string Data::convertToCharacter(string str)
{
	/* Ham chuyen doi chuoi str ve mot dang ky tu, sau khi luu vao dictionary */

	/* So sanh chuoi da ton tai trong dictionary chua */
	int indexTemp = index;
	for (int i = 0; i < dictionary.size(); i++)
	{
		if (dictionary[i] == str)
		{
			indexTemp = i;
			goto convertString;
		}
	}
	
	dictionary.push_back(str);
	index++;

convertString:
	indexTemp += 1;
	str = "";
	while (indexTemp > 0)
	{
		int temp = indexTemp % 26;
		if (temp == 0)
		{
			str += "Z";
			indexTemp = (indexTemp / 26) - 1;
		}
		else
		{
			str += char((temp - 1) + 'A');
			indexTemp /= 26;
		}
	}

	return str;
}

void Data::getData()
{
	/* Ham doc du lieu tu file data.txt*/
	fstream dataFile;
	dataFile.open("data.txt", ios::in);
	string a, str;
	vector<vector<string>> veTrai, vePhai, *temp;
	temp = &veTrai;
	vector<string> element;

	while (dataFile >> a)
	{
		if (a == "NEU")
		{
			
			if (str != "")
				insert(temp, str, element);
			temp = &veTrai;
			continue;
		}
		else if (a == "THI")
		{
			insert(temp, str, element);
			temp = &vePhai;
			continue;
		}
		else if (a == "VA")
		{
			str = convertToCharacter(str);
			element.push_back(str);
			str = "";
			continue;
		}
		str += (a + " ");
	}
	insert(temp, str, element);
	
	data.push_back(veTrai);
	data.push_back(vePhai);
}

string Data::getValue(string str)
{
	/*
		Ham lay du lieu tu dictionary voi tu khoa la ky tu duoc chuyen doi truoc do
		vi du: 
				getValue("A"); -> troi mua
	*/
	int index = 0;
	for (int i = 1; i < str.length(); i++)
		index += pow(26, i);
	for (int i = 0; i < str.length(); i++)
		index += (str[i] - 64 - 1) * pow(26,(str.length() - 1 - i));
	
	if(index < dictionary.size())
		return dictionary[index];
	cout << "Khong ton tai " << str << " tron dictionary" << endl;
	return "";
}


void main()
{
	vector<string> a;
	a.push_back("A");
	a.push_back("B");
	a.push_back("C");
	//a.push_back("D");
	vector<vector<string>> veTrai, vePhai;
	Data dulieu;
	//dulieu.getData();
	veTrai = dulieu.data[0];
	vePhai = dulieu.data[1];
	
	cout << "Ve trai: " << endl;
	for (int i = 0; i < veTrai.size(); i++)
	{
		cout << "Cau " << i + 1 << endl;
		for (int j = 0; j < veTrai[i].size(); j++)
		{
			cout << veTrai[i][j] << endl;
		}
	}

	cout << "Ve phai: " << endl;
	for (int i = 0; i < vePhai.size(); i++)
	{
		cout << "Cau " << i + 1 << endl;
		for (int j = 0; j < vePhai[i].size(); j++)
		{
			cout << vePhai[i][j] << endl;
		}
	}
	string test = dulieu.getValue("C");
	cout << test << endl;


	// test inputData()
	vector<vector<string>> results;
	
	results = dulieu.inputData();

	cout << "Ve trai: " << endl;
	for (int i = 0; i < results[0].size(); i++)
		cout << results[0][i] << " ";

	cout << endl;

	cout << "Ve phai: " << endl;
	for (int i = 0; i < results[1].size(); i++)
		cout << results[1][i] << " ";

	cout << endl;

	system("pause");
}