/*
Pseudo-code:


getline(str);
int index = 0;
for (int i = 0; i<str.length();i++)
{
	switch(index) {
		case 0: 
	
*/

#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Day {
protected:
	int day;
	double volts[24][60];
public:
	Day(int); 
	Day();
	void setDay(int);
	void setHMV(int h, int m, double v); //turn d,h,m,V\n into array
	//int getDay(); // returns day no.
	void printDay(string, int, int, int, int);
};

class Reader : public Day {
private:
	int fileN;
	int d0;
	int h0;
	int m0;
	int interval;
	string *file;
public:
	Day *days;
	Reader(int n, int nd, int d, int h, int m, int in);
	void parse(string, int, double(&dhmV)[4]);
	void read();
	~Reader();
};


int main()
{
	Reader reader(48, 2, 26, 21, 56, 30);
	reader.days[1].printDay("datatest.csv", 0, 0, 21, 56);
    return 0;
}


Day::Day(int d)
{
	day = d;
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			volts[i][j] = ',';
		}
	}
}
Day::Day()
{
	/*for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			volts[i][j] = ',';
		}
	}*/
}
void Day::setDay(int d)
{
	day = d;
	return;
}
void Day::setHMV(int h, int m, double V)
{
	volts[h][m] = V;
	return;
}
void Day::printDay(string fileName, int startH, int startM, int endH, int endM)
{
	ofstream output;
	output.open(fileName);
	for (int h = startH; h <= endH; h++)
	{
		for (int i = 0; i < 60; i++)
		{
			output << h*60 + i << ',';
		}
	}
	output << endl;
	for (int h = startH; h <= endH; h++)
	{
		for (int m = 0; m < 60; m++)
		{
			output << volts[h][m] << ',';
		}
	}
	output << "\n\n";
	for (int h = startH; h <= endH; h++)
	{
		for (int i = 0; i < 12; i++)
		{
			output << h << ':' << 5*i << ',' ;
		}
	}
	output << endl;
	double sum;
	for (int h = startH; h <= endH; h++)
	{
		for (int i = 0; i < 12; i++)
		{
			sum = 0;
			for (int m = i*5; m < i*5 + 5; m++)
			{
				sum += volts[h][m];
			}
			output << sum / 5.000 << ',';
		}
	}
}

Reader::Reader(int n, int nd, int d, int h, int m, int in)
{
	days = new Day[nd];
	file = new string[n];
	d0 = d;
	h0 = h;
	m0 = m;
	interval = in;
	fileN = n;
	for (int i = 0; i < nd; i++)
	{
		days[i].setDay(d0 + i);
	}
	file[0] = "data" + to_string(d0) + '_' + to_string(h0) + "h" + to_string(m0) + "m.csv";
	cout << file[0] << endl;
	int di = d0, hi = h0, mi = m0;
	for (int i = 1; i < n; i++)
	{
		mi += interval;
		if (mi > 59)
		{
			mi -= 60;
			hi += 1;
			if (hi > 23)
			{
				hi -= 24;
				di += 1;
			}
		}
		file[i] = "C:\\Users\\Gabriel\\Documents\\_Spring 2018\\BBE\\Arduino_Voltmeter\\data" + to_string(di) + '_' + to_string(hi) + "h" + to_string(mi) + "m.csv";
		cout << file[i] + '\n';
	}
	read();
	return;
}
Reader::~Reader()
{
	delete[] days;
	delete[] file;
}

void Reader::parse(string str, int index, double(&dhmV)[4])
{
	if (index == 0)
	{
		dhmV[index] = stod(str);
		return;
	}
	size_t loc = str.find_last_of(',');
	dhmV[index] = stod(str.substr(loc + 1));
	parse(str.substr(0, loc), index - 1, dhmV);
	return;
}

void Reader::read()
{
	double dhmV[4];
	string str;
	for (size_t i = 0; i < fileN; i++)
	{
		ifstream input(file[i].c_str(),ifstream::in);
		if (input.good())
		{
			for (int j = 0; j < 30; j++)
			{
				if (getline(input, str))
				{
					cout << str << endl;
					parse(str, 3, dhmV);
					days[(int)dhmV[0] - d0].setHMV(dhmV[1], dhmV[2], dhmV[3]);
				}
			}
		}
	}
}
//26,23,57,0
