
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
#include <unordered_map>
#include <memory>
#include <fstream>

typedef long long u64;

class SubSequencer 
{
public: 
    SubSequencer(const std::vector<char>& sequence, const std::vector<char>& alphabet)
        : sequence(sequence), alphabet(alphabet) {
        for (size_t i = 0; i < alphabet.size(); ++i) {
            alphabet_map[alphabet[i]] = i;
        }
    }

    SubSequencer() {}
    
    std::vector<char> getSequence() const {
        return sequence;
    }

    std::vector<char> getAlphabet() const {
        return alphabet;
    }

    u64 subSequence(u64 n, u64 m) {
        std::vector<u64> C((m+1)*(n+1), 0);
        C[0] = 1;
        int i = 1, j = 1;

        for (size_t k = 0; k < sequence.size(); k++, i++) {
            j = position(sequence[k])+1;

            for (u64 p = 1; p < n+1; p++) {
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

        return C[c2n(m,0)];
    }
    
    void read(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Failed to open file\n";
            return;
        }

        char c;
        while (file.get(c)) {
            if (position(c) == -1)
                alphabet.push_back(c);
            sequence.push_back(c);
        }
        
        for (size_t i = 0; i < alphabet.size(); ++i) {
            alphabet_map[alphabet[i]] = i;
        }
    }
    
private: 
    int position(char c) const {
        auto it = alphabet_map.find(c);
        if (it != alphabet_map.end())
            return it->second;
        return -1;
    }

    int c2n(int i, int j) const {
        return i*(alphabet.size()+1) + j;
    }
    
    std::vector<char> sequence;    
    std::vector<char> alphabet;
    std::unordered_map<char, int> alphabet_map;
};

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Missing filename!\n";
        return 1;
    }

    SubSequencer subsequencer;
    subsequencer.read(argv[1]);

    u64 m = subsequencer.getSequence().size();
    u64 n = subsequencer.getAlphabet().size();

    std::cout << "=> alphabet size: " << n << "\n"
              << "=> sequence length: " << m << "\n"
              << "=================================\n"
              << "number of subsequences: " << subsequencer.subSequence(n, m) << "\n";

    return 0;
}



