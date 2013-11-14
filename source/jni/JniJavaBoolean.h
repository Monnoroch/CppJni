#pragma once
#ifndef JNI_JAVA_OBJECT_BOOLEAN_H
#define JNI_JAVA_OBJECT_BOOLEAN_H

#include <JniForwards.h>
#include <JniJavaEnv.h>

namespace JNI {

class JavaBoolean : public JavaObject {
public:
	JavaBoolean() : JavaObject() {}
	JavaBoolean(JavaEnv env, jobject obj) : JavaObject(env, obj) {}
	JavaBoolean(const JavaBoolean& str) : JavaObject(str) {}
	JavaBoolean(JavaBoolean&& str) : JavaObject(str) {}
};

}

#endif
