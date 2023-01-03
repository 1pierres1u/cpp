#include <functional>
#include <iostream>
using namespace std;

struct Foo{
	Foo(int num):num_(num){}
	void print_add(int i) const{cout << num_+i<< "\n";}
	int num_;
};

void print_num(int i){
	cout << i << "\n";
}

struct PrintNum{
	void operator()(int i)const{
		cout << i << "\n";
	}
};

int main(){
	function<void(int)> f_display = print_num;
	f_display(-9);

	function<void()> f_display_42 = [](){print_num(42);};
	f_display_42();

	function<void()> f_display_31337 = bind(print_num,31337);
	f_display_31337();

	function<void(const Foo&, int)> f_add_display = &Foo::print_add;
	const Foo foo(314159);
	f_add_display(foo,1);
	f_add_display(314159,1);

	function<int(Foo const&)> f_num = &Foo::num_;
	cout << "num_: " << f_num(foo) << "\n";

	using std::placeholders::_1;
	function<void(int)> f_add_display2 = bind(&Foo::print_add, foo,_1);
	f_add_display2(2);

	function<void(int)> f_add_display3 = bind(&Foo::print_add, &foo, _1);
	f_add_display3(3);

	function<void(int)> f_display_obj = PrintNum();
	f_display_obj(18);

	auto factorial = [](int n){
		function<int(int)> fac = [&](int n){return (n<2)?1:n*fac(n-1);};
		return fac(n);
	};
	for(int i{5}; i!=8; i++){
		cout << i << "!= " << factorial(i) << "; ";
	}

}
