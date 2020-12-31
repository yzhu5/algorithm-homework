#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <vector>
#include <string>
using namespace std;



// save data of each line
struct data
{
    int x;
    int y;
    string z;
};

string E = "E";
string N = "N";

vector<int> parents;



//make a parent set
vector<int> makeset( int n)
{
    vector<int> P;
    for(int i = 0; i < n+1; i++)
    {
        P.push_back(i);
    }
    return P;
}

int Find(int target)
{
  // find the parent node
  int i = target;
  while(parents[i] != i)
        i = parents[i];

  return i;
}


//if x and y not in a tree, we connect them
void join(int x, int y)
{
    int findx = Find(x);
    int findy = Find(y);
    if(findx != findy)
    {
        parents[findx] = findy;
    }
}


//if x and y not in the same tree, we return true
bool ifsatisfible (int x, int y)
{
    int findx = Find(x);
    int findy = Find(y);
    if(findx != findy)
    {
        return true;
    }
    return false;
}



int main(int argc, char **argv)
{


    //Input data
	/////////////////////////////////////////////////
	if(argc!=2)
	{
		cout << "usage: " << argv[0] << " filename" << endl;
		return 0;
	}
	fstream inputFile;
	inputFile.open(argv[1], ios::in);
	if(!inputFile.is_open())
	{
		cout << argv[1] << " not found!" << endl;
		return 0;
	}

	vector<data> EqualSet; // Save data in vector
	vector<data> UnequalSet;
    string line;
    getline(inputFile,line);
    int variablesNum;
    variablesNum = stoi(line);
    int lineNumber = 0;
    while(getline(inputFile, line))
	{
		stringstream input(line);
		int i = 0;
		string tempos;
		data EmptySet;
		while(input >> tempos)
        {
            if(i == 0)
            {
            EmptySet.x = stoi(tempos);
            }
            else if(i == 1)
            {
                EmptySet.z = (tempos);
            }
            else if(i == 2)
            {
                EmptySet.y = stoi(tempos);
            }
            i++;

        }
        if(!EmptySet.z.compare(E))
        {
            EqualSet.push_back(EmptySet);
            //cout << EmptySet.x << " " << EmptySet.y << " " << EmptySet.z << endl;
        }
        else if(!EmptySet.z.compare(N))
        {
            UnequalSet.push_back(EmptySet);
            //cout << EmptySet.x << " " << EmptySet.y << " " << EmptySet.z << endl;
        }
	}

	inputFile.close();

	///////////////////////////////////////////

//make parent sets
    parents = makeset(variablesNum);

//join connected points
    for(int i = 0; i < EqualSet.size(); i++)
    {
        join(EqualSet[i].x, EqualSet[i].y);
    }

    bool satisfible = true;
    //decide if the file satisfied
    for(int i = 0; i < UnequalSet.size(); i++)
    {
        satisfible = ifsatisfible(UnequalSet[i].x,UnequalSet[i].y);
        if(satisfible == false)
        {
            cout << "Not satisfiable" << endl;
            break;
        }
    }
    if(satisfible)
    {
        cout << "satisfiable" << endl;
    }

	return 0;
}
