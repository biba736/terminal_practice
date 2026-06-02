#include "terminal.h"

int main() {
    te::Terminal terminal(new te::Directory(""));
    terminal.run();
}