#include "Xml_resource.h"

int main() {

	Xml_resource* tree_simple = Xml_resource::create_simple();
	std::unique_ptr<Xml_resource> tree = Xml_resource::create();



	return 1;
}