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
	SixtyFourBitUnit __add__(
								SixtyFourBitUnit const& a=SixtyFourBitUnit(), 
								SixtyFourBitUnit const& b = SixtyFourBitUnit(), 
								bool ci = false) {

		//Boring setup
		SixtyFourBitUnit out;

		//Handle carry out
		out.co = detect_overflow(a.Mantissa, b.Mantissa, ci);

		//Compute addition
		out.Mantissa = a.Mantissa + b.Mantissa + ci;

		return out;

	}

	//def __sub__(self, other, ci=True):
	SixtyFourBitUnit __sub__(
								SixtyFourBitUnit const& a = SixtyFourBitUnit(), 
								SixtyFourBitUnit const& b = SixtyFourBitUnit(), 
								bool ci = true) {

		//Boring setup
		SixtyFourBitUnit out;
		SixtyFourBitUnit not_b = b;

		not_b.__not__();

		//Handle carry out
		out.co = detect_overflow(a.Mantissa, not_b.Mantissa, ci);

		//Compute subtraction
		out.Mantissa = a.Mantissa + not_b.Mantissa + ci;

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

	bool operator==(SixtyFourBitUnit const& other) {

		//Check sign
		if (this->sign != other.sign) { return false; }

		//Check Mantissa
		if (this->Mantissa != other.Mantissa) { return false; }

		return false;

	};
	bool operator!=(SixtyFourBitUnit const& other) {

		//Check sign
		if (this->sign != other.sign) { return true; }

		//Check Mantissa
		if (this->Mantissa == other.Mantissa) { return false; }

		return true;

	};
	bool operator>(SixtyFourBitUnit const& other) {

		//Check sign
		if (this->sign && !other.sign) { return true; }
		if (!this->sign && other.sign) { return false; }

		//Check mantissa
		if (this->Mantissa > other.Mantissa) { return true; }

		return false;

	};
	bool operator<(SixtyFourBitUnit const& other) {

		//Check sign
		if (this->sign && !other.sign) { return false; }
		if (!this->sign && other.sign) { return true; }

		if (this->Mantissa < other.Mantissa) { return true; }

		return false;

	};
	bool operator>=(SixtyFourBitUnit const& other) {

		if ((*this == other) || (*this > other)) { return true; }

	}; 
	bool operator<=(SixtyFourBitUnit const& other) {

		if ((*this == other) || (*this < other)) { return true; }

	}
	//Get variable length bits from mantissa with an offset
	unsigned long long int GetOffsetBitsFromMantissa(
														unsigned long long int offset = 0, 
														unsigned long long  int length = 1, 
														bool direction = false) {

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

	//Mantissa, Carry Out, sign
	list<SixtyFourBitUnit> data;
	bool co, sign;

	//def __init__(self, data):
	random_access_list(
						list<SixtyFourBitUnit> a = list<SixtyFourBitUnit>(), 
						bool b = false, 
						bool c = true) {

		cout << "--Initializing Random Access List--\n";

		data = a;
		co = b;
		sign = c;

	};

	//Bitwise and
	random_access_list __and__(
								random_access_list a = random_access_list(), 
								random_access_list b = random_access_list()) {

		random_access_list ral;
		random_access_list out;
		list<random_access_list> Aligned = ral.SixtyFourBitUnitAlign(a, b);

		for (int i = 0; i < Aligned.size(); i++) {

			out.push_front(a.get(i).__and__(b.get(i)));

		};

		return out;

	};
	//Bitwise or
	random_access_list __or__(
								random_access_list a = random_access_list(), 
								random_access_list b = random_access_list()) {

		random_access_list ral;
		random_access_list out;
		list<random_access_list> Aligned = ral.SixtyFourBitUnitAlign(a, b);

		for (int i = 0; i < Aligned.size(); i++) {

			out.push_front(a.get(i).__or__(b.get(i)));

		};

		return out;

	};
	//Bitwise xor
	random_access_list __xor__(
								random_access_list a = random_access_list(),
								random_access_list b = random_access_list()) {

		random_access_list ral;
		random_access_list out;
		list<random_access_list> Aligned = ral.SixtyFourBitUnitAlign(a, b);

		for (int i = 0; i < Aligned.size(); i++) {

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
	random_access_list __shift__(
									random_access_list a = random_access_list(), 
									int shifts = 0, 
									bool direction = false) {

		//Boring setup
		random_access_list ral_handler;
		random_access_list out = random_access_list();
		list<random_access_list> AlignedInput;
		unsigned long long int working_lower_int, working_higher_int, working_int_top, working_int_bottom;
		unsigned long long int shifted_offset = static_cast<unsigned long long>(1) << shifts;
		int unsigned_long_long_int_removed = shifts >> 6;

		//Handle shifts larger than 64
		if (direction == false) { //If shift down | div 2
			if (shifts >= 64) { for (int i = 0; i < unsigned_long_long_int_removed; i++) { a.pop_front(); shifts -= 64; } }
		}
		else { //If shift up | mul 2
			if (shifts >= 64) { for (int i = 0; i < unsigned_long_long_int_removed; i++) { a.push_back(0); shifts -= 64; } }
		};

		//Perform shift
		for (size_t i = 0; i < a.size(); i++) {

			//Handle working int's
			if (direction = false) { //If shift down | div 2

				working_higher_int = a.get(i).LimitedToInt();
				if (i >= 1) {

					working_lower_int = a.get(i - 1).LimitedToInt();

				}
				else {

					working_lower_int = 0;

				};

			}
			else { //If shift up | mul 2

				working_lower_int = a.get(i).LimitedToInt();
				if (i + 1 < a.size()) {

					working_higher_int = a.get(i + 1).LimitedToInt();

				}
				else {

					working_higher_int = 0;

				};

			};

			//Calculate actual shift
			working_int_top = (working_higher_int % shifted_offset) << (63 - shifts);
			working_int_bottom = working_lower_int >> shifts;

			out.push_back(working_int_top + working_int_bottom);

		};

		return out;

	};

	//Boring getter
	SixtyFourBitUnit get(size_t index=0) {

		//Boring setup
		list<SixtyFourBitUnit>::iterator it = data.begin();

		//Hack for getting pseudo-random access list
		for (size_t i = 0; i < index; i++) {  it++; }

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

	//Pythonic insert(0, a)
	void push_back(SixtyFourBitUnit a = SixtyFourBitUnit()) { data.push_back(a); };

	//Pythonic append(a)
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

	//def __pure_add__(self, other):
	random_access_list __pure_add__(
									random_access_list a = random_access_list(), 
									random_access_list b = random_access_list(), 
									bool ci = false, 
									bool is_float_add = false) {

		random_access_list ral, aligned_a, aligned_b;
		random_access_list out;

		//Cringe c++ 'must'
		list<random_access_list> aligned_inp = ral.SixtyFourBitUnitAlign(a, b, is_float_add);
		list<random_access_list>::iterator it = aligned_inp.begin();

		//Why can't I just do this like in python?
		aligned_a = *it;
		++it;
		aligned_b = *it;

		list<SixtyFourBitUnit>::iterator a_it = aligned_a.data.begin();
		list<SixtyFourBitUnit>::iterator b_it = aligned_b.data.begin();

		SixtyFourBitUnit worker;

		for (int i = 0; i < aligned_a.size(); i++) {

			worker = worker.__add__(*a_it, *b_it, ci);
			ci = worker.co;

			out.push_front(worker);

			++a_it;
			++b_it;

		}

		return out;

	};
	//def __pure_sub__(self, other):
	random_access_list __pure_sub__(
									random_access_list a = random_access_list(), 
									random_access_list b = random_access_list(), 
									bool ci = true, 
									bool is_float_sub = false,
									bool using_twos_compliments = true) {

		random_access_list ral, aligned_a, aligned_b;
		random_access_list out;

		//Cringe c++ 'must'
		list<random_access_list> aligned_inp = ral.SixtyFourBitUnitAlign(a, b, is_float_sub);
		list<random_access_list>::iterator it = aligned_inp.begin();

		//Why can't I just do this like in python?
		aligned_a = *it;
		++it;
		aligned_b = *it;

		list<SixtyFourBitUnit>::iterator a_it = aligned_a.data.begin();
		list<SixtyFourBitUnit>::iterator b_it = aligned_b.data.begin();

		SixtyFourBitUnit worker;

		for (int i = 0; i < aligned_a.size(); i++) {

			worker = worker.__sub__(*a_it, *b_it, ci);
			ci = worker.co;

			out.push_front(worker);

			++a_it;
			++b_it;

		}

		out.co = ci;

		if (using_twos_compliments==true) {

			if (ci == true) {
				out.sign = ci;
				return out;
			}
			out.__not__();
			out.co = true;
			out.sign = false;
			return out;

		}

		return out;

	};

	random_access_list operator+(const random_access_list& other) {

		random_access_list b = other;
		random_access_list temporary;

		if (this->sign == true) {

			if (other.sign == true) {

				return this->__pure_add__(other);

			};

			return this->__pure_sub__(other);

		};

		if (other.sign == true) {

			return b.__pure_sub__(*this);

		};

		temporary = this->__pure_add__(other);
		temporary.sign = false;

		return temporary;

	};
	random_access_list operator-(const random_access_list& other) {

		random_access_list b = other;
		random_access_list temporary;

		if (this->sign == true) {

			if (other.sign == true) {

				return this->__pure_sub__(other);

			};

			temporary = b.__pure_add__(*this);
			temporary.sign = true;
			return temporary;

		};

		if (other.sign == true) {

			temporary = this->__pure_add__(other);
			temporary.sign = false;
			return temporary;

		};

		temporary = this->__pure_sub__(other);
		temporary.sign = not temporary.sign;
		return temporary;

	};
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

	//TODO
	//Bit-precise alignment of random_access_list's
	//Only use when a and b are same length and b is to be shifted compared to a!
	random_access_list BitAlign(
								random_access_list a,
								random_access_list b, 
								bool Inverse = false, 
								int offset = 0) {

		//Boring setup
		random_access_list out;
		SixtyFourBitUnit SixtyFourBitUnit_handler;
		signed long long int working_lower_int, working_higher_int, working_int_top, working_int_bottom;
		signed long long int shifted_offset = (static_cast<unsigned long long>(1) << offset);

		//If aligning for floating point login
		if (Inverse) {

			for (size_t i = 0; i < a.size(); i++) {

				//Get int's to work with for shifting
				working_lower_int = b.get(i).LimitedToInt();
				if (i < b.size()) {

					working_higher_int = b.get(i + 1).LimitedToInt();

				}
				else {

					working_higher_int = 0;

				};


				//Get top and bottom part of the int to align
				working_int_top = (working_higher_int % shifted_offset) << (63-offset);
				working_int_bottom = working_lower_int >> offset;

				//Insert to out
				SixtyFourBitUnit_handler.set_mantissa(working_int_top + working_int_bottom);
				out.push_front(SixtyFourBitUnit_handler);

			};

		} //If aligning for standard bitwise operations
		else {

			for (size_t i = 0; i < b.size(); i++) {


				//Get int's to work with for shifting
				working_lower_int = b.get(i).LimitedToInt();
				if (i < b.size()) {

					working_higher_int = b.get(i + 1).LimitedToInt();

				}
				else {

					working_higher_int = 0;

				};

				working_int_top = (working_higher_int % shifted_offset) << (63-offset);
				working_int_bottom = working_lower_int >> offset;

				SixtyFourBitUnit_handler.set_mantissa(working_int_top + working_int_bottom);
				out.push_front(SixtyFourBitUnit_handler);

			};

		};

		return out;

	};

	//Why can't I do this like in python?
	list<random_access_list> SixtyFourBitUnitAlign(
													random_access_list a, 
													random_access_list b,
													bool Inverse = false, 
													size_t offset = 0) {

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
	list<random_access_list> SixtyFourBitUnitDivAlign(
														random_access_list a, 
														random_access_list b, 
														size_t offset = 0) {

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

/*High Precision Float->Proprietary format for
  arbitrarily high precision floating point numbers 
  (Cringe inferior c++ implementation to the superior python implementation)*/
const class hpf {

public:

	/*Arbitrarily long mantissa and exponent, based off of
	  the idea of the ieee 754 floating point standard, 
	  but expanded with arbitrarily high precision and large numbers*/
	random_access_list Mantissa, Exponent;
	bool sign, CarryOut, is_zero, CarryIn;

	//__init__(self, mantissa, exponent, sign, co, is_zero):
	hpf(
		random_access_list a = random_access_list(), 
		random_access_list b = random_access_list(), 
		bool c = true, 
		bool d = false, 
		bool e = true, 
		bool f = false) {

		cout << "--Initializing Binary--\n";

		Mantissa = a;
		Exponent = b;
		sign = c;
		CarryOut = d;
		is_zero = e;
		CarryIn = f;

	};

	hpf operator + (hpf const& obj) {

		hpf hpf_handler;

		if (sign == true) {

			if (obj.sign == true) { return hpf_handler.__pure_add__(*this, obj); };
			return hpf_handler.__pure_sub__(*this, obj);

		};

		if (obj.sign == true) { return hpf_handler.__pure_sub__(obj, *this); }
		return hpf_handler.__pure_add__(*this, obj);

	};

	hpf operator - (hpf const& obj) {

		hpf hpf_handler;

		hpf out;

		if (sign == true) {

			if (obj.sign == true) { return hpf_handler.__pure_sub__(*this, obj); };
			return hpf_handler.__pure_add__(*this, obj);

		};

		if (obj.sign == true) { 
			
			out = hpf_handler.__pure_add__(*this, obj);
			out.sign = false;
			return out;
		
		};
		out = hpf_handler.__pure_sub__(*this, obj);
		out.sign = not out.sign;
		return out;

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

	bool operator==(hpf const& other) {

		//Check is_zero flags
		if (this->is_zero != other.is_zero) { return false; }

		random_access_list a_list = this->Mantissa;
		random_access_list b_list = other.Mantissa;

		for (size_t i = 0; i < this->Mantissa.size(); i++) {

			if (a_list.get(i) != b_list.get(i)) { return false; }

		};

		return true;

	};
	bool operator!=(hpf const& other) {

		//Check is_zero flags
		if (this->is_zero != other.is_zero) { return true; }

		random_access_list a_list = this->Mantissa;
		random_access_list b_list = other.Mantissa;

		for (size_t i = 0; i < this->Mantissa.size(); i++) {

			if (a_list.get(i) != b_list.get(i)) { return true; }

		};

		return false;

	};

private:

	//Convert encoded exponent value to actual signed exponent value
	random_access_list GetExponentValue() {

		random_access_list out;

		for (size_t i = 1; i < Exponent.size(); i++) {

			out.push_front(0);

		};

		out.push_front((unsigned long long int)1 << 63);

		return out;

	};

	//TODO
	list<hpf> Align(const hpf a, const hpf b) {

		list<hpf> out;



		return out;
		
	};

	//TODO
	//Propper python gang
	//def __pure_add__(self, other, ci=False):
	hpf __pure_add__(const hpf a, const hpf b, bool ci = false) {

		hpf out;



		return out;

	};

	//def __pure_sub__(self, other, ci=True):
	hpf __pure_sub__(hpf a = hpf(), hpf b = hpf(), bool ci = true) {

		hpf out;



		return out;

	};

};

int main() {

	hpf a = hpf();

	cout << "\n----------------------------------\nC++: High Precision Floating point\n";

	cout << "a: " << a.__str__();

	return 0;

};