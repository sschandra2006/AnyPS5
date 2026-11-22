#include <cstdlib>
#include <exception>
#include <filesystem>
#include <new>
#include <regex>

namespace {

void Require(bool condition) {
    if (!condition) std::abort();
}

void TestRegexDelivery() {
    bool caught = false;
    try {
        std::regex re;
        re.assign("[a-z-9");
    } catch (const std::regex_error&) {
        caught = true;
    } catch (const std::exception&) {
        caught = true;
    }
    Require(caught);
}

void TestFilesystemDelivery() {
    bool caught = false;
    try {
        const std::filesystem::path illegal("//?/\\\\illegal:path\0/bad");
        (void)std::filesystem::canonical(illegal);
    } catch (const std::filesystem::filesystem_error&) {
        caught = true;
    } catch (const std::exception&) {
        caught = true;
    }
    Require(caught);
}

void TestBadAllocDelivery() {
    bool caught = false;
    try {
        void* block = ::operator new(std::size_t{1} << 46);
        (void)block;
    } catch (const std::bad_alloc&) {
        caught = true;
    }
    Require(caught);
}

}

int main() {
    TestRegexDelivery();
    TestFilesystemDelivery();
    TestBadAllocDelivery();
    return 0;
}
