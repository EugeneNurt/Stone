#include <iostream>
#include <random>
#include <chrono>
#include <sstream>

int read_int(const char * question){
		int result;
	re:	std::string inp;
		std::cout << question;
		std::getline (std::cin, inp);
		{
			std::stringstream inps {inp};
			inps >> result;
			if (inps.fail()){
				if (std::cin.fail()){
					std::cerr << "������ �����-������!" << std::endl;
					exit(1);
				}
				std::cout << "| ������������ ����!" << std::endl;
				goto re;
			} else if(not inps.eof()) {
				std::cout << "| �����-�� ������ ����! ����� �������" << std::endl;
				goto re;
			}
		}
		return result;
}

int read_int_in_range(const char * question, int min, int max){ // @suppress("No return")
	int result;
	for(;;) {
		result = read_int(question);
		if (result >= min and result <= max)
			return result;
		std::cout << "| ����� ������ ���� � ��������� �� " << min << " �� " << max << std::endl;
	}
}

int main(){
	using clk = std::chrono::system_clock;
	std::minstd_rand rnd{
		unsigned(clk::now().time_since_epoch().count())
	};
	std::uniform_int_distribution <> d{15,25};
	std::uniform_int_distribution <> db{1,3};
	unsigned stone_count = d(rnd);

	int level = read_int_in_range("| ----------------------------\n| �������� ������� ���������:\n| 1) ������\n| 2) �������\n| 3) �������3\n| ", 1, 3);

	std::cout << "| ----------------------------\n| � ���� " << stone_count << " ������" << std::endl;
	do {
		int count = read_int_in_range("| ������� ���-�� ������: ", 1, std::min(3u, stone_count));
		stone_count -= count;
		if (stone_count < 26){
			std::cout << "| � ���� " << stone_count << " ������" << std::endl;
		}
		if (stone_count == 0 || stone_count > 25){
			std::cout << "| ----------------------------\n � � --| ��� ������� |--" << std::endl;
			break;
		} else {
			unsigned count_bot;
			if (stone_count < 5 && level != 1){
				switch(stone_count){
					case 4: count_bot = 3; break;
					case 3: count_bot = 2; break;
					case 2: count_bot = 1; break;
				}
			} else {
				if(level == 1){
					count_bot = db(rnd);
				} else if (level == 2){
					switch(count){
						case 1: count_bot = 3; break;
						case 2: count_bot = 2; break;
						case 3: count_bot = 1; break;
					}
				} else {
					for(unsigned i = 25; i > 0; i -= 4){
						if (i == stone_count){
							count_bot = db(rnd);
							break;
						}
						if (stone_count > i){
							count_bot = stone_count - i;
							break;
						}
					}
				}
			}
			stone_count -= count_bot;
			std::cout << "| ��� ���� " << count_bot << " �����\n| ----------------------------" << std::endl;
			if (stone_count == 0 || stone_count > 25){
				std::cout << " --| ������������ ������� |--" << std::endl;
				break;
			}
			std::cout << "| � ���� " << stone_count << " ������" << std::endl;
		}
	}while(true);
	return 0;
}
// 1 5 9 13 17 21 25
