#include "quickjs.h"
#include <stdio.h>
#include <string.h>

/**
 * Prints a message.
 */
JSValue js_print(JSContext *ctx, JSValueConst arg, int argc, JSValueConst *argv) {
    size_t len;
    const char *str = JS_ToCStringLen(ctx, &len, argv[0]);
    printf("Output: %s\n", str);
    JS_FreeCString(ctx, str);
    return JS_UNDEFINED;
}

int main() {
    // Create the runtime
    JSRuntime* qjs_rt = JS_NewRuntime();
    if (!qjs_rt) {
        printf("Could not create QuickJS Runtime");
        return 1;
    }

    // Create the context
    JSContext* qjs_ctx = JS_NewContext(qjs_rt);
    if (!qjs_ctx) {
        printf("Could not allocate QuickJS context");
        return 1;
    }

    // Add the global functions
    JSValue global_obj = JS_GetGlobalObject(qjs_ctx);
    JS_SetPropertyStr(qjs_ctx, global_obj, "print", JS_NewCFunction(qjs_ctx, js_print, "print", 1));

    // Test evaluating some code
    const char* code = " \
let blah = \"Hello World!\"; \
print(blah);";
    JSValue val = JS_Eval(qjs_ctx, code, strlen(code), "input.js", 0);

    // Ensure there were no errors
    if (JS_IsException(val)) {
        JSValue exval = JS_GetException(qjs_ctx);
        const char *str = JS_ToCString(qjs_ctx, exval);
        if (str) {
            printf("%s", str);
            JS_FreeCString(qjs_ctx, str);
        } else {
            printf("[[exception]]");
        }
    }

    // Clean up
    JS_FreeValue(qjs_ctx, global_obj);
    JS_FreeContext(qjs_ctx);
    JS_FreeRuntime(qjs_rt);
    return 0;
}
