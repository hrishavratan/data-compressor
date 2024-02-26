#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;
struct trie
{
    int freq;
    char data;
    const trie *left, *right;
    trie(char d, int f = -1)
    {
        data = d;
        freq = f;
        left = NULL;
        right = NULL;
    }
    trie(const trie *c0, const trie *c1)
    {
        data = 0;
        freq = c0->freq + c1->freq;
        left = c0;
        right = c1;
    }
    bool operator<(const trie &a) const
    { 
        return freq > a.freq;
    }
    void traverse(string code = "") const
    {
        if (left != NULL)
        {
            left->traverse(code + '0'); 
            right->traverse(code + '1'); 
        }
        else
        {
            cout << "Data: " << data << ", Frequency: " << freq << ", Code: " << code << endl;
        }
    }
};
void huffmanCoding(string str)
{
    priority_queue<trie> prq;
    int frequency[256];
    for (int i = 0; i < 256; i++)
        frequency[i] = 0; 
    for (int i = 0; i < str.size(); i++)
    {
        frequency[int(str[i])]++; 
    }
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i])
        {
            prq.push(trie(i, frequency[i]));
        }
    }
    while (prq.size() > 1)
    {
        trie *c0 = new trie(prq.top()); 
        prq.pop();
        trie *c1 = new trie(prq.top()); 
        prq.pop();
        prq.push(trie(c0, c1)); 
    }
    cout << "The Huffman Code: " << endl;
    prq.top().traverse();
}


int main()
{
    cout << "Enter the name of the file you wish to input" << endl;
    string file;
    cin >> file;
    ifstream inputFile(file);

    if (!inputFile.is_open())
    {
        cout << "Error opening the file!" << endl;
        return 1;
    }
    string fileContent, line;

    while (getline(inputFile, line))
    {
        fileContent += line + "\n";
    }
    inputFile.close();
    huffmanCoding(fileContent);
}