
void init_sol(solution &init)
{
	int rnd=1;
	int counterr=0;
	init.Tcost=0;
	strt=clock(); stp=clock();

	Here:
	
	if(stp-strt>=5000) {strt=stp; cntr=cntr+5; cout<<endl<<"Elapsed time: ";  cout<< cntr; cout<<" sec"<<endl;
		cout<<"Total Cost: ";
		cout<< init.Tcost;
		cout<<endl<<endl; }
	counterr++;
	for (int i = 1 ; i <= Nlink; i++)
	{   
		//here2:
		rnd=(rand() % (Ndiam)) + 1;
		//if(rnd<=9) goto here2;
		
		init.IDdiam[i]=rnd;
		ENsetlinkvalue(i, EN_DIAMETER, ComDiam[rnd]);
	}
	//ENsetlinkvalue(4, EN_DIAMETER, ComDiam[4]);
	//ENsetlinkvalue(8, EN_DIAMETER, ComDiam[1]);

	ENsolveH();
	for (int ii = 1 ; ii <= Nlink; ii++)
		ENgetlinkvalue(ii, EN_VELOCITY, &init.velocity[ii]);
	for (int ij = 1 ; ij <= Nnode; ij++)
		ENgetnodevalue(ij, EN_PRESSURE, &init.pressure[ij]);
	stp=clock();
	if(check_sol(init)==false) 
		goto Here;

	//for (int i = 1 ; i <= Nlink; i++)
	//	ENgetlinkvalue(i, EN_DIAMETER, &init.diamtr[i]);

	Tcost_calc(init);

	for (int il = 1 ; il <= Nlink; il++)
		init.diam[il]=ComDiam[init.IDdiam[il]];
	
	EvaCost[1]=init.Tcost;
	EvaBst=init.Tcost;
	

	//if(init.Tcost>=420000)
	//	goto Here;

	//ENsaveH();

	//int rnd_nu=3;

	return;
}