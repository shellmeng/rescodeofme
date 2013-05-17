#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<cmath>

#define NUM 2

#define LAYER 2
int pnum[LAYER]={0};
using namespace std;

typedef struct TrainPoint
{

	vector< vector<double> > x;
	int res;
};

int printV3(vector< vector< vector<double> > >& weight)
{
	for(int i=0;i<weight.size();i++)
	{
		for(int j=0;j<weight[i].size();j++)
		{
			for(int k=0;k<weight[i][j].size();k++)
				cout<<weight[i][j][k]<<"\t";
			cout<<endl;
		}
		cout<<endl;
	}
	cout<<endl;
}
//int adaptWeight(vector<TrainPoint> &tp, vector< vector< vector<double> > >& weight)
vector<vector< vector< double> > >  adaptWeight(vector<TrainPoint> &tp, vector< vector< vector<double> > >& weight)
{
	double predict;
	double lamada=0.3;
	TrainPoint temtp;
	vector<vector< double> > gama;

	vector<TrainPoint> newtp;

	int flag=1;
	//for(lamada=1;lamada>0;lamada-=0.1) //add flag,
//	{
	//	if(lamada<1)
	//		flag=0;
	for(int o=0;o<tp.size();o++)
	{
	//	lamada-=0.1;
		for(int k=0;k<LAYER;k++)
		{

			tp[o].x.push_back(vector<double > (0));
			gama.push_back(vector<double> (0));
			flag=0;
		
			for(int l=0;l<weight[k].size();l++)
			{
				//cout<<"size= "<<weight[k].size()<<endl;
				predict=0;
				for(int h=0;h<weight[k][l].size();h++)
				{
					//用前一层的节点*当前节点的权重，得到当前节点的输出
				//	cout<<"x="<<tp[o].x[k][h]<<"\t";
					predict +=tp[o].x[k][h]*weight[k][l][h];
				}

				//cout<<"over"<<endl;

		/*		if(predict>=0)
					predict=1;
				else
					predict=0;*/
				//predict=1/(1+exp(-predict));
				predict=1/(1+exp(-predict));

				cout<<"predict="<<predict<<endl;
				tp[o].x[k+1].push_back(predict);
				//gama[k+1].push_back(0);
				gama[k].push_back(0);
				//cout<<"push"<<endl;
			}

			tp[o].x[k+1].push_back(-1);
		}
			
		double out=0;
		for(int k=LAYER-1;k>=0;k--)
		{

			if(k==LAYER-1)
			{
				for(int l=0;l<weight[k].size();l++)
				{
					out=tp[o].x[k+1][l];
					gama[k][l]=out*(1-out)*(tp[o].res-out);
				}
			}
			else
			{

				double sum=0;
				for(int l=0;l<weight[k].size();l++)
				{
					out=tp[o].x[k+1][l];
					sum=0;
					for(int m=0;m<weight[k+1].size();m++)
						sum+=gama[k+1][m]*weight[k+1][m][l];


					gama[k][l]=out*(1-out)*sum;

				}
			}
//update the w
			double dew=0;
			for(int l=0;l<weight[k].size();l++)
			{
				for(int n=0;n<weight[k][l].size();n++)
				{
					
					dew=lamada*gama[k][l]*tp[o].x[k][n];
			//		cout<<"dew= "<<dew<<endl;
					weight[k][l][n]+=dew;
				}
			}
		}
	}
	return weight;
}


int test(vector<TrainPoint> tp, vector< vector< vector<double> > >& weight)
{
	double predict;
	double lamada=0.01;
	TrainPoint temtp;
	vector<vector< double> > gama;

	vector<TrainPoint> newtp;
	cout<<"the predict result"<<endl;

	int flag=1;
//	for(lamada=1;lamada>0;lamada-=0.1) //add flag,
	for(int o=0;o<tp.size();o++)
	{
		//cout<<"tpsize()"<<tp.size()<<endl;
		for(int k=0;k<LAYER;k++)
		{
//			cout<<"k= "<<k<<"/"<<weight.size()<<endl;

			//tp[o].x.push_back(vector<int > (0));
			//gama.push_back(vector<double> (0));
		
			for(int l=0;l<weight[k].size();l++)
			{
//				cout<<"l= "<<l<<"/"<<weight[k].size()<<endl;
				predict=0;
				for(int h=0;h<weight[k][l].size();h++)
				{
					//用前一层的节点*当前节点的权重，得到当前节点的输出
//					cout<<"h = "<<h<<"/"<<weight[k][l].size()<<endl;
					predict +=tp[o].x[k][h]*weight[k][l][h];
					if(k==0 && l==0&& flag==1)
					{
						cout<<tp[o].x[k][h]<<"\t";
					}

				}


			/*	if(predict>=0)

					predict =1;
				else
					predict =0;*/
				predict=1/(1+exp(-predict));

				if(k==0 && l==0)  //输出预测值
					cout<<predict<<endl;

			}
		}
	}
}
int main()
{
	vector<TrainPoint> tp;
	ifstream in;
	in.open("train.txt");
	if(!in)
	{
		cout<<"open file error,exit"<<endl;
		exit(0);
	}

	TrainPoint tem;
	int ele;
	tem.x.push_back(vector<double > (0));
	while(!in.eof())
	{
		tem.x[0].clear();
		for(int i=0;i<NUM;i++)
		{
			in>>ele;
			tem.x[0].push_back(ele);
			//tem.newx.push_back(ele);
		}
		tem.x[0].push_back(-1);
		//tem.newx.push_back(-1);
		in>>tem.res;
		tp.push_back(tem);
	}


	tp.erase(tp.end()-1);
	vector<double> temw;
	double ran=0;
	srand(time(NULL));
	/*for(int i=0;i<NUM+1;i++)
	{
		ran=rand()%20*1.0;
		temw.push_back(ran);
	}*/

	pnum[0]=tp.size();
	pnum[1]=2;
	pnum[2]=1;
	int max=2;
	int layNum=LAYER;
	vector< vector< vector<double> > > weight(layNum,vector< vector< double> > (max, vector<double> (tp[0].x[0].size())));
	//define the layer num of the network
	//the first layer is the train data
	//the last layer is the final output, 1
	//the middle are to be set 


	int cur=0;
	for(int i=0;i<layNum;i++)
	{
		//cout<<"i="<<i<<endl;
		for(int j=0;j<pnum[i+1];j++)
		{

		//	cout<<"j="<<j<<endl;
			for(int z=0;z<tp[0].x[0].size();z++)
			{
				//cout<<"z="<<z<<endl;
				ran=rand()%50*1.0/10 ;
				weight[i][j][z]=ran;

				cur=z;
			}
			cur++;
			for(;cur<tp[0].x[0].size();cur++)
			{
				weight[i][j].erase(weight[i][j].end()-1);
	//			cout<<"erase weight[i][j][last]"<<endl;
			}
			
			cur=j;
		}
		cur++;
		for(;cur<max;cur++)
		{
			weight[i].erase(weight[i].end()-1);
			cout<<"erase weight[i][last]"<<endl;
		}

	}


	cout<<"display the wegith ************************"<<endl;
	for(int i=0;i<weight.size();i++)
	{
		for(int j=0;j<weight[i].size();j++)
		{
			for(int w=0;w<weight[i][j].size();w++)
			{
				cout<<weight[i][j][w]<<"\t";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	cout<<"display the wegith ************************"<<endl;
	weight=adaptWeight(tp, weight);

	cout<<"the weight are as fellows:"<<endl;
	printV3(weight);
	//for(int i=0;i<weight.size();i++)
	//	cout<<weight[i]<<endl;

	test(tp,weight);
}
