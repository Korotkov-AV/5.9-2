// 5.9-2.cpp 


#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>

class big_integer {
private:
	std::vector<int> num;
public:
	big_integer(std::string  s) {
		for (int i = 0; i < s.length(); i++) {
			num.push_back(int(s[i]) - 48);
		}
	}

	std::string operator +(big_integer& other) {
		int s = (num.size() >= other.num.size()) ? num.size() : other.num.size();
		std::vector<int> res;
		int remainder = 0;
		int i = num.size() - 1;
		int j = other.num.size() - 1;
		for (s - 1; s >= 0; s--) {
			if (i >= 0 && j >= 0) {
				int sum = num[i] + other.num[j] + remainder;
				if (sum < 10) {
					res.push_back(sum);
					remainder = 0;
				}
				else {
					res.push_back(sum - 10);
					remainder = 1;
				}
			}
			else if (i >= 0) {
				res.push_back(num[i]);
				remainder = 0;
			}
			else if (j >= 0) {
				res.push_back(other.num[j]);
				remainder = 0;
			}
			i--;
			j--;
		}

		std::reverse(res.begin(), res.end());

		std::stringstream ss;
		for (auto it = res.begin(); it != res.end(); it++) {
			ss << *it;
		}
		std::string string_res = ss.str();

		return string_res;
	}

	std::string operator *(int other) {
		std::vector<int> res;
		int carry = 0;

		for (int i = num.size() - 1; 0 <= i; i--) {
			int product = num[i] * other + carry;
			res.insert(res.begin(), product % 10);
			carry = product / 10;
		}

		while (carry > 0) {
			res.insert(res.begin(), carry % 10);
			carry /= 10;
		}

		std::stringstream ss;
		for (auto it = res.begin(); it != res.end(); it++) {
			ss << *it;
		}

		std::string string_res = ss.str();
		return string_res;
	}

	big_integer(std::vector<int> other_num) {
		other_num = std::move(num);
	}

	big_integer& operator=(big_integer&& other) noexcept // РѕРїРµСЂР°С‚РѕСЂ РїРµСЂРµРјРµС‰Р°СЋС‰РµРіРѕ РїСЂРёСЃРІР°РёРІР°РЅРёСЏ
	{
		std::swap(num, other.num);
		return *this;
	}

	big_integer(big_integer&& other) noexcept // РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ РїРµСЂРµРјРµС‰РµРЅРёСЏ
		: num(std::move(other.num)) {}


	big_integer& operator=(const big_integer& other) // РѕРїРµСЂР°С‚РѕСЂ РєРѕРїРёСЂСѓСЋС‰РµРіРѕ РїСЂРёСЃРІР°РёРІР°РЅРёСЏ
	{
		return *this = big_integer(other);
	}

	big_integer(const big_integer& other) // РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ РєРѕРїРёСЂРѕРІР°РЅРёСЏ
		: big_integer(other.num) {}
};

int main()
{
	auto number1 = big_integer("114575");
	auto number2 = big_integer("78524");

	auto addition = number1 + number2;
	std::cout << addition << std::endl; // 193099

	auto multiplication = number1 * 3;
	std::cout << multiplication << std::endl;;
}

