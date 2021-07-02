
#include<iostream>
#include <ctime>     
#include <fstream>
#include <cstdlib>   
#include <sstream>   
#include <vector>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int k = 0;
int numOfElements = 0;
int num_of_processes = 0;

double distance(double x1, double y1, double x2, double y2){
  return sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));
}

/* This function goes through that data points and assigns them to a cluster */
void assign2Cluster(double P1x1[], double P1y1[], double P2x2[], double P2y2[], int assign[])
{
	double minDist = numeric_limits<float>::infinity();

	double tempDist = 0;
	int cluster = -1;

	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < k; j++)
		{
			tempDist = distance(P1x1[j],P1y1[j], P2x2[i], P2y2[i]);
			cout<<"Temp Distance"<< tempDist<<endl;
			// new minimum distance found
			if(tempDist < minDist)
			{
				minDist = tempDist;
				cluster = j;
        
			}
		}

		// update the cluster assignment of this data points
	cout<<" Assigned -> "<<cluster<<endl;
    assign[i] = cluster;
	}

}

/* Recalcuate k-means of each cluster because each data point may have
   been reassigned to a new cluster for each iteration of the algorithm */
void calcKmeans(double k_means_x[], double k_means_y[], double data_x_points[], double data_y_points[],int k_assignment[])
{
  
	double total_x = 0;
	double total_y = 0;
	int count = 0;

	for(int i = 0; i < 3; i++)
	{
		total_x = 0;
		total_y = 0;
		count = 0;

		for(int j = 0; j < 10; j++)
		{
			if(k_assignment[j] == i)
			{
				total_x += data_x_points[j];
				total_y += data_y_points[j];
				count++;
				cout<<k_assignment[j]<<" = "<<i<<endl;
			}
		}

		if(count != 0)
		{
			k_means_x[i] = total_x / count;
			k_means_y[i] = total_y / count;
		}
	}
	 ofstream myfile; 
    myfile.open("output22.txt");
    myfile << "x, y, c" << endl;

    for (int i = 0; i <10; ++i) {
        myfile << data_x_points[i] << ", " << data_y_points[i] << " , " << k_assignment[i] << endl;
    }

    myfile.close();

}

int main(int argc, char *argv[])
{
	
    k =3;
    double data_x_points[10];
    double data_y_points[10];
    double k_means_x[3];
    double k_means_y[3];
    int k_assignment[10];

      //Have to fill the array
      for(int i = 0; i < 10;i++){
			data_x_points[i] = rand()%50;
			data_y_points[i] = rand()%50;

			// assign the initial k means to zero
			//k_assignment[i] = 0;
      }
		

		// randomly select initial k-means
		
		//srand((unsigned) time(0));
		int random;
		for(int i = 0; i < k; i++) {
			random = rand() % 10;
			k_means_x[i] = data_x_points[random];
			k_means_y[i] = data_y_points[random];
		}
  
		
		cout<<"Running k-means algorithm for "<<100<< "iterations...\n"<<endl;
		for(int i = 0; i < k; i++)
		{
			cout<<"Initial K-means: ("<<k_means_x[i]<<","<<k_means_y[i]<<")"<<endl;
		}
	


	int co = 0;
	while(co < 1)
	{
		
      assign2Cluster(k_means_x, k_means_y, data_x_points, data_y_points, k_assignment);
			//  for(int i = 0; i < 10; i++) 
      		// 	cout<<k_assignment[i]<<"  ";
        
      //calcKmeans(k_means_x, k_means_y, data_x_points, data_y_points, k_assignment);
	calcKmeans(k_means_x, k_means_y, data_x_points, data_y_points, k_assignment);
     
			co++;
		
	}


		cout<<"--------------------------------------------------\n"<<endl;
		cout<<"FINAL RESULTS:\n"<<endl;
    for(int i = 0; i < 10; i++){
      cout<<"("<<data_x_points[i]<<","<<data_y_points[i]<<") cluster -> "<<k_assignment[i]<<endl;
    }
		for(int i = 0; i < k; i++)
		{
			cout<<"Cluster "<< i<<"("<<k_means_x[i]<<"," <<k_means_y[i]<<")"<<endl;
		}
		cout<<"--------------------------------------------------\n"<<endl;
	

}
