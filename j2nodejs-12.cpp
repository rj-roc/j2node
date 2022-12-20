// j2nodejs-12.cpp: 定义应用程序的入口点。
//


/*
* j2c2nodejs c
*/
// com_j2nodejs_NodeJS.cpp: 定义应用程序的入口点。
//

#include <jni.h>

#include <v8.h>
#include <libplatform/libplatform.h>

#include <node.h>

#include "j2nodejs-12.h"
#include <uv.h>

using namespace std;
using namespace v8;
using namespace node;

//在node环境运行js
static void startNode(const char* srcpit);

//启动v8
static void startV8();

static bool v8Start = false;

static unique_ptr<MultiIsolatePlatform> staticPlatform;

static Environment* staticEnv;

static int argc = 1;
static char* argv[] = { "j2nodejs-12" };
static vector<string> args;
static vector<std::string> exec_args({});

JNIEXPORT void JNICALL Java_com_j2nodejs_NodeJS_nodeStart
(JNIEnv* env, jobject obj, jstring script) {
	const char* scriptChar = env->GetStringUTFChars(script, NULL);
	startNode(scriptChar);
}

void startNode(const char* srcpit) {
	startV8();

	// Set up a libuv event loop.
	uv_loop_t loop;
	int ret = uv_loop_init(&loop);

	if (ret != 0) {
		fprintf(stderr, "%s: Failed to initialize loop: %s\n",
			args[0].c_str(),
			uv_err_name(ret));
		return;
	}

	std::shared_ptr<ArrayBufferAllocator> allocator = ArrayBufferAllocator::Create();
    MultiIsolatePlatform* platform = staticPlatform.get();
	Isolate* isolate = NewIsolate(allocator.get(), &loop, platform);

	if (isolate == nullptr) {
		fprintf(stderr, "%s: Failed to initialize V8 Isolate\n", args[0].c_str());
		return;
	}

	{
        Locker locker(isolate);
        Isolate::Scope isolate_scope(isolate);

        // Create a node::IsolateData instance that will later be released using
        // node::FreeIsolateData().
        std::unique_ptr<IsolateData, decltype(&node::FreeIsolateData)> isolate_data(
            node::CreateIsolateData(isolate, &loop, platform, allocator.get()),
            node::FreeIsolateData);

        // Set up a new v8::Context.
        HandleScope handle_scope(isolate);
        Local<Context> context = node::NewContext(isolate);
        if (context.IsEmpty()) {
            fprintf(stderr, "%s: Failed to initialize V8 Context\n", args[0].c_str());
            return ;
        }

        // The v8::Context needs to be entered when node::CreateEnvironment() and
        // node::LoadEnvironment() are being called.
        Context::Scope context_scope(context);

        // Create a node::Environment instance that will later be released using
        // node::FreeEnvironment().
         std::unique_ptr<Environment, decltype(&node::FreeEnvironment)> env(
            node::CreateEnvironment(isolate_data.get(), context, args, exec_args),
            node::FreeEnvironment);
         staticEnv = env.get();

        // Set up the Node.js instance for execution, and run code inside of it.
        // There is also a variant that takes a callback and provides it with
        // the `require` and `process` objects, so that it can manually compile
        // and run scripts as needed.
        // The `require` function inside this script does *not* access the file
        // system, and can only load built-in Node.js modules.
        // `module.createRequire()` is being used to create one that is able to
        // load files from the disk, and uses the standard CommonJS file loader
        // instead of the internal-only `require` function.
        MaybeLocal<Value> loadenv_ret = node::LoadEnvironment(staticEnv, srcpit);

        if (loadenv_ret.IsEmpty())  // There has been a JS exception.
            return ;

        {
            // SealHandleScope protects against handle leaks from callbacks.
            SealHandleScope seal(isolate);
            bool more;
            do {
                uv_run(&loop, UV_RUN_DEFAULT);

                // V8 tasks on background threads may end up scheduling new tasks in the
                // foreground, which in turn can keep the event loop going. For example,
                // WebAssembly.compile() may do so.
                platform->DrainTasks(isolate);

                // If there are new tasks, continue.
                more = uv_loop_alive(&loop);
                if (more) continue;

                // node::EmitBeforeExit() is used to emit the 'beforeExit' event on
                // the `process` object.
                node::EmitBeforeExit(staticEnv);

                // 'beforeExit' can also schedule new work that keeps the event loop
                // running.
                more = uv_loop_alive(&loop);
            } while (more == true);
        }

        // node::EmitExit() returns the current exit code.
        node::EmitExit(staticEnv);

        // node::Stop() can be used to explicitly stop the event loop and keep
        // further JavaScript from running. It can be called from any thread,
        // and will act like worker.terminate() if called from another thread.
        node::Stop(staticEnv);
	}
}

void startV8()
{
    if (v8Start) {
        return;
    }
    char** tempArgv = uv_setup_args(argc, argv);
    vector<string> tempArgs(tempArgv, tempArgv + argc);
    args = tempArgs;
	vector<string> errors;
	int exit_code = node::InitializeNodeWithArgs(&args, &exec_args, &errors);
	for (const std::string& error : errors) {
		fprintf(stderr, "%s:\n", error.c_str());
	}
	if (exit_code != 0) {
		fprintf(stderr, "node start fail\n");
		return;
	}
	//启动node
	staticPlatform = MultiIsolatePlatform::Create(4);
	V8::InitializePlatform(staticPlatform.get());
	V8::Initialize();
	v8Start = true;
}

int main(int argc, char* argv[]) {
	startNode("const { Worker, isMainThread, parentPort, workerData } = require('worker_threads');  if (isMainThread) {      var mainWorker = new Worker('./index.js');      mainWorker.on('message', (res) => {          if (res == 'close') {              mainWorker.terminate();          }      });  } else {  }");
    //startNode("console.log(123)");
    return 1;
}