#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>

#define NUM 2


using namespace std;

typedef struct TrainPoint
{

	vector<int> x;
	int res;
};

int adaptWeight(vector<TrainPoint> & tp, vector<double>& weight)
{
	double predict;
	double lamada=0.01;
	for(lamada=1;lamada>0;lamada-=0.1)
	{
	for(int i=0;i<tp.size();i++)
	{
		predict=0;
		for(int w=0;w<tp[i].x.size();w++)
			predict+=tp[i].x[w]*weight[w];
		if(predict>=0)//-weight[weight.size()-1])
			predict=1;
		else
			predict =0;
		
		for(int j=0;j<weight.size();j++)
		{
			weight[j]=weight[j]+lamada*(tp[i].res-predict)*tp[i].x[j];
		}

	}
	}
}


int test(vector<TrainPoint> & tp, vector<double>& weight)
{
	double predict;
	double lamada=0.01;
	for(int i=0;i<tp.size();i++)
	{
		predict=0;
		for(int w=0;w<tp[i].x.size();w++)
		{
			predict+=tp[i].x[w]*weight[w];
			cout<<tp[i].x[w]<<"\t";
		}
		if(predict>=0)//-weight[weight.size()-1])
			predict=1;
		else
			predict =0;
		
		
		cout<<predict<<endl;
		cout<<endl;
	}
	
	
}
int main()
{
	cout<<"usage: put the train data in train.txt file"<<endl;
	vector<TrainPoint> tp;
	ifstream in;
	in.open("train.txt");
	if(!in)
	{
		cout<<"open file train error, the train data are in this file,exit"<<endl;
		exit(0);
	}

	TrainPoint tem;
	int ele;
	while(!in.eof())
	{
		tem.x.clear();
		for(int i=0;i<NUM;i++)
		{
			in>>ele;
			tem.x.push_back(ele);
		}
		tem.x.push_back(-1);
		in>>tem.res;
		tp.push_back(tem);
	}


	tp.erase(tp.end()-1);
	vector<double> weight;
	double ran=0;
	srand(time(NULL));
	for(int i=0;i<NUM+1;i++)
	{
		ran=rand()%20*1.0;
		weight.push_back(ran);
	}

	adaptWeight(tp, weight);

	cout<<"the weight vector is: "<<endl;
	for(int i=0;i<weight.size();i++)
		cout<<weight[i]<<"\t";
	cout<<endl;
	cout<<endl;
	cout<<endl;

	cout<<"the test result is "<<endl;
	test(tp,weight);
}
