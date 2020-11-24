#ifndef __CREATE_TEST_DIRECTORIES_H
#define __CREATE_TEST_DIRECTORIES_H

#include <filesystem>
#include <fstream>

namespace Tests
{
void createTestDirectory()
{
	auto directoryName = "test_files";

	if (std::filesystem::exists(directoryName))
		return;

	auto readmeFileName = "README.txt";
	auto readmeContent =
		"This folder contains temporary files created during tests.\n"
		"It can be safely removed";

	auto path = std::filesystem::path(directoryName);
	std::filesystem::create_directory(path);
	std::ofstream ofs(path / readmeFileName);
	ofs << readmeContent;
	ofs.close();
}

} // namespace Tests

#endif // __CREATE_TEST_DIRECTORIES_H
