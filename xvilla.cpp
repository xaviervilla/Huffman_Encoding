#include <iostream>
#include <tuple>
#include <vector>
#include <limits.h>
#include <bits/stdc++.h>

using namespace std;

// Reference #1 used for my code: https://www.geeksforgeeks.org/implement-min-heap-using-stl/
//  - This reference helped me use the built-in STL priority_queue data structure.

// Reference #2 used for my code: https://marknelson.us/posts/1996/01/01/priority-queues.html
//  - This reference helped me print using the traversal function of the root node.

struct Symbol
{
    int freq;
    int index;
    Symbol *leftChild;
    Symbol *rightChild;
    string code;

    Symbol(int freq, int index, Symbol* leftChild=0, Symbol* rightChild=0){
        this->freq = freq;
        this->index = index;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
    }
    
    int getFreq() const { return freq; }
    int getIndex() const { return index; }
    // This is the traversal function to print 1 or 0
    void traverse( string* codes, string code = "" ) {
    if ( this->leftChild ) {
        this->leftChild->traverse( codes, code + '0' );
        this->rightChild->traverse( codes, code + '1' );
    } else {
        // cout << " " << index << "      ";
        // cout << setw( 2 ) << freq;
        // cout << "     " << code << endl;
        this->code = code;
        codes[index] = code;
    }
}
};

class myCmp
{
public:
    int operator() (const Symbol& s1, const Symbol& s2){ 
        if (s1.getFreq() == s2.getFreq()) {
            return s1.getIndex() > s2.getIndex();
        }
        else{
            return s1.getFreq() >= s2.getFreq();
        } 
    }
};

void huffman(int size, int* arr, string* codes)
{
    // create a priority que of Symbols with our special comparator
    priority_queue <Symbol, vector<Symbol>, myCmp> minPQ;

    // fill our que with the values
    for (int i = size-1; i >= 0; i--){
        minPQ.push(Symbol(arr[i], i));
    }

    // cout << "Popping my Min Priority Que until there is only one Symbol left" << endl;

    int i = INT16_MIN;
    while (minPQ.size() > 1){
        Symbol* l = new Symbol(minPQ.top());
        minPQ.pop();
        Symbol* r = new Symbol(minPQ.top());
        minPQ.pop();
        // cout << "L: freq:" << l->getFreq() << " index:" << l->getIndex() << endl;
        // cout << "R: freq:" << r->getFreq() << " index:" << r->getIndex() << endl << endl;
        minPQ.push( Symbol( l->getFreq()+r->getFreq(), i, l, r ) );
        i--;
    }

    // cout << "printing my queue" << endl;
    
    Symbol head = minPQ.top();
    head.traverse(codes);

}

int main(int argc, char const *argv[])
{
    // Get size and input frequencies
    int size;
    cin >> size;
    int arr[size];
    for (int i=0; i<size; i++){ cin >> arr[i]; }
    
    // return the Hoffman codes we want.
    string codes[size];
    // codes = huffman(size, arr);
    huffman(size, arr, codes);

    // print the codes
    // for (int i=0; i<size; i++){ cout << arr[i] << " -> " << codes[i] << endl; }
    for (int i=0; i<size; i++){ cout << codes[i] << endl; }
    
    return 0;
}
