#include "Xml_resource.h"

int main() {

	std::unique_ptr<Xml_resource> tree = std::move(Xml_resource::create());
	try {
		tree->load("file.txt");
		tree->print();
	}
	catch (const char* error_message)
	{
		std::cout << error_message;
	}

	

	return 0;
}