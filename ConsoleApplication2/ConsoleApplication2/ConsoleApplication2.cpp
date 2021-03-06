// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <sstream>
using namespace std;

struct ranges
{
	int Xhurmin = 0;//hurtbox
	int Xhurmax = 0;
	int Xhitmin = 0;//hitbox
	int Xhitmax = 0;
	int Xspikemin = 0;//spike
	int Xspikemax = 0;
	int XSAmin = 0;//super armor
	int XSAmax = 0;
	int XWBmin = 0;//windbox
	int XWBmax = 0;
	int Xgrabmin = 0;//grab box
	int Xgrabmax = 0;
	int Xreflectmin = 0;//reflector
	int Xreflectmax = 0;
	int Xscanmin = 0;//scan
	int Xscanmax = 0;

	int Yhurmin = 0;
	int Yhurmax = 0;
	int Yhitmin = 0;
	int Yhitmax = 0;
	int YhitminR = 0;
	int YhitmaxR = 0;
	int YhitminL = 0;
	int YhitmaxL = 0;
	int Yspikemin = 0;
	int Yspikemax = 0;
	int YSAmin = 0;
	int YSAmax = 0;
	int YWBmin = 0;
	int YWBmax = 0;
	int Ygrabmin = 0;
	int Ygrabmax = 0;
	int Yreflectmin = 0;
	int Yreflectmax = 0;
	int Yscanmin = 0;
	int Yscanmax = 0;


};

void StandData(int &Xsizemin, int &Xsizemax, int &Ysizemin, int &Ysizemax, vector<ranges> &standdata)
{
	Xsizemin = 0;
	Xsizemax = 0;
	Ysizemin = 0;
	Ysizemax = 0;

	for (int i = 0; i < standdata.size(); i++)
	{
		Xsizemin = Xsizemin + standdata[i].Xhurmin;
		Xsizemax = Xsizemax + standdata[i].Xhurmax;
		Ysizemin = Ysizemin + standdata[i].Yhurmin;
		Ysizemax = Ysizemax + standdata[i].Yhurmax;
	}

	Xsizemin = Xsizemin / standdata.size();
	Xsizemax = Xsizemax / standdata.size();
	Ysizemin = Ysizemin / standdata.size();
	Ysizemax = Ysizemax / standdata.size();
}

void MvCSim(int &move1_disjRight, int &move1_disjLeft, int &move1_disjUp, int &move1_disjDown, int &move1_hitstart, int &move1_hitend, int &move1_extRight_start, int &move1_extLeft_start, int &move1_extUp_start, int &move1_extDown_start, int &move1_extUp_max, int &move1_extDown_max, int &move1_extUp_maxFRAME, int &move1_extDown_maxFRAME, int & move1_extRight_max, int & move1_extLeft_max, vector<int> &move1_multihit, bool &hitactive1, vector<int> &move1_misshigh, vector<int> &move1_misslow, bool &hitright1, bool &hitleft1, bool &complicated, vector<ranges> &move1data, int &Xsizemax1, int &Xsizemin1, int &Ysizemax1, int &Ysizemin1, int &Ysizemax2, int &Ysizemin2, bool aerial1)//, int &move1_extUp_maxRight, int &move1_extDown_maxRight, int &move1_extUp_maxLeft, int &move1_extDown_maxLeft)
{
	for (int i = 1; i < move1data.size(); i++)
	{
		if (move1data[i].Xhitmax != -1)//if hitbox active
		{
			if (move1_extRight_max == -1 || move1data[i].Xhitmax > move1data[move1_extRight_max].Xhitmax)
			{
				move1_extRight_max = i;
			}
			if (move1_extLeft_max == -1 || move1data[i].Xhitmin < move1data[move1_extLeft_max].Xhitmin)
			{
				move1_extLeft_max = i;
			}
			if (aerial1 == false)//done from standing perspective
			{
				if (move1data[i].Yhitmax < move1_extUp_max || move1_extUp_max == -1)
				{
					move1_extUp_max = move1data[i].Yhitmax;
					move1_extUp_maxFRAME = i;
				}
				if (move1data[i].Yhitmin > move1_extDown_max || move1_extDown_max == -1)
				{
					move1_extDown_max = move1data[i].Yhitmin;
					move1_extDown_maxFRAME = i;
				}
				if (move1data[i].Yhitmin < Ysizemax2)
				{
					move1_misshigh.push_back(i);
					complicated = true;
					//cout << "\n move 1 is too high (stand) \n";
				}
				else if (move1data[i].Yhitmax > Ysizemin2)
				{
					move1_misslow.push_back(i);
					complicated = true;
					//cout << "\n move 1 is too high (stand) \n";
				}
				else
				{
					if (move1data[i].Xhitmax > Xsizemax1)//move does hit at some point... replace with new data?
					{
						hitright1 = true;
					}
					if (move1data[i].Xhitmin < Xsizemin1)
					{
						hitleft1 = true;
					}

				}
			}
			else//done from when hitbox touches ground perspective
			{
				if ((move1data[i].Yhitmax - (move1data[i].Yhurmin - 917)) < move1_extUp_max || move1_extUp_max == -1)
				{
					move1_extUp_max = move1data[i].Yhitmax - (move1data[i].Yhurmin - 917);
					move1_extUp_maxFRAME = i;
				}
				if ((move1data[i].Yhitmin - (move1data[i].Yhurmin - 917)) > move1_extDown_max || move1_extDown_max == -1)
				{
					move1_extDown_max = move1data[i].Yhitmin - (move1data[i].Yhurmin - 917);
					move1_extDown_maxFRAME = i;
				}
				if ((move1data[i].Yhitmin - (move1data[i].Yhurmin - 917)) < Ysizemax2)
				{
					move1_misshigh.push_back(i);
					complicated = true;
					//cout << "\n move 1 is too high (stand) \n";
				}
				else if ((move1data[i].Yhitmax - (move1data[i].Yhurmin - 917))> Ysizemin2)
				{
					move1_misslow.push_back(i);
					complicated = true;
					//cout << "\n move 1 is too high (stand) \n";
				}
				else
				{
					if (move1data[i].Xhitmax > Xsizemax1)
					{
						hitright1 = true;
					}
					if (move1data[i].Xhitmin < Xsizemin1)
					{
						hitleft1 = true;
					}

				}
			}


			if (hitactive1 == false)
			{
				move1_multihit.push_back(i);
				hitactive1 = true;
			}
			if (move1_hitstart == -1)
			{
				move1_hitstart = i;
			}
			move1_hitend = i;

			if (move1data[i].Xhitmax > Xsizemax1 && move1_extRight_start == -1)
			{
				move1_extRight_start = i;
			}
			if (move1data[i].Xhitmin < Xsizemin1 && move1_extLeft_start == -1)
			{
				move1_extLeft_start = i;
			}
			if (move1data[i].Yhitmax < Ysizemax1 && move1_extUp_start == -1)
			{
				move1_extUp_start = i;
			}
			if (move1data[i].Yhitmin > Ysizemin1 && move1_extDown_start == -1)
			{
				move1_extDown_start = i;
			}
			if (move1data[i].Xhurmax != -1)
			{
				if (move1_disjRight == -1)
				{
					move1_disjRight = i;
					move1_disjLeft = i;
					move1_disjUp = i;
					move1_disjDown = i;
				}
				else
				{
					if (move1data[i].Xhitmax - move1data[i].Xhurmax > move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax)
					{
						move1_disjRight = i;
					}
					if (move1data[i].Xhurmin - move1data[i].Xhitmin > move1data[move1_disjLeft].Xhurmin - move1data[move1_disjLeft].Xhitmin)
					{
						move1_disjLeft = i;
					}
					if (move1data[i].Yhitmax - move1data[i].Yhurmax < move1data[move1_disjUp].Yhitmax - move1data[move1_disjUp].Yhurmax)
					{
						move1_disjUp = i;
					}
					if (move1data[i].Yhurmin - move1data[i].Yhitmin < move1data[move1_disjLeft].Yhurmin - move1data[move1_disjLeft].Yhitmin)
					{
						move1_disjDown = i;
					}
				}
			}
		}
		else
		{
			if (hitactive1 == true)
			{
				move1_multihit.push_back(i);
			}
			hitactive1 = false;
		}
	}
}

void MvMSim(vector<int> &move1_vsmisshigh, vector<int> &move1_vsmisslow, vector<int> &move2_vsmisshigh, vector<int> &move2_vsmisslow, int &move1_extDown_max, int &move1_extUp_max, int &move2_extDown_max, int &move2_extUp_max, bool &complicated, vector<ranges> &move1data, vector<ranges> &move2data)
{
	//cout << "inhere!" << endl;
	for (int i = 0; i < move2data.size(); i++)
	{
		//cout << move2data[i].Yhurmax << "  >?  " << move1_extDown_max << endl;
		if (move2data[i].Yhurmax > move1_extDown_max)
		{

			move1_vsmisshigh.push_back(i);
			complicated = true;
			//cout << "\n move 1 is too high \n";
		}
		if (move2data[i].Yhurmin < move1_extUp_max)
		{
			move1_vsmisslow.push_back(i);
			complicated = true;
			//cout << "\n move 1 is too low \n";
			//cout << i << endl << move2data[i].Yhurmax << endl << move2data[i].Yhurmin << endl << move1_extUp_max << endl << move1_extDown_max << endl;
		}
	}


	for (int i = 0; i < move1data.size(); i++)
	{
		if (move1data[i].Yhurmax > move2_extDown_max)
		{
			move2_vsmisshigh.push_back(i);
			complicated = true;
			//	cout << "\n move 2 is too high \n";
		}
		if (move1data[i].Yhurmin < move2_extUp_max)
		{
			move2_vsmisslow.push_back(i);
			complicated = true;
			//	cout << "\n move 2 is too low \n";
			//cout << i << endl << move1data[i].Yhurmax << endl << move1data[i].Yhurmin << endl << move2_extUp_max << endl << move2_extDown_max << endl;


		}
	}
}

int main(int argc, char* argv[])
{

	if (string(argv[2]).compare("vs"))
	{
		cout << "incorrect format \n" << endl;
		cout << "possible commands: \n \n";
		cout << "char_move vs char_move \n";

	}
	string char1 = "";
	string move1 = "";
	string char2 = "";
	string move2 = "";
	int strIndex = 0;

	while (argv[1][strIndex] != '_' && strIndex < string(argv[1]).length())
	{
		char1 = char1 + argv[1][strIndex];
		strIndex++;
	}

	if (strIndex != string(argv[1]).length())
	{
		strIndex++;
		while (strIndex < string(argv[1]).length())
		{
			move1 = move1 + argv[1][strIndex];
			strIndex++;
		}

	}

	strIndex = 0;

	while (argv[3][strIndex] != '_' && strIndex < string(argv[3]).length())
	{
		char2 = char2 + argv[3][strIndex];
		strIndex++;
	}

	if (strIndex != string(argv[3]).length())
	{
		strIndex++;
		while (strIndex < string(argv[3]).length())
		{
			move2 = move2 + argv[3][strIndex];
			strIndex++;
		}
	}

	//cout << char1 << endl << move1 << endl << char2 << endl << move2 << endl;
	bool aerial1 = false;
	bool aerial2 = false;
	string land1 = "landing";
	string land2 = "landing";

	if (!move1.compare("bair") || !move1.compare("fair") || !move1.compare("upair") || !move1.compare("dair") || !move1.compare("nair"))
	{
		aerial1 = true;
		land1 = land1 + move1;
	}
	if (!move2.compare("bair") || !move2.compare("fair") || !move2.compare("upair") || !move2.compare("dair") || !move2.compare("nair"))
	{
		aerial2 = true;
		land2 = land2 + move2;

	}


	string reader;
	string trash;
	string comparer = char1;
	ifstream in("sm4shrangedata.txt");
	bool charReader = false;
	bool breaker = false;
	string frames;
	ranges rangeman;
	vector<ranges> move1data;
	vector<ranges> move2data;
	vector<ranges> stand1data;
	vector<ranges> stand2data;
	vector<ranges> land1data;
	vector<ranges> land2data;
	string strtoint = "";
	in >> reader;


	int moveselect = 0;
	//READ IN DATA bool DataReader(vector<ranges> & move1data, vector<ranges> & move2data, vector<ranges> & stand1data, vector<ranges> & stand2data)

	while (moveselect < 2)
	{

		while (breaker == false && getline(in, frames))//might not work for char with only word, add space between char and :
		{
			if (in.fail())
			{
				cout << "character not here\n";
				return 0;
			}

			//cout << reader << endl;



			if (!reader.compare(comparer) && charReader == false)
			{
				charReader = true;
				comparer = "stand";

			}
			if (!reader.compare(comparer) && charReader == true)
			{
				breaker = true;
				//	in >> trash;
				//	cout << trash << endl;
				//	getline(in, frames);
				//	cout << frames;
			}
			in >> reader;
			in >> trash;
		}
		if (!frames.compare("missing") || !frames.compare(" missing"))
		{
			cout << comparer << " hitboxes not avalable\n";
		}
		else
		{
			strIndex = 0;
			while (strIndex < frames.length())
			{
				if (frames[strIndex] == ' ')
				{
					if (strIndex == 0)
					{
						//cout << "getline includes space as well: \n" << frames << endl;
						strIndex++;
					}
				}
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xhurmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xhurmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Yhurmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Yhurmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xhitmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xhitmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Yhitmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Yhitmax;
				/*
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				
				istringstream(strtoint) >> rangeman.YhitminR;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.YhitmaxR;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.YhitminL;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.YhitmaxL;
				*/
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xspikemin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xspikemax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Yspikemin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Yspikemax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.XSAmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.XSAmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.YSAmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.YSAmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.XWBmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.XWBmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.YWBmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.YWBmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xgrabmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xgrabmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Ygrabmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Ygrabmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xreflectmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xreflectmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Yreflectmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Yreflectmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xscanmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Xscanmax;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Yscanmin;
				strtoint = "";
				strIndex++;
				while (frames[strIndex] != ',')
				{
					strtoint = strtoint + frames[strIndex];
					strIndex++;
				}
				istringstream(strtoint) >> rangeman.Yscanmax;
				strtoint = "";
				strIndex++;
				if (frames[strIndex] == ' ')
				{
					if (moveselect == 0)
					{
						if (!comparer.compare("stand"))
						{

							stand1data.push_back(rangeman);
							if (!move1.compare("stand"))
							{
								move1data.push_back(rangeman);
							}
						}
						else if (!comparer.compare(land1) && aerial1 == true)
						{
							land1data.push_back(rangeman);
						}
						else
						{
							move1data.push_back(rangeman);
						}

					}
					else
					{
						if (!comparer.compare("stand"))
						{
							stand2data.push_back(rangeman);
							if (!move2.compare("stand"))
							{
								move2data.push_back(rangeman);
							}
						}
						else if (!comparer.compare(land2) && aerial2 == true)
						{
							land2data.push_back(rangeman);
						}
						else
						{
							move2data.push_back(rangeman);
						}
					}
					strIndex++;
				}
			}
		}
	
		charReader = false;
		breaker = false;
		if (!comparer.compare("stand"))
		{
			if (moveselect == 0)
			{
				comparer = move1;

			}
			else
			{
				comparer = move2;

			}
			charReader = true;
			if (!comparer.compare("stand"))
			{
				moveselect++;
				comparer = char2;
				in.clear();
				in.seekg(0, ios::beg);
				in >> reader;
			}
			//in >> reader;
		}
		else if ((moveselect == 0 && aerial1 && comparer.compare(land1)))
		{

			comparer = land1;
			charReader = true;
		}
		else if ((moveselect == 1 && aerial2 && comparer.compare(land2)))
		{
			comparer = land2;
			charReader = true;
			//in >> reader; 
		}
		else
		{
			charReader = false;
			breaker = false;
			moveselect++;
			comparer = char2;
			in.clear();
			in.seekg(0, ios::beg);
			in >> reader;



		}

	}



	//stand data getter move 1  bool StandData(int &Xsizemin, int &Xsizemax, &int Ysizemin, &int Ysizemax)
	int Xsizemin1 = 0;
	int Xsizemax1 = 0;
	int Ysizemin1 = 0;
	int Ysizemax1 = 0;

	int Xsizemin2 = 0;
	int Xsizemax2 = 0;
	int Ysizemin2 = 0;
	int Ysizemax2 = 0;
	StandData(Xsizemin1, Xsizemax1, Ysizemin1, Ysizemax1, stand1data);

	StandData(Xsizemin2, Xsizemax2, Ysizemin2, Ysizemax2, stand2data);

	int airerror1 = 917 - Ysizemin1;
	int airerror2 = 917 - Ysizemin2;






	//max disjoint finder move 1 (all below including vector<int> move#_vsmisshigh
	int move1_disjRight = -1;
	int move1_disjLeft = -1;
	int move1_disjUp = -1;
	int move1_disjDown = -1;

	int move1_hitstart = -1;
	int move1_hitend = -1;
	int move1_extRight_start = -1;
	int move1_extLeft_start = -1;
	int move1_extUp_start = -1;
	int move1_extDown_start = -1;
	int move1_extUp_max = -1;
	int move1_extDown_max = -1;
	int move1_extUp_maxFRAME = -1;
	int move1_extDown_maxFRAME = -1;
	int move1_extRight_max = -1;
	int move1_extLeft_max = -1;
	vector<int> move1_multihit;
	bool hitactive1 = false;
	vector<int> move1_misshigh;
	vector<int> move1_misslow;
	bool hitright1 = false;
	bool hitleft1 = false;

	int move2_disjRight = -1;
	int move2_disjLeft = -1;
	int move2_disjUp = -1;
	int move2_disjDown = -1;

	int move2_hitstart = -1;
	int move2_hitend = -1;
	int move2_extRight_start = -1;
	int move2_extLeft_start = -1;
	int move2_extUp_start = -1;
	int move2_extDown_start = -1;
	int move2_extUp_max = -1;
	int move2_extDown_max = -1;
	int move2_extUp_maxFRAME = -1;
	int move2_extDown_maxFRAME = -1;
	int move2_extRight_max = -1;
	int move2_extLeft_max = -1;
	vector<int> move2_multihit;
	bool hitactive2 = false;
	vector<int> move2_misshigh;
	vector<int> move2_misslow;
	bool hitright2 = false;
	bool hitleft2 = false;

	//int floor = 917;

	bool complicated = false;

	MvCSim(move1_disjRight, move1_disjLeft, move1_disjUp, move1_disjDown, move1_hitstart, move1_hitend, move1_extRight_start, move1_extLeft_start, move1_extUp_start, move1_extDown_start, move1_extUp_max, move1_extDown_max, move1_extUp_maxFRAME, move1_extDown_maxFRAME, move1_extRight_max, move1_extLeft_max, move1_multihit, hitactive1, move1_misshigh, move1_misslow, hitright1, hitleft1, complicated, move1data, Xsizemax1, Xsizemin1, Ysizemax1, Ysizemin1, Ysizemax2, Ysizemin2, aerial1);

	MvCSim(move2_disjRight, move2_disjLeft, move2_disjUp, move2_disjDown, move2_hitstart, move2_hitend, move2_extRight_start, move2_extLeft_start, move2_extUp_start, move2_extDown_start, move2_extUp_max, move2_extDown_max, move2_extUp_maxFRAME, move2_extDown_maxFRAME, move2_extRight_max, move2_extLeft_max, move2_multihit, hitactive2, move2_misshigh, move2_misslow, hitright2, hitleft2, complicated, move2data, Xsizemax2, Xsizemin2, Ysizemax2, Ysizemin2, Ysizemax1, Ysizemin1, aerial2);


	vector<int> move1_vsmisshigh;
	vector<int> move1_vsmisslow;
	vector<int> move2_vsmisshigh;
	vector<int> move2_vsmisslow;

	int move1_extUp_max_LANDTEST;
	int move2_extUp_max_LANDTEST;
	int move1_extDown_max_LANDTEST;
	int move2_extDown_max_LANDTEST;

	if (aerial1 == true && aerial2 == true)
	{
		MvMSim(move1_vsmisshigh, move1_vsmisslow, move2_vsmisshigh, move2_vsmisslow, move1_extDown_max, move1_extUp_max, move2_extDown_max, move2_extUp_max, complicated, land1data, land2data);
	}
	else if (aerial1 == true)
	{
		MvMSim(move1_vsmisshigh, move1_vsmisslow, move2_vsmisshigh, move2_vsmisslow, move1_extDown_max, move1_extUp_max, move2_extDown_max, move2_extUp_max, complicated, land1data, move2data);
	}
	else if (aerial2 == true)
	{
		MvMSim(move1_vsmisshigh, move1_vsmisslow, move2_vsmisshigh, move2_vsmisslow, move1_extDown_max, move1_extUp_max, move2_extDown_max, move2_extUp_max, complicated, move1data, land2data);

	}
	else
	{
		MvMSim(move1_vsmisshigh, move1_vsmisslow, move2_vsmisshigh, move2_vsmisslow, move1_extDown_max, move1_extUp_max, move2_extDown_max, move2_extUp_max, complicated, move1data, move2data);
	}
	//cout << land2data.size() << endl << move2data.size() << endl;
	//cout << move1_vsmisshigh.size() << endl;
	//cout << move2data.size() << endl;
	//cout << move1data.size() << endl;
	/*
	cout << move1_vsmisshigh.size() << endl;
	cout << move1_vsmisslow.size() << endl;
	cout << move2_vsmisshigh.size() << endl;
	cout << move2_vsmisslow.size() << endl;
	cout << move1_extUp_max<< endl;
	cout << move1_extDown_max << endl;
	*/



	cout << char1 << "\'s " << move1 << " info:" << endl;
	if (move1_hitstart != -1)
	{
		if (move1_multihit.size() > 2)
		{
			cout << "hitbox comes out on frames ";
			for (int i = 0; i < move1_multihit.size(); i += 2)
			{
				cout << move1_multihit[i] << " to " << move1_multihit[i + 1];
				if (i < move1_multihit.size() - 4)
				{
					cout << ", ";
				}
				else if (i < move1_multihit.size() - 4)
				{
					cout << " and ";
				}
				else
				{
					cout << endl;
				}

			}
		}
		else
		{
			cout << "hitbox first comes out on frame " << move1_hitstart + 1 << " and ends on frame " << move1_hitend + 1 << " (" << move1_hitend - move1_hitstart + 1 << " frames total)" << endl;
		}

		cout << "endlag lasts from frame " << move1_hitend + 2 << " to " << move1data.size() << " (" << move1data.size() - move1_hitend - 1 << " frames total)" << endl; // might not be accurate for things like landing lag and FAF
		cout << "hitbox first comes out ";
		if (move1_extRight_start == move1_hitstart && move1_extUp_start == move1_hitstart && move1_extLeft_start == move1_hitstart && move1_extDown_start == move1_hitstart)
		{
			cout << "on all sides of " << char1 << endl;
		}
		else
		{
			if (!(move1_extRight_start == move1_hitstart || move1_extUp_start == move1_hitstart || move1_extLeft_start == move1_hitstart || move1_extDown_start == move1_hitstart))
			{
				cout << "from inside of " << char1 << "\'s hurtbox" << endl;
			}
			else
			{
				cout << "on the";
				if (move1_extRight_start == move1_hitstart)
				{
					cout << " front";
				}
				if (move1_extUp_start == move1_hitstart)
				{
					cout << " top";
				}
				if (move1_extLeft_start == move1_hitstart)
				{
					cout << " back";
				}
				if (move1_extDown_start == move1_hitstart)
				{
					cout << " bottom";
				}
				cout << " side/sides of " << char1 << endl;
			}
		}

		if (move1_extRight_start != move1_hitstart && move1_extRight_start != -1)
		{
			cout << "Hitbox first extends right of " << char1 << "\'s standing position at frame " << move1_extRight_start << endl;
		}
		if (move1_extUp_start != move1_hitstart && move1_extUp_start != -1)
		{
			cout << "Hitbox first extends above " << char1 << "\'s standing position at frame " << move1_extUp_start << endl;
		}
		if (move1_extLeft_start != move1_hitstart && move1_extLeft_start != -1)
		{
			cout << "Hitbox first extends left of " << char1 << "\'s standing position at frame " << move1_extLeft_start << endl;
		}
		if (move1_extDown_start != move1_hitstart && move1_extDown_start != -1)
		{
			cout << "Hitbox first extends below " << char1 << "\'s standing position at frame " << move1_extDown_start << endl;
		}
	}
	else
	{
		cout << char1 << "\'s " << move1 << " contains no hitboxes" << endl;
	}

	cout << endl;
	cout << char2 << "\'s " << move2 << " info:" << endl;
	if (move2_hitstart != -1)
	{
		if (move2_multihit.size() > 2)
		{
			cout << "hitbox comes out on frames ";
			for (int i = 0; i < move2_multihit.size(); i += 2)
			{
				cout << move2_multihit[i] << " to " << move2_multihit[i + 1];
				if (i < move2_multihit.size() - 4)
				{
					cout << ", ";
				}
				else if (i < move2_multihit.size() - 2)
				{
					cout << " and ";
				}
				else
				{
					cout << endl;
				}

			}
		}
		else
		{
			cout << "hitbox first comes out on frame " << move2_hitstart + 1 << " and ends on frame " << move2_hitend + 1 << " (" << move2_hitend - move2_hitstart + 1 << " frames total)" << endl;
		}

		cout << "endlag lasts from frame " << move2_hitend + 2 << " to " << move2data.size() << " (" << move2data.size() - move2_hitend << " frames total)" << endl; // might not be accurate for things like landing lag and FAF
		cout << "hitbox first comes out ";
		if (move2_extRight_start == move2_hitstart && move2_extUp_start == move2_hitstart && move2_extLeft_start == move2_hitstart && move2_extDown_start == move2_hitstart)
		{
			cout << "on all sides of " << char2 << endl;
		}
		else
		{
			if (!(move2_extRight_start == move2_hitstart || move2_extUp_start == move2_hitstart || move2_extLeft_start == move2_hitstart || move2_extDown_start == move2_hitstart))
			{
				cout << "from inside of " << char2 << "\'s hurtbox" << endl;
			}
			else
			{
				cout << "on the";
				if (move2_extRight_start == move2_hitstart)
				{
					cout << " front";
				}
				if (move2_extUp_start == move2_hitstart)
				{
					cout << " top";
				}
				if (move2_extLeft_start == move2_hitstart)
				{
					cout << " back";
				}
				if (move2_extDown_start == move2_hitstart)
				{
					cout << " bottom";
				}
				cout << " side/sides of " << char2 << endl;
			}
		}


		if (move2_extRight_start != move2_hitstart && move2_extRight_start != -1)
		{
			cout << "Hitbox first extends right of " << char2 << "\'s standing position at frame " << move2_extRight_start << endl;
		}
		if (move2_extUp_start != move2_hitstart && move2_extUp_start != -1)
		{
			cout << "Hitbox first extends above " << char2 << "\'s standing position at frame " << move2_extUp_start << endl;
		}
		if (move2_extLeft_start != move2_hitstart && move2_extLeft_start != -1)
		{
			cout << "Hitbox first extends left of " << char2 << "\'s standing position at frame " << move2_extLeft_start << endl;
		}
		if (move2_extDown_start != move2_hitstart && move2_extDown_start != -1)
		{
			cout << "Hitbox first extends below " << char2 << "\'s standing position at frame " << move2_extDown_start << endl;
		}
	}
	else
	{
		cout << char2 << "\'s " << move2 << " contains no hitboxes" << endl;
	}

	if (((move1_misshigh.size() != 0 || move1_misslow.size() != 0 || move1_vsmisshigh.size() != 0 || move1_vsmisslow.size() != 0) && (move1_hitstart != -1)) || ((move2_misshigh.size() != 0 || move2_misslow.size() != 0 || move2_vsmisshigh.size() != 0 || move2_vsmisslow.size() != 0) && move2_hitstart != -1))
	{
		cout << endl;
		cout << char1 << "\'s " << move1 << " vs " << char2 << "\'s " << move2 << "horizontal info:" << endl;
		//cout << move1_vsmisshigh.size() << endl;

		if (move1_hitstart != -1)
		{
			if (move1_misslow.size() != 0)
			{
				if (move1_misshigh.size() >= move1_hitend - move1_hitstart + 1)
				{
					cout << "Due to height differences between " << char1 << "\'s " << move1 << " and " << char2 << ", " << char1 << "\'s " << move1 << " is unable to hit a standing " << char2 << " at any point," << endl;
				}
				else
				{
					cout << "Due to height differences between " << char1 << "\'s " << move1 << " and " << char2 << ", " << char1 << "\'s " << move1 << " will miss a standing " << char2 << " from frames ";
					cout << move1_misshigh[0];
					for (int i = 1; i < move1_misshigh.size(); i++)
					{
						if (i == move1_misshigh.size() - 1)
						{
							if (move1_misshigh[i] == move1_misshigh[i - 1] + 1)
							{
								cout << " to " << move1_misshigh[i];
							}
							else
							{
								cout << ", " << move1_vsmisshigh[i];
							}
						}
						else if (move1_misshigh[i] + 1 < move1_misshigh[i + 1])
						{
							if (move1_misshigh[i] > move1_misshigh[i - 1] + 1)
							{
								cout << ", " << move1_misshigh[i + 1];
							}
							else
							{
								cout << " to " << move1_misshigh[i] << ", " << move1_misshigh[i + 1];
							}

						}
					}
					cout << " of " << char1 << "\'s " << move1 << endl;

					if (hitright1 == false && move1_extRight_start != -1 && hitleft1 == false && move1_extLeft_start != -1)//if both arrays are empty and 
					{
						cout << char1 << "\'s " << move1 << " can not hit " << char2 << " on both the front and back sides";
					}
					else
					{
						if (hitright1 == false && move1_extRight_start != -1)//if array is empty
						{
							cout << char1 << "\'s " << move1 << " can not hit " << char2 << " from the front side";
						}
						if (hitleft1 == false && move1_extLeft_start != -1)
						{
							cout << char1 << "\'s " << move1 << " can not hit " << char2 << " from the back side";
						}
					}
					cout << endl;
				}
			}







			if (move1_vsmisshigh.size() != 0)
			{
				if (((move1_vsmisshigh.size() >= move2data.size()) && aerial1 == false) || ((move1_vsmisshigh.size() >= land2data.size()) && aerial1 == true))
				{
					cout << "Due to height differences between " << char1 << "\'s " << move1 << " and " << char2 << "\'s " << move2 << ", " << char1 << "\'s " << move1 << " is unable to hit " << char2 << " at any point," << endl;
				}
				else
				{
					cout << "Due to height differences between " << char1 << "\'s " << move1 << " and " << char2 << "\'s " << move2 << ", " << char1 << "\'s " << move1 << " will miss " << char2 << " durring frames ";
					cout << move1_vsmisshigh[0];
					for (int i = 1; i < move1_vsmisshigh.size(); i++)
					{
						if (i == move1_vsmisshigh.size() - 1)
						{
							if (move1_vsmisshigh[i] == move1_vsmisshigh[i - 1] + 1)
							{
								cout << " to " << move1_vsmisshigh[i];
							}
							else
							{
								cout << ", " << move1_vsmisshigh[i];
							}
						}
						else if (move1_vsmisshigh[i] + 1 < move1_vsmisshigh[i + 1])
						{
							if (move1_vsmisshigh[i] > move1_vsmisshigh[i - 1] + 1)
							{
								cout << ", " << move1_vsmisshigh[i + 1];
							}
							else
							{
								cout << " to " << move1_vsmisshigh[i] << ", " << move1_vsmisshigh[i + 1];
							}

						}
					}
					cout << " of " << char2 << "\'s ";
					if (aerial2 == true)
					{
						cout << "landing ";
					}
					cout << move2 << "," << endl;
				}
				cout << "due to " << char2 << " being too low (could be that the top of " << char2 << " becomes intangible)" << endl;

			}
			if ((move1_misshigh.size() != 0 || move1_vsmisshigh.size() != 0) && aerial1 == true && airerror1 > 0)
			{
				cout << "(potential height error of about " << airerror1 << " pixels, depending on how " << char1 << " lands)" << endl << endl;
			}
			if (aerial1 == false)
			{
				if (move1_vsmisslow.size() != 0)
				{
					if (move1_vsmisslow.size() >= move2_hitend - move2_hitstart + 1)
					{
						cout << "Due to height differences between " << char1 << "\'s " << move1 << " and " << char2 << "\'s " << move2 << ", " << char1 << "\'s " << move1 << " is unable to hit " << char2 << " at any point," << endl;
					}
					else
					{
						cout << "Due to height differences between " << char1 << "\'s " << move1 << " and " << char2 << "\'s " << move2 << ", " << char1 << "\'s " << move1 << " will miss " << char2 << " durring frames ";
						cout << move1_vsmisslow[0];
						for (int i = 1; i < move1_vsmisslow.size(); i++)
						{
							if (i == move1_vsmisslow.size() - 1)
							{
								if (move1_vsmisslow[i] == move1_vsmisslow[i - 1] + 1)
								{
									cout << " to " << move1_vsmisslow[i];
								}
								else
								{
									cout << ", " << move1_vsmisslow[i];
								}
							}
							else if (move1_vsmisslow[i] + 1 < move1_vsmisslow[i + 1])
							{
								if (move1_vsmisslow[i] > move1_vsmisslow[i - 1] + 1)
								{
									cout << ", " << move1_vsmisslow[i + 1];
								}
								else
								{
									cout << " to " << move1_vsmisslow[i] << ", " << move1_vsmisslow[i + 1];
								}

							}
						}
						cout << " of " << char2 << "\'s " << move2 << "," << endl;
					}
					cout << "due to " << char2 << " being too high (could be that the bottom of " << char2 << " becomes intangible)" << endl;
				}

			}

		}

		if (move2_hitstart != -1)
		{

			if (move2_misshigh.size() != 0)
			{
				if (move2_misshigh.size() >= move2_hitend - move2_hitstart + 1)
				{
					cout << "Due to height differences between " << char2 << "\'s " << move2 << " and " << char1 << ", " << char2 << "\'s " << move2 << " is unable to hit a standing " << char1 << " at any point," << endl;
				}
				else
				{
					cout << "Due to height differences between " << char2 << "\'s " << move2 << " and " << char1 << ", " << char2 << "\'s " << move2 << " will miss a standing " << char1 << " from frames ";
					cout << move2_misshigh[0];
					for (int i = 1; i < move2_misshigh.size(); i++)
					{
						if (i == move2_misshigh.size() - 1)
						{
							if (move2_misshigh[i] == move2_misshigh[i - 1] + 1)
							{
								cout << " to " << move2_misshigh[i];
							}
							else
							{
								cout << ", " << move2_vsmisshigh[i];
							}
						}
						else if (move2_misshigh[i] + 1 < move2_misshigh[i + 1])
						{
							if (move2_misshigh[i] > move2_misshigh[i - 1] + 1)
							{
								cout << ", " << move2_misshigh[i + 1];
							}
							else
							{
								cout << " to " << move2_misshigh[i] << ", " << move2_misshigh[i + 1];
							}

						}
					}
					cout << " of " << char2 << "\'s " << move2 << endl;

					if (hitright2 == false && move2_extRight_start != -1 && hitleft2 == false && move2_extLeft_start != -1)
					{
						cout << char2 << "\'s " << move2 << " can not hit " << char1 << " on both the front and back sides";
					}
					else
					{
						if (hitright2 == false && move2_extRight_start != -1)
						{
							cout << char2 << "\'s " << move2 << " can not hit " << char1 << " from the front side";
						}
						if (hitleft2 == false && move2_extLeft_start != -1)
						{
							cout << char2 << "\'s " << move2 << " can not hit " << char1 << " from the back side";
						}
					}
					cout << endl;
				}
			}






			if (move2_vsmisshigh.size() != 0)
			{
				if (((move2_vsmisshigh.size() >= move1data.size()) && aerial2 == false) || ((move2_vsmisshigh.size() >= land1data.size()) && aerial2 == true))
				{
					cout << "Due to height differences between " << char2 << "\'s " << move2 << " and " << char1 << "\'s " << move1 << ", " << char2 << "\'s " << move2 << " is unable to hit " << char1 << " at any point," << endl;
				}
				else
				{
					cout << "Due to height differences between " << char2 << "\'s " << move2 << " and " << char1 << "\'s " << move1 << ", " << char2 << "\'s " << move2 << " will miss " << char1 << " durring frames ";
					cout << move2_vsmisshigh[0];
					for (int i = 1; i < move2_vsmisshigh.size(); i++)
					{
						if (i == move2_vsmisshigh.size() - 1)
						{
							if (move2_vsmisshigh[i] == move2_vsmisshigh[i - 1] + 1)
							{
								cout << " to " << move2_vsmisshigh[i];
							}
							else
							{
								cout << ", " << move2_vsmisshigh[i];
							}
						}
						else if (move2_vsmisshigh[i] + 1 < move2_vsmisshigh[i + 1])
						{
							if (move2_vsmisshigh[i] > move2_vsmisshigh[i - 1] + 1)
							{
								cout << ", " << move2_vsmisshigh[i + 1];
							}
							else
							{
								cout << " to " << move2_vsmisshigh[i] << ", " << move2_vsmisshigh[i + 1];
							}

						}
					}
					cout << " of " << char1 << "\'s ";
					if (aerial1 == true)
					{
						cout << "landing ";
					}
					cout << move1 << "," << endl;
				}
				cout << "due to " << char1 << " being too low (could be that the top of " << char1 << " becomes intangible)" << endl;
			}
			if ((move2_misshigh.size() != 0 || move2_vsmisshigh.size() != 0) && aerial2 == true && airerror2 > 0)
			{
				cout << "(potential height error of about " << airerror2 << " pixels, depending on how " << char2 << " lands)" << endl << endl;
			}

			if (aerial2 == false)
			{
				if (move2_vsmisslow.size() != 0)
				{
					if (move2_vsmisslow.size() >= move1_hitend - move1_hitstart + 1)
					{
						cout << "Due to height differences between " << char2 << "\'s " << move2 << " and " << char1 << "\'s " << move1 << ", " << char2 << "\'s " << move2 << " is unable to hit " << char1 << " at any point," << endl;
					}
					else
					{
						cout << "Due to height differences between " << char2 << "\'s " << move2 << " and " << char1 << "\'s " << move1 << ", " << char2 << "\'s " << move2 << " will miss " << char1 << " durring frames ";
						cout << move2_vsmisslow[0];
						for (int i = 1; i < move2_vsmisslow.size(); i++)
						{
							if (i == move2_vsmisslow.size() - 1)
							{
								if (move2_vsmisslow[i] == move2_vsmisslow[i - 1] + 1)
								{
									cout << " to " << move2_vsmisslow[i];
								}
								else
								{
									cout << ", " << move2_vsmisslow[i];
								}
							}
							else if (move2_vsmisslow[i] + 1 < move2_vsmisslow[i + 1])
							{
								if (move2_vsmisslow[i] > move2_vsmisslow[i - 1] + 1)
								{
									cout << ", " << move2_vsmisslow[i + 1];
								}
								else
								{
									cout << " to " << move2_vsmisslow[i] << ", " << move2_vsmisslow[i + 1];
								}

							}
						}
						cout << " of " << char1 << "\'s " << move1 << "," << endl;
					}
					cout << "due to " << char1 << " being too high (could be that the bottom of " << char1 << " becomes intangible)" << endl;
				}
			}
		}

	}
	cout << endl;
	if (complicated == true)
	{
		cout << " (note where moves may whiff from above)" << endl;
	}
	if (move1_hitstart != -1 && move2_hitstart != -1)
	{
		cout << "In terms of disjoints:" << endl;


		if (move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax > move2data[move2_disjRight].Xhitmax - move2data[move2_disjRight].Xhurmax)//normal
		{
			cout << char1 << "\'s " << move1 << "(frame " << move1_disjRight + 1 << ") will beat out " << char2 << "\'s " << move2 << "(frame " << move2_disjRight + 1 << ") by " << (move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax) - (move2data[move2_disjRight].Xhitmax - move2data[move2_disjRight].Xhurmax) << " pixels" << endl;
		}
		else if (move2data[move2_disjRight].Xhitmax - move2data[move2_disjRight].Xhurmax > move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax)
		{
			cout << char2 << "\'s " << move2 << "(frame " << move2_disjRight + 1 << ") will beat out " << char1 << "\'s " << move1 << "(frame " << move1_disjRight + 1 << ") by " << (move2data[move2_disjRight].Xhitmax - move2data[move2_disjRight].Xhurmax) - (move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax) << " pixels" << endl;
		}
		else
		{
			cout << "both " << char1 << "\'s " << move1 << "(frame " << move1_disjRight + 1 << ") and " << char2 << "\'s " << move2 << "(frame " << move2_disjRight + 1 << ") are equally disjointed!" << endl;
		}
		if (move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin > 0)//move 2 has reverse
		{
			if (move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax > move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin)
			{
				cout << char1 << "\'s " << move1 << "(frame " << move1_disjRight + 1 << ") will beat out " << char2 << "\'s reverse " << move2 << "(frame " << move2_disjLeft + 1 << ") by " << move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax - (move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin) << " pixels" << endl;
			}
			else if (move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax < move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin)
			{
				cout << char2 << "\'s reverse " << move2 << "(frame " << move2_disjLeft + 1 << ") will beat out " << char1 << "\'s " << move1 << "(frame " << move1_disjRight + 1 << ") by " << (move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin) - (move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax) << " pixels" << endl;
			}
			else
			{
				cout << "both " << char1 << "\'s " << move1 << "(frame " << move1_disjRight + 1 << ") and " << char2 << "\'s  reverse " << move2 << "(frame " << move2_disjLeft + 1 << ") are equally disjointed!" << endl;
			}
		}

		if (move1data[move1_disjLeft].Xhurmin - move1data[move1_disjLeft].Xhitmin > 0)//move 1 has reverse
		{
			if (move2data[move2_disjRight].Xhitmax - move2data[move2_disjRight].Xhurmax > move1data[move1_disjLeft].Xhurmin - move1data[move1_disjLeft].Xhitmin)
			{
				cout << char2 << "\'s " << move2 << "(frame " << move2_disjRight + 1 << ") will beat out " << char1 << "\'s reverse " << move1 << "(frame " << move1_disjLeft + 1 << ") by " << (move2data[move2_disjRight].Xhitmax - move2data[move2_disjRight].Xhurmax) - (move1data[move1_disjLeft].Xhurmin - move1data[move1_disjLeft].Xhitmin) << " pixels" << endl;
			}
			else if (move2data[move2_disjRight].Xhitmax - move2data[move2_disjRight].Xhurmax < move1data[move1_disjLeft].Xhurmin - move1data[move1_disjLeft].Xhitmin)
			{
				cout << char1 << "\'s reverse " << move1 << "(frame " << move1_disjLeft + 1 << ") will beat out " << char2 << "\'s " << move2 << "(frame " << move2_disjRight + 1 << ") by " << (move1data[move1_disjLeft].Xhurmin - move1data[move1_disjLeft].Xhitmin) - (move2data[move2_disjRight].Xhitmax - move2data[move2_disjRight].Xhurmax) << " pixels" << endl;
			}
			else
			{
				cout << "both " << char1 << "\'s  reverse " << move1 << "(frame " << move1_disjLeft + 1 << ") and " << char2 << "\'s " << move2 << "(frame " << move2_disjRight + 1 << ") are equally disjointed!" << endl;
			}



			if (move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin > 0)//move 1 and 2 have reverse
			{
				if (move1data[move1_disjLeft].Xhurmin - move1data[move1_disjLeft].Xhitmin > move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin)
				{
					cout << char1 << "\'s reverse " << move1 << "(frame " << move1_disjLeft + 1 << ") will beat out " << char2 << "\'s reverse " << move2 << "(frame " << move2_disjLeft + 1 << ") by " << (move1data[move1_disjLeft].Xhurmin - move1data[move1_disjLeft].Xhitmin) - (move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin) << " pixels" << endl;
				}
				else if (move1data[move1_disjLeft].Xhurmin - move1data[move1_disjLeft].Xhitmin < move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin)
				{
					cout << char2 << "\'s reverse " << move2 << "(frame " << move2_disjLeft + 1 << ") will beat out " << char1 << "\'s reverse " << move1 << "(frame " << move1_disjLeft + 1 << ") by " << (move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin) - (move1data[move1_disjLeft].Xhurmin - move1data[move1_disjLeft].Xhitmin) << " pixels" << endl;
				}
				else
				{
					cout << "both " << char1 << "\'s reverse " << move1 << "(frame " << move1_disjLeft + 1 << ") and " << char2 << "\'s  reverse " << move2 << "(frame " << move2_disjLeft + 1 << ") are equally disjointed!" << endl;
				}
			}
		}
		cout << endl;
	}
	//cout << endl << move1_hitstart << " " << move2_hitstart << endl;
	if (move1_hitstart != -1 && move2_hitstart != -1)
	{
		cout << "In terms of hitbox extension:" << endl;


		if (move1data[move1_extRight_max].Xhitmax - Xsizemax1 > move2data[move2_extRight_max].Xhitmax - Xsizemax2)//normal
		{
			cout << char1 << "\'s " << move1 << "(frame " << move1_extRight_max + 1 << ") extends further than " << char2 << "\'s " << move2 << "(frame " << move2_extRight_max + 1 << ") by " << (move1data[move1_extRight_max].Xhitmax - move1data[move1_extRight_max].Xhurmax) - (move2data[move2_extRight_max].Xhitmax - move2data[move2_extRight_max].Xhurmax) << " pixels" << endl;
		}
		else if (move2data[move2_extRight_max].Xhitmax - Xsizemax2 > move1data[move1_extRight_max].Xhitmax - Xsizemax1)
		{
			cout << char2 << "\'s " << move2 << "(frame " << move2_extRight_max + 1 << ") extends further than " << char1 << "\'s " << move1 << "(frame " << move1_extRight_max + 1 << ") by " << (move2data[move2_extRight_max].Xhitmax - move2data[move2_extRight_max].Xhurmax) - (move1data[move1_extRight_max].Xhitmax - move1data[move1_extRight_max].Xhurmax) << " pixels" << endl;
			cout << endl << char2 << " " << move2 << " " << move1 << endl;
		}
		else
		{
			cout << "both " << char1 << "\'s " << move1 << "(frame " << move1_extRight_max + 1 << ") and " << char2 << "\'s " << move2 << "(frame " << move2_extRight_max + 1 << ") are equal in range!" << endl;
		}
		if (move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin > 0)//move 2 has reverse
		{
			if (move1data[move1_extRight_max].Xhitmax - Xsizemax1 > Xsizemin2 - move2data[move2_extLeft_max].Xhitmin)
			{
				cout << char1 << "\'s " << move1 << "(frame " << move1_extRight_max + 1 << ") extends further than " << char2 << "\'s reverse " << move2 << "(frame " << move2_extLeft_max + 1 << ") by " << move1data[move1_extRight_max].Xhitmax - move1data[move1_extRight_max].Xhurmax - (move2data[move2_extLeft_max].Xhurmin - move2data[move2_extLeft_max].Xhitmin) << " pixels" << endl;
			}
			else if (move1data[move1_extRight_max].Xhitmax - Xsizemax1 < Xsizemin2 - move2data[move2_extLeft_max].Xhitmin)
			{
				cout << char2 << "\'s reverse " << move2 << "(frame " << move2_extLeft_max + 1 << ") extends further than " << char1 << "\'s " << move1 << "(frame " << move1_extRight_max + 1 << ") by " << (move2data[move2_extLeft_max].Xhurmin - move2data[move2_extLeft_max].Xhitmin) - (move1data[move1_extRight_max].Xhitmax - move1data[move1_extRight_max].Xhurmax) << " pixels" << endl;
			}
			else
			{
				cout << "both " << char1 << "\'s " << move1 << "(frame " << move1_extRight_max + 1 << ") and " << char2 << "\'s  reverse " << move2 << "(frame " << move2_extLeft_max + 1 << ") are equal in range!" << endl;
			}
		}

		if (move1data[move1_disjLeft].Xhurmin - move1data[move1_disjLeft].Xhitmin > 0)//move 1 has reverse
		{
			if (move2data[move2_extRight_max].Xhitmax - Xsizemax2 > Xsizemin1 - move1data[move1_extLeft_max].Xhitmin)
			{
				cout << char2 << "\'s " << move2 << "(frame " << move2_extRight_max + 1 << ") extends further than " << char1 << "\'s reverse " << move1 << "(frame " << move1_extLeft_max + 1 << ") by " << (move2data[move2_extRight_max].Xhitmax - move2data[move2_extRight_max].Xhurmax) - (move1data[move1_extLeft_max].Xhurmin - move1data[move1_extLeft_max].Xhitmin) << " pixels" << endl;
			}
			else if (move2data[move2_extRight_max].Xhitmax - Xsizemax2 < Xsizemin1 - move1data[move1_extLeft_max].Xhitmin)
			{
				cout << char1 << "\'s reverse " << move1 << "(frame " << move1_extLeft_max + 1 << ") extends further than " << char2 << "\'s " << move2 << "(frame " << move2_extRight_max + 1 << ") by " << (move1data[move1_extLeft_max].Xhurmin - move1data[move1_extLeft_max].Xhitmin) - (move2data[move2_extRight_max].Xhitmax - move2data[move2_extRight_max].Xhurmax) << " pixels" << endl;
			}
			else
			{
				cout << "both " << char1 << "\'s  reverse " << move1 << "(frame " << move1_extLeft_max + 1 << ") and " << char2 << "\'s " << move2 << "(frame " << move2_extRight_max + 1 << ") are equal in range!" << endl;
			}



			if (move2data[move2_disjLeft].Xhurmin - move2data[move2_disjLeft].Xhitmin > 0)//move 1 and 2 have reverse
			{
				if (Xsizemin1 - move1data[move1_extLeft_max].Xhitmin > Xsizemin2 - move2data[move2_extLeft_max].Xhitmin)
				{
					cout << char1 << "\'s reverse " << move1 << "(frame " << move1_extLeft_max + 1 << ") extends further than " << char2 << "\'s reverse " << move2 << "(frame " << move2_extLeft_max + 1 << ") by " << (move1data[move1_extLeft_max].Xhurmin - move1data[move1_extLeft_max].Xhitmin) - (move2data[move2_extLeft_max].Xhurmin - move2data[move2_extLeft_max].Xhitmin) << " pixels" << endl;
				}
				else if (Xsizemin1 - move1data[move1_extLeft_max].Xhitmin < Xsizemin2 - move2data[move2_extLeft_max].Xhitmin)
				{
					cout << char2 << "\'s reverse " << move2 << "(frame " << move2_extLeft_max + 1 << ") extends further than " << char1 << "\'s reverse " << move1 << "(frame " << move1_extLeft_max + 1 << ") by " << (move2data[move2_extLeft_max].Xhurmin - move2data[move2_extLeft_max].Xhitmin) - (move1data[move1_extLeft_max].Xhurmin - move1data[move1_extLeft_max].Xhitmin) << " pixels" << endl;
				}
				else
				{
					cout << "both " << char1 << "\'s reverse " << move1 << "(frame " << move1_extLeft_max + 1 << ") and " << char2 << "\'s  reverse " << move2 << "(frame " << move2_extLeft_max + 1 << ") are equal in range!" << endl;
				}
			}
		}
	}
	/*
	if (aerial1 == true || aerial2 == true)
	{
	cout << "move vs move vertical";
	if (aerial2 == true)
	{
	if (move1data[move1_disjUp].Yhurmin - move1data[move1_disjUp].Yhitmin > move2data[move2_disjDown].Yhitmax - move2data[move2_disjRight].Yhurmax)//normal
	{
	cout << char1 << "\'s " << move1 << "(frame " << move1_disjRight + 1 << ") will beat out " << char2 << "\'s " << move2 << "(frame " << move2_disjRight + 1 << ") by " << (move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax) - (move2data[move2_disjRight].Xhitmax - move2data[move2_disjRight].Xhurmax) << " pixels" << endl;
	}
	else if (move2data[move2_disjRight].Xhitmax - move2data[move2_disjRight].Xhurmax > move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax)
	{
	cout << char2 << "\'s " << move2 << "(frame " << move2_disjRight + 1 << ") will beat out " << char1 << "\'s " << move1 << "(frame " << move1_disjRight + 1 << ") by " << (move2data[move2_disjRight].Xhitmax - move2data[move2_disjRight].Xhurmax) - (move1data[move1_disjRight].Xhitmax - move1data[move1_disjRight].Xhurmax) << " pixels" << endl;
	}
	else
	{
	cout << "both " << char1 << "\'s " << move1 << "(frame " << move1_disjRight + 1 << ") and " << char2 << "\'s " << move2 << "(frame " << move2_disjRight + 1 << ") are equally disjointed!" << endl;
	}
	if (aerial1 == true)
	{
	cout << "same info from above";
	}
	}
	}
	*/

	return 0;
}
