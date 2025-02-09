#include "RayFlect.h"

int main(int argc, char* argv[]) {
    RayFlect app;
    if (!app.Init()) {
        return 1;
    }
    app.Run();
    app.Close();
    return 0;
}