# **Huffman Compression and Decompression in C++**

## 📌 Overview
This project implements **Huffman coding**, a lossless data compression algorithm, in **C++**. The program:
- **Compresses text files** using Huffman encoding.
- **Decompresses the compressed file** back to its original form.
- **Displays compression efficiency** by comparing file sizes before and after compression.

This implementation is optimized for **efficiency**, using **priority queues**, **bit manipulation**, and **unordered maps** to store Huffman codes.

---

## ⚡ Features
✔️ **Efficient Huffman Tree construction** based on character frequencies.  
✔️ **Lossless compression & decompression** of text files.  
✔️ **Stores and reconstructs Huffman codes from compressed files.**  
✔️ **Displays compression ratio** by calculating file sizes in bits.  
✔️ **Works with any text file input** (`.txt` files).  

---

## 📂 Project Structure

📦 HuffmanCompression
┣ 📜 main.cpp – Main driver program
┣ 📜 huffman_tree.cpp – HuffmanTree class (compression & decompression)
┣ 📜 huffman_tree.h – Header file for HuffmanTree
┣ 📜 notes.txt – Sample input file
┣ 📜 a_cmp.txt – Compressed output file
┣ 📜 a_d_cmp.txt – Decompressed file (should match notes.txt)
┣ 📜 README.md – Documentation (this file)


---

## 🛠️ How It Works
### **1️⃣ Frequency Count**
- Reads input text and counts occurrences of each character.

### **2️⃣ Huffman Tree Construction**
- Uses a **min-heap (priority queue)** to construct the optimal Huffman tree.

### **3️⃣ Generating Huffman Codes**
- Assigns shorter binary codes to frequently occurring characters.

### **4️⃣ Compression**
- Encodes input text using generated Huffman codes.
- Saves the Huffman code table along with the compressed data.

### **5️⃣ Decompression**
- Reads the Huffman code table from the compressed file.
- Reconstructs the Huffman tree.
- Decodes the binary data back into text.

---
### **5️⃣ Example File Size Comparison Output**
Compressed File has a size of 75 bits
Decompressed File has a size of 120 bits
Our compression algorithm takes 62.5% less space.


---

## 🚀 Usage
### **1️⃣ Compilation**
Compile using **g++**:
```sh
g++ -std=c++17 -o output main.cpp && ./output
```


## 📌 Performance Considerations
- 🏗️ **Uses a min-heap (priority queue) for Huffman tree construction** → `O(n log n)`.
- ⚡ **Fast lookup times for encoding using an unordered_map** → `O(1) per character`.
- 📁 **Efficient file handling with binary mode** to store compressed data.

---

## 📝 Future Improvements
- 🔢 **Bit-level compression**: Currently stores encoded data as text (`'0'` and `'1'`). Could be optimized using actual bits.
- 🎨 **GUI Interface**: Add a simple UI to make compression user-friendly.
- 📂 **Support for non-text files**: Extend to handle binary files.

---

## 💡 Author & Contributions
- 👨‍💻 **Developer**: Arkash Sai Vijayakumar
- 🚀 **Contributions**: Feel free to submit a pull request if you want to improve the project! 😊

