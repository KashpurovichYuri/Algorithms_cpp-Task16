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
	std::sort( std::begin(vector1), std::end(vector1) );
	vector1.erase( std::unique( std::begin(vector1), std::end(vector1) ), std::end(vector1) );

	// 5
	auto count_not_even = std::count_if(std::begin(vector1), std::end(vector1), [](auto& i){ return i % 2 != 0; });
	std::cout << "Amount of not even numbers: " << count_not_even << std::endl;

	// 6
	const auto minimum = std::min_element(std::begin(vector1), std::end(vector1));
	const auto maximum = std::max_element(std::begin(vector1), std::end(vector1));
	std::cout << "Min value: " << *minimum << ", max value: " << *maximum << std::endl;
	// alternativly:
	const auto [minimum_alt, maximum_alt] = std::minmax_element(std::begin(vector1), std::end(vector1));
	std::cout << "Alternative way. Min value: " << *minimum << ", max value: " << *maximum << std::endl << std::endl;

	// 7
	auto it = std::find_if(
		std::begin(vector1), 
		std::end(vector1), 
		[](auto& i)
		{
			if ((i == 1) || (i % 2 == 0))
				return 0;
			for (auto j = 3; j < i / 2; j += 2) // we can use j < sqrt(i) to optimize
				if (i % j == 0)
					return 0;
			return 1;
		});
	
	if (it != std::end(vector1))
		std::cout << "The first prime number in the first sequence is " << *it << std::endl;
	else
		std::cout << "There is no prime number in the first sequence is " << std::endl;

	// 8
	std::for_each(std::begin(vector1), std::end(vector1), [](auto& i){ i *= i; });

	// 9
	std::random_device seed;
	std::mt19937 engine(seed());
	std::uniform_int_distribution< int > distribution(0, 30);
	std::vector < int > vector2(vector1.size());
	std::for_each(
		std::begin(vector2), 
		std::end(vector2), 
		[ &engine, &distribution ](auto& i)
		{			
			i = distribution(engine);
		});

	// 10
	auto sum_of_elem_of_vector2 = std::accumulate(std::cbegin(vector2), std::cend(vector2), 0);
	std::cout << "Sum: " << sum_of_elem_of_vector2 << std::endl;

	// 11
	std::fill_n(std::begin(vector2), 3, 1);

	// 12
	std::vector < int > vector3;
	std::transform(std::cbegin(vector1), std::cend(vector1), std::cbegin(vector2),
				   std::back_inserter(vector3), std::minus<> {});

	// 13
	std::replace_if(std::begin(vector3), std::end(vector3), [](auto& i){ if (i < 0) return 1; else return 0; }, 0);

	// 14? because of the next line, the program does not output everything that is expected
	vector3.erase( ( std::remove(std::begin(vector3), std::end(vector3), 0 ), std::end(vector3)));

	// 15
	std::reverse(std::begin(vector3), std::end(vector3));

	// 16
	std::nth_element(std::begin(vector3), std::next(std::begin(vector3), 2), std::end(vector3), std::greater {});
	std::cout << "Top-3 the biggest elements of the third sequance is " 
		<< vector3.at(0) << ", " << vector3.at(1) << ", " << vector3.at(2) << std::endl;

	// 17
	std::sort(std::begin(vector1), std::end(vector1));
	std::sort(std::begin(vector2), std::end(vector2));

	// 18
	std::vector < int > vector4;
	std::merge(std::cbegin(vector1), std::cend(vector1), std::cbegin(vector2), std::cend(vector2), std::back_inserter(vector4));

	// 19
	const auto [begin_index, end_index] = std::equal_range(std::cbegin(vector4), std::cend(vector4), 1);
	auto left = std::distance(std::cbegin(vector4), begin_index);
	auto right = left + std::distance(begin_index, end_index);
	std::cout << "Diapazone of ordered insertion of 1: ["
		<< left << ", " << right << ")" << std::endl;

	// 20
	std::cout << std::endl << std::endl;
	std::copy(std::cbegin(vector1), std::cend(vector1), std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl << std::endl;
	std::copy(std::cbegin(vector2), std::cend(vector2), std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl << std::endl;
	std::copy(std::cbegin(vector3), std::cend(vector3),	std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl << std::endl;
	std::copy(std::cbegin(vector4), std::cend(vector4),	std::ostream_iterator < int > (std::cout, " "));
	std::cout << std::endl << std::endl;

	system("pause");

	return EXIT_SUCCESS;

}