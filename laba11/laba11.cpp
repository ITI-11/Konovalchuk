#include<iostream>
#include<stdlib.h>

int numLength(int n){
	int s = 0;
	if(n == 0) 
		return 1;
		
	while(n > 0){ 
		n = n / 10;
		s++;
	}
	return s;
}

bool do_you_have_permissions(int you_have, int you_need){
	std::string go_next;
	
	if(you_have > you_need){
		std::cout << "Упс!Недостаточно прав!\nВведите что-нибудь, чтобы продолжить\n";
		std::cin >> go_next;
		return false;
	}	
	return true;
}

void makeSpaces(int n){
	for(int i = 0;i < n;i++)
		std::cout << " ";
}

struct data{
	std::string name;
	int page_;
	int padding_;
	int appeal;  //обращений
};

void autentification(int *authority){
	std::string user_name;
	int password;
	
	std::cout << "Введите имя пользователя\n";
	std::cin >> user_name;
	std::cout << "ВВедите пароль\n";
	std::cin >> password;
	
	if(user_name == "admin" && password == 1){
		std::cout << "Добро пожаловать, админ!!!\n";
		*authority = 1;
		return;
	}
	if(user_name == "user" && password == 2){
		std::cout << "Добро пожаловать, пользователь\n";
		*authority = 2;
		return;
	}
	if(user_name == "reader" && password == 3){
		std::cout << "Доступно только чтение\n";
		*authority = 3;
		return;
	}
	std::cout << "Неправильное имя или пароль\n";
	autentification(authority);
}

void giveInfo(float available_memory, int num_of_pages, int num_of_free_pages, float size_of_page){
	float percent_of_free_pages;
	int translate;
	
	percent_of_free_pages = (float)num_of_free_pages * 100 / (float)num_of_pages;
	
	translate = percent_of_free_pages * 10;
	percent_of_free_pages = (float)translate / 10;
	
	translate = size_of_page * 10;
	size_of_page = (float)translate / 10;
	
	translate = available_memory * 10;
	available_memory = (float)translate / 10;
	
	std::cout << "1.Добавить";
	makeSpaces(88 - numLength(available_memory));
	std::cout << "Свободной памяти: " << available_memory << "КБ\n2.Удалить";
	makeSpaces(96 - numLength(num_of_pages));
	std::cout << "Число страниц: " << num_of_pages << "\n3.Показать таблицу";
	makeSpaces(79 - numLength(num_of_free_pages));
	std::cout << "Свободных страниц: " << percent_of_free_pages << "%\n4.Показать физический адрес";
	makeSpaces(73 - numLength(size_of_page));
	std::cout << "Размер страницы: " << size_of_page << "КБ\n5.Обратится куда-нибудь\n6.Выход\n";
}

void showAddress(int page, int padding, data *a, int prikol){
	int i = 0;
	std::string go_next;
	bool found = true;
	while(i < prikol && found){
		if((a+i)->page_ == page && (a+i)->padding_ == padding)
			found = false;
		i++;
	}
	std::cout << a+i << "\nВведите что-нибудь, чтобы продолжить\n";
	std::cin >> go_next;
	
}

void do_smth(data *a, int prikol, int authority){
	int i = rand() % (prikol);
	(a+i)->appeal = (a+i)->appeal + (rand() % 10);
}

void showTable(data *a, int prikol){
	for(int i = 0; i < 80;i++) 
		std::cout << "_";
	std::cout << "\n";	
	std::cout << "Имя процесса        |" << "        Номер страницы     |" << "           Сдвиг              |\n";
	
	for(int i = 0;i < 80;i++)
		std::cout << "-";
	std::cout << "\n";
	
	for(int i = 0;i < prikol;i++){
		std::cout << (a+i)->name;
		makeSpaces(20 - (a+i)->name.length());
		std::cout << "|" << (a+i)->page_;
		makeSpaces(27 - numLength((a+i)->page_));
		std::cout << "|" << (a+i)->padding_;
		makeSpaces(30 - numLength((a+i)->padding_));
		std::cout << "|\n";
	}
	
	for(int i = 0;i < 80;i++)
		std::cout << "-";
		
	std::cout << "\nВведите что-нибудь, чтобы продолжить\n";
	std::string go;
	std::cin >> go;
}

void remove(data *a, int *n, int page_to_kill, int padding_to_kill, float *available_memory, float size_of_page, int *num_of_free_pages){
		
	bool i_find_it = false;
	
	for(int i = 0;i < *n;i++){
		if((a+i)->page_ == page_to_kill && (a+i)->padding_ == padding_to_kill){
			i_find_it = true;
			*(available_memory) += size_of_page;
		}
			
		if(i_find_it)
			*(a+i) = *(a+i+1);
	}
	if(i_find_it){
		*n = *n - 1;
		*num_of_free_pages = *num_of_free_pages + 1;
	}
}

void you_not_admin(data *a, int *n, int *j, int *prikol, float *available_memory, int *num_of_free_pages, float *size_of_page){
	*available_memory = 150;
	*size_of_page = 50;
	
	*num_of_free_pages = 2;
	*(available_memory) -= *size_of_page;
	(a+*prikol)->name = "p1"; 
	(a+*prikol)->appeal = 0 + rand() % 10;
	
	if(*n > 10){
		*j = *j + 1;
		*n = 0;
	}
	
	(a+*prikol)->page_ = *j;
	(a+*prikol)->padding_ = *n;
	*n = *n + 1;
	*prikol = *prikol + 1;
}

void addPlace(data *a, int *n, int *j, int *prikol, float *available_memory, int *num_of_free_pages, float size_of_page){
	std::string name;
	
	if(*num_of_free_pages == 0){
		int page_of_min;
		int padding_of_min;
		
		int s;
		s = (a+1)->appeal;
		page_of_min = (a+1)->page_;
		padding_of_min = (a+1)->padding_;
		
		for(int i = 0;i < *prikol;i++)
			if((a+i)->appeal < s){
				s = (a+i)->appeal;
				page_of_min = (a+i)->page_;
				padding_of_min = (a+i)->padding_;
			}
		remove(a, prikol, page_of_min, padding_of_min, available_memory, size_of_page, num_of_free_pages);
	}
		
	std::cout << "Введите имя процесса\n";
	std::cin >> name;
	
	*num_of_free_pages = *num_of_free_pages - 1;
	*(available_memory) -= size_of_page;
	(a+*prikol)->name = name; 
	(a+*prikol)->appeal = 0 + rand() % 10;
	
	if(*n > 10){
		*j = *j + 1;
		*n = 0;
	}
	
	(a+*prikol)->page_ = *j;
	(a+*prikol)->padding_ = *n;
	*n = *n + 1;
	*prikol = *prikol + 1;
}

void create_memory(float *available_memory,int *num_of_pages,int *num_of_free_pages, float *size_of_page){
	std::cout << "Введите доступную память(кб)\n";
	std::cin >> *available_memory;
	std::cout << "Сколько страниц нужно?\n";
	std::cin >> *num_of_pages;
	*num_of_free_pages = *num_of_pages;
	*size_of_page = *available_memory / *num_of_pages;
}

int main(){
	setlocale(LC_ALL, "Russian");
	bool dialog = true;
	int your_choose;
	data memory[100];
	int n = 0;
	int j = 0;
	int prikol = 0;  // Сколько процессов всего
	float available_memory;
	int num_of_pages;
	int num_of_free_pages;
	int authority;
	float size_of_page;
	
	autentification(&authority);
	
	if(authority > 1){
		you_not_admin(&memory[0], &n, &j, &prikol, &available_memory, &num_of_free_pages, &size_of_page);
		num_of_pages = 3;
	}
	else
		create_memory(&available_memory, &num_of_pages, &num_of_free_pages, &size_of_page);
		
	while(dialog){
	system("clear");
		giveInfo(available_memory, num_of_pages, num_of_free_pages, size_of_page);
		std::cout << "Что бы вы хотели сделать?\n";
		std::cin >> your_choose;
		
		switch(your_choose){
			case 1:
				if(do_you_have_permissions(authority, 1))
					addPlace(&memory[0], &n, &j, &prikol, &available_memory, &num_of_free_pages, size_of_page);
				break;
			case 2:
				if(do_you_have_permissions(authority, 1)){
					int page_to_kill;
					int padding_to_kill;
					std::cout << "Введите номер страницы и сдвиг\n";
					std::cin >> page_to_kill >> padding_to_kill;
					remove(&memory[0], &prikol, page_to_kill, padding_to_kill, &available_memory, size_of_page, &num_of_free_pages);
				}
				break;
			case 3:
				showTable(&memory[0], prikol);
				break;
			case 4:
				std::cout << "Введите номер страницы и сдвиг\n";
				int page;
				int padding;
				std::cin >> page >> padding;
				showAddress(page, padding, &memory[0], prikol);
				break;
			case 5:
				if(do_you_have_permissions(authority, 2))
					do_smth(&memory[0], prikol, authority);
				break;
			case 6:
				dialog = false;
				break;
				
		}
	}
	std::cout << "\nХорошего дня!";
	return 0;
}
