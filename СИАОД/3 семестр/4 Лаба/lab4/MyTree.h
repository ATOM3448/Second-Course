namespace MyTask
{
	class MyTree
	{
	public:
		//Структура
		struct Tree
		{
			int item;
			Tree* parent;
			Tree* left;
			Tree* right;
		};

		//Корень
		Tree* root;

		//Инициализация
		MyTree();

		//Очитка памяти
		~MyTree();

		//Поиск элемента
		Tree* search_tree(Tree* node, int info);

		//Обход дерева(Вычсиление суммы листьев)
		int travel_tree_sum(Tree* node);

		//Обход дерева(Вывод в консоль)
		void travel_tree_print_boring(Tree* node, int level = 0);

		//Обход дерева(Очистка памяти)
		void travel_tree_clear(Tree* node);

		//Получение максимального элемента
		Tree* max_of_tree(Tree* node);

		//Получение минимального элемента
		Tree* min_of_tree(Tree* node);

		//Вставка
		void insert_tree(Tree** node, int info, Tree* parent);

		//Удаление
		void remove_tree(Tree* node);
	};
}
