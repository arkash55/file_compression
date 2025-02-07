#include<iostream>
#include<fstream>
#include <string>
#include<cstdlib>
#include<vector>
#include"huffman_tree.cpp"
#include <sstream>
#include <filesystem> 
namespace fs = std::filesystem;
using namespace std;











int main() {
    string in_file_name = "notes.txt";
    // string in_file_name = "test.txt";
    string compressed_file_name = "a_cmp.txt";
    string decompressed_file_name = "a_d_cmp.txt";



    
    HuffmanTree huffman_tree;
    ofstream* compressed_file = huffman_tree.compress_data(in_file_name, compressed_file_name);


    //print the size the compressed file


    ofstream* decompressed_file = huffman_tree.decompress(compressed_file_name, decompressed_file_name);
    
    auto compressed_sz = fs::file_size(compressed_file_name);
    auto decompressed_sz = fs::file_size(decompressed_file_name)*8;
    

    cout << "Compressed File has a size of " << compressed_sz << " bits\n";
    cout << "Decompressed File has a size of " << decompressed_sz << " bits\n";

    cout << "Our compression algorithm takes " << (compressed_sz/(decompressed_sz*8.0) * 100) << "% less space.\n";




}

