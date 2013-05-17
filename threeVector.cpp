#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#define Layer 3
int pn[4]={4,4,2,1};

using namespace std;
int main()
{
/*	vector< vector< vector<double> > > w(Layer);

	for(int i=1;i<Layer+1;i++)
	{
		w[i].push_back(vector< vector< double> > (pn[i]));
		for(int j=0;j<w[i]
	}*/


	vector< vector<int> > w;
	for(int i=0;i<3;i++)
	{
		w.push_back( vector<int>(0));
		for(int j=0;j<pn[i];j++)
		{
			//w[i][j]=rand()%15;
			w[i].push_back(rand()%15);
		}

	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<w[i].size();j++)
			cout<<w[i][j]<<"\t";
		cout<<endl;

	}
}
