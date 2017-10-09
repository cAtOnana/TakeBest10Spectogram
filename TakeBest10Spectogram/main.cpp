#include<iostream>
#include<fstream>
#include"pFind_PairResearch.h"
#include"pQuant.h"
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;
typedef unordered_map<string, int> Map;
typedef vector<spectra> sp;
typedef vector<pquant> pq;
bool SortbyFScore(spectra& a, spectra&b) { return a.final_score < b.final_score; }
string spectraname{ "Hep3B_2.spectra" };
string pquantname{ "Hep3B_2.spectra.list" };
string outname{ "Hep3B_2.best100" };
int main() {
	ifstream inspectra(spectraname);
	if (!inspectra.is_open())
	{
		cout << "spectra文件打开失败，请按任意键结束程序。";
		cin.get();
		exit(EXIT_FAILURE);
	}
	sp splist;
	string title1;
	getline(inspectra, title1);
	inspectra >> splist;
	ifstream inpquant(pquantname);
	if (!inpquant.is_open())
	{
		cout << "pquant文件打开失败，请按任意键结束程序。";
		cin.get();
		exit(EXIT_FAILURE);
	}
	pq pqlist; 
	string title2;
	getline(inpquant, title2);
	inpquant >> pqlist;
	sort(splist.begin(), splist.end(), SortbyFScore);
	Map map;
	for (int i=0;i<pqlist.size();i++)
	{
		if (map.find(pqlist[i].name_ms2) == map.end())
			map[pqlist[i].name_ms2] = i;
	}
	//random_shuffle(splist.begin(), splist.end());//乱序
	ofstream out(outname);
	out << title1 << endl;
	for (int i = 0,count=0; i<splist.size()&&count<100;i++)
	{
		if (map.find(splist[i].file_name) != map.end())
		{
			splist[i].ratio = pqlist[map[splist[i].file_name]].ratio;
			splist[i].intensity1 = pqlist[map[splist[i].file_name]].inten_s1;
			splist[i].intensity2 = pqlist[map[splist[i].file_name]].inten_s2;
			count++;
		}	
		out << splist[i] << endl;
		cout << i << endl;
	}
	return 0;
}
