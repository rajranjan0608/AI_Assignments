#include<bits/stdc++.h>

using namespace std;

vector<double> averageData;
int totalGrp;

vector<double> averageMark(vector<vector<int>> subData) {
    int n = subData.size(), m = subData[0].size();

    vector<double> averageSubjectScore;
    for(int i = 0; i < n; i++){
        double total = 0;
        for(int j = 0; j < m; j++){
            total += subData[i][j];
        }
        averageSubjectScore.push_back(total / m);
    }
    return averageSubjectScore;
}

double fitness(vector<int> a);
vector<vector<int>> sortWithFit(vector<vector<int>> a);

bool compare(vector<int> a, vector<int> b) {
    return fitness(a) < fitness(b);
}

vector<vector<int>> crossover(vector<vector<int>> a){
    vector<vector<int>> crossedPopulation;
    int n=a.size(),m=a[0].size();
    crossedPopulation.resize(n,vector<int>(m));
    int cpop=rand()%m;
    for(int i=0;i<n;i+=2)
    {
        if(i+1<n)
        {
            for(int j=0;j<m;j++)
            {
                if(j<=cpop)
                {
                    crossedPopulation[i][j]=a[i][j];
                    crossedPopulation[i+1][j]=a[i+1][j];
                }else{
                    crossedPopulation[i][j]=a[i+1][j];
                    crossedPopulation[i+1][j]=a[i][j];
                }
            }
        }else{
            crossedPopulation[i]=a[i];
        }
    }
    return sortWithFit(crossedPopulation);
}

vector<vector<int>> sortWithFit(vector<vector<int>> a) {
    sort(a.begin(), a.end(), compare);
    return a;
}

void print(string x, vector<vector<int>> a) {
    cout << x << "\n";
    
    int n = a.size(), m = a[0].size();
    for(int i = 0; i<n; i++){
        for(int j = 0; j < m; j++){
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

vector<vector<int>> newPopulation(int totalStudents, int totalgroups, int newPopulationSize){

    vector<int> groupSize;
    groupSize.resize(totalgroups,0);

    vector<vector<int>> init;
    init.resize(newPopulationSize, vector<int>(totalStudents));

    for(int i = 0; i < newPopulationSize; i++){
        for(int j = 0; j < totalStudents; j++){
            init[i][j] = rand()%totalgroups;        
        }
        int x = rand()%totalStudents;
        for(int j = 0; j < totalgroups; j++){
            init[i][(j+x)%totalStudents] = j; 
        }
    }
    
    return sortWithFit(init);
}

vector<vector<int>> mutation(vector<vector<int>> a){
    int population=a.size(),totalStudents=a[0].size();
    int random=rand()%population;
    for(int i=0;i<random;i++){
        int p_index=rand()%population;
        int x=rand()%totalStudents;
        int y=rand()%totalStudents;
        int tmp=a[p_index][x];
        a[p_index][x]=a[p_index][y];
        a[p_index][y]=tmp;
    }
    return sortWithFit(a);
}

double fitness(vector<int> a){
    
    vector<double> averageGroupMarks;
    averageGroupMarks.resize(totalGrp, 0);

    vector<int> count; 
    count.resize(totalGrp,0);

    int n = a.size();

    for(int i = 0; i<n; i++){
        averageGroupMarks[a[i]] += averageData[i];
        count[a[i]]++;
    }

    for(int i = 0; i < totalGrp; i++){
        averageGroupMarks[i] /= count[i];
    }

    double fitVal = 0;

    for(int i=0;i<n;i++){
        fitVal+=abs(averageGroupMarks[a[i]]-averageData[i]);
    }
    
    return fitVal;
}

int main(){

    int totalStudents,totalSubjects,totalgroups;
    
    cout << "Number Of Students: "; cin >> totalStudents;
    cout << "Number Of Subjects: "; cin >> totalSubjects;
    cout << "Number Of Groups: "; cin >> totalgroups;

    totalGrp=totalgroups;
    if(totalgroups>totalStudents){
        cout << "Total groups should be less than equal to total number of students\n";
        return 0;
    }
    vector<vector<int>> student_data;
    student_data.resize(totalStudents,vector<int> (totalSubjects));
    
    for(int i=0;i<totalStudents;i++){
        cout << "Student " << i+1 << ":\n";

        for(int j=0; j < totalSubjects; j++){
            cout << "Subject " << j << ": "; cin >> student_data[i][j];
        }
    }
    vector<double> averageMarks ;
    averageMarks=averageMark(student_data);
    averageData=averageMarks;

    vector<vector<int>> initial_population;
    initial_population=newPopulation(totalStudents,totalgroups,5);
    
    
    
    print("Initial Population: ",initial_population);

    vector<vector<int>> crossedPopulation;
    crossedPopulation=crossover(initial_population);    
    
    print("1st Crossover Population: ",crossedPopulation);
    
    int break_while=0;
    int generation=1;
    while(true){
        generation++;
        for(int i=0;i<crossedPopulation.size();i++){
            int less=0;
            for(int j=0;j<initial_population.size();j++){
                if(fitness(crossedPopulation[i])<fitness(initial_population[j]))
                {   less=1;
                    break_while=0;
                    initial_population.pop_back();
                    initial_population.push_back(crossedPopulation[i]);
                    initial_population=sortWithFit(initial_population);
                    break;
                }
            }
            if(less==0)
            {   if(i==0)
                {
                    break_while++;
                }
                break;
            }
            
        }
        if(break_while>10)
        {
            break;
        }
        if(rand()%2)
        {
            initial_population=mutation(initial_population);
        }
        crossedPopulation=crossover(crossedPopulation);
    }
    cout<<"Avg_Marks: \n";
    for(int i=0;i<averageMarks.size();i++){
       
        cout<<averageMarks[i]<<" ";
    }
    cout<<endl;
    print("Final Population: ",initial_population);
    cout<<"Fitness Values Of Each Population in Final Population: \n";
    for(int i=0;i<initial_population.size();i++){
       
        cout<<fitness(initial_population[i])<<" ";
    }
    cout<<"\nGeneration "<<generation<<endl;

return 0;
}