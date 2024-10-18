#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix {
public:
    Matrix(vector<vector<int> > a_): a(a_){};
    Matrix(){};

    vector<vector<int> > a;

    const Matrix operator+(const Matrix& right) {
        Matrix ret;
        for (size_t i = 0; i < this->a.size(); i++) {
            vector<int> tmp;
            for (size_t j = 0; j < this->a[i].size(); j++)
                tmp.push_back(this->a[i][j] + right.a[i][j]);
            ret.a.push_back(tmp);
        }
        return ret;
    };
};

int main () {
   int cases,k;
   cin >> cases;
   for(k=0;k<cases;k++) {
      Matrix x;
      Matrix y;
      Matrix result;
      int n,m,i,j;
      cin >> n >> m;
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         x.a.push_back(b);
      }
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         y.a.push_back(b);
      }
      result = x+y;
      for(i=0;i<n;i++) {
         for(j=0;j<m;j++) {
            cout << result.a[i][j] << " ";
         }
         cout << endl;
      }
   }  
   return 0;
}
