/*실습*/

//#include<iostream>
//#include<array>
//
//using namespace std;
//
///*
//void print(array<int, 5> arr) {
//	for (auto ele : arr) {
//		cout << ele << ", ";
//	}
//}
//*/
//template <size_t N>
//void print(const array<int, N>& arr) {
//	/*
//	for (auto ele : arr) {
//		cout << ele << ", ";
//	}
//	*/
//	for (auto iter = arr.begin(); iter != arr.end(); iter++) {
//		auto ele = (*iter);
//		cout << ele << ' ';
//	}
//}
//
//int main(void) {
//
//	std::array<int, 10> arr1;
//
//	arr1[0] = 1;
//	cout << "arr1 배열의 첫 번째 원소: " << arr1[0] << endl;
//
//	array<int, 4> arr2 = { 1,2,3,4 };
//	cout << "arr2의 모든 원소: " << endl;
//
//	for (int i = 0; i < arr2.size(); i++) {
//		cout << arr2[i] << " ";
//	}
//
//	cout << endl;
//
//	array<int, 4> arr3 = { 1,2,3,4 };
//	try {
//		cout << arr3.at(3) << endl;
//		cout << arr3.at(4) << endl;
//	}
//	catch(const out_of_range& ex) {
//		cerr << ex.what() << endl;
//	}
//	array<int, 5> arr4 = { 1,2,3,4,5 };
//	print(arr4);
//
//	return 0;
//}

/*연습문제 1*/

#include<iostream>
#include<sstream>
#include<algorithm>

using namespace std;

template <typename T>
class dynamic_array
{
	T* data;
	size_t n;

public:
	dynamic_array(int n) {
		this->n = n;
		data = new T[n];
	}

	dynamic_array(const dynamic_array<T>& other) {
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; i++) {
			data[i] = other[i];
		}
	}
	T& operator[](int index) {
		return data[index];
	}

	const T& operator[](int index) const {
		return data[index];
	}
	T& at(int index) {
		if (index < n)
			return data[index];
		throw "index out of range";
	}

	size_t size() const {
		return n;
	}

	~dynamic_array() {
		delete[] data;
	}

	T* begin() { return data; }
	const T* begin() const { return data; }
	T* end() { return data + n; }
	const T* end() const { return data + n; }

	friend dynamic_array<T> operator+(const dynamic_array<T>& arr1, dynamic_array<T>& arr2) {
		dynamic_array<T> result(arr1.size() + arr2.size());
		copy(arr1.begin(), arr1.end(), result.begin());
		copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());

		return result;
	}

	string to_string(const string& sep = ", ") {
		if (n == 0)
			return "";
		ostringstream os;
		os << data[0];

		for (int i = 1; i < n; i++) {
			os << sep << data[i];
		}
		return os.str();
	}

	
};

struct student {
	string name;
	int standard;
};

std::ostream& operator<<(std::ostream& os, const student& s) {
	return (os << "[" << s.name << ", " << s.standard << "]");
}

int main() {
	int nstudent;
	cout << "1반 학생 수를 입력하세요,: ";
	cin >> nstudent;

	dynamic_array<student> class1(nstudent);
	for (int i = 0; i < nstudent; i++) {
		string name;
		int standard;
		cout << i + 1 << "번째 학생 이름과 나이를 입력하세요.: ";
		cin >> name >> standard;
		class1[i] = student{ name, standard };
	}
	try {
		class1.at(nstudent) = student{ "John",8 };
	}
	catch(...) {
		cout << "예외 발생" << endl;
	}

	auto class2 = class1;
	cout << "1반을 복사하여 2반 생성: " << class2.to_string() << endl;

	auto class3 = class1 + class2;
	cout << "1반과 2반을 합쳐 3반 생성: " << class3.to_string() << endl;

	return 0;
}