#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

//Huffman tree node
struct MinHeapNode{
    char data;
    int freq;

    MinHeapNode *left, *right;
    MinHeapNode (char data, int freq){
        left = right = NULL;
        this -> data = data;
        this -> freq = freq;
    }

};

//struct compare
struct compare{
    bool operator()(MinHeapNode *a, MinHeapNode *b){
        return (a->freq > b->freq);
    }

};
//printing huffman code
void printcodes(MinHeapNode* root, unordered_map<char,string>&huffmancodes, string str =" ") {
    if (!root ){
        return;
    }

    if(root->data != '\0'){
        huffmancodes[root->data] = str;
    }
    printcodes(root->left, huffmancodes,str+'0');
    printcodes(root->right, huffmancodes, str+'1');

}



//build huffman tree

MinHeapNode* generatehuffmancode(const unordered_map<char, int> freq){

    //create min heap
    struct MinHeapNode  *left, *right, *top;
    
    priority_queue<MinHeapNode*, vector<MinHeapNode*>,compare>minheap;


    //creat node for each

    for(const auto&entry : freq)
        minheap.push(new MinHeapNode(entry.first, entry.second));

    //itereate till 1 
    while(minheap.size() > 1){

        left = minheap.top();
        minheap.pop();

        right = minheap.top();
        minheap.pop();

        top= new MinHeapNode('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minheap.push(top);
        

    }

    //print node
    return(minheap.top());

}


//encode 
string encoded(const string& data, const unordered_map<char, string>& huffmancodes) {
    string encoded;
    for(char ch: data){
        encoded+=huffmancodes.at(ch);
    }
    return encoded;
}



//decode 
string decoded(const string& encoded, MinHeapNode* root){
    string decoded;
    MinHeapNode* curr=root;
    
    for(char ch:encoded){
        if(ch =='0'){
            curr = curr->left;
        }
        else if(ch =='1'){
            curr = curr->right;
        }
        

        if(curr->data !='\0'){
            decoded+=curr->data;
            curr=root;
        }
    }
    return decoded;
    
    
}



int main(){

    string input = "Hello, World!";
    unordered_map<char,int>FreqTable;

    for(char ch:input){
        FreqTable[ch]++;
    }

    MinHeapNode* HuffmanTree = generatehuffmancode(FreqTable);

    unordered_map<char,string> huffmancodes;
    printcodes(HuffmanTree, huffmancodes);

    //string encode 
    string encodedData= encoded(input,huffmancodes);

    string decodedData= decoded(encodedData,HuffmanTree);

    cout << "Input: " << input << endl;
    cout << "Encoded data: " << encodedData << endl;
    cout << "Decoded data: " << decodedData << endl;

    
}
