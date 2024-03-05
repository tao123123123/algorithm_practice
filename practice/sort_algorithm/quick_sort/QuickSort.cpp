// The header <algorithm> defines a collection of functions especially designed
// to be used on ranges of elements included random_shuffle  
#include <algorithm>

#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

// The keyword typename is used to declare template parameters that 
// represent types, and class can also be used interchangeably with typename in this context
template <typename T>
class QuickSort {
public:

    // Sorts the input vector a using the QuickSort Algorithm
    // It first shuffles the elements randomly and then performs
    // the recursive QuickSort.

    static void sort(std::vector<T>& a) {
	// Use the random_shuffle in the header file algorithm
        std::random_shuffle(a.begin(), a.end());
	// Performs the recursive QuickSort
        sort(a, 0, a.size() - 1);
    }
	
    // Finds the k-th smallest element in the vector
    // Declare a static method named select that returns a value of type T
    // The method takes a reference to a vector of type T and an integer k as parameters
    static T select(std::vector<T>& a, int k) {

	// Check if the value of k is outside the valid range for the vector a to avoid
	// worst-case scenarios in the QuickSelect algorithm
	// The worst-case of this method is when the largest or smallest element
	// in the begin or the end position
	// The average time is not O(N), is O(N^2)
        if (k < 0 || k >= static_cast<int>(a.size())) {
            throw std::runtime_error("Selected element out of bounds");
        }
	
	// Shuffle the elements of vector a randomly
        std::random_shuffle(a.begin(), a.end());
	// lo and hi represent the low and high indices of the subarray
        int lo = 0, hi = a.size() - 1;
	// This starts a while loop that continues as long as the hi is greater than
	// the low index
        while (hi > lo) {
	    // Call the partition function to partition the subarray defined by lo and hi
	    // And stores the returned index in the variable i
            int i = partition(a, lo, hi);
            if (i > k) hi = i - 1;
            else if (i < k) lo = i + 1;
            else return a[i];			// return element at index i from the vector
        }
	// if hi becomes less than or equal ot lo, the method returns the element at index lo
	// if return lo, two situation: the first one is Empty array and another is singleton array
        return a[lo];
    }

    static void show(const std::vector<T>& a) {
        for (const auto& elem : a) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    
    // for-each version
    // In the range-based for loop, const T& elem iterates over each element in the
    // vector a, and elem represents the current element in each iteration. 
    // static void show(const std::vector<T>& a)
    // {
           // for (const T& elem : a)
	   // {
	          // std::cout << elem << " ";
	   // }
	   // std::cout << std::endl;
    // }

// private key word indicates that the following members of the class are
// private, accessible only within the class itself.
private:
    // Declares a private static method named sort. It takes a 
    // reference to a vector of type T and two integer parameters lo and hi
    // representing the low and high indices of the subarray to be sorted.
    static void sort(std::vector<T>& a, int lo, int hi) {
        // The base case check. If the high index hi is less than or equal to the low index lo
        // it means the subarray has either zero or one element and it is already sorted
        if (hi <= lo) return;
        int j = partition(a, lo, hi);
        sort(a, lo, j - 1);
        sort(a, j + 1, hi);
        assert(isSorted(a, lo, hi));	// An assertion check is performed to ensure that the subarray is sorted.
    }

    // Declares a private static method named partition. It takes a reference to a vector of type
    // T and two integer parameters lo and hi, representing the low and high indices 
    // of the subarray to be partitioned. The method returns an integer, which is the final position of the
    // the pivot element after partitioning.
    static int partition(std::vector<T>& a, int lo, int hi) {
        int i = lo;
        int j = hi + 1;
        T v = a[lo];
        while (true) {
            while (less(a[++i], v))
                if (i == hi) break;
            while (less(v, a[--j]))
                if (j == lo) break;
            if (i >= j) break;		// cross index check
            std::swap(a[i], a[j]);
        }
	
	// swap algorithm from the header file <algorithm>
        std::swap(a[lo], a[j]);
	// return the final position of the pivot element after partitioning.
        return j;
    }
    
    // Declare a private static method named isSorted. It takes a reference to a constant vector
    // of type T and two integer parameters lo and hi, representing the range of element to 
    // check for sorted order.
 
    static bool isSorted(const std::vector<T>& a, int lo, int hi) {
        for (int i = lo + 1; i <= hi; i++)
            if (less(a[i], a[i - 1])) return false;
        return true;
    }
    
    // const indicates that the referenced object is constant. This means that you cannot modify the value of the
    // object through this reference. It provides a guarantee that the object's value won't be changed within the
    // scope of this reference
    // & denotes that this is a reference
    static bool less(const T& v, const T& w) {
        return v < w;
    }
};

// Declare a template function, indicating that the function is parameterized by a type T
template <typename T>
void processFile(const char* filename) {
    // creates an input file stream ifstream object named inputFile and attempt to open the file specified by the
    // filename
    std::ifstream inputFile(filename);

    // check whether the file was successfully opened. 
    // If not, it prints an error message to the standard stream error stream cerr and exits the program
    // with an error code.
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        exit(1);
    }
     
    // Declares a vector named dataVector of type T to store the data read from the file
    // T value: Declare a variable value of type T to temporarily store each value read from the file.
    std::vector<T> dataVector;
    T value;
    
    // Reads values from the file into value one by one until the end of the file is reached
    while (inputFile >> value) {
        dataVector.push_back(value);		// Appends each read value to the vector dataVector
    }

    inputFile.close();			        // Closes the input file stream after reading all the data

    std::cout << "Original Data Vector: ";      // Output the message
    QuickSort<T>::show(dataVector);		// Use the show method of the QuickSort class

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
    // Check if the number of command-line arguments is not equal to 3. If not, it prints a
    // usage message to the standard error stream and returns with an error code
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <data_type>" << std::endl;
        return 1;
    }
    
    // Retrieves the filename and data type from the command-line arguments
    // std::string is a type-safe class that avoids common pitfalls associated with C-style
    // strings, such as buffer overflows.
    const char* filename = argv[1];         // Declare a pointer to a character, used for fixed String
    std::string dataType = argv[2];         // Provides a dynamic, resizable string

    if (dataType == "int") {
        processFile<int>(filename);
    } else if (dataType == "double") {
        processFile<double>(filename);
    } else if (dataType == "char") {
        processFile<char>(filename);
    } else if (dataType == "string") {
        processFile<std::string>(filename);
    } else {
        std::cerr << "Error: Unsupported data type." << std::endl;
        return 1;
    }

    // Indicate successful execution of the program. A return value of 0 conventionally indicates success in most
    // operating systems
    return 0;
}