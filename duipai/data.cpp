#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;
int id = 1;

int ra(){
    return rand()*id;
}

int main() {
    srand((unsigned int) time (NULL));
    freopen("data.in","w", stdout);
    freopen("dp.out","r", stdin);
    cin >> id;

    cout << "1\n";
    int n = ra() % 1000 + 1, m = ra() % 1+ 1, V = ra() % 1000 + 1, L = ra() % 1000 + 1 ;
    vector<int> M;
    for(int i = 0; i <= L; i ++) {
        if(ra()%5 == 0) M.push_back(i);
    }
    m = M.size();
    cout << n << " " << m << " " << L << " " << V << endl;
    for(int i = 1; i <= n; i ++) {
        int a = ra() % L, b = ra() % 2*V, c = ra()% V;
        if(ra()%2)c = -c;
        cout << a << " " << b << " " << c << endl;
    }
    for(auto m : M) cout << m << " " ;

}