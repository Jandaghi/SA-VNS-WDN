
//--------------------------- SA-VNS for Water Distribution Network Optimization --------------------------
//--------------------------------- Version 1.0 : 1400/Tir/20 ---------------------------------------------

#include "input.cpp"
#include "Init_sol.cpp"
#include "Imp_sol.cpp"
#include "Output.cpp"
//#include "BubbleSort.cpp"



void main()
{

	

	bool repeat=0;
	srand((unsigned)time(0));
	
	RunAgain:
	solution init; //Initial solotion
	solution imp;  //Improved solotion

	
	// Read input data files
	input();

	// Initial solotion building function()
	
	strt1=clock();

	init_sol(init);
	
	output(init, 0);

	// Improved solotion building function()
	imp_sol(init, imp);

	stp1=clock();

	output(imp, 1);
	
	

	//stp1=clock();
	//output(imp, 0); // vorodi ro bayad imp bezani
	
	// output file building function()


	//ENsetlinkvalue(1,EN_DIAMETER,20);

	//errcode = ENclose(InputFileName ,ReportFileName , "");
	//cout<<"ok";

	//ENsaveH();
	ENclose();
	cout<< '\a';
	//PlaySound(TEXT("finish.wav"), NULL, SND_FILENAME | SND_ASYNC);
	goto RunAgain; 
}
