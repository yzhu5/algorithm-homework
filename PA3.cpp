#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;



//compare two integer value
int Max(int a, int b)
{
    if(a>=b)
        return a;
    else
        return b;

}



int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "Usage: "  << argv[0] << "filename";
    }

    char *fileName = argv[1];

    fstream readFile(fileName, ios::in);

    int X, Y; //the dimensions of initial cloth
    int n; // the number of n products
    vector<int> a,b,c; // the dimension of and the selling price of products

    //read file
    if(readFile.is_open())
    {
        readFile >> X >> Y;
        readFile >> n;
        int temp1, temp2, temp3;
        while(readFile >> temp1 >> temp2 >> temp3)
            {
                a.push_back(temp1);
                b.push_back(temp2);
                c.push_back(temp3);
            }
    }
    else
    {
        cerr << "Cannot open " << fileName << " !" << endl;
    }

    /*
    //print input file
    cout << X << " " << Y << endl;
    cout << n << endl;
    for(int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " " << b[i] << " " << c[i] << endl;
    }
    */

    //initial a 2D array
    int p[X+1][Y+1];

    for(int i = 0; i <= X; i++)
    {
        for(int j = 0; j <=Y;j++)
        {
            p[i][j] = 0;
        }
    }

    //update the maximum value for each sub_conditions
    //for 1<= x <= X; 1<=j<=Y, let p(x,y) be the best return that can be get from a cloth of shape x*y
    //initialize p(0,y) and p(x,0) equal to 0
    //the recursion is  p[x][y] = Max(p[x-a[i]][y-b[i]] + c[i], p[x][y]), find the max value by updating p[x][y], until we find p[X][Y]
    for(int i = 0; i < n; i++) // n is the number of products
    {
        for(int x = a[i]; x <= X; ++x) // X is max dimension
        {
            for(int y = b[i]; y<=Y; ++y) // Y is the max dimension
                p[x][y] = Max(p[x-a[i]][y-b[i]] + c[i], p[x][y]); // recursion of max value
        }
    }

    cout <<"The maximum value is " <<  p[X][Y] << endl;



    /*
    //print the 2-D table
    for(int i = 0; i < X+1; i++)
    {
        for(int j = 0; j < Y+1; j++)
        {
            cout << p[i][j] <<" ";
        }
        cout << endl;
    }
    */


    return 0;
}
