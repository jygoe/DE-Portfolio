#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Vector{
	private:
		int *items;
		int size;
		
	public:
		// 1.a Default constructor
		Vector(){
			items = nullptr;
			size = 0;
		}
		
		// 1.b Constructor size	
		Vector(int s){
			size = s;
			items = new int [size];
		}
		
		// 1.c Constructor size & items		
		Vector(int s, int *i){
			size = s;
			items = i;
		}
		
		// 1.d Constructor list of digits
		Vector(string s){
			items = new int [s.size()];
			size = s.size();
			for(int i = s.size()-1; i >= 0; i--){
				items[i] = s[i] - 48;
			}
		}
		
		// 1.e Copy Constructor				
		Vector(Vector &v){
			this->items = new int [v.size];
			this->size = v.size;
			for(int i = 0; i < v.size; i++){
				items[i] = v.items[i];
			}
		}
		
		// 2. Deconstructor				
		~Vector(){
			delete [] items;
			items = nullptr;
		}
		
		// 3.a Vector to int 				
		operator int(){
			return size;
		}
		
		// 3.b Magnitude
		double magnitude(){
			double sum = 0;
			for (int i = 0; i < size; i++){
				sum += pow(items[i], 2);
			}
			return pow(sum, 0.5);
		}
		
		// 3.c Vector to string
		operator string(){
			string s = "";
			for (int i = 0; i < size; i++){
				s += to_string(items[i]);
				if(i != size - 1){
					s += ",";
				}
			}
			return s;
		}
		
		// 4.a Multiplication operator 
		Vector operator * (int m){
			Vector temp;
			temp.size = size;
			temp.items = new int [size];
			for (int i = 0; i < size; i++){
				temp.items[i] = items[i] * 2; 
			}
			return temp;
		}

        // 4.b Vector + Vector
        Vector operator + (Vector &v){
            Vector temp;
            temp.size = size;
            temp.items = new int [size];
            for (int i = 0; i < size; i++){
                temp.items[i] = items[i] + v.items[i];
            }
            return temp;
        }

        // 4.c Vector + element
        Vector operator + (int n){
            Vector temp;
            temp.size = size + 1;
            temp.items = new int [temp.size];
            temp.items[size] = n;
            for (int i = 0; i < size; i++){
				temp.items[i] = items[i];
			}
            return temp;
        }

        // 4.d Subscript operator
        int operator [] (int n){
            if(n >= 0 || n < size){
                return items[n];
            }
        }

        // 4.e Equality operator
        bool operator == (Vector &obj){
            if (size != obj.size)
                return 0;

            for (int i = 0; i < size; i++){
                if (items[i != obj.items[i]])
                    return 0;
            }
            return 1;
        }
    	
        // 4.f Greater than
        bool operator > (Vector &obj){
            return magnitude() > obj.magnitude();
        }

        // 5.b Friend
        friend void print(Vector &, string);
};

 // 5.a Regular function
void print(Vector & obj, string title){
	string s = obj;
    cout << title << ": ( (" << s << "), s: " << obj.size << ", m: " << obj.magnitude() << ")\n";
}

int main(){
    int array[] = {6, 7, 8, 9};
    Vector a(4, array);
    Vector b("678");
    Vector c = b;
    Vector *d = &b;
	Vector e;
	e = *d + 1;                          
	Vector f;
	f = c * 2;
    Vector g;
	g = a + e;

    // 6.h Print all Vectors
    print(a, "a");
    print(b, "b");
    print(c, "c");
    cout << endl;
    print(*d, "d");
    cout << endl;
    print(e, "e");
    print(f, "f");
    print(g, "g");
    cout << endl;

    // 6.i If a and b are equivalent
    if (a == b)
        cout << "a is equivalent to b\n";
    else
        cout << "a is not equivalent to b\n";

    // 6.j If a > e
    if (a > e)
        cout << "a is greater than e\n";
    else 
        cout << "a is less than e\n";

    // 6.k Destroy d
    delete d;
    d = nullptr;

    return 0;
}
