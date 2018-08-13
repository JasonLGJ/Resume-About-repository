#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
  
  
  
/////////////The definiton of user data////  
#define Cmax 100   //certain maximal value  
#define Cmin 0   //certain minimum value  
  
#define LENGHT1  3  //the chromosome length of 1st variable  
#define LENGHT2  3  //the chromosome length of 2nd variable  
  
//��Ⱦ�峤��  
#define CHROMLENGTH LENGHT1+LENGHT2   
const int MaxGeneration = 100;  //������  
const int PopSize = 10;  //������С  
const double Pc = 0.6; //�������  
const double Pm = 0.001; //�������  
  
  
  
////////////// ���ݽṹ����///////////////////  
struct Individual{  
    char chrom[CHROMLENGTH + 1];  //һ�������Ⱦɫ��  
    double value;  //Ŀ��ֵ  
    double fitness;  //��Ӧ��  
};  
  
int generation ;  //��������  
int bestIndex;  //��ø�����±�  
int worstIndex;  //�������α�  
  
Individual bestIndividual ;  //��ǰһ���е���ø���  
Individual worstIndividual ;  ///��ǰһ���еĻ�����  
// best individual by now   
Individual currentBest ;// ��ĿǰΪֹ����ø���  
Individual  population [PopSize]  ;//����  
  
  
///////////////////////  
void generateInitialPopulation();  
void generateNextPopulation();  
void evalutePopulation();  
long decomdeChromosome(char*, int, int);  
void calculateObjectValue();  
void calculateFitnessValue();  
void findBestAndWorstIndividual();  
void performEvolution();  
void selectionOperator();  
void crossoverOperator();  
void mutationOperator();  
void outputTextReport();  
//////////////////////////////////////////////  
  
  
int main(){  
    generation = 0;  
    generateInitialPopulation();  
    evalutePopulation();  
    while (generation < MaxGeneration) {  
        generation++;  
        generateNextPopulation();  
        evalutePopulation();  
        performEvolution();  
        outputTextReport();  
    }  
    return 0;  
}  
  
  
//////////////////////////////////////////////////////////////  
  
//////������һ������/////  
void generateInitialPopulation() {  
    int i, j;  
    srand((unsigned)time(NULL));  
    for (i = 0; i < PopSize; i++) {  
        for (j = 0; j < CHROMLENGTH; j++) {  
            population[i].chrom[j] = ((rand() % 10) < 5) ? '0' : '1';  
        }  
        population[i].chrom[CHROMLENGTH] = '/0';  
    }  
  
}  
  
  
////////������һ������ //////  
void generateNextPopulation() {  
    selectionOperator();  
    crossoverOperator();  
    mutationOperator();  
}  
  
//��������//  
void mutationOperator() {  
    int i, j;  
    double p;  
    // bit mutation  
    for (i = 0; i < PopSize; i++) {  
        for (j = 0; j < CHROMLENGTH; j++) {  
            p = rand() % 1000 / 1000.0;  
            if (p < Pm) {  
                population[i].chrom[j] = (population[i].chrom[j] == '0') ? '1': '0';  
            }  
        }  
    }  
  
}  
  
//��������///  
void crossoverOperator() {  
    int i, j;  
    int index[PopSize];  
    int point, temp;  
    double p;  
    char ch;  
    for (i = 0; i < PopSize; i++) {  
        index[i] = i;  
    }  
    for (i = 0; i < PopSize; i++) {  
  
        point = rand() %(PopSize - i);  
        temp = index[i];  
        index[i] = index[point + i];  
        index[point + i] = temp;  
    }  
    for (i = 0; i < PopSize - 1; i+=2) {  
        p = rand() % 1000 / 1000.0;  
        if (p < Pc) {  
            point = rand()% (CHROMLENGTH - 1) + 1;  
            for (j = point; j < CHROMLENGTH; j++) {  
                ch = population[index[i]].chrom[j];  
                population[index[i]].chrom[j] = population[index[i + 1]].chrom[j];  
                population[index[i + 1]].chrom[j] = ch;  
            }  
        }  
    }  
}  
  
///ѡ������/////////////  
void selectionOperator() {  
    int i, index;  
    double p, sum = 0.0;  
    double cfitness[PopSize];  
    Individual newpopulation[PopSize];  
    for (i = 0; i < PopSize; i++) {  
        sum += population[i].fitness;  
    }  
    for (i = 0; i < PopSize; i++) {  
        cfitness[i] = population[i].fitness / sum;  
    }  
    // calculate cumulative fitness   
    for (i = 1; i < PopSize; i++) {  
        cfitness[i] = cfitness[i] + cfitness[i - 1];  
    }  
    for (i = 0; i < PopSize; i++) {  
        p = rand() % 1000 / 1000.0;  
        index = 0;  
        while (p > cfitness[index]) {  
            index++;  
        }  
        newpopulation[i] = population[index];  
    }  
    for (i = 0; i < PopSize; i++) {  
        population[i] = newpopulation[i];  
    }  
}  
  
  
/////����ĳЩ��ʽ��������������////  
void evalutePopulation() {  
    calculateObjectValue();  
    calculateFitnessValue();  
    findBestAndWorstIndividual();  
}  
  
  
  
//�ҳ���ĿǰΪֹ��õĸ���//////  
void findBestAndWorstIndividual() {  
  
    int i;  
    double sum = 0.0;  
    bestIndividual = population[0];  
    worstIndividual = population[0];  
    for (i = 0; i < PopSize; i++) {  
        if (population[i].fitness > bestIndividual.fitness) {  
            bestIndividual = population[i];  
            bestIndex = i;  
        } else if (population[i].fitness < worstIndividual.fitness) {  
            worstIndividual = population[i];  
            worstIndex = i;  
        }  
        sum += population[i].fitness;  
    }  
    if (generation == 0) {  
        currentBest = bestIndividual;  
    } else {  
        if (bestIndividual.fitness > currentBest.fitness) {  
            currentBest = bestIndividual;  
        }  
    }  
  
}  
  
//������Ӧ��///  
void calculateFitnessValue() {  
    int i;  
    long temp1, temp2;  
    double x1, x2;  
    for (i = 0; i < PopSize; i++) {  
        temp1 = decomdeChromosome(population[i].chrom, 0, LENGHT1);  
        temp2 = decomdeChromosome(population[i].chrom, LENGHT1, LENGHT2);  
        x1 = temp1 * temp1;  
        x2 = temp2 * temp2;  
        population[i].fitness = x1+x2;  
    }  
  
}  
  
//����Ŀ��ֵ  
//Ŀ�꺯��Ϊf(x) = x1* x1 +  x2*x2  
void calculateObjectValue() {  
    int i;  
    long temp1, temp2;  
    double x1, x2;  
    for (i = 0; i < PopSize; i++) {  
        temp1 = decomdeChromosome(population[i].chrom, 0, LENGHT1);  
        temp2 = decomdeChromosome(population[i].chrom, LENGHT1, LENGHT2);  
        x1 = temp1 * temp1;  
        x2 = temp2 * temp2;  
        population[i].value = x1 + x2;  
    }  
  
}  
  
//�Ѷ�����ת��Ϊʮ����  
long decomdeChromosome(char* string, int point, int length) {  
    int i;  
    long decimal = 0L;  
    char * pointer;  
    for(i = 0, pointer=string+point; i < length;i++,pointer++){  
        decimal += (*pointer - '0') << (length - 1 - i);  
    }  
    return decimal;  
}  
  
  
//����ͬʱ���������Ŀǰ��ø������///  
void performEvolution() {  
    if (bestIndividual.fitness > currentBest.fitness) {  
        currentBest = population[bestIndex];  
    } else {  
        population[worstIndex] = currentBest;  
    }  
}  
  
  
//��ӡ��ǰ������Ϣ///  
void outputTextReport() {  
    int i;  
    double sum;  
    double average;  
  
    sum = 0.0;  
    for (i = 0; i < PopSize; i++) {  
        sum += population[i].value;  
    }  
    average = sum / PopSize;  
    printf("gen=%d, avg=%f, best=%f",generation, average,currentBest.value);  
    printf(" chromosome=");  
    for(  i = 0; i < CHROMLENGTH; i++){  
        printf("%c", currentBest.chrom[i]);  
    }  
    printf("\n");
  
}  