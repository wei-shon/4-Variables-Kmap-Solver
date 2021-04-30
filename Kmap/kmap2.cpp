#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//use strtok
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
//draw k map and count minilizer num
struct Map{
  int array[4][4];
};

int FinalMap[4][4];
int FinalInputNumber;
//to 化簡 boolean function
const int ROWS = 4, COMLUMNS = 4;

int numberOfMinterms = 0;
int DecimalMinterms[15];

struct KmapElement
{
	int state;
	int DecimalMinterm;
	int inclusion = 0;
	string binaryminterm;
};
struct Implicant
{
	vector <KmapElement> minterms;
	int Size;
};
KmapElement Kmap[ROWS][COMLUMNS];

vector <KmapElement> V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, AllElemntsInImplicant;;
vector <Implicant> AllImplicants;
//function
void split(string& s , vector<string>& fun);
void CheckInput();
string FinalExpression = "";
void GetInput();
void IntializeKMap(), IntializeBinaryMintermsKMap();
void PrintKMap();
void AlgorithmFindImplicants();
vector <KmapElement> GetVectorOfMaxSize(vector<KmapElement> V1, vector<KmapElement> V2, vector<KmapElement> V3, vector<KmapElement> V4, vector<KmapElement> V5, vector<KmapElement> V6, vector<KmapElement> V7, vector<KmapElement> V8, vector<KmapElement> V9, vector<KmapElement> V10);
void SortAllImplicantsBySizeInAscendingOrder();
void AssignInclusionTimesToImplicants();
void RemoveDuplicateImplicants();
void DecreaseInclusionOfMintermsInDeletedImplicant(int i);
void GetEssentialPrimeImplicants();
void GetFinalExpression();
ofstream ofs;//to satisfy the output name

ifstream ifs;//to satisfy the input name
int main(){
	CheckInput();
	IntializeKMap();
	IntializeBinaryMintermsKMap();
	//PrintKMap();
	AlgorithmFindImplicants();
	SortAllImplicantsBySizeInAscendingOrder();
	AssignInclusionTimesToImplicants();
	RemoveDuplicateImplicants();
	GetEssentialPrimeImplicants();
	GetFinalExpression();
	cout << "F(A, B, C, D) = " << FinalExpression << endl;
	ofs << "F(A, B, C, D) = " << FinalExpression << endl;
	system("pause");
	ofs.close();
    

}
void split(string& s , vector<string>& fun) {
    fun.clear();
    char* buffer=new char[s.size()+1];
    buffer[s.size()]='\0';
    copy(s.begin(),s.end(),buffer);
    char *p=strtok(buffer,"+\n()");
    while(p!=NULL){
        fun.push_back(p);
        p=strtok(NULL,"+\n()");
    }
    delete buffer;
    return;
}
void CheckInput(){
	ifs.open("input.txt");//open input.txt
	string s ((istreambuf_iterator<char>(ifs)),istreambuf_iterator<char>());
	ifs.close();//close input.txt
	ofs.open("output.txt");//open output.txt
    //read equation and split
  	vector<int>min;
  	vector<Map>totalmap;
  //read equation and split
//   string s;
//   cin>>s;
  	vector<string>fun;
	split(s,fun);
   	Map map;//to remember the k map that every product of component consist of  
  	bool inverse=false;//to check whether the '(negate) appear in product term
  //to see each product term
  for(int i = 0 ;i < fun.size();i++){
    string y = fun[i];
    int sign;//to confirm first component is negate or 'abcd -> 0 is ' and 1 is "abcd"
    if(y[y.length()-1]=='\''){//if the first is negate(')
      sign=0;
      if(y[y.length()-2]=='a'){
        map.array[0][0]=1;
        map.array[0][1]=1;
        map.array[1][0]=1;
        map.array[1][1]=1;
        map.array[2][0]=1;
        map.array[2][1]=1;
        map.array[3][0]=1;
        map.array[3][1]=1;
      }
      else if(y[y.length()-2]=='b'){
        map.array[0][0]=1;
        map.array[0][3]=1;
        map.array[1][0]=1;
        map.array[1][3]=1;
        map.array[2][0]=1;
        map.array[2][3]=1;
        map.array[3][0]=1;
        map.array[3][3]=1;
      }
      else if(y[y.length()-2]=='c'){
        map.array[0][0]=1;
        map.array[0][1]=1;
        map.array[0][2]=1;
        map.array[0][3]=1;
        map.array[1][0]=1;
        map.array[1][1]=1;
        map.array[1][2]=1;
        map.array[1][3]=1;
      }
      else if(y[y.length()-2]=='d'){
        map.array[0][0]=1;
        map.array[0][1]=1;
        map.array[0][2]=1;
        map.array[0][3]=1;
        map.array[3][0]=1;
        map.array[3][1]=1;
        map.array[3][2]=1;
        map.array[3][3]=1;
      }
    }
    else if(y[y.length()-1]!='\''){//if the first is the a or b or c or d
      sign=1;
      if(y[y.length()-1]=='a'){
        map.array[0][2]=1;
        map.array[0][3]=1;
        map.array[1][2]=1;
        map.array[1][3]=1;
        map.array[2][2]=1;
        map.array[2][3]=1;
        map.array[3][2]=1;
        map.array[3][3]=1;
      }
      else if(y[y.length()-1]=='b'){
        map.array[0][2]=1;
        map.array[0][1]=1;
        map.array[1][2]=1;
        map.array[1][1]=1;
        map.array[2][2]=1;
        map.array[2][1]=1;
        map.array[3][2]=1;
        map.array[3][1]=1;
      }
      else if(y[y.length()-1]=='c'){
        map.array[2][0]=1;
        map.array[2][1]=1;
        map.array[2][2]=1;
        map.array[2][3]=1;
        map.array[3][0]=1;
        map.array[3][1]=1;
        map.array[3][2]=1;
        map.array[3][3]=1;
      }
      else if(y[y.length()-1]=='d'){
        map.array[2][0]=1;
        map.array[2][1]=1;
        map.array[2][2]=1;
        map.array[2][3]=1;
        map.array[1][0]=1;
        map.array[1][1]=1;
        map.array[1][2]=1;
        map.array[1][3]=1;
      }     
    }
    if(sign==0){//to continue checking the second component is what
      for(int j = y.length()-3 ; 0<=j ; j--){//since the first component is negate, we should see the y.length-3 that is the second component 
        if(y[j]=='a'&&inverse==false){//if is next ecomponent is a then a' should be 0
          map.array[0][0]=0;
          map.array[0][1]=0;
          map.array[1][0]=0;
          map.array[1][1]=0;
          map.array[2][0]=0;
          map.array[2][1]=0;
          map.array[3][0]=0;
          map.array[3][1]=0;
        }
        else if(y[j]=='b'&&inverse==false){//if is next component is b then b' should be 0
          map.array[0][0]=0;
          map.array[0][3]=0;
          map.array[1][0]=0;
          map.array[1][3]=0;
          map.array[2][0]=0;
          map.array[2][3]=0;
          map.array[3][0]=0;
          map.array[3][3]=0;
        }
        else if(y[j]=='c'&&inverse==false){//if is next component is c then c' should be 0
          map.array[0][0]=0;
          map.array[0][1]=0;
          map.array[0][2]=0;
          map.array[0][3]=0;
          map.array[1][0]=0;
          map.array[1][1]=0;
          map.array[1][2]=0;
          map.array[1][3]=0;
        }
        else if(y[j]=='d'&&inverse==false){//if is next component is d then d' should be 0
          map.array[0][0]=0;
          map.array[0][1]=0;
          map.array[0][2]=0;
          map.array[0][3]=0;
          map.array[3][0]=0;
          map.array[3][1]=0;
          map.array[3][2]=0;
          map.array[3][3]=0;
        }
        if(y[j]=='a'&&inverse==true){//if is next component is a' then a should be 0
          map.array[0][2]=0;
          map.array[0][3]=0;
          map.array[1][2]=0;
          map.array[1][3]=0;
          map.array[2][2]=0;
          map.array[2][3]=0;
          map.array[3][2]=0;
          map.array[3][3]=0;
        }
        else if(y[j]=='b'&&inverse==true){//if is next component is b' then b should be 0
          map.array[0][2]=0;
          map.array[0][1]=0;
          map.array[1][2]=0;
          map.array[1][1]=0;
          map.array[2][2]=0;
          map.array[2][1]=0;
          map.array[3][2]=0;
          map.array[3][1]=0;
        }
        else if(y[j]=='c'&&inverse==true){//if is next component is c' then c should be 0
          map.array[2][0]=0;
          map.array[2][1]=0;
          map.array[2][2]=0;
          map.array[2][3]=0;
          map.array[3][0]=0;
          map.array[3][1]=0;
          map.array[3][2]=0;
          map.array[3][3]=0;
        }
        else if(y[j]=='d'&&inverse==true){//if is next component is d' then d should be 0
          map.array[2][0]=0;
          map.array[2][1]=0;
          map.array[2][2]=0;
          map.array[2][3]=0;
          map.array[1][0]=0;
          map.array[1][1]=0;
          map.array[1][2]=0;
          map.array[1][3]=0;
        }
        else if (y[j]=='\''){
          inverse=true;
          continue;
        }
        inverse=false;             
      }
    }
    else if(sign==1){//if the first is not negate
    //the below for-loop is same as the up 
      for(int j = y.length()-2 ; 0<=j ; j--){
        
        if(y[j]=='a'&&inverse==false){//if is next exponent is a then a' should be 0
          map.array[0][0]=0;
          map.array[0][1]=0;
          map.array[1][0]=0;
          map.array[1][1]=0;
          map.array[2][0]=0;
          map.array[2][1]=0;
          map.array[3][0]=0;
          map.array[3][1]=0;
        }
        else if(y[j]=='b'&&inverse==false){
          map.array[0][0]=0;
          map.array[0][3]=0;
          map.array[1][0]=0;
          map.array[1][3]=0;
          map.array[2][0]=0;
          map.array[2][3]=0;
          map.array[3][0]=0;
          map.array[3][3]=0;
        }
        else if(y[j]=='c'&&inverse==false){
          map.array[0][0]=0;
          map.array[0][1]=0;
          map.array[0][2]=0;
          map.array[0][3]=0;
          map.array[1][0]=0;
          map.array[1][1]=0;
          map.array[1][2]=0;
          map.array[1][3]=0;
        }
        else if(y[j]=='d'&&inverse==false){
          map.array[0][0]=0;
          map.array[0][1]=0;
          map.array[0][2]=0;
          map.array[0][3]=0;
          map.array[3][0]=0;
          map.array[3][1]=0;
          map.array[3][2]=0;
          map.array[3][3]=0;
        }
        else if(y[j]=='a'&&inverse==true){
          map.array[0][2]=0;
          map.array[0][3]=0;
          map.array[1][2]=0;
          map.array[1][3]=0;
          map.array[2][2]=0;
          map.array[2][3]=0;
          map.array[3][2]=0;
          map.array[3][3]=0;
        }
        else if(y[j]=='b'&&inverse==true){
          map.array[0][2]=0;
          map.array[0][1]=0;
          map.array[1][2]=0;
          map.array[1][1]=0;
          map.array[2][2]=0;
          map.array[2][1]=0;
          map.array[3][2]=0;
          map.array[3][1]=0;
        }
        else if(y[j]=='c'&&inverse==true){
          map.array[2][0]=0;
          map.array[2][1]=0;
          map.array[2][2]=0;
          map.array[2][3]=0;
          map.array[3][0]=0;
          map.array[3][1]=0;
          map.array[3][2]=0;
          map.array[3][3]=0;
        }
        else if(y[j]=='d'&&inverse==true){
          map.array[2][0]=0;
          map.array[2][1]=0;
          map.array[2][2]=0;
          map.array[2][3]=0;
          map.array[1][0]=0;
          map.array[1][1]=0;
          map.array[1][2]=0;
          map.array[1][3]=0;
        }
        else if (y[j]=='\''){
          inverse=true;
          continue;
        }
        inverse=false;      
      }     
    }
    // for(int j = 0 ; j < 4 ; j++){
    //   for (int k = 0 ; k < 4 ; k++){
    //     cout<<map.array[j][k]<<" ";
    //   }
    //   cout<<endl;  
    // } 
    //to combine k map of the every product term into one k map
    
    for(int j = 0 ; j < 4 ; j++){
      for (int k = 0 ; k < 4 ; k++){
        if(map.array[j][k]==1){
          FinalMap[j][k]=1;         
        }
        map.array[j][k]=0;
      }
    } 
  }
  for(int i = 0 ; i < 4 ; i++){
    for (int j = 0 ; j < 4 ; j++){
      if(FinalMap[i][j]==1){
          if(i==0 and j==0){
            min.push_back(0);
          }
          else if(i==1 and j==0){
            min.push_back(1);
          }
          else if(i==3 and j==0){
            min.push_back(2);
          }       
          else if(i==2 and j==0){
            min.push_back(3);
          }
          else if(i==0 and j==1){
            min.push_back(4);
          }  
          else if(i==1 and j==1){
            min.push_back(5);
          }
          else if(i==3 and j==1){
            min.push_back(6);
          }
          else if(i==2 and j==1){
            min.push_back(7);
          }       
          else if(i==0 and j==3){
            min.push_back(8);
          }  
          else if(i==1 and j==3){
            min.push_back(9);
          }
          else if(i==3 and j==3){
            min.push_back(10);
          }
          else if(i==2 and j==3){
            min.push_back(11);
          }
          else if(i==0 and j==2){
            min.push_back(12);
          } 
          else if(i==1 and j==2){
            min.push_back(13);
          }    
          else if(i==3 and j==2){
            min.push_back(14);
          }  
          else if(i==2 and j==2){
            min.push_back(15);
          }
      }
    }
  }
  //check final map
//   for(int j = 0 ; j < 4 ; j++){
//     for (int k = 0 ; k < 4 ; k++){
//       cout<<FinalMap[j][k]<<" ";
//     }
//     cout<<endl;  
//   }
//   for(int j = 0 ; j < min.size() ; j++){
//     cout<<min[j]<<" ";
//   }
  numberOfMinterms=min.size();
  for(int i = 0 ; i < min.size();i++){
      DecimalMinterms[i] = min[i];
  }
		
	cout<<"========= K Map ========="<<endl; 
	cout<<"  \\AB|                  "<<endl;
	cout<<"CD \\ | 00 | 01 | 11 | 10"<<endl;
	cout<<"-----+----+----+----+-----"<<endl;
	cout<<"  00 |";
	for(int i = 0 ; i < 4;i++){
		for(int j = 0 ; j < 4;j++){
			if(i==0){
				cout<<"  "<<FinalMap[i][j]<<" |";
				if(j==3){
					cout<<endl;
				}
			}
		}
	}
	cout<<"-----+----+----+----+----|"<<endl;
	cout<<"  01 |";
	for(int i = 0 ; i < 4;i++){
		for(int j = 0 ; j < 4;j++){
			if(i==1){
				cout<<"  "<<FinalMap[i][j]<<" |";
				if(j==3){
					cout<<endl;
				}
			}
		}
	}
	cout<<"-----+----+----+----+----|"<<endl;
	cout<<"  11 |";
	for(int i = 0 ; i < 4;i++){
		for(int j = 0 ; j < 4;j++){
			if(i==2){
				cout<<"  "<<FinalMap[i][j]<<" |";
				if(j==3){
					cout<<endl;
				}
			}
		}
	}
	cout<<"-----+----+----+----+----|"<<endl;
	cout<<"  10 |";
	for(int i = 0 ; i < 4;i++){
		for(int j = 0 ; j < 4;j++){
			if(i==3){
				cout<<"  "<<FinalMap[i][j]<<" |";
				if(j==3){
					cout<<endl;
				}
			}
		}
	}
	cout<<"--------------------------"<<endl;

	ofs<<"========= K Map ========="<<endl; 
	ofs<<"  \\AB|                  "<<endl;
	ofs<<"CD \\ | 00 | 01 | 11 | 10"<<endl;
	ofs<<"-----+----+----+----+-----"<<endl;
	ofs<<"  00 |";
	for(int i = 0 ; i < 4;i++){
		for(int j = 0 ; j < 4;j++){
			if(i==0){
				ofs<<"  "<<FinalMap[i][j]<<" |";
				if(j==3){
					ofs<<endl;
				}
			}
		}
	}
	ofs<<"-----+----+----+----+----|"<<endl;
	ofs<<"  01 |";
	for(int i = 0 ; i < 4;i++){
		for(int j = 0 ; j < 4;j++){
			if(i==1){
				ofs<<"  "<<FinalMap[i][j]<<" |";
				if(j==3){
					ofs<<endl;
				}
			}
		}
	}
	ofs<<"-----+----+----+----+----|"<<endl;
	ofs<<"  11 |";
	for(int i = 0 ; i < 4;i++){
		for(int j = 0 ; j < 4;j++){
			if(i==2){
				ofs<<"  "<<FinalMap[i][j]<<" |";
				if(j==3){
					ofs<<endl;
				}
			}
		}
	}
	ofs<<"-----+----+----+----+----|"<<endl;
	ofs<<"  10 |";
	for(int i = 0 ; i < 4;i++){
		for(int j = 0 ; j < 4;j++){
			if(i==3){
				ofs<<"  "<<FinalMap[i][j]<<" |";
				if(j==3){
					ofs<<endl;
				}
			}
		}
	}
	ofs<<"--------------------------"<<endl;
}
void IntializeKMap()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COMLUMNS; j++)
			Kmap[i][j].state = 0;

	Kmap[0][0].DecimalMinterm = 0;
	Kmap[0][1].DecimalMinterm = 4;
	Kmap[0][2].DecimalMinterm = 12;
	Kmap[0][3].DecimalMinterm = 8;
	Kmap[1][0].DecimalMinterm = 1;
	Kmap[1][1].DecimalMinterm = 5;
	Kmap[1][2].DecimalMinterm = 13;
	Kmap[1][3].DecimalMinterm = 9;
	Kmap[2][0].DecimalMinterm = 3;
	Kmap[2][1].DecimalMinterm = 7;
	Kmap[2][2].DecimalMinterm = 15;
	Kmap[2][3].DecimalMinterm = 11;
	Kmap[3][0].DecimalMinterm = 2;
	Kmap[3][1].DecimalMinterm = 6;
	Kmap[3][2].DecimalMinterm = 14;
	Kmap[3][3].DecimalMinterm = 10;

	for (int i = 0; i < numberOfMinterms; i++)
	{
		if (DecimalMinterms[i] == 0)
			Kmap[0][0].state = 1;
		else if (DecimalMinterms[i] == 4)
			Kmap[0][1].state = 1;
		else if (DecimalMinterms[i] == 12)
			Kmap[0][2].state = 1;
		else if (DecimalMinterms[i] == 8)
			Kmap[0][3].state = 1;
		else if (DecimalMinterms[i] == 1)
			Kmap[1][0].state = 1;
		else if (DecimalMinterms[i] == 5)
			Kmap[1][1].state = 1;
		else if (DecimalMinterms[i] == 13)
			Kmap[1][2].state = 1;
		else if (DecimalMinterms[i] == 9)
			Kmap[1][3].state = 1;
        else if (DecimalMinterms[i] == 3)
			Kmap[2][0].state = 1;
		else if (DecimalMinterms[i] == 7)
			Kmap[2][1].state = 1;
		else if (DecimalMinterms[i] == 15)
			Kmap[2][2].state = 1;
		else if (DecimalMinterms[i] == 11)
			Kmap[2][3].state = 1;
		else if (DecimalMinterms[i] == 2)
			Kmap[3][0].state = 1;
		else if (DecimalMinterms[i] == 6)
			Kmap[3][1].state = 1;
		else if (DecimalMinterms[i] == 14)
			Kmap[3][2].state = 1;
		else if (DecimalMinterms[i] == 10)
			Kmap[3][3].state = 1;
	}
}
void IntializeBinaryMintermsKMap()
{
	Kmap[0][0].binaryminterm = "0000";
	Kmap[0][1].binaryminterm = "0100";
	Kmap[0][2].binaryminterm = "1100";
	Kmap[0][3].binaryminterm = "1000";
	Kmap[1][0].binaryminterm = "0001";
	Kmap[1][1].binaryminterm = "0101";
	Kmap[1][2].binaryminterm = "1101";
	Kmap[1][3].binaryminterm = "1001";
	Kmap[2][0].binaryminterm = "0011";
	Kmap[2][1].binaryminterm = "0111";
	Kmap[2][2].binaryminterm = "1111";
	Kmap[2][3].binaryminterm = "1011";
	Kmap[3][0].binaryminterm = "0010";
	Kmap[3][1].binaryminterm = "0110";
	Kmap[3][2].binaryminterm = "1110";
	Kmap[3][3].binaryminterm = "1010";
}
// void PrintKMap()
// {
// 	for (int i = 0; i < 4; i++)
// 	{
// 		for (int j = 0; j < 4; j++)
// 			cout << Kmap[i][j].state << "  ";
// 		cout << endl;
// 	}
// }
void AlgorithmFindImplicants()
{
	if (numberOfMinterms == 16)
	FinalExpression = "1";
	else if (numberOfMinterms == 0)
		FinalExpression = "0";
	else
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COMLUMNS; j++)
			{
				int implicantNum = 0;
				if (Kmap[i][j].state == 1)
				{
					V1.push_back(Kmap[i][j]);
					if (Kmap[i][(j + 1) % COMLUMNS].state == 1)
					{
						V2.push_back(Kmap[i][j]);
						V2.push_back(Kmap[i][(j + 1) % COMLUMNS]);
					}
					if (Kmap[(i + 1) % ROWS][j].state == 1)
					{
						V3.push_back(Kmap[i][j]);
						V3.push_back(Kmap[(i + 1) % ROWS][j]);
					}
					if(i==0){
						int k=5;
						if (Kmap[k - 1][j].state == 1)
						{
							V9.push_back(Kmap[i][j]);
							V9.push_back(Kmap[k - 1][j]);
						}
					}
					else if(i>0){
						if (Kmap[(i - 1) % ROWS][j].state == 1)
						{
							V9.push_back(Kmap[i][j]);
							V9.push_back(Kmap[(i - 1) % ROWS][j]);
						}	
					}
					if(j==0){
						int k = 5 ;
						if (Kmap[i][k-1].state == 1)
						{
							V10.push_back(Kmap[i][j]);
							V10.push_back(Kmap[i][k-1]);
						}
					}
					else if(j>0){
						if (Kmap[i][abs(j - 1) % COMLUMNS].state == 1)
						{
							V10.push_back(Kmap[i][j]);
							V10.push_back(Kmap[i][(j - 1) % COMLUMNS]);
						}
					}
					if (Kmap[i][(j + 1) % COMLUMNS].state == 1 && Kmap[(i + 1) % ROWS][j].state == 1 && Kmap[(i + 1) % ROWS][(j + 1) % COMLUMNS].state == 1)
					{
						V4.push_back(Kmap[i][j]);
						V4.push_back(Kmap[i][(j + 1) % COMLUMNS]);
						V4.push_back(Kmap[(i + 1) % ROWS][j]);
						V4.push_back(Kmap[(i + 1) % ROWS][(j + 1) % COMLUMNS]);
					}
					if (Kmap[i][(j + 1) % COMLUMNS].state == 1 && Kmap[i][(j + 2) % COMLUMNS].state == 1 && Kmap[i][(j + 3) % COMLUMNS].state == 1)
					{
						V5.push_back(Kmap[i][j]);
						V5.push_back(Kmap[i][(j + 1) % COMLUMNS]);
						V5.push_back(Kmap[i][(j + 2) % COMLUMNS]);
						V5.push_back(Kmap[i][(j + 3) % COMLUMNS]);
					}
					if (Kmap[(i+ 1)% ROWS][j].state == 1 && Kmap[(i+ 2)% ROWS][j].state == 1 && Kmap[(i+ 3)% ROWS][j].state == 1)
					{
						V6.push_back(Kmap[i][j]);
						V6.push_back(Kmap[(i+ 1)% ROWS][j]);
						V6.push_back(Kmap[(i+ 2)% ROWS][j]);
						V6.push_back(Kmap[(i+ 3)% ROWS][j]);
					}
					if (Kmap[i][(j + 1) % COMLUMNS].state == 1 && Kmap[(i + 1) % ROWS][j].state == 1 && Kmap[(i + 1) % ROWS][(j + 1) % COMLUMNS].state == 1 && Kmap[(i + 2) % ROWS][j].state == 1 &&Kmap[(i + 2) % ROWS][(j + 1) % COMLUMNS].state == 1 && Kmap[(i + 3) % ROWS][j].state == 1 && Kmap[(i + 3) % ROWS][(j + 1) % COMLUMNS].state == 1)
					{
						V7.push_back(Kmap[i][j]);
						V7.push_back(Kmap[i][(j + 1) % COMLUMNS]);
						V7.push_back(Kmap[(i + 1) % ROWS][j]);
						V7.push_back(Kmap[(i + 1) % ROWS][(j + 1) % COMLUMNS]);
                        V7.push_back(Kmap[(i + 2) % ROWS][j]);
                        V7.push_back(Kmap[(i + 2) % ROWS][(j + 1) % COMLUMNS]);
                        V7.push_back(Kmap[(i + 3) % ROWS][j]);
                        V7.push_back(Kmap[(i + 3) % ROWS][(j + 1) % COMLUMNS]);
					}
					if (Kmap[i][(j + 1) % COMLUMNS].state == 1 && Kmap[(i + 1) % ROWS][j].state == 1 && Kmap[(i + 1) % ROWS][(j + 1) % COMLUMNS].state == 1 && Kmap[i][(j + 2) % COMLUMNS].state == 1 && Kmap[(i + 1) % ROWS][(j + 2) % COMLUMNS].state == 1 && Kmap[i][(j + 3) % COMLUMNS].state == 1 && Kmap[(i + 1) % ROWS][(j + 3) % COMLUMNS].state == 1)
					{
						V8.push_back(Kmap[i][j]);
						V8.push_back(Kmap[i][(j + 1) % COMLUMNS]);
						V8.push_back(Kmap[(i + 1) % ROWS][j]);
						V8.push_back(Kmap[(i + 1) % ROWS][(j + 1) % COMLUMNS]);
                        V8.push_back(Kmap[i][(j + 2) % COMLUMNS]);
                        V8.push_back(Kmap[(i + 1) % ROWS][(j + 2) % COMLUMNS]);
                        V8.push_back(Kmap[i][(j + 3) % COMLUMNS]);
                        V8.push_back(Kmap[(i + 1) % ROWS][(j + 3) % COMLUMNS]);
					}
					AllElemntsInImplicant = GetVectorOfMaxSize(V1, V2, V3, V4, V5, V6, V7, V8, V9, V10);
					for (int m = 0; m < AllElemntsInImplicant.size(); m++)
					{
						if (AllElemntsInImplicant[m].DecimalMinterm == 0)
							Kmap[0][0].inclusion = Kmap[0][0].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 1)
							Kmap[1][0].inclusion = Kmap[1][0].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 2)
							Kmap[3][0].inclusion = Kmap[3][0].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 3)
							Kmap[2][0].inclusion = Kmap[2][0].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 4)
							Kmap[0][1].inclusion = Kmap[0][1].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 5)
							Kmap[1][1].inclusion = Kmap[1][1].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 6)
							Kmap[3][1].inclusion = Kmap[3][1].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 7)
							Kmap[2][1].inclusion = Kmap[2][1].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 8)
							Kmap[0][3].inclusion = Kmap[0][3].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 9)
							Kmap[1][3].inclusion = Kmap[1][3].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 10)
							Kmap[3][3].inclusion = Kmap[3][3].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 11)
							Kmap[2][3].inclusion = Kmap[2][3].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 12)
							Kmap[0][2].inclusion = Kmap[0][2].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 13)
							Kmap[1][2].inclusion = Kmap[1][2].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 14)
							Kmap[3][2].inclusion = Kmap[3][2].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 15)
							Kmap[2][2].inclusion = Kmap[2][2].inclusion + 1;

					}

					Implicant A;
					for (int k = 0; k < AllElemntsInImplicant.size(); k++)
					{
						A.minterms.push_back(AllElemntsInImplicant[k]);
						//cout << AllElemntsInImplicant[k].binaryminterm << " ";
					}
					//cout << endl << "All elements in Implicant done." << endl;
					A.Size = AllElemntsInImplicant.size();
					AllImplicants.push_back(A);
					A.minterms.clear();
					A.Size = 0;

					implicantNum++;
				}
				V1.clear();
				V2.clear();
				V3.clear();
				V4.clear();
				V5.clear();
                V6.clear();
                V7.clear();
                V8.clear();
                V9.clear();
                V10.clear();
			}
		}
	}
}
vector <KmapElement> GetVectorOfMaxSize(vector<KmapElement> V1, vector<KmapElement> V2, vector<KmapElement> V3, vector<KmapElement> V4, vector<KmapElement> V5, vector<KmapElement> V6, vector<KmapElement> V7, vector<KmapElement> V8, vector<KmapElement> V9, vector<KmapElement> V10)
{
	int Sizes[10];
	Sizes[0] = V1.size();
	Sizes[1] = V2.size();
    Sizes[2] = V9.size();
    Sizes[3] = V10.size();
	Sizes[4] = V3.size();
	Sizes[5] = V4.size();
	Sizes[6] = V5.size();
    Sizes[7] = V6.size();
    Sizes[8] = V7.size();
    Sizes[9] = V8.size();


	int max = -1;
	int vector_number;
	for (int i = 0; i < 10; i++)
	{
		if (Sizes[i] > max)
		{
			max = Sizes[i];
			vector_number = i + 1;
		}
	}
	if (vector_number == 1)
		return V1;
	if (vector_number == 2)
		return V2;
	if (vector_number == 3)
		return V9;
	if (vector_number == 4)
		return V10;
	if (vector_number == 5)
		return V3;
	if (vector_number == 6)
		return V4;
	if (vector_number == 7)
		return V5;
	if (vector_number == 8)
		return V6;
	if (vector_number == 9)
		return V7;
	if (vector_number == 10)
		return V8;
}
void SortAllImplicantsBySizeInAscendingOrder()
{
	int i, j;
	for (i = 0; i < AllImplicants.size() - 1; i++)
	{
		for (j = 0; j < AllImplicants.size() - i - 1; j++)
			if (AllImplicants[j].Size > AllImplicants[j + 1].Size)
			{
				Implicant temp = AllImplicants[j];
				AllImplicants[j] = AllImplicants[j + 1];
				AllImplicants[j + 1] = temp;
			}
	}

	// for (i = 0; i < AllImplicants.size(); i++)
	// {
	// 	cout << "After Sortion: " << i << "  ";
	// 	for (j = 0; j < AllImplicants[i].minterms.size(); j++)
	// 		cout << AllImplicants[i].minterms[j].binaryminterm << "  ";
	// 	cout << endl;
	// }
}
void AssignInclusionTimesToImplicants()
{
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			if (AllImplicants[i].minterms[j].DecimalMinterm == 0)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][0].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 1)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][0].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 2)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[3][0].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 3)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[2][0].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 4)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][1].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 5)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][1].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 6)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[3][1].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 7)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[2][1].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 8)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][3].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 9)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][3].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 10)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[3][3].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 11)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[2][3].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 12)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][2].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 13)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][2].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 14)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[3][2].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 15)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[2][2].inclusion;
			}
		}
	}
}
void RemoveDuplicateImplicants()
{
	int isEqual = 0;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		for (int k = 1; k < AllImplicants.size() - 1; k++)
		{
			for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
			{
				for (int N = 0; N < AllImplicants[k].minterms.size(); N++)
				{
					if (AllImplicants[i].minterms[j].binaryminterm == AllImplicants[k].minterms[N].binaryminterm)
					{
						isEqual++;
					}
				}

				if (isEqual == AllImplicants[i].minterms.size() && AllImplicants[i].Size == AllImplicants[k].Size)
				{
					DecreaseInclusionOfMintermsInDeletedImplicant(i);
					AllImplicants.erase(AllImplicants.begin() + i);
				}
				isEqual = 0;
			}
		}
	}
}
void DecreaseInclusionOfMintermsInDeletedImplicant(int i)
{
	int* DecimalMinterm = new int[AllImplicants[i].minterms.size()];
	for (int m = 0; m < AllImplicants[i].minterms.size(); m++)
	{
		DecimalMinterm[m] = AllImplicants[i].minterms[m].DecimalMinterm;
	}
	for (int k = 0; k < AllImplicants.size(); k++)
	{
		for (int L = 0; L < AllImplicants[k].minterms.size(); L++)
		{
			for (int S = 0; S < AllImplicants[i].minterms.size(); S++)
			{
				if (AllImplicants[k].minterms[L].binaryminterm == AllImplicants[i].minterms[S].binaryminterm)
				{
					AllImplicants[k].minterms[L].inclusion = AllImplicants[k].minterms[L].inclusion - 1;
				}
			}
		}
	}
}
void GetEssentialPrimeImplicants()
{
	//cout << "After removing duplicate implicants " << endl;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		//cout << "Implicant " << i << " with minterms ";
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
			//cout << AllImplicants[i].minterms[j].binaryminterm << " ";
		;//cout << endl;
	}

	int NumberOfMintermsIncludedinOtherImplicants = 0;

	for (int i = 0; i < AllImplicants.size(); i++)
	{
		NumberOfMintermsIncludedinOtherImplicants = 0;
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			//cout << "inclusion of minterm  " << j << " is = " << AllImplicants[i].minterms[j].inclusion << " in implicant  " << i << endl;
			if (AllImplicants[i].minterms[j].inclusion > 1)
				NumberOfMintermsIncludedinOtherImplicants++;
		}

		if (NumberOfMintermsIncludedinOtherImplicants == AllImplicants[i].Size)
		{
			DecreaseInclusionOfMintermsInDeletedImplicant(i);
			AllImplicants.erase(AllImplicants.begin() + i);
			--i;
			//cout << "erase" << endl;
		}
	}
	//cout << "After deletion" << endl;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			string minterm = AllImplicants[i].minterms[j].binaryminterm;
			//cout << minterm << " ";
		}
		//cout << i << endl;
	}
}
void GetFinalExpression()
{
	string express="";
	string* MintermsInPI;
	string PI = "";
	int NumOfMinterms;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		cout<<"group "<<i+1<<": [";
		ofs<<"group "<<i+1<<": [";
		NumOfMinterms = AllImplicants[i].minterms.size();
		MintermsInPI = new string[AllImplicants[i].minterms.size()];
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			MintermsInPI[j] = AllImplicants[i].minterms[j].binaryminterm;
			//cout << MintermsInPI[j];
		}

		int NoChange = 0;

		for (int L = 0; L < 4; L++)
		{
			int m = 0;
			for (int k = 1; k < NumOfMinterms; k++)
			{
				//cout << endl << "MintermsInPI[m][L] == MintermsInPI[k][L]" << MintermsInPI[m][L] << " " << MintermsInPI[k][L] << endl;
				if (MintermsInPI[m][L] == MintermsInPI[k][L])
				{
					NoChange++;
				}
			}


			//cout << "No change " << NoChange << endl;

			if (NoChange == NumOfMinterms - 1)
			{
				if (MintermsInPI[0][L] == '0')
				{
					PI += char(L + 97);
					PI += "\'";
					express+=char(L+97);
					express+="\'";
				}
				else if (MintermsInPI[0][L] == '1')
				{
					PI += char(L + 97);
					express+=char(L+97);
				}
			}
			NoChange = 0;
		}
		PI += " + ";
		for(int w = 0 ; w < AllImplicants[i].minterms.size();w++){
			if(w==NumOfMinterms-1){
				cout<<AllImplicants[i].minterms[w].DecimalMinterm;
				ofs<<AllImplicants[i].minterms[w].DecimalMinterm;
				continue;
			}
			cout<<AllImplicants[i].minterms[w].DecimalMinterm<<", ";
			ofs<<AllImplicants[i].minterms[w].DecimalMinterm<<", ";
		}
		cout<<"]"<<endl;
		ofs<<"]"<<endl;
		cout<<"simplification of group "<<i+1<<" ->"<<express<<endl;
		ofs<<"simplification of group "<<i+1<<" ->"<<express<<endl;
		express="";
	}
	FinalExpression = PI;
	FinalExpression = FinalExpression.erase(FinalExpression.size() - 2);
}