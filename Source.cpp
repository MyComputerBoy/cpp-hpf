//hpf.cpp -> proprietary high precision floating point format --OHP branch - Optimized High Performance high precision floating point format
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
class SixtyFourBitUnit {

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
	
	//Mantissa is 64 bit unsigned integer, co, sign, ci is bool
	unsigned long long int Mantissa;
	bool co, sign, ci;

	//__init__(self, Mantissa, co, sign, ci):
	SixtyFourBitUnit(unsigned long long int a=0, bool b=false, bool c=true, bool d=false) {

		cout << "--Initializing Sixty-four Bit Signed Unit--\n";

		Mantissa = a;
		co = b;
		sign = c;
		ci = d;

	};
	
	//Bitwise and
	SixtyFourBitUnit __and__(SixtyFourBitUnit const& obj) {

		SixtyFourBitUnit a = *this;
		SixtyFourBitUnit b = obj;
		SixtyFourBitUnit out;

		out = a.get_mantissa() & b.get_mantissa();

		return out;

	};

	//Bitwise or
	SixtyFourBitUnit __or__(SixtyFourBitUnit const& obj) {

		SixtyFourBitUnit a = *this;
		SixtyFourBitUnit b = obj;
		SixtyFourBitUnit out;

		out = a.get_mantissa() | b.get_mantissa();

		return out;

	};

	//Bitwise xor
	SixtyFourBitUnit __xor__(SixtyFourBitUnit const& obj) {

		SixtyFourBitUnit a = *this;
		SixtyFourBitUnit b = obj;
		SixtyFourBitUnit out;

		out = a.get_mantissa() ^ b.get_mantissa();

		return out;

	};

	//Bitwise not
	SixtyFourBitUnit __not__() {

		SixtyFourBitUnit a = *this;
		SixtyFourBitUnit out;

		out = ~a.get_mantissa();

		return out;

	};

	//Boring setter
	void set_mantissa(unsigned long long int a = 0) {

		Mantissa = a;

	};

	//Boring getter
	unsigned long long int get_mantissa() {

		return Mantissa;

	}

	//Propper python gang
	//def __add__(self, other, ci=False):
	SixtyFourBitUnit __add__(SixtyFourBitUnit const& a=SixtyFourBitUnit(), SixtyFourBitUnit const& b = SixtyFourBitUnit(), bool ci = false) {

		//Boring setup
		SixtyFourBitUnit out;

		//Handle carry out
		out.co = detect_overflow(a.Mantissa, b.Mantissa, ci);

		//Compute addition
		out.Mantissa = a.Mantissa + b.Mantissa;

		return out;

	}

	//def __sub__(self, other, ci=True):
	SixtyFourBitUnit __sub__(SixtyFourBitUnit const& a = SixtyFourBitUnit(), SixtyFourBitUnit const& b = SixtyFourBitUnit(), bool ci = true) {

		//Boring setup
		SixtyFourBitUnit out;

		//Handle carry out
		out.co = detect_overflow(a.Mantissa, ~b.Mantissa, ci);

		//Compute subtraction
		out.Mantissa = a.Mantissa - b.Mantissa;

		return out;
	}

	//Cringe c++
	//__add__(self, other, ci=False):
	SixtyFourBitUnit operator + (SixtyFourBitUnit const& obj) {
		
		//Boring setup
		SixtyFourBitUnit res;

		//Handle carry out
		res.co = detect_overflow(Mantissa, obj.Mantissa, ci);

		//Compute addition
		res.Mantissa = Mantissa + obj.Mantissa;

		return res;

	};

	//__sub__(self, other, ci=True):
	SixtyFourBitUnit operator - (SixtyFourBitUnit const& obj) {

		//Boring setup
		SixtyFourBitUnit res;

		//Handle carry out
		res.co = detect_overflow(Mantissa, ~obj.Mantissa, not ci);

		//Compute subtraction
		res.Mantissa = Mantissa - obj.Mantissa;

		return res;

	}

	//Get variable length bits from mantissa with an offset
	unsigned long long int GetOffsetBitsFromMantissa(unsigned long long int offset = 0, unsigned long long  int length = 1, bool direction = false) {

		//Boring setup
		unsigned long long int out = 0;
		unsigned long long int mask;
		unsigned long long int temp_bit;

		//Extracting bits from mantissa
		for (int i = 0; i < length; i++) {

			//If direction is false read right to left and write right to left
			if (direction == false) {

				mask = static_cast<unsigned long long>(1) << (offset + i);
				temp_bit = mask >> (offset + i);

			}
			else { //If direction is true read left to left and write right to left

				mask = static_cast<unsigned long long>(1) << (offset - i);
				temp_bit = mask >> (offset - i);

			};

			temp_bit = temp_bit << i;
			out += temp_bit;

		};

		return out;

	};

	signed long long int LimitedToInt() {

		signed long long int out = Mantissa;

		if (sign) { return out; }
		else { return -out; }

	}

	//__str__(self):
	string ToString() {

		stringstream work_out;
		string out, sign_str;

		//Handle sign
		if (sign == true) { sign_str = "+"; }
		else { sign_str = "-"; }
		
		//Convert mantissa to string
		work_out << sign_str << Mantissa;

		//Convert to std::string
		out = work_out.str();

		return out;

	}

};

//Cringe inferior c++ class for pythonic dynamic random access lists
class random_access_list {

public:

	list<SixtyFourBitUnit> data;

	//def __init__(self, data):
	random_access_list(list<SixtyFourBitUnit> a = list<SixtyFourBitUnit>()) {

		cout << "--Initializing Random Access List--\n";

		data = a;

	};

	//Bitwise and
	random_access_list __and__(random_access_list a = random_access_list(), random_access_list b = random_access_list()) {

		random_access_list ral;
		random_access_list out;
		list<random_access_list> Alligned = ral.Align(a, b);

		for (int i = 0; i < Alligned.size(); i++) {

			out.push_front(a.get(i).__and__(b.get(i)));

		};

		return out;

	};
	//Bitwise or
	random_access_list __or__(random_access_list a = random_access_list(), random_access_list b = random_access_list()) {

		random_access_list ral;
		random_access_list out;
		list<random_access_list> Alligned = ral.Align(a, b);

		for (int i = 0; i < Alligned.size(); i++) {

			out.push_front(a.get(i).__or__(b.get(i)));

		};

		return out;

	};
	//Bitwise xor
	random_access_list __xor__(random_access_list a = random_access_list(), random_access_list b = random_access_list()) {

		random_access_list ral;
		random_access_list out;
		list<random_access_list> Alligned = ral.Align(a, b);

		for (int i = 0; i < Alligned.size(); i++) {

			out.push_front(a.get(i).__xor__(b.get(i)));

		};

		return out;

	};
	//Bitwise not
	random_access_list __not__(random_access_list a = random_access_list()) {

		random_access_list out;

		for (int i = 0; i < a.size(); i++) {

			out.push_front(a.get(i).__not__());

		};

		return out;

	};
	//TODO
	//Bitwise shift
	random_access_list __shift__(random_access_list a = random_access_list(), int shifts = 0, bool direction = false) {

		random_access_list out = random_access_list();

		//Shift down | floor(div 2)
		if (direction == false) {

			for (int i = 0; i < a.size(); i++) {



			};

		}//Shift up | mul 2
		else {



		}

		return out;

	};

	//Boring getter
	SixtyFourBitUnit get(int index=0) {

		//Boring setup
		list<SixtyFourBitUnit>::iterator it = data.begin();

		//Hack for getting pseudo-random access list
		for (int i = 0; i < index; i++) {  it++; }

		return *it;

	}

	//Boring setter
	void set(int index = 0, SixtyFourBitUnit a = SixtyFourBitUnit()) {

		//Boring setup
		list<SixtyFourBitUnit>::iterator it = data.begin();

		//Hack for getting pseudo-random access list
		for (int i = 0; i < index; i++) { it++; }

		*it = a;

	};

	//Why can't I do this like in python?
	void set_ci(int index = 0, bool a = false) {

		//Annoyingly you have to get object
		SixtyFourBitUnit temp = get(index);

		//Then set parameter
		temp.ci = a;

		//Then apply to the actual object
		set(index, temp);

	};

	//Pythonic append(0, a)
	void push_back(SixtyFourBitUnit a = SixtyFourBitUnit()) { data.push_back(a); };

	//Pythonic append(-1, a)
	void push_front(SixtyFourBitUnit a = SixtyFourBitUnit()) { data.push_front(a); };

	//Pythonic pop(0)
	SixtyFourBitUnit pop_front() {

		//Hack for pythonic pop(0)
		SixtyFourBitUnit out = data.front();
		data.pop_front();

		return out;

	};

	//Python pop(-1)
	SixtyFourBitUnit pop_back() {

		//Hack for pythonic pop(-1)
		SixtyFourBitUnit out = data.back();
		data.pop_back();

		return out;

	}

	string ToTring() {

		string out = "";

		for (int i = 0; i < this->size(); i++) {

			out += this->get(i).ToString();

		}

		return out;

	}

	size_t size() { return data.size(); };

private:

	//Semi-redundant LengthAppend(self, length = 1, a = 0):
	void LengthAppend(size_t length = 1, unsigned long long int a = 0) {

		for (int i = 0; i < length; i++) {

			data.push_back(a);

		};

	}

	//Semi-redundant InverseLengthAppend(self, length = 1, a = 0):
	void InverseLengthAppend(size_t length = 1, unsigned long long int a = 0) {

		for (size_t i = 0; i < length; i++) {

			data.push_front(a);

		};

	}

	//Why can't I do this like in python?
	list<random_access_list> Align(random_access_list a=random_access_list(), random_access_list b=random_access_list(), bool Inverse = false, size_t offset = 0) {

		//Boring setup
		list<random_access_list> out = list<random_access_list>();
		random_access_list _new_self = a;
		random_access_list _new_other = b;
		size_t _self_len = _new_self.size();
		size_t _other_len = _new_other.size();

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
	//DivAlign(self, other, offset=0):
	list<random_access_list> DivAlign(random_access_list a, random_access_list b, size_t offset = 0) {

		//Boring setup
		list<random_access_list> out = list<random_access_list>();
		random_access_list _new_self = a;
		random_access_list _new_other = b;
		size_t _self_len = a.size();
		size_t _other_len = b.size();

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

//High Precision Float -> Proprietary format for arbitrarily high precision floating point numbers (Cringe inferior c++ implementation to the superior python implementation)
class hpf {

public:

	//Arbitrarily long mantissa and exponent, based off of the idea of the ieee 754 floating point standard, but expanded with arbitrarily high precision and large numbers
	random_access_list Mantissa, Exponent;
	bool sign, CarryOut, is_zero, CarryIn;

	//__init__(self, mantissa, exponent, sign, co, is_zero):
	hpf(random_access_list a = random_access_list(), random_access_list b = random_access_list(), bool c = true, bool d = false, bool e = true, bool f = false) {

		cout << "--Initializing Binary--\n";

		Mantissa = a;
		Exponent = b;
		sign = c;
		CarryOut = d;
		is_zero = e;
		CarryIn = f;

	};

	//Boring setter
	void set_mant(list<SixtyFourBitUnit> a) { Mantissa = a; };

	//Boring getter
	random_access_list get_mantissa() { return Mantissa; };

	//TODO
	hpf shift(hpf a, unsigned long long int shifts, bool direction) {

		hpf q;

		

		return q;

	};

	hpf operator + (hpf const& obj) {

		hpf a = *this;
		hpf b = obj;

		if (sign == true) {

			if (obj.sign == true) { return this->__pure_add__(obj); };
			return this->__pure_sub__(obj);

		};

		if (obj.sign == true) { return b.__pure_sub__(a); }
		return this->__pure_add__(obj);

	};

	hpf operator - (hpf const& obj) {

		hpf a = *this;
		hpf b = obj;
		hpf out;

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

	hpf __float_add__(hpf a, hpf b, bool ci = false) {

		hpf q;



		return q;

	};

	size_t GetLength() { return Mantissa.size(); };

	string __str__() {

		string out;
		signed long long int exp_val;
		unsigned long long int bits;

		//Handle zero
		if (is_zero == true) { return "0"; }

		//Handle sign
		if (sign == false) { out = "-"; }
		else { out = "+"; }

		//Handle large numbers, default to "infinity"
		if (Exponent.size() > 1 && Exponent.get(1).LimitedToInt() > 0) { return out + "infinity"; }

		//Handle Numbers within 64 bits
		if (Exponent.size() == 1 && Exponent.get(0).LimitedToInt() < 64) {

			exp_val = Exponent.get(0).LimitedToInt();

			bits = Mantissa.get(0).GetOffsetBitsFromMantissa(64 - exp_val, exp_val);
			out += to_string(bits);

		};

		return out;

	};

	string __repr__() {

		string out;

		if (sign == false) { out = "-"; }
		else { out = "+"; }

		out += Exponent.ToTring() + "|" + Mantissa.ToTring();

		return out;

	};

private:

	//TODO
	//Propper python gang
	//def __pure_add__(self, other, ci=False):
	hpf __pure_add__(hpf a = hpf(), hpf b = hpf(), bool ci = false) {

		hpf out;



		return out;

	};

	//def __pure_sub__(self, other, ci=False):
	hpf __pure_sub__(hpf a = hpf(), hpf b = hpf(), bool ci = true) {

		hpf out;



		return out;

	};

};

int main() {

	hpf a = hpf();

	cout << "\n----------------------------------\nC++: High Precision Floating point\n";

	return 0;

};