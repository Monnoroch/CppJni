#include <JniJavaEnv.h>
#include <JniJavaVM.h>
#include <JniJavaClass.h>


namespace JNI {

JniJavaVM JavaEnv::GetVM() const {
	JavaVM * vm;
	if(val->GetJavaVM(&vm) != 0) {
		printf("Error: cannot get JavaVM from JNIEnv!\n");
		return JniJavaVM(nullptr); // return invalid
	}
	return JniJavaVM(vm, Version());
}

JavaClass JavaEnv::FindClass(const char * name) const {
	return JavaClass(*this, name);
}

JavaClass JavaEnv::FindClass(const std::string& name) const {
	return FindClass(name.c_str());
}

}
