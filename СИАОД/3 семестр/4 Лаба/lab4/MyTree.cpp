#include <iostream>
#include <Windows.h>
#include "MyTree.h"

using namespace std;
using namespace MyTask;

//Инициализация
MyTree::MyTree()
{
	root = NULL;
}

//Очитка памяти
MyTree::~MyTree()
{
	travel_tree_clear(root);
}

//Поиск элемента
MyTree::Tree* MyTree::search_tree(Tree* node, int info)
{
	//Если узел пуст - прекращаем обход
	if (!node)
		return NULL;

	//Если нашли нужные данные - возвращаем узел
	if (node->item == info)
		return node;

	//Если нужный элемент меньше текущего - идём в левую ветвь иначе - в правую
	if (info < node->item)
		return(search_tree(node->left, info));
	else
		return(search_tree(node->right, info));
}

//Обход дерева(Вычсиление суммы листьев)
int MyTree::travel_tree_sum(Tree* node)
{
	if (node)
	{
		int sum = 0;
		if ((!node->left) && (!node->right))
			sum += node->item;
		sum += travel_tree_sum(node->left);
		sum += travel_tree_sum(node->right);
		return sum;
	}
	return 0;
}

//Обход дерева(Вывод в консоль)
void MyTree::travel_tree_print_boring(Tree* node, int level)
{
	if (node)
	{
		if ((node->left))
			travel_tree_print_boring(node->left, level + 1);

		if (node != root)
		{
			for (int i = 0; i < level; i++)
			{
				cout << "\t";
			}
		}
		cout << node->item;
		cout << "\n";
		if (node->right)
		{
			travel_tree_print_boring(node->right, level + 1);
		}
	}
}

//Обход дерева(Очистка памяти)
void MyTree::travel_tree_clear(Tree* node)
{
	if (node)
	{
		travel_tree_clear(node->left);
		travel_tree_clear(node->right);
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->item = 0;
		delete[] node;
	}
}

//Получение максимального элемента
MyTree::Tree* MyTree::max_of_tree(Tree* node)
{
	Tree* max;
	if (!node)
		return NULL;
	max = node;
	while (max->right)
		max = max->right;
	return max;
}

//Получение минимального элемента
MyTree::Tree* MyTree::min_of_tree(Tree* node)
{
	Tree* min;
	if (!node)
		return NULL;
	min = node;
	while (min->left)
		min = min->left;
	return min;
}

//Вставка
void MyTree::insert_tree(Tree** node, int info, Tree* parent)
{
	Tree* timeNode;
	if (!(*node))
	{
		timeNode = new Tree;
		timeNode->item = info;
		timeNode->left = timeNode->right = NULL;
		timeNode->parent = parent;
		*node = timeNode;
		if (!parent)
			root = *node;
		return;
	}

	if (info < (*node)->item)
		insert_tree(&((*node)->left), info, *node);
	else
		if (info != (*node)->item)
			insert_tree(&((*node)->right), info, *node);
}

//Удаление
void MyTree::remove_tree(Tree* node)
{
	if (node->left == node->right == NULL)
	{
		if (node->parent->left == node)
		{
			node->parent->left = NULL;
		}
		else
		{
			node->parent->right = NULL;
		}

		node->item = 0;
		node->left = NULL;
		node->right = NULL;
		delete[] node;

		return;
	}

	Tree* pOne = node->left;
	Tree* pTwo = node;

	while (pOne)
	{
		pOne = pOne->right;
		pTwo = pOne;
	}

	if (node->parent->left == node)
	{
		node->parent->left = pTwo;
	}
	else
	{
		node->parent->right = pTwo;
	}

	node->item = 0;
	node->left = NULL;
	node->right = NULL;
	delete[] node;
	
	return;
}
