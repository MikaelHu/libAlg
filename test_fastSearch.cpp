#include <stdio.h>
//#include "fastSearch.h"
#include "fastSearchInsens.h"


int main(int argc, char** argv) {
	constexpr char search_str[]{ "methin" };
	constexpr char search_str1[]{ "metHiN" };
	constexpr char textf[]{ "hgal(&5ngerg(76%%aef ah*9methin*sdgis*^^%%%efg46246243 athwt5435 gat0%^&*%$" };
	
	/*int pos = fastSearch(search_str, textf, std::strlen(textf));
	printf("Find pos = %d\n", pos);*/
	int pos = fastSearchInsens(search_str1, textf, std::strlen(textf));
	printf("Find pos = %d\n", pos);

	return 0;
}