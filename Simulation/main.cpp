#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "queue.h"
#include "stack.h"
using namespace std;

const unsigned int MAX_T = 500;
unsigned int seed = time(NULL);

void readFromFile(string filename, ofstream &out, int &averageAmount, int &averagePrice, int &priceDevation, int &amountDevation, int &surcharge);
int randomValue(int max, bool beNegative);
double FIFOmethod(ofstream &out, int averageAmount, int averagePrice, int priceDevation, int amountDevation, int surcharge);
double LIFOmethod(ofstream &out, int averageAmount, int averagePrice, int priceDevation, int amountDevation, int surcharge);

int main()
{
    int averageAmount, averagePrice, priceDevation, amountDevation, surcharge;
    double profitFIFO = 0, profitLIFO = 0;

    ofstream file("protokolas.txt"); 

    system("cls");
    cout << "Pijus Zlatkus, 4 grupe 2 pogrupis, 3 uzdavinis 12 variantas." << endl;
    cout << "Uzduotis - grudu sandelis (ADT: stekas, eile)."<< endl;
    cout << "Programos tikslas istirti, kuris grudu apskaitos metodas yra geresnis tarp FIFO (first-in, first-out) ir LIFO (last-in, first-out) supirkimo metodu." << endl << endl;
    cout << "Pradiniai duomenys:" << endl;

    file << "PIRMA DALIS. Duomenys" << endl;
    file << "  1) Pijus Zlatkus, 4 grupe 2 pogrupis, 3 uzdavinis 12 variantas." << endl;
    file << "  2) Uzduotis - grudu sandelis (ADT: stekas, eile)."<< endl;
    file << "  3) Programos tikslas istirti, kuris grudu apskaitos metodas yra geresnis tarp FIFO (first-in, first-out) ir LIFO (last-in, first-out) supirkimo metodu." << endl;

    readFromFile("test.txt", file, averageAmount, averagePrice, priceDevation, amountDevation, surcharge);

    file << endl << "ANTRA DALIS. Vykdymas" << endl;
    file << endl << "FIFO supirkimo metodas:" << endl;
    profitFIFO = FIFOmethod(file, averageAmount, averagePrice, priceDevation, amountDevation, surcharge);
    file << endl << "LIFO supirkimo metodas:" << endl;
    profitLIFO = LIFOmethod(file, averageAmount, averagePrice, priceDevation, amountDevation, surcharge);

    file << endl << "TRECIA DALIS. Rezultatai" << endl;
    file << "  1) Is viso imone prekiavo " << MAX_T << " dienu" << endl;
    cout << endl << "Is viso imone prekiavo " << MAX_T << " dienu" << endl;
    file << "  2) FIFO supirkimo pelnas: " << fixed << setprecision(2) << profitFIFO << " Eur" << endl;
    cout << "FIFO supirkimo pelnas: " <<  fixed << setprecision(2) << profitFIFO << " Eur" << endl;
    file << "  3) LIFO supirkimo pelnas: " <<  fixed << setprecision(2) << profitLIFO << " Eur" << endl;
    cout << "LIFO supirkimo pelnas: " <<  fixed << setprecision(2) << profitLIFO << " Eur" << endl;

    if(profitFIFO == profitLIFO)
    {
        file << "  4) Abiem apskaitos metodais gautas vienodas pelnas " << endl;
        cout << "Abiem apskaitos metodais gautas vienodas pelnas " << endl;
    }
    else if (profitFIFO > profitLIFO)
    {
        file << "  4) Didesnis pelnas gautas FIFO metodu" << endl;
        cout << "Didesnis pelnas gautas FIFO metodu" << endl;
    }
    else
    {
        file << "  4) Didesnis pelnas gautas LIFO metodu" << endl;
        cout << "Didesnis pelnas gautas LIFO metodu" << endl;
    }

    return 0;
}

void readFromFile(string filename, ofstream &out, int &averageAmount, int &averagePrice, int &amountDevation, int &priceDevation, int &surcharge)
{
    ifstream file(filename);

    if(!file)
    {
        cout << "Failo " << filename << " neimanoma atidaryti" << endl;
        out << endl << "TRECIA DALIS. Rezultatai" << endl;
        out << "  1) Programa sekmingai nebaige darbo" << endl;
        cout << "Uzdaroma programa..." << endl;
        exit(0);
    }


    string tmp;
    file >> averageAmount;
    cout << "Superkamu grudu norma: " << averageAmount << " t" << endl;
    out << "  4) Superkamu grudu norma: " << averageAmount << " t" << endl;
    getline(file, tmp);
    file >> amountDevation;
    cout << "Superkamu grudu kiekio maksimalus nuokrypis: " << amountDevation << "%" << endl;
    out << "  5) Superkamu grudu kiekio maksimalus nuokrypis: " << amountDevation << "%" << endl;
    getline(file, tmp);

    file >> averagePrice;
    cout << "Supirkimo kaina: " << averagePrice << " Eur/t" << endl;
    out << "  6) Supirkimo kaina: " << averagePrice << " Eur/t" << endl;
    getline(file, tmp);
    file >> priceDevation;
    cout << "Supirkimo kainos maksimalus nuokrypis: " << priceDevation << "%" << endl;
    out << "  7) Supirkimo kainos maksimalus nuokrypis: " << priceDevation << "%" << endl;
    getline(file, tmp);

    file >> surcharge;
    cout << "Grudu kainos antkainis: " << surcharge << "%" << endl;
    out << "  8) Grudu kainos antkainis: " << surcharge << "%" << endl;
    getline(file, tmp);
    file.close();
}

int randomValue(int max, bool beNegative)
{
    int value;
    seed = seed * 1103515245 + 12345;

    if(beNegative == true)
    {
        value = ((seed / 65536) % 32768) % ((max * 2) + 1) - max;
    }
    else
    {
        value = ((seed / 65536) % 32768) % (max + 1);
    }


    return value;
}

double FIFOmethod(ofstream &out, int averageAmount, int averagePrice, int priceDevation, int amountDevation, int surcharge)
{
    double profit = 0;
    double totalAmount = 0;
    double buyAmount, buyPrice;
    double sellAmount;
    double dailyProfit;

    int error;
    queue* grainAmount = createQueue(MAX_T, &error);
    queue* grainPrice = createQueue(MAX_T, &error);

    if(error == 1)
    {
        cout << "Klaida su atminties priskirimu" << endl;
        out << endl << "TRECIA DALIS. Rezultatai" << endl;
        out << "  1) Programa sekmingai nebaige darbo" << endl;
        cout << "Uzdaroma programa..." << endl;
        exit(0);
    }

    double tempAmount;
    double tempPrice;

    for(int t = 1; t <= MAX_T; ++t)
    {
        out << "  T = " << t << endl;

        buyAmount = (double) averageAmount * (1 + ((double) randomValue(amountDevation, true) / 100));
        buyPrice = (double) averagePrice * (1 + ((double) randomValue(priceDevation, true) / 100));
        enqueue(grainAmount, buyAmount, &error);
        enqueue(grainPrice, buyPrice, &error);
        totalAmount += buyAmount;

        out << "    1) Nupirkta " << fixed << setprecision(2) << buyAmount << " t grudu uz " << fixed << setprecision(2) << buyAmount * buyPrice << " Eur" << endl;

        sellAmount = totalAmount * ((double) randomValue(100, false) / 100);
        totalAmount -= sellAmount;
        dailyProfit = 0;
        out << "    2) Parduota " << fixed << setprecision(2) << sellAmount << " t grudu uz ";

        while(!(sellAmount < 0.0001))
        {
            if(sellAmount >= getQueueFirstElement(grainAmount, &error))
            {
                sellAmount -= getQueueFirstElement(grainAmount, &error);
                dailyProfit += getQueueFirstElement(grainAmount, &error) * getQueueFirstElement(grainPrice, &error) * (1 + (double) surcharge / 100);
                dequeue(grainAmount, &error);
                dequeue(grainPrice, &error);
            }
            else
            {
                grainAmount->front->data -= sellAmount;
                dailyProfit += sellAmount * getQueueFirstElement(grainPrice, &error) * (1 + (double) surcharge / 100);
                sellAmount = 0;
            }
        }

        profit += dailyProfit - (buyAmount * buyPrice);
        out << fixed << setprecision(2) << dailyProfit << " Eur" << endl;
        out << "    3) Dienos pelnas: " << fixed << setprecision(2) << dailyProfit - (buyAmount * buyPrice) << " Eur" << endl << endl;
    }

    return profit;
}

double LIFOmethod(ofstream &out, int averageAmount, int averagePrice, int priceDevation, int amountDevation, int surcharge)
{
    double profit = 0;
    double totalAmount = 0;
    double buyAmount, buyPrice;
    double sellAmount;
    double dailyProfit;

    int error;
    stack* grainAmount = createStack(MAX_T, &error);
    stack* grainPrice = createStack(MAX_T, &error);

    if(error == 1)
    {
        cout << "Klaida su atminties priskirimu" << endl;
        out << endl << "TRECIA DALIS. Rezultatai" << endl;
        out << "  1) Programa sekmingai nebaige darbo" << endl;
        cout << "Uzdaroma programa..." << endl;
        exit(0);
    }

    stack* tempAmount = createStack(MAX_T, &error);
    stack* tempPrice = createStack(MAX_T, &error);

    double numerator = 0;
    double denominator = 0;

    int rand;
    for(int t = 1; t <= MAX_T; ++t)
    {
        out << "  T = " << t << endl;

        buyAmount = (double) averageAmount * (1 + ((double) randomValue(amountDevation, true) / 100));

        buyPrice = (double) averagePrice * (1 + ((double) randomValue(priceDevation, true) / 100));

        pushStack(grainAmount, buyAmount, &error);
        pushStack(grainPrice, buyPrice, &error);
        totalAmount += buyAmount;

        out << "    1) Nupirkta " << fixed << setprecision(2) << buyAmount << " t grudu uz " << fixed << setprecision(2) << buyAmount * buyPrice << " Eur" << endl;

        sellAmount = totalAmount * ((double) randomValue(100, false) / 100);
        totalAmount -= sellAmount;
        dailyProfit = 0;
        out << "    2) Parduota " << fixed << setprecision(2) << sellAmount << " t grudu uz ";

        while(!(sellAmount < 0.0001))
        {

            if(sellAmount >= peekStack(grainAmount, &error))
            {
                numerator = 0;
                denominator = 0;
                sellAmount -= peekStack(grainAmount, &error);

                double temp = 0;
                for(int i = 1, j = getStackSize(grainAmount, &error); i <= j ;++i)
                {
                    numerator += peekStack(grainAmount, &error) * peekStack(grainPrice, &error);
                    denominator += peekStack(grainAmount, &error);

                    temp = popStack(grainAmount, &error);
                    pushStack(tempAmount, temp, &error);
                    temp = popStack(grainPrice, &error);
                    pushStack(tempPrice, temp, &error);
                }

                for(int i = 1, j = getStackSize(tempAmount, &error); i <= j ;++i)
                {
                    temp = popStack(tempAmount, &error);
                    pushStack(grainAmount, temp, &error);
                    temp = popStack(tempPrice, &error);
                    pushStack(grainPrice, temp, &error);
                }

                dailyProfit += peekStack(grainAmount, &error) * (numerator / denominator) * (1 + (double) surcharge / 100);
                popStack(grainAmount, &error);
                popStack(grainPrice, &error);
            }
            else
            {
                numerator = 0;
                denominator = 0;
                grainAmount->top->data -= sellAmount;

                double temp = 0;
                for(int i = 1, j = getStackSize(grainAmount, &error); i <= j ;++i)
                {
                    numerator += peekStack(grainAmount, &error) * peekStack(grainPrice, &error);
                    denominator += peekStack(grainAmount, &error);

                    temp = popStack(grainAmount, &error);
                    pushStack(tempAmount, temp, &error);
                    temp = popStack(grainPrice, &error);
                    pushStack(tempPrice, temp, &error);
                }

                for(int i = 1, j = getStackSize(tempAmount, &error); i <= j ;++i)
                {
                    temp = popStack(tempAmount, &error);
                    pushStack(grainAmount, temp, &error);
                    temp = popStack(tempPrice, &error);
                    pushStack(grainPrice, temp, &error);
                }

                dailyProfit += sellAmount * (numerator / denominator) * (1 + (double) surcharge / 100);

                sellAmount = 0;
            }
        }

        profit += dailyProfit - (buyAmount * buyPrice);
        out << fixed << setprecision(2) << dailyProfit << " Eur" << endl;
        out << "    3) Dienos pelnas: " << fixed << setprecision(2) << dailyProfit - (buyAmount * buyPrice) << " Eur" << endl << endl;
    }

    return profit;
}