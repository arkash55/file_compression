#include<iostream>
#include<fstream>
#include <string>
#include<cstdlib>
#include<vector>
using namespace std;









int main() {
    string file_name = "notes.txt";
    // string file_name = "test.txt";

    ifstream file(file_name);

    //check that the file has opened without issues    
    if (!file.is_open()) {    
        //can i debug the issues?
        return EXIT_FAILURE;
    }    


    //read the file and store character count
    const int N = 256;
    char ch;
    vector<int> cnt(N, 0);
    while (file.get(ch)) cnt[ch]++;
    
    for (int i=0; i<N; i++) {
        if (!cnt[i]) continue;
        cout << (char) (i) << " " << cnt[i] << "\n";
    }




    //close the file
    file.close();
}

