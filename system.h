#pragma once
#include <Windows.h>
#include <iostream>
#include "std_defs.h"
#include "sha256.h"

#define HEADER_SIZE 4096

char* operation = nullptr;
char* password = nullptr;


int encrypt_header(std::filesystem::path path)
{
	std::cout << "process filename: " << path.filename() << " ....\n";
	auto close_file = [](FILE* f) {fclose(f); };

	FILE* f = NULL;
	fopen_s(&f, path.generic_string().c_str(), "r+b");
	auto holder = std::unique_ptr<FILE, decltype(close_file)>(f, close_file);
	if (!holder)
		return 1;

	if (fseek(f, 0, SEEK_SET) < 0)
		return 1;

	std::vector<u4byte> header(HEADER_SIZE);

	// C++17 defines .data() which returns a non-const pointer
	size_t read = fread(header.data(), sizeof(u4byte), HEADER_SIZE, f);

	if (fseek(f, 0, SEEK_SET) < 0)
		return 1;

	BYTE hash[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;
	sha256_init(&ctx);
	sha256_update(&ctx, reinterpret_cast<const BYTE *> (password), strlen(password));
	sha256_final(&ctx, hash);

	set_key(reinterpret_cast<const u4byte*> (hash), SHA256_BLOCK_SIZE);
	
	for (int iBlock = 0; iBlock < HEADER_SIZE / 4; iBlock +=4)
	{
		if (_stricmp(operation, "encrypt") == 0)
		{
			encrypt(&header[iBlock], &header[iBlock]);
		}

		if (_stricmp(operation, "decrypt") == 0)
		{
			decrypt(&header[iBlock], &header[iBlock]);
		}
	}

	if (fseek(f, 0, SEEK_SET) < 0)
		return 1;

	fwrite(header.data(), sizeof(u4byte), read, f);
	return 0;
}

