/*
 AdjacencyList.cpp
 Graphs
 
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

 This part was written by Dominik (the rest) and Krzysztof (constructor, partly Euler)
 */

#include"AdjacencyList.hpp"

AdjacencyList::AdjacencyList(int *tab, int size_of_tab, int _size){
    size = _size;
    type = 0;
    lists = new std::list<int>[size];
    int last = tab[0];
    int current;
    int first = tab[0];
    bool temp = false;
    
    for(int i=1;i<size_of_tab;i++){
        current = tab[i];
        if(temp){
            temp = false;
            first = tab[i];
            last = tab[i];
            continue;
        }
        if(current == first)
            temp = true;
        lists[last].push_back(current);
        lists[current].push_back(last);
        
        last = tab[i];
    }    
}

AdjacencyList::~AdjacencyList()
{
    for (int i = size; --i > 0;) {
        for (int j = 0; j < size; j++) {
            lists[i].clear();
        }
    }
}

void AdjacencyList::print_list(){
    for(int i = 0;i<size;i++){
        std::cout<< i <<" -> ";
        for(auto j = nextOnTheList(i);j!=lastOnTheList(i);j=nextOnTheList(i))
            std::cout<<getv(j)<<" -> ";
        std::cout<<".\n";
    }
    std::cout<<"\n";
    
}

//This is our attempt to write a "static" iterator, which can be used to 
//read list in a sequence from every function of our class, use with caution,
//Useful for recursive methods, as we won't need to pass iterator with every step,
//deleting a node might cause iterator to become invalid.
//--------------------------------------------------------------------------------
std::list<int>::iterator AdjacencyList::firstOnTheList(int whichList)
{
    return lists[whichList].begin();
}

std::list<int>::iterator AdjacencyList::lastOnTheList(int whichList)
{
    return lists[whichList].end();
}

std::list<int>::iterator AdjacencyList::nextOnTheList(int whichList) {
//intialisation, runs only on the first iteration
//-----------------------------------------------
    static bool firstExecution = true;
    static std::list<int>::iterator* pointers = new std::list<int>::iterator[size];
    if (firstExecution) {
        for (int i = 0; i < size; i++)
            pointers[i] = lists[i].begin();
        firstExecution = false;
    }
    
//actual function
//-----------------------------------------------
    //return next node
    if (pointers[whichList] != lists[whichList].end())
        return pointers[whichList]++;
    //set pointer on the begining of the list, and
    //return last node
    pointers[whichList] = lists[whichList].begin();
    return lists[whichList].end();
}

bool AdjacencyList::connected(int a, int b)
{
    //imposible to be fulfiled, one or more elements does not exist
    if (a >= size || b >= size) {
        return false;
    }
    
    //check every succesor of a (aka. look for b)
    for (auto succesor : lists[a]) {
        if (succesor == b)
            return true;
    }
    
    return false;
}


//WARNING: Hamilton's visited and public member visited is not the same variable
void AdjacencyList::Hamilton(int i,bool boo) {
//intialisation, runs only on the first iteration
//-----------------------------------------------
    static int idx = 0;
    static bool firstExecution = true;
    static bool completed = false;
    static int* sol = new int[size];
    static int* visited = new int[size];
    if (firstExecution) {
        firstExecution = false;
        for (int k = 0; k < size; k++) {
            sol[k] = 0;
        }
        for (int k = 0; k < size; k++) {
            visited[k] = 0;
        }
    }
    
//actual function
//-----------------------------------------------
    if (completed) { //if we were looking for only one Hamilton, 
    //just write if it's already known
        for (int k = 0; k < size; k++) {
            std::cout << sol[k] << " ";
        }
        return;
    }
    
    visited[i] = 1;
    sol[idx++] = i;
    if (idx == size) {
        if (connected(i, sol[0])) {
            //SUCCES HAMILTON FOUND
            completed = boo;
        }
        for (int k = 0; k < size; k++) {
            std::cout << sol[k] << " ";
        }
    }
     for (auto succesor : lists[i]) {
         if (!visited[succesor]) {
             Hamilton(succesor,boo);
         }
         if(completed)
             return;
    }
    visited[i] = 0;
    idx--;
    return;
}

void AdjacencyList::Euler(int v) {
    auto i = lists[v].begin();
    while (lists[v].size() != 0) {
        int suc = getv(lists[v].begin());//succesor
        lists[suc].remove(v);
        lists[v].remove(suc);
        Euler(suc);
    }
    std::cout<< v << " ";
}
