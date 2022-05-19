
void LocalSearch (solution cur, solution &out) 
{
	//solution bst;
	solution cur2;
	//cpy_sol(cur,out);
	cpy_sol(cur,cur2);
	cpy_sol(cur,out);
	float tmp_vel[maxn];
	float tmp_pre[maxn];

	int selectd_i=0;
	int selectd_up_down=0;
	int up=0;
	int down=0;
	int Ncheck_pipe=gama*Nlink;

	float sortd_diam[maxn];
	int sortd_indx[maxn];

	for(int ii=1;ii<=Nlink;ii++){
		sortd_diam[ii]=cur.diam[ii];
		sortd_indx[ii]=ii;
	}
	for (int pp=1; pp<=Nlink; pp++)
		ENsetlinkvalue(pp, EN_DIAMETER, ComDiam[cur.IDdiam[pp]]);

	bubbleSort(sortd_diam, sortd_indx);

	
	for(int i=1; i<=Ncheck_pipe;  i++)
	{	
		if(cur2.IDdiam[sortd_indx[i]]==1 || cur2.IDdiam[sortd_indx[i]]<= Ndecrease_diam) 
			{ goto nxt;}

		for(int j=1; j<=Ndecrease_diam; j++)
		{
			for(int m=1; m<=Nlink; m++)
				tmp_vel[m]=cur2.velocity[m];
			for(int m=1; m<=Nnode; m++)
				tmp_pre[m]=cur2.pressure[m];
			//EvaCount++;///////////
			ENsetlinkvalue(sortd_indx[i], EN_DIAMETER,ComDiam[cur2.IDdiam[sortd_indx[i]]-1]);
			//ENsetlinkvalue(sortd_indx[i], EN_DIAMETER, ComDiam[cur2.IDdiam[sortd_indx[i]]-1]);
			cur2.diam[sortd_indx[i]]=ComDiam[cur2.IDdiam[sortd_indx[i]]-1];
			cur2.IDdiam[sortd_indx[i]]=cur2.IDdiam[sortd_indx[i]]-1;
			
			//EvaCount++;
			ENsolveH();
			for (int k = 1 ; k <= Nlink; k++)
				ENgetlinkvalue(k, EN_VELOCITY, &cur2.velocity[k]);
			for (int k = 1 ; k <= Nnode; k++)
				ENgetnodevalue(k, EN_PRESSURE, &cur2.pressure[k]);

			if(check_sol(cur2)==false) {
				for(int m=1; m<=Nlink; m++)
					cur2.velocity[m]=tmp_vel[m];
				for(int m=1; m<=Nnode; m++)
					cur2.pressure[m]=tmp_pre[m];
				ENsetlinkvalue(sortd_indx[i], EN_DIAMETER, ComDiam[cur2.IDdiam[sortd_indx[i]]+1]);
				cur2.diam[sortd_indx[i]]=ComDiam[cur2.IDdiam[sortd_indx[i]]+1];
				cur2.IDdiam[sortd_indx[i]]=cur2.IDdiam[sortd_indx[i]]+1;
				//ENsetlinkvalue(sortd_indx[i], EN_DIAMETER, ComDiam[cur2.IDdiam[sortd_indx[i]]+1]);
				//ENsetlinkvalue(i, EN_DIAMETER, ComDiam[cur2.IDdiam[i]+1]);

				goto nxt;
			}

			//cur2.diam[sortd_indx[i]]= ComDiam[cur2.IDdiam[sortd_indx[i]]-1];
			//cur2.IDdiam[sortd_indx[i]]= cur2.IDdiam[sortd_indx[i]]-1;
			Tcost_calc(cur2);
			EvaCount++;
			if(cur2.Tcost<EvaBst) {
				EvaI++;
				EvaCost[EvaI]=cur2.Tcost;
				EvaBst=cur2.Tcost;
				Evaluated[EvaI]=EvaCount;
			}

		}
	nxt:
	int nx=0;
	}
	for (int pp=1; pp<=Nlink; pp++)
			ENsetlinkvalue(pp, EN_DIAMETER, ComDiam[cur2.IDdiam[pp]]);
	cpy_sol(cur2, out);

}

	//for(int i=1; i<=Nlink; i++)
	//{

		//cpy_sol(cur,cur2);
		//if (cur.IDdiam[i]==Ndiam) 
		//	goto nxt1;

		////for (int m = 1 ; m <= Nlink; m++)
		////	ENsetlinkvalue(m, EN_DIAMETER, ComDiam[cur.IDdiam[m]]);

		//cur2.IDdiam[i]=cur2.IDdiam[i]+1;  
		//ENsetlinkvalue(i, EN_DIAMETER, ComDiam[cur2.IDdiam[i]]);
		//
		//ENsolveH();
		//for (int k = 1 ; k <= Nlink; k++)
		//	ENgetlinkvalue(k, EN_VELOCITY, &cur2.velocity[k]);
		//for (int k = 1 ; k <= Nnode; k++)
		//	ENgetnodevalue(k, EN_PRESSURE, &cur2.pressure[k]);

		////stp=clock();
		//if(check_sol(cur2)==false) 
		//	goto nxt1;
		//Tcost_calc(cur2);
		//if (cur2.Tcost<bst.Tcost){
		//	cpy_sol(cur2, bst); selectd_i=i; selectd_up_down=1;}

		//nxt1:

		//if (cur.IDdiam[i]==1) 
		//	goto end1;
		//cpy_sol(cur,cur2);

		//for (int m = 1 ; m <= Nlink; m++)
		//	ENsetlinkvalue(m, EN_DIAMETER, ComDiam[cur.IDdiam[m]]);

	//	cur2.IDdiam[i]=cur2.IDdiam[i]-1;  
	//	ENsetlinkvalue(i, EN_DIAMETER, ComDiam[cur2.IDdiam[i]]);
	//	
	//	ENsolveH();
	//	for (int k = 1 ; k <= Nlink; k++)
	//		ENgetlinkvalue(k, EN_VELOCITY, &cur2.velocity[k]);
	//	for (int k = 1 ; k <= Nnode; k++)
	//		ENgetnodevalue(k, EN_PRESSURE, &cur2.pressure[k]);

	//	//stp=clock();
	//	if(check_sol(cur2)==false) 
	//		goto end1;
	//	Tcost_calc(cur2);
	//	if (cur2.Tcost<bst.Tcost){
	//		cpy_sol(cur2, bst); selectd_i=i; selectd_up_down=0;}

	//	end1:
	//	int tmp=0;

	//}
	//int ss=0;
	//cpy_sol(bst, cur2);////////////////////////////////////////////////////////////////////////////

	//for(int i=1; i<=Nlink; i++)
	//{
	//	if(i==selectd) goto end;
	//	cpy_sol(bst,cur2);
	//	if (cur2.IDdiam[i]==Ndiam) goto nxt;
	//	cur2.IDdiam[i]=cur2.IDdiam[i]+1;  
	//	ENsetlinkvalue(i, EN_DIAMETER, ComDiam[cur2.IDdiam[i]]);
	//	
	//	ENsolveH();
	//	for (int j = 1 ; j <= Nlink; j++)
	//		ENgetlinkvalue(j, EN_VELOCITY, &cur2.velocity[j]);
	//	for (int j = 1 ; i <= Nnode; i++)
	//		ENgetnodevalue(j, EN_PRESSURE, &cur2.pressure[j]);
	//	//stp=clock();
	//	if(check_sol(cur2)==false) 
	//		goto nxt;
	//	Tcost_calc(cur2);
	//	if (cur2.Tcost<bst.Tcost)
	//		cpy_sol(cur2, bst);

	//	nxt:
	//	if (cur2.IDdiam[i]==1) goto end;
	//	cur2.IDdiam[i]=cur2.IDdiam[i]-1;  
	//	ENsetlinkvalue(i, EN_DIAMETER, ComDiam[cur2.IDdiam[i]]);
	//	
	//	ENsolveH();
	//	for (int j = 1 ; j <= Nlink; j++)
	//		ENgetlinkvalue(j, EN_VELOCITY, &cur2.velocity[j]);
	//	for (int j = 1 ; j <= Nnode; j++)
	//		ENgetnodevalue(j, EN_PRESSURE, &cur2.pressure[j]);
	//	//stp=clock();
	//	if(check_sol(cur2)==false) 
	//		goto end;
	//	Tcost_calc(cur2);
	//	if (cur2.Tcost<bst.Tcost)
	//		cpy_sol(cur2, bst);

	//	end:
	//	int tmp=0;


	//}

//
//
//	cpy_sol(bst,out);
//}

void shaking (solution cur, solution &cur22, double beta) 
{	
	cpy_sol(cur,cur22);

	int Nbeta=0;
	int rnd_num1;
	int rnd_num2;
	int tmp;

	Nbeta=beta*Nlink;

	for (int pp=1; pp<=Nlink; pp++)
		ENsetlinkvalue(pp, EN_DIAMETER, ComDiam[cur.IDdiam[pp]]);

	again:
	for(int i=1; i<=Nbeta; i++)
	{
		//again:
		rnd_num1=1 + int((Nlink)*rand()/(RAND_MAX + 1.0));
		rnd_num2=1 + int((Ndiam)*rand()/(RAND_MAX + 1.0));
		//tmp=cur22.IDdiam[rnd_num1];
		cur22.IDdiam[rnd_num1]=rnd_num2;
		cur22.diam[rnd_num1]=ComDiam[rnd_num2];
		//EvaCount++;/////////////////////
		ENsetlinkvalue(rnd_num1, EN_DIAMETER, ComDiam[rnd_num2]);
	}
	//EvaCount++;
	ENsolveH();
		for (int j = 1 ; j <= Nlink; j++)
			ENgetlinkvalue(j, EN_VELOCITY, &cur22.velocity[j]);
		for (int j = 1 ; j <= Nnode; j++)
			ENgetnodevalue(j, EN_PRESSURE, &cur22.pressure[j]);
	//stp=clock();
	if(check_sol(cur22)==false) {
		for (int pp=1; pp<=Nlink; pp++)
			ENsetlinkvalue(pp, EN_DIAMETER, cur.diam[pp]);
		cpy_sol(cur, cur22);
		goto again;
	}
	for (int pp=1; pp<=Nlink; pp++)
		ENsetlinkvalue(pp, EN_DIAMETER, ComDiam[cur22.IDdiam[pp]]);

	Tcost_calc(cur22);
	EvaCount++;


}

void imp_sol(solution init, solution &imp)
{

	//SA ---------------------------------------------------------------------------------------------
	double rnd;
	//float        Tmin= 1;
	int iter;
	bool SA_condition=false;
	double delta1=0;
	double delta2=0;
	float T;

	solution sol1;
	solution sol2;
	solution sol3;
	solution bstt;
	cpy_sol(init,sol1);
	cpy_sol(init,sol2);
	cpy_sol(init,sol3);
	cpy_sol(init,bstt);
	cpy_sol(init,imp);
	int Tcounter=0;

	int improveCount = 0;
	T=Tmax;

    while(T>=Tmin) 
	{ 
		iter=1;
		//improveCount=0;
		cpy_sol(bstt, sol2);
		cpy_sol(bstt, sol1);
		cpy_sol(bstt, sol3);

		for (int pp=1; pp<=Nlink; pp++)
			ENsetlinkvalue(pp, EN_DIAMETER, ComDiam[bstt.IDdiam[pp]]);
		ENsolveH();
		strt=clock()/1000;
		while(iter<=iter_max /*improveCount <= improveMax */)
		{   
			
			//strt=clock();
			//if(stp-strt>=5000) {strt=stp; cntr=cntr+5; cout<<endl<<"Elapsed time: ";  cout<< cntr; cout<<" sec"<<endl;
			//	cout<<"Total Cost: ";
			//	cout<< bstt.Tcost;
			//	cout<<endl<<endl; }

			//EvaCount++;
			LocalSearch(sol2,sol3);
			delta1=sol3.Tcost-bstt.Tcost;
			delta2=sol3.Tcost-sol1.Tcost;
			if(delta1<0) {
				cpy_sol(sol3,bstt);}			

			if(delta2<0) { 
				cpy_sol(sol3,sol1);							
			}else{
				rnd=(double) rand() / (RAND_MAX + 1);
				if  (exp(((-1)*delta1)/T)>rnd)
					cpy_sol(sol3,sol1);
			}
			//shaking (sol1, sol2, beta);
			//cpy_sol(sol2,sol3);
			shaking(sol1,sol2,beta);
			iter++;
		/*	if(bstt.Tcost<EvaBst) {
				EvaI++;
				EvaCost[EvaI]=bstt.Tcost;
				EvaBst=bstt.Tcost;
				Evaluated[EvaI]=EvaCount;
			}*/
			

		}
		stp=clock()/1000;
		Tcounter=Tcounter+(stp-strt);
		cout<<endl<<"Elapsed time: ";  cout<< Tcounter; cout<<" sec"<<endl;
		cout<<"Total Cost: ";
		cout<< bstt.Tcost;
		cout<<endl<<endl;

		T=alpa*T;

	}
		
	for (int pp=1; pp<=Nlink; pp++)
		ENsetlinkvalue(pp, EN_DIAMETER, ComDiam[bstt.IDdiam[pp]]);		///////////////////////////////////////////
		
	cpy_sol(bstt,imp);

	//End SA -----------------------------------------------------------------------------------------

	//return;		
		
}



