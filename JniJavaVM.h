#pragma once
#ifndef JNI_JAVA_VM_H
#define JNI_JAVA_VM_H

#include <JniForwards.h>


namespace JNI {

class JniJavaVM {
public:
	static const jint JNI_DEFAULT_VERSION = JNI_VERSION_1_6;

	JniJavaVM(JavaVM * v, jint ver = JNI_DEFAULT_VERSION) : val(v), version(ver), doDestroy(false) {}
	JniJavaVM(const JniJavaVM& vm) : val(vm.val), version(vm.version), doDestroy(false) {}
	JniJavaVM(JniJavaVM&& vm) : val(vm.val), version(vm.version), doDestroy(vm.doDestroy) {
		vm.val = nullptr;
		vm.version = 0;
		vm.doDestroy = false;
	}

	JniJavaVM(jint ver = JNI_DEFAULT_VERSION) : val(nullptr), version(ver), doDestroy(true) {
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

	JniJavaVM(const std::string& classPath, jint ver = JNI_DEFAULT_VERSION) : val(nullptr), version(ver), doDestroy(true) {
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

	JavaVM * Val() {
		return val;
	}

	const JavaVM * Val() const {
		return val;
	}

	jint Version() const {
		return version;
	}

	JavaEnv GetEnv() const;

	bool Valid() const {
		return val != nullptr;
	}

	bool operator==(const JniJavaVM& jvm) const {
		return val == jvm.val;
	}

	bool operator!=(const JniJavaVM& jvm) const {
		return !(*this == jvm);
	}

	~JniJavaVM() {
		Destroy();
	}

	JniJavaVM& operator=(const JniJavaVM& vm) {
		Destroy();
		val = vm.val;
		version = vm.version;
		doDestroy = false;
		return *this;
	}

	JniJavaVM& operator=(JniJavaVM&& vm) {
		std::swap(val, vm.val);
		std::swap(version, vm.version);
		std::swap(doDestroy, vm.doDestroy);
		return *this;
	}

private:
	JavaVM * val;
	jint version;
	bool doDestroy;

	void Destroy() {
		if(doDestroy && Valid()) {
			val->DestroyJavaVM();
			val = nullptr;
		}
	}
};

}

#endif
