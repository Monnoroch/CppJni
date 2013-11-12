#include <JniJavaVM.h>
#include <JniJavaEnv.h>


namespace JNI {

JniJavaVM::JniJavaVM(JavaVM * v, jint ver) : val(v), version(ver), doDestroy(false) {}
JniJavaVM::JniJavaVM(const JniJavaVM& vm) : val(vm.val), version(vm.version), doDestroy(false) {}
JniJavaVM::JniJavaVM(JniJavaVM&& vm) : val(vm.val), version(vm.version), doDestroy(vm.doDestroy) {
	vm.val = nullptr;
	vm.version = 0;
	vm.doDestroy = false;
}

JniJavaVM::JniJavaVM(jint ver) : val(nullptr), version(ver), doDestroy(true) {
	JNIEnv * env;
	JavaVMInitArgs args;
	args.version = version;
	if(JNI_GetDefaultJavaVMInitArgs(&args) != JNI_OK) {
		printf("JNI_GetDefaultJavaVMInitArgs failed!\n");
		return;
	}
	if(JNI_CreateJavaVM(&val, (void**) &env, &args) != JNI_OK) {
		printf("Error: cannot create JavaVM!\n");
	}
}

JniJavaVM::JniJavaVM(const std::string& classPath, jint ver) : val(nullptr), version(ver), doDestroy(true) {
	JNIEnv * env;
	JavaVMInitArgs args;
	args.version = version;
	JavaVMOption options[1];
	args.nOptions = 1;
	std::string argCP = "-Djava.class.path=" + classPath;
	options[0].optionString = (char*) argCP.c_str();
	args.options = options;
	if(JNI_CreateJavaVM(&val, (void**) &env, &args) != JNI_OK) {
		printf("Error: cannot create JavaVM!\n");
	}
}

JavaVM * JniJavaVM::Val() {
	return val;
}

const JavaVM * JniJavaVM::Val() const {
	return val;
}

jint JniJavaVM::Version() const {
	return version;
}

bool JniJavaVM::Valid() const {
	return val != nullptr;
}

bool JniJavaVM::operator==(const JniJavaVM& jvm) const {
	return val == jvm.val;
}

bool JniJavaVM::operator!=(const JniJavaVM& jvm) const {
	return !(*this == jvm);
}

JniJavaVM::~JniJavaVM() {
	Destroy();
}

JniJavaVM& JniJavaVM::operator=(const JniJavaVM& vm) {
	Destroy();
	val = vm.val;
	version = vm.version;
	doDestroy = false;
	return *this;
}

JniJavaVM& JniJavaVM::operator=(JniJavaVM&& vm) {
	std::swap(val, vm.val);
	std::swap(version, vm.version);
	std::swap(doDestroy, vm.doDestroy);
	return *this;
}

JavaEnv JniJavaVM::GetEnv() const {
	JNIEnv * env = nullptr;
	JavaVMAttachArgs attachArgs;

	jint res = val->GetEnv((void**) &env, Version());
	switch(res)
	{
		case JNI_OK:
			break;
		case JNI_EDETACHED:
			attachArgs.version = Version();
			attachArgs.name = (char*) "";
			attachArgs.group = nullptr;
			res = val->AttachCurrentThread((void**) &env, &attachArgs);
			if(res != JNI_OK)
			{
				printf("getJNIEnv: failed to attach to current thread.");
				return JavaEnv();
			}
			break;
		case JNI_EVERSION:
			printf("getJNIEnv: Unsupported JNI version.");
			return JavaEnv();
		default:
			printf("getJNIEnv: JNI API error.");
			return JavaEnv();
	}
	return JavaEnv(env);
}

void JniJavaVM::Destroy() {
	if(doDestroy && Valid()) {
		val->DestroyJavaVM();
		val = nullptr;
	}
}

}
