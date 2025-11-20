//25) схема №12, nt=6, a=5, b=7, c=6, d=4, e=6, f=8, g=4, h=9, i=6, j=5
#include <iostream>
#include <windows.h>
#include <thread>
#include <syncstream>
#include <chrono>
#include <vector>
#include <semaphore>
#include <barrier>

std::counting_semaphore<2> acq_j(0), acq_h_i(0), acq_i_j(0);
std::barrier barrier_for_4(4);


void f(char letter, int operation)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::osyncstream(std::cout) << "З набору " << letter << " виконано дію " << operation << "." << std::endl;
}

//{ a1, a2, a3, a4, a5, b1 } { g1, g2, g3, g4 }
void calc_a_b_g() 
{
	int a = 5;
	for (int i = 1; i <= a; i++)
	{
		f('a', i);
		if (i == a)
			f('b', 1);
	}

	barrier_for_4.arrive_and_wait();

	int g = 4;
	for (int i = 1; i <= g; i++)
		f('g', i);
}

//{b2, b3, b4, b5, b6, b7} {h1, h2, h3, h4}
void calc_b_h()
{
	int b = 7;
	for (int i = 2; i <= b; i++)
		f('b', i); 

	barrier_for_4.arrive_and_wait();

	acq_h_i.release();

	int h = 4;
	for (int i = 1; i <= h; i++)
		f('h', i);	
}

//{c1, c2, c3, c4, c5, c6} {h5, h6, h7, h8}
void calc_c_h()
{
	int c = 6;
	for (int i = 1; i <= c; i++)
		f('c', i); 

	barrier_for_4.arrive_and_wait();

	int h = 8;
	for (int i = 5; i <= h; i++)
		f('h', i);	
}

//{d1, d2, d3, d4, f1, f2} {h9, i1, i2, i3}
void calc_d_f_h_i()
{
	int d = 4;
	for (int i = 1; i <= d; i++)
	{
		f('d', i);
		if (i == d)
		{
			f('f', 1);
			f('f', 2);
		}
	}

	acq_j.release();
	acq_i_j.release();

	acq_h_i.acquire();
	acq_h_i.acquire();

	int i = 3;
	for (int j = 1; j <= i; j++)
	{
		if (j == 1)
			f('h', 9);

		f('i', j);	
	}
}

//{e1, e2, e3, e4, e5, e6} {i4, i5, i6, j1}
void calc_e_i_j()
{
	int e = 6;
	for (int i = 1; i <= e; i++)
		f('e', i);  

	barrier_for_4.arrive_and_wait();

	acq_h_i.release();

	int i = 6;
	for (int k = 4; k <= i; k++)
	{
		f('i', k);
		if (k == i)
		{
			acq_i_j.acquire();
			acq_i_j.acquire();

			f('j', 1);
		}
	}
}

//{f3, f4, f5, f6, f7, f8} {j2, j3, j4, j5}
void calc_f_j()
{
	int f_action = 8;
	for (int i = 3; i <= f_action; i++)
		f('f', i); 

	acq_j.acquire();

	acq_i_j.release();

	int j = 5;
	for (int i = 2; i <= j; i++)
		f('j', i);
}

void executeOp(int number)
{
	if (number == 1)
		calc_a_b_g();

	if (number == 2)
		calc_b_h();

	if (number == 3)
		calc_c_h();

	if (number == 4)
		calc_d_f_h_i();

	if (number == 5)
		calc_e_i_j();

	if (number == 6)
		calc_f_j();
}

int main()
{
	SetConsoleOutputCP(1251);

	int nt = 6;

	std::cout << "Обчислення розпочато.\n";

	std::vector<std::thread> threads;
	for (int i = 1; i <= nt; ++i)
		threads.emplace_back([i]() {executeOp(i); });

	for (auto& thread : threads)
		thread.join();

	std::cout << "Обчислення завершено.\n";
}