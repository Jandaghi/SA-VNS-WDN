

void output (solution sol, bool init_or_imp)
{
	
	if(init_or_imp==0)
	{
		cout<<endl<<endl;
		SetColor(15);
		cout<<endl<<"----------------------------Initial Solution Result--------------------------"<<endl<<endl;
		cout<<"Initial Diameters:  " ;SetColor(7);
		for (int i=1; i<=Nlink; i++)
		{
			cout<< ComDiam[sol.IDdiam[i]];
			cout<<" ";
		}
		cout<<endl;
		cout<<"-------------------------"<<endl;


		SetColor(15);
		cout<<endl<<"Initial Velocity in Pipes:  " ;SetColor(7);
		for (int i=1; i<=Nlink; i++)
		{
			cout<<floor((sol.velocity[i] * 100) + .5) / 100; 
			cout<<" ";
			//round(12.2);
		}
		cout<<endl;
		cout<<"-------------------------"<<endl;


		SetColor(15);
		cout<<endl<<"Initial Pressure Head in Nodes:  " ;SetColor(7);
		for (int i=1; i<=Nnode; i++)
		{
			cout<< floor((sol.pressure[i] * 100) + .5) / 100; 
			cout<<" ";
		}
		cout<<endl;
		cout<<"-------------------------"<<endl;



		SetColor(15);
		cout<<endl<<"Initial Total cost:  " ;SetColor(2);
			cout<<sol.Tcost/1000000;cout<<" *10^6 " ; 
			cout<<" ";SetColor(15);
		
		cout<<endl;
		cout<<"-------------------------"<<endl;

		SetColor(15);
		cout<<endl<<"----------------------------Improved Solution Result--------------------------"<<endl<<endl;
		cout<<endl<<"Improving please wait... "<<endl ;SetColor(15);
	}



	if(init_or_imp==1)
	{
		cout<<endl<<endl;
		SetColor(15);
		cout<<endl<<"----------------------------Improved Solution Result--------------------------"<<endl<<endl;
		cout<<"Improved Diameters:  " ;SetColor(7);
		for (int i=1; i<=Nlink; i++)
		{
			cout<< ComDiam[sol.IDdiam[i]];
			cout<<" ";
		}
		cout<<endl;
		cout<<"-------------------------"<<endl;


		SetColor(15);
		cout<<endl<<"Improved Velocity in Pipes:  " ;SetColor(7);
		for (int i=1; i<=Nlink; i++)
		{
			cout<<floor((sol.velocity[i] * 100) + .5) / 100; 
			cout<<" ";
			//round(12.2);
		}
		cout<<endl;
		cout<<"-------------------------"<<endl;


		SetColor(15);
		cout<<endl<<"Improved Pressure Head in Nodes:  " ;SetColor(7);
		for (int i=1; i<=Nnode; i++)
		{
			cout<< floor((sol.pressure[i] * 100) + .5) / 100; 
			cout<<" ";
		}
		cout<<endl;
		cout<<"-------------------------"<<endl;



		SetColor(15);
		cout<<endl<<"Improved Total cost:  " ;SetColor(2);
			cout<<sol.Tcost/1000000;cout<<" *10^6 " ; 
			cout<<" ";SetColor(15);
		
		cout<<endl;
		cout<<"-------------------------"<<endl;

		SetColor(15);

	ofstream outfile;
	outfile.open(ResultFile, ios::out);// ate = out bude
	//outfile.open("ok.txt");
	//outfile <<"Objective Value: " <<sol.tscor<<endl;
	outfile <<"Total Cost Value: " <<sol.Tcost<<endl<<"Run Time: " <<(stp1-strt1)/double(CLOCKS_PER_SEC)
		<<" Sec "<<endl<<endl<<"Selected Diameter (mm): "<<endl ;
	for (int i=1; i<=Nlink; i++)
				outfile <<ComDiam[sol.IDdiam[i]]<<endl;

	outfile <<endl<<endl<<"Pressure Head in Nodes (m): " ;
	for (int i=1; i<=Nnode; i++) 
		outfile <<floor((sol.pressure[i] * 100) + .5) / 100<<" ";
		

	outfile <<endl<<endl<<"Velocity in Pipes (m/s): " ;
	for (int i=1; i<=Nlink; i++) 
		outfile <<floor((sol.velocity[i] * 100) + .5) / 100<<" ";
				

    outfile.close();

	ofstream outfile1;
	//outfile.open(ResultFile, ios::out);// ate = out bude
	outfile1.open("Eva.txt");
	//outfile <<"Objective Value: " <<sol.tscor<<endl;
	outfile1 <<"Total Cost Value: " <<sol.Tcost<<endl<<"Run Time: " <<(stp1-strt1)/double(CLOCKS_PER_SEC)
		<<" Sec "<<endl<<endl<<"Evaluated (NO.): "<<endl ;
	for (int i=1; i<=EvaI; i++)
				outfile1 <<Evaluated[i]<<endl;

	outfile1 <<endl<<endl<<"Costs: "<<endl ;
	for (int i=1; i<=EvaI; i++) 
		outfile1 <<EvaCost[i]<<endl;
		
				

    outfile1.close();

	}



	}

