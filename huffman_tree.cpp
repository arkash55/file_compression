#include<iostream>
#include<fstream>

#include<vector>
#include<queue>
#include<string>
#include<unordered_map>
#include<bitset>
#include <sstream>


using namespace std;





class Node {
public:
    
    Node(bool is_leaf=false, int freq=-1, int ascii_code=-1) {
        this->freq = freq;
        this->is_leaf = is_leaf;
        this->ascii_code = ascii_code;
    }

    Node* left;
    Node* right;
    int freq;
    int ascii_code;
    bool is_leaf;

};



class Pq_comparator {
public:
    bool operator() (Node* ptr_1, Node* ptr_2) {
        return ptr_1->freq == ptr_2-> freq ? ptr_1->is_leaf > ptr_2->is_leaf: ptr_1->freq > ptr_2->freq;
    }
};




class HuffmanTree {

public:


    ofstream* compress_data(string& in_file_name, string& out_file_name) {

        ifstream in_file(in_file_name);
        if (!in_file.is_open()) {
            cerr << "Error opening file @ compress data" << "\n";
            return NULL;
        }


        stringstream buffer;
        buffer << in_file.rdbuf();
        string file_data = buffer.str();
        in_file.close();



        //generate frequency cnt
        generate_cnt(file_data);

        // create leaf nodes and add to pq
        generate_leaf_nodes();
        
        // create huffman tree
        generate_tree();

        //create huffman key table
        generate_huffman_codes();


        //encode data
        return encode_data(file_data, out_file_name);
    }


    ofstream* decompress(string& compressed_file_name, string& out_file_name) {

        //OPENING RELEVANT FILES//
        ifstream compressed_file(compressed_file_name, ios::binary);

        if (!compressed_file.is_open()) {
            cerr << "Error openeing compressed file @decode_data" << "\n";
            return NULL;
        }


        ofstream* decompressed_file = new ofstream(out_file_name);
        if (!decompressed_file->is_open()) {
            cerr << "Error opening output file @decode_data" << "\n";
            delete decompressed_file;
            return NULL;
        }



         //DECODING//

        //decode header
        unordered_map<int, string> huffman_codes = decode_header(compressed_file);


        //build tree
        Node* decoded_root = construct_tree_from_codes(huffman_codes);


        //decode body and write to output file
        decode_body(decompressed_file, compressed_file, decoded_root);

        return decompressed_file;



    }





private:


    vector<int> cnt;
    unordered_map<int, string> huffman_codes;
    priority_queue<Node*, vector<Node*>, Pq_comparator> pq;
    Node* root;



    //////////CREATE TREE//////////

    void generate_cnt(string& file_data) {
        const int N = 256;
        cnt = vector<int>(N, 0);
        for (char ch: file_data) cnt[ch]++;
    }


    void generate_leaf_nodes() {
      for (int i=0; i<cnt.size(); i++) {
            if (!cnt[i]) continue;
            Node* node_ptr = new Node(true, cnt[i], i);
            pq.push(node_ptr);
        }
        return;

    }


    Node* create_parent_node(Node* left_node, Node* right_node) {
        Node* parent_node = new Node(false, left_node->freq+right_node->freq);
        parent_node->left = left_node;
        parent_node->right = right_node;
        return parent_node;
    }


    void generate_tree() {

        while (pq.size() > 1) {
            Node* left_node = pq.top();
            pq.pop();
            Node* right_node = pq.top();
            pq.pop();
            Node* parent_node = create_parent_node(left_node, right_node);
            pq.push(parent_node);
        }

        //edge case of empty input file
        if (!pq.empty()) root = pq.top();
        return;
    }



 









    //////////ENCODE DATA//////////

    void generate_huffman_codes() {
        //traverse all paths of our huffman tree keeping track of the binary code, and when we reach a base node insert into our huffman_codes
        //traversing left is equal to 0, and right is equal to 1
        string code_string = "";
        traverse(root, code_string);
    }



    void traverse(Node* node, string& code) {

        //check if node is a leaf node 
        if (node->is_leaf) {
            // string x = code;
            huffman_codes[node->ascii_code] = code;
            // cout << node->ascii_code << " " << code << "\n";
            return;
        }

        //traverse left
        if (node->left) {
            code.push_back('0');
            traverse(node->left, code);
            code.pop_back();
        }


        //traverse right
        if (node->right) {
            code.push_back('1');
            traverse(node->right, code);
            code.pop_back();
        }

        return;


    }



    
    ofstream* encode_data(string& file_data, string& output_file_name) {

        //first compress the data using our Huffman codes
        ofstream* output_file = new ofstream(output_file_name, ios::binary);

        if (!output_file->is_open()) {
            cerr << "Error opening output file" << "\n";
            delete output_file;
            return NULL;
        }


        //write the table to the file 
        for (const auto& [ascii_code, huffman_code]: huffman_codes) {
            *output_file << ascii_code << " " << huffman_code << "\n";
        }


        //add separator to split the huffman code key from our compressed data
        *output_file << "#" << "\n";

        
        //now encode our data and write it to our output file
        for (char& ch: file_data) {
            *output_file << huffman_codes[ch];
            // cout << huffman_codes[ch];
        }
        // cout << "\n";



        output_file->close();

        return output_file;
    }


    //////////DECODE DATA//////////

    pair<int, string> parse_line(string& line) {
        pair<int, string> huffman_code = make_pair(0, "");

        string ascii_string;
        bool found_space = false;
        for (char& ch: line) {
            if (ch == ' ') {
                found_space = true;
                continue;
            }

            if (!found_space) ascii_string.push_back(ch);
            else huffman_code.second.push_back(ch);


        }

        huffman_code.first = stoi(ascii_string);
        return huffman_code;

    }


    unordered_map<int, string> decode_header(ifstream& compressed_file) {
        unordered_map<int, string> huffman_codes;
        char ch;
        //ascii: huffman_code
        string line;
        while (getline(compressed_file, line)) {
            if (line == "#") break;

            //holds ascii_code: binary code
            pair<int, string> huffman_code = parse_line(line);
            huffman_codes[huffman_code.first] = huffman_code.second;
        }


        return huffman_codes;

    }


    Node* construct_tree_from_codes(unordered_map<int, string>& huffman_codes) {
        Node* root = new Node();

        Node* node;
        for (const auto& [ascii_code, huffman_code]: huffman_codes) {
            node = root;
            for (const char& bit: huffman_code) {
                if (bit == '0') {
                    if (!node->left) node->left = new Node();
                    node = node->left;
                } else {
                    if (!node->right) node->right = new Node();
                    node = node->right;
                }
            }

            node->is_leaf = true;
            node->ascii_code = ascii_code;

        }

        return root;
    }



    void decode_body(ofstream* out_file, ifstream& in_file, Node* decoded_root) {

        char bit;
        Node* node = decoded_root;
        while (in_file.get(bit)) {
            node = bit == '0' ? node->left : node->right;
            if (node->is_leaf) {

                *out_file << (char) (node->ascii_code);
                // cout << (char) (node->ascii_code);
                node = decoded_root;
            }
        }
        out_file->close();
        return;



    }








};