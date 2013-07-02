#pragma once
#ifndef JNI_HELPER_H
#define JNI_HELPER_H

#include <JniForwards.h>


namespace JNI {

class JniHelper {
public:
	static JniJavaVM& GetJavaVM();
	static JniJavaVM& GetJavaVM(const std::string& classPath);
	static JniJavaVM& GetJavaVM(const std::string& classPath, jint ver);

	static JniJavaVM& GetJavaVM(JavaVM * vm);
	static JniJavaVM& GetJavaVM(JavaVM * vm, jint ver);

private:
	static JniJavaVM * javaVmInstance;
};

}

#endif
