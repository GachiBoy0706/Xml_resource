#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>

class Node {
public:
	int value = 0;
	std::string name = "";
	std::vector<std::unique_ptr<Node>> children;
	Node(std::string name, int value) :name(name), value(value) {};
	Node(const std::string name, const int value, std::vector<std::unique_ptr<Node>>& children) :name(name), value(value) {
		this->children = std::move(children);
	};

	Node() {};
};

class Xml_resource {
private:
	std::unique_ptr<Node> root = nullptr;
	std::unique_ptr<Node> rec_load(std::vector<std::string>& parsed, int& index);
	void rec_node_print(std::unique_ptr<Node>& node);
	void rec_node_upload(std::unique_ptr<Node>& node, std::ofstream& file);
	Xml_resource() {};
	Xml_resource(const Xml_resource&) {};
public:
	static Xml_resource* create_simple() { return new Xml_resource(); };
	static std::unique_ptr<Xml_resource> create() { return std::unique_ptr<Xml_resource>(); };
	void load(const char* file_name);
	void print();
	void upload(const char* file_name);
	class iterator {
	private:
		unsigned int current_index;
		std::vector<Node*> memory;

	public:
		iterator(const std::unique_ptr<Node>& node);
		iterator() = delete;
		iterator& operator++();
		iterator& operator--();
		iterator operator++(int);
		iterator operator--(int);
		iterator& operator+=(int n);
		iterator& operator-=(int n);
		bool operator==(const iterator& compare) const { return (memory[current_index] == compare.memory[compare.current_index]); }
		bool operator!=(const iterator& compare) const { return (memory[current_index] != compare.memory[current_index]); }
		Node& operator*() { return *memory[current_index]; }
		Node* operator->() { return memory[current_index]; };
	};
	iterator begin() const { return iterator(root); };
	iterator find_by_name(const std::string name) const;
	iterator find_by_value(const int value) const;
	iterator add(const std::string name, const int value, iterator& it);
};
