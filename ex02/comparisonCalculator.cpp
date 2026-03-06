//From emuminov FordJohnson Alogirthm: Humain Explenation & Visualisation by Clara
#include <cmath>
#include <cstdlib>
#include <iostream>

int F(int n);

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Wrong number of arguments" << std::endl;
		return 1;
	}
	int size = std::strtol(av[1], NULL, 10);
	std::cout << "For a list of " << size << " numbers there should be a maximum of " << F(size) << " comparisons" << std::endl;
	return 0;
}

int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}
