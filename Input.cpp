// ----------------------------- Header and Dependencies files --------------------------------------------
#include "epanet2.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include "string_n.h"
#include <cmath>

//---------------------------------- Declaring & Definitions -----------------------------------------------
using namespace std;
#define maxn 3001
double strt=0;
double stp=0;
double strt1=0;
double stp1=0;

int Nlink;  //Number of pipes
int Nnode;  //Number of nodes
int Ndiam;   //Number of available diameter
int Nres;
float length[maxn];  // length of pipes
float ComCost[100];  //Commercial available pipes cost
float MinVel;  //Minimum allowable velocity
float MaxVel;  //Maximum allowable velocity
float MinPrs; //Minimum pressure head
float MaxPrs;  //Maximum pressure head
int errcode;
int cntr=0;

	int Evaluated[maxn];
	float EvaCost[maxn];
	int EvaCount=1;
	float EvaBst;
	int EvaI=1;


// SA Parameters:

	float       Tmin= 0.5;         //large                         
	float       Tmax=	80;                                
	int         iter_max= 80;  //
	float       alpa= 0.95;   //Coefficient for decreasing //
	float       beta= 0.2;    //Coefficient for shaking 
    float       gama= 0.6;

	//float       Tmin= 3;       //small                           
	//float       Tmax=	50;                                
	//int         iter_max= 80;  //
	//float       alpa= 0.9;   //Coefficient for decreasing //
	//float       beta= 0.6;    //Coefficient for shaking 
 //   float       gama= 0.6;

	//Small Network		Large Network	
	//Tmax	50      Tmax    80
	//Tmin	3		Tmin	0.5 
	//(Alpha)	0.9		(Alpha)	0.95
	//(Beta)	0.6	    (Beta)	0.2
	//Iteration	80		Iteration	80
	//Gama	0.6		Gama	0.6
	                       
//-----------------------------------------------------------------------------------
	int Ndecrease_diam=3;              //maximum to N_Diameter-1
	 //Coefficient for pipes that change diameters 0.4 for ex1,2,3

//-----------------------------------------------------------------------------------



//int Nres;   //Number of reservoirs
//int ID[maxn];  //ID of each pipes
//int node1[maxn];  //"From node" of pipes
//int node2[maxn];  //"To node" of pipes
//float HW[maxn];  //Hazen-Williams Coefficient of pipes
//float demand[maxn];  //Demand of nodes
//float elevation[maxn];  //Elevation each nodes
//float THead[100];   //Total Head of reserviors
float ComDiam[200];  //Commercial available pipe diameters
char ResultFile[50];

struct solution
{
	int IDdiam[maxn];
	float diam[maxn];
	float velocity[maxn]; // velocity in pipes
	float pressure[maxn]; // Pressure head of nodes
	float Tcost;  //Total cost of solotion

	//float cost[maxn]; //Cost of pipe considering diameter	//float diamtr[maxn];	//float discharge[maxn];
};

void SetColor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}

void Tcost_calc (solution &sol)
{
	sol.Tcost=0;
	for(int i=1; i<=Nlink; i++)
		sol.Tcost +=  ComCost[sol.IDdiam[i]] * length[i];
}

void cpy_sol (solution from , solution &to)
{
	for(int i=1; i<=Nlink; i++)
	{
		to.IDdiam[i]=from.IDdiam[i];
		to.diam[i]=ComDiam[from.IDdiam[i]];
		to.velocity[i]=from.velocity[i];
		to.Tcost=from.Tcost;
		//to.cost[i]=from.cost[i];
		//to.diameter_ID[i]=from.diameter_ID[i];
		//to.discharge[i]=from.discharge[i];
	}

	for(int i=1; i<=Nnode; i++)
	{
		to.pressure[i]=from.pressure[i];
	}
}



bool check_sol (solution sol) //Check solotion feasibility
{
	bool flag=1;

	for(int i=1; i<=Nlink; i++)
	{
		if(	sol.velocity[i]>=MaxVel || sol.velocity[i]<=MinVel )
			flag=0;
	}

	for(int i=1; i<=Nnode; i++)
	{
		if(sol.pressure[i]>=MaxPrs || sol.pressure[i]<=MinPrs)
			flag=0;
	}
	return flag;
}

string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

void swap_float(float *xp, float *yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swap_int(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort (float (&arry)[maxn], int (&arry_indx)[maxn] /*,float (&sortd) [3001]*/)
{
   int i, j;
   bool swapped;
   for (i = 1; i <= Nlink; i++)
   {
     swapped = false;
     for (j = 1; j <= Nlink-i; j++)
     {
        if (arry[j] < arry[j+1])
        {
           swap_float(&arry[j], &arry[j+1]);
		   swap_int(&arry_indx[j], &arry_indx[j+1]);
           swapped = true;
        }
     }
     if (swapped == false)
        break;
   }
}


void input ()
{
	b:
	SetColor(7);
	int i; char InputFileName[50]; FILE *fp; char ReportFileName[50]; char DiamFile[50];cout<<endl;
	printf ("Give the input network file name (*.inp file): "); 
	scanf ("%s", InputFileName);

	
	for(int i=0;i<=50;i++)
	{
		ReportFileName[i]=InputFileName[i]; 
		DiamFile[i]=InputFileName[i];
	}

	for(int i=0;i<=50;i++)
		ResultFile[i]=InputFileName[i];
	strcat (ResultFile, "_Result");
	strcat (ResultFile, ".txt");
	
	strcat (InputFileName, ".inp");
	//exists(InputFileName) ? cout << "Exists\n" : cout << "Doesn't exist\n";
	

	strcat (ReportFileName, ".rpt");
  
    int a_size = sizeof(InputFileName) / sizeof(char);
	strcat (DiamFile, ".diam");
	fp = fopen (DiamFile, "r");
	ifstream my_file(DiamFile);
	if (my_file.good()) 
		goto a; 
	{ SetColor(12);
		cout<<endl<< "There is not file with this name"; cout<<endl<<endl; goto b;}
	a:
	cout<<endl;
	cout<<"Calculating...";
	cout<<endl<<endl;
  
    //string InputFileName_s = convertToString(InputFileName, a_size);
  
    //string ReportFileName_s = convertToString(ReportFileName, a_size);

	errcode = ENopen(InputFileName ,ReportFileName , ""); // Remember use ENclose()
	
	
	
	fscanf (fp, "%d %d %d %f %f %f %f",&Nlink, &Nnode, &Ndiam, &MinVel, &MaxVel, &MinPrs, &MaxPrs);
	for (int i = 1 ; i <= Ndiam; i++) fscanf (fp, "%f %f", ComDiam+i , ComCost+i);
	fclose (fp);

	for (int i = 1 ; i <= Nlink; i++)
		ENgetlinkvalue(i, EN_LENGTH, &length[i]);
	//ENsetlinkvalue(1,EN_DIAMETER,20); float ii;
	//ENgetlinkvalue(1, EN_DIAMETER, &ii);
	
	//cout<<"ok";

	//errcode = ENclose();

    return;
}
