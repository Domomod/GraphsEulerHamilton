/*
 AdjacencyList.hpp
 Graphs2.0
 
 Copyright � 2018  Dominik Witczak & Krzysztof Sychla
 
 This program is free software : you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.If not, see <https://www.gnu.org/licenses/>.

 This part was written by Krzysztof Sychla
 */


#include <iostream>
#include <fstream>
#include "AdjacencyList.hpp"
#include "Timer.hpp"

//Check if enough parameters were passed to program
//-------------------------------------------------------------
void usage(int argc, int ile){
    if(argc < ile){
        std::cout<<"Not enough parameters, exiting!\n";
        exit(0);
    }
}

//main function:
/*
argv[1]:
    Type of test: find Euler cycle, find first Hamilton cycle, find all Hamilton cycles
argv[2]:
    Data input file
argv[3]:
    Data output file
argv[4]:
    Input instance size
argv[5]:
    Number of nodes
*/
//-------------------------------------------------------------
int main(int argc, const char * argv[]) {
    usage(argc,6);

//Init:
//-------------------------------------------------------------   
    int number = atoi(argv[1]);
    std::fstream dane;
    std::fstream wynik;
    dane.open(argv[2],std::ios_base::in);
    wynik.open(argv[3],std::ios_base::app);
    
    int size = atoi(argv[4]);
    int size_of_graph = atoi(argv[5]);
    
    int *tab = new int [size];
    
    for(int i=0;i<size;i++)
        dane >> tab[i];
    AdjacencyList lista(tab,size,size_of_graph);
    
    Timer time;
    
    switch(number){
        case 0:
            time.StartTimer();
            lista.Euler(0);
            time.EndTimer();
            wynik<<"\t"<<time.GetDelta();
            break;
        case 1:
            time.StartTimer();
            lista.Hamilton(0,true);
            time.EndTimer();
            wynik<<"\t"<<time.GetDelta();
            break;
        case 2:
            time.StartTimer();
            lista.Hamilton(0, false);
            time.EndTimer();
            wynik<<"\t"<<time.GetDelta();
            break;
        default:
            std::cout<<"WRONG OPTION!!\n";
            break;
    }
    
    delete [] tab;
    dane.close();
    wynik.close();

    return 0;
}
