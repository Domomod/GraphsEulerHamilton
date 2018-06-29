/*
 AdjacencyList.hpp
 Graphs
 
 Copyright � 2018  Dominik Witczak
 
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
 */

#pragma once

#include <iostream>
#include <list>
#include <stack>


/*
Adjacency List is a Graph Representation, read more at: https://en.wikipedia.org/wiki/Adjacency_list
#Variables:
---------------------------------------------------------------------------------------
lists (STL list of int): 
    pointer to table of adjacency list, one for every node in the graph
size (int):
    number of nodes
visited (int*):
    pointer to a table for DFS traversal, declared as a member variable, because DFS 
    itself is implemented recursively and need this table in every lever of recursion,
        this table contains a map of visited nodes
predecessors (int*):
    pointer to a table for BFS traversal, declared as a member variable,
        each position of the table contains a number of predecessors so far not visited 
sorted (int*):
    pointer to a table containing a traversal (BFS or DFS)
type (int):
    type of adjacecny matrix, base on the enumerator:
        NEXT - list of succesors
        PREV - list of predecesors
        NOINCIDENCY - list of nodes with which there is no connection to current node
#Methods:
---------------------------------------------------------------------------------------
constructor:
    create a graph from a linear sequence of nodes.
destructor:
    frees memory
bool connected(int, int):
    check if edge exists

void print_list(void):
    print all stored Adjacency lists

list<int>::iterator firstOnTheList(int n)
    return begining of n'th list 

list<int>::iterator lastOnTheList(int n)
    return end of n'th list 

list<int>::iterator nextOnTheList(int n):
    return next on the n'th list, after iterating through whole
    list, loop to the begining

void Hamilton(int, bool):
    int is starting point
    find Hamilton cycle if bool == true
    find all Hamilton cycles if bool == false

void Euler(int):
    int is starting point, 
    find an Euler cycle
*/


class AdjacencyList {
    friend class GraphMatrix;
private:
    std::list<int> *lists;
    int size;
    
    std::stack<int> temp_euler;
    std::list<int> sol_euler;
    
    
    int *visited;
    int *predecessors;
    
    int *sorted;
    int *sol;
protected:
public:
    AdjacencyList(int *tab, int size_of_tab, int _size);
    ~AdjacencyList();
    
    void print_list();
    
    std::list<int>::iterator firstOnTheList(int whichList);
    std::list<int>::iterator lastOnTheList(int whichList);
    
    std::list<int>::iterator nextOnTheList(int whichList);
    
    bool connected(int a, int b);
    
    int getv(std::list<int>::iterator p) {
        return *&*p;
    }
    
    void Hamilton(int i,bool boo);
    
    void Euler(int v);
    
    
    int type;
    enum {
        NEXT,
        PREV,
        NOINCIDENCY
    };
};
