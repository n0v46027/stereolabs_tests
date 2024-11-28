#include <iostream>
#include <memory>

#include "Core.hpp"
#include "macros.hpp"

int main(void) {
    try
    {
        std::unique_ptr<Core> core = std::make_unique<Core>();
        core->run();
        return OK;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return KO;
    }
    return OK;
}