#pragma once
#ifndef JNI_JAVA_ENV_H
#define JNI_JAVA_ENV_H

#include <JniForwards.h>


namespace JNI {

class JavaEnv {
	struct JavaEnvIniter {
		JNIEnv * env;
	};
public:
	JavaEnv(JNIEnv * env = nullptr) : val(env) {}
	JavaEnv(const JavaEnvIniter& env) : JavaEnv(env.env) {}
	JavaEnv(const JavaEnv& env) : JavaEnv(env.val) {}
	JavaEnv(JavaEnv&& env) : JavaEnv(env.val) {
		env.val = nullptr;
	}

	bool Valid() const {
		return val != nullptr;
	}

	JNIEnv * Val() const {
		return (JNIEnv*) val;
	}

	jint Version() const {
		return val->GetVersion();
	}

	bool operator==(const JavaEnv& env) const {
		return val == env.val;
	}

	bool operator!=(const JavaEnv& env) const {
		return !(*this == env);
	}

	JavaEnv& operator=(const JavaEnv& env) {
		val = env.val;
		return *this;
	}

	JavaEnv& operator=(JavaEnv&& env) {
		std::swap(val, env.val);
		return *this;
	}

	JniJavaVM GetVM() const;

	JavaClass FindClass(const char * name) const;
	JavaClass FindClass(const std::string& str) const;

private:
	JNIEnv * val;
};

}

#endif
