
// ------------ written 2005 

// Matrix C_{m+1,n+1} records the total number of subsequences
// n := alphabet length
// m := sequence length

// Algorithm:
// + C[0][0] = 1; i = 1;
// + For each character in the sequence
// + update column C[i][1..n-1] with C[i-1][1..n-1]
// + index C[i][j] with j := position in alphabet(current character)
// + C[i][0] = (C[i-1][0] - C[i-1][j]) + C[i-1][0]
// + C[i][j] = (C[i-1][0] - C[i-1][j]) + C[i-1][j]
// + i = i+1

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <cstdlib>
#include <cstdio>
using namespace std;

typedef long long u64;


class SubSequencer 
{
    public: 
        SubSequencer(vector<char> sequence, vector<char> alphabet)
        {
            this->sequence = sequence;
            this->alphabet = alphabet;
        }
        
        SubSequencer()
        {
            
        }
    
        ~SubSequencer()
        {
        
        }
        
        vector<char> getSequence()
        {
            return sequence;
        }
     
        vector<char> getAlphabet()
        {
            return alphabet;
        }
     
        u64 subSequence(u64 n, u64 m)
        {
            u64 size = (m+1)*(n+1);
            C = new u64[size];	

            for (int i = 0; i < m+1; i++)
                for (int j = 0; j < n+1; j++)
                    C[c2n(i,j)] = 0;

            C[c2n(0,0)] = 1;
            int i = 1, j = 1;

            for (int k = 0; k < sequence.size(); k++, i++)
            {
                j = position(sequence[k])+1;

                for (int p = 1; p < n+1; p++)
                {
                    C[c2n(i,p)] = C[c2n(i-1,p)];
                    if (p != j)
                        C[c2n(i-1,p)] = 0;
                }

                u64 d = C[c2n(i-1,0)] - C[c2n(i-1,j)];
                C[c2n(i,0)] = d + C[c2n(i-1,0)];
                C[c2n(i,j)] = d + C[c2n(i-1,j)];
                C[c2n(i-1,0)] = 0;
                C[c2n(i-1,j)] = 0;
            }

            u64 res = C[c2n(m,0)];
            delete [] C;

            return res;
        }
        
        void read(FILE *file)
        {
            char c;
            
            while (c != EOF)
            {
                c = getc(file);
	
                if (position(c) == -1)
                    alphabet.push_back(c);
                sequence.push_back(c);
            }
	
            sequence.pop_back(); sequence.pop_back();
            alphabet.pop_back(); alphabet.pop_back();
            
        }
    
    private: 
        int position(char c) {
            for (unsigned i = 0; i < alphabet.size(); ++i)
                if (c == alphabet[i])
                    return i;
            return -1;
        }

        int c2n(int i, int j) {
            return i*(alphabet.size()+1) + j;
        }
    
        u64 *C;
        vector<char> sequence;    
        vector<char> alphabet;
};



int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Missing filename!" << endl;
		return 1;
	}

	FILE *file = fopen(argv[1], "r");
	char c;	
    
	u64 m = 0, n;
    
    SubSequencer subsequencer;
    subsequencer.read(file);

	cout << endl;

	m = subsequencer.getSequence().size();
	n = subsequencer.getAlphabet().size();

	cout << "=> alphabet size: " << n << "\n"
		<< "=> sequence length: " << m << "\n"
		<< "=================================\n";
	cout << "number of subsequences: " << subsequencer.subSequence(n, m) << endl;

	return 0;
}


