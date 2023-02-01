//Cringe, super inferior c++ implementation of the superior python implementation,
//I only do this for the speed, I don't want c++ anymore

#include <iostream>
#include <cmath>
#include <sstream>
#include <list>
#include <iterator>
#include <limits.h>
#include <math.h>
using namespace std;

//Sixty-Four bit signed Base Unit
class sfbu {

private:
	//Detect integer overflow from addition
	bool detect_overflow(unsigned long long int a, unsigned long long int b, bool ci) { 

		//Boring setup
		bool out = false;

		//Work-around for checking for unsigned long long int overflow
		if (a > 0 && (b+ci) > (ULLONG_MAX - a)) { out = true; }

		return out;

	};

public:
	
	//mant is 64 bit unsigned integer, co, sign, ci is bool
	unsigned long long int mant;
	bool co, sign, ci;

	//__init__(self, mant, co, sign, ci):
	sfbu(unsigned long long int a=0, bool b=false, bool c=true, bool d=false) {

		cout << "--Initializing Sixty-four Bit Signed Unit--\n";

		mant = a;
		co = b;
		sign = c;
		ci = d;

	};
	
	//Bitwise and
	sfbu __and__(sfbu const& obj) {

		sfbu a = *this;
		sfbu b = obj;
		sfbu out;

		out = a.get_mant() & b.get_mant();

		return out;

	};

	//Bitwise or
	sfbu __or__(sfbu const& obj) {

		sfbu a = *this;
		sfbu b = obj;
		sfbu out;

		out = a.get_mant() | b.get_mant();

		return out;

	};

	//Bitwise xor
	sfbu __xor__(sfbu const& obj) {

		sfbu a = *this;
		sfbu b = obj;
		sfbu out;

		out = a.get_mant() ^ b.get_mant();

		return out;

	};

	//Bitwise not
	sfbu __not__() {

		sfbu a = *this;
		sfbu out;

		out = ~a.get_mant();

		return out;

	};

	//Boring setter
	void set_mant(unsigned long long int a = 0) {

		mant = a;

	};

	//Boring getter
	unsigned long long int get_mant() {

		return mant;

	}

	/*list<unsigned long long int> shift(sfbu a, unsigned long long int shifts, bool direction) {

		list<unsigned long long int> q = list<unsigned long long int>{ 0, 0 };



		return q;

	};*/

	//Propper python gang
	//def __add__(self, other, ci=False):
	sfbu __add__(sfbu const& a=sfbu(), sfbu const& b = sfbu(), bool ci = false) {

		//Boring setup
		sfbu out;

		//Handle carry out
		out.co = detect_overflow(a.mant, b.mant, ci);

		//Compute addition
		out.mant = a.mant + b.mant;

		return out;

	}

	//def __sub__(self, other, ci=True):
	sfbu __sub__(sfbu const& a = sfbu(), sfbu const& b = sfbu(), bool ci = true) {

		//Boring setup
		sfbu out;

		//Handle carry out
		out.co = detect_overflow(a.mant, ~b.mant, ci);

		//Compute subtraction
		out.mant = a.mant - b.mant;

		return out;
	}

	//Cringe c++
	//__add__(self, other, ci=False):
	sfbu operator + (sfbu const& obj) {
		
		//Boring setup
		sfbu res;

		//Handle carry out
		res.co = detect_overflow(mant, obj.mant, ci);

		//Compute addition
		res.mant = mant + obj.mant;

		return res;

	};

	//__sub__(self, other, ci=True):
	sfbu operator - (sfbu const& obj) {

		//Boring setup
		sfbu res;

		//Handle carry out
		res.co = detect_overflow(mant, ~obj.mant, not ci);

		//Compute subtraction
		res.mant = mant - obj.mant;

		return res;

	}

	signed long long int LimitedToInt() {

		signed long long int out = mant;

		if (sign) { return out; }
		else { return -out; }

	}

	//__str__(self):
	string ToString() {

		//Boring setup
		unsigned long long int working_mant = mant;

		stringstream work_out;
		string out, sign_str;

		//Handle sign
		if (sign == true) { sign_str = "+"; }
		else { sign_str = "-"; }
		
		//Convert mant to string
		work_out << sign_str << mant;

		//Convert to std::string
		out = work_out.str();

		return out;

	}

};

class random_access_list {

public:

	list<sfbu> data;

	//__init__(data):
	random_access_list(list<sfbu> a = list<sfbu>()) {

		cout << "--Initializing Random Access List--\n";

		data = a;

	};

	//Bitwise and
	random_access_list __and__(random_access_list obj) {

		random_access_list a = *this;
		random_access_list b = obj;
		random_access_list out;



	}

	//Boring getter
	sfbu get(int index=0) {

		//Boring setup
		list<sfbu>::iterator it = data.begin();

		//Hack for getting pseudo-random access list
		for (int i = 0; i < index; i++) {  it++; }

		return *it;

	}

	//Boring setter
	void set(int index = 0, sfbu a = sfbu()) {

		//Boring setup
		list<sfbu>::iterator it = data.begin();

		//Hack for getting pseudo-random access list
		for (int i = 0; i < index; i++) { it++; }

		*it = a;

	};

	//Why can't I do this like in python?
	void set_ci(int index = 0, bool a = false) {

		//Annoyingly you have to get object
		sfbu temp = get(index);

		//Then set paramter
		temp.ci = a;

		//Then apply to the actual object
		set(index, temp);

	};

	//Pythonic append(0, a)
	void push_back(sfbu a = sfbu()) { data.push_back(a); };

	//Pythonic append(-1, a)
	void push_front(sfbu a = sfbu()) { data.push_front(a); };

	//Pythonic pop(0)
	sfbu pop_front() {

		//Hack for pythonic pop(0)
		sfbu out = data.front();
		data.pop_front();

		return out;

	};

	//Python pop(-1)
	sfbu pop_back() {

		//Hack for pythonic pop(-1)
		sfbu out = data.back();
		data.pop_back();

		return out;

	}

	sfbu shift(sfbu a, unsigned long long int shifts, bool direction) {

		sfbu q;



		return q;

	}

	int size() { return data.size(); };

private:

	//Semi-redundant LengthAppend(self, length = 1, a = 0):
	void LengthAppend(int length = 1, unsigned long long int a = 0) {

		for (int i = 0; i < length; i++) {

			data.push_back(a);

		};

	}

	//Semi-redundant InverseLengthAppend(self, length = 1, a = 0):
	void InverseLengthAppend(int length = 1, unsigned long long int a = 0) {

		for (int i = 0; i < length; i++) {

			data.push_front(a);

		};

	}

	//Why can't I do this like in python?
	list<random_access_list> Allign(random_access_list a, random_access_list b, bool Inverse = false, int offset = 0) {

		//Boring setup
		list<random_access_list> out = list<random_access_list>();
		random_access_list _new_self = a;
		random_access_list _new_other = b;
		int _self_len = _new_self.size();
		int _other_len = _new_other.size();

		//Handle Inverse
		if (Inverse == true) {

			if (_self_len < _other_len) { _new_self.InverseLengthAppend(_other_len - _self_len); }
			else {
				_new_other.InverseLengthAppend((_self_len - _other_len) - offset);
				_new_other.LengthAppend(offset);
			};

			//Cringe c++ rhetorical 'must'
			out.push_back(_new_self);
			out.push_back(_new_other);

			return out;

		};

		if (_self_len < _other_len) {

			_new_self.LengthAppend(_other_len - _self_len);

		}
		else {

			_new_other.LengthAppend((_self_len - _other_len) - offset);
			_new_other.InverseLengthAppend(offset);

		};

		//Why can't I do this like in python?
		out.push_back(_new_self);
		out.push_back(_new_other);

		return out;

	};
	//DivAllign(self, other, offset=0):
	list<random_access_list> DivAllign(random_access_list a, random_access_list b, int offset = 0) {

		//Boring setup
		list<random_access_list> out = list<random_access_list>();
		random_access_list _new_self = a;
		random_access_list _new_other = b;
		int _self_len = a.size();
		int _other_len = b.size();

		//Handle length difference
		if (_self_len < _other_len) { _new_self.InverseLengthAppend(_other_len - _self_len); } 
		else { _new_other.InverseLengthAppend(_self_len - _other_len); }

		//Handle offset
		_new_self.LengthAppend(offset);
		_new_other.LengthAppend(offset);

		//Imagine, inferior c++ 'requires' this to superior python, there you can just, do what you need to do
		out.push_back(_new_self);
		out.push_back(_new_other);

		return out;
		
	};
	
};

//Arbitrarily sized signed integer
class Binary {

public:

	random_access_list mant, exp;
	bool sign, co, is_zero, ci;

	//__init__(self, mant, exp, sign, co, is_zero):
	Binary(random_access_list a = random_access_list(), random_access_list b = random_access_list(), bool c = true, bool d = false, bool e = true, bool f = false) {

		cout << "--Initializing Binary--\n";

		mant = a;
		exp = b;
		sign = c;
		co = d;
		is_zero = e;
		ci = f;

	};

	//Boring setter
	void set_mant(list<sfbu> a) { mant = a; };

	//Boring getter
	random_access_list get_mant() { return mant; };

	Binary shift(Binary a, unsigned long long int shifts, bool direction) {

		Binary q;

		

		return q;

	};

	Binary operator + (Binary const& obj) {

		Binary a = *this;
		Binary b = obj;

		if (sign == true) {

			if (obj.sign == true) { return this->__pure_add__(obj); };
			return this->__pure_sub__(obj);

		};

		if (obj.sign == true) { return b.__pure_sub__(a); }
		return this->__pure_add__(obj);

	};

	Binary operator - (Binary const& obj) {

		Binary a = *this;
		Binary b = obj;
		Binary out;

		if (sign == true) {

			if (obj.sign == true) { return this->__pure_sub__(obj); };
			return this->__pure_add__(obj);

		};

		if (obj.sign == true) { 
			
			out = this->__pure_add__(obj); 
			out.sign = false;
			return out;
		
		};
		out = this->__pure_sub__(obj);
		out.sign = not out.sign;
		return out;

	};

	Binary __float_add__(Binary a, Binary b, bool ci = false) {

		Binary q;



		return q;

	};

	int GetLength() { return mant.size(); };

	signed long long int ToInt(int depth=75) {

		signed long long int out = 0;
		auto mant_iter = mant.data.begin();

		for (int i = 0; i < depth; i++) {

			std::advance(mant_iter, 1);
			out += pow(2, i) * (*mant_iter).LimitedToInt();

		};

		return out;

	}

	//string __str__() {



	//}

private:

	//Propper python gang
	//def __pure_add__(self, other, ci=False):
	Binary __pure_add__(Binary const& a = Binary(), Binary const& b = Binary(), bool ci = false) {

		//Boring setup
		Binary out;
		Binary ta = a;
		Binary tb = b;
		sfbu temp;
		bool co = false;

		//Handle is_zero
		if (a.is_zero == true) {

			if (b.is_zero == true) { return out; };
			return b;

		}

		if (b.is_zero == true) { return a; };

		//Set sign
		out.sign = tb.sign;

		//Compute __pure_add__():
		for (int i = 0; i < mant.size(); i++) {

			temp = ta.mant.get(i).__add__(tb.mant.get(i), ci);
			ci = temp.co;
			out.mant.push_back(temp);

		};

		return out;

	};

	//def __pure_sub__(self, other, ci=False):
	Binary __pure_sub__(Binary const& a = Binary(), Binary const& b = Binary(), bool ci = true) {

		//Boring setup
		Binary out;
		Binary ta = a;
		Binary tb = b;
		sfbu temp;
		random_access_list exp;
		bool co = false;

		//Handle is_zero
		if (a.is_zero == true) {

			if (b.is_zero == true) { return out; };
			return b;

		}

		if (b.is_zero == true) { return a; };
		
		//Set sign
		out.sign = ta.sign;

		//Compute __pure_sub__():
		for (int i = 0; i < mant.size(); i++) {

			temp = ta.mant.get(i).__sub__(tb.mant.get(i), ci);
			ci = temp.co;
			out.mant.push_back(temp);

		};

		return out;

	};

};

int main() {

	Binary a = Binary();

	cout << "\n----------------------------------\nC++: High Precision Floating point\n";

};