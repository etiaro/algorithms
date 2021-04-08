#include <vector>
using namespace std;
//ZŁOŻONOŚĆ O(log2(n))

//wyszukuje zadanej wartosci w uporządkowanym ciągu

//I assume v is 00......011....1

int binSearch(vector<bool> &v) {  //first 1
    int l = 0, r = v.size();
    while (l != r) {
        int s = (l + r) / 2;
        if (v[s])
            r = s;
        else
            l = s + 1;
    }
}

//SECOND VER. you add 1, cause you modify r not l(so case l=1,r=2 won't stuck)
int binSearch2(vector<bool> &v) {  //last 0
    int l = 0, r = v.size();
    while (l != r) {
        int s = (l + r + 1) / 2;
        if (v[s])
            r = s - 1;
        else
            l = s;
    }
}
