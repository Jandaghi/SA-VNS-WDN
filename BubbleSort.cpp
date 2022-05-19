  
// An optimized version of Bubble Sort
void bubbleSort(float (&arry)[3001] /*,float (&sortd) [3001]*/)
{
   int i, j;
   bool swapped;
   for (i = 1; i < Nlink; i++)
   {
     swapped = false;
     for (j = 1; j < Nlink-i; j++)
     {
        if (arry[j] > arry[j+1])
        {
           swap(&arry[j], &arry[j+1]);
           swapped = true;
        }
     }
  
     // IF no two elements were swapped by inner loop, then break
     if (swapped == false)
        break;
   }
   //for(int i=1;i<=Nlink;i++)
	  // sortd[i]=arry[i];
}