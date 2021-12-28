#include<iostream>
#include<string>
#include<cctype>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>

int main(int argc, char *argv[])
{
	using namespace std;
	
	int kol_vo_clov_v_tekste = 0;
	ifstream fin;
	string path_in = "text.txt";
	fin.open(path_in);
	if (!fin.is_open())
	{
    	cout << "Couldn't open text.txt!";
	}
	else
	{
		cout << "text.txt succesfully opened !";

		map<string, int> words;
		string line;
		while (!fin.eof())
		{
			line = "";
			getline(fin, line); // reading the sentence
			int length = line.length(); // the length of current sentence
			string slovo;
			for (int i = 0; i < length ; i++)
			{
				if (isalpha(line[i]) || isdigit(line[i]))
				{
					slovo += line[i];
					if (i == length - 1) // это нужно для того, чтобы последнее слово в строчке тоже было использовано
					{					 // в противном случае программа чиатет последнее слово в строчке, но ничего с ним не делает
						words[slovo] += 1;
						kol_vo_clov_v_tekste += 1;
						slovo = "";
						break;
					}
				}
				else
				{
					words[slovo] += 1;
					kol_vo_clov_v_tekste += 1;
					slovo = "";
					continue;
				}
			}
		}
		vector<pair<string, int>> vec(words.begin(), words.end());
		sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) -> bool {
			if (a.second == b.second) 
			{
				return a.first < b.first;
			}
			return a.second > b.second;
			});
		ofstream fout;
		string path_out = "out.csv";
		fout.open(path_out);
		if (!fout.is_open())
		{
			cout << "Couldn't open out.csv!";
		}
		else
		{
			for (auto e: vec)
			{
				fout << e.first << ";" << e.second << ";" << ((double)e.second / kol_vo_clov_v_tekste) * 100 << "%"<< endl;
			}
		}
		fin.close();
		fout.close();
	}
}
