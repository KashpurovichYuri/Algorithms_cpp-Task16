#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>
#include <random>

int main()
{
	// 1
	std::vector < int > vector1(10);
	std::iota(std::begin(vector1), std::end(vector1), 1);
	
	// 2
	std::copy(
		std::istream_iterator < int > (std::cin),
		std::istream_iterator < int > (),
		std::back_inserter(vector1));

	// 3
	std::random_device seed1;
	std::mt19937 engine1(seed1());
	std::shuffle(std::begin(vector1), std::end(vector1), engine1);

	// 4
	std::sort( vector1.begin(), vector1.end() );
	vector1.erase( std::unique( vector1.begin(), vector1.end() ), vector1.end() );

	// 5
	auto count_not_even = std::count_if(std::begin(vector1), std::end(vector1), [](int i){ return i % 2 != 0; });
	std::cout << "Amount of not even numbers: " << count_not_even << std::endl;

	// 6
	const auto minimum = std::min_element(std::begin(vector1), std::end(vector1));
	const auto maximum = std::max_element(std::begin(vector1), std::end(vector1));
	std::cout << "Min value: " << *minimum << ", max value: " << *maximum << std::endl;

	// 7
	auto it = std::find_if(
		std::begin(vector1), 
		std::end(vector1), 
		[](int i)
		{
			if ((i == 1) || (i % 2 == 0))
				return 0;
			for (auto j = 3; j < i / 2; j += 2) // we can use j < sqrt(i) to optimize
				if (i % j == 0)
					return 0;
			return 1;
		});
		
	std::cout << "The first prime number in the first sequance is " << *it << std::endl;

	// 8
	std::for_each(std::begin(vector1), std::end(vector1), [](int& i){ i *= i; });

	// 9
	std::vector < int > vector2(vector1.size());
	std::for_each(
		std::begin(vector2), 
		std::end(vector2), 
		[](int& i)
		{
			std::random_device seed;
			std::mt19937 engine(seed());
			std::uniform_int_distribution< int > distribution(0, 30);
			i = distribution(engine);
		});

	// 10
	auto sum_of_elem_of_vector2 = std::accumulate(std::begin(vector2), std::end(vector2), 0);
	std::cout << "Sum: " << sum_of_elem_of_vector2 << std::endl;

	// 11
	std::fill_n(std::begin(vector2), (vector2.size() - 5 > 0) ? vector2.size() - 5 : 1, 1);

	// 12
	std::vector < int > vector3;
	std::set_difference(vector1.begin(), vector1.end(), vector2.begin(), vector2.end(), std::back_inserter(vector3));

	// 13
	std::for_each(std::begin(vector3), std::end(vector3), [](int& i){ if (i < 0) i = 0; });

	// 14? because of the next line, the program does not output everything that is expected
	vector3.erase( ( std::remove(std::begin(vector3), std::end(vector3), 0 ), std::end(vector3)));

	// 15
	std::reverse(std::begin(vector3), std::end(vector3));

	// 16
	std::nth_element(std::begin(vector3), std::next(std::begin(vector3), 2), std::end(vector3), std::greater {});
	std::nth_element(std::begin(vector3), std::next(std::begin(vector3), 1), std::end(vector3), std::greater {});
	std::cout << "Top-3 the biggest elements of the third sequance is " 
		<< vector3.at(0) << ", " << vector3.at(1) << ", " << vector3.at(2) << std::endl;

	// 17
	std::sort(std::begin(vector1), std::end(vector1));
	std::sort(std::begin(vector2), std::end(vector2));

	// 18
	std::vector < int > vector4;
	std::set_union(vector1.begin(), vector1.end(), vector2.begin(), vector2.end(), std::back_inserter(vector4));

	// 19
	auto diapazone = std::find(std::begin(vector4), std::end(vector4), 1);
	auto size_of_diapazone = std::count(std::begin(vector4), std::end(vector4), 1);
	auto minimal_index = std::distance(std::begin(vector4), diapazone);
	auto maximal_index = minimal_index + size_of_diapazone;
	std::cout << "Diapazone of ordered insertion of 1: ["
		<< minimal_index << ", " << maximal_index << ")" << std::endl;

	// or using equal range:
	auto pair = std::equal_range(std::begin(vector4), std::end(vector4), 1);
	auto begin_index = pair.first;
	auto end_index = pair.second;
	auto left = std::distance(std::begin(vector4), begin_index);
	auto size = std::distance(begin_index, end_index);
	auto right = minimal_index + size;
	std::cout << "Diapazone of ordered insertion of 1: ["
		<< left << ", " << right << ")" << std::endl;

	// 20
	std::cout << std::endl << std::endl;
	std::copy(vector1.cbegin(), vector1.cend(), std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl << std::endl;
	std::copy(vector2.cbegin(), vector2.cend(), std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl << std::endl;
	std::copy(vector3.cbegin(), vector3.cend(),	std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl << std::endl;
	std::copy(vector4.cbegin(), vector4.cend(),	std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl << std::endl;

	system("pause");

	return EXIT_SUCCESS;

}