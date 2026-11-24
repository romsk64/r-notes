#include <iostream>
#include <fstream>

#include <CLI11.hpp>


int main(int argc, char **argv) {
    CLI::App app{"ASM Reformat - assembly language formatter"};

    std::vector<std::string> filenames;
    bool changeInputFiles;
    bool changeInNewFiles;
    std::string outputFilesNamingFormat;

    app.add_option("files", filenames, "Input files list");
    app.add_flag("-i", "--change-input", changeInputFiles, "Change input files");
    app.add_flag("-n", "--change-new", changeInNewFiles, "Change in new files");
    app.add_flag("-onf",
            "--output-naming-format", outputFilesNamingFormat, "Set the naming format to output files");

    CLI11_PARSE(app, argc, argv);

    return 0;
}
