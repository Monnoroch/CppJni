#include <JniJavaEnv.h>
#include <JniJavaVM.h>
#include <JniJavaClass.h>
#include <JniJavaException.h>


namespace JNI {

JavaEnv::JavaEnv(JNIEnv * env) : val(env) {}
JavaEnv::JavaEnv(const JavaEnvIniter& env) : JavaEnv(env.env) {}
JavaEnv::JavaEnv(const JavaEnv& env) : JavaEnv(env.val) {}
JavaEnv::JavaEnv(JavaEnv&& env) : JavaEnv(env.val) {
	env.val = nullptr;
}

bool JavaEnv::Valid() const {
	return val != nullptr;
}

JNIEnv * JavaEnv::Val() const {
	return (JNIEnv*) val;
}

jint JavaEnv::Version() const {
	return val->GetVersion();
}

bool JavaEnv::operator==(const JavaEnv& env) const {
	return val == env.val;
}

bool JavaEnv::operator!=(const JavaEnv& env) const {
	return !(*this == env);
}

JavaEnv& JavaEnv::operator=(const JavaEnv& env) {
	val = env.val;
	return *this;
}

JavaEnv& JavaEnv::operator=(JavaEnv&& env) {
	std::swap(val, env.val);
	return *this;
}

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

bool JavaEnv::ExceptionCheck() const {
	return val->ExceptionCheck() == JNI_TRUE;
}

void JavaEnv::ExceptionClear() const {
	val->ExceptionClear();
}

void JavaEnv::FatalError(const char * str) const {
	val->FatalError(str);
}

void JavaEnv::FatalError(const std::string& str) const {
	FatalError(str.c_str());
}

void JavaEnv::ExceptionDescribe() const {
	val->ExceptionDescribe();
}

jint JavaEnv::Throw(const JavaException& ex) const {
	return ex.Throw();
}

jint JavaEnv::Throw(const JavaClass& cls, const char * msg) const {
	return val->ThrowNew(cls.Val(), msg);
}

jint JavaEnv::Throw(const JavaClass& cls, const std::string& msg) const {
	return Throw(cls, msg.c_str());
}

JavaException JavaEnv::ExceptionOccurred() const {
	return FromJavaProxy<JavaException>(*this, val->ExceptionOccurred()).Val();
}

}
