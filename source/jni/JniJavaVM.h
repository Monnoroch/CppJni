#pragma once
#ifndef JNI_JAVA_VM_H
#define JNI_JAVA_VM_H

#include <JniForwards.h>


namespace JNI {

class JniJavaVM {
public:
	static const jint JNI_DEFAULT_VERSION = JNI_VERSION_1_6;

	JniJavaVM(JavaVM * v, jint ver = JNI_DEFAULT_VERSION);
	JniJavaVM(const JniJavaVM& vm);
	JniJavaVM(JniJavaVM&& vm);
	JniJavaVM(jint ver = JNI_DEFAULT_VERSION);
	JniJavaVM(const std::string& classPath, jint ver = JNI_DEFAULT_VERSION);

	JavaVM * Val();
	const JavaVM * Val() const;
	jint Version() const;
	JavaEnv GetEnv() const;

	bool Valid() const;

	bool operator==(const JniJavaVM& jvm) const;
	bool operator!=(const JniJavaVM& jvm) const;

	~JniJavaVM();

	JniJavaVM& operator=(const JniJavaVM& vm);
	JniJavaVM& operator=(JniJavaVM&& vm);

private:
	JavaVM * val;
	jint version;
	bool doDestroy;

	void Destroy();
};

}

#endif
