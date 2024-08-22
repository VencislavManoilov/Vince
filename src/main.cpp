#include <iostream>
#include "cef_app.h"
#include "cef_browser.h"
#include "cef_command_line.h"

class SimpleApp : public CefApp, public CefBrowserProcessHandler {
public:
    SimpleApp() {}

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
        return this;
    }

    void OnContextInitialized() override {
        CefWindowInfo window_info;
        CefBrowserSettings browser_settings;

        window_info.SetAsPopup(NULL, "CEF Simple");

        CefBrowserHost::CreateBrowser(window_info, new SimpleApp(), "https://www.google.com", browser_settings, nullptr, nullptr);
    }

private:
    IMPLEMENT_REFCOUNTING(SimpleApp);
};

int main(int argc, char *argv[]) {
    CefEnableHighDPISupport();

    CefMainArgs main_args(argc, argv);
    CefRefPtr<SimpleApp> app(new SimpleApp);

    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }

    CefSettings settings;
    CefInitialize(main_args, settings, app, nullptr);

    CefRunMessageLoop();

    CefShutdown();
    return 0;
}
