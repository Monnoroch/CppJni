#include <JniJavaEnv.h>
#include <JniJavaVM.h>
#include <JniJavaClass.h>
#include <JniJavaException.h>


namespace JNI {

JniJavaVM JavaEnv::GetVM() const {
	JavaVM * vm;
	if(val->GetJavaVM(&vm) != JNI_OK) {
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

jint JavaEnv::Throw(const JavaException& ex) const {
	return ex.Throw();
}

jint JavaEnv::Throw(const JavaClass& cls, const char * msg) const {
	return val->ThrowNew(cls.Val(), msg);
}


JavaException JavaEnv::ExceptionOccurred() const {
	return FromJavaProxy<JavaException>(*this, val->ExceptionOccurred()).Val();
}

}
