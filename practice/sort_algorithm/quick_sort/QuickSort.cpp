
#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

template <typename T>
class QuickSort {
public:
    static void sort(std::vector<T>& a) {
        std::random_shuffle(a.begin(), a.end());
        sort(a, 0, a.size() - 1);
    }

    static T select(std::vector<T>& a, int k) {
        if (k < 0 || k >= static_cast<int>(a.size())) {
            throw std::runtime_error("Selected element out of bounds");
        }
        std::random_shuffle(a.begin(), a.end());
        int lo = 0, hi = a.size() - 1;
        while (hi > lo) {
            int i = partition(a, lo, hi);
            if (i > k) hi = i - 1;
            else if (i < k) lo = i + 1;
            else return a[i];
        }
        return a[lo];
    }

    static void show(const std::vector<T>& a) {
        for (const auto& elem : a) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

private:
    static void sort(std::vector<T>& a, int lo, int hi) {
        if (hi <= lo) return;
        int j = partition(a, lo, hi);
        sort(a, lo, j - 1);
        sort(a, j + 1, hi);
        assert(isSorted(a, lo, hi));
    }

    static int partition(std::vector<T>& a, int lo, int hi) {
        int i = lo;
        int j = hi + 1;
        T v = a[lo];
        while (true) {
            while (less(a[++i], v))
                if (i == hi) break;
            while (less(v, a[--j]))
                if (j == lo) break;
            if (i >= j) break;
            std::swap(a[i], a[j]);
        }
        std::swap(a[lo], a[j]);
        return j;
    }

    static bool isSorted(const std::vector<T>& a, int lo, int hi) {
        for (int i = lo + 1; i <= hi; i++)
            if (less(a[i], a[i - 1])) return false;
        return true;
    }

    static bool less(const T& v, const T& w) {
        return v < w;
    }
};

template <typename T>
void processFile(const char* filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        exit(1);
    }

    std::vector<T> dataVector;
    T value;

    while (inputFile >> value) {
        dataVector.push_back(value);
    }

    inputFile.close();

    std::cout << "Original Data Vector: ";
    QuickSort<T>::show(dataVector);

    // Sort the vector
    QuickSort<T>::sort(dataVector);

    std::cout << "Sorted Data Vector: ";
    QuickSort<T>::show(dataVector);

    // Display results using select
    std::cout << std::endl;
    for (size_t i = 0; i < dataVector.size(); i++) {
        T ith = QuickSort<T>::select(dataVector, static_cast<int>(i));
        std::cout << "Selected Data Element at index " << i << ": " << ith << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <data_type>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    std::string dataType = argv[2];

    if (dataType == "int") {
        processFile<int>(filename);
    } else if (dataType == "double") {
        processFile<double>(filename);
    } else if (dataType == "String") {
        processFile<char>(filename);
    } else {
        std::cerr << "Error: Unsupported data type." << std::endl;
        return 1;
    }

    return 0;
}