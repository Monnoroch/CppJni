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
	JavaEnv(JNIEnv * env = nullptr);
	JavaEnv(const JavaEnvIniter& env);
	JavaEnv(const JavaEnv& env);
	JavaEnv(JavaEnv&& env);

	bool Valid() const;
	JNIEnv * Val() const;
	jint Version() const;

	bool operator==(const JavaEnv& env) const;
	bool operator!=(const JavaEnv& env) const;

	JavaEnv& operator=(const JavaEnv& env);
	JavaEnv& operator=(JavaEnv&& env);

	JniJavaVM GetVM() const;

	JavaClass FindClass(const char * name) const;
	JavaClass FindClass(const std::string& str) const;

	bool ExceptionCheck() const;
	void ExceptionClear() const;
	void FatalError(const char * str) const;
	void FatalError(const std::string& str) const;
	void ExceptionDescribe() const;

	jint Throw(const JavaException& ex) const;
	jint Throw(const JavaClass& cls, const char * msg) const;
	jint Throw(const JavaClass& cls, const std::string& msg) const;

	JavaException ExceptionOccurred() const;

private:
	JNIEnv * val;
};

}

#endif
